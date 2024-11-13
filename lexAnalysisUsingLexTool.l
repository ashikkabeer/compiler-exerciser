%{
    #include <stdio.h>
    #include <string.h>

    // Define keywords
    const char *keywords[] = {"int", "float", "return", "if", "else", "while", "for", "void"};
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    int isKeyword(const char *str) {
    for (int i = 0; i < numKeywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
    }
%}

%%

[ \t\n]+         ;// ignore all the whitespaces

"int"|"float"|"return"|"if"|"else"|"while"|"for"|"void" {
                        printf("kwd: %s\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
                        if (isKeyword(yytext)) {
                            printf("kwd: %s\n", yytext);
                        } else {
                            printf("id: %s\n", yytext);
                        }
}

"+"                 printf("op-plus\n");
"-"                 printf("op-sub\n");
"*"                 printf("op-mul\n");
"/"                 printf("op-div\n");

"="                 printf("op-=\n");
">"                 printf("op->\n");
"<"                 printf("op-<\n");
"!"                 printf("op-!\n");

.                   printf("same: %s\n", yytext);
%%

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);

    return 0;
}

int yywrap() {
    return 1;
}
