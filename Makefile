all:
	clang -Wall -lssh ssh.c linked_list.c tmux-set-buffer-remote.c -o tmux-set-buffer-remote
test:
	clang -Wall linked_list.c test_linked_list.c -o test_linked_list
	./test_linked_list
checkpatch:
	git diff -U0 HEAD^ | clang-format-diff-3.6 -style Chromium -i -p1
format-all:
	clang-format-3.6 -i -style=Chromium *.[hc]
