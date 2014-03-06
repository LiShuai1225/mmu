/*************************************************************************
	> File Name: process.c
	> Author: zhanglp
	> Mail: 820221185@qq.com 
	> Created Time: 2013年11月21日 星期四 17时59分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>


#define PATH_NAME	"."
#define PROJ_ID		32

#define MSG_TO_OS		3
#define MSG_FROM_OS		4
#define PS_APPLY_MEM	0x1
#define PS_END			0x2


struct mymsgbuf {
	long	msgtype;
	int		pid;
	int		msg;
}msgbuffer;


/**
 * * @brief child_ps 
 * *
 * * @describe : imitate process
 * */
void child_ps (void)
{
	printf ("child start!\n");
	srand ((int)time (NULL));
	sleep (rand () % 100);
	printf ("child end!\n");

	return;
}


/**
* @brief recv_msg 
*
* @param qid
* @param msgbuffer
* @param len
* @param f
*
* @describe : recv message from message's
*/
void recv_msg (int qid, struct mymsgbuf *msgbuffer, size_t len, int f)
{
    if (msgrcv (qid, msgbuffer, len, msgbuffer->msgtype, f) < 0) {
        perror ("msgsend o");
        exit (EXIT_FAILURE);
    }
}

/**
* @brief send_msg 
*
* @param qid
* @param msgbuffer
* @param len
* @param f
*
* @describe : send message to message queue
*/
void send_msg (int qid, struct mymsgbuf *msgbuffer, size_t len, int f)
{
    if (msgsnd (qid, msgbuffer, len, f) < 0) {
        perror ("msgsend o");
        exit (EXIT_FAILURE);
    }
}


int main (void) 
{

	int		qid;
	int		msglen;
	key_t	msgkey;

	if ((msgkey = ftok (PATH_NAME, PROJ_ID)) < 0) {
		perror ("ftok");
		exit (EXIT_FAILURE);
	}
	if ((qid = msgget (msgkey, IPC_CREAT | 0660)) < 0) {
		perror ("msgget");
		exit (EXIT_FAILURE);
	}


	int		pid;
	while (1) {

		msgbuffer.msgtype = MSG_TO_OS;
		msgbuffer.msg = PS_APPLY_MEM;
		send_msg (qid, &msgbuffer, sizeof (struct mymsgbuf)-4, 0);

		msgbuffer.msgtype = MSG_FROM_OS;
		recv_msg (qid, &msgbuffer, sizeof (struct mymsgbuf)-4, 0);
		if ((pid = msgbuffer.pid) >= 0) {
		
			if (fork () == 0) {
			    child_ps ();

				struct mymsgbuf	ps_buf;
				ps_buf.msgtype = MSG_TO_OS;
				ps_buf.msg = PS_END;
				ps_buf.pid = pid;
				send_msg (qid, &ps_buf, sizeof (struct mymsgbuf)-4, 0);
				exit (0);
			}
		}

        printf ("create a process ? (y/n) ");
        while (getchar () != 'y') {
            char    buf[256];
        //    read (STDIN_FILENO, buf, 256);
        }
        //    sleep (1);
	}

	return 0;
}
