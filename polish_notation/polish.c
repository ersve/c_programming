

#include <stdio.h> 
#include <stdlib.h>


#define MAX_SYMBOLS 2048
#define MAX_STRING 4
#define TRUE 1
#define FALSE 0
#define NONE '\0'



// A struct to keep the contents and meta information about the stack
struct LIFO {
	char **array;
	int index;
	unsigned size;
};

typedef struct LIFO Stack;

// Function to copy the contents from one string to another
char *copy_string(char *target, char *source){
	
	// Return if no memory has been allocated
	if ( target == NULL || source == NULL) {
		return NULL;		
	}
	
	// Pointer to the beginning of the target
	char *ptr = target;
	
	while (( *target++ = *source++) != NONE);
	
	// End the string with NUL
	*target = '\0';
	
	// Rewind target to original element
	target = ptr;
	
	return ptr;
}
// Function to initialize the stack
Stack *Stack_create(unsigned size) {
	
	Stack *new_stack = (Stack *)malloc(sizeof(Stack));
	
	if(new_stack == NULL){
		perror("Unable to allocate memory: new_stack \n");
		exit(1);
	}
	
	new_stack->array = (char **)malloc(size * sizeof(char*));
	new_stack->size = size;
	new_stack->index = -1;
	
	if(new_stack->array == NULL){
		perror("Unable to allocate memory: array \n");
		exit(1);
	}
	
	return new_stack;
	
}
// Chek if stack is empty
int Stack_is_empty(Stack *stack) {
	return (stack->index == -1);
}
// Check if stack is full
int Stack_is_full(Stack *stack) {
	return (stack->index == stack->size-1);
}
// Function to check the top value on the stacl
char *Stack_peek(Stack *stack) {
	if (!Stack_is_empty(stack)) {
		return stack->array[stack->index];
	}
	return NONE;
}
// Function to remove the latest appended value from the stack
char *Stack_pop(Stack *stack) {
	if (!Stack_is_empty(stack)) {
		return stack->array[stack->index--];
	}
	return NONE;
}
// Function to push a string into the stack
int Stack_push(Stack *stack, char *string) {
	
	if (!Stack_is_full(stack)) {
		// Move to next index
		stack->index++;
		
		// if element not initiated
		if (stack->array[stack->index] == NULL) {
			stack->array[stack->index] = malloc(MAX_STRING*sizeof(char));
		}
		// return operation outcome
		return copy_string(stack->array[stack->index],string) ? TRUE : FALSE;		
		
	}
	return 0;
}

// Function to free all the memory allocated by the stack
void Stack_free(Stack *stack) {
	int i = 0;
	// Free each string in array
	for ( i=0; i<stack->size; i++){
		free(stack->array[i]);
	}
	// Free pointer to strings
	free((*stack).array);
	
	// Free struct
	free(stack);

}
// function to reset the stack without freeing memory
void Stack_clear(Stack *stack){
	int i = 0;
	
	//Start all of the allocated strings with NUL
	for ( i=0; stack->array[i] != NULL && i<stack->size; i++){
		stack->array[i][0] = NONE;
	}
	stack->index = -1;
}

read_value
	
	
int main(){
	Stack *stack = Stack_create(MAX_SYMBOLS);
	printf("Push is successful:%d\n",Stack_push(stack,"-9"));
	printf("Push is successful:%d\n",Stack_push(stack,"-10"));
	printf("%s\n",Stack_pop(stack));
	printf("%s\n",Stack_pop(stack));
	Stack_free(stack);
	
	
}
		
	
	
	
	
	
	
	
	
	
	
