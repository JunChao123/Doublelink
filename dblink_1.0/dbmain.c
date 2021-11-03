#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"dblink.h"


void _ShowCharLink_f(void *val)
{
	char *nodevalue = (char *)val;
	printf("%c\t",*nodevalue);
}

void _ShowIntLink_f(void *val)
{
	int *nodevalue = (int *)val;
	printf("%d\t",*nodevalue);
}

void _ShowFloatLink_f(void *val)
{
	float *nodevalue = (float *)val;
	printf("%f\t",*nodevalue);
}

void _FreeDefine_f(void *val)
{
	LinkNode_s *nodeaddress_p = (LinkNode_s *)val;
	free(nodeaddress_p->value);
	nodeaddress_p->value = NULL;
	free(nodeaddress_p);
	nodeaddress_p = NULL;
}

bool _CompareChar_f(void *value1, void *value2)
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

bool _CompareInt_f(void *value1, void *value2)
{
	int * val1 = (int *)value1;
	int * val2 = (int *)value2;
	if(*val1 <= *val2)
	{
		return true;
	}
	return false;
}

void _ChangeLine()
{
	printf("\n");
}

char *CharTest_g = NULL;
int *IntTest_g = NULL;


int main()
{
	LinkHome_s *headchar_p = _InitLink();
	LinkHome_s *headint_p = _InitLink();
	
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
		* CharTest_g = a[a_count];
		_InsertTail(headchar_p, CharTest_g);
	}
	
	for(;int_count < 50;int_count++)
	{
		IntTest_g = (int *)malloc(sizeof(int));
		//* IntTest_g = b[b_count];
		*IntTest_g = random() % 50;
		_InsertTail(headint_p, IntTest_g);
	}

	
	//正反遍历
	_ShowHeadLink(headchar_p, _ShowCharLink_f);
	_ChangeLine();
	_ShowTailLink(headchar_p, _ShowCharLink_f);
	_ChangeLine();
	_ShowHeadLink(headint_p, _ShowIntLink_f);
	_ChangeLine();
	_ShowTailLink(headint_p, _ShowIntLink_f);
	_ChangeLine();
	//删除数据
	_DeleteNode(headchar_p, 6, _FreeDefine_f);
	_ShowHeadLink(headchar_p, _ShowCharLink_f);
	//_ChangeLine();
	//_ShowTailLink(headchar_p, _ShowCharLink_f);
	_ChangeLine();
	//插入数据
	_InsertSite(headint_p, 50, insertdata);
	_ShowHeadLink(headint_p, _ShowIntLink_f);
	_ChangeLine();
	//查找指定位置数据
	_FindSiteValue(headchar_p, 5, _ShowCharLink_f);
	_ChangeLine();
	
	//_ShowHeadLink(headint_p, _ShowIntLink_f);
	//快速排序，char链表
	_QuickSort(headchar_p->head->next, headchar_p->tail->prior, _CompareChar_f);
	_ShowHeadLink(headchar_p, _ShowCharLink_f);
	_ChangeLine();
	//快速排序，int链表
	_QuickSort(headint_p->head->next, headint_p->tail->prior, _CompareInt_f);
	_ShowHeadLink(headint_p, _ShowIntLink_f);
	_ChangeLine();
	//释放链表
	_DestoryLink(headint_p, _FreeDefine_f);
	_DestoryLink(headchar_p, _FreeDefine_f);

}
