#ビルド構成ファイルの作成
cmake . -B build -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="build/build/Debug/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="Debug"

cd build

#ビルド
ninja
