#include<stdio.h>
#include<stdlib.h>
#include"dblink.h"

void showcharlink(void *val){
	char *nodevalue = (char *)val;
	printf("%c\t",*nodevalue);
}

void showintlink(void *val){
	int *nodevalue = (int *)val;
	printf("%d\t",*nodevalue);
}

void showfloatlink(void *val){
	float *nodevalue = (float *)val;
	printf("%f\t",*nodevalue);
}

int main(){
	char a[10] = "program";
	int b[10] = {1,2,3,4,5,6,7,8,9,10};
	int *tmp =(int *)malloc(10);
	*tmp = 66;
	char *findnum = NULL;
	instrt result_of_insert;
	//char print_of_insert[2][20] = {"insert ok","insert fail"};

	linkhead *headcharp = initlink();
	linkhead *headintp = initlink();	


	int datetype = 0;
	
	for(;datetype < 2;datetype++){
		int count = 0;
		if(datetype == 0){
			while(a[count] != '\0'){
				//headcharp = initlink();
				inserttail(headcharp, &a[count]);
				count++;
				}
		}
		else{
			while(count<10){
				//headintp = initlink();
				inserttail(headintp, &b[count]);
				count++;
				//printf("%d\n",b[count]);
				
			}
		}
	}

	traverse(headcharp, showcharlink);
	traverse(headintp, showintlink);

	_delete(headcharp, 5);
	traverse(headcharp, showcharlink);

	result_of_insert = insert(headintp, 5, tmp);
	//printf("%s\n",print_of_insert[result_of_insert]);
	traverse(headintp, showintlink);
	free(tmp);

	findnum = (char *)find_site_value(headcharp, 3);
	printf("第三个位置的字符是：%c\n",*findnum);

	

	_destory(headintp);
	_destory(headcharp);

}
