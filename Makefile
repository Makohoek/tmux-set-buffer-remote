CC=clang
CFLAGS=-Wall
LDLIBS=-lssh

all:
	${CC} ${CFLAGS} ssh.c linked_list.c tmux-set-buffer-remote.c ${LDLIBS} -o tmux-set-buffer-remote
test:
	${CC} ${CFLAGS} linked_list.c test_linked_list.c -o test_linked_list
	./test_linked_list
checkpatch:
	git diff -U0 HEAD^ | clang-format-diff-3.6 -style Chromium -i -p1
format-all:
	clang-format-3.6 -i -style=Chromium *.[hc]
