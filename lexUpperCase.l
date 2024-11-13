%{
    #include <stdio.h>
%}

%%
[a-z] printf("%c",yytext[0] - 'a' + 'A');
. printf("%s",yytext);
%%

int main() {
   yylex();
    return 0; 
}

int yywrap() {
    return 1;
}