%{
#include <stdio.h>

int vowel_count = 0;
int consonant_count = 0;
%}

%%
[AEIOUaeiou]   { vowel_count++; }        // Match any vowel (case-insensitive)
[a-zA-Z]       { consonant_count++; }    // Match any letter (increment consonant_count if not a vowel)
[^a-zA-Z]      ;                         // Ignore non-alphabet characters
%%

int main() {
    yylex();  // Start lexical analysis
    printf("Number of vowels: %d\n", vowel_count);
    printf("Number of consonants: %d\n", consonant_count);
    return 0;
}

int yywrap() {
    return 1;
}
