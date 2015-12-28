#include <stdio.h>

void reverseString(int arr[], int length,FILE *f_out)
{
    //REVERSE THE STRING AND PRINT INTO OUTPUT FILE
    int temp,start=0,end=length-1,i;

    
    while(start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
    
    for (i=0; i <length; i++)

        putc(arr[i],f_out);

}

int main(int argc, char * argv[])
{
    int c,k=0;
    if (argc<=2) {
        printf("\nUSAGE: ./a.out INPUT_FILE OUTPUT_FILE\n");
        return 0;
        
    }
    int a[20]={0};
    FILE *f_in;
    FILE *f_out;
    f_in=fopen(argv[1],"r");
    f_out=fopen(argv[2],"w");
    
    while ((c=getc(f_in))!=EOF){
        
        if ((48<=c&&c<=57)||(65<=c&&c<=90)||(97<=c&&c<=122)){
            a[k] = c;
//DETECT IF THE CHARACTER IS A ALPHANUMERIC
            k++;
        }
    
        
        else{

            reverseString(a,k,f_out);
            putc(c,f_out);
            k = 0;
            int a[20] = { 0};
            //FOR ALL OTHER SYMBOLS PARSE THE STRING TO FUNCTION AND PRINT THIS CHARACTER

        }
        
    }
    fclose(f_in);
    printf("\n");
}
