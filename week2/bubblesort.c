#include <stdio.h>
#include <cs50.h>

int main(void) {
	int len = 0, i, j, temp;
	int a[10];
	char con;
	
	do {
		printf("\nEnter number%d:", len + 1);
		scanf("%d", &a[len]);
		len++;
		if (len == 10) break;
		printf("\ncontinue? (y/n)\n");
		scanf(" %c", &con);
	} while(con == 'y' || con == 'Y');
	
	printf("\nYou Entered numbers: ");
	for (i = 0; i < len; i++) {
		if (i < len-1)
			printf("%d, ", a[i]);
		else
			printf("%d;\n", a[i]);
	}
	
	{
	
	for (i = 0; i < len-1; i++) {
		for (j = 0; j < len - i; j++) {
			if (a[j] > a[j+1]) {
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}
		
//	printf("\nlen = %d", len);
	
	printf("\nSorted numbers: ");
	for (i = 0; i < len; i++) {
		if (i < len-1)
			printf("%d, ", a[i]);
		else
			printf("%d;\n", a[i]);
	}
	return 0;
}