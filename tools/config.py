'''config.py

Contains the common configuration for the tools of the engine'''

namespace = 'he'
dll_header = 'DllExport.h'
dll_define = 'ENGINE_API'

include_path = '../src'
src_path = '../src'

include_guard_exclude_dirs = ['json']
include_guard_exclude_files = ['base64.h', 'GLee.h']

endl = '\r\n'
separator = '//' + '-' * 76 + '//' + endl

