#include "ex.h"

uint8_t led = 0x00;
RELTIM quantum;   

void task1 (intptr_t exinf)
{
    uint8_t led_state = 0x01;
    SYSTIM time;

    taskinfo(exinf);
    get_tim(&time);
    syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%ld, START",
           time / 1000, time % 1000, exinf);

    while (1) {
		
        get_tim(&time);

        led ^= led_state;

        sil_wrb_mem((void *)PORTD_DR_ADDR, led & 0x0f);
    }
}

void task2 (intptr_t exinf)
{
    uint8_t led_state = 0x02;
    SYSTIM time;

    taskinfo(exinf);
    get_tim(&time);
    syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%ld, START",
           time / 1000, time % 1000, exinf);

    while (1) {
		
        get_tim(&time);

        led ^= led_state;

        sil_wrb_mem((void *)PORTD_DR_ADDR, led & 0x0f);
    }
}

void task3 (intptr_t exinf)
{
    uint8_t led_state = 0x04;
    SYSTIM time;

    taskinfo(exinf);
    get_tim(&time);
    syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%ld, START",
           time / 1000, time % 1000, exinf);

    while (1) {
		
        get_tim(&time);

        led ^= led_state;

        sil_wrb_mem((void *)PORTD_DR_ADDR, led & 0x0f);
    }
}

void task4 (intptr_t exinf)
{
	int tsk_number = 1;
	SYSTIM time;
	taskinfo(exinf);
    get_tim(&time);
    syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%ld, START",
           time / 1000, time % 1000, exinf);

    while (1) {

		get_tim(&time);
		syslog(LOG_NOTICE, "[  :%2d.%03d] TASKID:%d -> dispatch",
           time / 1000, time % 1000, tsk_number, led & 0x0f);

        dly_tsk(quantum);

		tsk_number ++;

		if (tsk_number > 3) {
			tsk_number = 1;
		}
        rot_rdq(6);
    }
}

void main_task (intptr_t exinf)
{
    sil_wrb_mem((void *)PORTD_DDR_ADDR, 0x0f);

    quantum = 1000; 

    taskinfo(exinf);
    act_tsk(TASK1);
    act_tsk(TASK2);
    act_tsk(TASK3);
    act_tsk(TASK4);

    slp_tsk();
}
 