#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//typedef void(*OptCache[3])(int x, int y);

#define SIZE 5
typedef void(*Opt) (int, int);
typedef Opt OptCache[SIZE];

void opt1(int x,int y) {
	printf("now execute  opt1 \n");
}

void opt2(int x, int y) {
	printf("now execute  opt2 \n");
}

void opt3(int x, int y) {
	printf("now execute  opt3 \n");
}

void opt4(int x, int y) {
	printf("now execute  opt4 \n");
}

void opt5(int x, int y) {
	printf("now execute  opt5 \n");
}

void opt6(int x, int y) {
	printf("now execute  opt6 \n");
}

void opt7(int x, int y) {
	printf("now execute  opt7 \n");
}

void opt8(int x, int y) {
	printf("now execute  opt8 \n");
}




OptCache worker1_cache= {0};
OptCache worker2_cache= {0};


void pushOpt(Opt opt,int index) {
	printf("has push opt%d func\n",index);
	if (index%2==0){
		//can count num for foreach
		worker2_cache[index] = opt;
	}else{
	//can count num  for foreach
		worker1_cache[index] = opt;
	}
}


void * worker1_routine(void* arg){

//about test
int i;
Opt opt=0;
	for (i=0;i<SIZE;++i){
	opt=worker1_cache[i];
	if (opt!=NULL){
		opt(i,i+1);
		sleep(1);
	}
	}


	return (void*)0;
}

void *worker2_routine(void* arg){

	//about test
	int i;
	Opt opt=0;
		for (i=0;i<SIZE;++i){
		opt=worker2_cache[i];
		if (opt!=NULL){
			opt(i,i+1);
			sleep(1);
		}
		}

	return (void*)0;
}



int main(int argc,const char *argvs[]) {
	
	pushOpt(opt1, 1);
	pushOpt(opt2, 2);
	pushOpt(opt3, 3);
	pushOpt(opt4, 4);
	pushOpt(opt5, 5);
	pushOpt(opt6, 6);
	pushOpt(opt7, 7);
	pushOpt(opt8, 8);


	pthread_t worker1={0};
	pthread_t worker2={0};

	pthread_create(&worker1,0,worker1_routine,0);
	pthread_create(&worker2,0,worker2_routine,0);

	//getchar();

	pthread_join(worker1,0);
	pthread_join(worker2,0);

	return 0;
}


