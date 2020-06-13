#include "common.h"

/*
 * ����		: �}���f�[�^�������j���[
 * ����		: �}���f�[�^�������j���[��\�����āA
 *            �R�[�h�����A���얼������I�����A�I�������������������s����
 * �ďo�`��	: int LSearch(BOOK_MANAGER *root)
 * ����     : root		�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 */
int LSearch(BOOK_MANAGER *root)
{
	char num[64];
	int skbn;
	
	while(1)
	{
		/* ���j���[�\�� */
		printf("\n*** �}���f�[�^�������j���[ ***\n");
		printf(" 1 : �}���R�[�h����\n");
		printf(" 2 : ���Җ������܂�����\n");
		printf(" 9 : �߂�\n");
		printf("���j���[�ԍ��F");
		scanf("%s", num);
	
		/* ���͒l�`�F�b�N */
		skbn=numelicCheck(num, 1);		//common.c_numelicCheck�֐��Ăяo��
	
	
		switch(skbn)
		{
			/* �}���R�[�h���� */
			//search.c_inputBookCode�֐��Ăяo��
			case 1:
				inputBookCode(root);
				break;

			/* ���얼���� */
			//search.c_inputAuthor�֐��Ăяo��
			case 2:
				inputAuthor(root);	
				break;			
		
			/* ���C�����j���[�ɖ߂�*/
			case 9:
				clear_screen();
				break;
			
			case -1:
				break;
			
			default:
				printf("(Error) ���������l����͂��Ă��������B\n");
				break;
		}
		
		if(skbn==9)
		{
			break;	
		}
	}
	return 0;
}

/*
 * ����		: ���Җ���������
 * ����		: ���Җ������܂��������������͂��A
 *			: �Y������}�����������������ʂ�S�ĕ\������
 * �ďo�`��	: void inputAuthor(BOOK_MANAGER *root)
 * ����		: root		�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 * �߂�l	: none
 */
void inputAuthor(BOOK_MANAGER *root)
{
	char authorCode[64]; 
	/* ���Җ������܂������������� */			//����
	
	printf("���Җ��Ɋ܂܂�镶������͂��Ă��������F");
	scanf("%s", authorCode);
	
	/* �}���f�[�^���� */
	//search.c_searchAuthor�֐��Ăяo��
	searchAuthor(root, authorCode);

}

/*
 * ����		: �}���R�[�h��������
 * ����		: �}���R�[�h����͂��A�Y������}�����������������ʂ�S�ĕ\������
 * �ďo�`��	: void inputBookCode(BOOK_MANAGER *root)
 * ����		: root		�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 * �߂�l	: non
 */
void inputBookCode(BOOK_MANAGER *root)
{
	char bc[64];
	int bookCode;
	BOOK_MANAGER* temp;
	
	/* �}���R�[�h���� */							//����
	printf("�}���R�[�h����͂��ĉ������F");
	scanf("%s", bc);

	/* ���͒l�`�F�b�N */
	bookCode=numelicCheck(bc, 7);		//common.c_numelicCheck�֐��Ăяo��
	
	if(bookCode!=-1)
	{
		/* �}���f�[�^���� */
		//search.c_searchBook�֐��Ăяo��
		temp=searchBook(root, bookCode);

		if(temp!=NULL)
		{
			/* �}���f�[�^�w�b�_�[�\�� */
			printBookHead(); //common.c_printBookHead�֐��Ăяo��
	
			/* ���C���\�� */
			printLine();		//common.c_printLine�֐��Ăяo��
	
			/* �}���f�[�^�\�� */	
			//common.c_printBookData�֐��Ăяo��
			printBookData(temp->bookData);
		}
		else
		{
			printf("�}���f�[�^��������܂���B\n");
		}	
	}
}

/*
 * ����		: �}���f�[�^��������
 * ����		: ���Җ������܂�����������ɊY������}���f�[�^���������A
 *			: �Y������}���f�[�^��S�ĕ\������
 * �ďo�`��	: BOOK_MANAGER *searchAuthor(BOOK_MANAGER *root, char authorCode[64])
 * ����		: root		�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 *			: authorCode	���Җ������܂�����������
 * �߂�l	: ���������}���Ǘ��f�[�^�ւ̃|�C���^
 */
void searchAuthor(BOOK_MANAGER *root, char authorCode[64])
{
	/* ���͂����������}���f�[�^�̒��Җ��Ɋ܂܂�邩�`�F�b�N����	*/		//����
	BOOK_MANAGER* temp=root->next;
	int cnt=0;
	
	while(temp != NULL)
	{
		if(strstr(temp->bookData.author, authorCode)!=NULL)
		{
			/* �}���f�[�^�w�b�_�[�\�� */
			//common.c_printBookHead�֐��Ăяo��
			printBookHead();

			/* ���C���\�� */
			//common.c_printLine�֐��Ăяo��
			printLine();

			/* �}���f�[�^�\�� */
			//common.c_printBookData�֐��Ăяo��
			printBookData(temp->bookData);
			
			cnt++;
		}
		temp = temp->next;	
	}
	if(cnt==0)
	{
		printf("���͂��ꂽ�������܂ޒ��҂̐}���f�[�^�͂���܂���B\n");	
	}
		
	
}

/*
 * ����		: �}���f�[�^��������
 * ����		: �}���R�[�h�Ɉ�v����}���f�[�^���������A��v�����}���f�[�^�ւ�
 * 			: �|�C���^��Ԃ�
 * �ďo�`��	: BOOK_MANAGER *searchBook(BOOK_MANAGER *root, int bookCode)
 * ����		: root		�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 *			: bookCode	�����Ώۂ̐}���R�[�h�i�敪�{�R�[�h:7���j
 * �߂�l	: ���������}���f�[�^�ւ̃|�C���^
 *          : ������Ȃ������ꍇ�́ANULL
 */
BOOK_MANAGER *searchBook(BOOK_MANAGER *root, int bookCode)
{
	/* �����Ώۂ̐}���R�[�h�ƈ�v����}���f�[�^������ */
	BOOK_MANAGER* temp = root->next;
	int tempBookCode;
	
	while(temp!=NULL)
	{
		tempBookCode=(temp->bookData.bookKbn*100000) + (temp->bookData.bookCode);
		
		if(tempBookCode==bookCode)
		{
			break;	
		}
		
		temp=temp->next;
	}
	
	return temp;
	
	/* ��v����ꍇ�A�}���f�[�^�̃|�C���^��߂�l�ɐݒ� */
	
	/* ��v����}���f�[�^���Ȃ������ꍇ�A*/
	/* �ŏI�}���f�[�^�̎��m�[�h�ւ̃|�C���^(NULL)��߂�l�ɐݒ� */
	
}

