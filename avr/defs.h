#ifndef __DEFSH__
#define __DEFSH__



void print(char *fmt, ... );

#define PRINT(fmt, ...) \
 cli();print(fmt, __VA_ARGS__);sei()

#define TRACE(fmt, ...) \
 cli();print(fmt, __VA_ARGS__);sei()

#endif //__DEFSH__
