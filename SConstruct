import os

env = Environment(CCFLAGS = '-g')
Export( 'env' )

dirs_iter = os.walk(".", topdown=False)
first = last = next(dirs_iter)
for last in dirs_iter:
    pass

sc_scripts = [ os.path.join(p, 'SConscript') for p in last[1] if os.path.exists(os.path.join(p, 'SConscript')) ]

SConscript(sc_scripts)

