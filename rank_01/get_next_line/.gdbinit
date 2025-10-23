 set auto-load local-gdbinit

 break get_next_line
 display {get_next_line::ptr,  get_next_line::buf, get_next_line::nl}
