#include "ssh.h"

#define LIBSSH_STATIC 1
#include <libssh/libssh.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static ssh_session my_ssh_session;
static ssh_channel channel;

int new_ssh_session() {
  my_ssh_session = ssh_new();
  if (my_ssh_session == NULL) {
    fprintf(stderr, "Error creating ssh session\n");
    return SSH_ERROR;
  }
  return SSH_OK;
}

int connect_ssh_session(const char* user, const char* host) {
  ssh_options_set(my_ssh_session, SSH_OPTIONS_USER, user);
  ssh_options_set(my_ssh_session, SSH_OPTIONS_HOST, host);
  int ret = ssh_connect(my_ssh_session);
  if (ret != SSH_OK) {
    fprintf(stderr, "Error connecting to %s: %s\n", host,
            ssh_get_error(my_ssh_session));
  }
  return ret;
}

int authenticate_ssh_session() {
  int ret = ssh_userauth_publickey_auto(my_ssh_session, NULL, NULL);
  if (ret == SSH_AUTH_ERROR) {
    fprintf(stderr, "Authentication failed: %s\n",
            ssh_get_error(my_ssh_session));
  }
  return ret;
}

int new_ssh_channel() {
  channel = ssh_channel_new(my_ssh_session);
  if (channel == NULL) {
    fprintf(stderr, "Error creating ssh channel\n");
    return SSH_ERROR;
  }
  return SSH_OK;
}

int open_ssh_channel() {
  int ret = ssh_channel_open_session(channel);
  if (ret != SSH_OK) {
    fprintf(stderr, "Authentication failed: %s\n",
            ssh_get_error(my_ssh_session));
  }
  return ret;
}

int send_command_to_ssh_channel(char* command) {
  int ret = ssh_channel_request_exec(channel, command);
  if (ret != SSH_OK) {
    fprintf(stderr, "request channel exec: %s\n",
            ssh_get_error(my_ssh_session));
  }
  return ret;
}

void send_channel_eof() {
  ssh_channel_send_eof(channel);
}

void close_channel() {
  ssh_channel_close(channel);
}

void free_channel() {
  ssh_channel_free(channel);
}

void disconnect_session() {
  ssh_disconnect(my_ssh_session);
}

void free_session() {
  ssh_free(my_ssh_session);
}
