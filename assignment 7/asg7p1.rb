<command> ::= <set_command> | <echo_command> | <other_command>

<set_command> ::= "SET" <variable> "=" <string>
<echo_command> ::= "echo" <variable>
<other_command> ::= <command_name> <arg_list>

<variable> ::= "$" <identifier>
<identifier> ::= <letter> {<letter> | <digit>}
<letter> ::= "A" | "B" | ... | "Z" | "a" | "b" | ... | "z"
<digit> ::= "0" | "1" | ... | "9"
<string> ::= '"' {<any_character_except_double_quote>} '"'
<command_name> ::= <identifier>
<arg_list> ::= <arg> {<arg>}
<arg> ::= <string> | <variable> | <identifier>
