#!/usr/bin/env python3

from pathlib import Path
from random import randint
from argparse import ArgumentParser

parser = ArgumentParser(description="Generate a bool array with no consideration for path or whatnot. Just eases the constitution of a dataset.")

parser.add_argument("-w" "--width", metavar="<width (default: 20)>",
                    dest="width", default=20, type=int)
parser.add_argument("-H" "--height", metavar="<heigh (default: <width>)>",
                    dest="height", default=None, type=int)
parser.add_argument("-c", "--chance", metavar="<chance for 1 against 0 (default: 50)>",
                    dest="chance", default=50, type=int,
                    help="Chance to have '1' values against '0' values. 0 means only '0' values in the array, 100 means only '1'.")
parser.add_argument("-o", "--ouput", metavar="<output file> (default: array.txt)",
                    dest="output", default="array.txt", type=str,
                    help="Output file to write the array on. Appends array at the end.")


class Infos(object):

    def __init__(self, args):
        self.width = args.width
        self.height = args.width if args.height is None else args.height
        assert(self.width > 0 and self.height > 0)
        self.chance = args.chance
        assert(0 <= self.chance <= 100)
        self.output = (Path() / args.output).absolute()
        self.array = None


    def _write(self):
        assert(self.array)
        line = 0
        with self.output.open("a+") as filee:
            filee.write("{")
            line = 0
            for value in self.array:
                if not (line % self.width):
                    filee.write("\n  ")
                line += 1
                filee.write("{}, ".format(value))
            filee.write("\n};")


    def _generate(self):
        if self.chance in [0, 100]:
            self.array = [1*bool(self.chance)]*(self.width*self.height)
        else:
            self.array = [1*(randint(0, 100) < self.chance)
                          for i in range(self.width*self.height)]


    def run(self):
        self._generate()
        self._write()


if __name__ == "__main__":

    args = parser.parse_args()
    Infos(args).run()
