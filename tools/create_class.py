#!/usr/bin/env python

import argparse
import config
from config import endl, separator

script_description = 'Creates a class for the engine, with the header file and the source file in the corresponding folder'

def setup_args():
	parser = argparse.ArgumentParser(description=script_description)
	parser.add_argument('module_name', metavar='module', type=str,
						help = "the module where it's gonna be created")
	parser.add_argument('class_name', metavar='class', type=str,
						help = "the name of the class to create")

	args = parser.parse_args()
	return args.module_name, args.class_name

def header_text(class_name):
	include_guard = config.namespace.upper() + '_' + class_name.upper() + '_H'
	text = '#ifndef ' + include_guard + endl
	text += '#define ' + include_guard + endl
	text += separator
	text += '#include "' + config.dll_header + '"' + endl
	text += separator
	text += 'namespace ' + config.namespace + ' {' + endl
	text += separator
	text += 'class ' + config.dll_define + ' ' + class_name + endl
	text += '{' + endl
	text += '};' + endl
	text += separator
	text += '} // end namespace ' + config.namespace + endl
	text += separator
	text += '#endif // ' + include_guard + endl
	return text

def source_text(class_name, header_path):
	text = '#include "' + header_path + '"' + endl
	text += separator
	text += 'using namespace ' + config.namespace + ';' + endl
	text += separator
	return text

def main():
	module_name, class_name = setup_args()

	header_path = (module_name + '/' + class_name + '.h').lower()
	source_path = (module_name + '/' + class_name + '.cpp').lower()

	full_header_path = config.include_path + '/' + header_path
	full_source_path = config.src_path + '/' + source_path

	with open(full_header_path, 'w') as header_file:
		header_file.write(header_text(class_name))

	with open(full_source_path, 'w') as source_file:
		source_file.write(source_text(class_name, header_path))

if __name__ == '__main__':
	main()
