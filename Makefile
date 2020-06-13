# �}�N����`
CC		= gcc
SJIS	= -finput-charset=cp932 -fexec-charset=cp932

# Liblaly �����֘A���
#         �\�[�X�t�@�C����ύX�A�ǉ������Ƃ��͈ȉ����C��
OBJS	= main.o \
		common.o \
		search.o \
		booklist.o \
		display.o \
		rentret.o \
		rireki.o \
		end.o
TARGET	= Library

# �R���p�C���w��
$(TARGET):	$(OBJS)
			$(CC) $(SJIS) $? -o $@
# �ˑ��֌W
.c.o:
	$(CC) $(SJIS) -c $<

# �I�u�W�F�N�g�t�@�C���̍폜
clean:
	del *.o

# �\�[�X�t�@�C���̈ˑ��֌W
#         �\�[�X�t�@�C����ύX�A�ǉ������Ƃ��͈ȉ����C��
main.o    : main.c     common.h
common.o  : common.c   common.h
search.o  : search.c   common.h
booklist.o : booklist.c  common.h
display.o : display.c  common.h
rentret.o : rentret.c common.h
end.o     : end.c     common.h
rireki.o : rireki.c common.h  