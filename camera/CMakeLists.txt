# 使いたい名前でTARGETに入れる(defineみたいなもの)
set(TARGET capture2)

# 使用するCMakeの最低バージョンを2.8に設定
cmake_minimum_required(VERSION 2.8)
# プロジェクト名
project(${TARGET})
# OpenCVのパッケージを探す
find_package(OpenCV REQUIRED)
# インクルードディレクトリ
include_directories(${OpenCV_INCLUDE_DIRS})
# 実行ファイルを作成
add_executable(${TARGET} ${TARGET}.cpp)
# OpenCVライブラリへのリンクを追加
target_link_libraries(${TARGET} ${OpenCV_LIBS})
