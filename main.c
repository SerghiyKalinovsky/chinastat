#include <stdio.h>
#include <stdlib.h>

#define SIZE 50
#define B_SIZE 255
#define M_SIZE 17

#define DATA_FILE "data.txt"
#define DATA_MORT_FILE "mort.txt"



void outArray(long* data, int size);

int readData(long* data, int size);

void readMort(double *data);

void mergeData(long* data_in, long* data_out);

void fourYearCycle(long* data, double* mortData, int ch);

int printData(long* data, int size);


int main (int argc, char **argv){
		
	long data_in[SIZE];						// Input Data male famale apart
	long data_age[M_SIZE];					// Modified date male female common 
	double mortData[M_SIZE];				// Age specific mortality rate array
	int k = 0; 
	int ch = 0;
	if (argc>1)
		ch = atoi(argv[1]);
	else 
		ch=2;
	
	
	k = readData(data_in, SIZE); 					// read from file quantity
	readMort(mortData);							// read age specific mort rate
	mergeData(data_in, data_age);				// Merge male female data
	//printData (data_age, M_SIZE);
	
	/*outArray(data_in, k);
	printf ("Number of elements %d\n",k);
	
	for (int n=0; n<M_SIZE ; n++){
		printf("%d\n", data_age[n]);
	}
	*/
	int s=1980;
	while (s<=2020){
		fourYearCycle(data_age, mortData, ch);
		printf("Year %d\n", s); 
		printData(data_age, M_SIZE);
		s+=4;
	}
	
	return 0;
}



int readData(long* data, int size){
	FILE *fp;
	int k=0;
	char buf[B_SIZE] = {[0 ... B_SIZE -1] = 0 };
	fp = fopen (DATA_FILE, "r+");
	if (fp == NULL){
		fprintf (stderr, "Can't open the file  - %s\n", DATA_FILE); 
		exit (0);
	}
	
	for (int n=0; n < size; n++)
		data[n] = 0;
	
	while (!feof(fp)){
		fscanf(fp,"%s",buf);
		data[k]=atoi(buf);
		k++;
	
	
	}
	fclose(fp);		
	return k-1;
}

void readMort(double *data){
	FILE *fp;
	char buf[B_SIZE];
	fp = fopen (DATA_MORT_FILE, "r+");
	if (fp == NULL){
		fprintf (stderr, "Can't open the file  - %s\n", DATA_MORT_FILE); 
		exit (0);
	}
	for (int n = 0; n<M_SIZE; n++){
		fscanf(fp,"%s",buf);
		data[n] = atof (buf);
	}
	fclose(fp);		
	
/*	for (int n=0; n<M_SIZE ; n++){
		printf("%f\n", data[n]);
	}*/
	
	
}


void outArray(long*data, int size){
	
	int t = size-1;
	for (int n = ((size-1)/2); n>=0; n--){
		printf("%10d",data[t]);
		t--;
		printf("%10d",data[t]);
		t--;
		printf("\n");
		
		
		
	}
	printf("\n");

}	

void mergeData(long* data_in, long* data_out){
	
	for(int n=0; n<M_SIZE ; n++){
		int k = n*2;
		data_out[n] = data_in[n]  + data_in[n+1];
		
	}
	
	
}

void fourYearCycle(long* data, double* mortData, int ch){
	
	int newBorn = 0;
	for (int n=5, k=0; k<ch;n++, k++)
		newBorn= data[n]/2 + newBorn;
	printf ("New born is - %d\n", newBorn);
	/*printData (data, M_SIZE);*/
	int n = ch - 1;
	while (n){
		data[n] = data[n-1];
		n--;
	}
	data[0] = newBorn;
	/*printData (data, M_SIZE);*/
	for (int n=0; n<M_SIZE; n++){
		data[n] = data[n] * (1- (mortData[n])/100);
		data[n] = data[n] * (1- (mortData[n])/100);
		data[n] = data[n] * (1- (mortData[n])/100);
		data[n] = data[n] * (1- (mortData[n])/100);
		if (data[n]<0)
			data[n] = 0;
	}
	
	/* printData (data, M_SIZE);*/
	
	
}

int printData(long* data, int size){
	
	int k = size;
	do {
		k--;
		printf("%d\n", data[k]);
		
	} while (k);
	printf("\n");
	long sum=0;
	
	for (int n=0; n<size; n++)
		sum = sum + data[n];
	printf("Total amount - %d\n\n", sum);
	
}
