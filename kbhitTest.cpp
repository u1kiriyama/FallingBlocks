#include <iostream>
#include "kbhit.hpp"

int main(void)
{
	printf("please input any key > ");

	while (1) {
		if (kbhit()) {
			printf("\n");
			printf("the key was : %c\n", getchar());
			break;
		}
		
		// sleep(1); // sec
		usleep(10 * 1000);
	}

	return 0;
}