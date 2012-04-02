
/*Author Feiyi Su*/
#include <stdio.h>
#include <conversion.h>

int main(void) {
	printf("%.5f\n", conversion_ktp());
        printf("%.5f\n", conversion_ktb());
        printf("%.5f\n", conversion_ptk(29.1));
        printf("%.5f\n", conversion_ptb(29.1));
        printf("%.5f\n", conversion_btk(30.2));
        printf("%.5f\n", conversion_btp(30.2));
return 0;
}


