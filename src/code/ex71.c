#include "ex.h"

void timer(long t) {
	t *= 100000;
	while(t--);
}

void task1 (intptr_t exinf)
{
	SYSTIM	time;
	uint8_t old, now;

	taskinfo(exinf);
	old = sil_reb_mem((void *)PORTE_PORT_ADDR);
	get_tim(&time);
	while (1) {
		while (1) {
			now = sil_reb_mem((void *)PORTE_PORT_ADDR);
			if (now != old) {
				old = now;
				break;
			}
		}
		timer(1);
		get_tim(&time);
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, TSKID:%2d: Wake up",
		       time / 1000, time % 1000, exinf, TASK2);
		snd_dtq(DTQ1, (intptr_t)now);
	}
}

void task2 (intptr_t exinf)
{
	int	count = 0;
	uint8_t task1_sw_addr;
	SYSTIM	time;

	taskinfo(exinf);
	get_tim(&time);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d,  SW: 0x%02x",
	       time / 1000, time % 1000, exinf, count, task1_sw_addr);
	while (rcv_dtq(DTQ1, (intptr_t*)&task1_sw_addr) == E_OK) {
		count ++;
		get_tim(&time);
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d,  SW: 0x%02x",
	       time / 1000, time % 1000, exinf, count, task1_sw_addr);
	}
}

void main_task (intptr_t exinf)
{
	sil_wrb_mem((void *)PORTE_DDR_ADDR, 0x00);
	sil_wrb_mem((void *)PORTE_PCR_ADDR, 0x0f);
	sil_wrb_mem((void *)PORTE_ICR_ADDR, 0x0f);
	
	taskinfo(exinf);
	act_tsk(TASK1);
	act_tsk(TASK2);
	slp_tsk();
}

