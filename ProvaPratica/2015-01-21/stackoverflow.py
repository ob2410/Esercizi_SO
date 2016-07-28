#!/usr/bin/env python3
from collections import defaultdict
import hashlib
import os
import sys


def md5checksum(filepath):
    with open(filepath, "rb") as afile:
        m = hashlib.md5()
        data = afile.read()
        m.update(data)
    return m.hexdigest()


def calculate_checksums(search_dir):
    checksums = defaultdict(list)

    for root, dirs, files in os.walk(search_dir):
        for filename in files:
            path = os.path.join(root, filename)
            checksum = md5checksum(path)
            checksums[checksum].append(path)
    return checksums


def display_equal_files(checksums):
    for checksum, paths in checksums.items():
        if len(paths) > 1:
            print("MD5 sum: {}".format(checksum))
            for path in paths:
                print("    {}".format(path))


if __name__ == "__main__":

	if (len(sys.argv)>1):
		search_dir = sys.argv[1]
	else:
		search_dir = '.'

	checksums = calculate_checksums(search_dir)
	display_equal_files(checksums)

