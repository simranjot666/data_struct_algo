#include <stdio.h>

struct yearbook
{
        int num_day[12];      
};

struct date
{
	int day;	
	int month;
} start,end;

void print_mon(int mon){
    
 switch(mon){
     case(1): printf("January");break;
     case(2): printf("February");break;
     case(3): printf("March");break;
     case(4): printf("April");break;
     case(5): printf("May");break;
     case(6): printf("June");break;
     case(7): printf("July");break;
     case(8): printf("August");break;
     case(9): printf("September");break;
     case(10): printf("October");break;
     case(11): printf("November");break;
     case(12): printf("December");break;
 }
    
    
}
void main(int argc, char *argv[])
{
        
    int start_date=4,start_day,temp=0,i,days=0;
    printf("Input: ");
    scanf("%d %d %d %d", &start.month, &start.day, &end.month,&end.day);
    struct yearbook sim;

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
    // CALCULATE NUMBER OF DAYS IN EACH MONTH FOR A NON-LEAP YEAR
   
    for (i=start.month+1;i<end.month;i++) temp+=sim.num_day[i-1];
    //ADD NUMBER OF DAYS FOR MONTHS IN BETWEEN THE START AND END MONTH
    
    (end.month==start.month) ? (days=end.day-start.day) : (days = sim.num_day[start.month-1]-start.day+end.day+temp);
   
    print_mon(end.month);
    printf(" %d is %d days after ",end.day,days);
    print_mon(start.month);
    printf(" %d\n",start.day);
   
}


