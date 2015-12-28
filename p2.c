#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NEW(x) (x*)malloc(sizeof(x))
#define POW(x) (pow(10.0,(double)x))

//PROJECT 2 CODE , PLEASE USE 'gcc -w -std=c99 -g pro2_3.c -lm' for compiling as math functions were not working without it
// the code has been tested with block size starting from 1 upto 4 digits
//known issues : output saved values in text file have zeros in front 


//Submitted by Simranjot S Antaal 
//for ENTS689A Algorithms and Data Structures Fall 2015

struct suc{ // to store output of k digit adder
	int sum;
	int carry;
};

typedef struct node
{ int * data;
    struct node * next;
   
} NODE;

typedef struct
{ long num;
    NODE * head;
   
}ROOT;

NODE * make_node (int *data)
{ NODE * temp;
    temp = NEW(NODE);
    if (temp != NULL)
    { temp->data = data;
        temp->next = NULL;
      
    }
    return temp;
}

ROOT * make_root (void)
{ ROOT * temp;
    temp = NEW(ROOT);
    if (temp != NULL)
    { temp->num = 0;
        temp->head = NULL;
      
    }
    return temp;
}


void display_list(ROOT *r,int K) //display contents of the linked list, appending with zeros if value of data in node is less number of digits than K digits
{ NODE * temp;
	int v1=K;int v=v1-1;
    
    if (r != NULL)
    { temp = r->head;
        do
        {
			if ((int)temp->data<POW(v)) {
				printf(",");
				for (int k=1;k<=v;k++){
					if((int)temp->data<POW(k)) printf("0");
				}
				printf("%d",(int)temp->data);
			}
			else{
            printf(",%d",(int)temp->data);
		}
            temp = temp->next;
        } while (temp != NULL);
    }
    printf("\n");
}

void print_to_file_list(ROOT *r,int K,FILE * fp)// same as display list but prints out to file
{ NODE * temp;

	int v1=K;int v=v1-1;int t=0;
	
    if (r != NULL)
    { temp = r->head;
        do
        {
			if ((int)temp->data!=0||t!=0){
				
			if ((int)temp->data<POW(v)) {
				printf(",");
				for (int k=1;k<=v;k++){
					if((int)temp->data<POW(k)) fprintf(fp,"0");
				}

				fprintf(fp,"%d",temp->data);
			}
			else{
            fprintf(fp,"%d",temp->data);
		}
		t=1;
	}
            temp = temp->next;
        } while (temp != NULL);
    }
    

}


int insert_at_head(ROOT *r, int *d){ 
	NODE * temp;
    temp = make_node(d);
    
    if (temp == NULL) return -1;
    
    if (r == NULL)
    { r = make_root();
        if (r == NULL) return -1;
    }
    
    (r->num)++;

    if(r->num==1){
        temp->next = r->head;
        
        r->head = temp;
    }
    else{
        temp->next = r->head;
        
        r->head = temp;
    }
    
    return 0;
}
void rev_lis(ROOT *root){// this function reverses list, as singly list and only 
	//insert_at_head is used therefore this function is used e.g. to get 
	//before adding the output of multiplication (which reverses the order due to insert_at_head)
	
    NODE *p = root->head,
                *q = NULL,
                *r=NULL;
    while (p != NULL)
    {
        r = q; 
        q = p;
        p = p->next;
        q->next = r;
    }
     root->head=q;

}
int num_chars(char *file_name){//to find the bigger number
    int count=0,k,c;
    FILE *fp = fopen(file_name, "r");
    while((c=fgetc(fp))) {
        if(c == EOF || c==10) break;
        count+=1;
    }
    fclose(fp);
    return count;
}

void file_to_list(char *file_name,ROOT *r,int len,int K){
    FILE *fp = fopen(file_name, "r");
    int offs;
    
    offs=len%K;//NUMBER OF DIGITS TO BE TAKEN IN EARLIEST NODE IF LEN%K!=0

    int c,v=offs-1,val=0;
    
    for (int n=0;n<offs;n++){//PUT OFFS - 1 DIGITS IN EARLIEST NODE
		c=fgetc(fp);
		val+=(c-48)*(int)POW(v);
        if (v==0){
			insert_at_head(r,val);
        }
        else{
        v=v-1;
	}
	}
	v=K;
	int v1=v-1;
	val=0;

    while(c=fgetc(fp)) {//PUT REMAINING DIGITS IN GROUP OF K IN LATER NODES
        if(c == EOF || c==10) break;        
        val+=(c-48)*(int)POW(v1);
        
        if (v1==0){
			insert_at_head(r,val);
            v1=v-1;
            val=0;       
        }
        else{
        v1--;
	}
    
    }    
    fclose(fp);
    

}

struct suc ADD_K(int a, int b,int c,int d,int K){

	static int call_add=0;
	call_add++;

	 struct suc res;int x;int v=K;
	 	if (d){
		res.sum=call_add;
		res.carry=call_add;
	}
	else{
	 
	 
	 x=a+b;//CALCULATE THE SUM
	 if (c) {
		 res.sum=x;res.carry=0;
		 return res;
		 }
	 
	 res.sum=x-(int)POW(v);//SUBTRACT 100
	 
	 if(res.sum>=0) {

		 res.carry=1;//IF SUM>100 THEN RETURN CARRY AND AND SUBTRACTED VALUE
	 }
	 else{
		 res.sum=x;//IF SUM<0 THEN RETURN X AND CARRY=0
		 res.carry=0;
		 }
	 }
	return res;
	}

struct suc MUL_K(int a, int b,int c,int K){//K digit multiplier, returns data in K digit blocks in carry and
										//sum fields of structure suc
	static int call_mul=0;
	call_mul++;

	 struct suc res;
	 if (c){
		 res.sum=call_mul;//return static variable call_mul if int c is set by user
		 res.carry=call_mul;
	 }
	 else{
	 int x;int v=K;
	 x=a*b;
	 res.carry=x/(int)POW(v);
	 res.sum=x%(int)POW(v);
	}	
	 return res;
	}

int SUB_K(int a, int b,int c){//acts as K digit subtractor
	static int call_sub=0;
	call_sub++;
	
	if (c){
		return call_sub;
	}
	else{

	 return a-b;
	 }
	}

ROOT * add_lists(ROOT *r1,ROOT *r2,int K){
    NODE * temp1,*temp2;
    ROOT *root;   // OUTPUT LIST
    root = make_root();
    int carry,v=K;
    struct suc res = {0,0};
    if (r1 != NULL&&r2!=NULL)
    
    { temp1 = r1->head;//RUN THROUGH R1 AND R2
        temp2=r2->head;

        do
        {
            if (res.carry){
                res=ADD_K(temp1->data,res.carry,1,0,K);//ADD CARRY IF PRESENT TO UPPER NODE
                //IF STILL CARRY IS THERE THEN ADD GET ABS SUM WITHOUT CARRY
					
                res=ADD_K(res.sum,temp2->data,0,0,K);//ADD THE SUM TO LOWER NODE TO GET RES
            }
            else{
                res=ADD_K(temp1->data,temp2->data,0,0,K);//SIMPLY ADD IF NO CARRY
            }

            insert_at_head(root,res.sum);
            temp2=temp2->next;
            temp1=temp1->next;
        } while (temp1 != NULL&&temp2!=NULL);
        
	//case of carry left at last addition
        while (res.carry!=0&&temp1!=NULL){

            res=ADD_K(temp1->data,res.carry,0,0,K);

            
            insert_at_head(root,res.sum);
            temp1=temp1->next;

        }
        while (res.carry!=0&&temp2!=NULL){
	
            res=ADD_K(temp2->data,res.carry,0,0,K);
      
            
            insert_at_head(root,res.sum);
            temp2=temp2->next;
        }
        //case of one num longer than other, after carry is adjusted
        while(temp1!=NULL){
			insert_at_head(root,(int)temp1->data);
			temp1=temp1->next;
			}
        while(temp2!=NULL){
			insert_at_head(root,(int)temp2->data);
			temp2=temp2->next;
			}			
		if(res.carry) insert_at_head(root,res.carry);//IF A CARRY IS LEFT AFTER ALL THE NODES EXPIRED
    }
    
    return root;
}

ROOT * multiply_lists(ROOT *r1,ROOT *r2,int K){
 NODE * temp1,*temp2;
    ROOT *root1,*root2,*root3,*root4;   // OUTPUT LIST
    root3 = make_root();
    root1 = make_root();
    root2 = make_root();
    root4=make_root();
    insert_at_head(root4,0);
    int carry,v=K;
    int count=0,l=0;
	struct suc res = {0,0};
    if (r1 != NULL&&r2!=NULL)
    { temp2 = r2->head;
        do
        {
			temp1=r1->head;
			l=0;
			for (int i=0;i<count+1;i++){
				insert_at_head(root2,0);
			}
			for (int i=0;i<count;i++){
                insert_at_head(root1,0);
            }
			do
			{//make two linked lists depending on which node is selected of the list running in inner loop
				//and add them later, finally accumulated in another list
				if(l%2==0){
					res=MUL_K(temp1->data,temp2->data,0,K);
					insert_at_head(root1,res.sum);
			
					insert_at_head(root1,res.carry);

				}
				else{
					res=MUL_K(temp1->data,temp2->data,0,K);
					insert_at_head(root2,res.sum);
					insert_at_head(root2,res.carry);
				}
                
                l++;
				temp1 = temp1->next;
			}while(temp1!=NULL);
			

            rev_lis(root2);// as first multiplication result is at the end of the list so, reverse the list 
            rev_lis(root1);

            root3=add_lists(root1,root2,K);
            rev_lis(root3);// again reverse list to get MSB at first position
            root4=add_lists(root3,root4,K);
            rev_lis(root4);

            temp2=temp2->next;
            root1->head=NULL;
            root1->num=0;
            root2->head=NULL;
            root2->num=0;
            root3->head=NULL;
            root3->num=0;

            count++;
        } while (temp2 != NULL);
    }
    
    return root4;
}

ROOT * sub_lists(ROOT *r1,ROOT *r2,int K){
 NODE * temp1,*temp2;//ASSUMING R1 has more nodes FIRST NODE RUNS THROUGH R2    R1>R2
    ROOT *root;   // OUTPUT LIST
    root = make_root();
    int res=0,b=0;
    int v=K;
	
    if (r1 != NULL&&r2!=NULL)
    { temp1 = r1->head;
	  temp2=r2->head;
			do
			{
				if(b){
					if(temp2->data>=temp1->data){
					
					res=SUB_K(POW(v)+(int)temp1->data-1,(int)temp2->data,0);
					b=1;
					
					}
				else{
					res=SUB_K((int)temp1->data-1,(int)temp2->data,0);
					b=0;
					}
				}
				else{
				if(temp2->data>temp1->data){
			
					res=SUB_K(POW(v)+(int)temp1->data,(int)temp2->data,0);
					b=1;
					
					}
				else{
					res=SUB_K((int)temp1->data,(int)temp2->data,0);
					
					b=0;
					}
				}
				
				
			insert_at_head(root,res);
			temp2=temp2->next;
            temp1=temp1->next;
        } while (temp1 != NULL&&temp2!=NULL);
        
        while (temp1!=NULL) {
            if(b){
				if((int)temp1->data==0){
					insert_at_head(root,(int)POW(v)+(int)temp1->data-1);
					b=1;					
				}
				else{
					insert_at_head(root,(int)temp1->data-1);
					b=0;
			}
                
            }
            else{
                insert_at_head(root,(int)temp1->data);
            }
            temp1=temp1->next;
        }

    }
    
    return root;
}

int bigger_numlis(ROOT * r1,ROOT * r2){
	NODE * temp1;
	NODE * temp2;
    if (r1 != NULL && r2 != NULL)
    { temp1 = r1->head;
		temp2=r2->head;
        do
        {
			if ((int)temp1->data > (int)temp2->data){
				return 1;
		}		
				else if ((int)temp1->data < (int)temp2->data){
				return 2;
				}

				
			temp2=temp2->next;
            temp1 = temp1->next;
        } while (temp1 != NULL&&temp2!=NULL);
        
    }
    return 0;
    printf("\n");
}


int main(int argc, char *argv[] )
{	
	int K;
	K=atoi(argv[1]);

    ROOT *root1;   // a pointer to ROOT type
    root1 = make_root(); // see what happend when this line is deleted.

    ROOT *root2;   // a pointer to ROOT type
    root2 = make_root(); // see what happend when this line is deleted.
    ROOT *root3;   // a pointer to ROOT type
    root3 = make_root(); // see what happend when this line is deleted.    
    
    int len_lis1,len_lis2,tempin;
    NODE * temp;
    
    len_lis1=num_chars(argv[2]);
    len_lis2=num_chars(argv[3]);

    if(len_lis1>len_lis2){
		
		file_to_list(argv[2],root1,len_lis1,K);
		file_to_list(argv[3],root2,len_lis2,K);
	}
	else if(len_lis1<len_lis2){

		
		file_to_list(argv[2],root2,len_lis1,K);
		file_to_list(argv[3],root1,len_lis2,K);
	}
	else{
		file_to_list(argv[2],root1,len_lis1,K);
		file_to_list(argv[3],root2,len_lis2,K);

		if (bigger_numlis(root1,root2)==2){

			temp=root1->head;
			tempin=root1->num;
			root1->head=root2->head;
			root1->num=root2->num;
			root2->head=temp;
			root2->num=tempin;	
		}		
	}
	FILE * fp;
	struct suc OP;
	fp = fopen(argv[4],"w");
	 
	root3= add_lists(root1,root2,K);
	
	OP=ADD_K(0,0,0,1,K);OP.sum--;
	fprintf(fp,"sum: %d block operations\n",OP.sum);
	print_to_file_list(root3,K,fp);
	fprintf(fp,"\n");

	root3= sub_lists(root1,root2,K);
	
	fprintf(fp,"subtract: %d block operations\n",SUB_K(0,0,1));
	print_to_file_list(root3,K,fp);
	fprintf(fp,"\n");
		
	root3= multiply_lists(root1,root2,K);
	rev_lis(root3);
	
	OP=MUL_K(0,0,1,K);OP.sum--;
	fprintf(fp,"multiply: %d block operations\n",OP.sum);
	print_to_file_list(root3,K,fp);
	fprintf(fp,"\n");
	
	fclose(fp);
    return 0;
}

