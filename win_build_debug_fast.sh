cmake . -B build_win -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="build_win_out/build/Debug/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_C_COMPILER=clang \
      -DCMAKE_CXX_COMPILER=clang++ \
      -DCMAKE_SYSTEM_NAME=Windows \
      -DCMAKE_C_COMPILER_TARGET=x86_64-pc-windows-gnu \
      -DCMAKE_CXX_COMPILER_TARGET=x86_64-pc-windows-gnu \

cd build_win

ninja

cd ..