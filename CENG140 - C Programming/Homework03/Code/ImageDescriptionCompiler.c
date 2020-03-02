/****************************************************************************************************************************************************
|
| Flood filling (recursively) a large region will require a large stack size.
|
| Increasing stack size:
|
| On Windows (MinGW gcc, add an argument ) : -Wl,--stack,50000000  (The last number is the desired stack size in bytes)
| On Linux   (Issue a shell command      ) : ulimit -s unlimited
| On WSL     (Windows Subsystem for Linux) : It seems that there is currently no way to increase the stack size, the default is 8192 KB
|
****************************************************************************************************************************************************/




/***************************************************************************************************************************************************/

/* TODO                      */
/* Include header files here */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

/***************************************************************************************************************************************************/




/***************************************************************************************************************************************************/

#if    defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
       #define OS ( "Windows" )  /* This is a Windows environment.                            */
#elif  defined(__linux__)
       #define OS ( "Linux"   )  /* This is a Linux environment (any GNU/Linux distribution). */
#elif  defined(__APPLE__)
       #define OS ( "MacOSX"  )  /* This is a Mac OS X environment.                           */
#endif

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#ifndef PI
  #define PI ( acos( -1.0 ) )
#endif

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#define TRUE             (    1 )
#define FALSE            (    0 )

#define IMAGE_MAX_WIDTH  ( 1000 )
#define IMAGE_MAX_HEIGHT ( 1000 )

/***************************************************************************************************************************************************/




/***************************************************************************************************************************************************/

typedef short int     Coordinate      ;
typedef unsigned char Byte  , Boolean ;
typedef struct rgb    Color , Pixel   ;
typedef struct point  Point           ;
typedef struct image  Image           ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

struct rgb
{
  Byte red   ;
  Byte green ;
  Byte blue  ;
} ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

struct point
{
  Coordinate row ;
  Coordinate col ;
} ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

struct image
{
  unsigned short int   width  ;
  unsigned short int   height ;
  Pixel              * pixels ;
} ;

/***************************************************************************************************************************************************/




/***************************************************************************************************************************************************/

/* Bitmapped fonts (character rasters) are taken from OpenGL implementation. */
/* OpenGL(TM) is a trademark of Silicon Graphics, Inc.                       */
/* Copyright (c) 1993, Silicon Graphics, Inc. All rights reserved.           */

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

#define FIRST_CHARACTER ( ' ' )  /* ASCII Code  32 (Space) */
#define  LAST_CHARACTER ( '~' )  /* ASCII Code 126 (Tilde) */

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

unsigned char characterRasters[][13] =
{                                                                                     /*ASCII*/
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ,    /*  32 */
  {0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18} ,    /*  33 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x36, 0x36, 0x36} ,    /*  34 */
  {0x00, 0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00} ,    /*  35 */
  {0x00, 0x00, 0x18, 0x7e, 0xff, 0x1b, 0x1f, 0x7e, 0xf8, 0xd8, 0xff, 0x7e, 0x18} ,    /*  36 */
  {0x00, 0x00, 0x0e, 0x1b, 0xdb, 0x6e, 0x30, 0x18, 0x0c, 0x76, 0xdb, 0xd8, 0x70} ,    /*  37 */
  {0x00, 0x00, 0x7f, 0xc6, 0xcf, 0xd8, 0x70, 0x70, 0xd8, 0xcc, 0xcc, 0x6c, 0x38} ,    /*  38 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x1c, 0x0c, 0x0e} ,    /*  39 */
  {0x00, 0x00, 0x0c, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c} ,    /*  40 */
  {0x00, 0x00, 0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x18, 0x30} ,    /*  41 */
  {0x00, 0x00, 0x00, 0x00, 0x99, 0x5a, 0x3c, 0xff, 0x3c, 0x5a, 0x99, 0x00, 0x00} ,    /*  42 */
  {0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00} ,    /*  43 */
  {0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ,    /*  44 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00} ,    /*  45 */
  {0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ,    /*  46 */
  {0x00, 0x60, 0x60, 0x30, 0x30, 0x18, 0x18, 0x0c, 0x0c, 0x06, 0x06, 0x03, 0x03} ,    /*  47 */
  {0x00, 0x00, 0x3c, 0x66, 0xc3, 0xe3, 0xf3, 0xdb, 0xcf, 0xc7, 0xc3, 0x66, 0x3c} ,    /*  48 */
  {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78, 0x38, 0x18} ,    /*  49 */
  {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0xe7, 0x7e} ,    /*  50 */
  {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0x07, 0x03, 0x03, 0xe7, 0x7e} ,    /*  51 */
  {0x00, 0x00, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0xff, 0xcc, 0x6c, 0x3c, 0x1c, 0x0c} ,    /*  52 */
  {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xff} ,    /*  53 */
  {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e} ,    /*  54 */
  {0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x03, 0x03, 0xff} ,    /*  55 */
  {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e} ,    /*  56 */
  {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x03, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e} ,    /*  57 */
  {0x00, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x38, 0x38, 0x00, 0x00, 0x00, 0x00} ,    /*  58 */
  {0x00, 0x00, 0x30, 0x18, 0x1c, 0x1c, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x00} ,    /*  59 */
  {0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06} ,    /*  60 */
  {0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00} ,    /*  61 */
  {0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60} ,    /*  62 */
  {0x00, 0x00, 0x18, 0x00, 0x00, 0x18, 0x18, 0x0c, 0x06, 0x03, 0xc3, 0xc3, 0x7e} ,    /*  63 */
  {0x00, 0x00, 0x3f, 0x60, 0xcf, 0xdb, 0xd3, 0xdd, 0xc3, 0x7e, 0x00, 0x00, 0x00} ,    /*  64 */
  {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18} ,    /*  65 */
  {0x00, 0x00, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe} ,    /*  66 */
  {0x00, 0x00, 0x7e, 0xe7, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e} ,    /*  67 */
  {0x00, 0x00, 0xfc, 0xce, 0xc7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xce, 0xfc} ,    /*  68 */
  {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xff} ,    /*  69 */
  {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfc, 0xc0, 0xc0, 0xc0, 0xff} ,    /*  70 */
  {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xcf, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e} ,    /*  71 */
  {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3} ,    /*  72 */
  {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e} ,    /*  73 */
  {0x00, 0x00, 0x7c, 0xee, 0xc6, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06} ,    /*  74 */
  {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xe0, 0xf0, 0xd8, 0xcc, 0xc6, 0xc3} ,    /*  75 */
  {0x00, 0x00, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0} ,    /*  76 */
  {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xdb, 0xff, 0xff, 0xe7, 0xc3} ,    /*  77 */
  {0x00, 0x00, 0xc7, 0xc7, 0xcf, 0xcf, 0xdf, 0xdb, 0xfb, 0xf3, 0xf3, 0xe3, 0xe3} ,    /*  78 */
  {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e} ,    /*  79 */
  {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe} ,    /*  80 */
  {0x00, 0x00, 0x3f, 0x6e, 0xdf, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c} ,    /*  81 */
  {0x00, 0x00, 0xc3, 0xc6, 0xcc, 0xd8, 0xf0, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe} ,    /*  82 */
  {0x00, 0x00, 0x7e, 0xe7, 0x03, 0x03, 0x07, 0x7e, 0xe0, 0xc0, 0xc0, 0xe7, 0x7e} ,    /*  83 */
  {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff} ,    /*  84 */
  {0x00, 0x00, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3} ,    /*  85 */
  {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3} ,    /*  86 */
  {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xff, 0xdb, 0xdb, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3} ,    /*  87 */
  {0x00, 0x00, 0xc3, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3} ,    /*  88 */
  {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3} ,    /*  89 */
  {0x00, 0x00, 0xff, 0xc0, 0xc0, 0x60, 0x30, 0x7e, 0x0c, 0x06, 0x03, 0x03, 0xff} ,    /*  90 */
  {0x00, 0x00, 0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c} ,    /*  91 */
  {0x00, 0x03, 0x03, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60} ,    /*  92 */
  {0x00, 0x00, 0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c} ,    /*  93 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18} ,    /*  94 */
  {0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} ,    /*  95 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x38, 0x30, 0x70} ,    /*  96 */
  {0x00, 0x00, 0x7f, 0xc3, 0xc3, 0x7f, 0x03, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00} ,    /*  97 */
  {0x00, 0x00, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0} ,    /*  98 */
  {0x00, 0x00, 0x7e, 0xc3, 0xc0, 0xc0, 0xc0, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00} ,    /*  99 */
  {0x00, 0x00, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03} ,    /* 100 */
  {0x00, 0x00, 0x7f, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00} ,    /* 101 */
  {0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x33, 0x1e} ,    /* 102 */
  {0x7e, 0xc3, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0x7e, 0x00, 0x00, 0x00, 0x00} ,    /* 103 */
  {0x00, 0x00, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0} ,    /* 104 */
  {0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x18, 0x00} ,    /* 105 */
  {0x38, 0x6c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x00} ,    /* 106 */
  {0x00, 0x00, 0xc6, 0xcc, 0xf8, 0xf0, 0xd8, 0xcc, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0} ,    /* 107 */
  {0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x78} ,    /* 108 */
  {0x00, 0x00, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xfe, 0x00, 0x00, 0x00, 0x00} ,    /* 109 */
  {0x00, 0x00, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xfc, 0x00, 0x00, 0x00, 0x00} ,    /* 110 */
  {0x00, 0x00, 0x7c, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x7c, 0x00, 0x00, 0x00, 0x00} ,    /* 111 */
  {0xc0, 0xc0, 0xc0, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0x00, 0x00, 0x00, 0x00} ,    /* 112 */
  {0x03, 0x03, 0x03, 0x7f, 0xc3, 0xc3, 0xc3, 0xc3, 0x7f, 0x00, 0x00, 0x00, 0x00} ,    /* 113 */
  {0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xe0, 0xfe, 0x00, 0x00, 0x00, 0x00} ,    /* 114 */
  {0x00, 0x00, 0xfe, 0x03, 0x03, 0x7e, 0xc0, 0xc0, 0x7f, 0x00, 0x00, 0x00, 0x00} ,    /* 115 */
  {0x00, 0x00, 0x1c, 0x36, 0x30, 0x30, 0x30, 0x30, 0xfc, 0x30, 0x30, 0x30, 0x00} ,    /* 116 */
  {0x00, 0x00, 0x7e, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00} ,    /* 117 */
  {0x00, 0x00, 0x18, 0x3c, 0x3c, 0x66, 0x66, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00} ,    /* 118 */
  {0x00, 0x00, 0xc3, 0xe7, 0xff, 0xdb, 0xc3, 0xc3, 0xc3, 0x00, 0x00, 0x00, 0x00} ,    /* 119 */
  {0x00, 0x00, 0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00} ,    /* 120 */
  {0xc0, 0x60, 0x60, 0x30, 0x18, 0x3c, 0x66, 0x66, 0xc3, 0x00, 0x00, 0x00, 0x00} ,    /* 121 */
  {0x00, 0x00, 0xff, 0x60, 0x30, 0x18, 0x0c, 0x06, 0xff, 0x00, 0x00, 0x00, 0x00} ,    /* 122 */
  {0x00, 0x00, 0x0f, 0x18, 0x18, 0x18, 0x38, 0xf0, 0x38, 0x18, 0x18, 0x18, 0x0f} ,    /* 123 */
  {0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18} ,    /* 124 */
  {0x00, 0x00, 0xf0, 0x18, 0x18, 0x18, 0x1c, 0x0f, 0x1c, 0x18, 0x18, 0x18, 0xf0} ,    /* 125 */
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x8f, 0xf1, 0x60, 0x00, 0x00, 0x00}      /* 126 */
} ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

Color  /* Some common colors */

Black   = {   0 ,   0 ,   0 } ,
White   = { 255 , 255 , 255 } ,
Red     = { 255 ,   0 ,   0 } ,
Lime    = {   0 , 255 ,   0 } ,
Blue    = {   0 ,   0 , 255 } ,
Yellow  = { 255 , 255 ,   0 } ,
Cyan    = {   0 , 255 , 255 } ,
Magenta = { 255 ,   0 , 255 } ,
Silver  = { 192 , 192 , 192 } ,
Gray    = { 128 , 128 , 128 } ,
Maroon  = { 128 ,   0 ,   0 } ,
Olive   = { 128 , 128 ,   0 } ,
Green   = {   0 , 128 ,   0 } ,
Purple  = { 128 ,   0 , 128 } ,
Teal    = {   0 , 128 , 128 } ,
Navy    = {   0 ,   0 , 128 } ;

/***************************************************************************************************************************************************/




/***************************************************************************************************************************************************/

char * getOperatingSystem ( void )
{
  return OS ;
}

/*=================================================================================================================================================*/

Color makeColor ( Byte red , Byte green , Byte blue )
{
  Color color ;

  color.red   = red   ;
  color.green = green ;
  color.blue  = blue  ;

  return color ;
}

/*=================================================================================================================================================*/

Point makePoint ( Coordinate row , Coordinate col )
{
  Point point ;

  point.row = row ;
  point.col = col ;

  return point ;
}

/*=================================================================================================================================================*/

Boolean isColorsEqual ( Color color1 , Color color2 )
{
  if   ( ( color1.red == color2.red ) && ( color1.green == color2.green ) && ( color1.blue == color2.blue ) )  { return TRUE  ; }
  else                                                                                                         { return FALSE ; }
}

/*=================================================================================================================================================*/

Boolean isPointInsideImage ( Image image , Point point )
{
  if ( point.row <  0            )  { return FALSE ; }
  if ( point.row >= image.height )  { return FALSE ; }
  if ( point.col <  0            )  { return FALSE ; }
  if ( point.col >= image.width  )  { return FALSE ; }

  return TRUE ;
}

/*=================================================================================================================================================*/

Pixel getPixel ( Image image , Point point )
{
  if   ( isPointInsideImage( image , point ) )  { return image.pixels[ point.row * image.width + point.col ] ; }
  else                                          { return Black                                               ; }
}

/*=================================================================================================================================================*/

Boolean setPixel ( Image image , Point point , Pixel pixel )
{
  if   ( isPointInsideImage( image , point ) )  { image.pixels[ point.row * image.width + point.col ] = pixel ;  return TRUE  ; }
  else                                          {                                                                return FALSE ; }
}

/*=================================================================================================================================================*/

Image * createImage ( unsigned short int width , unsigned short int height )
{
  Image * pImage ;

  if ( width  > IMAGE_MAX_WIDTH  )  { return NULL ; }
  if ( height > IMAGE_MAX_HEIGHT )  { return NULL ; }

  pImage         = (Image *) malloc( sizeof( Image )                  ) ;  if ( pImage         == NULL )  {                   return NULL ; }
  pImage->pixels = (Pixel *) malloc( sizeof( Pixel ) * width * height ) ;  if ( pImage->pixels == NULL )  { free( pImage ) ;  return NULL ; }
  pImage->width  = width  ;
  pImage->height = height ;

  return pImage ;
}

/*=================================================================================================================================================*/

void freeImage ( Image * pImage )
{
  free( pImage->pixels ) ;
  free( pImage         ) ;
}

/*=================================================================================================================================================*/

Boolean saveImage ( Image image , char * fileName )
{
  /* TODO */
  
	unsigned short int i,j;

	FILE * fp ;

	Pixel current ;

	fp = fopen( fileName , "w") ;

	if( fp == NULL) { printf("Unable to save Image\n" ); exit(-1) ; } 

	fprintf( fp , "%c%d\n", 'P', 3 );

	fprintf( fp , "%d %d\n%d\n",image.width , image.height , 255 );

	for(i=0 ; i < image.height ; i++){

		for(j=0 ; j<image.width ; j++){

			current = image.pixels[ i*image.width + j] ;	

			fprintf( fp , "%d %d %d    ", current.red , current.green , current.blue );	
		}

		fprintf( fp , "\n" );	
	}

	fclose( fp ) ;

	return TRUE;

}

/*=================================================================================================================================================*/

void displayImage ( char * fileName )
{
  char displayImageSystemCommand[256] = {0} ;

  if   ( strcmp( OS , "Windows" ) == 0 )  { sprintf( displayImageSystemCommand , "CMD /C START %s" , fileName ) ; }
  else /* Assumption: Linux */            { sprintf( displayImageSystemCommand , "xdg-open %s &"   , fileName ) ; }

  if ( system( displayImageSystemCommand ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */
}

/*=================================================================================================================================================*/

void clearImage ( Image image , Color color )
{
  unsigned int index                                       ;
  unsigned int numberOfPixels = image.width * image.height ;

  for ( index = 0 ; index < numberOfPixels ; index++ )  { image.pixels[ index ] = color ; }
}

/*=================================================================================================================================================*/

Boolean drawLine ( Image image , Point from , Point to , Color color )    /* Bresenham Line Drawing Algorithm (Integer Version) */
{
  int x0    = from.col ;
  int y0    = from.row ;
  int x1    = to.col   ;
  int y1    = to.row   ;
  int dx    = x1 - x0  ;
  int dy    = y1 - y0  ;
  int stepx = 1        ;
  int stepy = 1        ;

  if ( dx < 0 )  { dx = -dx ;  stepx = -1 ; }
  if ( dy < 0 )  { dy = -dy ;  stepy = -1 ; }

  dx <<= 1 ;
  dy <<= 1 ;

  setPixel( image , makePoint( y0 , x0 ) , color ) ;

  if ( dx > dy )
  {
    int fraction = dy - ( dx >> 1 ) ;

    while ( x0 != x1 )
    {
      if ( fraction >= 0 )  { y0 += stepy ;  fraction -= dx ; }
                              x0 += stepx ;  fraction += dy ;

      setPixel( image , makePoint( y0 , x0 ) , color ) ;
    }
  }
  else
  {
    int fraction = dx - ( dy >> 1 ) ;

    while ( y0 != y1 )
    {
      if ( fraction >= 0 )  { x0 += stepx ;  fraction -= dy ; }
                              y0 += stepy ;  fraction += dx ;

      setPixel( image , makePoint( y0 , x0 ) , color ) ;
    }
  }

  return TRUE ;
}

/*=================================================================================================================================================*/

Boolean drawArc
(
  Image        image             ,
  Point        center            ,
  double       startAngleDegrees ,
  double       endAngleDegrees   ,
  unsigned int radius            ,
  unsigned int numberOfSegments  ,
  Color        color
)
{
  /* TODO */

	Point point_from , point_to ;

	double degree , degree2 , temp_row ,temp_col,start_degree_value;
  
	if(startAngleDegrees > endAngleDegrees) {

		degree            = startAngleDegrees ;
		startAngleDegrees = endAngleDegrees   ;
		endAngleDegrees   =     degree        ;    	
	}

	start_degree_value = (startAngleDegrees )*22.0/7.0/180.0 ;

	degree = (22.0*(abs(endAngleDegrees - startAngleDegrees)/(double)numberOfSegments)) / (180.0 * 7.0) ;

	degree2 = degree ;

	temp_row = center.row - cos(start_degree_value) * radius ;

	temp_col = center.col + sin(start_degree_value) * radius ;

	point_from.row = temp_row + 1 ; 

	point_from.col = temp_col + 1 ;	

	while(numberOfSegments){

		temp_row = center.row - cos(start_degree_value + degree) * radius ;

		temp_col = center.col + sin(start_degree_value + degree) * radius ;

		point_to.row = temp_row + 1 ;

		point_to.col = temp_col + 1 ;

		drawLine( image , point_from , point_to , color ) ;

		point_from = point_to ;

		degree += degree2 ;

		numberOfSegments -- ;	
	}

	return TRUE ;
}

/*=================================================================================================================================================*/

Boolean drawRectangle ( Image image , Point topLeft , unsigned short int width , unsigned short int height , Color color )
{
  /* TODO */
  
  if(isPointInsideImage( image , topLeft) ) {	

  	drawLine(image , topLeft , makePoint(topLeft.row+height-1 , topLeft.col) , color);

  	drawLine(image , topLeft , makePoint(topLeft.row , topLeft.col+ width-1) , color);

	drawLine(image , makePoint(topLeft.row+height-1 , topLeft.col) , makePoint(topLeft.row+height-1 , topLeft.col+ width-1) , color);

	drawLine(image , makePoint(topLeft.row , topLeft.col+width-1) ,  makePoint(topLeft.row+height-1 , topLeft.col+ width-1) , color);

	return TRUE;  	  

  }

  return FALSE;
}

/*=================================================================================================================================================*/

Boolean drawRegularConvexPolygon ( Image image , Point center , unsigned short int radius , unsigned short int numberOfSides , Color color )
{
  /* TODO */
  	Point point_from , point_to ;

  	double degree , degree2 , temp_row ,temp_col;

  	degree = (22.0*(360.0/(double)numberOfSides)) / (180.0 * 7.0) ; 

  	degree2 = degree ;

  	point_from.row = center.row - radius ;
  	point_from.col = center.col          ;

  	while(numberOfSides){

  		temp_row = center.row - cos(degree) * radius ;

		temp_col = center.col + sin(degree) * radius ;

		point_to.row = temp_row + 1 ;

		point_to.col = temp_col + 1 ;
  		
  		drawLine( image , point_from , point_to , color) ;

  		point_from = point_to ;

  		degree += degree2 ;

  		numberOfSides -- ;

  	}
  	return TRUE ;
}	

/*=================================================================================================================================================*/

static void floodFill ( Image * pImage , Coordinate row , Coordinate col , Color * pColorToPaintOver , Color * pNewColor )
{
  if ( ! isColorsEqual( getPixel( *pImage , makePoint(row , col) ) , *pColorToPaintOver ) )  { return ; }

  setPixel( *pImage , makePoint(row,col)  , *pNewColor ) ;

  if ( col < pImage->width  - 1 )  { floodFill( pImage , row     , col + 1 , pColorToPaintOver , pNewColor ) ; }
  if ( row < pImage->height - 1 )  { floodFill( pImage , row + 1 , col     , pColorToPaintOver , pNewColor ) ; }
  if ( col > 0                  )  { floodFill( pImage , row     , col - 1 , pColorToPaintOver , pNewColor ) ; }
  if ( row > 0                  )  { floodFill( pImage , row - 1 , col     , pColorToPaintOver , pNewColor ) ; }
}

/*=================================================================================================================================================*/

Boolean fill ( Image image , Point start , Color color )
{
  Color colorToPaintOver ;

  if ( isPointInsideImage( image , start ) == FALSE )  { return FALSE ; }

  colorToPaintOver = getPixel( image , start ) ;

  if ( isColorsEqual( color , colorToPaintOver ) == TRUE )  { return TRUE ; }

  floodFill( &image , start.row , start.col , &colorToPaintOver , &color ) ;

  return TRUE ;
}

/*=================================================================================================================================================*/

Boolean drawCharacter ( Image image , Point topLeft , char c , Color color )
{
  /* TODO */
	unsigned char threshold = 128 , i = 0 , j = 0 ,raster_row = 0 , data = 0;

	Point point ;

	if( isPointInsideImage( image , topLeft) == FALSE ) return FALSE ;

	raster_row = c - 32 ;
  
	while( i < 13){

		data = characterRasters[raster_row][12 - i] ;

		threshold = 128 ;

		j = 0 ;

		while (threshold) {

			if(data >= threshold){

				point = makePoint(topLeft.row+i , topLeft.col+j) ;

				if( isPointInsideImage( image , point) ){

					setPixel(image , point , color ) ;

					data = data - threshold ;

					}

				else return FALSE ;

			}

			threshold /= 2 ;

			j++;

		 }	

		 i++;
	}

	i = 0;

	return TRUE ;
}

/*=================================================================================================================================================*/

Boolean drawString ( Image image , Point topLeft , char * string , Color color )
{
  while ( *string )
  {
    if ( drawCharacter( image , topLeft , *string , color ) == FALSE )  { return FALSE ; }

    topLeft.col += 8 * sizeof( unsigned char ) + 1 ;

    string++ ;
  }

  return TRUE ;
}

/***************************************************************************************************************************************************/




/***************************************************************************************************************************************************/

int main ( int argc , char * argv[] )
{
  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  Image * pImage        = NULL                 ;
  Image   image         = {   0 ,   0 , NULL } ;
  Color   color         = { 255 , 255 , 255  } ;
  char    fileName[256] = { 0                } ;
  FILE  * inFile                               ;
  char  * marker                               ;
  char    line    [512]                        ;
  char    string  [128]                        ;
  int     i1 , i2 , i3 , i4 , i5 , i6          ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  if ( argc < 2 )  { printf( "\nUsage: %s <Image Description File>\n\n" , argv[0] ) ;  return 0 ; }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  inFile = fopen( argv[1] , "r" ) ;

  if ( inFile == NULL )  { printf( "Unable to open image description file!\n" ) ;  exit( -1 ) ; }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  while ( fgets( line , 512 , inFile ) )
  {
    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    marker = line ;

    while ( ( marker < ( line + strlen(line) ) ) && isspace( *marker ) )  { marker++ ; }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    if ( strlen( marker ) == 0   )  { continue ; }
    if ( marker[0]        == '#' )  { continue ; }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    sscanf( marker , "%s" , string ) ;

    if      ( ! strcmp( string , "Image"     ) )  { marker += strlen( "Image" )                                                  ;
                                                    sscanf( marker , " %d %d %s" , &i1 , &i2 , fileName )                        ;
                                                    pImage = createImage( i1 , i2 )                                              ;
                                                    image  = *pImage                                                             ;
                                                  }
    else if ( ! strcmp( string , "SetColor"  ) )  { marker += strlen( "SetColor" )                                               ;
                                                    sscanf( marker , " %d %d %d" , &i1 , &i2 , &i3 )                             ;
                                                    color = makeColor( i1 , i2 , i3 )                                            ;
                                                  }
    else if ( ! strcmp( string , "Clear"     ) )  { marker += strlen( "Clear" )                                                  ;
                                                    clearImage( image , color )                                                  ;
                                                  }
    else if ( ! strcmp( string , "Point"     ) )  { marker += strlen( "Point" )                                                  ;
                                                    sscanf  ( marker , " %d %d" , &i1 , &i2        )                             ;
                                                    setPixel( image , makePoint( i1 , i2 ) , color )                             ;
                                                  }
    else if ( ! strcmp( string , "Line"      ) )  { marker += strlen( "Line" )                                                   ;
                                                    sscanf  ( marker , " %d %d %d %d" , &i1 , &i2 , &i3 , &i4             )      ;
                                                    drawLine( image , makePoint( i1 , i2 ) , makePoint( i3 , i4 ) , color )      ;
                                                  }
    else if ( ! strcmp( string , "Arc"       ) )  { marker += strlen( "Arc" )                                                    ;
                                                    sscanf ( marker , " %d %d %d %d %d %d" , &i1 , &i2 , &i3 , &i4 , &i5 , &i6 ) ;
                                                    drawArc( image , makePoint( i1 , i2 ) , i3 , i4 , i5 , i6 , color          ) ;
                                                  }
    else if ( ! strcmp( string , "Rectangle" ) )  { marker += strlen( "Rectangle" )                                              ;
                                                    sscanf       ( marker , " %d %d %d %d" , &i1 , &i2 , &i3 , &i4 )             ;
                                                    drawRectangle( image , makePoint( i1 , i2 ) , i3 , i4 , color  )             ;
                                                  }
    else if ( ! strcmp( string , "Polygon"   ) )  { marker += strlen( "Polygon" )                                                ;
                                                    sscanf                  ( marker , " %d %d %d %d" , &i1 , &i2 , &i3 , &i4 )  ;
                                                    drawRegularConvexPolygon( image , makePoint( i1 , i2 ) , i3 , i4 , color  )  ;
                                                  }
    else if ( ! strcmp( string , "Fill"      ) )  { marker += strlen( "Fill" )                                                   ;
                                                    sscanf( marker , " %d %d" , &i1 , &i2        )                               ;
                                                    fill  ( image , makePoint( i1 , i2 ) , color )                               ;
                                                  }
    else if ( ! strcmp( string , "Print"     ) )  { marker += strlen( "Print" )                                                  ;
                                                    sscanf    ( marker , " %d %d %[^\n]s" , &i1 , &i2 , string )                 ;
                                                    drawString( image , makePoint( i1 , i2 ) , string , color  )                 ;
                                                  }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/
  }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fclose      ( inFile           ) ;
  saveImage   ( image , fileName ) ;
  displayImage( fileName         ) ;

  return 0 ;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/
}

/***************************************************************************************************************************************************/
