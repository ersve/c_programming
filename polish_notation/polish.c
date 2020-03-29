

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

int is_number(char *string){
	
	//keep track of reference
	char *ptr = string;
	
	while( *string != NONE ){
		switch(*(string++)){
			case '-':
			case '+':
				// return false if only + or - sign
				if(*(string) == NONE){ 
					string = ptr;
					return FALSE; 
				}
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				break;
			default:
				// return false if anything else
				string = ptr;
				return FALSE;
		}
	}
	string = ptr;
	return TRUE;
}

void populate(Stack *stack){
	char read_char;
	char expression_array[MAX_STRING];
	char *expression = &expression_array[0];

	
	while (TRUE) {
				
		read_char = getc(stdin);
		
		if(read_char == '\n' || read_char == NONE || read_char == ' ') { //done parsing the expression
			
			// Push the current expression
			*expression = NONE;
			expression = &expression_array[0];
			Stack_push(stack,expression);
			
			// Line is done
			if (read_char == '\n' || read_char == NONE){
				break;
			}
			
		}
		else { // Add the current char to the expression
			*(expression++) = read_char;			
			
		}
					
	}
}

int main(){
	/*Stack *stack = Stack_create(MAX_SYMBOLS);
	populate(stack);
	while (!Stack_is_empty(stack)){
		printf("%s",Stack_pop(stack));
	}
	printf("\n");
	Stack_free(stack); */
	

}	
	

		
	
	
	
	
	
	
	
	
	
	
