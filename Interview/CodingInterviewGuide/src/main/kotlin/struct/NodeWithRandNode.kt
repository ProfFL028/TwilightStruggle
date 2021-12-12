package struct

/**
 * a node contain a point points to next node and a rand point pionts to random
 */
class NodeWithRandNode(var value: Int, var next: NodeWithRandNode? = null, var rand: NodeWithRandNode? = null) {
    override fun toString(): String {
        var s = when (next) {
            null -> "null"
            else -> next!!.value
        }
        var r = when (rand) {
            null -> "null"
            else -> rand!!.value
        }

        return "$value->$s, $value(r)->$r"
    }
}
