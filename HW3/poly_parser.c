#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "basic.h"

int poly_parser(char str[], struct polynomial p[]){
    struct item_info item={.po=1, .coeff=0, .deg_po=1, .deg=0};
    int str_len=strlen(str),flag=0,coeff_and_deg_key=0 /* 0: coeff , 1: deg */;
    for(int i=0;i<str_len;i++){
        // printf("i=%d , coeff_and_deg_key = %d , flag = %d\n",i,coeff_and_deg_key,flag);
        // printf("item-> po = %d , coeff = %d , deg_po = %d , deg = %d\n",item.po, item.coeff, item.deg_po, item.deg);
        if(coeff_and_deg_key==1 && (str[i]=='-' || str[i]=='+') && str[i-1]!='^'){
            if(coeff_and_deg_key==1 && item.deg==0) item.deg=1;
            p[flag++].exp=(item.deg*item.deg_po);
            item.deg=0;
            item.deg_po=1;
            if(str[i]=='-') item.po=-1;
            else if(str[i]=='+') item.po=1;
            coeff_and_deg_key=0;
        }
        else if(coeff_and_deg_key==1 && (str[i]=='-' || str[i]=='+') && str[i-1]=='^'){
            if(str[i]=='-') item.deg_po=-1;
            else if(str[i]=='+') item.deg_po=1;
        }
        if(coeff_and_deg_key==0 && (str[i]=='-' || str[i]=='+') && item.coeff!=0){ // 常數項
            if(str[i]=='-') item.po=-1;
            else if(str[i]=='+') item.po=1;
            p[flag].coef=(item.coeff*item.po), p[flag++].exp=0;
            item.coeff=0, item.po=1;
        }
        if(coeff_and_deg_key==0 && str[i]=='-') item.po=-1;
        else if(coeff_and_deg_key==0 && str[i]=='+') item.po=1;
        if(coeff_and_deg_key==0 && str[i]>='0' && str[i]<='9') item.coeff=item.coeff*10+(str[i]-'0');
        if(str[i]=='x'){
            if(item.coeff==0) item.coeff=1;
            p[flag].coef=(item.coeff*item.po);
            item.coeff=0;
            item.po=1;
            coeff_and_deg_key=1;
        }
        if(coeff_and_deg_key==1 && str[i]>='0' && str[i]<='9') item.deg=item.deg*10+(str[i]-'0');
    }
    if(coeff_and_deg_key==1 && item.deg==0) item.deg=1;
    if(coeff_and_deg_key==1) p[flag++].exp=(item.deg*item.deg_po);
    else if(coeff_and_deg_key==0) p[flag].coef=(item.coeff*item.po), p[flag++].exp=0;
    //return p;
    return flag;
}