#include <iostream>
#include "consumer.h"
#include "database.h"
#include <cstring>
#include <string>
#include <sys/mman.h>
#include <fcntl.h>
#include "utilities.h"
#include <mqueue.h>

std::string textFromSharedMemory() {
//    Open shared memory
    int fd = shm_open("/sh_mem", O_RDWR, 0);
    if (fd == -1)
        exitWithError("Consumer can't open the shared memory");
//    Map the data into the caller's address space
    void *mapped_memory = mmap(NULL, kSharedMemoryBufferSize,
                               PROT_READ, MAP_SHARED, fd, 0);
    if (mapped_memory == MAP_FAILED)
        exitWithError("Consumer can't map the memory");
    shm_unlink("/sh_mem");
    return std::string((char *) mapped_memory);
}

std::string textFromMessageQueue() {
    const int kBufferSize = 64;
    char buffer[kBufferSize];
    mqd_t descriptor = mq_open("/test_queue", O_RDONLY);
    if (descriptor == -1) {
        exitWithError("Consumer can't open the queue");
    }
    ssize_t received_bytes_n = mq_receive(descriptor, buffer, kBufferSize, nullptr);
    if (received_bytes_n == -1) {
        exitWithError("Consumer can't receive the data");
    }
    return std::string(buffer, received_bytes_n);
}