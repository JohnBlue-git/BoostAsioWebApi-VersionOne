project('WebApi', 'cpp', version: '1.0', default_options: ['cpp_std=c++20'])

# Boost JSON (if Boost version >= 1.75.0)
boost_dep = dependency('boost', version: '>=1.75.0', required: false, modules: ['json'])
if boost_dep.found()
  add_project_arguments('-DBOOST_JSON', language: 'cpp')
endif

# Compile definitions
add_project_arguments([
  '-DBOOST_ASIO_DISABLE_THREADS',
  '-DBOOST_ALL_NO_LIB',
  '-DBOOST_SYSTEM_NO_DEPRECATED',
  '-DBOOST_ERROR_CODE_HEADER_ONLY',
  '-DBOOST_COROUTINES_NO_DEPRECATION_WARNING'
], language: 'cpp')



# Include directories
inc_dir = include_directories(
  'include',
  'include/server',
  'include/controllers',
  'include/services',
  'include/models',
  'include/serializers'
)
#
inc_dir += include_directories(
  'include/controllers/person',
  'include/models/person',
  'include/serializers/person'
)
inc_dir += include_directories(
  'include/services/person',
)
inc_dir += include_directories(
  'include/services/advance_person',
)
#
inc_dir += include_directories(
  'include/controllers/file',
  'include/services/file',
)

# Source files
# Use glob to find all .cpp files recursively
sources = files('src/**/*.cpp')
# append in subdir via subdir('...')
# .../meson.build
# sources += files(...)

# Options for server type
async_accept = get_option('USE_ASYNC_ACCEPT')
block_accept = get_option('USE_BLOCK_ACCEPT')
if async_accept
  add_project_arguments('-DASYNC_ACCEPT', language: 'cpp')
elif block_accept
  add_project_arguments('-DBLOCK_ACCEPT', language: 'cpp')
else
  add_project_arguments('-DBLOCK_ACCEPT', language: 'cpp')
endif

# Executable
executable('WebApi', sources,
  include_directories: inc_dir,
  cpp_args: ['-Wall', '-Wpedantic', '-Wextra'],
  dependencies: [
    dependency('threads'),
    boost_dep
  ]
)
