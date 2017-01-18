#ifndef DEBUG_H
#define DEBUG_H

#include <Definitions.h>

#ifdef DEBUG
    #define ASSERT(expression, message) \
    if (!expression) { \
        printf(#message); \
        exit(1); \
    } \
    else { }

#else
    #define ASSERT(expression, message)
#endif

#endif /*DEBUG_H*/
