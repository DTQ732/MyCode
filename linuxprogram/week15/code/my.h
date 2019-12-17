#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <error.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>
#define LOOP 1000000
#define NUM 4
#define TN 100
#define WRITER_FIRST
