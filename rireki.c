#include "common.h"

void LRireki(BOOK_MANAGER* rroot)
{
	char num[64];
	int skbn;
	
	while(1)
	{
		printf("\n*** �ݏo����\�����j���[ ***\n");
		printf(" 1�F�ݏo������\������\n");
		printf(" 9�F�I��\n");
		/*�I�����j���[�\��*/
		printf("���j���[�ԍ��F");
		scanf("%s", num);
	
		skbn=numelicCheck(num, 1);
	
		switch(skbn)
		{
			case 1:	
				printRireki(rroot);
				break;
			case 9:
				clear_screen();
				break;
			case -1:
				break;
			
			default:
				printf("(Error)���������l�œ��͂��Ă��������B\n");
				break;		
		}
		
		if(skbn==9)
		{
			break;	
		}
	}	
}

void printRireki(BOOK_MANAGER* rroot)
{
	BOOK_MANAGER* temp=rroot->next;
	
	/* �w�b�_�[�\��*/
	printBookHead();
		
	/* ���C���\��*/
	printLine();
	while(temp!=NULL)
	{	
		/* �ݏo���̐}���R�[�h������\��*/
		printBookData(temp->bookData);
		
		temp = temp->next;
	}
}

