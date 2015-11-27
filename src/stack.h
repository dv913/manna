void stack_init (int length) {
int len = length;
int stack[len];
int stack_used = 0;
}

void stack_push(int * stack, int cell_num) {
stack[stack_used] = cell_num;
stack_used++;

}

void stack_pop(int * stack)  {
return stack[stack_used];
stack_used--;
}
