/*************************************************************************
	> File Name: change_allocate.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2013年11月25日 星期一 19时23分57秒
 ************************************************************************/

#include "allocate_ari.c"
#include <string.h>

void print_change_mem (int);

/**
* @brief ps_size 
*
* @return : block size
*
* @describe : rand get process size
*/
int ps_size (void)
{
#ifdef _ALLOCATE_H_
    int     s = PS_MIN-1; 
    srand ((int)time (NULL)); 
    while (s < PS_MIN) 
        s = rand () % PS_MAX; 
    return s; 
#endif
    // ......
    return -1;
}

/**
 * @brief init_change_block 
 *
 * @describe : init change block
 */
void init_change_block (void)
{
#ifdef _CHANGE_ALLOCATE_
	block_link->table.base = 0;
	block_link->table.size = MEMORY_MAX;
	block_link->table.state = FALSE;
	block_link->table.pid = 0;

	block_link->no = 0;
	block_link->pre = block_link->next = block_link;
#endif
	return ;
}

/**
 * @brief allocate_change_mem : allocate change memory
 *
 * @param size : process size
 *
 * @return : pid
 */
#ifdef _CHANGE_ALLOCATE_ 
int allocate_change_mem (int size, int air)
{
#ifdef _CHANGE_ALLOCATE_ 
    int     pid = alloc_air[air](block_link, size); 

	if (pid >= 0) 
		_hit++;
	_count++;

	return pid;
#endif
}
#endif

/**
 * @brief destroy_change_mem : free a block
 *
 * @param no : no of block
 */
void destroy_change_mem (int no) 
{
#ifdef _CHANGE_ALLOCATE_ 
	printf ("destroy_change_mem : %d\n", no); 
	link_table	*p = block_link, *q; 

	do { 
		if (p->no == no) {
			p->table.state = FALSE;
			q = p->next;
			if (q->table.state == FALSE) {
				p->table.size += q->table.size;
				p->next = q->next;
				q->next->pre = p;
				free (q);
			}
			q = p->pre;
			if (p != block_link && q->table.state == FALSE) {
				q->table.size += p->table.size;
				q->next = p->next;
				p->next->pre = q;
				free (p);
			}
			return ;
		}

		p = p->next;
	}while (p != block_link);

#endif
	return;
}

void destroy_mem (void)
{
#ifdef _CHANGE_ALLOCATE_
	link_table	*p = block_link->next, *q;

	while (p != block_link) {
		q = p->next;
		free (p);
		p = q;
	}
#endif
}

/**
 * @brief print_change_mem 
 *
 * @param mode
 *
 * @describe : print memory
 */
void print_change_mem (int mode) 
{
#ifdef _CHANGE_ALLOCATE_
	link_table	*p = block_link;

	int		cnt = 0, unuse_mem_sum = 0, unuse_block_cnt = 0;
	
    printf ("\t ┏━━━━━━━━┳━━━━━━━━┳━━━━━━┓\n");

	if (mode == PRINT_MEM) {
		do {
			cnt++;
			if (p->table.state == FALSE) {
				unuse_mem_sum += p->table.size;
				unuse_block_cnt++;
			}
			printf ("\t ┃%-8u┃%-8u┃%-6d┃\n", p->table.base, p->table.size, p->table.state);
	        printf ("\t ┣━━━━━━━━╋━━━━━━━━╋━━━━━━┫\n");

			p = p->next;
		}while (p != block_link);
	}else {
		do {
			cnt++;
			if (p->table.state == FALSE) {
				unuse_mem_sum += p->table.size;
				unuse_block_cnt++;
			}
			p = p->next;
		}while (p != block_link);
	}

    printf ("\t ┃%-8u┃%-8u┃%-6d┃ %d/%d = %.2f\n", cnt, unuse_mem_sum, unuse_block_cnt, _hit, _count, _hit/(float)_count);
    printf ("\t ┗━━━━━━━━┻━━━━━━━━┻━━━━━━┛\n");
#endif
}


/**
* @brief clear_chip : clear chip of memory
*/
void clear_chip (void)
{
#ifdef _CHANGE_ALLOCATE_
	link_table	*p, *q_0, *q_1 = NULL, *q;
	p = q_0 = block_link; 
	int		flag = FALSE;

	do { 
		if (p->table.state == FALSE) { 
            if (flag == FALSE) { 
                q_0 = p; 
            }

            if (p != q_0) { 
				int		i = q_1->table.base;
				int		j = q_0->table.base;
				int		len = p->table.base - q_1->table.base;

				memmove ((char *)&(_memory[j]), (char *)&(_memory[i]), len);
				for (q = q_1; q != p; q = q->next) 
					q->table.base -= q_0->table.size; 
				q->table.base -= q_0->table.size; 
                q->table.size += q_0->table.size;

				q = q_0->pre;
				q->next = q_1;
				q_1->next = q;
				free (q_0);

                q_0 = p; 
			}
			flag = FALSE; 
		}else {
			if (flag == FALSE) 
				q_1 = p;
			flag = TRUE;
		}

		p = p->next;
	}while (p != block_link);
#endif
}
