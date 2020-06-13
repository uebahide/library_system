/*
 *  IC�}���كV�X�e��
 */
#include "common.h"

RENT_MANAGER* initRentRetList(void);
int createRentData(RENT_MANAGER *root, const char *fileName);
int registRent(RENT_MANAGER *root, const RENT *newData);
void clearRentData(RENT_MANAGER *root);
int outPutRireki(BOOK_MANAGER *temp);


/*
 * ����		: �ݏo�ԋp���j���[�\��
 * ����		: �}���f�[�^�̑ݏo�ԋp���j���[��\�����āA
 *            �ݏo�A�ԋp��I�����A�I���������������s����
 * �ďo�`��	: int LRentRet(BOOK_MANAGER *root)
 * ����     : root		�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 */
int LRentRet(BOOK_MANAGER *root)
{
	int skbn3; /* switch���̏������ɗ��p�AnumelicCheck()�̕Ԃ�l���i�[ */
	int ret_num3; /* �e�֐��̕Ԃ�l���i�[���� */
	char menu_num[256];	// ���̓f�[�^���i�[����

	while (1) {
		/* ���j���[�\�� */
		printf("\n*** �}���ݏo�ԋp���j���[ ***\n");
		printf(" 1�F�ݏo\n");
		printf(" 2�F�ԋp\n");
		printf(" 9�F�I��\n");

		/* ���j���[�ԍ������ */
		printf("���j���[�ԍ�:");
		scanf("%s", menu_num);

		/* ���͒l�`�F�b�N */ /* �Ԃ�l��int�^�ɂȂ� */
		skbn3 = numelicCheck(menu_num, 1); // common.c

		/* �ݏo�ԋp���� */
		switch (skbn3) {
			case 1:
				/* �ݏo�������s�� */
				rentBook(root, 0);
				break;
			case 2:
				/* �ԋp�������s�� */
				rentBook(root, 1);
				break;
			case 9:
				system("cls");
				break;

			case -1:
				break;

			default:
				printf("(Error)���������l����͂��Ă��������B\n");
				break;
		}
		if(skbn3 == 9) break; /* debug�p:9����͂�����I�� */
	}

	return 0;
}

/*
 * ����		: �ݏo�ԋp����
 * ����		: �}���݂��o���E�ԋp�������s��
 * �ďo�`��	: int rentBook(BOOK_MANAGER *root,int kbn)
 * ����		: root	�}���f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃|�C���^
 *			  kbn	0�F�ݏo�@1�F�ԋp
 * �߂�l	: ��������0, �G���[����1
 */
int rentBook(BOOK_MANAGER *root, int kbn)
{
	FILE *fp = NULL;		/* �t�@�C���|�C���^ */
	BOOK_MANAGER *temp = root->next; /* �����Ώۃm�[�h */
	RENT_MANAGER* rentRetRoot = NULL;
	RENT_MANAGER* rentRetTemp;
	int tempBookCode;
	int ret = 0;
	char fileName_rr[64]; /* �t�@�C�����i�[�p�̕ϐ� */

	/* �ݏoor�ԋp�̃t�@�C�������擾 */
	if(kbn == 0){
		strcpy(fileName_rr, "Ret.bin");
	}
	else if(kbn == 1){
		strcpy(fileName_rr, "Rent.bin");
	}
	else printf("Error\n"); /* debug : ���݂��� */

	/* �t�@�C�����J���邩�ǂ����̊m�F */
	if((fp = fopen(fileName_rr, "rb")) == NULL){
		printf("�t�@�C�����I�[�v���ł��܂���");
		return 1; /* ErrorCode 1:���s */
	}

	/* �ݏo�ԋp�f�[�^�\�z */
	rentRetRoot = initRentRetList();
	createRentData(rentRetRoot, fileName_rr);

	/* �����^���f�[�^�����Ƃɐ}���f�[�^�̑ݏo����ύX���� */
	while(temp != NULL)
	{
		tempBookCode = temp->bookData.bookKbn*100000 + temp->bookData.bookCode;
		rentRetTemp = rentRetRoot->next;
		while (rentRetTemp != NULL) {
			if(rentRetTemp->rentData.sumCode == tempBookCode)
			{
				/* ���łɑݏo���ɑݏo���� or ���łɕԋp���ɕԋp���� */
				if(kbn != temp->bookData.isRent){
					if(kbn == 0) {
						printf("�}���R�[�h�F%07d | �^�C�g���F %s �͊��ɑݏo���ł��B\n", tempBookCode, temp->bookData.title);
					}
					else {
						printf("�}���R�[�h�F%07d | �^�C�g���F %s �͊��ɕԋp�ςł��B\n", tempBookCode, temp->bookData.title);
					}
				}
				if(kbn == 0){
					/* �ݏo����ݏo�i�ԋp�j�ɂ��� */
					temp->bookData.isRent = 1;
					break;
				} else if (kbn == 1){
					/* �ݏo����ݏo���ɂ��� */
					temp->bookData.isRent = 0;
					outPutRireki(temp);
					break;
				}
			}
			rentRetTemp = rentRetTemp->next;
		}

		temp = temp->next; /* ��ƂȂ�m�[�h����i�߂�*/

	}

	if(kbn == 0){
		printf("\n�ݏo�s�\�ɕύX���܂����B");
	}
	else if(kbn == 1){
		printf("\n�ݏo�\�ɕύX���܂����B");
	}
	else {
		printf("Error");
	}

	/* �ݏo�ԋp�f�[�^�p�������J�� */
	clearRentData(rentRetRoot);

	printf("\n");

	return ret;
}

/*
 * ����		: �ݏo�ԋp�f�[�^����������
 * ����		: �ݏo�A�����́A�ԋp�t�@�C������A�����^���f�[�^��ǂݍ��ނ��߂́A
 *            �ݏo�ԋp�f�[�^�i���X�g�\���j�̐擪�m�[�h���쐬���A������������
 * �ďo�`��	: RENT_MANAGER* initRentRetList(void)
 * ����		: non
 * �߂�l	: rDummy �_�~�[�m�[�h�̃A�h���X
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
 * ����		: �ݏo�ԋp�f�[�^�\�z����
 * ����		: �ݏo�A�����́A�ԋp�t�@�C������A�����^���f�[�^��ǂݍ��݁A
 *            �ݏo�ԋp�f�[�^�i���X�g�\���j�ɓo�^���A�ݏo�ԋp�f�[�^���\�z����
 * �ďo�`��	: int createRentData(RENT_MANAGER *root, char *fileName)
 * ����		: root		�ݏo�ԋp�f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃_�u���|�C���^
 *			  fileName	�ݏo�i�ԋp�j�f�[�^���̓t�@�C�����iRent.bin or Ret.bin�j
 * �߂�l	: ��������0, �G���[����1
 */
int createRentData(RENT_MANAGER *rentRetRoot, const char *fileName)
{
	FILE *fp = NULL;		/* �t�@�C���|�C���^ */
	int ret = 1;			/* �߂�l */
	RENT newData;			/* 1�����̐}���f�[�^�i�敪+�R�[�h�j */
	RENTDAT newRentData;	/* 1�����̐}���f�[�^(�敪�A�R�[�h�j*/

	int kbn = 0;
	int code = 0;

	/* �t�@�C�����J�����ꍇ */
	if ((fp = fopen(fileName, "rb")) != NULL) {
		/* 1���������^���f�[�^��ǂݍ��� */
		while (fread(&newRentData, sizeof(RENTDAT), 1, fp) != 0) {
			/* �f�[�^�\���ɓo�^����*/
			newData.sumCode = ( newRentData.kbn * 100000 ) + newRentData.code;
			registRent(rentRetRoot, &newData);
		}
		fclose(fp);		/* �t�@�C���N���[�Y */
		ret = 0;		/* �������� */
	}
	return ret;
}

/*
 * ����		: �����^���f�[�^�o�^����
 * ����		: �݂��o��/�ԋp�f�[�^��1���A�ݏo�ԋp�f�[�^�i���X�g�\���j�ɒǉ�����
 * �ďo�`��	: int registRent(RENT_MANAGER *root, RENT *newData)
 * ����		: root		�ݏo�ԋp�f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃_�u���|�C���^
 *			  newData	�ǉ��Ώۂ̐}���f�[�^�ւ̃|�C���^
 * �߂�l	: ��������0, �G���[����1
 */
int registRent(RENT_MANAGER *rentRetRoot, const RENT *newData)
{
	int ret = 1;				/* �߂�l�p�ϐ� */
	RENT_MANAGER *temp = rentRetRoot;	/* �ǉ��ꏊ�Q�Ɨp */
	RENT_MANAGER *newNode;

	newNode = (RENT_MANAGER *)malloc(sizeof(RENT_MANAGER));	/* �V�K�m�[�h�p�ϐ� */

	/* �V�K�m�[�h�̐��� */
	if (newNode != NULL) {
		newNode->rentData = *newData;	/* �f�[�^�̐ݒ� */
		newNode->next = rentRetRoot->next;
		rentRetRoot->next = newNode;
		ret = 0;						/* �߂�l�̐ݒ� */
	}

	return ret;
}

/*
 * ����		: �����^���f�[�^�p���������
 * ����		: �ݏo�ԋp�f�[�^�i���X�g�\���j�Ŏg�p�������I���������������
 * �ďo�`��	: void clearRentData(RENT_MANAGER *root)
 * ����		: root		�ݏo�ԋp�f�[�^�i���X�g�\���j�̐擪�m�[�h�ւ̃_�u���|�C���^
 * �߂�l	: non
 */
void clearRentData(RENT_MANAGER *root)
{
	RENT_MANAGER *current = root;
	RENT_MANAGER *next = NULL;

	while (current != NULL) {
		next = current->next;

		/* ���I�������̉�� */
		free(current);
		current = next;
	}
}

/*
 * ����		: �ݏo�����o�͏���
 * ����		: �ݏo�������O���t�@�C���irireki.bin�j�ɏo�͂���
 * �ďo�`��	: int outPutRireki(BOOK_MANAGER *temp)
 * ����		: temp		�ݏo�f�[�^�i���X�g�\���j�̃m�[�h�ւ̃_�u���|�C���^
 * �߂�l	: non
 */
int outPutRireki(BOOK_MANAGER *temp)
{
	char fileName[128] = "rireki.bin";		/* �}�����̓��̓f�[�^ */
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
