#include "ex.h" // (1)

void task1 (intptr_t exinf)
{
	// (2) 6・7行目
	int	count = 0;
	SYSTIM	time;

	taskinfo(exinf);// (3)
	
	// (4) 12・13行目
	get_tim(&time);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
	       time / 1000, time % 1000, exinf, count);
	
	// (5) 17～23行目
	while (1) {
		tslp_tsk(3*1000);
		count ++;
		get_tim(&time);
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
		       time / 1000, time % 1000, exinf, count);
	}
}

void task2 (intptr_t exinf)
{
	// (6) 29・30行目
	int	count = 0;
	SYSTIM	time;

	taskinfo(exinf);// (7)

	// (8) 35・36行目
	get_tim(&time);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
	       time / 1000, time % 1000, exinf, count);
	
    // (9) 40～46行目
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

	// (11) 54・55行目
	act_tsk(TASK1);
	act_tsk(TASK2);

	slp_tsk();// (12)
}
