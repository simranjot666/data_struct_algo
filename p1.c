#include <stdio.h>
#include <stdlib.h>

/* ########################################################################################################
 * PROJECT ONE ; ENTS 689A ; ALGORITHMS AND DATA STRUCTURES
 * AUTHOR SIMRANJOT SINGH ANTAAL
 * Usage :
	0 (Copy to new file) source_file destination_file 
	1 (interleave two text files to third one) source_file_1 source_file_2 destination file
	2 (more display file) Input File
	3 (grep find string in a file) Input File
	4 (word count and other file details) Input File
 *  NOTES:
 *  1. DISPLAY FUNCTION TAKES "ENTER" TO PRINT NEXT LINE (CAN BE WITH ANY CHARACTER ENTERED AS WELL), AND Q+ENTER TO QUIT
 *  2. IN WORD COUNT IF THE LINE NUMBER IS SAME FOR BOTH LOWEST COUNT OF WORDS AND CHARACTERS THEN LINE IS PRINTED ONLY ONCE WITH NUMBER OF CHARACTERS AND WORDS
 *  3. SOME VARIABLES ARE INITIALIZED WITH A VALUE THAT CAN LIMIT EXTREME CASES , BUT THESE CAN BE CHANGED TO SUPPORT HIGHER RANGE OF VALUES
 *########################################################################################################*/
 
int main(int argc, char * argv[])
{

    if (argc==1 || ( (argv[1][0]!='0') && (argv[1][0]!='1') && (argv[1][0]!='2')&&(argv[1][0]!='3') &&(argv[1][0]!='4'))){
        printf("Usage :\n0 (Copy to new file) source_file destination_file \n1 (interleave two text files to third one) source_file_1 source_file_2 destination file\n2 (more display file) Input File\n3 (grep find string in a file) Input File\n4 (word count and other file details) Input File\n");
        return 0;
    }
    
    switch(argv[1][0]){
            FILE *f_in1;
            FILE *f_out;
            FILE *f_in2;
            char ch,sel;
            int flag1=0,flag2=0,status=0,num_lines=0,k=0,num_chars=0,num_words=0,num_ch,smal_ch,smal_ch_line,r=0,n=0;
            int flagm=0,conter=0;
            int num_words_lin,smal_words_lin,smal_words_linNumber,flagn=0;;
            int dis[3]={0};
            char saved_words[3][20];
            char a[20];
            char str1[60],str[60];
        case '0':
            if (argc<4) {
                printf("Usage 1 (Copy to new file) source_file destination_file\n");
                return 0;
            }
            
            printf ("%c : Copying file %s to %s\n",argv[1][0],argv[2],argv[3]);
            f_in1=fopen(argv[2],"r");
            f_out=fopen(argv[3],"w");            
            while( fscanf(f_in1, "%c", &ch) != EOF )
            {
                fprintf(f_out, "%c", ch); //COPY FROM f_in1 TO f_out AS IT IS AND EACH CHARACTER
            }
            fclose(f_out);
            fclose(f_in1);
            break;
            
        case '1':
            if (argc<5) {
                printf("Usage 1  (interleave two text files to third one) source_file_1 source_file_2 destination file\n");
                return 0;
            }

            flag1=0;
            flag2=0;
            f_in1=fopen(argv[2],"r");
            f_in2=fopen(argv[3],"r");
            f_out=fopen(argv[4],"w");
            printf ("%c : Interleaving files %s and %s to %s\n",argv[1][0],argv[2],argv[3],argv[4]);
            
            while(flag1==0 || flag2==0){
                
                while(status = fscanf(f_in1, "%c", &ch))
                {
                    if (status!=1){
                        flag1=1; //CHECK IF f_in1 REACHED ITS END
                        break;
                    }
                    
                    if (ch=='\n') {
                        fprintf(f_out,"\n");
                        break;
                    }
                    
                    else{
                        fprintf(f_out, "%c", ch);
                        if (ch=='\n') printf("FU");
                    }
                    
                }

                while(status = fscanf(f_in2, "%c", &ch))
                {
                    if (status!=1){
                        flag2=1;//CHECK IF f_in2 REACHED ITS END
                        break;
                    }
                    
                    if (ch=='\n') {
                        fprintf(f_out,"\n");
                        break;                        
                    }
                    
                    else{
                        fprintf(f_out, "%c", ch);
                    }
                }                
            }
//FINISH THE OTHER FILE WRITING TASK
            if (flag1==1){
                while((status = fscanf(f_in1, "%c", &ch)) != EOF){
                    if(status) break;
                    fprintf(f_out,"%c",ch);
                }
            }
            if (flag2==1){
                while((status = fscanf(f_in1, "%c", &ch)) != EOF){
                    if (status) break;
                    fprintf(f_out,"%c",ch);
                }
            }
            fclose(f_in1);
            fclose(f_in2);
            fclose(f_out);
            break;
            
        case '2':
            if (argc<3) {
                printf("Usage 2 (more display file) Input File\n");
                return 0;
            }
            num_lines=0;
            f_in1=fopen(argv[2],"r");
            printf ("%c : Displaying file %s\n",argv[1][0],argv[2]);
            
            while((status = fscanf(f_in1, "%c", &ch)))
            {
                if (ch=='\n') {
                    num_lines++;
                }
                if (status!=1 || num_lines>9) { 
					//STOP PRINTING IF REACHED 10 LINES OR END OF FILE	
                    break;
                }
                else{
                    printf("%c",ch);
                }
            }
            
            int u=0;
            while(1){
				sel=getchar();
				//WAIT FOR USER INPUT
                if (sel=='Q'){
                    break;
                }
                else 
                //PRINT ONE MORE IF NOT RETURNED 'Q'
                {
                    while (status=fscanf(f_in1, "%c", &ch)){
						if(status!=1) return 1;           
                        if (ch=='\n') {
                            break;
                        }
                        else{
                 
                            u++;
                            printf("%c",ch); 
                        }
                    }
                }
            }
            fclose(f_in1);
            break;
            
            
        case '3':
            if (argc<3) {
                printf("Usage 3 (grep find string in a file) Input File\n");
                return 0;
            }
            
            printf("enter the string : ");
            scanf("%s",&str1);
            f_in1=fopen(argv[2],"r");
            printf ("%c : Finding  ' %s ' in %s\n",argv[1][0],str1,argv[2]);
            while( fgets (str, 100, f_in1)!=NULL )
            {
                if (strstr(str, str1) != NULL) {
                    puts(str);
                }
            }
            fclose(f_in1);
            break;
            
        case '4':
            if (argc<3) {
                printf("Usage 4 (word count for file details) Input File\n");
                return 0;
            }
            k=0;
            for (r=0;r<=2;r++){dis[r]=0;}
            flagn=0;num_lines=0;num_chars=0;num_words=0;num_ch=0;smal_ch=10000;smal_ch_line=0;num_words_lin=0;smal_words_lin=10000;smal_words_linNumber=0;
            f_in1=fopen(argv[2],"r");
            while((status = fscanf(f_in1, "%c", &ch)))
            {
                if(status==1){
                    num_chars++;
                    num_ch++;
                    if (ch=='\n') {
                        num_lines++;
                        if (num_ch < smal_ch) { // STORE THE LINE NUMBER OF NUMBER OF CHARACTERS IN THE LINE ARE LESS THAN PREVIOUSLY RECORDED
                            smal_ch=num_ch;
                            smal_ch_line=num_lines;
                        }
                        num_ch=0;
                        
                    }
                    
                if ((ch>='0' & ch<='9')|(ch>='a' & ch<='z')|(ch>='A' & ch<='Z')){
                    a[k]=ch;
                    k++;
                }
                else{

                    if(k!=0 ){
                        num_words++;
                        num_words_lin++;
                    }
                    if (ch=='\n'){
                        if (num_words_lin < smal_words_lin) { // STORE THE LINE NUMBER IF NUMBER OF WORDS IN THIS LINE ARE LESS THAN IN ALL LINES UPTO THIS POINT
                            smal_words_lin=num_words_lin;
                            smal_words_linNumber=num_lines;
                        }
                        num_words_lin=0;
                    }
                    for (r=0;r<=2;r++){
                        if (dis[r]<k) {
                            flagn=1; // CHECK IF THE WORD LENGTH IS LARGER THAN ANY OF THE TOP THREE RECORDED WORD LENGTHS
                        }
                    }
                    if (flagn==1){
                        r=(dis[0]<dis[1])?((dis[2]<dis[0])?2:0):((dis[2]<dis[1])?2:1);
                        strncpy(saved_words[r],a,k); // IF YES THAN SAVE THE WORD TO THE ARRAY
                        dis[r]=k;
                    }
                    flagn=0;
                    k=0;
                }
			}
                if (status!=1) {
                    printf("The number of characters is : %d\n",num_chars);
                    printf("The number of words is : %d\n",num_words);
                    printf("The number of line is %d\n",num_lines);
                    fclose(f_in1);
                    num_lines=0;
                    f_in1=fopen(argv[2],"r");
                    flagn=0;
                    flagm=0;
                    conter=0;
                    if (smal_ch_line==1) {
                        flagn=1;
                        printf ("The shortest line (%d characters) : ",smal_ch);
                    }
                    if (smal_words_linNumber==1) {
                        flagm=1;
                        printf ("The shortest line (%d words) : ",smal_words_lin);
                    }
                    while((status = fscanf(f_in1, "%c", &ch)))
                    {
                        if (flagn==1 || flagm==1){ 
                            printf("%c",ch);
                        }
                        if (ch=='\n') {
                            if (flagn==1){
								//FIND IF SHORTEST LINE IN TERMS OF CHARACTERS COMES FIRST OR WITH FEWEST WORDS COMES FIRST AND THEN PRINT IN THIS ORDER
                                flagn=0;
                                //IF BOTH ARE IN SAME LINE NUMBER THEN PRINT THAT LINE ONLY ONCE
                                conter++;
                            }
                            if (flagm==1){
                                flagm=0;
                                conter++;
                            }
                            if (conter==2){
                                break;
                            }
                            num_lines++;
                            if (num_lines==smal_ch_line-1){
                                flagn=1;	
                                printf ("The shortest line (%d characters) : ",smal_ch);
                            }
                            if(num_lines==smal_words_linNumber-1){
                                flagm=1;
                                printf ("The shortest line (%d words) : ",smal_words_lin);
                            }
                        }
                    }
                    
                    printf("The longest three words are : ");
                    for(r=0;r<3;r++){
                        for (n=0;n<=dis[r]-1;n++){
                            printf("%c",saved_words[r][n]);
                        }
                        printf(" ");
                    }
                    printf("\n");
                    
                    break;
                }
            }

    }
    
}

