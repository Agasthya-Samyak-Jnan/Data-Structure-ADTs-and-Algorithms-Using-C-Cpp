//STACK USING ARRAY (STATIC)
#include<stdio.h>
#include<stdlib.h>

int top = -1,n;

void push (int s[], int a){
    if (top >= n-1){printf("%d Cannot Push, Stack Overflow!(FULL)\n",top); return;}
    top++; s[top] = a;
}

int pop (int s[]){
    if(top < 0){printf("%d Cannot Pop, Stack Underflow!(EMPTY)\n",top); return -1;}
    int a = s[top]; top--;
    return a;
}

void display (int s[]) {
    for(int i=0;i<=top;i++) {
        printf("%d ", s[i]);
    }
    printf("\n");
}

int main () {
int x,a;
printf("Enter Size of Stack:");
scanf("%d", &n);
int stack[n];
while(1) {
    scanf("%d", &x);
    switch (x) {
        case 0 :{return 0;}
        case 1 :{printf("Enter value to push:");
                 scanf("%d", &a);
                 push(stack,a);
                 break;
                }
        case 2 :{printf("Popped %d ,\n", pop(stack));break;}
        case 3 :{display(stack); break;}
        default: break;
    }
}

    return 0;
}