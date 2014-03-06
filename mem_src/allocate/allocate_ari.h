/*************************************************************************
	> File Name: allocate_ari.h
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2013年11月28日 星期四 16时11分14秒
 ************************************************************************/

#ifndef _ALLOCATE_AIR_H_ 
#define _ALLOCATE_AIR_H_ 

int first_fit (link_table *mem, int size); 
int next_fit (link_table *mem, int size); 
int best_fit (link_table *mem, int size); 
int worst_fit (link_table *mem, int size); 
int quick_fit (link_table *mem, int size); 

#endif 
