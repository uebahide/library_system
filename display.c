/*
 *  IC図書館システム
 *
 *  COPYRIGHT(C) FUJITSU LEARNING MEDIA LIMITED
 *
 */
#include "common.h"

/*
 * 名称		: 図書データ表示メニュー
 * 処理		: 図書データの表示メニューを表示して、
 *            昇順、降順、区分別貸出状況を選択し、選択した表示処理を実行する
 * 呼出形式	: int LDisp(BOOK_MANAGER *root)
 * 引数     : root		図書データ（リスト構造）の先頭ノードへのポインタ
 */
int LDisp(BOOK_MANAGER *root)
{
	char menu_num[256];
	int skbn;
	
	while(1) {
		/* メニュー表示 */
		printf("\n***図書データ表示メニュー***\n");
		printf(" 1：昇順\n");
		printf(" 2：降順\n");
		printf(" 3：区分別貸出状況\n");
		printf(" 9：戻る\n");
		printf("メニュー番号：");
		scanf("%s", menu_num);

		/* 入力値チェック */
		skbn = numelicCheck(menu_num, 1);
		
		/* 図書データソート */
		switch(skbn)
		{
			case 1:
				sortBook(root, skbn);
				printf("\n昇順ソート\n");
				sortDisp(root);
				break;
			case 2:
				sortBook(root, skbn);
				printf("\n降順ソート\n");
				sortDisp(root);
				break;
			case 3:
				rentalDisp(root);
				break;
			case 9:
				break;
			case -1:
				break;
			default:
			printf("(Error)正しい数値を入力してください。\n");
			 	break;
		}

		if(skbn==9)
		{
			clear_screen();
			break;
		}
	}

	return 0;
}
/*
 * 名称		:	図書データソート処理
 * 処理		:	図書データを図書コード（区分＋コード）でソートする
 * 呼出形式	:	void sortBook(BOOK_MANAGER *root,int skbn)
 * 引数		:	root	図書データ（リスト構造）の先頭ノードへのポインタ
 *				skbn	ソート区分（1:昇順  2:降順）
 * 戻り値	:	ソートした図書データ（リスト構造）の先頭ノードへのポインタ
 */
void sortBook(BOOK_MANAGER *root, int skbn)        /* 戻り値はvoid ではないか*/
{
	BOOK_MANAGER *temp = root->next;
	BOOK work;      /* 退避用*/
	
	BOOK_MANAGER *room;

	int nextBookCode; /* 合算したコード */
	int tempBookCode;

	
	/* 基準ループ*/
	if(skbn == 1)
	{
		while(temp != NULL)
		{	
			room=temp->next;
			
			/* 整列ループ*/
			while(room != NULL)
			{
				nextBookCode = room->bookData.bookKbn*100000 + room->bookData.bookCode;
				tempBookCode = temp->bookData.bookKbn*100000 + temp->bookData.bookCode;

				
				if(nextBookCode < tempBookCode)
				{
					work                 = temp->bookData;
					temp->bookData       =room->bookData;
					room->bookData = work;
				}
				
				room=room->next;/* 基準ノードと比較するノードを一つ進める*/
				
			}
			
			temp = temp->next; /* 整列の基準となるノードを一つ進める*/
			
		}
	}

	if(skbn == 2)
	{
		while(temp != NULL)
		{	
			room=temp->next;
			
			/* 整列ループ*/
			while(room != NULL)
			{
				nextBookCode = room->bookData.bookKbn*100000 + room->bookData.bookCode;
				tempBookCode = temp->bookData.bookKbn*100000 + temp->bookData.bookCode;

				
				if(nextBookCode > tempBookCode)
				{
					work                 = temp->bookData;
					temp->bookData       =room->bookData;
					room->bookData = work;
				}
				
				room=room->next;/* 基準ノードと比較するノードを一つ進める*/
				
			}
			
			temp = temp->next; /* 整列の基準となるノードを一つ進める*/
			
		}
	}
}


/*
 * 名称		: 図書データ表示処理
 * 処理		: ソートされた図書データの図書情報を全て表示する
 * 呼出形式	: void display(BOOK_MANAGER *root)
 * 引数		: root	図書データ（リスト構造）の先頭ノードへのポインタ
 * 戻り値	: non
 */
void sortDisp(BOOK_MANAGER *root)
{
	BOOK_MANAGER* temp = root->next; /* 処理対象ノード */

	/* 図書データヘッダー表示 */
	printBookHead();

	/* ライン表示 */
	printLine();

	/* 図書データ表示 */
	while(temp != NULL)
	{
		printBookData(temp->bookData);
		temp = temp->next; /* 整列の基準となるノードを一つ進める*/
	}

}



/*
 * 名称		: 区分別貸出状況表示
 * 処理		: 図書区分ごとの貸出状況表示を行う
 * 呼出形式	: void rentalDisp(BOOK_MANAGER *root)
 * 引数		: root	図書データ（リスト構造）の先頭ノードへのポインタ
 * 戻り値	: non
 */
void rentalDisp(BOOK_MANAGER *root)
{

	BOOK_MANAGER *temp = root->next;	/* 処理対象ノード */
	int ztotal = 0;				/* 在庫総合計 */
	int rentOKcnt = 0;			/* 貸出可総合計	*/
	int rentNGcnt = 0;			/* 貸出中総合計 */
	int k_rentOKcnt = 0;		/* 貸出可区分合計 */
	int k_rentNGcnt = 0;		/* 貸出中総合計 */
	int svkbn;					/* 処理中区分 */

	svkbn = temp->bookData.bookKbn; /* 最初の区分を保持 */

	/* ガイドメッセージ表示 */
	printf("\n区分ごとの貸出可・貸出中合計一覧\n");

	/* ライン表示 */
	printLine();

	/* 区分ごとの貸出可、貸出中の本の数を計算する */
	// while(temp->next != NULL){
	while(1){
		// printf("svkbn: %02d\n", svkbn);
		ztotal++;
		if(temp->bookData.isRent == 1){
			rentOKcnt++; /* 貸出可総合計に 1加える	*/
			k_rentOKcnt++; /* 区分別貸出可総合計に 1加える */
		}
		else {
			rentNGcnt++; /* 貸出中総合計に 1加える */
			k_rentNGcnt++; /* 区分別貸出中総合計に 1加える */
		}
		/* 次のノードが存在する場合 */
		if(temp->next == NULL) {
			printf("区分 %02d の貸出可の冊数合計は：%d\n", temp->bookData.bookKbn, k_rentOKcnt);
			printf("区分 %02d の貸出中の冊数合計は：%d\n", temp->bookData.bookKbn, k_rentNGcnt);
			break;
		}
		/* 最後のノードの場合 */
		if(temp->next != NULL && svkbn != temp->next->bookData.bookKbn){
			printf("区分 %02d の貸出可の冊数合計は：%d\n", temp->bookData.bookKbn, k_rentOKcnt);
			printf("区分 %02d の貸出中の冊数合計は：%d\n", temp->bookData.bookKbn, k_rentNGcnt);

			svkbn = temp->bookData.bookKbn;

			/* 区分ごとの合計値をリセット */
			k_rentOKcnt = 0;
			k_rentNGcnt = 0;
		}
		temp = temp->next;/* ノードを進める */

	}
	/* ライン表示 */
	printLine();

	/* ガイドメッセージ表示 */
	printf("\n貸出中・貸出可の冊数合計一覧\n");

	/* ライン表示 */
	printLine();

	/* 図書データ全体の貸出可、貸出中の本の数を表示する */
	printf("貸出可の冊数合計は：%d\n", rentOKcnt);
	printf("貸出中の冊数合計は：%d\n", rentNGcnt);
	printf("在庫の総合計は %d\n", ztotal);

	/* ライン表示 */
	printLine();
	printf("\n");
}
