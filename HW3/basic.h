#define RED_BOLD "\x1b[;31;1m"
#define BLU_BOLD "\x1b[;34;1m"
#define YEL_BOLD "\x1b[;33;1m"
#define GRN_BOLD "\x1b[;32;1m"
#define PURPLE "\e[1;35m"
#define CYAN_BOLD_ITALIC "\x1b[;36;1;3m"
#define RESET "\x1b[0;m"
#define MALLOC(p,s) \
    if(!((p) = (int*)malloc(s))) { /*注意 malloc 前的型別*/ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
#define CALLOC(p,n,s) \
    if(!((p) = (int*)calloc(n,s))) { /*注意 calloc 前的型別*/ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
#define REALLOC(p,s) \
    if(!((p) = (int*)realloc(p,s))) { /*注意 realloc 前的型別*/ \
        fprintf(stderr, "Insufficient memory"); \
        exit(EXIT_FAILURE); \
    }
typedef struct polynomial{
    int coef;
    int exp;
}polynomial;
typedef struct item_info {
    int po,coeff,deg_po,deg;
}item_info;