/*************************************************************************
	> File Name: allocate_euqal.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2013年11月20日 星期三 21时46分06秒
 ************************************************************************/


//#ifndef _ALLOCATE_EQUAL_
//#define _ALLOCATE_EQUAL_

#ifndef _ALLOCATE_NOT_EQUAL_
#define _ALLOCATE_NOT_EQUAL_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#ifdef _ALLOCATE_EQUAL_
	#define _BLOCK_EQUAL_
	#include "allocate/allocate.h"
	#undef _BLOCK_EQUAL_
	#undef _ALLOCATE_EQUAL_
#endif

#ifdef _ALLOCATE_NOT_EQUAL_
	#define _BLOCK_NOT_EQUAL_
	#include "allocate/allocate.h"
	#undef _BLOCK_NOT_EQUAL_
	#undef _ALLOCATE_NOT_EQUAL_
#endif



struct mymsgbuf {
    long    msgtype;
    int     pid;
    int     msg;
};

#define PATH_NAME	"."
#define PROJ_ID		32

#define MSG_FROM_PS		3
#define MSG_TO_PS		4

#define MSG_APPLY_MEM	0x1
#define MSG_PS_END		0x2

#endif
