tmux-set-buffer-remote
======================

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
