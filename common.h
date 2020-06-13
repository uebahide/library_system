#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tagBook {
	int bookKbn;			/* �}���敪 */
	int bookCode;			/* �}���R�[�h */
	int dummy1;
	int dummy2;
	char title[64];			/* ���� */
	char author[32];		/* ���� */
	int isRent;				/* �݂��o���� */
	int dummy3[3];
} BOOK;

typedef struct tagBookManager {
	BOOK bookData;					/* �}���f�[�^ */
	struct tagBookManager *next;	/* ���̃m�[�h�ւ̃|�C���^ */
} BOOK_MANAGER;

/* ----------------------------------------- */
/* �ݏo�ԋp���Ǎ��ݍ\���̒�` */
typedef struct tagRentDat {
	int kbn;			/* �敪2�� */
	int code;			/* �R�[�h5�� */
} RENTDAT;

/* �ݏo�ԋp���\���̒�` */
typedef struct tagRent {
	int sumCode;			/* �}���敪2��+�R�[�h5�� */
} RENT;

/* �ݏo�ԋp���Ǘ��\���̒�` */
typedef struct tagRentManager {
	RENT rentData;					/* �}���f�[�^ */
	struct tagRentManager *next;	/* ���̃m�[�h�ւ̃|�C���^ */
} RENT_MANAGER;

/* ----------------------------------------- */


/*�v���g�^�C�v�錾*/
/*main.c*/
int endCheck(BOOK_MANAGER *root);
int outPutData(BOOK_MANAGER *root);

/*search.c*/
int LSearch(BOOK_MANAGER *root);                                 /* �}���f�[�^�������j���[*/
void inputBookCode(BOOK_MANAGER *root);                          /* �}���R�[�h�Ō������Y���f�[�^��\�� searchBook���g��*/                                   /* ������*/
BOOK_MANAGER *searchBook(BOOK_MANAGER *root, int bookCode);      /* �}���f�[�^�ƃR�[�h���r���A��v����f�[�^�ւ̃|�C���^��Ԃ�*/                          /* ������*/
void inputAuthor(BOOK_MANAGER *root);                            /* ��������͂��A����𒘎Җ��Ɋ܂ސ}���f�[�^��S�ĕ\�� searchAuthor���g��*/               /* ������*/
void searchAuthor(BOOK_MANAGER *root, char authorCode[64]);

/*common.c*/
void clear_screen();
int numelicCheck(char inpdata[],int inpLength);
void printLine();                                                /* ���C���\��*/                                                                            /* ������*/
void printBookHead();                                            /* �u�b�N�w�b�_�[��\��*/                                                                  /* ������*/
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
