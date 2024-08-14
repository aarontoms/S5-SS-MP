#include<stdio.h>

struct process{
	int name, at, bt, ct, tat, wt, priority, status, rem;
}proc[20], temp, queue[20], ready[20];

int blocks=0, ch, procs, pointer=0, quan=2;

void sort(){
	for(int i=0; i<procs-1; i++){
		for(int j=0; j<procs-i-1; j++){
			if(proc[j].at > proc[j+1].at){
				temp = proc[j];
				proc[j] = proc[j+1];
				proc[j+1] = temp;
			}
		}
	}
}

void read(){
	printf("Enter the number of processes: ");
	scanf("%d", &procs);
	for(int i=0; i<procs; i++){
		if(ch==3){
			printf("Process%d (AT, BT, Priority): ", i);
			scanf("%d %d %d", &proc[i].at, &proc[i].bt, &proc[i].priority);
		}
		else{
			printf("Process%d (AT, BT): ", i);
			scanf("%d %d", &proc[i].at, &proc[i].bt);
		}
		proc[i].name = i;
		proc[i].status = 0;
		proc[i].rem = proc[i].bt;
	}
	sort();
}

void display(){	
	
	if(ch==3){
		printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\tPriority\n");
		for(int i=0; i<procs; i++){
			printf("p%d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].name, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt, proc[i].priority);
		}
	}
	else{
		printf("\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
		for(int i=0; i<procs; i++){
			printf("p%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].name, proc[i].at, proc[i].bt, proc[i].ct, proc[i].tat, proc[i].wt);
		}
	}
	
	
	//GANTT Chart
	printf("\n\nGANTT Chart\n");
	
	for(int i=0; i<blocks; i++){
		printf("--------");
	}
	printf("\n");
	for(int i=0; i<blocks; i++){
		if(queue[i].ct == 0)
			printf("| idle |");
		else
			printf("|  p%d  |", queue[i].name);
	}
	printf("\n");
	for(int i=0; i<blocks; i++){
		printf("--------");
	}
	printf("\n");
	for(int i=0; i<blocks+1; i++){
		if(queue[i-1].ct == 0)
			printf("%d\t", queue[i].at);
		else
			printf("%d\t", queue[i-1].ct);
	}
}

void fcfs(){
	int ct=0;
	
	read();
	
	for(int i=0; i<procs; i++){
		if(proc[i].at > ct){
			blocks++;
			ct = proc[i].ct = proc[i].at + proc[i].bt;
		}
		else{
			ct = proc[i].ct = ct + proc[i].bt;
		}
		
		proc[i].tat = proc[i].ct - proc[i].at;
		proc[i].wt = proc[i].tat - proc[i].bt;
		queue[blocks] = proc[i];
		blocks++;
	}
	display();
}

void sjf(){
	int ct=0, done=0, min;
	
	read();
	
	while(done < procs){
		int found = 0;
		for(int i=0; i<procs; i++){
			if(proc[i].at <= ct && !proc[i].status){
				found = 1;
				min = i;
				break;
			}
		}
		for(int i=0; i<procs; i++){
			if(proc[i].at <= ct && !proc[i].status){
				if(proc[i].bt < proc[min].bt)
					min = i;
			}
		}
		
		if(!found){
//		printf("why here lol");
			blocks++;
			for(int i=0; i<procs; i++){
				if(!proc[i].status){
					min = i;
					break;
				}
			}
			ct = proc[min].ct = proc[min].at + proc[min].bt;
		}
		else{
			ct = proc[min].ct = ct + proc[min].bt;
		}

		printf("min=%d", min);
		proc[min].tat = proc[min].ct - proc[min].at;
		proc[min].wt = proc[min].tat - proc[min].bt;
		proc[min].status = 1;
		queue[blocks] = proc[min];
		blocks++;
		done++;
	}
	display();
}

void priority(){
	int ct=0, done=0, min;
	
	read();
	
	while(done < procs){
		int found = 0;
		for(int i=0; i<procs; i++){
			if(proc[i].at <= ct && !proc[i].status){
				found = 1;
				min = i;
				break;
			}
		}
		for(int i=0; i<procs; i++){
			if(proc[i].at <= ct && !proc[i].status){
				if(proc[i].priority < proc[min].priority)
					min = i;
			}
		}
		
		if(!found){
//		printf("why here lol");
			blocks++;
			for(int i=0; i<procs; i++){
				if(!proc[i].status){
					min = i;
					break;
				}
			}
			ct = proc[min].ct = proc[min].at + proc[min].bt;
		}
		else{
			ct = proc[min].ct = ct + proc[min].bt;
		}

		proc[min].tat = proc[min].ct - proc[min].at;
		proc[min].wt = proc[min].tat - proc[min].bt;
		proc[min].status = 1;
		queue[blocks] = proc[min];
		blocks++;
		done++;
	}
	display();
}

void enqueue(int i){
	ready[pointer] = proc[i];
	pointer++;
	
	for(int i=0; i<pointer; i++){
	//	printf("| p%d |", ready[i].name);
	}
	//printf("**eri**");
	//printf("\n");
}

struct process dequeue(){
	temp = ready[0];
	
	for(int i=1; i<pointer; i++){
		ready[i-1] = ready[i];
	}
	pointer--;
}

void robin(){
	int ct=0, done=0, min;
	
	read();
	
	while(done < procs){
		
		for(int i=0; i<procs; i++){
			if(proc[i].at <= ct && !proc[i].status){
				enqueue(i);
				proc[i].status = 1;
			}
		}
		//dequeue, fulfil, then repeat
		dequeue();
		for(int i=0; i<procs; i++){
			if(proc[i].name == temp.name){
				min = i;
				break;
			}
		}
		//printf("\n>>>p%d", proc[min].name);
		
		if(quan > proc[min].rem){
			//printf("heieh");
			ct = proc[min].ct = ct + proc[min].rem;
			proc[min].tat = proc[min].ct - proc[min].at;
			proc[min].wt = proc[min].tat - proc[min].bt;
			proc[min].rem = 0;
			queue[blocks] = proc[min];
			blocks++;
			done++;
		}
		else{
			ct = proc[min].ct = ct + quan;
			proc[min].rem -= quan;
			queue[blocks] = proc[min];
			blocks++;
			for(int i=0; i<procs; i++){
				if(proc[i].at <= ct && !proc[i].status){
					enqueue(i);
					proc[i].status = 1;
				}
			}
			enqueue(min);
		}
		//done=procs;
	}
	blocks -= 2;
	display();
}

void main(){
	do{
		printf("\n---MENU---\n 1. FCFS\n 2. SJF\n 3. Priority\n 4. Round Robin\nEnter your choice: ");
		scanf("%d", &ch);
		switch(ch){
		case 1:
			fcfs();
			break;
			
		case 2:
			sjf();
			break;
		
		case 3:
			priority();
			break;
			
		case 4:
			robin();
			break;
		}
	}while(ch!=5);
}
