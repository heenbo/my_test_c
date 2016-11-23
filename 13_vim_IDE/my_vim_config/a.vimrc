" All system-wide defaults are set in $VIMRUNTIME/debian.vim and sourced by
" the call to :runtime you can find below.  If you wish to change any of those
" settings, you should do it in this file (/etc/vim/vimrc), since debian.vim
" will be overwritten everytime an upgrade of the vim packages is performed.
" It is recommended to make changes after sourcing debian.vim since it alters
" the value of the 'compatible' option.

" This line should not be removed as it ensures that various options are
" properly set to work with the Vim-related packages available in Debian.
runtime! debian.vim

" Uncomment the next line to make Vim more Vi-compatible
" NOTE: debian.vim sets 'nocompatible'.  Setting 'compatible' changes numerous
" options, so any other options should be set AFTER setting 'compatible'.
"set compatible

" Vim5 and later versions support syntax highlighting. Uncommenting the next
" line enables syntax highlighting by default.
if has("syntax")
  syntax on
endif

" If using a dark background within the editing area and syntax highlighting
" turn on this option as well
"set background=dark

" Uncomment the following to have Vim jump to the last position when
" reopening a file
"if has("autocmd")
"  au BufReadPost * if line("'\"") > 1 && line("'\"") <= line("$") | exe "normal! g'\"" | endif
"endif

" Uncomment the following to have Vim load indentation rules and plugins
" according to the detected filetype.
"if has("autocmd")
"  filetype plugin indent on
"endif

" The following are commented out as they cause vim to behave a lot
" differently from regular Vi. They are highly recommended though.
"set showcmd		" Show (partial) command in status line.
"set showmatch		" Show matching brackets.
"set ignorecase		" Do case insensitive matching
"set smartcase		" Do smart case matching
"set incsearch		" Incremental search
"set autowrite		" Automatically save before commands like :next and :make
"set hidden		" Hide buffers when they are abandoned
"set mouse=a		" Enable mouse usage (all modes)
"heenbo
if 1
"set nu
"set ruler 
set showcmd
"新建 c 文件自动加头文件__
autocmd BufNewFile *.c exec ":call SetTitle()"
func SetTitle()
	if &filetype == 'c'
		call setline(1, "/*************************************************************************") 
		call append(line("."),   " *   > File Name: ".expand("%")) 
		call append(line(".")+1, " *   > Author: heenbo") 
		call append(line(".")+2, " *   > Mail: 379667345@qq.com ") 
		call append(line(".")+3, " *   > Created Time:  ".strftime("%c")) 
		call append(line(".")+4, " *   > Modified Time: ".strftime("%c")) 
		call append(line(".")+5, " ************************************************************************/") 
		call append(line(".")+6, "")
	endif

	if &filetype == 'c'
		call append(line(".")+7, "#include <stdio.h>")
		call append(line(".")+8, "")
	endif
	autocmd BufNewFile * normal G
endfunc

"修改 c 自动更新最后的修改时间
autocmd BufWrite *.c exec ":call SetModifiedTime()"
func SetModifiedTime()
	if &filetype == 'c'
		let n=1
		while n < 7
			let line = getline(n)
			if line =~ '^\s\*\s\s\s>\sModified\sTime:'
				call setline(n, " *   > Modified Time: ".strftime("%c")) 
				return
			endif
			let n = n + 1
		endwhile
	endif
endfunc

"光标移动到buffer的顶部和底部时保持3行距离""
set scrolloff=3
"自动补全"
""set completeopt=preview,menu	
"允许插件"
""filetype plugin on
"当前行高亮"
"set cursorline
":highlight CursorLine cterm=NONE ctermbg=darkred ctermfg=white guibg=darkred guifg=white
":highlight CursorLine cterm=NONE ctermbg=grey ctermfg=black guibg=darkred guifg=white
":highlight CursorLine cterm=NONE ctermbg=NONE ctermfg=white guibg=darkred guifg=white
":highlight Comment cterm=underline ctermfg=red ctermbg=blue
":highlight Keyword term=reverse,bold
"当前列高亮"
"set cursorcolumn
"hi CursorColumn cterm=NONE ctermbg=darkred ctermfg=white guibg=darkred guifg=white
"autocmd InsertLeave * se nocul  " 用浅色高亮当前行  
"autocmd InsertEnter * se cul    " 用浅色高亮当前行
"自动缩进"
set autoindent
set cindent
" Tab键的宽度
set tabstop=4
" 统一缩进为8
set softtabstop=4
set shiftwidth=4
" 侦测文件类型
filetype on
" 载入文件类型插件
filetype plugin on
" 为特定文件类型载入相关缩进文件
""filetype indent on
" 可以在buffer的任何地方使用鼠标（类似office中在工作区双击鼠标定位）
"set mouse=a
"set selection=exclusive
"set selectmode=mouse,key
"set matchtime=1
"光标移动到buffer的顶部和底部时保持3行距离
set scrolloff=3
" 为C程序提供自动缩进
set smartindent
"自动补全 ctrl+N 或者 ctrl+P
:inoremap ( ()<ESC>i
:inoremap ) <c-r>=ClosePair(')')<CR>
:inoremap { {<CR>}<ESC>O
:inoremap } <c-r>=ClosePair('}')<CR>
:inoremap [ []<ESC>i
:inoremap ] <c-r>=ClosePair(']')<CR>
:inoremap " ""<ESC>i
:inoremap ' ''<ESC>i
function! ClosePair(char)
    if getline('.')[col('.') - 1] == a:char
        return "\<Right>"
    else
        return a:char
    endif
endfunction
filetype plugin indent on 
"打开文件类型检测, 加了这句才可以用智能补全
set completeopt=longest,menu


" Source a global configuration file if available
"if filereadable("/etc/vim/vimrc.local")
"  source /etc/vim/vimrc.local
"endif

endif
