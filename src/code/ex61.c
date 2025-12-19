#include "ex.h"

uint8_t led = 0;

void timer(long t) {
	t *= 4100000;
	while(t--);
}

void task1 (intptr_t exinf)
{
	uint8_t	ch, ch_old;
	SYSTIM	time;

	taskinfo(exinf);
	ch_old = sil_reb_mem((void *)PORTE_PORT_ADDR);
	while (1) {
		get_tim(&time);

		while (1) {
			ch = sil_reb_mem((void *)PORTE_PORT_ADDR);
			if (ch != ch_old) {
				ch_old = ch;
				break;
			}
			timer(1);
		}
		
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d,  SW: 0x%02x pressed",
	       time / 1000, time % 1000, exinf, ch);
		
		led = ~(ch);
		
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, LED: 0x%02x setting",
			     time / 1000, time % 1000, exinf, led);
		
		sig_sem(SEM1);
	}
}

void task2 (intptr_t exinf)
{
	SYSTIM	time;

	taskinfo(exinf);
	 
	while(1) {
		wai_sem(SEM1);
		sil_wrb_mem((void *)PORTD_DR_ADDR, led & 0x0f);
		get_tim(&time);
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, LED: 0x%02x ",
		    time / 1000, time % 1000, exinf, led & 0x0f);
	}
	
}

void main_task (intptr_t exinf)
{

	
	sil_wrb_mem((void *)PORTD_DDR_ADDR, 0x0f);
	sil_wrb_mem((void *)PORTE_DDR_ADDR, 0x00);
	sil_wrb_mem((void *)PORTE_PCR_ADDR, 0x0f);
	sil_wrb_mem((void *)PORTE_ICR_ADDR, 0x0f);

	taskinfo(exinf);
	act_tsk(TASK1);
	act_tsk(TASK2);
	slp_tsk();
}
