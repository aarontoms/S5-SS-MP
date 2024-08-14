#include<stdio.h>
#include<stdlib.h>

int tracks, head, upper_bound=199, lower_bound=0;
int track[20];

void read(){
	printf("Enter the number of tracks: ");
	scanf("%d", &tracks);
	tracks++;
	printf("Enter the tracks: ");
	for(int i=1; i<tracks; i++){
		scanf("%d", &track[i]);
	}
	
	printf("Enter head position: ");
	scanf("%d", &head);
	track[0] = head;
}

void fcfs(){
	int dist = 0;
	
	read();
	
	printf("\nService order: %d", track[0]);
	for(int i=1; i<tracks; i++){
		dist += abs(track[i]-track[i-1]);
		printf(" -> %d", track[i]);
	}
	
	printf("\nTotal distance: %d", dist);
}

void scan(){
	int dist=0, pos;
	
	read();
	for(int i=0; i<tracks-1; i++){
		for(int j=0; j<tracks-i-1; j++){
			if(track[j] > track[j+1]){
				int temp = track[j];
				track[j] = track[j+1];
				track[j+1] = temp;
			}
		}
	}
	
	for(int i=0; i<tracks; i++){
		if(track[i] == head)
			pos = i;
	}

	printf("\nService order: %d", track[pos]);
	for(int i=pos+1; i<tracks; i++){
		dist += abs(track[i] - track[i-1]);
		printf(" -> %d", track[i]);
//		printf("\nTotal distance: %d", dist);
	}
	dist += abs(upper_bound - track[tracks-1]);
//	printf("\nTotal distance: %d", dist);
	dist += abs(upper_bound - track[pos-1]);
//	printf("\nTotal distance: %d", dist);
	printf(" -> %d", upper_bound);
	for(int i=pos-1; i>0; i--){
		dist += abs(track[i] - track[i-1]);
		printf(" -> %d", track[i]);
//		printf("\nTotal distance: %d", dist);
	}
	
	printf("\nTotal distance: %d", dist);
}

void cscan(){
	int dist=0, pos;
	
	read();
	for(int i=0; i<tracks-1; i++){
		for(int j=0; j<tracks-i-1; j++){
			if(track[j] > track[j+1]){
				int temp = track[j];
				track[j] = track[j+1];
				track[j+1] = temp;
			}
		}
	}
	
	for(int i=0; i<tracks; i++){
		if(track[i] == head)
			pos = i;
	}
	printf("Service order: %d", track[pos]);
	for(int i=pos+1; i<tracks; i++){
		dist += abs(track[i] - track[i-1]);
		printf(" -> %d", track[i]);
	}
	dist += abs(upper_bound - track[tracks-1]);
	dist += abs(upper_bound - lower_bound);
	dist += abs(lower_bound - track[0]);
	printf(" -> %d", upper_bound);
	printf(" -> %d", lower_bound);
	for(int i=1; i<pos; i++){
		dist += abs(track[i] - track[i-1]);
		printf(" -> %d", track[i]);
	}
	
	printf("\nTotal distance: %d", dist);
}

void main(){
	int ch;
	
	do{
		printf("\n\n---MENU---\n 1. FCFS\n 2. SCAN\n 3. C-SCAN\nEnter your choice: ");
		scanf("%d", &ch);
		switch(ch){
		case 1:
			fcfs();
			break;
			
		case 2:
			scan();
			break;
		
		case 3:
			cscan();
			break;
		}
	}while(ch!=4);
	
}
