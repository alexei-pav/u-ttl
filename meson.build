project('application', 'cpp')

gtkmm_dep = dependency('gtkmm-4.0', version: '>= 4.6.0')

exe_file = executable('application', 'main.cpp',
  dependencies: gtkmm_dep,
  win_subsystem: 'windows',
)