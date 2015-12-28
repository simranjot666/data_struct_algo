#include <stdio.h>
#include <stdlib.h>

void searchprint(char C[],char D[],char *ptrb){
	int i;
    if(strstr(ptrb,C)){
        printf("Matched : %s\n",D);
    }
    else{
        printf("Not Matched: %s\n",ptrb);
    }
}


int main(int argc, char * argv[])
{
    int len_max = 128;
    int current_size = 0;
    
    char *pStr = malloc(len_max);
    current_size = len_max;
    
    printf("Enter String:");
    
    if(pStr != NULL)
    {
        int c = EOF;
        int i =0;
        
        while (( c = getchar() ) != '\n' && c != EOF)
        {
            pStr[i++]=(char)c;
            
            //if i reached increase size then realloc size
            if(i == current_size)
            {
                current_size = i+len_max;
                pStr = realloc(pStr, current_size);
            }
        }
        
        pStr[i] = '\0';
    }
    
    char A[]="Tony", B[] = "'s sister helps ", *ptr1,*ptr2;
    printf("A = '%s' and B='%s'\n",A,B);
    ptr1=malloc((2*strlen(A)+strlen(B))*sizeof(char)); 
    //MAKE SPACE FOR ABA AND AB STRINGS
    ptr2=malloc((strlen(A)+strlen(B))*sizeof(char));
	strcpy(ptr1,A);
	strcpy(ptr2,A);
	strcat(ptr1,B);
	strcat(ptr2,B);
    strcat(ptr1,A);
    //PUT ABA INTO PTR1 AND AB TO PTR2
    searchprint(ptr1,ptr2,pStr);

}

