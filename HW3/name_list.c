#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "basic.h"
int cmp(const void *a1, const void *a2)
{
    const struct polynomial *tmp1 = a1;
    const struct polynomial *tmp2 = a2;
    return tmp1->exp < tmp2->exp;
}
void poly_sort(struct polynomial p[],int poly_len){
    // for(int i=0;i<poly_len;i++){
    //     printf("coeff = %d , exp = %d\n",p[i].coef, p[i].exp);
    // }
    qsort(p,poly_len,sizeof(p[0]),cmp);
}
int print_poly(struct polynomial p[],int poly_len){
    int deter=0;
    for(int i=0;i<poly_len;i++){
        if(p[i].coef==0) continue;
        if(deter!=0){
            if(p[i].exp==0){ // 常數項
                if(p[i].coef>0) printf("+%d",p[i].coef);
                else printf("%d",p[i].coef);
            }
            else if(p[i].exp==1){ // 一次方項
                if(p[i].coef==1) printf("+x");
                else if(p[i].coef>0) printf("+%dx",p[i].coef);
                else if(p[i].coef==-1) printf("-x");
                else printf("%dx",p[i].coef);
            }
            else{ // 其他項
                if(p[i].coef==1) printf("+x^%d",p[i].exp);
                else if(p[i].coef>0) printf("+%dx^%d",p[i].coef,p[i].exp);
                else if(p[i].coef==-1) printf("-x^%d",p[i].exp);
                else printf("%dx^%d",p[i].coef,p[i].exp);
            }
        }
        else{
            if(p[i].exp==0){ // 常數項
                if(p[i].coef>0) printf("%d",p[i].coef);
                else printf("%d",p[i].coef);
            }
            else if(p[i].exp==1){ // 一次方項
                if(p[i].coef==1) printf("x");
                else if(p[i].coef>0) printf("%dx",p[i].coef);
                else if(p[i].coef==-1) printf("-x");
                else printf("%dx",p[i].coef);
            }
            else{ // 其他項
                if(p[i].coef==1) printf("x^%d",p[i].exp);
                else if(p[i].coef>0) printf("%dx^%d",p[i].coef,p[i].exp);
                else if(p[i].coef==-1) printf("-x^%d",p[i].exp);
                else printf("%dx^%d",p[i].coef,p[i].exp);
            }
            deter=1;
        }
    }
    return deter;
}
bool enter_poly_name(char tmp_poly_name, int tmp_poly_id, int flag_of_Poly){
    // printf("%c %d %d\n",tmp_poly_name, tmp_poly_id, flag_of_Poly);
    if(tmp_poly_id>flag_of_Poly || tmp_poly_name!='P' ||  tmp_poly_id<=0){
        printf(RED_BOLD);
        printf("Error input. Found no id or the polynominal name was not big letter 'P'. ");
        printf("For example, use the form of \"P2\" or \"p2\".\n");
        printf(RESET);
        return false;
    }
    return true;
}
/*
int query_poly_id(char arr[], int fod){
    struct name_info *result, key = {arr};
    // printf("%ld %ld\n",sizeof(dict[0]),sizeof(dict));
    printf("fod= %d\n",fod);
    if(fod<=0) return -1;
    result = bsearch(&key, dict, sizeof(dict)/sizeof(dict[0]), sizeof dict[0], cmp);
    if(result) printf("result: %d\n",result->n);
    if (!result) return -1;
    return result->n;
}
bool add_poly_name(char str[]){
    int qpi=query_poly_id(str, flag_of_dict);
    printf("qpi= %d\n %s\n",qpi,dict[qpi].str);
    if(qpi!=-1){
        if(!strcmp(dict[qpi].str,str)){
            printf(RED_BOLD), printf("The name was repeated. Please choose another name.\n"), printf(RESET);
            return false;
        }
    }
    dict[flag_of_dict].str=str;
    dict[flag_of_dict].n=flag_of_dict;
    flag_of_dict++;
    printf("%s %d",dict[flag_of_dict-1].str, dict[flag_of_dict-1].n);
    return true;
}*/
