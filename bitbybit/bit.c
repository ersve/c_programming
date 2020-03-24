#include <stdio.h>
#include <string.h>

#define REGISTER_LENGTH 32
#define COMMAND_LENGHT 10

/* Global Variable Declarations */

	//register of data
	unsigned int data = 0;
	unsigned int *pData = &data;	
	
	//register of knowledge status (1) known, (0) unknown
	unsigned int status = 0;
	unsigned int *pStatus = &status;
	
	//register used for print
	char result[REGISTER_LENGTH +1];
	char *pResult = &result[0];
		
/* Function Declarations */
	
unsigned int check_bit( unsigned int *pRegister,  unsigned int index){
	return *pRegister & 1<<index;
}

void set_bit( unsigned int *pRegister,  unsigned int index){
	*pRegister |= 1 << index;
}

void clear_bit( unsigned int *pRegister, unsigned int index){
	*pRegister &= ~(1 << index);
}

void and_bit( unsigned int *pRegister,  unsigned int index1,  unsigned int index2){
     unsigned int bit1 =*pRegister&(1 << index1);
	 unsigned int bit2 =*pRegister&(1 << index2);
	*pRegister = (*pRegister & (~(1 << index1))) | ((bit1&&bit2) << index1);
}
	
void or_bit( unsigned int *pRegister,  unsigned int index1, unsigned int index2){
     unsigned int bit1 =*pRegister&(1 << index1);
	 unsigned int bit2 =*pRegister&(1 << index2);
	*pRegister = (*pRegister & (~(1 << index1))) | ((bit1||bit2) << index1);
}

unsigned int is_set( unsigned int index){
	return check_bit(pStatus,index) & check_bit(pData,index);
}

unsigned int is_clear( unsigned int index){
	return check_bit(pStatus,index) & ~check_bit(pData,index);
}

void unknown(unsigned int index){
	clear_bit(pData,index);
	clear_bit(pStatus,index);
}

void set( unsigned int index){
	set_bit(pData, index);
	set_bit(pStatus,index);
}

void clear( unsigned int index){
	clear_bit(pData,index);
	set_bit(pStatus,index);
	
}

void and( unsigned int index1,  unsigned int index2){
	if (is_set(index1) && is_set(index2)){
		set(index1);
	}

	else if (is_clear(index1) || is_clear(index2)){
		clear(index1);
	}	
	else {
		unknown(index1);
	}
}

void or( unsigned int index1,  unsigned int index2){
	if (is_set(index1) || is_set(index2)){
		set(index1);
	}
	else if (is_clear(index1) && is_clear(index2)){
		clear(index1);
	}
	else {
		unknown(index1);
	}
	
}

int main(){
	//counters
	int i,j;	

    //String to store the command in
    char command[COMMAND_LENGHT];
    char *pCommand = &command[0];
    
	//Arguments
	int arg1, arg2, inputs;
	int *pArg1 = &arg1;
	int *pArg2 = &arg2;
	int *pInputs= &inputs;
	
	while (1) {
		
		if (feof(stdin)){
			break;
		}
		//get number of commands that will follow
		scanf("%d", pInputs);
		
		if (*pInputs) {
			for(i=0;i<*pInputs;i++){
				// Read the command
				scanf("%s",pCommand);
				
				/* SET */
				if( strcmp(pCommand,"SET") == 0 ) {
					scanf(" %d",pArg1);
					set(*pArg1);	
		
				}
				/* CLEAR */
				else if( strcmp(pCommand,"CLEAR") == 0 ){
					scanf(" %d",pArg1);
					clear(*pArg1);
			
				}
				/* AND */
				else if( strcmp(pCommand,"AND") == 0 ){
					scanf(" %d %d",pArg1,pArg2);
					and(*pArg1,*pArg2);
				}
				/* OR */							
				else if( strcmp(pCommand,"OR") == 0 ){
					scanf(" %d %d",pArg1,pArg2);
					or(*pArg1,*pArg2);
		
				}				
				/* Default */
				else {			
					fprintf(stderr, "Error: Undefined command '%s'\n",pCommand);				
					return(1);
				}		
			
			}
			
			for(j = 0; j < REGISTER_LENGTH ; j++){

				if (check_bit(pStatus,j)) {
					*(pResult - j + REGISTER_LENGTH -1 ) = check_bit(pData,j) ? '1' : '0' ;
				}
				else {
					*(pResult - j + REGISTER_LENGTH -1) = '?';
				}
			}
			printf("%s\n",pResult);
			*pData = 0;
			*pStatus = 0;
		}
	}	
	
return 0;
}


