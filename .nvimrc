" use expand() to strip basename and extension when building with make
" See :help filename-modifiers
set makeprg=make\ bin/%:t:r

" Helper used when executing compiled c programs outputted to bin/[target] and
" outputted to new vertical buffer.
command! Exec set splitbelow | new | read ! bin/#:t:r

" Helper mapping for running compiled c programs that are outputted to
" bin/[target]
map <F5> :! bin/%:t:r<cr>
