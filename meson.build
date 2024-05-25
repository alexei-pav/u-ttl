project('u-ttl', 'cpp', 
        default_options: ['cpp_std=c++20'],
        version: '0.0.1')

deps = dependency('gtkmm-4.0', version: '>= 4.6.0')

inc_dir = include_directories('include/')

src = [
  'src/main.cpp'
]

exe_file = executable('u-ttl', src,
  dependencies: deps,
  win_subsystem: 'windows',
  include_directories: inc_dir,
)