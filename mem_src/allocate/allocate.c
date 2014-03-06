/*************************************************************************
	> File Name: allocate.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2013年11月20日 星期三 21时39分57秒
 ************************************************************************/

/**
* @brief child_ps 
*
* @describe : imitate process
*/
void child_ps (void)
{
#ifdef _ALLOCATE_H_
    printf ("child start!\n");
    srand ((int)time (NULL));
    sleep (rand () % 10);
    printf ("child end!\n");
#endif
    return;
}


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
* @brief init_block 
*
* @describe : init block
*/
void init_block (void)
{
    int     i;

#ifdef _BLOCK_EQUAL_
    block_table[BLOCK_BEGIN].size = BLOCK_SIZE; 
    for (i = BLOCK_BEGIN+1; i <= BLOCK_END; i++) { 

        block_table[i].base = block_table[i-1].base + block_table[i-1].size; 
        block_table[i].size = BLOCK_SIZE; 
    }
    return ;
#endif

#ifdef _BLOCK_NOT_EQUAL_
    block_table[BLOCK_MIN_BEGIN].size = BLOCK_MIN;
    for (i = BLOCK_MIN_BEGIN+1; i <= BLOCK_MIN_END; i++) {
        
        block_table[i].base = block_table[i-1].base + block_table[i-1].size; 
        block_table[i].size = BLOCK_MIN; 
    }
    for (i = BLOCK_MID_BEGIN; i <= BLOCK_MID_END; i++) {
        
        block_table[i].base = block_table[i-1].base + block_table[i-1].size; 
        block_table[i].size = BLOCK_MID; 
    }
    for (i = BLOCK_MAX_BEGIN; i <= BLOCK_MAX_END; i++) {
        
        block_table[i].base = block_table[i-1].base + block_table[i-1].size; 
        block_table[i].size = BLOCK_MAX; 
    }

    return;
#endif

    return;
}

/**
* @brief allocate_mem 
*
* @param size : block size
*
* @return : sucess or fail, and error code write to my_perror
*
* @describe : allocate memory
*/

int allocate_mem (int size)
{
#ifdef _ALLOCATE_H_
    _count++;

    ERR_INFO = 0;
    if (size > BLOCK_MAX) 
        return (ERR_INFO = ERR_PS_TOO_BIG);

    int     s = 0, e = -1, i;
    #ifdef _BLOCK_EQUAL_
    if (BLOCK_VALUE >= BLOCK_CNT)
        return (ERR_INFO = ERR_MEM_FULL);
    BLOCK_VALUE++;
    s = BLOCK_BEGIN;
    e = BLOCK_END;
    #endif

    #ifdef _BLOCK_NOT_EQUAL_
    if ((size <= BLOCK_MIN) && (BLOCK_MIN_VALUE < BLOCK_MIN_CNT)) {
        BLOCK_MIN_VALUE++;
        s = BLOCK_MIN_BEGIN;
        e = BLOCK_MIN_END;
    }else if ((size <= BLOCK_MID) && (BLOCK_MID_VALUE < BLOCK_MID_CNT)) {
        BLOCK_MID_VALUE++;
        s = BLOCK_MID_BEGIN;
        e = BLOCK_MID_END;
    }else if (BLOCK_MAX_VALUE < BLOCK_MAX_CNT) {
        BLOCK_MAX_VALUE++;
        s = BLOCK_MAX_BEGIN;
        e = BLOCK_MAX_END;
    }else 
        return (ERR_INFO = ERR_MEM_FULL);
    #endif

    for (i = s; i <= e; i++) {
        if (!block_table[i].state) {
            block_table[i].state = TRUE;
            _hit++;
            return i;
        }
    }

    return (ERR_INFO = ERR_HAVE_MEM_STRUCT);
#endif
    // ......
    return -1;
}


/**
* @brief destroy_mem 
*
* @param pid : process id
*
* @describe : destroy memory
*/
void destroy_mem (int pid) 
{
#ifdef _ALLOCATE_H_
    if ((pid < BLOCK_BEGIN) || (pid > BLOCK_END))
        return ;
    #ifdef _BLOCK_EQUAL_
    BLOCK_VALUE--;
    #endif

    #ifdef _BLOCK_NOT_EQUAL_
    if (pid < BLOCK_MIN_CNT)
        BLOCK_MIN_VALUE--;
    else if (pid < BLOCK_MID_CNT)
        BLOCK_MID_VALUE--;
    else if (pid < BLOCK_MAX_CNT)
        BLOCK_MAX_VALUE--;
    #else
    return;
    #endif

    block_table[pid].state = FALSE;
    printf ("destroy_mem success!\n");
#endif

    return ;
}

/**
* @brief print_mem 
*
* @param mode : print memory or not
*
* @describe : print memory
*/
void print_mem (int mode)
{
    //  ┏━━━┳━━━━━━━┳━━━━━━━━━━━┳━━━━━━━┓
    //  ┣━━━╋━━━┳━━━╋━━━━━━━━━━━╋━━━━━━━┫
    //  ┗━━━┻━━━┻━━━┻━━━┻━━━━━━━┻━━━━━━━┛
    //  ┃ 7  ┃ G  ┃

#ifdef _ALLOCATE_H_
    int     i, s = 0, e = -1;
    int     unuse_mem_sum, unuse_block_cnt;
    table_struct    temp;

    #ifdef _BLOCK_EQUAL_
    s = BLOCK_BEGIN;
    e = BLOCK_END;
    #endif
    #ifdef _BLOCK_NOT_EQUAL_
    s = BLOCK_BEGIN;
    e = BLOCK_END;
    #endif
    printf ("\t ┏━━━━━━━━┳━━━━━━━━┳━━━━━━┓\n");
    unuse_mem_sum = unuse_block_cnt = 0;

    if (mode == PRINT_MEM) {
        for (i = s; i <= e; i++) {
            temp = block_table[i];
            if (!temp.state) {
                unuse_mem_sum += temp.size;
                unuse_block_cnt++;
            }
            printf ("\t ┃%-8u┃%-8u┃%-6d┃\n", temp.base, temp.size, temp.state);
            printf ("\t ┣━━━━━━━━╋━━━━━━━━╋━━━━━━┫\n");
        }
    } else {
        for (i = s; i <= e; i++) {
            temp = block_table[i];
            if (!temp.state) {
                unuse_mem_sum += temp.size;
                unuse_block_cnt++;
            }
        }
    }

    printf ("\t ┃%-8u┃%-8u┃%-6d┃ %d/%d = %.2f\n", e-s+1, unuse_mem_sum, unuse_block_cnt, _hit, _count, _hit/(float)_count);
    printf ("\t ┗━━━━━━━━┻━━━━━━━━┻━━━━━━┛\n");
#endif
    return ;
}
