#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<stdint.h>
#include<string.h>
#include<math.h>
#include<signal.h>
#include<stdio.h>
#include<stdbool.h>
#include<stdio.h>
#include<ctype.h>
#include "basic.h"
#include "name_list.h"
#include "print_menu.h"
#include "poly_parser.h"
struct polynomial Poly[105][10005],tmp_poly_ans[100005];
int length_of_poly[105];
int main(void) {
    bool deter_break = false;
    int flag_of_Poly=0;
    while(!deter_break){
        int choose_menu_num;
        while(1){
            print_menu();
            scanf("%d",&choose_menu_num);
            if(choose_menu_num<0 || choose_menu_num>9) printf(RED_BOLD), printf("Error option!\n"), printf(RESET);
            else break;
        }
        if(choose_menu_num==0){
            printf(GRN_BOLD), printf("Good Bye.\n"), printf(RESET);
            break; 
        }
        else if(choose_menu_num==1){
            printf(YEL_BOLD); 
            printf("Enter a polynomial of X (use the form of ax^b+cx^d+...+n).\n");
            printf(RESET); 
            while(1){
                char tmp[100005];
                scanf("%s",tmp);
                int Poly_len=poly_parser(tmp,Poly[flag_of_Poly]);
                length_of_poly[flag_of_Poly]=Poly_len;
                poly_sort(Poly[flag_of_Poly],Poly_len);
                printf("This polynomial name is P%d\n",flag_of_Poly+1);
                flag_of_Poly++;
                break;
                //if(add_poly_name(tmp)) break;
            }
        } 
        else if(choose_menu_num==2){
            printf(YEL_BOLD); 
            printf("The following(s) is/are your polynomial(s):\n");
            for(int i=0;i<flag_of_Poly;i++){
                printf("P%d: ",i+1);
                int is_zero=print_poly(Poly[i],length_of_poly[i]);
                if(!is_zero) printf("0");
                printf("\n");
            }
            printf(RESET);
        }
        else if(choose_menu_num==3){
            printf(YEL_BOLD); printf("Enter a degree, and show the coefficient.\n"); printf(RESET);
            int tmp_poly_id, tmp_poly_degree;
            char tmp_poly_name;
            while(1){
                printf("Enter polynominal name: ");
                scanf(" %c%d",&tmp_poly_name, &tmp_poly_id);
                // printf("%c %d %d\n",tmp_poly_name, tmp_poly_id, flag_of_Poly);
                if(tmp_poly_id>flag_of_Poly || tmp_poly_name!='P' ||  tmp_poly_id<=0){
                    printf(RED_BOLD);
                    printf("Error input. Found no id or the polynominal name was not big letter 'P'. ");
                    printf("For example, use the form of \"P2\" or \"p2\".\n");
                    printf(RESET);
                }
                else break;
            }
            printf("Enter the degree: ");
            scanf("%d",&tmp_poly_degree);
            tmp_poly_id--;
            bool deter_search_degree=false;
            for(int i=0;i<length_of_poly[tmp_poly_id];i++){
                if(Poly[tmp_poly_id][i].exp==tmp_poly_degree){
                    deter_search_degree=true;
                    printf(YEL_BOLD);
                    printf("The polynomial coefficient of P%d at degree %d is: %d\n",tmp_poly_id+1, tmp_poly_degree, Poly[tmp_poly_id][i].coef);
                    printf(RESET);
                    break;
                }
            }
            if(!deter_search_degree){
                printf(YEL_BOLD);
                printf("The polynomial coefficient of P%d at degree %d is: 0\n",tmp_poly_id+1, tmp_poly_degree);
                printf(RESET);
            }
        }
        else if(choose_menu_num==4){
            printf(YEL_BOLD); printf("New a non-zero item in the polynomail.\n"); printf(RESET);
            // template of enter poly name
            bool deter_name=false;
            int new_degree, new_coeff, tmp_poly_id;
            char tmp_poly_name;
            while(!deter_name){
                printf("Enter polynominal name: ");
                scanf(" %c%d",&tmp_poly_name, &tmp_poly_id);
                deter_name=enter_poly_name(tmp_poly_name,tmp_poly_id,flag_of_Poly);
            }
            tmp_poly_id--;
            //
            printf("Which item would you want to add. Please enter the degree: ");
            scanf("%d", &new_degree);
            printf("Enter the coefficient of the degree %d: ", new_degree);
            scanf("%d", &new_coeff);
            bool deter_search_degree=false,deter_search_coef=false;
            int repeated_pos;
            for(int i=0;i<length_of_poly[tmp_poly_id];i++){
                if(Poly[tmp_poly_id][i].exp==new_degree){
                    deter_search_degree=true;
                    printf(YEL_BOLD);
                    printf("There is the repeated degree in P%d, and the original item was changed.\n",tmp_poly_id+1);
                    printf(RESET);
                    repeated_pos=i;
                    break;
                }
            }
            if(deter_search_degree){
                Poly[tmp_poly_id][repeated_pos].coef=new_coeff;
                Poly[tmp_poly_id][repeated_pos].exp=new_degree;
            }
            else{
                for(int i=0;i<length_of_poly[tmp_poly_id];i++){
                    if(Poly[tmp_poly_id][i].coef==0){
                        deter_search_coef=true;
                        Poly[tmp_poly_id][i].coef=new_coeff;
                        Poly[tmp_poly_id][i].exp=new_degree;
                        break;
                    }
                }
                if(!deter_search_coef){
                    int len=length_of_poly[tmp_poly_id];
                    Poly[tmp_poly_id][len].coef=new_coeff;
                    Poly[tmp_poly_id][len++].exp=new_degree;
                    length_of_poly[tmp_poly_id]=len;
                }
                poly_sort(Poly[tmp_poly_id],length_of_poly[tmp_poly_id]);
            }
        }
        else if(choose_menu_num==5){
            printf(YEL_BOLD); printf("Remove a non-zero item in the polynomail.\n"); printf(RESET); 
            // template of enter poly name
            bool deter_name=false;
            int remove_degree, tmp_poly_id;
            char tmp_poly_name;
            while(!deter_name){
                printf("Enter polynominal name: ");
                scanf(" %c%d",&tmp_poly_name, &tmp_poly_id);
                deter_name=enter_poly_name(tmp_poly_name,tmp_poly_id,flag_of_Poly);
            }
            tmp_poly_id--;
            //
            printf("Which item would you want to remove. Please enter the degree: ");
            scanf("%d", &remove_degree);
            bool deter_search_degree=false;
            for(int i=0;i<length_of_poly[tmp_poly_id];i++){
                if(Poly[tmp_poly_id][i].exp==remove_degree){
                    deter_search_degree=true;
                    Poly[tmp_poly_id][i].coef=0;
                    break;
                }
            }
            if(!deter_search_degree) printf(YEL_BOLD), printf("No item to remove.\n"), printf(RESET);
            // for(int i=0;i<length_of_poly[tmp_poly_id];i++){
            //     printf("coeff = %d , exp = %d\n",Poly[tmp_poly_id][i].coef, Poly[tmp_poly_id][i].exp);
            // }
        }
        else if(choose_menu_num==6 || choose_menu_num==7){
            if(flag_of_Poly<2){
                printf(RED_BOLD);
                printf("There are not at least two polynominal.");
                printf(RESET);
                continue;
            }
            if(choose_menu_num==6) printf(YEL_BOLD), printf("Show the result of a polynomial plus a polynomial\n"), printf(RESET);
            else printf(YEL_BOLD), printf("Show the result of a polynomial minus a polynomial\n"), printf(RESET);
            // enter two name of poly template
            bool deter_name1=false,deter_name2=false;
            int tmp_poly_id1, tmp_poly_id2;
            char tmp_poly_name1, tmp_poly_name2;
            while(!deter_name1){
                printf("Enter polynominal1 name: ");
                scanf(" %c%d",&tmp_poly_name1, &tmp_poly_id1);
                deter_name1=enter_poly_name(tmp_poly_name1,tmp_poly_id1,flag_of_Poly);
            }
            tmp_poly_id1--;
            while(!deter_name2){
                printf("Enter polynominal2 name: ");
                scanf(" %c%d",&tmp_poly_name2, &tmp_poly_id2);
                deter_name2=enter_poly_name(tmp_poly_name2,tmp_poly_id2,flag_of_Poly);
            }
            tmp_poly_id2--;
            //
            for(int i=0;i<length_of_poly[tmp_poly_id1];i++) tmp_poly_ans[i]=Poly[tmp_poly_id1][i];
            // for(int i=0;i<length_of_poly[tmp_poly_id1];i++){
            //     printf("coeff = %d , exp = %d\n",tmp_poly_ans[i].coef, tmp_poly_ans[i].exp);
            // }
            int flag_of_poly_ans=length_of_poly[tmp_poly_id1];
            for(int i=0;i<length_of_poly[tmp_poly_id2];i++){
                bool deter_search_degree=false;
                int same_coef_pos;
                for(int j=0;j<length_of_poly[tmp_poly_id1];j++){
                    if(Poly[tmp_poly_id2][i].exp==Poly[tmp_poly_id1][j].exp){
                        deter_search_degree=true;
                        same_coef_pos=j;
                        break;
                    }
                }
                if(deter_search_degree && choose_menu_num==6) tmp_poly_ans[same_coef_pos].coef+=Poly[tmp_poly_id2][i].coef;
                else if(deter_search_degree && choose_menu_num==7) tmp_poly_ans[same_coef_pos].coef-=Poly[tmp_poly_id2][i].coef;
                else{
                    tmp_poly_ans[flag_of_poly_ans].exp=Poly[tmp_poly_id2][i].exp;
                    if(choose_menu_num==6) tmp_poly_ans[flag_of_poly_ans++].coef=Poly[tmp_poly_id2][i].coef;
                    else tmp_poly_ans[flag_of_poly_ans++].coef=Poly[tmp_poly_id2][i].coef*-1;
                }
            }
            poly_sort(tmp_poly_ans,flag_of_poly_ans);
            printf(YEL_BOLD);
            if(choose_menu_num==6) printf("P%d + P%d = ",tmp_poly_id1+1, tmp_poly_id2+1);
            else printf("P%d - P%d = ",tmp_poly_id1+1, tmp_poly_id2+1);
            int is_zero=print_poly(tmp_poly_ans,flag_of_poly_ans);
            if(!is_zero) printf("0\n");
            printf(RESET);
            for(int i=0;i<flag_of_poly_ans;i++){
                tmp_poly_ans[i].coef=0;
                tmp_poly_ans[i].exp=0;
            }
        }
        else if(choose_menu_num==8){
            if(flag_of_Poly<2){
                printf(RED_BOLD);
                printf("There are not at least two polynominal.");
                printf(RESET);
                continue;
            }
            printf(YEL_BOLD); printf("Show the result of a polynomial multiply a polynomial\n"); printf(RESET);
            // enter two name of poly template
            bool deter_name1=false,deter_name2=false;
            int tmp_poly_id1, tmp_poly_id2;
            char tmp_poly_name1, tmp_poly_name2;
            while(!deter_name1){
                printf("Enter polynominal1 name: ");
                scanf(" %c%d",&tmp_poly_name1, &tmp_poly_id1);
                deter_name1=enter_poly_name(tmp_poly_name1,tmp_poly_id1,flag_of_Poly);
            }
            tmp_poly_id1--;
            while(!deter_name2){
                printf("Enter polynominal2 name: ");
                scanf(" %c%d",&tmp_poly_name2, &tmp_poly_id2);
                deter_name2=enter_poly_name(tmp_poly_name2,tmp_poly_id2,flag_of_Poly);
            }
            tmp_poly_id2--;
            // 
            int flag_of_poly_ans=0;
            for(int i=0;i<length_of_poly[tmp_poly_id1];i++){
                for(int j=0;j<length_of_poly[tmp_poly_id2];j++){
                    int tmp_ans_exp=Poly[tmp_poly_id1][i].exp+Poly[tmp_poly_id2][j].exp, tmp_same_pos;
                    int tmp_ans_coef=Poly[tmp_poly_id1][i].coef*Poly[tmp_poly_id2][j].coef;
                    printf("tmp_ans_coef= %d\n",tmp_ans_coef);
                    bool deter_multi_ans_exp=false;
                    for(int k=0;k<flag_of_poly_ans;k++){
                        if(tmp_ans_exp==tmp_poly_ans[k].exp){
                            deter_multi_ans_exp=true;
                            tmp_same_pos=k;
                            break;
                        }
                    }
                    if(deter_multi_ans_exp) tmp_poly_ans[tmp_same_pos].coef+=tmp_ans_coef;
                    else{
                        tmp_poly_ans[flag_of_poly_ans].coef=tmp_ans_coef;
                        tmp_poly_ans[flag_of_poly_ans++].exp=tmp_ans_exp;
                    }
                }
            }
            poly_sort(tmp_poly_ans,flag_of_poly_ans);
            printf(YEL_BOLD);
            print_poly(tmp_poly_ans,flag_of_poly_ans);
            printf("\n");
            printf(RESET);
            for(int i=0;i<flag_of_poly_ans;i++){
                tmp_poly_ans[i].coef=0;
                tmp_poly_ans[i].exp=0;
            }
        }
        else if(choose_menu_num==9){
            if(flag_of_Poly<2){
                printf(RED_BOLD);
                printf("There are not at least two polynominal.");
                printf(RESET);
                continue;
            }
            printf(YEL_BOLD); printf("Show the result of a polynomial devided by a polynomial\nNumber: "); printf(RESET); 
            // enter two name of poly template
            bool deter_name1=false,deter_name2=false;
            int tmp_poly_id1, tmp_poly_id2;
            char tmp_poly_name1, tmp_poly_name2;
            while(!deter_name1){
                printf("Enter polynominal1 name: ");
                scanf(" %c%d",&tmp_poly_name1, &tmp_poly_id1);
                deter_name1=enter_poly_name(tmp_poly_name1,tmp_poly_id1,flag_of_Poly);
            }
            tmp_poly_id1--;
            while(!deter_name2){
                printf("Enter polynominal2 name: ");
                scanf(" %c%d",&tmp_poly_name2, &tmp_poly_id2);
                deter_name2=enter_poly_name(tmp_poly_name2,tmp_poly_id2,flag_of_Poly);
            }
            tmp_poly_id2--;
            //
        }
    }
    return 0;
}