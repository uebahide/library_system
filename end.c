#include "common.h"

/*
 * ����		:	�I���m�F����
 * ����		:	�I���m�F���A�{���ɏI������ꍇ�́A�}���f�[�^�Ŏg�p�������I���������J������
 * �ďo�`��	:	int endCheck(BOOK_MANAGER *root)
 * ����		:	root		�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 * �߂�l	:	1:�I������  9:���j���[�ɖ߂�
 */
int endCheck(BOOK_MANAGER *root)
{
	int endselect;			/* ���̓��j���[�ԍ� */
	char enddata[64];		/* ���̓f�[�^ */
	BOOK_MANAGER *root_tmp; /* �������J���p�̃m�[�h�e���v���[�g */

	while (endselect != 1 && endselect != 2){
		/*�I���m�F���j���[�\��*/
		printf("\n*** �I���m�F ***\n");
		printf("�I�����܂���?\n");
		printf(" 1�F�I������\n");
		printf(" 9�F���j���[�ɖ߂�\n");
		printf("���j���[�ԍ��F");

		scanf("%s",enddata);
		/* ���͒l�`�F�b�N */
		endselect = numelicCheck(enddata,1);


		/* ���j���[�ʏ��� */
		if(endselect == 1){
			/* 3�F�ŕύX�������e��library.bin�ɏo�� */
			outPutData(root);
			/* �}���f�[�^�p�������J�� */
			while(root->next!=NULL){
				root_tmp = root->next;
				root->next = root_tmp->next;
				free(root_tmp);
			}
			break;
		}
		else if (endselect == 9){
			clear_screen();
			break;
		}
		else if (endselect == -1){
			continue;
		}
		else {
			printf("(Error)���͂��m�F���Ă��������B\n");
		}
	}
	return endselect;
}

/*
 * ����		:	���ʏo�͏���
 * ����		:	�I���̍ۂɁA�ύX�������e��}���f�[�^���i�[����Ă���t�@�C���ɏ㏑���ۑ�����
 * �ďo�`��	:	int outPutData(BOOK_MANAGER *root)
 * ����		:	root		�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 * �߂�l	:	non
 */
int outPutData(BOOK_MANAGER *root)
{
	char fileName[128] = "library.bin";		/* �}�����̓��̓f�[�^ */
	FILE *fp = NULL;
	BOOK_MANAGER *opt_temp = root->next;
	BOOK book = {0};

	if ((fp = fopen(fileName, "wb")) != NULL) {
		while (opt_temp != NULL) {
			book = opt_temp->bookData;
			if (book.isRent != 1 && book.isRent != 0) {
				puts("error");
			} else {
				fwrite(&book, sizeof(BOOK), 1, fp);
				/* printf("bookKbn:%02d bookCode:%05d title:%s author:%s\n",
				 		book.bookKbn, book.bookCode, book.title, book.author); // debug:���e�m�F */
			}
			opt_temp = opt_temp->next;
		}
	}
	return 0;
}

