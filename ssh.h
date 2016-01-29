#ifndef TMUX_SSH_INCLUDED
#define TMUX_SSH_INCLUDED

#define LIBSSH_STATIC 1
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int new_ssh_session();
int connect_ssh_session(const char* user, const char* host);
int authenticate_ssh_session();
int new_ssh_channel();
int open_ssh_channel();
int send_command_to_ssh_channel(char* command);
void send_channel_eof();
void close_channel();
void free_channel();
void disconnect_session();
void free_session();

#endif
