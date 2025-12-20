#include "ex.h" // (1)

void task1 (intptr_t exinf)
{
	// (2) 6・7行目
	int	count = 0;
	SYSTIM	old, now;


	taskinfo(exinf); // (3)

	// (4) 13・14行目
	get_tim(&old);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
	       old / 1000, old % 1000, exinf, count);
	
	// (5) 18～29行目
	while (1) {
		// (a) 20～26行目
		while (1) {
			get_tim(&now);
			if (now > old + 3*1000) {
				old = now;
				break;
			}
		}
		count ++; // (b)
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
		       now / 1000, now % 1000, exinf, count); // (c)
	}
}

void task2 (intptr_t exinf)
{
	// (6) 36・37行目
	int	count = 0;
	SYSTIM	time;

	taskinfo(exinf);// (7)

	// (8) 42・43行目
	get_tim(&time);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
	       time / 1000, time % 1000, exinf, count);

	// (9) 47～53行目
	while (1) {
		tslp_tsk(2*1000);
		count ++;
		get_tim(&time);
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
		       time / 1000, time % 1000, exinf, count);
	}
}

void main_task (intptr_t exinf)
{
	taskinfo(exinf);// (10)

	// (11) 61・62行目
	act_tsk(TASK1);
	act_tsk(TASK2);

	slp_tsk();// (12)
}
