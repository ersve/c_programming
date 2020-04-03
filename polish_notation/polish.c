

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
// Function to convert a string number represenation to an integer
int to_int(char *string, int *integer){
	*integer = 0;
	if (string == NULL){
		perror("in function to_int: pointer is NULL\n");
		return 0;
	}
	
	if (*string == '-'){
		string++;
		while (*string){
			*integer = *integer * 10 + *string - '0';
			string++;
		}
		*integer = -*integer;
	}
	else{
		while (*string){
			*integer = *integer * 10 + *string - '0';
			string++;
		}
	}
	return 1;
}
// Function to convert an integer to a string number represenation
int to_string(char *string, int *integer){
	
	if (string == NULL){
		perror("in function to_string: pointer is NULL\n");
	return 0;
	
	// Handle 0 seperatly since (char) 0 = '\0'
	if(*integer == 0){
		*string++ = '0';
		*string = '\0';
		return 0;
	}
	
	
}
}

// Function to copy the contents from one string to another
char *copy_string(char *destination, char *target){
	
	// Return if no memory has been allocated
	if ( destination == NULL || target == NULL) {
		perror("in function copy_string: pointer is NULL\n");
		return NULL;		
	}
	
	// Pointer to the beginning of the destination
	char *ptr = destination;
	
	// Copy contents of target into source
	while (*destination++ = *target++);
	
	// End the string with NUL
	*destination = '\0';

	
	return ptr;
}

// Function to concatenate the target string into the source
char *concatenate_string(char *destination, char *target){
	
	// Return if no memory has been allocated
	if ( destination == NULL || target == NULL) {
		perror("in function concatenate_string: pointer is NULL\n");
		return NULL;		
	}
	
	char* ptr = destination;
	
	// Move to end of destination
	while (*destination){
		destination++;
		}
	
	// Copy contents of target into source
	while(*destination++ = *target++);
	
	// End the string with NUL
	*destination = '\0';
	
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
// Function to check the top value on the stack
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
			// Malloc failed
			if (stack->array[stack->index] == NULL){
				return FALSE;
			}
		}
		// return operation outcome
		return copy_string(stack->array[stack->index],string) ? TRUE : FALSE;		
		
	}
	return FALSE;
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
	

	
	while( *string ){
		switch(*(string++)){
			case '-':
				// return false if only  - sign
				if(*(string) == NONE){ 
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
				return FALSE;
		}
	}
	return TRUE;
}

int is_variable(char *string){

	while( *string ){
		
		if(*string == '-' && *string ){  }
		else if (*string >= 'a' && *string <= 'z') {  }
		else { return FALSE; }
		
		string++;
	}
	return TRUE;

}

int is_operator(char *string){
	
	while( *string ){
		switch(*(string++)){
			case '-':
			case '+':
			case '*':
			case '/':
				break;
			default:
				// return false if anything else
				return FALSE;
		}
	}
	return TRUE;
}

int read_next(char * element){
	char read_char;
	//keep reference
	char *expression = element;
	while (TRUE) {		
			
		read_char = getc(stdin);
		
		if(read_char == '\n' || read_char == NONE || read_char == ' ') { //done parsing the expression
			
			// end the current expression
			*expression = NONE;
			break;			
		}
		else { // Add the current char to the expression
			*(expression++) = read_char;			
			
		}				
	}
				
	// Line is done
	if (read_char =! ' '){
		return 0;
	}

	//else 
	return 1;
}

void parse_prefix(){
	char *output = (char*)malloc(MAX_SYMBOLS*sizeof(char)+1);
	*output = NONE;
	Stack *input = Stack_create(MAX_SYMBOLS);
	Stack *queue = Stack_create(MAX_SYMBOLS);
	
	// Element read
	char *read_str;
	// First argument
	char *char_arg1;
	int int_arg1 = 0;
	
	// Second argument
	char *char_arg2 = 0;
	int int_arg2;
	
	// Operand
	char *op;
	
	// Read into stack
	while(TRUE){
		int_arg1 = read_next(read_str);
		if (!Stack_push(input,read_str)){
			perror("Unable to push into stack");
			exit(1);
		}
		else if (int_arg1){
			break;
		}			
		
	}
	
	// Parse prefix
	while(!Stack_is_empty(input)){
		if(is_operator(Stack_peek(input))){
			op = Stack_pop(input);
			char_arg1 = Stack_pop(queue);
			char_arg2 = Stack_pop(queue);
			
			if (is_variable(char_arg1) || is_variable(char_arg2) ){
				switch(*op){
					case '+':
					case '-':
					case '*':
					case '/':
						concatenate_string(concatenate_string(concatenate_string(output,op),char_arg1),char_arg2);
						break;
					default:
						perror("Undefined operator!\n");
						exit(1);
				}
			}
			else if (is_number(char_arg1) || is_number(char_arg2) ){
				if( !(to_int(char_arg1,&int_arg1) && to_int(char_arg2,&int_arg2)) ){
					perror("Failed to convert char to int!");
					exit(1);
				}
				
				switch(*op){
					
					case '+':
					
						break;
					case '-':
					
						break;
					case '*':
					
						break;
					case '/':
						
						break;
					default:
						perror("Undefined operator!\n");
						exit(1);
				}
			}		
		}
		else {		
			if (!Stack_push(queue,Stack_pop(input))){
			perror("Unable to push into stack");
			exit(1);
			}
		}
	}
}

void main(){



}	
	

		
	
	
	
	
	
	
	
	
	
	
