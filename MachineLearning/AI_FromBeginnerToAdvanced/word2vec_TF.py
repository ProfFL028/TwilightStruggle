from __future__ import absolute_import
from __future__ import division
from __future__ import print_function

import collections
import jieba
import re
import random
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
from sklearn.manifold import TSNE

#读取停用词
stop_words=[]
with open("data\stop_words.txt", "r", encoding="utf-8") as f_stopwords:
    for line in f_stopwords:
        #去掉停用词中的回车、换行符、空格
        line = line.replace("\r", "").replace("\n", "").strip()
        #print(line)
        stop_words.append(line)
#打印停用词的长度
print(len(stop_words))
#去掉重复后停用词的长度
stop_words=set(stop_words)
print(len(stop_words))

#文本预处理
#分完词存储列表
raw_word_list = []
rules = u"([\u4e00-\u9fa5]+)"
pattern = re.compile(rules)
f_writer = open("data/Seg_The_Smiling_Proud_Wanderer.txt", "w", encoding="utf-8")
#读取数据集
with open("data/The_Smiling_Proud_Wanderer.txt", "r", encoding="utf-8") as f_reader:
    lines = f_reader.readlines()
    for line in lines:
        # 去掉文本中的回车、换行符、空格
        line = line.replace("\r", "").replace("\n", "").strip()
        if line == "" or line is None:
            continue
        #jieba分词处理
        line = " ".join(jieba.cut(line))
        seg_list = pattern.findall(line)
        # 去掉停用词的列表
        word_list = []
        for word in seg_list:
            if word not in stop_words:
                word_list.append(word)
        if len(word_list) > 0:
            raw_word_list.extend(word_list)
            line = " ".join(word_list)
            # line=" ".join(seg_list)
            f_writer.write(line + "\n")
            f_writer.flush()
f_writer.close()
print(len(raw_word_list))
print(len(set(raw_word_list)))

#文本编码，通过汉字找到相应的编码，通过编码找到相应的汉字
vocabulary_size = len(set(raw_word_list))
words = raw_word_list
#count存放每个词在文本出现的次数
count =[['UNK', '-1']]
count.extend(collections.Counter(words).most_common(vocabulary_size-1))
print("count",len(count))
dictionary = dict()

#词的整形编码
for word, _ in count:
    dictionary[word]=len(dictionary)
data=list()
unk_count = 0
for word in words:
    if word in dictionary:
        index = dictionary[word]
    else:
        index = 0
        unk_count = unk_count+1
    data.append(index)
count[0][1] = unk_count
#根据编码找到相应的词
reverse_dictionary = dict(zip(dictionary.values(), dictionary.keys()))
del words
print(reverse_dictionary[1000])
print(data[:200])

#模型搭建
"""
批量数据生成，在训练之前需要一批一批送入数据
"""

data_index = 0
def generate_batch(batch_size, num_skips, skip_window):
    global data_index
    #声明全局变量
    batch = np.ndarray(shape=(batch_size), dtype=np.int32)
    labels = np.ndarray(shape=(batch_size, 1), dtype=np.int32)
    span = 2 * skip_window + 1

    #对某个单词创建相关样本时使用到的单词数量
    buffer = collections.deque(maxlen=span)
    for _ in range(span):
        buffer.append(data[data_index])
        data_index = (data_index + 1) % len(data)
    for i in range(batch_size // num_skips):
        target = skip_window
        targets_to_avoid = [skip_window]
        for j in range(num_skips):
            while target in targets_to_avoid:
                target = random.randint(0, span - 1)
            targets_to_avoid.append(target)
            batch[i * num_skips + j] = buffer[skip_window]
            labels[i * num_skips + j] = buffer[target]
        buffer.append(data[data_index])
        data_index = (data_index + 1) % len(data)
    return batch,labels
batch, labels = generate_batch(batch_size=128 , num_skips=4 , skip_window=2)

for i in range(10):
    print(batch[i], reverse_dictionary[batch[i]], "-->", labels[i, 0], reverse_dictionary[labels[i, 0]])

#skip-gram model
batch_size = 128  #batch_size为batch大小
embedding_size = 300
skip_window = 2  #skip_window为单词最远可以联系的距离
num_skips = 4  #num_skips为对每个单词生成样本数
valid_window = 100
num_sample = 64
learning_rate = 0.01

#校验集
valid_word = ['令狐冲', '左冷禅', '林平之', '岳不群', '桃根仙']
valid_example = [dictionary[li] for li in valid_word]

#定义skip-gram网络结构
data_index = 0

# 为skip-gram模型生成训练批次
def next_batch(batch_size, num_skips, skip_window):
    global data_index
    assert batch_size % num_skips == 0
    assert num_skips <= 2 * skip_window
    batch = np.ndarray(shape=(batch_size), dtype=np.int32)
    labels = np.ndarray(shape=(batch_size, 1), dtype=np.int32)

    # 得到窗口长度( 当前单词左边和右边 + 当前单词)
    span = 2 * skip_window + 1
    buffer = collections.deque(maxlen=span)
    if data_index + span > len(data):
        data_index = 0
    buffer.extend(data[data_index:data_index + span])
    data_index += span
    for i in range(batch_size // num_skips):
        context_words = [w for w in range(span) if w != skip_window]
        words_to_use = random.sample(context_words, num_skips)
        for j, context_word in enumerate(words_to_use):
            batch[i * num_skips + j] = buffer[skip_window]
            labels[i * num_skips + j, 0] = buffer[context_word]
        if data_index == len(data):
            buffer.extend(data[0:span])
            data_index = span
        else:
            buffer.append(data[data_index])
            data_index += 1

    #回溯一点，以避免在批处理结束时跳过单词
    data_index = (data_index + len(data) - span) % len(data)
    return batch, labels

# 确保在CPU上分配以下操作和变量
# (某些操作在GPU上不兼容)
with tf.device('/cpu:0'):
    # 创建嵌入变量（每一行代表一个词嵌入向量） embedding vector).
    embedding = tf.Variable(tf.random.normal([vocabulary_size, embedding_size]))
    # 构造NCE损失的变量
    nce_weights = tf.Variable(tf.random.normal([vocabulary_size, embedding_size]))
    nce_biases = tf.Variable(tf.zeros([vocabulary_size]))

def get_embedding(x):
    with tf.device('/cpu:0'):
       # 对于X中的每一个样本查找对应的嵌入向量
        x_embed = tf.nn.embedding_lookup(embedding, x)
        return x_embed

def nce_loss(x_embed, y):
    with tf.device('/cpu:0'):
        # 计算批处理的平均NCE损失
        y = tf.cast(y, tf.int64)
        loss = tf.reduce_mean(
            tf.nn.nce_loss(weights=nce_weights,
                           biases=nce_biases,
                           labels=y,
                           inputs=x_embed,
                           num_sampled=num_sample,
                           num_classes=vocabulary_size))
        return loss

# 评估
def evaluate(x_embed):
    with tf.device('/cpu:0'):
         # 计算输入数据嵌入与每个嵌入向量之间的余弦相似度
        x_embed = tf.cast(x_embed, tf.float32)
        x_embed_norm = x_embed / tf.sqrt(tf.reduce_sum(tf.square(x_embed)))
        embedding_norm = embedding / tf.sqrt(tf.reduce_sum(tf.square(embedding), 1, keepdims=True), tf.float32)
        cosine_sim_op = tf.matmul(x_embed_norm, embedding_norm, transpose_b=True)
        return cosine_sim_op


# 定义优化器
optimizer = tf.optimizers.SGD(learning_rate)

# 优化过程
def run_optimization(x, y):
    with tf.device('/cpu:0'):
       # 将计算封装在GradientTape中以实现自动微分
        with tf.GradientTape() as g:
            emb = get_embedding(x)
            loss = nce_loss(emb, y)

        # 计算梯度
        gradients = g.gradient(loss, [embedding, nce_weights, nce_biases])

         # 按gradients更新 W 和 b
        optimizer.apply_gradients(zip(gradients, [embedding, nce_weights, nce_biases]))


# 用于测试的单词
x_test = np.array(valid_example)
num_steps = 2000000
avg_loss = 0
# 针对给定步骤数进行训练
for step in range(num_steps):
    batch_inputs, batch_labels = generate_batch(batch_size, num_skips, skip_window)
    run_optimization(batch_inputs, batch_labels)
    loss = nce_loss(get_embedding(batch_inputs), batch_labels)
    avg_loss = avg_loss + loss

    if step % 5000 == 0:
        if step > 0:
            avg_loss = avg_loss / 5000
        loss = nce_loss(get_embedding(batch_inputs), batch_labels)
        print("step: %i, loss: %f" % (step, loss))
        # print("平均损失在", num_steps, "中为：", avg_loss)

    # 计算验证集合的相似度
    if step % 10000 == 0:
        sim = evaluate(get_embedding(x_test)).numpy()
        for i in range(len(valid_word)):
            val_word = reverse_dictionary[valid_example[i]]
            top_k = 10
            nearest = (-sim[i, :]).argsort()[1:top_k+1]
            sim_str = "与" + val_word + "最近的前10词是"
            for k in range(top_k):
                close_word = reverse_dictionary[nearest[k]]
                sim_str = "%s %s," % (sim_str, close_word)
            print(sim_str)







