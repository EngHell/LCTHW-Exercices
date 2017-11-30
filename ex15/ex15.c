#include <stdio.h>

int main(int argc, char *args[]){
	// create two arrays we carea bout
	int ages[] = { 20, 21, 22, 23};
	char *names[] = {"me", "not me", "maybe me", "coku"};

	// safely get the size of the arrays
	int count = sizeof(ages)/sizeof(int);
	int i = 0;

	//first way using indexing
	for(i=count-1; i>-1; i--){
		printf("%s has %d years old.\n",names[i], ages[i]);
	}

	printf("\n\n------------------------------\n\n");

	// setting pointers to the start...
	int *cur_age = ages;
	char **cur_name = names;

	// 2nd way using pointers
	for(i=count-1;i>=0;i--){
		printf("%s is %d years old\n", *(cur_name + i), *(cur_age + i) );
	}

	printf("\n\n------------------------------\n\n");
	
	//3 stupid complex way :D
	for(cur_age = ages+count-1, cur_name = names+count-1; (cur_age-ages) >= 0;cur_age--, cur_name--){
		printf("This dude: %s has %d years of living in dis world\n", *cur_name, *cur_age);
	}

	printf("\n\n------------------------------\n\n");

	for(i=0, cur_name = names, cur_age = ages; i<count; i++){
		printf("Address of cur_name[%d]=%p\n",i,cur_name+i);
	}

	return 0;
}


