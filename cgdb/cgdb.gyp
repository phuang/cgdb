{
  'target_defaults': {
    'default_configuration': 'Debug',
    'configurations': {
      'Debug': {
        'define': [
          'DEBUG'
        ],
        'cflags': [
          '-g',
          '-O0',
        ],
      },
      'Release': {
        'cflags': [
          '-O3',
        ],
      },
    }
  },
  'targets': [
    {
      'target_name': 'cgdb',
      'type': 'executable',
      'msvs_guid': '51639a87-5d59-43ff-aea5-4c1f89e9abbb',
      'dependencies': [
        # '../bar/bar.gyp:bar',
      ],
      'defines': [
        # 'DEFINE_FOO',
        # 'DEFINE_A_VALUE=value',
      ],
      'include_dirs': [
        '..',
      ],
      'sources': [
        'main.cc',
        'main_loop.cc',
        'main_loop.h',
        'source.h',
      ],
      'conditions': [
        ['OS=="linux"', {
          'defines': [
            # 'LINUX_DEFINE',
          ],
          'include_dirs': [
            # 'include/linux',
          ],
        }],
        ['OS=="win"', {
          'defines': [
            # 'WINDOWS_SPECIFIC_DEFINE',
          ],
        }, { # OS != "win",
          'defines': [
            # 'NON_WINDOWS_DEFINE',
          ],
        }]
      ],
    },
  ],
}
