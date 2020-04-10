
#include <stdio.h> 
#include <stdlib.h>


#define MAX_SYMBOLS 2048
#define MAX_STRING 10
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
int to_string(char *string, int integer){
	
	int digits = 0;
	int number = integer;
	int rem = 0;

	
	if (string == NULL){
		perror("in function to_string: pointer is NULL\n");
		return 0;
	}
	
	if(integer < 0){
		*string++ = '-';
		integer *= -1;
	}
	
	
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
	
	*(string+digits) = '\0';
	return 1;
	
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
// returns the number of appended characters
int concatenate_string(char *destination, char *target){
	int appended = 0;
	// Return if no memory has been allocated
	if ( destination == NULL || target == NULL) {
		perror("in function concatenate_string: pointer is NULL\n");
		return appended;		
	}
	
	char* ptr = destination;
	
	// Move to end of destination
	while (*destination){
		destination++;
		}
	
	// Copy contents of target into source
	while(*destination++ = *target++){
		appended++;
	}
	
	// End the string with NUL
	*destination = '\0';
	
	return appended;
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
	return NULL;
}
// Function to remove the latest appended value from the stack
int Stack_pop(Stack *stack, char *string) {
	if (!Stack_is_empty(stack)) {
		return copy_string(string,stack->array[stack->index--]) == NULL;
	}
	return 1;
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
				return 1;
			}
		}
		// return operation outcome
		return copy_string(stack->array[stack->index],string) != NULL ? 0 : 1;		
		
	}
	return 1;
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
// Function that checks if the input string is a number
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
			return 0;
		}
		
	}
	return 1;
}
/*
// Function that pops the content of a stack to a string
char *Stack_to_string(Stack *stack,char *string){
	*string = '\0'; //overwrite old string
	while(!Stack_is_empty(stack)){
		concatenate_string(string,Stack_pop(stack));
		if(Stack_peek(stack) != NULL){
			concatenate_string(string," ");
		}
		else{
			concatenate_string(string,"\n");
		}
	}
	return string;
}
*/

void Stack_print(Stack *stack){
	int i;
	for (i = 0; i<stack->index+1; i++) {
		printf("%s ", stack->array[i]);
	}
	printf("\n");
}
// Function that parse one "Symbol" from the stdin
char read_next(char * element){
	char read_char;
	//keep reference
	char *expression = element;
	while (TRUE) {		
			
		read_char = getchar();
		
		
		if(read_char == '\n' || feof(stdin) || read_char == ' ' || read_char == 0 ) { //done parsing the expression
			
			// end the current expression
			*expression = NONE;
			break;			
		}
		else { // Add the current char to the expression
			*(expression++) = read_char;			
			
		}				
	}
				
	// Line is done
	if (read_char != ' ' ){
		return 1;
	}
	else{
		return 0;
	}
}
// Function that reads in one prefix expression into the stack
Stack *Stack_read_stdin(Stack *stack){

	int proceed=0;
	char array[MAX_STRING];
	char *read_str = (char *)malloc(MAX_STRING*sizeof(char));
	
	if (read_str == NULL){
		perror("Failed to allocate memory");
		exit(1);
	}
		
	// Read into stack
	while(TRUE){
		proceed = read_next(read_str);
		//printf("read_str:%s\n",read_str);
		//printf("proceed:%d\n",proceed);
		if (Stack_push(stack,read_str)){
			perror("Unable to push into stack");
			exit(1);
		}
		if (proceed == 1){
			break;
		}			
		
	}
	free(read_str);
	return stack;
}

// Function that parses and simplifies a prefix expression stored in a Stack
void parse_prefix(Stack *stack, char *result ){
	// internal stack
	Stack *queue = Stack_create(MAX_SYMBOLS);
	char *track = result;
	int test = 0;
	// First argument
	char *char_arg1 = (char *)malloc(MAX_STRING*sizeof(char));
	int int_arg1 = 0;
	
	// Second argument
	char *char_arg2 = (char *)malloc(MAX_STRING*sizeof(char));
	int int_arg2 = 0;
	
	// Operand
	char *op = (char *)malloc(MAX_STRING*sizeof(char));
	
	// Result of calculation
	char *res = (char *)malloc(MAX_STRING*sizeof(char));
	
	while(!Stack_is_empty(stack)){
		printf("loop: %d\n",test++);
		printf("Stack content: ");
		Stack_print(stack);
		printf("queue content: ");
		Stack_print(queue);
		printf("Result: %s\n",track);
		if(is_operator(Stack_peek(stack))){
			printf("in Operator\n");
			if (Stack_pop(stack,op)){
				printf("Failed to pop to op\n");
			}
			printf("op: %s\n",op);
			
			if (Stack_pop(queue,char_arg1)){
				printf("Failed to pop to char_arg1\n");
			}
			printf("char_arg1: %s\n",char_arg1);
			
			if (Stack_pop(queue,char_arg2)){
				printf("Failed to pop to char_arg2\n");
			}
			printf("char_arg2: %s\n",char_arg2);
			
			if (is_variable(char_arg1) || is_variable(char_arg2) ){
				switch(*op){
					case '+':
					case '-':
					case '*':
					case '/':
						
						
						//if(Stack_push(queue,char_arg1)){
						//	printf("Failed to push char_arg1:%s\n",char_arg1);
						//}
						//printf("char_arg1: Stack got %s when pushed %s\n",Stack_peek(queue),char_arg1);
						result += concatenate_string(result,char_arg1)-1;
						result += concatenate_string(result," ")-1;
						
						//if(Stack_push(queue,char_arg2)){
						//	printf("Failed to push char_arg1:%s\n",char_arg2);
						//}
						//printf("char_arg2: Stack got %s when pushed %s\n",Stack_peek(queue),char_arg2);
						result += concatenate_string(result,char_arg2)-1;
						result += concatenate_string(result," ")-1;
						
						//if(Stack_push(queue,op)){
						//	printf("Failed to push op:%s\n",op);
						//}
						//printf("op: Stack got %s when pushed %s\n",Stack_peek(queue),op);
						result += concatenate_string(result,op)-1;
						result += concatenate_string(result," ")-1;
						printf("Result: %s\n",track);
						break;
					default:
						perror("Undefined operator!\n");
						exit(1);
				}
			}
			else if (is_number(char_arg1) && is_number(char_arg2) ){
				
				if( !(to_int(char_arg1,&int_arg1) && to_int(char_arg2,&int_arg2)) ){
					perror("Failed to convert char to int!");
					exit(1);
				}
				
				switch(*op){
					
					case '+':
						
						to_string(res, int_arg1 + int_arg2);
						Stack_push(queue,res);
						
						break;
					case '-':
						to_string(res, int_arg1 - int_arg2);
						Stack_push(queue,res);
						break;
					case '*':
						to_string(res, int_arg1 * int_arg2);
						Stack_push(queue,char_arg1);
						break;
					case '/':
						to_string(res, int_arg1 / int_arg2);
						Stack_push(queue,res);
						break;
					default:
						perror("Undefined operator!\n");
						exit(1);
				}
			}
			else{
				printf("why do i get here?");
			}		
		}
		else {		
			Stack_pop(stack,res);
			if (Stack_push(queue,res)){
			perror("Unable to push into stack");
			exit(1);
			}
		}
	}
	Stack_pop(queue,res);
	result += concatenate_string(result,res);
    result += concatenate_string(result,"\n");
    *(result+1) = '\0';
    
    
	free(char_arg1);
	free(char_arg2);
	free(op);
	free(res);
	Stack_free(queue);
	printf("Result: %s\n",result);
}


void test();

void main(){

	Stack *stack = Stack_create(MAX_SYMBOLS);
	char array[2*MAX_SYMBOLS];
	char *string = &array[0];
	char test;
	

	

	while(TRUE){
		if(feof(stdin)){ break;}
		Stack_read_stdin(stack);
		parse_prefix(stack,string);
		
		
	}
	


	

	

Stack_free(stack);



/*
	while(!Stack_is_empty(stack)){
		printf("%s ",Stack_pop(stack));
	}
	
Stack_free(stack);
* 
* 	printf("queue: ");
	while(!Stack_is_empty(queue)){
		printf("%s ",Stack_pop(queue));
	}
	printf("\n");
	printf("stack: ");
	while(!Stack_is_empty(stack)){
		printf("%s ",Stack_pop(stack));
	}
	printf("\n");
*/
}	

	

		
/*	
	
void test(){
		//Test to_int
	printf("Testing to_int:\n");
	int test1_int;
	to_int("-100",&test1_int);
	
	if (test1_int == -100){
		printf("Test (1/3) : success\n");
	}
	else { 
		printf("Test (1/3) : failiure\n");
		}
		
	to_int("0",&test1_int);	
	if (test1_int == 0){
		printf("Test (2/3) : success\n");
	}
	else { 
		printf("Test (2/3) : failiure\n");
		}
		
	to_int("100",&test1_int);	
	if (test1_int == 100){
		printf("Test (3/3) : success\n");
	}
	else { 
		printf("Test (3/3) : failiure\n");
		}
	
	//test is_equal
	printf("Testing is_equal:\n");
	char *str1 = "equal";
	char *str2 = "equal";
	char *str3 = "equa";
	char *str4 = "diffe";
	if (is_equal(str1,str2)){
		printf("Test (1/4) : success\n");
	}
	else { 
		printf("Test (1/4) : failiure\n");
	}
		
	if (!is_equal(str2,str3)){
		printf("Test (2/4) : success\n");
	}
	else { 
		printf("Test (2/4) : failiure\n");
	}
	if (!is_equal(str1,str3)){
		printf("Test (3/4) : success\n");
	}
	else { 
		printf("Test (3/4) : failiure\n");
		}
	if (!is_equal(str1,str4)){
		printf("Test (4/4) : success\n");
	}
	else { 
		printf("Test (4/4) : failiure\n");
		}
	
	
	//Test to_string
	printf("Testing to_string:\n");
	
	char test2[10];
	char res2[10];
	char *test2_str = &test2[0];
	char *res2_str = &res2[0];
	copy_string(res2_str,"-10");
	to_string(test2_str,-10);
	if (is_equal(test2_str,res2_str)){
		printf("Test (1/3) : success\n");
	}
	else { 
		printf("Test (1/3) : failiure\n");
	}
		
	copy_string(res2_str,"0");		
	to_string(test2_str,0);	
	if (is_equal(test2_str,res2_str)){
		printf("Test (2/3) : success\n");
	}
	else { 
		printf("Test (2/3) : failiure\n");
		}
	copy_string(res2_str,"10");	
	to_string(test2_str,10);	
	if (is_equal(test2_str,res2_str)){
		printf("Test (3/3) : success\n");
	}
	else { 
		printf("Test (3/3) : failiure\n");
		}
	
	
	//test copy_string
	
	printf("Testing copy_string:\n");
	char *test3= "testar1";
	char result[10];
	char * result3 = &result[0];
	copy_string(result3,test3);
	if (is_equal(result3,test3)){
		printf("Test (1/1) : success\n");
	}
	else { 
		printf("Test (1/1) : failiure\n");
		}
	
	
	//test concatenate_string
	printf("Testing concatenate_string:\n");
	char testv4[10]={'\0'};
	char resultv4[10]={'\0'};
	char *test4 = &testv4[0];
	char *result4 =&resultv4[0];
	concatenate_string(test4,"");
	if (is_equal(result4,test4)){
		printf("Test (1/3) : success\n");
	}
	else { 
		printf("Test (1/3) : failiure\n");
		}
	concatenate_string(test4,"lol");
	copy_string(result4,"lol");
	if (is_equal(result4,test4)){
		printf("Test (1/3) : success\n");
	}
	else { 
		printf("Test (1/3) : failiure\n");
		}
	concatenate_string(test4,"lol");
	copy_string(result4,"lollol");	
	if (is_equal(result4,test4)){
		printf("Test (1/3) : success\n");
	}
	else { 
		printf("Test (1/3) : failiure\n");
		}
	
	//test is_number
	printf("Testing is_number:\n");
	if(is_number("10")){
		printf("Test (1/4) : success\n");
	}
	else { 
		printf("Test (1/4) : failiure\n");
		}
		
	if(is_number("-10")){
		printf("Test (2/4) : success\n");
	}
	else { 
		printf("Test (2/4) : failiure\n");
		}
	if(!is_number("a")){
		printf("Test (3/4) : success\n");
	}
	else { 
		printf("Test (3/4) : failiure\n");
	}
	if(!is_number("4a")){
		printf("Test (4/4) : success\n");
	}
	else { 
		printf("Test (4/4) : failiure\n");
		}
	
	//test is_operator
		printf("Testing is_operator:\n");
	if(is_operator("+")){
		printf("Test (1/4) : success\n");
	}
	else { 
		printf("Test (1/4) : failiure\n");
		}
		
	if(is_operator("-")){
		printf("Test (2/4) : success\n");
	}
	else { 
		printf("Test (2/4) : failiure\n");
		}
	if(!is_operator("a")){
		printf("Test (3/4) : success\n");
	}
	else { 
		printf("Test (3/4) : failiure\n");
	}
	if(!is_operator("4")){
		printf("Test (4/4) : success\n");
	}
	else { 
		printf("Test (4/4) : failiure\n");
		}
	
	//test is_variable
	printf("Testing is_variable:\n");
	if(!is_variable("10")){
		printf("Test (1/4) : success\n");
	}
	else { 
		printf("Test (1/4) : failiure\n");
		}
		
	if(!is_variable("-10")){
		printf("Test (2/4) : success\n");
	}
	else { 
		printf("Test (2/4) : failiure\n");
		}
	if(is_variable("a")){
		printf("Test (3/4) : success\n");
	}
	else { 
		printf("Test (3/4) : failiure\n");
	}
	if(is_variable("z")){
		printf("Test (4/4) : success\n");
	}
	else { 
		printf("Test (4/4) : failiure\n");
	}
	
	//test Stack_create
	printf("Testing Stack_create:\n");
	Stack *stack_test = Stack_create(1);
	if( stack_test != NULL){
		printf("Test (1/1) : success\n");
	}
	else { 
		printf("Test (1/1) : failiure\n");
	}
	
	//test Stack_push
	printf("Testing Stack_push:\n");
	if( Stack_push(stack_test,"test")){
		printf("Test (1/2) : success\n");
	}
	else { 
		printf("Test (1/2) : failiure\n");
	}
	
		if(!Stack_push(stack_test,"test")){
		printf("Test (2/2) : success\n");
	}
	else { 
		printf("Test (2/2) : failiure\n");
	}	
	
	//test Stack_pop
	char char_test[MAX_STRING];
	printf("Testing Stack_pop:\n");
	if( is_equal(Stack_pop(stack_test,&char_test[0]),"test")){
		printf("Test (1/2) : success\n");
	}
	else { 
		printf("Test (1/2) : failiure\n");
	}
	

	if( Stack_pop(stack_test,&char_test[0]) == NULL){
		printf("Test (1/2) : success\n");
	}
	else { 
		printf("Test (1/2) : failiure\n");
	}
		
	//test Stack_peek
	printf("Testing Stack_peek:\n");	
	if( Stack_peek(stack_test) == NULL){
		printf("Test (1/2) : success\n");
	}
	else { 
		printf("Test (1/2) : failiure\n");
	}
	Stack_push(stack_test,"test");
	
	if( is_equal(Stack_peek(stack_test),"test")){
		printf("Test (2/2) : success\n");
	}
	else { 
		printf("Test (2/2) : failiure\n");
	}
	
}	
	
*/	
	
	
	
	
	
