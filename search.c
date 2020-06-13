#include "common.h"

/*
 * 名称		: 図書データ検索メニュー
 * 処理		: 図書データ検索メニューを表示して、
 *            コード検索、著作名検索を選択し、選択した検索処理を実行する
 * 呼出形式	: int LSearch(BOOK_MANAGER *root)
 * 引数     : root		図書データ（リスト構造）の先頭ノードへのポインタ
 */
int LSearch(BOOK_MANAGER *root)
{
	char num[64];
	int skbn;
	
	while(1)
	{
		/* メニュー表示 */
		printf("\n*** 図書データ検索メニュー ***\n");
		printf(" 1 : 図書コード検索\n");
		printf(" 2 : 著者名あいまい検索\n");
		printf(" 9 : 戻る\n");
		printf("メニュー番号：");
		scanf("%s", num);
	
		/* 入力値チェック */
		skbn=numelicCheck(num, 1);		//common.c_numelicCheck関数呼び出し
	
	
		switch(skbn)
		{
			/* 図書コード検索 */
			//search.c_inputBookCode関数呼び出し
			case 1:
				inputBookCode(root);
				break;

			/* 著作名検索 */
			//search.c_inputAuthor関数呼び出し
			case 2:
				inputAuthor(root);	
				break;			
		
			/* メインメニューに戻る*/
			case 9:
				clear_screen();
				break;
			
			case -1:
				break;
			
			default:
				printf("(Error) 正しい数値を入力してください。\n");
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
 * 名称		: 著者名検索処理
 * 処理		: 著者名あいまい検索文字列を入力し、
 *			: 該当する図書情報を検索した結果を全て表示する
 * 呼出形式	: void inputAuthor(BOOK_MANAGER *root)
 * 引数		: root		図書データ（リスト構造）の先頭ノードへのポインタ
 * 戻り値	: none
 */
void inputAuthor(BOOK_MANAGER *root)
{
	char authorCode[64]; 
	/* 著者名あいまい検索文字入力 */			//自作
	
	printf("著者名に含まれる文字を入力してください：");
	scanf("%s", authorCode);
	
	/* 図書データ検索 */
	//search.c_searchAuthor関数呼び出し
	searchAuthor(root, authorCode);

}

/*
 * 名称		: 図書コード検索処理
 * 処理		: 図書コードを入力し、該当する図書情報を検索した結果を全て表示する
 * 呼出形式	: void inputBookCode(BOOK_MANAGER *root)
 * 引数		: root		図書データ（リスト構造）の先頭ノードへのポインタ
 * 戻り値	: non
 */
void inputBookCode(BOOK_MANAGER *root)
{
	char bc[64];
	int bookCode;
	BOOK_MANAGER* temp;
	
	/* 図書コード入力 */							//自作
	printf("図書コードを入力して下さい：");
	scanf("%s", bc);

	/* 入力値チェック */
	bookCode=numelicCheck(bc, 7);		//common.c_numelicCheck関数呼び出し
	
	if(bookCode!=-1)
	{
		/* 図書データ検索 */
		//search.c_searchBook関数呼び出し
		temp=searchBook(root, bookCode);

		if(temp!=NULL)
		{
			/* 図書データヘッダー表示 */
			printBookHead(); //common.c_printBookHead関数呼び出し
	
			/* ライン表示 */
			printLine();		//common.c_printLine関数呼び出し
	
			/* 図書データ表示 */	
			//common.c_printBookData関数呼び出し
			printBookData(temp->bookData);
		}
		else
		{
			printf("図書データが見つかりません。\n");
		}	
	}
}

/*
 * 名称		: 図書データ検索処理
 * 処理		: 著者名あいまい検索文字列に該当する図書データを検索し、
 *			: 該当する図書データを全て表示する
 * 呼出形式	: BOOK_MANAGER *searchAuthor(BOOK_MANAGER *root, char authorCode[64])
 * 引数		: root		図書データ（リスト構造）の先頭ノードへのポインタ
 *			: authorCode	著者名あいまい検索文字列
 * 戻り値	: 見つかった図書管理データへのポインタ
 */
void searchAuthor(BOOK_MANAGER *root, char authorCode[64])
{
	/* 入力した文字が図書データの著者名に含まれるかチェックする	*/		//自作
	BOOK_MANAGER* temp=root->next;
	int cnt=0;
	
	while(temp != NULL)
	{
		if(strstr(temp->bookData.author, authorCode)!=NULL)
		{
			/* 図書データヘッダー表示 */
			//common.c_printBookHead関数呼び出し
			printBookHead();

			/* ライン表示 */
			//common.c_printLine関数呼び出し
			printLine();

			/* 図書データ表示 */
			//common.c_printBookData関数呼び出し
			printBookData(temp->bookData);
			
			cnt++;
		}
		temp = temp->next;	
	}
	if(cnt==0)
	{
		printf("入力された文字を含む著者の図書データはありません。\n");	
	}
		
	
}

/*
 * 名称		: 図書データ検索処理
 * 処理		: 図書コードに一致する図書データを検索し、一致した図書データへの
 * 			: ポインタを返す
 * 呼出形式	: BOOK_MANAGER *searchBook(BOOK_MANAGER *root, int bookCode)
 * 引数		: root		図書データ（リスト構造）の先頭ノードへのポインタ
 *			: bookCode	検索対象の図書コード（区分＋コード:7桁）
 * 戻り値	: 見つかった図書データへのポインタ
 *          : 見つからなかった場合は、NULL
 */
BOOK_MANAGER *searchBook(BOOK_MANAGER *root, int bookCode)
{
	/* 検索対象の図書コードと一致する図書データを検索 */
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
	
	/* 一致する場合、図書データのポインタを戻り値に設定 */
	
	/* 一致する図書データがなかった場合、*/
	/* 最終図書データの次ノードへのポインタ(NULL)を戻り値に設定 */
	
}

