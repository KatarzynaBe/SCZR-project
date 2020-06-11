#include <database.h>
#include "producer.h"

int main(int argc, char *argv[]) {
    sendViaSharedMemory("Hello world");
    generateRandomlyFilledTable();
    return 0;
}