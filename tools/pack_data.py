#!/usr/bin/env python

import argparse
import zlib
import os
import struct

script_description = 'Packs all the files in a dir tree into a pack'
compress = False

class DataPacker(object):
	"""Packs all files in a certain directory into a zlib compressed file"""

	def __init__(self):
		self.output_data = ''

	def pack(self, input_dir, output_file):
		self.input_dir = input_dir

		for root, dirs, files in os.walk(input_dir):
			files = filter(lambda f:self.filter_file(f, output_file), files)
			# convert to filepaths
			files = map(lambda f:os.path.join(root, f), files)
			# pack files
			map(self.pack_file, files)
		
		self.write_file(output_file)

	def pack_file(self, filepath):
		# remove the input_dir from the filepath to get the filename
		filename = filepath.replace(self.input_dir, '', 1)
		if filename[0] == os.sep:
			filename = filename[1:]
		
		with open(filepath, 'rb') as f:
			data_to_pack = self.prepare_data(f.read())
			data_size = len(data_to_pack)
			print 'Packing', filename, '[', os.path.getsize(filepath), '->', data_size, ']'
			self.output_data += filename
			self.output_data += '\n' # this way we can use getline() to get the filename
			self.output_data += struct.pack('i', data_size)
			self.output_data += data_to_pack

	def prepare_data(self, data):
		if compress:
			return zlib.compress(data)
		else:
			return data

	def write_file(self, filepath):
		print 'Writing ' + filepath
		with open(filepath, 'wb') as f:
			f.write(self.output_data)

	def filter_file(self, filename, output_file):
		if filename == os.path.basename(output_file):
			# exclude the output file
			return False
		if filename[0] == '.':
			# exclude files starting with '.' (like .DS_Store)
			return False
		return True


def setup_args():
	parser = argparse.ArgumentParser(description=script_description)
	parser.add_argument('input_dir', type=str,
						help = "the directory to look for the data")
	parser.add_argument('output_file', type=str,
						help = "the name of the data pack file")

	args = parser.parse_args()
	return args.input_dir, args.output_file

def main():
	input_dir, output_file = setup_args()

	data_packer = DataPacker()
	data_packer.pack(input_dir, output_file)

if __name__ == '__main__':
	main()