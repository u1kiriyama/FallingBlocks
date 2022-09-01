#include <iostream>
#include "kbhit.hpp"

int main(void)
{
	printf("please input any key > ");

	while (1) {
		if (kbhit()) {
			printf("\n");
			char c1 = getchar();
			if (int(c1) == 0x1b) {
				printf("the key was : %c\n", c1);
				printf("the key was : %d\n", c1);
				printf("not charctor\n");
				char c2 = getchar();
				printf("the key was : %c\n", c2);
				printf("the key was : %d\n", c2);
				char c3 = getchar();
				printf("the key was : %c\n", c3);
				printf("the key was : %d\n", c3);

				break;
			}
			printf("the key was : %c\n", c1);
			printf("the key was : %d\n", c1);
			break;
		}
		
		// sleep(1); // sec
		usleep(10 * 1000);
	}

	return 0;
}