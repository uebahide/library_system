#include "common.h"

void LRireki(BOOK_MANAGER* rroot)
{
	char num[64];
	int skbn;
	
	while(1)
	{
		printf("\n*** 貸出履歴表示メニュー ***\n");
		printf(" 1：貸出履歴を表示する\n");
		printf(" 9：終了\n");
		/*選択メニュー表示*/
		printf("メニュー番号：");
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
				printf("(Error)正しい数値で入力してください。\n");
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
	
	/* ヘッダー表示*/
	printBookHead();
		
	/* ライン表示*/
	printLine();
	while(temp!=NULL)
	{	
		/* 貸出中の図書コードを一冊表示*/
		printBookData(temp->bookData);
		
		temp = temp->next;
	}
}

