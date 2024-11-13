#include<stdio.h>
#include<string.h>


char op[2],arg1[5],arg2[5],result[5];

void main() {
    FILE *fp1, *fp2;
    fp1 = fopen("input.txt","r");
    fp2 = fopen("output.txt","w");
    
    
    while(!feof(fp1)) {
        fscanf(fp1,"%s%s%s%s", op,arg1,arg2,result);
        if(strcmp(op,"+")== 0)
    }
}