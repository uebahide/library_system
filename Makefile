# マクロ定義
CC		= gcc
SJIS	= -finput-charset=cp932 -fexec-charset=cp932

# Liblaly 生成関連情報
#         ソースファイルを変更、追加したときは以下を修正
OBJS	= main.o \
		common.o \
		search.o \
		booklist.o \
		display.o \
		rentret.o \
		rireki.o \
		end.o
TARGET	= Library

# コンパイル指定
$(TARGET):	$(OBJS)
			$(CC) $(SJIS) $? -o $@
# 依存関係
.c.o:
	$(CC) $(SJIS) -c $<

# オブジェクトファイルの削除
clean:
	del *.o

# ソースファイルの依存関係
#         ソースファイルを変更、追加したときは以下を修正
main.o    : main.c     common.h
common.o  : common.c   common.h
search.o  : search.c   common.h
booklist.o : booklist.c  common.h
display.o : display.c  common.h
rentret.o : rentret.c common.h
end.o     : end.c     common.h
rireki.o : rireki.c common.h  