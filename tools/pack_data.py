#!/usr/bin/env python

import zlib
import os
import struct

def filter_file(filename):
	if (filename[0] == '.'):
		# exclude files starting with '.' (like .DS_Store)
		return False
	return True

class DataPacker(object):
	"""Packs all files in a certain directory into a zlib compressed file"""

	def __init__(self):
		self.output_data = ''

	def pack(self, input_dir, output_file):
		self.input_dir = input_dir

		for root, dirs, files in os.walk(input_dir):
			files = filter(filter_file, files)
			# convert to filepaths
			files = map(lambda f:os.path.join(root, f), files)
			# compress files
			map(self.compress_file, files)
		
		self.write_file(output_file)

	def compress_file(self, filepath):
		# remove the input_dir from the filepath to get the filename
		filename = filepath.replace(self.input_dir + os.sep, '')
		print 'Compressing ' + filename
		with open(filepath, 'rb') as f:
			compressed_data = zlib.compress(f.read())
			print os.path.getsize(filepath), '->', len(compressed_data)
			self.output_data += filename
			self.output_data += '\n'
			self.output_data += struct.pack('i', len(compressed_data))
			self.output_data += '\n'
			self.output_data += compressed_data

	def write_file(self, filepath):
		print 'Writing ' + filepath
		with open(filepath, 'wb') as f:
			f.write(self.output_data)


def main():
	data_packer = DataPacker()
	data_packer.pack("../bin/data", "data.pack")

if __name__ == '__main__':
	main()