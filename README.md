Advent of code 2022
===================

My solutions to [Advent of code 2022](https://adventofcode.com/2022/)

To compile a file run:

```sh
make bin/day1.out
```

Program expects input on `stdin`:

```sh
bin/day1.out < input/day1.txt
```

## Project local config

A local `.nvimrc` is included in this repo, with some helper config, enabled by setting
```vim
" allows loading local executing local rc files.
set exrc

" secure disallows the use of :autocmd, shell and write commands in local
" .vimrc files
set secure
```
### makeprg
```vim
" use expand() to strip basename and extension when compiling with make
" See :help filename-modifiers
set makeprg=make\ bin/%:t:r.out
```

This will ensure that the `:make` command compiles the current buffer. Basename
and extension is removed so that `src/1-3.c` becomes `bin/1-3.out`


### Exec command

This command executes the compiled file and reads its output to a new vsplit.
```vim
command! Exec set splitright | vnew | read ! bin/#<.out
```
### F5 mapping

This binding quietly executes a compiled file in the `bin` folder
```vim
map <F5> :! bin/%<.out<cr>


