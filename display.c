/*
 *  IC�}���كV�X�e��
 *
 *  COPYRIGHT(C) FUJITSU LEARNING MEDIA LIMITED
 *
 */
#include "common.h"

/*
 * ����		: �}���f�[�^�\�����j���[
 * ����		: �}���f�[�^�̕\�����j���[��\�����āA
 *            �����A�~���A�敪�ʑݏo�󋵂�I�����A�I�������\�����������s����
 * �ďo�`��	: int LDisp(BOOK_MANAGER *root)
 * ����     : root		�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 */
int LDisp(BOOK_MANAGER *root)
{
	char menu_num[256];
	int skbn;
	
	while(1) {
		/* ���j���[�\�� */
		printf("\n***�}���f�[�^�\�����j���[***\n");
		printf(" 1�F����\n");
		printf(" 2�F�~��\n");
		printf(" 3�F�敪�ʑݏo��\n");
		printf(" 9�F�߂�\n");
		printf("���j���[�ԍ��F");
		scanf("%s", menu_num);

		/* ���͒l�`�F�b�N */
		skbn = numelicCheck(menu_num, 1);
		
		/* �}���f�[�^�\�[�g */
		switch(skbn)
		{
			case 1:
				sortBook(root, skbn);
				printf("\n�����\�[�g\n");
				sortDisp(root);
				break;
			case 2:
				sortBook(root, skbn);
				printf("\n�~���\�[�g\n");
				sortDisp(root);
				break;
			case 3:
				rentalDisp(root);
				break;
			case 9:
				break;
			case -1:
				break;
			default:
			printf("(Error)���������l����͂��Ă��������B\n");
			 	break;
		}

		if(skbn==9)
		{
			clear_screen();
			break;
		}
	}

	return 0;
}
/*
 * ����		:	�}���f�[�^�\�[�g����
 * ����		:	�}���f�[�^��}���R�[�h�i�敪�{�R�[�h�j�Ń\�[�g����
 * �ďo�`��	:	void sortBook(BOOK_MANAGER *root,int skbn)
 * ����		:	root	�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 *				skbn	�\�[�g�敪�i1:����  2:�~���j
 * �߂�l	:	�\�[�g�����}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 */
void sortBook(BOOK_MANAGER *root, int skbn)        /* �߂�l��void �ł͂Ȃ���*/
{
	BOOK_MANAGER *temp = root->next;
	BOOK work;      /* �ޔ�p*/
	
	BOOK_MANAGER *room;

	int nextBookCode; /* ���Z�����R�[�h */
	int tempBookCode;

	
	/* ����[�v*/
	if(skbn == 1)
	{
		while(temp != NULL)
		{	
			room=temp->next;
			
			/* ���񃋁[�v*/
			while(room != NULL)
			{
				nextBookCode = room->bookData.bookKbn*100000 + room->bookData.bookCode;
				tempBookCode = temp->bookData.bookKbn*100000 + temp->bookData.bookCode;

				
				if(nextBookCode < tempBookCode)
				{
					work                 = temp->bookData;
					temp->bookData       =room->bookData;
					room->bookData = work;
				}
				
				room=room->next;/* ��m�[�h�Ɣ�r����m�[�h����i�߂�*/
				
			}
			
			temp = temp->next; /* ����̊�ƂȂ�m�[�h����i�߂�*/
			
		}
	}

	if(skbn == 2)
	{
		while(temp != NULL)
		{	
			room=temp->next;
			
			/* ���񃋁[�v*/
			while(room != NULL)
			{
				nextBookCode = room->bookData.bookKbn*100000 + room->bookData.bookCode;
				tempBookCode = temp->bookData.bookKbn*100000 + temp->bookData.bookCode;

				
				if(nextBookCode > tempBookCode)
				{
					work                 = temp->bookData;
					temp->bookData       =room->bookData;
					room->bookData = work;
				}
				
				room=room->next;/* ��m�[�h�Ɣ�r����m�[�h����i�߂�*/
				
			}
			
			temp = temp->next; /* ����̊�ƂȂ�m�[�h����i�߂�*/
			
		}
	}
}


/*
 * ����		: �}���f�[�^�\������
 * ����		: �\�[�g���ꂽ�}���f�[�^�̐}������S�ĕ\������
 * �ďo�`��	: void display(BOOK_MANAGER *root)
 * ����		: root	�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 * �߂�l	: non
 */
void sortDisp(BOOK_MANAGER *root)
{
	BOOK_MANAGER* temp = root->next; /* �����Ώۃm�[�h */

	/* �}���f�[�^�w�b�_�[�\�� */
	printBookHead();

	/* ���C���\�� */
	printLine();

	/* �}���f�[�^�\�� */
	while(temp != NULL)
	{
		printBookData(temp->bookData);
		temp = temp->next; /* ����̊�ƂȂ�m�[�h����i�߂�*/
	}

}



/*
 * ����		: �敪�ʑݏo�󋵕\��
 * ����		: �}���敪���Ƃ̑ݏo�󋵕\�����s��
 * �ďo�`��	: void rentalDisp(BOOK_MANAGER *root)
 * ����		: root	�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 * �߂�l	: non
 */
void rentalDisp(BOOK_MANAGER *root)
{

	BOOK_MANAGER *temp = root->next;	/* �����Ώۃm�[�h */
	int ztotal = 0;				/* �݌ɑ����v */
	int rentOKcnt = 0;			/* �ݏo�����v	*/
	int rentNGcnt = 0;			/* �ݏo�������v */
	int k_rentOKcnt = 0;		/* �ݏo�敪���v */
	int k_rentNGcnt = 0;		/* �ݏo�������v */
	int svkbn;					/* �������敪 */

	svkbn = temp->bookData.bookKbn; /* �ŏ��̋敪��ێ� */

	/* �K�C�h���b�Z�[�W�\�� */
	printf("\n�敪���Ƃ̑ݏo�E�ݏo�����v�ꗗ\n");

	/* ���C���\�� */
	printLine();

	/* �敪���Ƃ̑ݏo�A�ݏo���̖{�̐����v�Z���� */
	// while(temp->next != NULL){
	while(1){
		// printf("svkbn: %02d\n", svkbn);
		ztotal++;
		if(temp->bookData.isRent == 1){
			rentOKcnt++; /* �ݏo�����v�� 1������	*/
			k_rentOKcnt++; /* �敪�ʑݏo�����v�� 1������ */
		}
		else {
			rentNGcnt++; /* �ݏo�������v�� 1������ */
			k_rentNGcnt++; /* �敪�ʑݏo�������v�� 1������ */
		}
		/* ���̃m�[�h�����݂���ꍇ */
		if(temp->next == NULL) {
			printf("�敪 %02d �̑ݏo�̍������v�́F%d\n", temp->bookData.bookKbn, k_rentOKcnt);
			printf("�敪 %02d �̑ݏo���̍������v�́F%d\n", temp->bookData.bookKbn, k_rentNGcnt);
			break;
		}
		/* �Ō�̃m�[�h�̏ꍇ */
		if(temp->next != NULL && svkbn != temp->next->bookData.bookKbn){
			printf("�敪 %02d �̑ݏo�̍������v�́F%d\n", temp->bookData.bookKbn, k_rentOKcnt);
			printf("�敪 %02d �̑ݏo���̍������v�́F%d\n", temp->bookData.bookKbn, k_rentNGcnt);

			svkbn = temp->bookData.bookKbn;

			/* �敪���Ƃ̍��v�l�����Z�b�g */
			k_rentOKcnt = 0;
			k_rentNGcnt = 0;
		}
		temp = temp->next;/* �m�[�h��i�߂� */

	}
	/* ���C���\�� */
	printLine();

	/* �K�C�h���b�Z�[�W�\�� */
	printf("\n�ݏo���E�ݏo�̍������v�ꗗ\n");

	/* ���C���\�� */
	printLine();

	/* �}���f�[�^�S�̂̑ݏo�A�ݏo���̖{�̐���\������ */
	printf("�ݏo�̍������v�́F%d\n", rentOKcnt);
	printf("�ݏo���̍������v�́F%d\n", rentNGcnt);
	printf("�݌ɂ̑����v�� %d\n", ztotal);

	/* ���C���\�� */
	printLine();
	printf("\n");
}
