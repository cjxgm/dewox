
debug = int(ARGUMENTS.get('debug', 0))
Dfullscreen = '-DFULLSCREEN ' if int(ARGUMENTS.get('fullscreen', 0)) else ''
defines = Dfullscreen + ' -Isrc/dui -Isrc/dutil '

# environments
debug_gcc = '-g -DDEBUG' if debug else '-s -O2'
env_gcc = Environment(CC = 'gcc', \
					CCFLAGS = defines + debug_gcc + ' -Wall -Werror', \
					LIBS = Split('glut openal m GL'))

debug_clang = '-g -DDEBUG' if debug else '-O2'
env_clang = Environment(CC = 'clang', \
					CCFLAGS = defines + debug_clang + ' -Wall -Werror', \
					LIBS = Split('glut openal m GL'))

env = env_gcc	# default environment
if ARGUMENTS.get('CC', 0) == 'clang':
	env = env_clang

Export('env')
SConscript('src/SConscript')

Help('''
Usage: scons [options]

* [...] means it's default.

	fullscreen=1,[0]    enable fullscreen or not
	debug=1,[0]         enable debugging  or not
	CC=clang,[gcc]      use which compiler
''')
