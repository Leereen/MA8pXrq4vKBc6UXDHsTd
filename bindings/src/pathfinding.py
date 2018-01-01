from ctypes import CFUNCTYPE, POINTER, cdll, c_int, c_char, c_char_p, c_bool

DIJKSTRA = 0
ASTAR_MANHATTAN = 1


class FindPath(object):

    def __init__(self, lib_path):
        self._path = lib_path
        self._proto = CFUNCTYPE(
            c_int,          # return type
            c_int, c_int,   # start X & Y
            c_int, c_int,   # target X & Y
            c_char_p,       # map
            c_int, c_int,   # map width & height
            POINTER(c_int), # output buffer
            c_int,          # buffer size
            c_bool,         # early_break (opt)
            c_int           # pathfinding algorithm
        )
        self._function = self._load_function()

    def _load_function(self):
        libpathfinding = cdll.LoadLibrary(self._path)
        return self._proto(("FindPath", libpathfinding))


    def find_path(self, start_x, start_y, target_x, target_y,
                  array, array_width, array_height,
                  out_buffer, out_buffer_size,
                  early_break=True, algo=DIJKSTRA):
        # initialization of RW buffer to be filled by C library
        buffer = (c_int * out_buffer_size)(*([-1]*out_buffer_size))
        result = self._function(c_int(start_x), c_int(start_y),
                                c_int(target_x), c_int(target_y),
                                (c_char * len(array))(*array),
                                c_int(array_width), c_int(array_height),
                                buffer,
                                c_int(out_buffer_size),
                                c_bool(early_break),
                                c_int(algo))
        for value in buffer:
            out_buffer.append(value)
        return result
