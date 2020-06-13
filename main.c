#include "common.h"

int main(void)
{
	int chk_num; /* switch���̏������ɗ��p�AnumelicCheck()�̕Ԃ�l���i�[ */
	char inp_code[256];	// ���̓f�[�^���i�[����
	
	BOOK_MANAGER* root = NULL;/* �}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^ */
	BOOK_MANAGER* rroot = NULL; /* �����f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^*/
	char* fileName = "library.bin";
	char* fileName2 = "rireki.bin";
	int end_chk;/* �I���֐��̖߂�l���i�[*/
	
	/* �}���f�[�^�\�z */
	root = initBookList();
	createBookList(root, fileName);
	
	clear_screen();
	
	/* ���C�����j���[�̃��[�v*/
	while (1) {
		/* �R�}���h�C���^�v���^�̉�ʃN���A���߂����s�����C�����j���[�ɖ߂邽�тɎ��s����i���u���j */

		/* ���j���[�\�� */
		printf("\n*** ���C�����j���[ ***\n");
		printf(" 1�F�}���\��\n");
		printf(" 2�F�}������\n");
		printf(" 3�F�ݏo/�ԋp\n");
		printf(" 4�F�ݏo����\��\n");
		printf(" 9�F�I��\n");
		printf("���j���[�ԍ��F");

		scanf("%s", inp_code);
		chk_num = numelicCheck(inp_code, 1); 

		/* �e�����i�@�\���j�b�g�j�����s */
		switch (chk_num) {
			case 1: /* 1 �\�� */
				LDisp(root);		// LDisp(BOOK_MANAGER *root),display.c �Ԃ�l0
				break;
			
			case 2: /* 2 ���� */
				LSearch(root);		//LSearch(BOOK_MANAGER *root),search.c �Ԃ�l0
				break;
			
			case 3: /* 3 �݂��o���󋵕\�� */
				LRentRet(root);		//LRentRet(BOOK_MANAGER *root),rentret.c �Ԃ�l0
				break;
			
			case 4:
				/* �����f�[�^�\�z*/
				rroot = initBookList();
				createBookList(rroot, fileName2);
				LRireki(rroot);
				break;
			
			case 9: /* 9 �I������ */
				end_chk = endCheck(root);		//endCheck(BOOK_MANAGER *root),main.c �Ԃ�l 1 or 9
				break;
			
			case -1:
				break;
			
			default:
			printf("(Error) ���������l����͂��Ă��������B\n");
				break;
		}
		if(end_chk== 1) break; 
	}
	return 0;
}