#include <stdio.h>
#include <stdlib.h>
#define NEW(x) (x*)malloc(sizeof(x))

//I TOOK THE LINKED LIST STRUCTURE FROM THE C CODES PROVIDED FOR THE LOGIC,  I HOPE NEXT TIME MINE WILL BE READY :)

typedef int DATA;

typedef struct node
{ void * data;
  struct node * next;
} NODE;

typedef struct
{ long num;
  NODE * head;
  NODE * tail;
}ROOT;

void display1(NODE n)
{ printf("By display1: %d\n", *(int *)(n.data));
}

void display2(void *data)
{ printf("By display2: %d\n", *(DATA *)(data));
}

NODE * make_node (void *data)
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
    temp->tail = NULL;
  }
  return temp;
}


void display_list(ROOT *r)
{ NODE * temp;

  if (r != NULL)	
    { temp = r->head;
    do 
    { 
		putchar(*(DATA *)(temp->data));
      temp = temp->next;
    } while (temp != NULL);
  }
  printf("\n");
}

int find_duplicate(ROOT *r,DATA *d)
{ NODE * temp;

  if (r != NULL)	
	{ temp = r->head;
    do 
    {
        if (*d==*(DATA *)(temp->data)) {
			return 1;
		}
      temp = temp->next;
    } while (temp != NULL);
  }
  
 return 0;
}


int insert_at_tail(ROOT *r, DATA *d)
{ NODE * temp;
  temp = make_node(d);

  if (temp == NULL) return -1;  

  if (r == NULL)
  { r = make_root();
    if (r == NULL) return -1;   
  }
    
  (r->num)++;

  if (r->num == 1)             
    r->head = r->tail = temp;

  else 
  { r->tail->next = temp;
    r->tail = temp;
  }
 
  return 0;
}
 
int main(void)
{ ROOT *root;	
  DATA *data2,*data1;	
  int i=1;
  char str[100];
  root = make_root();  // START THE LINKED LIST WITH ROOT
 printf("Input : ");
 gets(str);
 data2=NEW(DATA);
 *data2=str[0];
 insert_at_tail(root,data2);
 
 while(str[i]!='$')
    {
    data2 = NEW(DATA);
    data1 = NEW(DATA);
    *data1 = (int)str[i];   
    *data2 = (int)str[i];   
       if (find_duplicate(root,data1)==0){ // IF DUPLICATE IS NOT THERE THEN ADD NODE TO THE LINKED LIST
            insert_at_tail(root,data2);
        }
        i++;
    }
	display_list(root);
 return 0;
  }

