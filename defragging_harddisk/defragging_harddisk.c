#include <stdio.h>
#include <stdlib.h>


#define DISK_DATABLOCK_MAX 80
#define EMPTY '.'
#define OCCUPIED '*'
#define END_OF_ROW '\n'

int main() {
	char datapoint; // temporary variable to store the read character
	char data[DISK_DATABLOCK_MAX+1]; //+2 for newline and termination
	char *pData;
	int size = 0; // number of datablocks on current diskmap
	int used = 0; // numer of occiped blocks on current diskmap
	int total = 0; // total occipoed diskblocks
	int i;
	
	pData = &data[0];


	while(1) {
		
		/* Get data from stdin */
		datapoint = getchar();
		if(feof(stdin)){break;}
		
		/* If empty, only increment array size */
		if(datapoint == EMPTY){
			size += 1;
		}
		/* Also increment number of occupied files */	
		else if(datapoint == OCCUPIED){
			size += 1;
			used += 1;
			
		}	
		else if(datapoint == END_OF_ROW){			
			/* add "OCCUPIED" in the interval [size-total-used , size-total) in the array */
			for (i = 0; i<size ; i++){
				if ( i>=(size-total-used ) && i<(size-total)){
					*(pData+i) = OCCUPIED;
				}
				else {
					*(pData+i) = EMPTY;
				}
				
			}
			/* Add new line and termination character so that printf knows where to stop */
			*(pData+i) = END_OF_ROW;
			*(pData+i+1)= '\0';
			
			printf("%s",data);
			
			
			if (size > 0) {
				total += used;
			}
			/* reset all for new matrix if a blank line if found */
			else{
				total = 0;
			}
			used = 0;
			size = 0;		

		}
		else {
			fprintf(stderr, "Error: Undefined character in disk map");
			return(1);
		}
	}
return(0);
}

		
