all:
	clang -Wall -lssh ssh.c linked_list.c tmux-set-buffer-remote.c -o tmux-set-buffer-remote
test:
	clang -Wall linked_list.c test_linked_list.c -o test_linked_list
	./test_linked_list
