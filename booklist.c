#include "common.h"

/*
 * ����		: ���X�g�\������������
 * ����		: �_�~�[�m�[�h�𐶐�����
 * �ďo�`��	: BOOK_LIST *initBookList(void)
 * ����		: void
 * �߂�l	: �_�~�[�m�[�h�̐擪�A�h���X
 */

BOOK_MANAGER* initBookList(void)
{
	BOOK_MANAGER* dummy;
	
	dummy = (BOOK_MANAGER*)malloc(sizeof(BOOK_MANAGER));
	
	dummy->bookData.bookKbn = 0;
	dummy->bookData.bookCode = 0;
	dummy->bookData.title[0] = '\0';
	dummy->bookData.author[0] = '\0';
	dummy->bookData.isRent = 0;
	dummy->next = NULL;
	
	return dummy;
}

/*
 * ����		: ���Ѓt�@�C���f�[�^�ǂݍ��ݏ���
 * ����		: ��������ɏ��Ѓf�[�^�̃��X�g�\����W�J����
 * �ďo�`��	: int createBookList(BOOK_LIST *root, const char *fileName)
 * ����		: *root		�擪�m�[�h�ւ̃|�C���^
 *			  *fileName	���̓t�@�C����������
 * �߂�l	: ��������0, �G���[����1
 */

int createBookList(BOOK_MANAGER* root, const char* fileName)
{
	FILE* fp;
	int ret=1;
	BOOK bookData;
	
	if((fp=fopen(fileName, "rb"))==NULL)
	{
		printf("�t�@�C�����I�[�v���ł��܂���B%s\n", fileName);
	}
	else
	{
		while(fread(&bookData, sizeof(BOOK), 1, fp) != 0)
		{
			registBookList(root, &bookData);
		}
		
		fclose(fp);
		ret=0;
	}
	
	return ret;
}


/*
 * ����		: ���Ѓf�[�^�o�^����
 * ����		: ���Ѓf�[�^1�����~���Ƀ��X�g�ɒǉ�����
 * �ďo�`��	: int registBookList(BOOK_LIST *root, const BOOK *book)
 * ����		: *root		�擪�m�[�h�ւ̃|�C���^
 *			  *book		�m�[�h�֒ǉ����鏑�Џ��ւ̃|�C���^
 * �߂�l	: ��������0, �G���[����1
 */
 
 int registBookList(BOOK_MANAGER* root, const BOOK* bookData)
{
	BOOK_MANAGER* temp=root;
	BOOK_MANAGER* new;
	int ret = 1;
	
	new=(BOOK_MANAGER*)malloc(sizeof(BOOK_MANAGER));
	
	if (new != NULL) 
	{
		new->bookData = *bookData;
		new->next = root->next;
		root->next=new;
		
		ret = 0;
	}
	
	return ret;
}
