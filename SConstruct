import os

env = Environment(CCFLAGS = ['-std=c++11', '-g'])
Export( 'env' )

practices = [
    'cpp_vtable'
]

scons_scripts = [ os.path.join(p, 'SConscript') for p in practices ]

SConscript(scons_scripts)

