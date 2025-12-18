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
 *  ex61.c -- LED����v���O����
 */

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

	/* 
	 * LED�A�|�[�gD �̐ݒ�: �o��
	 */
	sil_wrb_mem((void *)PORTD_DDR_ADDR, 0x0f);
	sil_wrb_mem((void *)PORTE_DDR_ADDR, 0x00);
	sil_wrb_mem((void *)PORTE_PCR_ADDR, 0x0f);
	sil_wrb_mem((void *)PORTE_ICR_ADDR, 0x0f);

	taskinfo(exinf);
	act_tsk(TASK1);
	act_tsk(TASK2);
	slp_tsk();
}
