#include "gtest/gtest.h"
#include "producer.h"
#include "consumer.h"
#include "database.h"

TEST(ShMem, singleThreadCorrectBytesReceived) {
    std::string text = generatestring();//std::string(4095, 'a');
    sendViaSharedMemory(text);
    getData();
  //  generateRandomlyFilledTable();
   // std::cout<< generatestring();
    ASSERT_TRUE(text == textFromSharedMemory());
}
