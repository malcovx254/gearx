cmake_minimum_required(VERSION 3.10)
project(OpenCSGDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSYS2環境用のOpenGL/GLUT/glewのパッケージ
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# GLUTはFreeGLUTとして提供されていることが多い
find_package(GLUT REQUIRED)



# ソースファイル
add_executable(${PROJECT_NAME} 
    # HPP
    ${PROJECT_SOURCE_DIR}/../vector.hpp
    ${PROJECT_SOURCE_DIR}/../shapes/cache/circle_cache.hpp
    
    ${PROJECT_SOURCE_DIR}/../shapes/2d/shape2D.hpp

    ${PROJECT_SOURCE_DIR}/../shapes/3d/normal.hpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/flat_renderfunctions.hpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/solid_renderfunctions.hpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/shape3D.hpp

    ${PROJECT_SOURCE_DIR}/coord.hpp
    ${PROJECT_SOURCE_DIR}/gizmo.hpp

    # CPP
    ${PROJECT_SOURCE_DIR}/../vector.cpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/normal.cpp
    ${PROJECT_SOURCE_DIR}/../shapes/cache/circle_cache.cpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/flat_renderfunctions.cpp
    ${PROJECT_SOURCE_DIR}/../shapes/3d/solid_renderfunctions.cpp

    # MAIN
    ${PROJECT_SOURCE_DIR}/main.cpp
)

# インクルードディレクトリ
target_include_directories(${PROJECT_NAME} PRIVATE
    ${OpenGL_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIR}
)

# リンクするライブラリ
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OpenGL_LIBRARIES}
    opengl32 
    freeglut
    glu32
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARY}
)