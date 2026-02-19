[settings]
os=Windows
arch=x86_64
compiler=clang
compiler.version=18
compiler.cppstd=20
build_type=Release

[conf]
tools.build:compiler_executables={"c": "clang", "cpp": "clang++"}
tools.build:cflags=["--target=x86_64-w64-mingw32"]
tools.build:cxxflags=["--target=x86_64-w64-mingw32"]
tools.build:sharedlinkflags=["--target=x86_64-w64-mingw32"]
tools.build:exelinkflags=["--target=x86_64-w64-mingw32"]

tools.cmake.cmaketoolchain:system_name=Windows

[options]
flatbuffers/*:build_flatc=False