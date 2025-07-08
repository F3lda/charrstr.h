#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ChArrLenStr.h



typedef struct charrstr
{
    int size;
    int curr_size;
    char str[];
} *ChArrStr;


#define casinit(sizee, str) malloc(sizeof(struct charrstr) + sizeof(char)*sizee); str->size = sizee; str->curr_size = 0; str->str[0] = '\0'
ChArrStr initChArrStr(int size) {
    ChArrStr ret_str = malloc(sizeof(struct charrstr) + sizeof(char)*size);
    ret_str->size = size;
    ret_str->curr_size = 0;
    ret_str->str[0] = '\0';
    return ret_str;
}


#define casclr(str) str->curr_size = 0; str->str[0] = '\0'


#define cascpy(str, str2) str->curr_size = 0; ChArrStrCat(str, str2)


#define cascat(str, str2) ChArrStrCat(str, str2)
int ChArrStrCat(ChArrStr str, char *str2){
    int i = 0;
    while (str->curr_size+1 < str->size && str2[i] != '\0') {
        str->str[str->curr_size++] = str2[i++];
    }
    str->str[str->curr_size] = '\0';
    return i;
}


#define casfree(str) free(str); str = NULL
#define freeChArrStr(str) free(str); str = NULL


int main()
{
    //ChArrStr str = initChArrStr(7);
    /*ChArrStr str = casinit(7);


    ChArrStrCat(str, "Text");
    cascat(str, "Text");
    cascat(str, "1234");


    printf("TEXT: %d %d (%s)\n", str->size, str->curr_size, str->str);


    cascpy(str, "1234");
    printf("TEXT: %d %d (%s)\n", str->size, str->curr_size, str->str);


    casclr(str);
    printf("TEXT: %d %d (%s)\n", str->size, str->curr_size, str->str);


    freeChArrStr(str);*/
	
	
	//#define LOOP_LEN 100000000
	//#define LOOP_LEN 100000
	#define ARRAY_LEN 100000
	//#define ARRAY_LEN 1000000
	
	
	
	double start = (float)clock()/CLOCKS_PER_SEC;
	
	
	
	
	
	ChArrStr str = casinit(ARRAY_LEN, str);
	cascpy(str, "Text");

	int i = 0;
	//for (i = 0; i < LOOP_LEN; i++) {
	while (i+5 < ARRAY_LEN) {	
		cascat(str, "1234");
		i += 5;
	}

    casclr(str);

    freeChArrStr(str);



	
	
	double end = (float)clock()/CLOCKS_PER_SEC;
	
	printf("it took %f seconds.\n", (end - start));
    // TODO speed tests vs without knowing array length
	
	
	
	double start2 = (float)clock()/CLOCKS_PER_SEC;
	
	
	
	
	
	char str2[ARRAY_LEN] = {0};
	strcpy(str2, "Text");

	int i2 = 0;
	//for (i2 = 0; i2 < LOOP_LEN; i2++) {
	while (i2+5 < ARRAY_LEN) {
		strcat(str2, "1234");
		i2 += 5;
	}

    str2[0] = '\0';

    str2[0] = '\0';
	
	
	
	
	double end2 = (float)clock()/CLOCKS_PER_SEC;
	
	printf("it took %f seconds.\n", (end2 - start2));

    return 0;
}
