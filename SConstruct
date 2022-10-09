import os
cpp_path = ['./']
libs = []
flags = ['-g']

env = Environment(ENV = {'PATH' : os.environ['PATH']} , CXX="g++", CC = "g++", tools = ["mingw"])

platform = env['PLATFORM']
print("platform:",platform)
if platform == "win32":
    env['ENV']['TMP'] = os.environ['TMP']
    libs = ['glfw3', 'opengl32', 'gdi32']

elif platform == 'unix':
    libs = ['glfw3', 'dl']



env.Program('main', ['main.cpp', 'driver/glad.c'], CPPPATH=cpp_path, LIBS=libs, CCFLAGS=flags)
