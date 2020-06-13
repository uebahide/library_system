#include "common.h"

/*
 * 名称		: 画面のクリア
 * 処理		: コマンドインタプリタの画面クリア命令を実行
* 呼出形式	: void clear_screen(void)
 * 引数		: 無し
 * 戻り値	: 無し
 */
void clear_screen()
{
	system("cls");
}

/*
 * 名称		: 入力データチェック処理
 * 処理		: 入力データのニューメリックチェック等を行う
 * 呼出形式	: int numelicCheck(char inpdata[],int inpLength)
 * 引数		: inpdata    チェック対象の入力データ
 *			  inpLength  入力許可桁数
 * 戻り値	: ret	9:終了 -1:入力エラー 以外:int型に変換した入力値
 */
int numelicCheck(char inpdata[],int inpLength)/* 文字列としてチェックするためにinpdataはchar型*/
{
	int i = 0;
	int ret = 1;
	
	/* 9:終了 */
	
	if (strlen(inpdata) == 1 && inpdata[0] == '9') /* 91とか999とかはだめで、9であればオッケイ*/{
		return 9;
	}
	
	
	/* 入力桁数チェック */
	if (strlen(inpdata) != inpLength || inpdata[0] == '\0')
	/* 指定した桁数以外の桁か何も入力がいない場合はエラー表示*/{
		printf("(Error) %d 桁の半角数字で入力してください。\n",inpLength);
		ret = -1;
	} else {
		/* 文字チェック */
		while (inpdata[i] != '\0' && ret != 99) {/* ret != 99 てどういうこと？？*/
			if (isdigit(inpdata[i]) == 0) {
				printf("(Error)数値を入力してください。\n");
				ret = -1;
				break;
			}
			i++;
		}
	}
	
	/* 数値が入力された場合はint型に変換 */
	if (ret >= 0) {
		ret = atoi(inpdata);
	}
	return ret;/* 異常な値なら-1、正常な値なら入力値をint型にして返す*/
}

/*
 * 名称		: ライン表示処理
 * 処理		: ライン表示を行う
 * 呼出形式	: void printLine()
 * 引数		: none
 * 戻り値	: none
 */
void printLine()
{
	printf("---------------------------------------------------------------------------------------------\n");
}

/*
 * 名称		: 図書データヘッダー表示
 * 処理		: 図書データヘッダー表示を行う
 * 呼出形式	: void printBookHead()
 * 引数		: non
 * 戻り値	: non
 */
void printBookHead()
{
	printf("\n区分|   コード   |          タイトル           |             著者             |    状態    |\n");
}


/*
 * 名称		: 図書データ表示処理
 * 処理		: 図書データ一冊分の表示を行う
 * 呼出形式	: void printBookData(BOOK book)
 * 引数		: book 図書データ
 * 戻り値	: none
 */
void printBookData(BOOK book)
{
	printf("  %02d|", book.bookKbn);
	printf("       %05d|", book.bookCode);
	printf("%29s|", book.title);
	printf("%30s|", book.author);
	
	if (book.isRent == 0) {
		printf("    貸出可能|\n");
	} else {
		printf("    貸出不可|\n");
	}
}

