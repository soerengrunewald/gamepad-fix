project('fix-gamepad', 'c')

executable('fix-gamepad',
  'main.c',
  install : true,
  dependencies : dependency('libusb-1.0'))

install_data('99-gamepad-fix.rules',
  install_dir : get_option('sysconfdir') / 'udev' / 'rules.d')
