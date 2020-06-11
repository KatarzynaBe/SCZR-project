# 'Google_test' is the subproject name
project(SCZR-project)

add_executable(Google_Tests_run test.cpp)
target_link_libraries(Google_Tests_run gtest gtest_main producer-lib consumer-lib others-lib)
target_include_directories(Google_Tests_run PRIVATE ../Consumer ../Others ../Producer)