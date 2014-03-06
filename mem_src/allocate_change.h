/*************************************************************************
	> File Name: allocate_change.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2013年11月20日 星期三 21时46分06秒
 ************************************************************************/

#ifndef _ALLOCATE_CHANGE_
#define _ALLOCATE_CHANGE_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#ifdef _ALLOCATE_CHANGE_
	#define _CHANGE_ALLOCATE_
	#include "allocate/allocate.h"
	#undef _CHANGE_ALLOCATE_
	#undef _ALLOCATE_CHANGE_
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
