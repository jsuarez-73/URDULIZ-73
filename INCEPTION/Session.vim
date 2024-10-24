let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/URDULIZ-73/INCEPTION
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +27 ~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/Dockerfile
badd +2 ~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/default.conf
badd +3 ~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/nginx_signing.rsa.pub
badd +14 ~/URDULIZ-73/INCEPTION/srcs/docker-compose.yml
badd +5 ~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/conf/default.conf
badd +9 ~/URDULIZ-73/INCEPTION/srcs/.env
argglobal
%argdel
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit ~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/conf/default.conf
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
wincmd _ | wincmd |
vsplit
2wincmd h
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 79 + 119) / 238)
exe 'vert 2resize ' . ((&columns * 79 + 119) / 238)
exe 'vert 3resize ' . ((&columns * 78 + 119) / 238)
argglobal
balt ~/URDULIZ-73/INCEPTION/srcs/docker-compose.yml
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 6 - ((5 * winheight(0) + 28) / 57)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 6
normal! 030|
wincmd w
argglobal
if bufexists(fnamemodify("~/URDULIZ-73/INCEPTION/srcs/docker-compose.yml", ":p")) | buffer ~/URDULIZ-73/INCEPTION/srcs/docker-compose.yml | else | edit ~/URDULIZ-73/INCEPTION/srcs/docker-compose.yml | endif
if &buftype ==# 'terminal'
  silent file ~/URDULIZ-73/INCEPTION/srcs/docker-compose.yml
endif
balt ~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/conf/default.conf
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 10 - ((9 * winheight(0) + 28) / 57)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 10
normal! 015|
wincmd w
argglobal
if bufexists(fnamemodify("~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/Dockerfile", ":p")) | buffer ~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/Dockerfile | else | edit ~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/Dockerfile | endif
if &buftype ==# 'terminal'
  silent file ~/URDULIZ-73/INCEPTION/srcs/requirements/nginx/Dockerfile
endif
balt ~/URDULIZ-73/INCEPTION/srcs/docker-compose.yml
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 27 - ((26 * winheight(0) + 28) / 57)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 27
normal! 046|
wincmd w
3wincmd w
exe 'vert 1resize ' . ((&columns * 79 + 119) / 238)
exe 'vert 2resize ' . ((&columns * 79 + 119) / 238)
exe 'vert 3resize ' . ((&columns * 78 + 119) / 238)
tabnext
edit ~/URDULIZ-73/INCEPTION/srcs/.env
argglobal
balt ~/URDULIZ-73/INCEPTION/srcs/docker-compose.yml
setlocal fdm=manual
setlocal fde=0
setlocal fmr={{{,}}}
setlocal fdi=#
setlocal fdl=0
setlocal fml=1
setlocal fdn=20
setlocal fen
silent! normal! zE
let &fdl = &fdl
let s:l = 11 - ((10 * winheight(0) + 28) / 57)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 11
normal! 021|
tabnext 1
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
