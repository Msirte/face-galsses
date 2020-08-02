cmake_minimum_required(VERSION 2.8)

project(face_glasses C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)

find_package(OpenMP)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

include_directories(${CMAKE_CURRENT_LIST_DIR}/include) #ncnn 包含目录路径

link_directories(${CMAKE_CURRENT_LIST_DIR}/lib)        #ncnn 库目录路径

aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/register DIR_REGISTER)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src/recognition DIR_RECOGNITION)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/common)

# file(GLOB MTCNN_SRC ${CMAKE_CURRENT_LIST_DIR}/include/*.h ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

# set(MTCNN_COMPILE_CODE ${MTCNN_SRC})

add_executable(register ${DIR_REGISTER})
add_executable(recognition ${DIR_RECOGNITION})

target_link_libraries(register ${CMAKE_CURRENT_LIST_DIR}/lib/libncnn.a ${OpenCV_LIBS} common) #libncnn.a 路径
target_link_libraries(recognition ${CMAKE_CURRENT_LIST_DIR}/lib/libncnn.a ${OpenCV_LIBS} common) #libncnn.a 路径
