import codecs

import numpy as np
import onnx
from onnx_tf.backend import prepare

MAX_LEN = 20

def read_vocab(filename):
    token2id = {}
    id2token = {}
    with codecs.open(filename, encoding='utf-8') as f:
        for token_id, line in enumerate(f):
            token = line.strip()
            # vocab_id is zero base because 0 is for padding
            token2id[token] = token_id + 1
            id2token[token_id + 1] = token
    return token2id, id2token


def main():
    model = onnx.load('examples/pos/model.onnx')
    tf_rep = prepare(model)

    token2id, id2token = read_vocab('examples/pos/vocab/tokens.txt')
    pos2id, id2pos = read_vocab('examples/pos/vocab/pos.txt')

    tokens = ['Time', 'flies', 'like', 'an', 'arrow', '.']
    token_ids = np.zeros((1, MAX_LEN), dtype=np.long)
    mask = np.zeros((1, MAX_LEN), dtype=np.long)
    for i, token in enumerate(tokens):
        token_ids[0, i] = token2id.get(token, token2id['@@UNKNOWN@@'])
        mask[0, i] = 1

    logits = tf_rep.run((token_ids, mask))._0
    tag_ids = np.argmax(logits, axis=-1)[0]
    tag_ids = tag_ids[:len(tokens)]
    print([id2pos[tag_id] for tag_id in tag_ids])


if __name__ == '__main__':
    main()
