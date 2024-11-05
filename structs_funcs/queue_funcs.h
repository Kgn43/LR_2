#ifndef QUEUE_FUNCS_H
#define QUEUE_FUNCS_H

#include "generalFuncs.h"
#include "queue.h"

void printQueue(const request& request);
void queuePush(const request& request);
void queuePop(const request& request);
void queueGet(const request& request);


#endif //QUEUE_FUNCS_H
