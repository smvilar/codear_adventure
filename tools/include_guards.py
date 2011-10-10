#!/usr/bin/env python

import argparse
import os
import config
from config import endl, separator

verbose = False

script_description = 'Checks every header in the engine for the include guards'

def setup_args():
	parser = argparse.ArgumentParser(description=script_description)
	parser.add_argument('--verbose', dest='verbose', action='store_true',
						help='output log stuff')

	global verbose
	verbose = parser.parse_args().verbose

def log(text):
	if verbose: print(text)

def is_header(filename):
	'''Returns if a filename is a .h file'''
	return os.path.splitext(filename)[1] == '.h'

def make_include_guard(filename):
	'''Returns a include guard for a given filename'''
	return config.namespace.upper() + '_' + filename.upper().replace('.', '_')

def include_guard_begin(filename):
	'''Returns the first 2 lines of the include guard'''
	ig = make_include_guard(filename)
	return '#ifndef ' + ig + endl + '#define ' + ig + endl + separator

def include_guard_end(filename):
	'''Returns the last line of the include guard'''
	ig = make_include_guard(filename)
	return endl + separator + '#endif // ' + ig + endl

def check_include_guard(filepath):
	has_ig = False
	ig = None
	with open(filepath) as f:
		prev_line_was_ifndef = False
		for line in f:
			if prev_line_was_ifndef and 'define' in line:
				has_ig = True
				ig = line[line.find(' ') +1:line.find(endl)]
			prev_line_was_ifndef = 'ifndef' in line
	return has_ig, ig

def fix_include_guard(filepath, old_ig, new_ig):
	print(filepath + " had non-standard include guards (" + old_ig + "). Fixing...")
	filetext = ''
	new_filepath = filepath + '.new'
	with open(filepath) as f:
		with open(new_filepath, 'w') as new_f:
			for line in f:
				new_line = line.replace(old_ig, new_ig)
				new_f.write(new_line)
	os.remove(filepath)
	os.rename(new_filepath, filepath)

def add_include_guard(filepath, new_ig):
	print(filepath + " didn't contain include guards. Adding...")
	print("WARNING: TODO!!")

def process_header(filepath):
	log('Processing "' + filepath + '"...')
	filename = os.path.basename(filepath)
	has_ig, ig = check_include_guard(filepath)
	new_ig = make_include_guard(filename)
	if has_ig:
		if ig != new_ig:
			fix_include_guard(filepath, ig, new_ig)
	else:
		add_include_guard(filepath, new_ig)

def walk_dir(path):
	for root, dirs, files in os.walk(path):
		# remove non headers
		files = filter(is_header, files)
		# remove exclude files
		files = filter(lambda f:f not in config.include_guard_exclude_files, files)
		# convert to filepaths
		files = map(lambda f:os.path.join(root, f), files)
		# process them!
		for filename in files:
			process_header(filename)
		# remove exclude dirs
		for exclude_dir in config.include_guard_exclude_dirs:
			if exclude_dir in dirs:
				dirs.remove(exclude_dir)

def main():
	setup_args()
	log('exclude_dirs: ' + str(config.include_guard_exclude_dirs))
	log('exclude_files: ' + str(config.include_guard_exclude_files))
	walk_dir(config.include_path)
	walk_dir(config.src_path)

if __name__ == '__main__':
	main()
