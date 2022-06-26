import ctypes
import os
from .lib import core
from ctypes import c_char_p, c_uint32, create_string_buffer

module_path = os.path.dirname(__file__)

__version__ = '0.0.1'

fuzzy_hash_buff = core.fuzzy_hash_buf
fuzzy_hash_buff.argtypes = [c_char_p, c_uint32, c_char_p]
fuzzy_hash_buff.restype = c_uint32


def fuzzy_hash(buf):
    buf = buf.encode('utf-8')
    res = create_string_buffer(0x50000)
    fuzzy_hash_buff(buf, len(buf), res)
    return res.value


fuzzy_compare = core.fuzzy_compare
fuzzy_compare.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
fuzzy_compare.restype = ctypes.c_int


def py_fuzzy_compare(hash1: bytes, hash2: bytes) -> int:
    return fuzzy_compare(
        hash1,
        hash2,
    )
