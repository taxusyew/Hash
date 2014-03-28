function! QuickJump()
    let nxtchar = getline(".")
    if nxtchar == '"'
      
    end
endfunction

inormap <tab> <ESC>:call QuickJump()
