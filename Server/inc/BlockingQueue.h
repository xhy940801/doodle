#ifndef _BLOCKINGQUEUE_H
#define _BLOCKINGQUEUE_H

#include "ArrayBlockingQueue.h"

template <typename T>
using BlockingQueue = ArrayBlockingQueue<T>;

#endif