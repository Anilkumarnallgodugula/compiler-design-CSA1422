%%
/* Define the states */
INITIAL  

/* Regular Expressions for HTML Tags */
"<" [a-zA-Z0-9]+  	    { printf("<%s>\n", yytext+1); }
"</" [a-zA-Z0-9]+ ">	    { printf("</%s>\n", yytext+2); } 

/* Ignore whitespace and other non-tag characters */
[ \t\n]                  ; 

/* Error handling for unexpected characters */
.                       { printf("Invalid character: %s\n", yytext); }

%%