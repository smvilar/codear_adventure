'''config.py

Contains the common configuration for the tools of the engine'''

namespace = 'he'
dll_header = 'dllexport.h'
dll_define = 'ENGINE_API'

qtcreator_proj = '../prj/CODEARAdv.pro'
visualstudio_proj = '../prj/CODEARAdv.vcxproj'

include_path = '../src'
src_path = '../src'

include_guard_exclude_dirs = ['json', 'game']
include_guard_exclude_files = ['base64.h', 'GLee.h']

endl = '\r\n'
separator = '//' + '-' * 76 + '//' + endl

