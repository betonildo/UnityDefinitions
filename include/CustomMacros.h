#ifndef CUSTOMMACROS_H
#define CUSTOMMACROS_H

#define WRITE_TO_BYTE(v) \
    ((v) | (v) << 8 | (v) << 16 | (v) << 24)

#endif