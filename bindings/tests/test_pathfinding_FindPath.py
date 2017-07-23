from unittest import TestCase
from pathlib import Path
from random import randint

from pathfinding import FindPath
import dataset as dataset


class TestPathFinding(TestCase):

    def setUp(self):
        self.path = Path("../build/src/libpathfinding.so")
        self.finder = FindPath(str(self.path.absolute()))


    def test001_ok(self):
        output_buffer = list()
        result = self.finder.find_path(dataset.a1_sx, dataset.a1_sy,
                                       dataset.a1_dx, dataset.a1_dy,
                                       dataset.a1,
                                       dataset.a1_w, dataset.a1_h,
                                       output_buffer,
                                       dataset.a1_path_length)
        self.assertEqual(result, dataset.a1_path_length)
        self.assertEqual(len(output_buffer), result)
        self.assertEqual(output_buffer, dataset.a1_real)


    def test002_truncated_but_no_early_break(self):
        output_buffer = list()
        authorized_size = randint(0, 256) % dataset.a1_path_length
        result = self.finder.find_path(dataset.a1_sx, dataset.a1_sy,
                                       dataset.a1_dx, dataset.a1_dy,
                                       dataset.a1,
                                       dataset.a1_w, dataset.a1_h,
                                       output_buffer,
                                       authorized_size,
                                       False)
        self.assertEqual(result, dataset.a1_path_length)
        self.assertEqual(len(output_buffer), authorized_size)
        self.assertEqual(output_buffer, dataset.a1_real[:authorized_size])


    def test003_truncated_and_early_break(self):
        output_buffer = list()
        authorized_size = randint(0, 256) % dataset.a1_path_length
        result = self.finder.find_path(dataset.a1_sx, dataset.a1_sy,
                                       dataset.a1_dx, dataset.a1_dy,
                                       dataset.a1,
                                       dataset.a1_w, dataset.a1_h,
                                       output_buffer,
                                       authorized_size)
        self.assertEqual(result, -1)
        self.assertEqual(len(output_buffer), authorized_size)
        self.assertEqual(output_buffer, [-1]*authorized_size)
