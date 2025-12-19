#include "ex.h"

void timer(long t) {
	t *= 4100000;
	while(t--);
}

void task1 (intptr_t exinf)
{
	int	count = 0;
	char ch, ch_old;
	FLGPTN	flag = 0x0f;
	SYSTIM	time;

	taskinfo(exinf);
	get_tim(&time);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
	       time / 1000, time % 1000, exinf, count);
	ch_old = sil_reb_mem((void *)PORTE_PORT_ADDR);
	while (1) {
		tslp_tsk(1000);
		count ++;
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
		
		flag = ~(ch) ;
		flag &= 0x0f;

		if (flag == 0x00) {
			flag |= 0x10;
		}

		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH: 0x%02x, FLG: 0x%02x",
			    time / 1000, time % 1000, exinf, ch, flag);

		set_flg(FLG1, flag);
		
	}
}

void task2 (intptr_t exinf)
{
	int	count = 0;
	FLGPTN	flag = 0x00;
	SYSTIM	time;

	taskinfo(exinf);
	get_tim(&time);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
	       time / 1000, time % 1000, exinf, count);
	while (1) {
		wai_flg(FLG1, 0x1f, TWF_ORW, &flag);
		clr_flg(FLG1, 0x00);

		count ++;
		get_tim(&time);
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d, flag: 0x%02x",
		       time / 1000, time % 1000, exinf, count, flag & 0x0f);
		sil_wrb_mem((void *)PORTD_DR_ADDR, flag & 0x0f);
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
