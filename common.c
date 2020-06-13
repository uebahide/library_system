#include "common.h"

/*
 * ����		: ��ʂ̃N���A
 * ����		: �R�}���h�C���^�v���^�̉�ʃN���A���߂����s
* �ďo�`��	: void clear_screen(void)
 * ����		: ����
 * �߂�l	: ����
 */
void clear_screen()
{
	system("cls");
}

/*
 * ����		: ���̓f�[�^�`�F�b�N����
 * ����		: ���̓f�[�^�̃j���[�����b�N�`�F�b�N�����s��
 * �ďo�`��	: int numelicCheck(char inpdata[],int inpLength)
 * ����		: inpdata    �`�F�b�N�Ώۂ̓��̓f�[�^
 *			  inpLength  ���͋�����
 * �߂�l	: ret	9:�I�� -1:���̓G���[ �ȊO:int�^�ɕϊ��������͒l
 */
int numelicCheck(char inpdata[],int inpLength)/* ������Ƃ��ă`�F�b�N���邽�߂�inpdata��char�^*/
{
	int i = 0;
	int ret = 1;
	
	/* 9:�I�� */
	
	if (strlen(inpdata) == 1 && inpdata[0] == '9') /* 91�Ƃ�999�Ƃ��͂��߂ŁA9�ł���΃I�b�P�C*/{
		return 9;
	}
	
	
	/* ���͌����`�F�b�N */
	if (strlen(inpdata) != inpLength || inpdata[0] == '\0')
	/* �w�肵�������ȊO�̌����������͂����Ȃ��ꍇ�̓G���[�\��*/{
		printf("(Error) %d ���̔��p�����œ��͂��Ă��������B\n",inpLength);
		ret = -1;
	} else {
		/* �����`�F�b�N */
		while (inpdata[i] != '\0' && ret != 99) {/* ret != 99 �Ăǂ��������ƁH�H*/
			if (isdigit(inpdata[i]) == 0) {
				printf("(Error)���l����͂��Ă��������B\n");
				ret = -1;
				break;
			}
			i++;
		}
	}
	
	/* ���l�����͂��ꂽ�ꍇ��int�^�ɕϊ� */
	if (ret >= 0) {
		ret = atoi(inpdata);
	}
	return ret;/* �ُ�Ȓl�Ȃ�-1�A����Ȓl�Ȃ���͒l��int�^�ɂ��ĕԂ�*/
}

/*
 * ����		: ���C���\������
 * ����		: ���C���\�����s��
 * �ďo�`��	: void printLine()
 * ����		: none
 * �߂�l	: none
 */
void printLine()
{
	printf("---------------------------------------------------------------------------------------------\n");
}

/*
 * ����		: �}���f�[�^�w�b�_�[�\��
 * ����		: �}���f�[�^�w�b�_�[�\�����s��
 * �ďo�`��	: void printBookHead()
 * ����		: non
 * �߂�l	: non
 */
void printBookHead()
{
	printf("\n�敪|   �R�[�h   |          �^�C�g��           |             ����             |    ���    |\n");
}


/*
 * ����		: �}���f�[�^�\������
 * ����		: �}���f�[�^������̕\�����s��
 * �ďo�`��	: void printBookData(BOOK book)
 * ����		: book �}���f�[�^
 * �߂�l	: none
 */
void printBookData(BOOK book)
{
	printf("  %02d|", book.bookKbn);
	printf("       %05d|", book.bookCode);
	printf("%29s|", book.title);
	printf("%30s|", book.author);
	
	if (book.isRent == 0) {
		printf("    �ݏo�\|\n");
	} else {
		printf("    �ݏo�s��|\n");
	}
}

