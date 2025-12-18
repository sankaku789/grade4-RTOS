/*
 *  EX (Exercise for RTOS)
 * 
 *  Copyright (C) 2001-2019 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
 *  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
 *  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
 *  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
 *  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
 *  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
 *      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
 *      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
 *  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
 *      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
 *      �̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
 *      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̏����𖞂������ƁD
 *    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
 *        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
 *  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
 *      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
 *
 *  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
 *  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
 *  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
 *  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
 * 
 *  @(#) $Id: $
 */

/*
 *  RTOS ���K
 *
 *  ex40.c -- LED����v���O����
 */

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

	/* 
	 * LED�A�|�[�gD �̐ݒ�: �o��
	 */
	sil_wrb_mem((void *)PORTD_DDR_ADDR, 0x0f);

	taskinfo(exinf);
	act_tsk(TASK1);
	act_tsk(TASK2);
	slp_tsk();
}
