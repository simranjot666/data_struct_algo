#include <stdio.h>
#include <stdlib.h>
#define NEW(x) (x*)malloc(sizeof(x))

//I TOOK THE LINKED LIST STRUCTURE FROM THE C CODES PROVIDED FOR THE LOGIC,  I HOPE NEXT TIME MINE WILL BE READY :)
// DOUBLY LINKED LIST IS USED TO STORE SCHEDULE DATA, ALONG WITH FIND FUNCTIONALITY
// LIST DISPLAY FUNCTION USES THE PREVIOUS POINTER OF THE NODES TO TRAVERSE THROUGH THE LIST

typedef int DATA;

typedef struct date
{
	int day;	
	int month;
} DATE;

typedef struct node
{ DATE * data;
  struct node * next;
  struct node * prev;
} NODE;

typedef struct
{ long num;
  NODE * head;
  NODE * tail;
}ROOT;

NODE * make_node (DATE *data)
{ NODE * temp;
  temp = NEW(NODE);
  if (temp != NULL)
  { temp->data = data;
    temp->next = NULL;
    temp->prev = NULL;
  }
  //printf("ss %d\n",data->month);
  return temp;
}

ROOT * make_root (void)
{ ROOT * temp;
  temp = NEW(ROOT);
  if (temp != NULL)
  { temp->num = 0;
    temp->head = NULL;
    temp->tail = NULL;
  }
  return temp;
}


void display_list(ROOT *r)
{ NODE * temp;

  if (r != NULL)	
    { temp = r->tail;
    do 
    { 
		printf("%d/%d,",temp->data->month,temp->data->day);
      temp = temp->prev;
    } while (temp != NULL);
  }
  printf("\n");
}

int find_duplicate(ROOT *r,DATE *d)
{ NODE * temp;

  if (r != NULL)	
	{ temp = r->head;
    do 
    {
        if ((d->day==temp->data->day)&&(d->month==temp->data->month)) {
			return 1;
		}
      temp = temp->next;
    } while (temp != NULL);
  }
  
 return 0;
}


int insert_at_tail(ROOT *r, DATE *d)
{ NODE * temp;
  temp = make_node(d);

  if (temp == NULL) return -1;  

  if (r == NULL)
  { r = make_root();
    if (r == NULL) return -1;   
  }
    
  (r->num)++;

  if (r->num == 1)             {
    r->head = r->tail = temp;
    temp->prev=NULL;
}

  else 
  { r->tail->next = temp;
	temp->prev = r->tail;
    r->tail = temp;
		
    
  }
 
  return 0;
}
 
 int insert_at_position(ROOT *r, DATE *d)
{ NODE * temp, *this;
  temp = make_node(d);

  if (temp == NULL) return -1; 

  if (r == NULL)
  { r = make_root();
    if (r == NULL) return -1;  
  }
  
  this = r->head;
  if (this==NULL) {
	  insert_at_head(r,temp->data);
	  return 0;
  }
  
    if ((30*(this->data->month) + this->data->day)<= (30*(temp->data->month)+temp->data->day)){ 
  
    insert_at_head(r, temp->data);
}
  else
  {
	  while (this->next!=NULL&&((30*(this->next->data->month) + this->next->data->day)> (30*(temp->data->month)+temp->data->day)))

      this = this->next;

    if (this->next == NULL)  insert_at_tail(r,temp->data);
    
    else
    { temp->next = this->next;
      this->next = temp;
      temp->prev=this;
      temp->next->prev=temp;
      
      (r->num)++;
    }
  }
  return 0;
}

 int insert_at_head(ROOT *r, DATE *d)
{ NODE * temp;
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
	r->head->prev=temp;  
  temp->next = r->head;
  
  r->head = temp;
}

  if (r->num == 1)    r->tail = temp;
 
  return 0;
}

 
 
int main(void)
{ ROOT *root;	
  DATE *data1;
  	data1=NEW(DATE);
  	
  	int i=0;
  	
  	root = make_root();
  while(1){
	  data1=NEW(DATE);
	  printf("Enter month and day (MONTH DAY) or Enter 0 0 to search in the schedule or -1 -1 to exit :  ");
	  scanf("%d %d",&data1->month,&data1->day);
	  
	  if(data1->day==0 || data1->month==0) {
		if (i==0){
			printf("No entries in the schedule\n");
			continue;
		}
		else{
		printf("Enter the day and month to be checked in schedule: ");  
		scanf("%d %d",&data1->month,&data1->day);
		if(find_duplicate(root,data1)){
			printf("Entry Found for this date %d/%d\n",data1->month,data1->day);
			continue;
		}
		else{
			printf("No Entry on this date %d/%d\n",data1->month,data1->day);
			continue;
		}
	  }
  }

	  else if(data1->day==-1 || data1->month==-1) {
		  return 0;
	  }
	  if (i==0){
		  insert_at_position(root,data1);
		  display_list(root);	
	  }
	  
	  if(i>0){
		  if(find_duplicate(root,data1)==0){
		insert_at_position(root,data1);
		  
	  display_list(root);	
  
		}
		else {
			printf("Another entry present on this date %d/%d\n",data1->month,data1->day);
		}
	}
  i++;
  }
 
 return 0;
  }
	  

