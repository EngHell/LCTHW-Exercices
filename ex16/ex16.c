#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight) {
	struct Person *who = malloc(sizeof(struct Person));
	assert(who!=NULL);

	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who) {
	assert(who!=NULL);
	free(who->name);
	free(who);
}

void Person_print(struct Person *who){
	printf("Name:\t%s\n",who->name);
	printf("Age:\t%d\n",who->age);
	printf("Height:\t%d\n", who->height);
	printf("Weight:\t%d\n", who->weight);
}

int main(int argc, char *argv[]){
	//make two Person struct
	struct Person *joe = Person_create("Joe", 20, 2, 5);
	struct Person *me = Person_create("Goku", 32, 102, 75);

	printf("ponter to joe: %p\n", joe);
	Person_print(joe);

	printf("pinter to me: %p\n", me);
	Person_print(me);

	Person_destroy(joe);
	Person_destroy(me);

	

	return 0;
}









