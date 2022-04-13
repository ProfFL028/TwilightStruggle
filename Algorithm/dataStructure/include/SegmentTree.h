#ifndef DATASTRUCTURE_SEGMENTTREE_H
#define DATASTRUCTURE_SEGMENTTREE_H

#include <iostream>
/**
 * Segment tree is a faster way to find the answer of a giving segment of an array. It is especially used when there's a lot of segments and you need to find all these answers.
 * For example if you wanna to find the minimal value of an array from ai to aj.
 * Normally the root of the tree tree[0] stores the result of the whole array, and tree[1] stores the result of the left part of the array, and tree[2] stores the result of the right part of the array.
 * If we store results like this, we need to init, update and query the tree in recursive manner.
 *
 * Instead we store single values in tree[n+i], and for 0<i<n, we store method(tree[i*2], tree[i*2+1]).
 * Although there may exists some tree[x] stores the value represent n-2, n-1,0,1,2, with optimized tree path, these nodes will never be accessed.
 */
namespace tree {
    template<class T, class F=std::function<T(const T &, const T &)>> // notice '<' position in declaring
    class SegmentTree {
    private:
        // size of the original array.
        std::size_t size;
        // statistical method.
        F method;
        // store values of every segment. 0 is useless.
        std::vector<T> tree;
        // statistical default result.
        T result;
    public:
        /**
         * constructor.
         * @param arr data array.
         * @param m statistic method such as sum, min, max.
         * @param _res default result. for sum it is 0, for min it is INT_MAX, for max it is INT_MIN.
         */
        SegmentTree(std::vector<T> &arr, const F &m, const T _res) : method(m), result(_res) {
            size = arr.size();
            tree.assign(size << 1, result);
            // tree[n+i] stores arr[i]
            std::copy(arr.begin(), arr.end(), tree.begin() + size);
            // tree[i] stores method(tree[i*2], tree[i*2+1]
            for (std::size_t i = size - 1; i > 0; i--) {
                tree[i] = method(tree[i << 1], tree[i << 1 | 1]);
            }
        }

        /**
         * query the result from left to right
         * @param l left position.
         * @param r right position.
         * @return result.
         */
        T query(std::size_t l, std::size_t r) {
            l += size, r += size;
            T ans = result;

            while (l <= r) {
                if (l & 1)
                    ans = method(ans, tree[l++]);
                if (r & 1 ^ 1)
                    ans = method(ans, tree[r--]);
                l >>= 1, r >>= 1;
            }

            return ans;
        }

        /**
         * Update value at position. It will also update the related tree values.
         * @param position
         * @param newValue
         */
        void update(std::size_t position, const T newValue) {
            position += size;
            tree[position] = newValue;
            while (position) {
                position >>= 1;
                tree[position] = method(tree[position << 1], tree[position << 1 | 1]);
            }
        }
    };
}
#endif //DATASTRUCTURE_SEGMENTTREE_H
