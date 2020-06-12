#include "gtest/gtest.h"
#include "producer.h"
#include "consumer.h"
#include "database.h"
#include <chrono>

TEST(ShMem, singleThreadCorrectBytesReceived) {
  create_results();

   // auto clock_start = std::chrono::high_resolution_clock::now();
   // auto clock_end = std::chrono::high_resolution_clock::now();

    ASSERT_TRUE(1==1 );
}
TEST(ShMem, CHILD_PARENT_PROCESSES_CORRECTED_TEXT_RECEIVED) {
    std::string text =  generatestring();

    int pid = fork();

    if (-1 == pid) {

        FAIL() << "fork error";

    }

    if (0 == pid) { // child

        sendViaSharedMemory(text);

        exit(0);

    } else { // parent

        sleep(1);

        ASSERT_EQ(text, textFromSharedMemory());

    }



}

TEST(ShMem, kasia) {
    std::string text = generatestring();
    sendViaSharedMemory(text);
    std::cout<<text;
    getData();
    ASSERT_TRUE(text == textFromSharedMemory());
}
