#include <stdio.h>



void main(){

	int var1,var2,var3;

	printf("Input: ");

	scanf("%d %d %d", &var1, &var2, &var3);

	

	if (var1>var2){

		if (var2>var3){

			

			printf("Output: %d %d %d\n",var3,var2,var1);

		}

		else{

			if (var1>var3){

				printf("Output: %d %d %d\n",var2,var3,var1);

			}

			else {

				printf("Output: %d %d %d\n",var2,var1,var3);

			}

		}

	}

			

	else{

		if (var1>var3){

			printf("Output: %d %d %d\n",var3,var1,var2);

		}

		else{

			if (var2>var3){

				printf("Output: %d %d %d\n",var1,var3,var2);

			}

			else{

			printf("Output: %d %d %d\n",var1,var2,var3);	

			}

			

		}

		}

		}

	

   


