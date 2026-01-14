cmake_minimum_required(VERSION 3.10)
project(OpenCSGDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSYS2環境用のOpenGL/GLUT/glewのパッケージ
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# GLUTはFreeGLUTとして提供されていることが多い
find_package(GLUT REQUIRED)

# OpenCSGはMSYS2でインストール済みと仮定
find_path(OpenCSG_INCLUDE_DIR OpenCSG.h)
find_library(OpenCSG_LIBRARY NAMES OpenCSG)

# インクルードとライブラリが見つかったか確認
if(NOT OpenCSG_INCLUDE_DIR OR NOT OpenCSG_LIBRARY)
    message(FATAL_ERROR "OpenCSG not found. Please install it via pacman.")
endif()

# ソースファイル
add_executable(${PROJECT_NAME} 
    #HPP
    ${PROJECT_SOURCE_DIR}/../vector.hpp
    ${PROJECT_SOURCE_DIR}/../shapes/cache/circle_cache.hpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/flat_renderfunctions.hpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/solid_renderfunctions.hpp
    ${PROJECT_SOURCE_DIR}/../shapes/shape_list.hpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/shape3D.hpp
    ${PROJECT_SOURCE_DIR}/displaylistPrimitive.hpp

    #CPP
    ${PROJECT_SOURCE_DIR}/../vector.cpp
    ${PROJECT_SOURCE_DIR}/../shapes/cache/circle_cache.cpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/flat_renderfunctions.cpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/solid_renderfunctions.cpp
    ${PROJECT_SOURCE_DIR}/main.cpp

    
)

# インクルードディレクトリ
target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIR}
    ${OpenCSG_INCLUDE_DIR}
)

# リンクするライブラリ
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OpenGL_LIBRARIES}
    opengl32 
    freeglut
    glu32
    opencsg
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARY}
    ${OpenCSG_LIBRARY}
)