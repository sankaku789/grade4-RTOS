#include "ex.h"

uint8_t led = 0;

void task1 (intptr_t exinf)
{
	char	ch;
	SYSTIM	time;

	taskinfo(exinf);
	while (1) {
		serial_rea_dat(CONSOLE_PORTID, &ch, sizeof(ch));
		get_tim(&time);
		
		switch(ch) {
			case 'r':
			case 'R':
				led ^= 0x01;
				syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH:    %c, LED:0x%02x setting",
			       time / 1000, time % 1000, exinf, ch, led);
				break;
			case 'g':
			case 'G':
				led ^= 0x08;
				syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH:    %c, LED:0x%02x setting",
			       time / 1000, time % 1000, exinf, ch, led);
				break;
			case 'b':
			case 'B':
				led ^= 0x04;
				syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH:    %c, LED:0x%02x setting",
			       time / 1000, time % 1000, exinf, ch, led);
				break;
			case 'y':
			case 'Y':
				led ^= 0x02;
				syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH:    %c, LED:0x%02x setting",
			       time / 1000, time % 1000, exinf, ch, led);
				break;
			case 'a':
			case 'A':
				led = 0x0f;
				syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH:    %c, LED:0x%02x setting",
			       time / 1000, time % 1000, exinf, ch, led);
				break;
			case 'c':
			case 'C':
				led = 0x00;
				syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH:    %c, LED:0x%02x setting",
			       time / 1000, time % 1000, exinf, ch, led);
				break;
			case 'l':
			case 'L':
				led ^= 0x03;
				syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH:    %c, LED:0x%02x setting",
			       time / 1000, time % 1000, exinf, ch, led);
				break;
			case 'u':
			case 'U':
				led ^= 0x0c;
				syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH:    %c, LED:0x%02x setting",
			       time / 1000, time % 1000, exinf, ch, led);
				break;
		}
		
		if (ch < ' ')
			syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, CH: 0x%02x press",
			       time / 1000, time % 1000, exinf, ch);
		
		wup_tsk(TASK2);
	}
}

void task2 (intptr_t exinf)
{
	SYSTIM	time;

	taskinfo(exinf);
	 
	while(1) {
		slp_tsk();
		sil_wrb_mem((void *)PORTD_DR_ADDR, led & 0x0f);
		get_tim(&time);
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%2d, LED: 0x%02x toggle",
		    time / 1000, time % 1000, exinf, led & 0x0f);
	}
	
}

void main_task (intptr_t exinf)
{
	serial_ctl_por(CONSOLE_PORTID,
	               IOCTL_CRLF | IOCTL_FCSND | IOCTL_FCANY | IOCTL_FCRCV);

	sil_wrb_mem((void *)PORTD_DDR_ADDR, 0x0f);

	taskinfo(exinf);
	act_tsk(TASK1);
	act_tsk(TASK2);
	slp_tsk();
}
