/*************************************************************************
	> File Name: allocate.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2013年11月19日 星期二 19时41分00秒
 ************************************************************************/


#ifndef _ALLOCATE_H_
#define _ALLOCATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TRUE    1
#define FALSE   0

#define MEMORY_MAX      0x1000  // 4k
#define PS_MIN  5
#define PS_MAX  40

typedef struct _TABLE   table_struct; 

/** allocate block that size is equal */
#ifdef _BLOCK_EQUAL_
    #define BLOCK_MAX       0x20    // 32B
    #define BLOCK_SIZE      0x20    // 32B

    #define BLOCK_CNT       0x80    // 128
    #define BLOCK_BEGIN     0x0
    #define BLOCK_END       0x7F

    int     BLOCK_VALUE;
	table_struct    block_table[BLOCK_CNT];
#endif

/** allocate block that size isn't equal */
#ifdef _BLOCK_NOT_EQUAL_
	#define BLOCK_MIN       0x8     // 8B
	#define BLOCK_MID       0x20    // 32B
	#define BLOCK_MAX       0x80    // 128B

	#define BLOCK_MIN_CNT   0x100   // 2^8
	#define BLOCK_MID_CNT   0x20    // 2^5
	#define BLOCK_MAX_CNT   0x8     // 2^3
	#define BLOCK_CNT       0x128   // 2^8 + 2^5 + 2^3

	#define BLOCK_MIN_BEGIN     0x0
	#define BLOCK_MIN_END       0xFF
	#define BLOCK_MID_BEGIN     0x100
    #define BLOCK_MID_END       0x11F
	#define BLOCK_MAX_BEGIN     0x120
    #define BLOCK_MAX_END       0x127
	#define BLOCK_BEGIN     0x0
    #define BLOCK_END       0x127

	int     BLOCK_MIN_VALUE;
    int     BLOCK_MID_VALUE;
	int     BLOCK_MAX_VALUE;
	table_struct    block_table[BLOCK_CNT];
#endif 

#define PRINT_MEM		0
#define PRINT_NOT_MEM	1

#define ADDR_TYPE   unsigned
#define BLOCK_T     unsigned
#define BOOL        unsigned char
struct _TABLE {
    ADDR_TYPE   base;
    BLOCK_T     size;
    BOOL        state;
    unsigned    pid;
};



/** calculate probability of bit */
unsigned int    _hit;
unsigned int    _count;


#define ERR_PS_TOO_BIG  -1
    #define ERR_MEM_FULL			-2
	#define ERR_HAVE_MEM_STRUCT		-3

int     ERR_INFO;
/**
* @brief my_perror 
*
* @param str : user error describe
*
* @describe : print error
*/
void my_perror (const char *str)
{
    switch (ERR_INFO) {
        case 0 : 
            printf ("%s : no error!\n", str); break;

        case ERR_PS_TOO_BIG : 
            printf ("%s : process too big!\n", str); break;

        case ERR_MEM_FULL :
            printf ("%s : process too big!\n", str); break;
		
		case ERR_HAVE_MEM_STRUCT :
            printf ("%s : have not memory struct!\n", str); break;
			
        default :
            printf ("%s : ERROR!\n", str); break;
    }
}

#include "allocate.c"
#endif 
