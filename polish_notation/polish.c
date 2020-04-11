
#include <stdio.h> 
#include <stdlib.h>

#define MAX_SYMBOLS 2049
#define TRUE 1
#define FALSE 0
#define END_OF_STRING '\0'

// A struct to keep the contents and meta information about the stack
struct LIFO {
	char **array;
	ssize_t index;
	size_t size;
};

typedef struct LIFO Stack;
// Function to convert a string number represenation to an integer
ssize_t to_int(char *string, int *integer){
	*integer = 0;
	if (string == NULL){
		perror("in function to_int: pointer is NULL\n");
		return FALSE;
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
	return TRUE;
}
// Function that returns the length of a string, excluding string terminator
ssize_t length_string(char *string){
	size_t length = 0;
	if (string == NULL){
		return -1;
	}
	while (*(string + length++));
	return length;	
}
// Function to convert an integer to a string number represenation
ssize_t to_string(char *string, int integer){
	
	int digits = 0;
	int number = integer;
	int rem = 0;

	
	if (string == NULL){
		perror("in function to_string: pointer is NULL\n");
		return FALSE;
	}
	// Append '-' if number is negative
	if(integer < 0){
		*string++ = '-';
		integer *= -1;
	}
	
	// Calculate the number of digits
	while(TRUE){		
		digits++;
		if(number /= 10){}
		else {break;}
	}
	
	for( number = 0; number < digits ; number++ ){		
		rem = integer % 10;
        integer = integer / 10;
        *(string + digits - (number + 1)) = rem + '0';
	}
	
	*(string+digits) = END_OF_STRING;
	return TRUE;
	
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
	*destination = END_OF_STRING;

	
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
	
	// End the string with NULL
	*destination = END_OF_STRING;
	
	return ptr;
}

// Function that parses the string back to front. Each call one of the elements
// of the string will be parsed and returned through the substring pointer. 
// all of the elements will reside in *string so that is the ptr that shall be freed
// returns if string is at an end after previous call
int parse_string(char *string, size_t length, char **substring, ssize_t *offset){
	length = length - *offset -1 ;
	
	for (length; length > 0; length--){
		*offset += 1;
		if (*(string+length) == '\n'){
			*(string+length) = END_OF_STRING;
		}
		else if (*(string+length) == ' '){
			*(string+length) = END_OF_STRING;
			*substring = string+length+1;
			return FALSE;
		}
		
	}
	*substring = (string);
	return TRUE;
}

// Function to initialize the stack
Stack *Stack_create(size_t size) {
	
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
	return NULL;
}
// Function to remove the latest appended value from the stack
// returns success of operation
int Stack_pop(Stack *stack, char *string) {
	if (!Stack_is_empty(stack)) {
		return copy_string(string,stack->array[stack->index--]) != NULL;
	}
	return FALSE;
}
// Function to push a string into the stack
// returns success of operation
int Stack_push(Stack *stack, char *string) {
	
	size_t length = length_string(string);
	char *tmp;
	
	if (!Stack_is_full(stack)) {
		
		// Move to next index
		stack->index++;
		
		// if element not initiated
		if (stack->array[stack->index] == NULL) {
			//printf("allocating memory...");
			stack->array[stack->index] = (char *)malloc(length*sizeof(char)+1);
			// nalloc failed
			if (stack->array[stack->index] == NULL){
				return FALSE;
			}
			//printf("Sucess!\n");
		}
		// current array is too small
		else if (length_string(stack->array[stack->index]) < length ){
			//printf("Reallocating memory...");
			
			//allocate new bigger
			stack->array[stack->index] = (char *)realloc(stack->array[stack->index],length*sizeof(char)+1);
			// nalloc failed
			if (stack->array[stack->index] == NULL){
				return FALSE;
			}
			//printf("Sucess!\n");
			
		}
		
		// return operation outcome
		return copy_string(stack->array[stack->index],string) != NULL ? TRUE : FALSE;		
		
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
	stack->index = -1;
}
// Function that checks if the input string is a number
int is_number(char *string){
		
	while( *string ){
		switch(*(string++)){
			case '-':
				// return false if only  - sign
				if(*(string) == END_OF_STRING){ 
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
// Function to check if the input string is a variable(small letter)
int is_variable(char *string){

	while( *string ){
		
		if(*string == '-' && *(string+1)){  }
		else if (*string >= 'a' && *string <= 'z') {  }
		else { return FALSE; }
		
		string++;
	}
	return TRUE;

}
// Function to check if the input string is a mathematical operator
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
// Function that assesses if two strings have the same content
int is_equal(char *string1, char* string2){
	while( *string1 || *string2 ){
		if(*string1++ != *string2++){
			return FALSE;
		}
		
	}
	return TRUE;
}

void Stack_print(Stack *stack){
	int i;
	for (i = 0; i<stack->index; i++) {
		printf("%s ", stack->array[i]);
	}
	printf("%s\n", stack->array[i]);
}
// pops the entire stack to a string
void Stack_to_string(Stack *stack,char *string){
	int i;
	int success = 1;
	for (i = 0; i<stack->index+1; i++) {
		if(!Stack_pop(stack,string)){
			printf("Stack_to_string: failed to pop from stack!\n");
			success = 0;
		}
		string += length_string(string);
		*string = ' ';		
	}
}

void parse_prefix(char *prefix,size_t size_prefix, Stack *stack){

	ssize_t offset = 0; 										// used for backwards parsing
	int is_end = 0; 											// boolean if string has ended 
	char *c_arg1 = (char *)malloc(size_prefix*sizeof(char)+1);	// string representation of variable 1
	int arg1;													// integer representation of variable 1
	char *c_arg2 = (char *)malloc(size_prefix*sizeof(char)+1);	// string representation of variable 2	
	int arg2; 													// integer representation of variable 2
	char *element = NULL; 										// No need to malloc since it points to prefix string
	char *res = (char *)malloc(size_prefix*sizeof(char)+1);		// string to store result from calculation
	
		
		while(TRUE){
		is_end = parse_string(prefix,size_prefix,&element,&offset);
		
		if (is_operator(element)){

			if(!Stack_pop(stack,c_arg1)){
				printf("failed to pop c_arg1 from stack!\n");
				exit(1);
			 }

			if(!Stack_pop(stack,c_arg2)){
				printf("failed to pop c_arg2 from stack!\n");
				exit(1);
			}

			// if both args are int, perform numeric operation
			if ( is_number(c_arg1) && is_number(c_arg2) ) {
				to_int(c_arg1,&arg1);
				to_int(c_arg2,&arg2);
				
				switch(*element){
					case '+':
						to_string(res, arg1 + arg2);				
						break;
					case '-':
						to_string(res, arg1 - arg2);
						break;
					case '*':
						to_string(res, arg1 * arg2);
						break;
					case '/':
						to_string(res, arg1 / arg2);

						break;
					default:
						printf("Undefined operator '%c'\n",*element);
						break;
				}

			}			
			else {				
				// otherwise concatenate (operator) (variable1) (variable 2)
				concatenate_string(concatenate_string(concatenate_string(concatenate_string(copy_string(res,element)," "),c_arg1)," "),c_arg2);

			}
			//push result of calculations to the stack
			if (!Stack_push(stack,res)){
					printf("failed to push %s to stack!\n",res);
					exit(1);
				}
			
		}
		else {
			// push variable from string to stack
			if (!Stack_push(stack,element)){
				printf("failed to push %s to stack!\n",res);
				exit(1);
			}
		}		
		if (is_end) break;	
	}
	free(c_arg1);
	free(c_arg2);
	free(res);		
}

void main(){
Stack *stack = Stack_create(2*MAX_SYMBOLS/3);
char *prefix = NULL; // prefix expression to be allocated in getline


size_t len = 0;
ssize_t size_prefix;
size_t nr = 1;

while ((size_prefix = getline(&prefix, &len , stdin)) != -1) {
	parse_prefix(prefix,size_prefix,stack);
	Stack_to_string(stack,prefix);
	printf("Case %lu: %s\n",nr++,prefix);
	
}
Stack_free(stack);
free(prefix);
exit(0);	
}	

	
	
