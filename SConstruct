#!python

import os, subprocess, platform, sys, glob


def add_sources(sources, dir, extension, ignores=[]):
    for f in os.listdir(dir):
        if f.endswith('.' + extension):
            ignore = False
            for i in ignores:
                if f.endswith(i):
                    ignore = True
            if not ignore:
                sources.append(dir + '/' + f)

# Try to detect the host platform automatically
# This is used if no `platform` argument is passed
if sys.platform.startswith('linux'):
    host_platform = 'linux'
elif sys.platform == 'darwin':
    host_platform = 'osx'
elif sys.platform == 'win32':
    host_platform = 'windows'
else:
    raise ValueError('Could not detect platform automatically, please specify with platform=<platform>')

opts = Variables([], ARGUMENTS)

opts.Add(EnumVariable('platform', 'Target platform', host_platform, ('linux', 'osx', 'windows')))
opts.Add(EnumVariable('bits', 'Target platform bits', 'default', ('default', '32', '64')))
opts.Add(BoolVariable('use_llvm', 'Use the LLVM compiler - only effective when targeting Linux', False))
opts.Add(BoolVariable('use_mingw', 'Use the MinGW compiler - only effective on Windows', False))

# Must be the same setting as used for cpp_bindings
opts.Add(EnumVariable('target', 'Compilation target', 'debug', ('debug', 'release')))
opts.Add(PathVariable('headers_dir', 'Path to the directory containing header files', 'addons'))

bits = opts.args.get('bits', 'default')
if bits == 'default':
    target_arch = 'x86'
elif bits == '64':
    target_arch = 'amd64'
else:
    target_arch ='x86'
env = Environment(TARGET_ARCH=target_arch)
opts.Update(env)
Help(opts.GenerateHelpText(env))

print("================ platform ================")
print(env['platform'])

print("================ TARGET_ARCH ================")
print(env['TARGET_ARCH'])

is64 = sys.maxsize > 2**32
if env['bits'] == 'default':
    env['bits'] = '64' if is64 else '32'

if env['platform'] == 'linux':
    if env['use_llvm']:
        env['CXX'] = 'clang++'

    env.Append(CCFLAGS=['-fPIC', '-g', '-std=c++14', '-Wwrite-strings'])
    env.Append(LINKFLAGS=["-Wl,-R,'$$ORIGIN'"])

    if env['target'] == 'debug':
        env.Append(CCFLAGS=['-Og'])
    elif env['target'] == 'release':
        env.Append(CCFLAGS=['-O3'])

    if env['bits'] == '64':
        env.Append(CCFLAGS=['-m64'])
        env.Append(LINKFLAGS=['-m64'])
    elif env['bits'] == '32':
        env.Append(CCFLAGS=['-m32'])
        env.Append(LINKFLAGS=['-m32'])

elif env['platform'] == 'osx':
    if env['bits'] == '32':
        raise ValueError('Only 64-bit builds are supported for the macOS target.')

    env.Append(CCFLAGS=['-g', '-std=c++14', '-arch', 'x86_64'])
    env.Append(LINKFLAGS=['-arch', 'x86_64', '-framework', 'Cocoa', '-Wl,-undefined,dynamic_lookup'])

    if env['target'] == 'debug':
        env.Append(CCFLAGS=['-Og'])
    elif env['target'] == 'release':
        env.Append(CCFLAGS=['-O3'])

elif env['platform'] == 'windows':
    # This makes sure to keep the session environment variables on Windows
    # This way, you can run SCons in a Visual Studio 2017 prompt and it will find all the required tools
    if env['bits'] == '64' or env['bits'] == '32':
        env.Override(os.environ)

    if host_platform == 'windows' and not env['use_mingw']:
        # MSVC
        env.Append(LINKFLAGS=['/WX'])
        if env['target'] == 'debug':
            env.Append(CCFLAGS=['/EHsc', '/D_DEBUG', '/MDd'])
        elif env['target'] == 'release':
            env.Append(CCFLAGS=['/O2', '/EHsc', '/DNDEBUG', '/MD'])
    else:
        # MinGW
        if env['bits'] == '64':
            env['CXX'] = 'x86_64-w64-mingw32-g++'
        elif env['bits'] == '32':
            env['CXX'] = 'i686-w64-mingw32-g++'

        env.Append(CCFLAGS=['-g', '-O3', '-std=c++14', '-Wwrite-strings'])
        env.Append(LINKFLAGS=['--static', '-Wl,--no-undefined', '-static-libgcc', '-static-libstdc++'])


print("================ bits ================")
print(env['bits'])

print("================ target ================")
print(env['target'])
       

env.Append(CCFLAGS=['/DMY_SERVERCORE_BUILDING_SHARED',
                    '/D__STDC_CONSTANT_MACROS',
                    '/D__STDC_FORMAT_MACROS',
                    '/DHAVE_STRUCT_TIMESPEC',
                    '/DNO_SYS_UN',
                    '/DNO_STRNDUP',
                    '/D_CRT_SECURE_NO_WARNINGS',
                    '/D_ENABLE_ATOMIC_ALIGNMENT_FIX',
                    '/D_CONSOLE']
)

cpp_paths = ['.',env['headers_dir'], 'include', 'include/core', 
            'src',
            'src/thirdparty/stlsoft/STLSoft/include',
            'src/thirdparty/stlsoft/FastFormat/include',
            'src/thirdparty/stlsoft/pantheios/include'
            ]
if host_platform == 'windows' and not env['use_mingw']:
    cpp_paths.append('C:/Program Files (x86)/Visual Leak Detector/include')

env.Append(CPPPATH=cpp_paths)

lib_paths = []
if host_platform == 'windows' and not env['use_mingw']:
    lib_paths = ['C:/Program Files (x86)/Visual Leak Detector/lib/{}'.format(sys.platform)]

env.Append(LIBPATH=lib_paths)

# Generate bindings?
json_api_file = ''

if ARGUMENTS.get('use_custom_api_file', 'no') == 'yes':
    json_api_file = ARGUMENTS.get('custom_api_file', '')
else:
    json_api_file = os.path.join(os.getcwd(), 'godot_api.json')

if ARGUMENTS.get('generate_bindings', 'no') == 'yes':
    # Actually create the bindings here

    import binding_generator

    binding_generator.generate_bindings(json_api_file)

# capnp_kj
capnp_sources = []
capnp_sources.append('src/UsingCapnp.cc')
add_sources(capnp_sources, 'src/capnp', 'cc')
add_sources(capnp_sources, 'src/capnp/kj', 'cc')

capnp_kj = env.StaticLibrary(
    target='lib/' + env['target'] + '/' + 'capnp_kj', source=capnp_sources
)
env.Append(LIBPATH=['lib/' + env['target']])

print("================ LIBPATH ================")
print(env['LIBPATH'])

# servercore
sources = []
add_sources(sources, 'src', 'cpp')
add_sources(sources, 'src/base', 'cpp')
add_sources(sources, 'src/base', 'c')
add_sources(capnp_sources, 'src/capnp', 'cpp')

sources.append('src/base/timingwheel/timeout/timeout.c')
sources.append('src/base/timingwheel/timeout/timeout-bitops.c')

add_sources(sources, 'src/io', 'cpp')
add_sources(sources, 'src/log', 'cpp')

add_sources(sources, 'src/thirdparty/stlsoft/FastFormat/src', 'cpp')
add_sources(sources, 'src/thirdparty/stlsoft/FastFormat/src/bitbucket', 'cpp')
add_sources(sources, 'src/thirdparty/stlsoft/FastFormat/src/inserters', 'cpp')

add_sources(sources, 'src/thirdparty/stlsoft/pantheios/src/b64', 'c')

sources.append('src/thirdparty/stlsoft/pantheios/src/backends/be.N.c')
sources.append('src/thirdparty/stlsoft/pantheios/src/backends/bec.file.cpp')
sources.append('src/thirdparty/stlsoft/pantheios/src/backends/bec.fprintf.cpp')

add_sources(sources, 'src/thirdparty/stlsoft/pantheios/src/core', 'c')
add_sources(sources, 'src/thirdparty/stlsoft/pantheios/src/core', 'cpp')

sources.append('src/thirdparty/stlsoft/pantheios/src/frontends/fe.N.c')
add_sources(sources, 'src/thirdparty/stlsoft/pantheios/src/inserters', 'cpp', ['m2w.cpp'])

pantheios_sources_c = env.Glob('src/thirdparty/stlsoft/pantheios/src/util/*.c',
                            strings=True,
                            exclude='')
pantheios_sources_cpp = env.Glob('src/thirdparty/stlsoft/pantheios/src/util/*.cpp',
                            strings=True,
                            exclude='')

sources = sources + pantheios_sources_c + pantheios_sources_cpp

platform_libs = []
if env['platform'] == 'windows':
    platform_libs = [
        'kernel32',
        'user32',
        'gdi32',
        'winspool',
        'comdlg32',
        'advapi32',
        'shell32',
        'ole32',
        'oleaut32',
        'uuid',
        'odbc32',
        'odbccp32']

servercore = env.SharedLibrary(
    target='lib/' + env['target'] + '/' + 'servercore',
    source=sources,
    LIBS = platform_libs + ['capnp_kj']
)

'''
sources = []
#add_sources(sources, 'src/core', 'cpp')
add_sources(sources, 'src', 'cpp')

library = env.StaticLibrary(
    target='bin/' + 'libgodot-cpp.{}.{}.{}'.format(env['platform'], env['target'], env['bits']),
    source=sources,
)
'''

Default(capnp_kj, servercore)