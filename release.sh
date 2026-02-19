#source setup.shで実行
curl -LsSf https://astral.sh/uv/install.sh | sh

#UV初期化
uv venv env --clear

#UV起動
source env/bin/activate

#conan導入
uv pip install conan

#glfwの依存関係とninjaをインストール
sudo apt install ninja-build
sudo apt install -y build-essential libgl1-mesa-dev libx11-dev libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libxkbcommon-dev pkg-config
sudo apt update && sudo apt install -y \
  libx11-dev libx11-xcb-dev libfontenc-dev libice-dev libsm-dev \
  libxau-dev libxaw7-dev libxcomposite-dev libxdamage-dev \
  libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxres-dev \
  libxss-dev libxt-dev libxtst-dev libxv-dev libxxf86vm-dev \
  libxcb-glx0-dev libxcb-render0-dev libxcb-render-util0-dev \
  libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev \
  libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev \
  libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev \
  libxcb-dri3-dev uuid-dev libxcb-cursor-dev libxcb-dri2-0-dev \
  libxcb-present-dev libxcb-composite0-dev libxcb-ewmh-dev libxcb-res0-dev libxcb-util-dev

#conanのプロフィールを検知
conan profile detect --force

#conanの依存関係の構築
conan install . --output-folder=build --build=missing -s build_type=Release

#ビルド構成ファイルの作成
cmake . -B build_release -G "Ninja" -DCMAKE_TOOLCHAIN_FILE="build/build/Release/generators/conan_toolchain.cmake" -DCMAKE_BUILD_TYPE="Release" 

cd build_release

#ビルド
ninja

cd ..