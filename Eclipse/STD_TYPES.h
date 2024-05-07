
#ifndef _STD_TYPES_H
#define _STD_TYPES_H

typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long  int u32;

typedef signed char s8;
typedef signed short int s16;
typedef signed long  int s32;

typedef float  f32;
typedef double f64;

typedef enum return_status{
    R_NOK,
    R_OK
}return_status_t;

#define NULL ((void *)0)

#endif
