<command> ::= <ls_command> | <cd_command> | <cat_command> | <print_command> | <exec_command>

<ls_command> ::= "ls" [<folder_name>]
<cd_command> ::= "cd" [<folder_path>]
<cat_command> ::= "cat" <filename>
<print_command> ::= "print" <filename>
<exec_command> ::= "exec" <filename>

<filename> ::= <name> "." <extension>
<name> ::= <letter> {<letter>}    (* up to 8 letters *)
<extension> ::= <letter> {<letter>}   (* exactly 3 letters *)
<folder_name> ::= <name>
<folder_path> ::= "\" | "\" <folder_name> {"\" <folder_name>}

<letter> ::= "A" | "B" | ... | "Z" | "a" | "b" | ... | "z"
