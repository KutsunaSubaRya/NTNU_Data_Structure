#pragma once
#include<stdio.h>
void print_menu(void){
    printf("Please enter a number 0~9 to choose what you want to do.\n");
    printf("(0) Exit.\n");
    printf("(1) Enter a polynomial of X (use the form of ax^b+cx^d...).\n");
    printf("(2) Print all polynomials on the screen.\n");
    printf("(3) Enter a degree, and show the coefficient.\n");
    printf("(4) New a non-zero item in the polynomail.\n");
    printf("(5) Remove a non-zero item in the polynomail.\n");
    printf("(6) Show the result of a polynomial plus a polynomial\n");
    printf("(7) Show the result of a polynomial minus a polynomial\n");
    printf("(8) Show the result of a polynomial multiply a polynomial\n");
    printf("(9) Show the result of a polynomial devided by a polynomial\nNumber: ");
}