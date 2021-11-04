#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"dblink.h"


void showCharLink_f(void *val)
{
	char *nodevalue = (char *)val;
	printf("%c\t",*nodevalue);
}

void showIntLink_f(void *val)
{
	int *nodevalue = (int *)val;
	printf("%d\t",*nodevalue);
}

void showFloatLink_f(void *val)
{
	float *nodevalue = (float *)val;
	printf("%f\t",*nodevalue);
}

void freeDefine_f(void *val)
{
	LinkNode_s *nodeaddress_p = (LinkNode_s *)val;
	free(nodeaddress_p->value);
	nodeaddress_p->value = NULL;
	free(nodeaddress_p);
	nodeaddress_p = NULL;
}

bool compareChar_f(void *value1, void *value2)
{
	char * val1 = (char *)value1;
	char * val2 = (char *)value2;
	//printf("%c\t%c\n",*val1,*val2);
	if(*val1 <= *val2)
	{
		return true;
	}	
	return false;
}

bool compareInt_f(void *value1, void *value2)
{
	int * val1 = (int *)value1;
	int * val2 = (int *)value2;
	if(*val1 <= *val2)
	{
		return true;
	}
	return false;
}

void changeLine()
{
	printf("\n");
}

char *CharTest_g = NULL;
int *IntTest_g = NULL;


int main()
{
	LinkHome_s *headchar_p = initLink();
	LinkHome_s *headint_p = initLink();
	
	int *insertdata =(int *)malloc(sizeof(int));
	*insertdata = 666;
	char *findnum = NULL;
	char a[7] = "program";
	//int b[10] = {1,2,3,4,5,6,7,8,9,10};
	int a_count = 0;
	int int_count = 0;

	for(;a[a_count] != '\0';a_count++)
	{
		CharTest_g = (char *)malloc(sizeof(char));
		if(CharTest_g == NULL)
		{
			return -1;
		}
		* CharTest_g = a[a_count];
		insertTail(headchar_p, CharTest_g);
	}
	
	for(;int_count < 50;int_count++)
	{
		IntTest_g = (int *)malloc(sizeof(int));
		if(IntTest_g == NULL)
		{
			return -1;
		}
		*IntTest_g = random() % 50;
		insertTail(headint_p, IntTest_g);
	}

	
	//正反遍历
	showHeadLink(headchar_p, showCharLink_f);
	changeLine();
	showTailLink(headchar_p, showCharLink_f);
	changeLine();
	showHeadLink(headint_p, showIntLink_f);
	changeLine();
	showTailLink(headint_p, showIntLink_f);
	changeLine();
	//删除数据
	deleteNode(headchar_p, 6, freeDefine_f);
	showHeadLink(headchar_p, showCharLink_f);
	//changeLine();
	//showTailLink(headchar_p, showCharLink_f);
	changeLine();
	//插入数据
	insertSite(headint_p, 50, insertdata);
	showHeadLink(headint_p, showIntLink_f);
	changeLine();
	//查找指定位置数据
	findSiteValue(headchar_p, 5, showCharLink_f);
	changeLine();
	
	//showHeadLink(headint_p, showIntLink_f);
	//快速排序，char链表
	quickSort(headchar_p->head->next, headchar_p->tail->prior, compareChar_f);
	showHeadLink(headchar_p, showCharLink_f);
	changeLine();
	//快速排序，int链表
	quickSort(headint_p->head->next, headint_p->tail->prior, compareInt_f);
	showHeadLink(headint_p, showIntLink_f);
	changeLine();
	//释放链表
	destoryLink(headint_p, freeDefine_f);
	destoryLink(headchar_p, freeDefine_f);

}
