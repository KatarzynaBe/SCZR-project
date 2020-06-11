cmake_minimum_required(VERSION 3.10)

project(SCZR-project)
add_library(producer-lib STATIC producer.cpp)
target_include_directories(producer-lib PRIVATE ../Others)
target_link_libraries(producer-lib others-lib)
