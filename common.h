#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tagBook {
	int bookKbn;			/* 図書区分 */
	int bookCode;			/* 図書コード */
	int dummy1;
	int dummy2;
	char title[64];			/* 書名 */
	char author[32];		/* 著者 */
	int isRent;				/* 貸し出し状況 */
	int dummy3[3];
} BOOK;

typedef struct tagBookManager {
	BOOK bookData;					/* 図書データ */
	struct tagBookManager *next;	/* 次のノードへのポインタ */
} BOOK_MANAGER;

/* ----------------------------------------- */
/* 貸出返却情報読込み構造体定義 */
typedef struct tagRentDat {
	int kbn;			/* 区分2桁 */
	int code;			/* コード5桁 */
} RENTDAT;

/* 貸出返却情報構造体定義 */
typedef struct tagRent {
	int sumCode;			/* 図書区分2桁+コード5桁 */
} RENT;

/* 貸出返却情報管理構造体定義 */
typedef struct tagRentManager {
	RENT rentData;					/* 図書データ */
	struct tagRentManager *next;	/* 次のノードへのポインタ */
} RENT_MANAGER;

/* ----------------------------------------- */


/*プロトタイプ宣言*/
/*main.c*/
int endCheck(BOOK_MANAGER *root);
int outPutData(BOOK_MANAGER *root);

/*search.c*/
int LSearch(BOOK_MANAGER *root);                                 /* 図書データ検索メニュー*/
void inputBookCode(BOOK_MANAGER *root);                          /* 図書コードで検索し該当データを表示 searchBookを使う*/                                   /* 未完成*/
BOOK_MANAGER *searchBook(BOOK_MANAGER *root, int bookCode);      /* 図書データとコードを比較し、一致するデータへのポインタを返す*/                          /* 未完成*/
void inputAuthor(BOOK_MANAGER *root);                            /* 文字を入力し、それを著者名に含む図書データを全て表示 searchAuthorを使う*/               /* 未完成*/
void searchAuthor(BOOK_MANAGER *root, char authorCode[64]);

/*common.c*/
void clear_screen();
int numelicCheck(char inpdata[],int inpLength);
void printLine();                                                /* ライン表示*/                                                                            /* 未完成*/
void printBookHead();                                            /* ブックヘッダーを表示*/                                                                  /* 未完成*/
void printBookData(BOOK book);

/*listbook.c*/
BOOK_MANAGER* initBookList(void);
int createBookList(BOOK_MANAGER* root, const char* fileName);
int registBookList(BOOK_MANAGER* root, const BOOK* bookData);

/*display.c*/
int LDisp(BOOK_MANAGER *root);
void sortBook(BOOK_MANAGER *root, int skbn);
void sortDisp(BOOK_MANAGER *root);
void rentalDisp(BOOK_MANAGER *root);

/* rentret.c */
int LRentRet(BOOK_MANAGER *root);
int rentBook(BOOK_MANAGER *root,int kbn);

/* rireki.c*/
void LRireki(BOOK_MANAGER* root);
void printRireki(BOOK_MANAGER* rroot);
