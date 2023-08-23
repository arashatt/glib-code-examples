#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct stack {
  size_t top;
  ssize_t capacity; 
  int * stack;
};

void initialize(struct stack * st, int capacity){
  st->top = 0;
  st->capacity = capacity;
  st->stack = (int *) malloc(sizeof(int) * capacity);
  if (st->stack == NULL){
    exit(1);
  }
  
}

int pop(struct stack * st){
  if (st->top != 0)
    return st->stack[st->top--];

}
void push (struct stack * st, int value){
  if (st->top != st->capacity){
    st->top++;
    st->stack[st->top] = value;
  }

}
int size(struct stack st){
  return st.top;
}
