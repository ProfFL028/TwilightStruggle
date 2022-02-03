package dp


class LongestSequenceSequence {
    companion object {
        fun find(arr: ArrayList<Int>):List<Int> {
            if (arr.isEmpty()) {
                return ArrayList()
            }
            var result = ArrayList<Int>()
            result.add(Int.MAX_VALUE)
            for (k in arr) {
                var editIdx = -1
                for (i in result.size - 1 downTo  0) {
                    if (editIdx == -1) {
                        if (result[i] >= k) {
                            editIdx = i
                        }
                    } else {
                        break
                    }
                }
                if (editIdx == -1) {
                    result.add(k)
                } else {
                    if (arr[arr.size - 1] != k) { // if it is last element, do not check the result array.
                        result[editIdx] = k
                    }
                }
            }
            return result
        }
    }
}

fun main() {
    var arr = arrayListOf<Int>(2,1,3,6,4,8,9,7)
    println(LongestSequenceSequence.find(arr))
}
