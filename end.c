#include "common.h"

/*
 * 名称		:	終了確認処理
 * 処理		:	終了確認し、本当に終了する場合は、図書データで使用した動的メモリを開放する
 * 呼出形式	:	int endCheck(BOOK_MANAGER *root)
 * 引数		:	root		図書データ（リスト構造）の先頭ノードへのポインタ
 * 戻り値	:	1:終了する  9:メニューに戻る
 */
int endCheck(BOOK_MANAGER *root)
{
	int endselect;			/* 入力メニュー番号 */
	char enddata[64];		/* 入力データ */
	BOOK_MANAGER *root_tmp; /* メモリ開放用のノードテンプレート */

	while (endselect != 1 && endselect != 2){
		/*終了確認メニュー表示*/
		printf("\n*** 終了確認 ***\n");
		printf("終了しますか?\n");
		printf(" 1：終了する\n");
		printf(" 9：メニューに戻る\n");
		printf("メニュー番号：");

		scanf("%s",enddata);
		/* 入力値チェック */
		endselect = numelicCheck(enddata,1);


		/* メニュー別処理 */
		if(endselect == 1){
			/* 3：で変更した内容をlibrary.binに出力 */
			outPutData(root);
			/* 図書データ用メモリ開放 */
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
			printf("(Error)入力を確認してください。\n");
		}
	}
	return endselect;
}

/*
 * 名称		:	結果出力処理
 * 処理		:	終了の際に、変更した内容を図書データが格納されているファイルに上書き保存する
 * 呼出形式	:	int outPutData(BOOK_MANAGER *root)
 * 引数		:	root		図書データ（リスト構造）の先頭ノードへのポインタ
 * 戻り値	:	non
 */
int outPutData(BOOK_MANAGER *root)
{
	char fileName[128] = "library.bin";		/* 図書情報の入力データ */
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
				 		book.bookKbn, book.bookCode, book.title, book.author); // debug:内容確認 */
			}
			opt_temp = opt_temp->next;
		}
	}
	return 0;
}

