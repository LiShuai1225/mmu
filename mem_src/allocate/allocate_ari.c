/*************************************************************************
	> File Name: allocate_ari.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2013年11月25日 星期一 20时32分49秒
 ************************************************************************/


#ifdef _ALLOCATE_H_



/**
* @brief first_fit 
*
* @param mem : memory
* @param size : process size
*
* @return : pid
*
* @describle : first fit ari
*/
int first_fit (link_table *mem, int size)
{
#ifdef _ALLOCATE_H_
    link_table  *p = mem, *temp;

    do {
        if (p->table.state == FALSE && p->table.size >= size) {
            /* when block is small isn't branch */
            if ((p->table.size - size) <= BLOCK_MIN) {
                p->table.state = TRUE;
                return p->no;
            }
            temp = (link_table *)malloc (sizeof (link_table)); 

            temp->table.base = p->table.base + size;
            temp->table.size = p->table.size - size;
            temp->table.state = FALSE;
            p->table.size = size;
            p->table.state = TRUE;

            temp->no = _ps_no++;
            temp->pre = p;
            temp->next = p->next;
            temp->next->pre = temp;
            p->next = temp;

            return p->no;
        }

        p = p->next;
    }while (p != mem);

    return (ERR_INFO = ERR_MEM_FULL);
#endif

    //......
    return -1;
}

/**
* @brief next_fit : next fit
*
* @param mem : memory
* @param size : process size
*
* @return : pid
*/
int next_fit (link_table *mem, int size)
{
#ifdef _ALLOCATE_H_
    link_table  *p = mem;
    link_table          *temp, *q = p;

    do {
        if (p->table.state == FALSE && p->table.size >= size) {
            if ((p->table.size - size) <= BLOCK_MIN) {
                p->table.state = TRUE;
                return p->no;
            }
            temp = (link_table *)malloc (sizeof (link_table)); 

            temp->table.base = p->table.base + size;
            temp->table.size = p->table.size - size;
            temp->table.state = FALSE;
            p->table.size = size;
            p->table.state = TRUE;

            temp->no = _ps_no++;
            temp->pre = p;
            temp->next = p->next;
            temp->next->pre = temp;
            p->next = temp;

            return p->no;
        }

        p = p->next;
    }while (p != q);

    return (ERR_INFO = ERR_MEM_FULL);
#endif

    //......
    return -1;
}

/**
* @brief best_fit : best fit
*
* @param mem : memory
* @param size : process size
*
* @return : pid
*/
int best_fit (link_table *mem, int size)
{
#ifdef _CHANGE_ALLOCATE_
    static link_table  *p = &mem_block;
    link_table          *temp, *q;
    int     b_size = MEMORY_MAX+1;

    do {
        if ((p->table.state == FALSE && p->table.size >= size) && p->table.size < b_size) {
            if ((p->table.size - size) <= BLOCK_MIN) {
                p->table.state = TRUE;
                return p->no;
            }
            b_size = p->table.size;
            q = p;
        }

        p = p->next;
    }while (p != mem);

    if (b_size <= MEMORY_MAX) {
        temp = (link_table *)malloc (sizeof (link_table)); 

        temp->table.base = q->table.base + size;
        temp->table.size = q->table.size - size;
        temp->table.state = FALSE;
        q->table.size = size;
        q->table.state = TRUE;

        temp->no = _ps_no++;
        temp->pre = q;
        temp->next = q->next;
        temp->next->pre = temp;
        q->next = temp;

        return p->no; 
    }
    return (ERR_INFO = ERR_MEM_FULL);

#endif

    // .... 
    return -1;
}

/**
* @brief worst_fit : worst fit
*
* @param mem : memory
* @param size : process size
*
* @return : pid
*/
int worst_fit (link_table *mem, int size)
{
#ifdef _CHANGE_ALLOCATE_
    static link_table  *p = &mem_block;
    link_table          *temp, *q;
    int     b_size = 0;

    do {
        if ((p->table.state == FALSE && p->table.size >= size) && p->table.size > b_size) {
            if ((p->table.size - size) <= BLOCK_MIN) {
                p->table.state = TRUE;
                return p->no;
            }
            b_size = p->table.size;
            q = p;
        }

        p = p->next;
    }while (p != mem);

    if (b_size > 0) {
        temp = (link_table *)malloc (sizeof (link_table)); 

        temp->table.base = q->table.base + size;
        temp->table.size = q->table.size - size;
        temp->table.state = FALSE;
        q->table.size = size;
        q->table.state = TRUE;

        temp->no = _ps_no++;
        temp->pre = q;
        temp->next = q->next;
        temp->next->pre = temp;
        q->next = temp;

        return p->no; 
    }
    return (ERR_INFO = ERR_MEM_FULL);

#endif

    // .... 
    return -1;
}

int quick_fit (link_table *mem, int size)
{
#ifdef _CHANGE_ALLOCATE_
    
#endif
}
#endif
