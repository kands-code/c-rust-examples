#include "linear-list/sl-list.h"
#include <stdio.h>

int main(void) {
    SL_List L = SL_Sington();
    SL_InsertBefore(L, 1, 10);
    printf("%d\n", SL_Length(L));
    return 0;
}