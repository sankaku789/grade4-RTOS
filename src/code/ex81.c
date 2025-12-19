#include "ex.h"

void task1 (intptr_t exinf)
{
	int	count = 0;
	char ch;
	FLGPTN	flag = 0x00;
	SYSTIM	time;

	taskinfo(exinf);
	get_tim(&time);
	syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, Count:%2d",
	       time / 1000, time % 1000, exinf, count);
	while (1) {
		tslp_tsk(1000);
		count ++;
		serial_rea_dat(CONSOLE_PORTID, &ch, sizeof(ch));
		get_tim(&time);
		
		switch(ch) {
			case 'r':
			case 'R':
				flag ^= 0x01;
				break;
			case 'g':
			case 'G':
				flag ^= 0x08;
				break;
			case 'b':
			case 'B':
				flag ^= 0x04;
				break;
			case 'y':
			case 'Y':
				flag ^= 0x02;
				break;
			case 'a':
			case 'A':
				flag = 0x0f;
				break;
			case 'c':
			case 'C':
				flag = 0x00;
				break;
			case 'l':
			case 'L':
				flag ^= 0x03;
				break;
			case 'u':
			case 'U':
				flag ^= 0x0c;
				break;
		}
			
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

	taskinfo(exinf);
	act_tsk(TASK1);
	act_tsk(TASK2);
	slp_tsk();
}
