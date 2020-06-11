cmake_minimum_required(VERSION 3.10)

project(SCZR-project)

add_library(consumer-lib STATIC consumer.cpp)
target_include_directories(consumer-lib PRIVATE ../Others)
target_link_libraries(consumer-lib others-lib)
