/*
 * This file represents what producer can do
 */

#ifndef SCZR_PROJECT_PRODUCER_H
#define SCZR_PROJECT_PRODUCER_H

#include <string>

void sendViaSharedMemory(const std::string &message);

void sendViaMessageQueue(const std::string &message);

#endif //SCZR_PROJECT_PRODUCER_H
