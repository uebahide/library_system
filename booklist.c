#include "common.h"

/*
 * 名称		: リスト構造初期化処理
 * 処理		: ダミーノードを生成する
 * 呼出形式	: BOOK_LIST *initBookList(void)
 * 引数		: void
 * 戻り値	: ダミーノードの先頭アドレス
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
 * 名称		: 書籍ファイルデータ読み込み処理
 * 処理		: メモリ上に書籍データのリスト構造を展開する
 * 呼出形式	: int createBookList(BOOK_LIST *root, const char *fileName)
 * 引数		: *root		先頭ノードへのポインタ
 *			  *fileName	入力ファイル名文字列
 * 戻り値	: 成功時は0, エラー時は1
 */

int createBookList(BOOK_MANAGER* root, const char* fileName)
{
	FILE* fp;
	int ret=1;
	BOOK bookData;
	
	if((fp=fopen(fileName, "rb"))==NULL)
	{
		printf("ファイルをオープンできません。%s\n", fileName);
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
 * 名称		: 書籍データ登録処理
 * 処理		: 書籍データ1件を降順にリストに追加する
 * 呼出形式	: int registBookList(BOOK_LIST *root, const BOOK *book)
 * 引数		: *root		先頭ノードへのポインタ
 *			  *book		ノードへ追加する書籍情報へのポインタ
 * 戻り値	: 成功時は0, エラー時は1
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
