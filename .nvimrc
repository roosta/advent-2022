" use expand() to strip basename and extension when building with make
" See :help filename-modifiers
set makeprg=make\ bin/%:t:r.out

" Helper used when executing compiled c programs outputted to bin/*.out and
" outputted to new vertical buffer.
command! Exec set splitbelow | new | read ! bin/#:t:r.out

" Helper mapping for running compiled c programs that are outputted to
" bin/*.out
map <F5> :! bin/%:t:r.out<cr>
