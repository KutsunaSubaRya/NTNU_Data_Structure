#pragma once
// bool add_poly_name(char str[]);
// int query_poly_id(char str[]);
int cmp(const void *a1, const void *a2);
void poly_sort(struct polynomial p[], int poly_len);
int print_poly(struct polynomial p[],int poly_len);
bool enter_poly_name(char tmp_poly_name, int tmp_poly_id, int flag_of_Poly);