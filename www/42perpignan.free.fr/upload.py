#!/usr/bin/env python3
import sys
import os

__author__ = "Jean Michel Labaise"
__version__ = "0.69.420"
__license__ = "MIT"


def main():
    print("executing python script ...")


if __name__ == "__main__":
    print ("Number of arguments:", len(sys.argv), "arguments")
    print ("\r\nArgument List:", str(sys.argv))
    
    for name, value in os.environ.items():
        print("{0}: {1}".format(name, value))