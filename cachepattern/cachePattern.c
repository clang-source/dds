#include <stdio.h>
#include <unistd.h>

//typedef void(*OptCache[3])(int x, int y);

#define SIZE 3
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



void pushOpt(OptCache* cache,Opt opt,int index) {
	(*cache)[index] = opt;
	printf("has push opt%d func\n",index);
}


int main(int argc,const char *argvs[]) {
	OptCache cache = {0};
	pushOpt(&cache, opt1, 0);
	pushOpt(&cache, opt2, 1);
	pushOpt(&cache, opt3, 2);

	int i;
	for (i = 0; i < SIZE; ++i) {
		cache[SIZE-1-i](i, i + 2);//reverse execute..
		//add some taste
		sleep(1);///take a break....
	}

	return 0;
}


