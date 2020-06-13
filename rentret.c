/*
 *  IC図書館システム
 */
#include "common.h"

RENT_MANAGER* initRentRetList(void);
int createRentData(RENT_MANAGER *root, const char *fileName);
int registRent(RENT_MANAGER *root, const RENT *newData);
void clearRentData(RENT_MANAGER *root);
int outPutRireki(BOOK_MANAGER *temp);


/*
 * 名称		: 貸出返却メニュー表示
 * 処理		: 図書データの貸出返却メニューを表示して、
 *            貸出、返却を選択し、選択した処理を実行する
 * 呼出形式	: int LRentRet(BOOK_MANAGER *root)
 * 引数     : root		図書データ（リスト構造）の先頭ノードへのポインタ
 */
int LRentRet(BOOK_MANAGER *root)
{
	int skbn3; /* switch文の条件分に利用、numelicCheck()の返り値を格納 */
	int ret_num3; /* 各関数の返り値を格納する */
	char menu_num[256];	// 入力データを格納する

	while (1) {
		/* メニュー表示 */
		printf("\n*** 図書貸出返却メニュー ***\n");
		printf(" 1：貸出\n");
		printf(" 2：返却\n");
		printf(" 9：終了\n");

		/* メニュー番号を入力 */
		printf("メニュー番号:");
		scanf("%s", menu_num);

		/* 入力値チェック */ /* 返り値はint型になる */
		skbn3 = numelicCheck(menu_num, 1); // common.c

		/* 貸出返却処理 */
		switch (skbn3) {
			case 1:
				/* 貸出処理を行う */
				rentBook(root, 0);
				break;
			case 2:
				/* 返却処理を行う */
				rentBook(root, 1);
				break;
			case 9:
				system("cls");
				break;

			case -1:
				break;

			default:
				printf("(Error)正しい数値を入力してください。\n");
				break;
		}
		if(skbn3 == 9) break; /* debug用:9を入力したら終了 */
	}

	return 0;
}

/*
 * 名称		: 貸出返却処理
 * 処理		: 図書貸し出し・返却処理を行う
 * 呼出形式	: int rentBook(BOOK_MANAGER *root,int kbn)
 * 引数		: root	図書データ（リスト構造）の先頭ノードへのポインタ
 *			  kbn	0：貸出　1：返却
 * 戻り値	: 成功時は0, エラー時は1
 */
int rentBook(BOOK_MANAGER *root, int kbn)
{
	FILE *fp = NULL;		/* ファイルポインタ */
	BOOK_MANAGER *temp = root->next; /* 処理対象ノード */
	RENT_MANAGER* rentRetRoot = NULL;
	RENT_MANAGER* rentRetTemp;
	int tempBookCode;
	int ret = 0;
	char fileName_rr[64]; /* ファイル名格納用の変数 */

	/* 貸出or返却のファイル名を取得 */
	if(kbn == 0){
		strcpy(fileName_rr, "Ret.bin");
	}
	else if(kbn == 1){
		strcpy(fileName_rr, "Rent.bin");
	}
	else printf("Error\n"); /* debug : 存在した */

	/* ファイルが開けるかどうかの確認 */
	if((fp = fopen(fileName_rr, "rb")) == NULL){
		printf("ファイルがオープンできません");
		return 1; /* ErrorCode 1:失敗 */
	}

	/* 貸出返却データ構築 */
	rentRetRoot = initRentRetList();
	createRentData(rentRetRoot, fileName_rr);

	/* レンタルデータをもとに図書データの貸出情報を変更する */
	while(temp != NULL)
	{
		tempBookCode = temp->bookData.bookKbn*100000 + temp->bookData.bookCode;
		rentRetTemp = rentRetRoot->next;
		while (rentRetTemp != NULL) {
			if(rentRetTemp->rentData.sumCode == tempBookCode)
			{
				/* すでに貸出中に貸出処理 or すでに返却中に返却処理 */
				if(kbn != temp->bookData.isRent){
					if(kbn == 0) {
						printf("図書コード：%07d | タイトル： %s は既に貸出中です。\n", tempBookCode, temp->bookData.title);
					}
					else {
						printf("図書コード：%07d | タイトル： %s は既に返却済です。\n", tempBookCode, temp->bookData.title);
					}
				}
				if(kbn == 0){
					/* 貸出情報を貸出可（返却）にする */
					temp->bookData.isRent = 1;
					break;
				} else if (kbn == 1){
					/* 貸出情報を貸出中にする */
					temp->bookData.isRent = 0;
					outPutRireki(temp);
					break;
				}
			}
			rentRetTemp = rentRetTemp->next;
		}

		temp = temp->next; /* 基準となるノードを一つ進める*/

	}

	if(kbn == 0){
		printf("\n貸出不能に変更しました。");
	}
	else if(kbn == 1){
		printf("\n貸出可能に変更しました。");
	}
	else {
		printf("Error");
	}

	/* 貸出返却データ用メモリ開放 */
	clearRentData(rentRetRoot);

	printf("\n");

	return ret;
}

/*
 * 名称		: 貸出返却データ初期化処理
 * 処理		: 貸出、或いは、返却ファイルから、レンタルデータを読み込むための、
 *            貸出返却データ（リスト構造）の先頭ノードを作成し、を初期化する
 * 呼出形式	: RENT_MANAGER* initRentRetList(void)
 * 引数		: non
 * 戻り値	: rDummy ダミーノードのアドレス
 */
RENT_MANAGER* initRentRetList(void)
{
	RENT_MANAGER* rDummy;

	rDummy = (RENT_MANAGER*)malloc(sizeof(RENT_MANAGER));

	rDummy->rentData.sumCode = 0;
	rDummy->next = NULL;

	return rDummy;
}

/*
 * 名称		: 貸出返却データ構築処理
 * 処理		: 貸出、或いは、返却ファイルから、レンタルデータを読み込み、
 *            貸出返却データ（リスト構造）に登録し、貸出返却データを構築する
 * 呼出形式	: int createRentData(RENT_MANAGER *root, char *fileName)
 * 引数		: root		貸出返却データ（リスト構造）の先頭ノードへのダブルポインタ
 *			  fileName	貸出（返却）データ入力ファイル名（Rent.bin or Ret.bin）
 * 戻り値	: 成功時は0, エラー時は1
 */
int createRentData(RENT_MANAGER *rentRetRoot, const char *fileName)
{
	FILE *fp = NULL;		/* ファイルポインタ */
	int ret = 1;			/* 戻り値 */
	RENT newData;			/* 1件分の図書データ（区分+コード） */
	RENTDAT newRentData;	/* 1件分の図書データ(区分、コード）*/

	int kbn = 0;
	int code = 0;

	/* ファイルが開けた場合 */
	if ((fp = fopen(fileName, "rb")) != NULL) {
		/* 1件ずつレンタルデータを読み込む */
		while (fread(&newRentData, sizeof(RENTDAT), 1, fp) != 0) {
			/* データ構造に登録する*/
			newData.sumCode = ( newRentData.kbn * 100000 ) + newRentData.code;
			registRent(rentRetRoot, &newData);
		}
		fclose(fp);		/* ファイルクローズ */
		ret = 0;		/* 処理成功 */
	}
	return ret;
}

/*
 * 名称		: レンタルデータ登録処理
 * 処理		: 貸し出し/返却データを1件、貸出返却データ（リスト構造）に追加する
 * 呼出形式	: int registRent(RENT_MANAGER *root, RENT *newData)
 * 引数		: root		貸出返却データ（リスト構造）の先頭ノードへのダブルポインタ
 *			  newData	追加対象の図書データへのポインタ
 * 戻り値	: 成功時は0, エラー時は1
 */
int registRent(RENT_MANAGER *rentRetRoot, const RENT *newData)
{
	int ret = 1;				/* 戻り値用変数 */
	RENT_MANAGER *temp = rentRetRoot;	/* 追加場所参照用 */
	RENT_MANAGER *newNode;

	newNode = (RENT_MANAGER *)malloc(sizeof(RENT_MANAGER));	/* 新規ノード用変数 */

	/* 新規ノードの生成 */
	if (newNode != NULL) {
		newNode->rentData = *newData;	/* データの設定 */
		newNode->next = rentRetRoot->next;
		rentRetRoot->next = newNode;
		ret = 0;						/* 戻り値の設定 */
	}

	return ret;
}

/*
 * 名称		: レンタルデータ用メモリ解放
 * 処理		: 貸出返却データ（リスト構造）で使用した動的メモリを解放する
 * 呼出形式	: void clearRentData(RENT_MANAGER *root)
 * 引数		: root		貸出返却データ（リスト構造）の先頭ノードへのダブルポインタ
 * 戻り値	: non
 */
void clearRentData(RENT_MANAGER *root)
{
	RENT_MANAGER *current = root;
	RENT_MANAGER *next = NULL;

	while (current != NULL) {
		next = current->next;

		/* 動的メモリの解放 */
		free(current);
		current = next;
	}
}

/*
 * 名称		: 貸出履歴出力処理
 * 処理		: 貸出履歴を外部ファイル（rireki.bin）に出力する
 * 呼出形式	: int outPutRireki(BOOK_MANAGER *temp)
 * 引数		: temp		貸出データ（リスト構造）のノードへのダブルポインタ
 * 戻り値	: non
 */
int outPutRireki(BOOK_MANAGER *temp)
{
	char fileName[128] = "rireki.bin";		/* 図書情報の入力データ */
	FILE *fp = NULL;
	BOOK_MANAGER *opt_temp = temp;
	BOOK bookRireki = {0};

	// printf("temp->bookData.title : %s\n", temp->bookData.title);

	if ((fp = fopen(fileName, "ab")) != NULL) {
		bookRireki = opt_temp->bookData;
		// printf("bookRireki.title: %s\n", bookRireki.title);
		fwrite(&bookRireki, sizeof(BOOK), 1, fp);

	}
	fclose(fp);
	return 0;
}
