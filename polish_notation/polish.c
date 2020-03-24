

#include <stdio.h> 
#include <stdlib.h>


#define MAX_SYMBOLS 2048
#define MAX_INT 10
#define TRUE 1
#define FALSE 0
#define NONE '\0'

int TYPE_INT = 0;
int TYPE_STRING = 1;
int TYPE_BOOLEAN = 2;
int TYPE_PERSON = 3;


// Linked node
struct Node {
	char data;
	struct Node *next;
	struct Node *prev;
};
typedef struct Node Node;

// struct to hold properties of the list
struct List {
	unsigned length;
	Node *head;
	Node *tail;
};
typedef struct List List;

void init(List *list) {
	list->length = 0;
	list->head = NULL;
	list->tail = NULL;
}

int isempty(List *list){
	return (list->tail == NULL);
}

void clean(List *list){
	Node *removed_node; 
	while(!isempty(list)){		
		// appoint first node to temporary pointer
		removed_node = list->head;
		// if we are at the final node move tail poiner to the node pointed out by the first
		if (list->head == list->tail){
			list->tail = list->tail->next; //should be NULL
		}
		// move head poiner to the node pointed out by the first
		list->head = list->head->next;
		// decrease list length
		list->length--;
		// free memory allocated by node
		free(removed_node);		
	}
	// remove pointer address	
	removed_node = NULL;
}


void push(List *list, char data ) {
	Node *new_node;
	
	//Create a new node and populate it with data
	new_node = (Node*)malloc(sizeof(Node));
	if(new_node == NULL) {
		fprintf(stderr,"ERROR:Unable to allocate memory");
		clean(list);
		exit(1);
	}
	else {
		new_node->data = data;
		new_node->next = NULL;
	}
	
	
	if (!isempty(list)){ 
		//Insert the node in the list
		list->tail->next = new_node;
		list->tail=new_node;
	}
	else { 
		// first element of the list
		list->head = new_node;
		list->tail = new_node;
	}
	list->length++;
	new_node = NULL;
			
}

void pop(List *list, char *data) {
	// create temporary node pointer
	if (!isempty(list)){
		Node *removed_node; 
		// retreive data
		*data = list->head->data;
		// appoint first node to temporary pointer
		removed_node = list->head;
		// if we are at the final node move tail poiner to the node pointed out by the first
		if (list->head == list->tail){
			list->tail = list->tail->next; // should be NULL
		}
		// move head poiner to the node pointed out by the first
		list->head = list->head->next;
		// decrease list length
		list->length--;
		// free memory allocated by node
		free(removed_node);
		// remove pointer address
		removed_node = NULL;
		
	}
	else {
		*data = NONE;
	}
}

void peak(List *list, char *data){
	if (!isempty(list)){
		*data =  list->head->data;
	}
	else {
		*data = NONE;
	}
}

char *toArray(List *list){
	int i;
	char *ptr;
	Node *prnt;
	
	ptr = (char*)malloc((list->length+1)*sizeof(char));	
	if(ptr == NULL) {
		fprintf(stderr,"ERROR:Unable to allocate memory");
		clean(list);
		exit(1);
	}
	
	prnt = list->head;
	for(i = 0; i<list->length; i++){
		*(ptr+i) = prnt->data;
		prnt = prnt->next;
	}
	*(ptr+i) = NONE;
	return ptr;
}

void printL(List *list){
	char *ptr = toArray(list);
	if(list->length >0){
		printf("%s\n",ptr);
	}
	free(ptr);
}

int isNumber(char data){
	return ( data >= 40 && data <= 57);
	}
	
int isOperator(char data){
	switch(data){
		case '+':
		case '-':
		case '*':
		case '/':
			return 1;
			break;
		default:
			return 0;
		}
	}
	
int parse_int(List *list){
	char data;
	int i = 0;
	char intArr[3];
	char *pIntArr = &intArr[0];
	peak(list,&data);
	while(isNumber(data)){
		pop(list,(pIntArr+i));
		peak(list,&data);
		i++;
	}
	*(pIntArr+i) = NONE;
	return atoi(pIntArr);
}
	
	

int main(){
	
	List *input, *output;
	char data;
	int d;
	input = malloc(sizeof(List));
	output = malloc(sizeof(List));
	init(input);
	init(output);
	/*
	while(TRUE){
		
		if(feof(stdin)){break;}
		
		// Read line into list
		while(TRUE){
			data = getchar();
			if (data == EOF || data == '\n'){
				break;
			}
			else {
				push(input,data);
			}

		}
		
		// Parse and simplify
		
		
		// print list onto stdout
	}
	free(input);
	*/
	
	push(input,'9');
	push(input,'-');
	push(input,'2');
	d = parse_int(input);
	printf("%d\n",d);
	
} // end of main
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
