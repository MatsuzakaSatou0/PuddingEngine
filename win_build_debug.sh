#source setup.shで実行
curl -LsSf https://astral.sh/uv/install.sh | sh

#UV初期化
uv venv env --clear

#UV起動
source env/bin/activate

uv pip install conan

sudo apt install clang lld llvm mingw-w64 g++-mingw-w64-x86-64

conan install .  --output-folder=build_win_out -pr:h=./win.profile -pr:b=default --build=missing -s build_type=Debug

cmake . -B build_win -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="build_win_out/build/Debug/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="Debug" -DCMAKE_C_COMPILER=clang \
      -DCMAKE_CXX_COMPILER=clang++ \
      -DCMAKE_SYSTEM_NAME=Windows \
      -DCMAKE_C_COMPILER_TARGET=x86_64-pc-windows-gnu \
      -DCMAKE_CXX_COMPILER_TARGET=x86_64-pc-windows-gnu \

cd build_win

ninja

cd ..