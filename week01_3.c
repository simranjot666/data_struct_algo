#include <stdio.h>
#define DAYS 365


struct yearbook
{
        int start_day[12];
        int num_day[12];
        
};//THIS STRUCTURE HOLDS START DAY AND NUMBER OF DAYS FOR EACH MONTH IN 2015


void prin(int num_day, int start_day){
//THIS FUNCTION TAKES NUMBER OF DAYS IN THE MONTH AND THE DAY OF 1ST OF THAT MONTH
        int i,j,count=1;
        printf("  Su   Mo   Tu   We   Th   Fr   Sa\n  --------------------------------\n");
        for (i=0;i<=5;i++){
                for (j=0;j<=6;j++){
                   if(num_day>0){
                        if (start_day>0){
                                printf("     ");//BLANKS FOR THE INITIAL DAYS IN MONTH
                        }
                        else{
                                printf(" %3d ",count);//PRINT DIGITS FOR CALENDAR AND INCREMENT
                                count++;
                                num_day=num_day-1;
                        }
                        
                        start_day=start_day-1;
                      }
                    }
                    printf("\n");
                }

        }


void main(int argc, char *argv[])
{
        int mont=8;

        if (argc==1) {
                printf("Please enter a month of 2015\nPrinting for September 2015 :\n\n");
                mont=8;
                //SEPTEMBER 2015BY DEFAULT
                
        }
        else if (argc==2){
    
    mont=atoi(argv[1])-1;
    //CONVERT TO INT FROM USER'S INPUT
    
    }
    
    int start_date=4;
        
    struct yearbook sim;
        
    int i;

    for (i=0;i<12;++i)
    {
            if ((i%2==1 & i<7) | (i%2==0 & i>6))
            {
                    sim.num_day[i]=30;
            }
            if((i%2==1 & i>6)|(i%2==0&i<7)) 
            {
                    sim.num_day[i]=31;
            }
                    
    }   
    
    sim.num_day[1]=28;
    sim.start_day[0]=start_date;
    //STARTING OF THE MONTH FOR JAN 2015 AND NUMBER OF DAYS IN A YEAR
    
    for (i=1;i<12;i++){
            sim.start_day[i]=(sim.start_day[i-1]+sim.num_day[i-1])%7;

    }

    prin(sim.num_day[mont],sim.start_day[mont]);

}

