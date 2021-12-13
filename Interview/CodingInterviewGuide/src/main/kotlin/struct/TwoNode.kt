package struct

class TwoNode(var value: Int, var leftNode: TwoNode?=null, var rightNode: TwoNode?=null) {

    override fun toString(): String {
        var left = if (leftNode != null) leftNode!!.value.toString() else ""
        var right = if (rightNode != null) rightNode!!.value.toString() else ""

        return "value: $value, left: $left, right: $right"
    }
}
