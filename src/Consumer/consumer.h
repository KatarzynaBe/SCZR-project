#ifndef SCZR_PROJECT_CONSUMER_H
#define SCZR_PROJECT_CONSUMER_H

std::string textFromSharedMemory();

/**
 * Receive a text from the message queue
 */
std::string textFromMessageQueue();

#endif //SCZR_PROJECT_CONSUMER_H
