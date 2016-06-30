tmux-set-buffer-remote
======================
reads text from stdin and set the tmux's paste-buffer on a remote machine over ssh.

usage examples
--------------

    dmesg | tmux-set-buffer-remote mako@remotehost
    echo "hello, world" | tmux-set-buffer-remote mako@remotehost

compiling
---------

### dependencies
`tmux-set-buffer-remote` depends on:
- `libssh-dev` which can be installed on debian systems with `apt-get`.
- `clang` to compile but it should work with gcc (has not been tested)

### compile command
run `make` in the root of the project.

todo
----
[ ] add host verification.
currently, the program is not checking if the server is safe to be used.
Should use `ssh_is_server_known()` to check that.
https://www.libssh.org/documentation/

[ ] Document set-buffer length limit in the code
There is a hard limit on command length for tmux.
This is observeable on: https://github.com/tmux/tmux/issues/254
For tmux 1.8, this is really small: 2028
For tmux 1.9, this is a bit better: 16344
I could probably add a warning/error check on the tmux version and
log whenever the buffer is bigger than the command length
