from numba import cuda
import numba
from .tensor_data import (
    count,
    index_to_position,
    broadcast_index,
    shape_broadcast,
    MAX_DIMS,
)
import numpy
import numpy as np

# This code will CUDA compile fast versions your tensor_data functions.
# If you get an error, read the docs for NUMBA as to what is allowed
# in these functions.

count = cuda.jit(device=True)(count)
index_to_position = cuda.jit(device=True)(index_to_position)
broadcast_index = cuda.jit(device=True)(broadcast_index)


def tensor_map(fn):
    """
    CUDA higher-order tensor map function. ::
      fn_map = tensor_map(fn)
      fn_map(out, ... )
    Args:
        fn: function mappings floats-to-floats to apply.
        out (array): storage for out tensor.
        out_shape (array): shape for out tensor.
        out_strides (array): strides for out tensor.
        out_size (array): size for out tensor.
        in_storage (array): storage for in tensor.
        in_shape (array): shape for in tensor.
        in_strides (array): strides for in tensor.
    Returns:
        None : Fills in `out`
    """

    def _map(out, out_shape, out_strides, out_size, in_storage, in_shape, in_strides):
        # TODO: Implement for Task 3.3.
        i = cuda.blockIdx.x * cuda.blockDim.x + cuda.threadIdx.x
        if i < len(out):
            out_index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
            in_index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
            count(i, out_shape, out_index)
            broadcast_index(out_index, out_shape, in_shape, in_index)
            data = in_storage[index_to_position(in_index, in_strides)]
            map_data = fn(data)
            out[index_to_position(out_index, out_strides)] = map_data

    return cuda.jit()(_map)


def map(fn):
    # CUDA compile your kernel
    f = tensor_map(cuda.jit(device=True)(fn))

    def ret(a, out=None):
        if out is None:
            out = a.zeros(a.shape)

        # Instantiate and run the cuda kernel.
        threadsperblock = 32
        blockspergrid = (out.size + (threadsperblock - 1)) // threadsperblock
        f[blockspergrid, threadsperblock](*out.tuple(), out.size, *a.tuple())
        return out

    return ret


def tensor_zip(fn):
    """
    CUDA higher-order tensor zipWith (or map2) function ::
      fn_zip = tensor_zip(fn)
      fn_zip(out, ...)
    Args:
        fn: function mappings two floats to float to apply.
        out (array): storage for `out` tensor.
        out_shape (array): shape for `out` tensor.
        out_strides (array): strides for `out` tensor.
        out_size (array): size for `out` tensor.
        a_storage (array): storage for `a` tensor.
        a_shape (array): shape for `a` tensor.
        a_strides (array): strides for `a` tensor.
        b_storage (array): storage for `b` tensor.
        b_shape (array): shape for `b` tensor.
        b_strides (array): strides for `b` tensor.
    Returns:
        None : Fills in `out`
    """

    def _zip(
        out,
        out_shape,
        out_strides,
        out_size,
        a_storage,
        a_shape,
        a_strides,
        b_storage,
        b_shape,
        b_strides,
    ):
        # TODO: Implement for Task 3.3.
        i = cuda.blockIdx.x * cuda.blockDim.x + cuda.threadIdx.x
        if i < len(out):
            a_index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
            b_index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
            o_index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
            count(i, out_shape, o_index)
            broadcast_index(o_index, out_shape, a_shape, a_index)
            broadcast_index(o_index, out_shape, b_shape, b_index)
            a_data = a_storage[index_to_position(a_index, a_strides)]
            b_data = b_storage[index_to_position(b_index, b_strides)]
            map_data = fn(a_data, b_data)
            out[index_to_position(o_index, out_strides)] = map_data

    return cuda.jit()(_zip)


def zip(fn):
    f = tensor_zip(cuda.jit(device=True)(fn))

    def ret(a, b):
        c_shape = shape_broadcast(a.shape, b.shape)
        out = a.zeros(c_shape)
        threadsperblock = 32
        blockspergrid = (out.size + (threadsperblock - 1)) // threadsperblock
        f[blockspergrid, threadsperblock](
            *out.tuple(), out.size, *a.tuple(), *b.tuple()
        )
        return out

    return ret


def tensor_reduce(fn):
    """
    CUDA higher-order tensor reduce function.
    Args:
        fn: reduction function maps two floats to float.
        out (array): storage for `out` tensor.
        out_shape (array): shape for `out` tensor.
        out_strides (array): strides for `out` tensor.
        out_size (array): size for `out` tensor.
        a_storage (array): storage for `a` tensor.
        a_shape (array): shape for `a` tensor.
        a_strides (array): strides for `a` tensor.
        reduce_shape (array): shape of reduction (1 for dimension kept, shape value for dimensions summed out)
        reduce_size (int): size of reduce shape
    Returns:
        None : Fills in `out`
    """

    def _reduce(
        out,
        out_shape,
        out_strides,
        out_size,
        a_storage,
        a_shape,
        a_strides,
        reduce_shape,
        reduce_size,
    ):
        # TODO: Implement for Task 3.3.
        i = cuda.blockIdx.x * cuda.blockDim.x + cuda.threadIdx.x
        if i < len(out):
            index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
            offset = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
            count(i, out_shape, index)
            k = index_to_position(index, out_strides)
            for s in range(reduce_size):
                count(s, reduce_shape, offset)
                a_index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
                for j in range(MAX_DIMS):
                    a_index[j] = index[j] + offset[j]
                out[k] = fn(
                    out[k], a_storage[index_to_position(a_index, a_strides)])

    return cuda.jit()(_reduce)


def reduce(fn, start=0.0):
    f = tensor_reduce(cuda.jit(device=True)(fn))

    def ret(a, dims=None, out=None):
        old_shape = None
        if out is None:
            out_shape = list(a.shape)
            for d in dims:
                out_shape[d] = 1
            # Other values when not sum.
            out = a.zeros(tuple(out_shape))
            out._tensor._storage[:] = start
        else:
            old_shape = out.shape
            diff = len(a.shape) - len(out.shape)
            out = out.view(*([1] * diff + list(old_shape)))

        # Assume they are the same dim
        assert len(out.shape) == len(a.shape)

        # Create a reduce shape / reduce size
        reduce_shape = []
        reduce_size = 1
        for i, s in enumerate(a.shape):
            if out.shape[i] == 1:
                reduce_shape.append(s)
                reduce_size *= s
            else:
                reduce_shape.append(1)

        threadsperblock = 32
        blockspergrid = (out.size + (threadsperblock - 1)) // threadsperblock
        f[blockspergrid, threadsperblock](
            *out.tuple(), out.size, *a.tuple(), np.array(reduce_shape), reduce_size
        )
        # START CODE CHANGE
        if old_shape is not None:
            out = out.view(*old_shape)
        # END CODE CHANGE
        return out

    return ret


@cuda.jit()
def tensor_matrix_multiply(
    out,
    out_shape,
    out_strides,
    out_size,
    a_storage,
    a_shape,
    a_strides,
    b_storage,
    b_shape,
    b_strides,
):
    """
    CUDA tensor matrix multiply function.
    Should work for any tensor shapes that broadcast as long as ::
        assert a_shape[-1] == b_shape[-2]
    Args:
        out (array): storage for `out` tensor
        out_shape (array): shape for `out` tensor
        out_strides (array): strides for `out` tensor
        out_size (array): size for `out` tensor.
        a_storage (array): storage for `a` tensor
        a_shape (array): shape for `a` tensor
        a_strides (array): strides for `a` tensor
        b_storage (array): storage for `b` tensor
        b_shape (array): shape for `b` tensor
        b_strides (array): strides for `b` tensor
    Returns:
        None : Fills in `out`
    """

    # TODO: Implement for Task 3.4.
    i = cuda.blockIdx.x * cuda.blockDim.x + cuda.threadIdx.x
    if i < out.size:
        out_index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
        count(i, out_shape, out_index)
        pos = index_to_position(out_index, out_strides)

        a_index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
        broadcast_index(out_index, out_shape, a_shape, a_index)
        a_index[len(a_shape) - 2] = out_index[len(out_shape) - 2]

        b_index = numba.cuda.local.array(MAX_DIMS, dtype=numba.int32)
        broadcast_index(out_index, out_shape, b_shape, b_index)
        b_index[len(b_shape) - 1] = out_index[len(out_shape) - 1]
        sum_out = 0
        for k in range(a_shape[-1]):
            a_index[len(a_shape) - 1] = k
            a_start = index_to_position(a_index, a_strides)
            b_index[len(b_shape) - 2] = k
            b_start = index_to_position(b_index, b_strides)
            sum_out += a_storage[a_start] * b_storage[b_start]
        out[pos] = sum_out


def matrix_multiply(a, b):
    """
    Tensor matrix multiply
    Should work for any tensor shapes that broadcast in the first n-2 dims and
    have ::
        assert a.shape[-1] == b.shape[-2]
    Args:
        a (:class:`Tensor`): tensor a
        b (:class:`Tensor`): tensor b
    Returns:
        :class:`Tensor` : new tensor
    """

    ls = list(shape_broadcast(a.shape[:-2], b.shape[:-2]))
    ls.append(a.shape[-2])
    ls.append(b.shape[-1])
    assert a.shape[-1] == b.shape[-2]
    out = a.zeros(tuple(ls))
    threadsperblock = 32
    blockspergrid = (out.size + (threadsperblock - 1)) // threadsperblock
    tensor_matrix_multiply[blockspergrid, threadsperblock](
        *out.tuple(), out.size, *a.tuple(), *b.tuple()
    )

    return out


class CudaOps:
    map = map
    zip = zip
    reduce = reduce
    matrix_multiply = matrix_multiply