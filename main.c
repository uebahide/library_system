#include "common.h"

int main(void)
{
	int chk_num; /* switch文の条件分に利用、numelicCheck()の返り値を格納 */
	char inp_code[256];	// 入力データを格納する
	
	BOOK_MANAGER* root = NULL;/* 図書データ（リスト構造）の先頭ノードへのポインタ */
	BOOK_MANAGER* rroot = NULL; /* 履歴データ（リスト構造）の先頭ノードへのポインタ*/
	char* fileName = "library.bin";
	char* fileName2 = "rireki.bin";
	int end_chk;/* 終了関数の戻り値を格納*/
	
	/* 図書データ構築 */
	root = initBookList();
	createBookList(root, fileName);
	
	clear_screen();
	
	/* メインメニューのループ*/
	while (1) {
		/* コマンドインタプリタの画面クリア命令を実行＞メインメニューに戻るたびに実行する（仮置き） */

		/* メニュー表示 */
		printf("\n*** メインメニュー ***\n");
		printf(" 1：図書表示\n");
		printf(" 2：図書検索\n");
		printf(" 3：貸出/返却\n");
		printf(" 4：貸出履歴表示\n");
		printf(" 9：終了\n");
		printf("メニュー番号：");

		scanf("%s", inp_code);
		chk_num = numelicCheck(inp_code, 1); 

		/* 各処理（機能ユニット）を実行 */
		switch (chk_num) {
			case 1: /* 1 表示 */
				LDisp(root);		// LDisp(BOOK_MANAGER *root),display.c 返り値0
				break;
			
			case 2: /* 2 検索 */
				LSearch(root);		//LSearch(BOOK_MANAGER *root),search.c 返り値0
				break;
			
			case 3: /* 3 貸し出し状況表示 */
				LRentRet(root);		//LRentRet(BOOK_MANAGER *root),rentret.c 返り値0
				break;
			
			case 4:
				/* 履歴データ構築*/
				rroot = initBookList();
				createBookList(rroot, fileName2);
				LRireki(rroot);
				break;
			
			case 9: /* 9 終了処理 */
				end_chk = endCheck(root);		//endCheck(BOOK_MANAGER *root),main.c 返り値 1 or 9
				break;
			
			case -1:
				break;
			
			default:
			printf("(Error) 正しい数値を入力してください。\n");
				break;
		}
		if(end_chk== 1) break; 
	}
	return 0;
}