# algorithms

## sorting

### find the Kth max/min element in a N size array.(quick sort、middle element, top Ks elements)

### Chang an array to zigzag format (A1< A2 > A3 < A4 > A5...)

### Given an array of N size, A1, A2...An and w weighted array W1, W2, .. Wn who's sum equals to 1. Find the element Ak, that the sum of weights who's value is less than Ak less than 1/2, and the sum of weights who's value is greater than Ak more than 1/2.

### 一个数组，找到出现次数最多的数，如果数组是有序的，不用hashmap.

## DP

## N Queue Problem。

### 10个台阶，每次只能跨1步或者2步，求到第10步总共有多少总方法。

### 丢棋子问题，K层楼，M个棋子，用最小次数找到杯子会摔坏的最高楼层。
[DropPieces](./Codeforces/dp/ThrowPieces.cpp)

### M和N长的字符串中最长重复部分。

## Graph

### 给一个有向图，知道该有向图中各个节点的入度和出度，求有向图中的所有环。

## Array

### Every digit represent three alphabet in phone. You're giving a sequence of digits. Write down all strings this sequence may represent.

### There're N numbers from 1..N. Maybe some of it is duplicated. Check whether the array is duplicated or not.

### Find all subarrays of an array[1..1000] that sums to 1000.

### Given an array and a constant number K. Find a1+a2=K.

### Simulate Queue using Stack.

### Combine two sorted arrays.

### 奇数个整数N个，只有一个数重复odd次，其他重复even次，找到这个重复odd次的数字。

## String

### Check if a string is circled.

### Reverse a String.

## Tree

### Retrieve tree (pre-order, mid-order, after-order, layered-order, use O(1) space)

### Given two tree nodes, find their nearest ancestor.

## Bits

### Count 1 in a bit format number.

## Arithmetic

###  acb - bca = abc. a, b, c are digital number of [0-9], find a, b, c.

### what's the last digit of 2007^2007?

### find c+e+g
```
a + b + c 
        d
        e + f + g
                h
                i
```
abc,cde,efg,ghi=13

### How many 0s in N!?

## Analytic

## 建一个data structure 表示没有括号的表达式，而且找出所有等价的表达式.

### There're three buskets, one fulfilled with oranges, one fulfilled with apples, and one have both oranges and apples. They all have labels, but it seems that all these labels are wrong. Can you correct these labels by just choose one fruit from a single buskets?

### Given two buskets, one can take 5(9) gallons and 3(4) gallons for another. Give us 4(6) gallons.

### 有两个沙漏，一个7分钟，一个4分钟，量出9分钟。

### 3:15时，分针和时针成几度。H:M时，成几度。

### Given two buskets, one can take A gallons and B gallons for another. Give us C gallons.

### There're 21(64,N) coins and one is heavier than others. How many check times would you take to find the heavier one?
I may take 3 times to find the heavier one. At first time, I'll pick 7 coins and another 7 coins, and check if they are equal weighted. It can be seen that the heavier coin is in the remain 7 coins if they are equal. Otherwise the heavier one is in the heavier 7coins.
And then I'll pick 2 coins and another 2 coins from heavier 7 coins. And check if they are weights is equal or not. If they're not equal, I just split these 2 coins again, and find the heavier one. If they're equal, so I'll check the remaining 3 coins by choosing 2 of them, and put them on the call.

### Four passengers are going through an bridge with only one light. They must take the light if they need to go through the bride. They have different speed. Ta <= Tb <= Tc <= Td. What's the minimal time will take if they all pass through the bride?
A,B,C,D <br>
C,D  (Tb) A, B<br>
A,C,D(Ta) B<br>
A (Td) B,C,D<br>
A,B(Tb)C,D<br>
<Tb>A,B,C,D<br>
total time: Ta+ 3 * tb + Td

### 用多少网球可以把公交车塞满？

### 四张牌，牌的一面分别是E,G,4,5。如果牌的一面是元音字母，另一面是偶数，要验证这个原则是不是正确，应翻开哪张牌?
应该翻E和5。

### 一个立方体，六面涂了颜色，将它分成1000个小立方体，问至少有两面涂有颜色的小立方体有多少个？

### 小船过河，有两组人3个M和3个C，小船最多可以载两个人，原则是河一边的M的人不能多于另一边C人数，需要多少次。

### 36匹马，6个跑道，怎么用最少的比赛次数，找到跑得最快的三匹马。

### 三个跑道，N匹马，需要跑多少次，才能对所有马进行的速度进行排序。二个跑道?

### 三个房间里面有3个人，选出最高的那个人，你只能选择当前房间的人，或者你没有进去过房间的人。

### 一条河，两岸各有一个城市，修一座与岸垂直的桥，使A、B的距离最短。

### 从0开始，第20号位置有一颗地雷，安全越过这颗地雷的概率有多少。

### 在河面上有一些荷叶，荷叶上有一只青蛙，在河里有一条鱼，这条鱼不知道青蛙在哪里。每次这条鱼选择一个荷叶，要是这只青蛙在这片荷叶上，那么这条鱼就能吃掉这只青蛙。这只青蛙也有选择，它能感知这条鱼要越出，能选择左右相邻的一片荷叶跳过去。有什么策略可以吃到这只青蛙。

### 烧绳问题，得到1/4时间。

### 100个球，50个红，50个蓝，2个盒子，把球都放进去，一个人可以随便从哪个盒子里拿球，如果他取到蓝，我赢，否则我输。如何放这些球，使我赢的几率更大。

### 有三种颜色的球，红色13(A)，绿色16(B)，黄色17(C)。有一种方法可以使球变色，拿出两个不同颜色的球，就能变成第三种颜色。有没有可能使球全部变成同一种颜色？

### 两个骰子，扔10次，至少一次为12的概率是多少？M个骰子，扔N次，至少一次为6*M的概率是多少?