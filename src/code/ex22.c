#include "ex.h"

void task1 (intptr_t exinf)
{
	int	count = 0;
	SYSTIM	old, now;

	taskinfo(exinf);
	get_tim(&old);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
	       old / 1000, old % 1000, exinf, count);
	while (1) {
		while (1) {
			get_tim(&now);
			if (now > old + 3*1000) {
				old = now;
				break;
			}
		}
		count ++;
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
		       now / 1000, now % 1000, exinf, count);
	}
}

void task2 (intptr_t exinf)
{
	int	count = 0;
	SYSTIM	time;

	taskinfo(exinf);
	get_tim(&time);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
	       time / 1000, time % 1000, exinf, count);
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
	taskinfo(exinf);
	act_tsk(TASK2);
	act_tsk(TASK1);
	slp_tsk();
}
