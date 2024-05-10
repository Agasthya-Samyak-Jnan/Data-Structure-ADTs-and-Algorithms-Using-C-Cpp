//CIRCULAR DOUBLE LINKED LIST ADT

#include<stdio.h>
#include<stdlib.h>

int i,j;

struct head {
  int count;
  struct node* hb_link, *hf_link;
};

struct node {
  int a;
  struct node* b_link, *f_link;
};

struct node* newloc() {
  struct node* p = (struct node*)malloc(sizeof(struct node));
  return p;
}

void createlist (struct head** q, int a) {
  (*q) = (struct head*)malloc(sizeof(struct head));
  struct node* p = newloc();
  p->a = a;
  (*q)->hf_link = p;
  (*q)->hb_link = p;
  p->f_link = p;
  p->b_link = p;
}

void display (struct head* q) {

  if(q->hf_link == NULL) {printf("No Nodes present! Add Nodes to Continue:"); return;}

  struct node* p = q->hf_link;
  do {
    printf("%d ", p->a);
    p = p->f_link;
  } while (p != q->hf_link);
  printf("\n");
}



void ins_pos (struct head* q, int pos, int a){
struct node* new  = newloc(), *p = (q)->hf_link;
new->a = a;

if(q->hf_link == NULL) {
  q->hf_link = new;
  q->hb_link = new;
  new->f_link = new;
  new->b_link = new;
  return;
}

if (pos == 1) 
  {
    new->f_link = (q)->hf_link;
    (q)->hf_link = new;
    new->b_link = p->b_link;
    p->b_link = new;
    (q)->hb_link->f_link = new;
    return;
  }
i = 1;
while (i<pos-1 && p!= (q)->hb_link){
  p = p->f_link; i++;
}
new->f_link = p->f_link;
p->f_link = new;
new->b_link = p;
new->f_link->b_link = new;
if(p == (q)->hb_link) { (q)->hb_link = new;}

}



void del_pos (struct head* q, int pos) {

  
  if(q->hf_link == NULL) {printf("No Nodes present! Add Nodes to Continue:"); return ;}

  struct node* p = q->hf_link;

  if (p->f_link == p || p->b_link == p) {free(p), q->hf_link=NULL; return;}

  if(pos == 1) {
    q->hf_link = p->f_link;
    p->f_link->b_link = p->b_link;
    p->b_link->f_link = p->f_link;
    free(p);
    return;
  }
  i=1;
  while (i<pos-1 && p->f_link != q->hb_link) {
    p = p->f_link; i++;
  }
   p->f_link = p->f_link->f_link;
   free(p->f_link->b_link);
   if (p->f_link->b_link == q->hb_link) { q->hb_link = p;}
   p->f_link->b_link = p;
  
}



int search_key (struct head* q, int a) {

  if(q->hf_link == NULL) {printf("No Nodes present! Add Nodes to Continue:"); return 0;}

  struct node* p = q->hf_link;
  i=1;
   while (p->f_link != q->hf_link && p->a != a) {
       i++; p = p->f_link;
     }
  if (p->a == a){return i;}
  else {return 0;}
}


void del_key (struct head* q, int a) {

i = search_key(q,a);
if (i != 0) {del_pos(q,i);}
else {printf("Key Value not found!\n");}
return;
}



void reverselist (struct head* q) {

 if(q->hf_link == NULL) {printf("No Nodes present! Add Nodes to Continue:"); return;}

 struct node* p = q->hf_link, *temp = NULL;
 while (temp != q->hf_link) 
 {
  temp = p->f_link;
  p->f_link = p->b_link;
  p->b_link = temp;
  p = p->b_link;
 }
 temp = q->hb_link;
 q->hb_link = q->hf_link;
 q->hf_link = temp;
 display(q);
}


void copylist (struct head* q, struct head* s) {

  if(q->hf_link == NULL) {printf("No Nodes present! Add Nodes to Continue:"); return;}
  
  struct node* p = q->hf_link, * r = p,*u;
  createlist(&s,p->a);
  struct node* t = s->hf_link;
  p = p->f_link;
  while (p != r) 
  {
    u = newloc();
    u->a = p->a;
    t->f_link = u;
    u->b_link = t;
    t = u;
    p = p->f_link;
  }
  s->hf_link->b_link = t;
  t->f_link = s->hf_link;
  s->hb_link = t;
   display(s);
}


void orderedlist (struct head* q, struct head* t) {

  if(q->hf_link == NULL) {printf("No Nodes present! Add Nodes to Continue:"); return;}

  struct node* p = q->hf_link;
  createlist(&t, p->a); 
  p = p->f_link;
  struct node* s = t->hf_link, *new;
  
  while (p != q->hf_link) {
      s = t->hf_link;
      new = newloc();
      new->a = p->a;
      if (s->a > p->a) 
      {
        new->f_link = s;
        new->b_link = s->b_link;
        s->b_link = new;
        new->b_link->f_link = new;
        t->hf_link = new;
      }
      else 
      { 
        s = s->f_link;
        while (p->a > s->a && s != t->hf_link)
        {
          s = s->f_link; 
        }
        new->b_link = s->b_link;
        s->b_link = new;
        new->f_link = s;
        new->b_link->f_link = new;
        if (new->b_link == q->hb_link) {q->hb_link = new;}
      }
      p = p->f_link;
  }
  display(t);
} 


void freelist (struct head* q) {
  if (q->hf_link == NULL) { free(q); q = NULL; return; }

  struct node* p = q->hf_link->f_link;
  while (p != q->hf_link) {
    free(p->b_link);
    p = p->f_link;
  }
  free(q->hb_link);
  free(q); q= NULL; 
}


int main () {

int pos, x, a, b;
struct head* q, *s, *t;
    
    printf("   - Circular Doubly Linked List - \n");
    printf("- 0 : EXIT.\n");
    printf("- 1 : Create List\n");
    printf("- 2 : Display List\n");
    printf("- 3 : Insert By Position\n");
    printf("- 4 : Delete By Position\n");
    printf("- 5 : Delete By Key\n");
    printf("- 6 : Search By Key\n");
    printf("- 7 : Reverse the List\n");
    printf("- 8 : Create Ordered List\n");
    printf("- 9 : Create a Copy of List\n");

while (1) {
  scanf("%d", &x);
  switch (x) {
    case 0 : {freelist(q), freelist(s), freelist(t); return 0;}
    case 1 : {
              printf("Enter value for first node:");
              scanf("%d",  &a);
              createlist(&q,a); 
              break;
             }
    case 2 : {display(q); break;}
    case 3 : {
              printf("Enter Position and value to insert:");
              scanf("%d %d", &pos, &a);
              ins_pos(q,pos,a);
              break;
              }
    case 4 : {
              printf("Enter Position to Delete:");
              scanf("%d", &pos);
              del_pos(q, pos);
              break;
             }
    case 5 : {
              printf("Enter Key value to search:");
              scanf("%d", &a);
              b = search_key(q,a);
              if (b != 0) {printf("Key Value %d is present at %d location.\n", a, b);}
              else {printf("Key Value Not Found!\n");}
              break;
             }
    case 6 : {
              printf("Enter Key Value to Delete:");
              scanf("%d",  &a);
              del_key(q,a);
              break;
             }
    case 7 : { reverselist(q); break; }
    case 8 : { orderedlist(q,t); break; }
    case 9 : { copylist(q,s); break; }
    default : break;
  }
}
  return 0;
}