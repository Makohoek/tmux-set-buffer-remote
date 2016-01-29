#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "ssh.h"
#include "linked_list.h"

static int read_stdin(struct linked_list* stdin_list) {
  char stdin_buf[LIST_BUFSZ];
  int nb = 0;
  while ((nb = read(STDIN_FILENO, stdin_buf, LIST_BUFSZ)) > 0) {
    linked_list_add(stdin_list, stdin_buf);
    memset(stdin_buf, '\0', LIST_BUFSZ);
  }
  if (nb == -1) {
    perror("read");
  }
  return nb;
}

static int forge_tmux_command(const struct linked_list text, char** command) {
  static const char* const tmux_buffer_prefix = "tmux set-buffer \"";
  static const char* const set_buffer_postfix = "\"";

  // forge the tmux command
  size_t tmux_command_size =
      sizeof(char) * (strlen(tmux_buffer_prefix) + strlen(set_buffer_postfix)) +
      linked_list_data_size(text) + 1;

  *command = (char*)malloc(tmux_command_size);  // "tmux set-buffer ";
  if (command == NULL) {
    fprintf(stderr, "not enough memory for malloc()\n");
    return -1;
  }

  // add prefix
  *command = strcat(*command, tmux_buffer_prefix);

  // add text to copy
  linked_list_for_each(text, node)* command =
      strncat(*command, node->buf, LIST_BUFSZ);

  // add suffix
  *command = strcat(*command, set_buffer_postfix);
  return 0;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "%s: missing argument\n", argv[0]);
    fprintf(stderr, "usage: %s username@hostname\n", argv[0]);
    return -1;
  }

  // parse argv[1] for username@hostname string
  char* at_ptr = strchr(argv[1], '@');
  if (at_ptr == NULL) {
    fprintf(stderr, "%s: invalid argument\n", argv[0]);
    fprintf(stderr, "usage: %s username@hostname\n", argv[0]);
    return -1;
  }
  char* hostname = at_ptr + 1;  // set pointer to first char of hostname
  char* username = argv[1];
  at_ptr[0] = '\0';  // set username to begin of the argv[1] string

  int ret = 0;
  struct linked_list text;
  linked_list_init(&text);
  ret = read_stdin(&text);
  if (ret < 0)
    goto exit_main;

  char* tmux_command = NULL;
  ret = forge_tmux_command(text, &tmux_command);
  if (ret < 0)
    goto exit_main;

  printf("%s\n", tmux_command);

  // initiate ssh session
  if (new_ssh_session() != SSH_OK) {
    goto free_buffers;
  }
  if (connect_ssh_session(username, hostname) != SSH_OK) {
    goto free_ssh_session;
  }
  if (authenticate_ssh_session() != SSH_OK) {
    goto disconnect_ssh_session;
  }
  if (new_ssh_channel() != SSH_OK) {
    goto disconnect_ssh_session;
  }
  if (open_ssh_channel() != SSH_OK) {
    goto free_ssh_channel;
  }

  send_command_to_ssh_channel(tmux_command);
  send_channel_eof();

  close_channel();
free_ssh_channel:
  free_channel();
disconnect_ssh_session:
  disconnect_session();
free_ssh_session:
  free_session();
free_buffers:
  free(tmux_command);
  tmux_command = NULL;
exit_main:
  linked_list_free(&text);
  return ret;
}
