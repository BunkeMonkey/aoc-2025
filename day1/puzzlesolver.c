#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main(){

	int dial_position = 50;
	int zero_counter = 0;
	int zero_intermittent_hits = 0;
	FILE* fileptr;

	fileptr = fopen("./puzzleinput.txt","r");

	if (fileptr == NULL){
		printf("file pointer was null, exiting\n");
		return 1;
	}


	char data[2];
	int index = 0;

	char current_spin[4];
	bool dial_at_zero = false;
	while (fgets(data,sizeof(data),fileptr) != NULL){
	
		bool spin_right;

		//if newline found we know were skipping into next line
		if (data[0] == *"\n"){
			index = 0;
			if (current_spin[0] == *"R"){
				spin_right = true;
			}else if(current_spin[0] == *"L"){
				spin_right = false;
			} else{
				printf("if condition failed we shouldnt be here\n");
			}
			char spin_count_char[3];

			for (int i = 0; i < sizeof(spin_count_char); i++){
				spin_count_char[i] = current_spin[i+1];
			}
			int spin_count = atoi(spin_count_char);

			//part 2 we also need the amount of times it hits zero in total
			if (spin_count >= 100){
				int hits = spin_count_char[0] - '0'; 
				zero_intermittent_hits += hits; 

				//printf("zero intermittent hits: %d \n", zero_intermittent_hits);
				//printf("spin_count: %d \nconverted number: %d \n\n",spin_count, hits);
			} 
			//we can do this because 100 is literally just a full rotation
			spin_count = spin_count % 100;

			if (spin_right){
				dial_position = dial_position + spin_count;
				if (dial_position > 99){
					int dial_before = dial_position;
					dial_position = dial_position - 100;
					if (dial_position != 0 && !dial_at_zero){
						zero_intermittent_hits++;
						printf("incremented zero intermittent\ndial_before: %d,\ndial_after: %d\nspin_right: %d\nspin_amount: %d\n",dial_before,dial_position,spin_right,spin_count);
					}
				}

			}else{
				dial_position = dial_position - spin_count;
				if (dial_position < 0){
					int dial_before = dial_position;
					dial_position = dial_position + 100;
					if (dial_position != 0 && !dial_at_zero){
						zero_intermittent_hits++;
						printf("incremented zero intermittent\ndial_before: %d,\ndial_after: %d\nspin_right: %d\nspin_amount: %d\n",dial_before,dial_position,spin_right,spin_count);
					}
				}
			}
			if (dial_position == 0){
				zero_counter++;
				dial_at_zero = true;
			}else{
				dial_at_zero = false;
			}

			memset(current_spin, 0, sizeof(current_spin));
			continue;
		}
		current_spin[index] = data[0];
		index++;
	}
	printf("number of times dial was zero: %d\n",zero_counter);
	printf("number of times dial hit zero intermittently: %d\n", zero_intermittent_hits);
	printf("total hits: %d\n", zero_intermittent_hits + zero_counter);
	fclose(fileptr);

	return 0;
}
