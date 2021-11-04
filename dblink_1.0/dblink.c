#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"dblink.h"


LinkHome_s *initLink()
{
	LinkHome_s *link_p = (LinkHome_s *)malloc(sizeof(LinkHome_s));
	if(link_p == NULL)
	{
		return NULL;
	}
	link_p->linklength = 0;
	link_p->head = NULL;
	link_p->tail = NULL;


	link_p->head = (LinkNode_s *)malloc(sizeof(LinkNode_s));
	if(link_p->head == NULL)
	{
		free(link_p);
		return NULL;
	}
	link_p->head->prior = NULL;
	link_p->head->value = 0;
	link_p->head->next = NULL;


	link_p->tail = (LinkNode_s *)malloc(sizeof(LinkNode_s));
	if(link_p->tail == NULL)
	{
		free(link_p->head);
		free(link_p);
		return NULL;
	}
	link_p->tail->prior = link_p->head;	
	link_p->tail->value = 0;
	link_p->tail->next = NULL;
	link_p->head->next = link_p->tail;
	return link_p;
}


static LinkNode_s *nodeCreate(void *value)
{
	LinkNode_s *newnode_p = (LinkNode_s *)malloc(sizeof(LinkNode_s));
	if(newnode_p == NULL)
	{
		return NULL;
	}

	newnode_p->prior = NULL;
	newnode_p->next = NULL;
	newnode_p->value = value;
	//printf("nodeCreate");
	return newnode_p;
}


static LinkNode_s *getSite(LinkHome_s *link_p, int site)
{
	LinkNode_s *site_p = link_p->head;
	if(site_p == NULL)
	{
		return NULL;
	}
	/*LinkNode_s *tail_p = link_p->tail;
	if(tail_p == NULL)
	{
		return NULL;
	}*/
	if(site < 0||site > (link_p->linklength))
	{
		return NULL;
	}
	//printf("site:%d\t",site);
	while(site>0)
	{
		site_p = site_p->next;
		site--;
	}
	
	return site_p;

}


OperateReturn_e insertSite(LinkHome_s *link_p, int site, void *value)
{
	LinkNode_s *insert_p = getSite(link_p, site);
	if(insert_p == NULL)
	{
		return ILLEGAL_DATA;
	}
	LinkNode_s *tail_p = link_p->tail;
	if(tail_p == NULL)
	{
		return INIT_FAIL;
	}
	LinkNode_s *newnode_p = nodeCreate(value);
	if(newnode_p == NULL)
	{
		return APPLY_FAIL;
	}
	if(value == NULL)
	{
		return ILLEGAL_DATA;
	}

	if(insert_p->next == tail_p)
	{
		insert_p->next = newnode_p;
		newnode_p->prior = insert_p;
		newnode_p->next = tail_p;
		tail_p->prior = newnode_p;
		(link_p->linklength)++;
		return OK;
	}

	newnode_p->next = insert_p->next;
	insert_p->next->prior = newnode_p;
	insert_p->next = newnode_p;
	newnode_p->prior = insert_p;
	(link_p->linklength)++;
	//printf("在第%d节点插入完成!\n",site);
	return OK;
}


OperateReturn_e insertTail(LinkHome_s *link_p, void *value)
{
	LinkNode_s *inserttail_p = getSite(link_p,(link_p->linklength));
	if(inserttail_p == NULL)
        {
                 return ILLEGAL_DATA;
        }
	LinkNode_s *newnode_p = nodeCreate(value);
	if(newnode_p == NULL)
	{
                return APPLY_FAIL;
        }
	LinkNode_s *tail_p = link_p->tail;
	if(tail_p == NULL)
	{
		return INIT_FAIL;
	}
	if(value == NULL)
	{
		return ILLEGAL_DATA;
	}

	inserttail_p->next = newnode_p;
	newnode_p->prior = inserttail_p;
	newnode_p->next = tail_p;
	tail_p->prior = newnode_p;
	(link_p->linklength)++;
	return OK;

}


OperateReturn_e findSiteValue(LinkHome_s *link_p, int site, listLink_f printLink_f)
{
	LinkNode_s *find_p = getSite(link_p, site);
	if(find_p == link_p->head)
	{
		return ILLEGAL_DATA;
	}
	if(find_p == NULL)
	{
		return ILLEGAL_DATA;
	}
	
	printLink_f(find_p->value);
	return OK;
}


OperateReturn_e showHeadLink(LinkHome_s *link_p,  listLink_f printLink_f)
{
	if(link_p == NULL)
	{
		return ILLEGAL_DATA;
	}

	LinkNode_s * showhead_p = link_p->head->next;
	while(showhead_p != link_p->tail)
	{
		printLink_f(showhead_p->value);
		showhead_p = showhead_p->next;
	}	
	//printf("链表打印已完成！\n");
}


OperateReturn_e showTailLink(LinkHome_s *link_p,  listLink_f printLink_f)
{
	if(link_p == NULL)
	{
		return ILLEGAL_DATA;
	}

	LinkNode_s * showtail_p = link_p->tail->prior;
	while(showtail_p != link_p->head)
	{
		printLink_f(showtail_p->value);
		showtail_p = showtail_p->prior;
	}

}

OperateReturn_e deleteNode(LinkHome_s *link_p, int site, listLink_f freeDefine_f)
{
	LinkNode_s *delete_p = getSite(link_p,site);
	if(delete_p == NULL)
	{
		return ILLEGAL_DATA;
	}
	if(delete_p == link_p->head)
	{
		return ILLEGAL_DATA;
	}
	LinkNode_s *tail_p = link_p->tail;
	if(tail_p == NULL)
	{
		return INIT_FAIL;
	}

	if(delete_p->next == link_p->tail)
	{
		delete_p->prior->next = tail_p;
		tail_p->prior = delete_p->prior; 
		(link_p->linklength)--;
		freeDefine_f(delete_p);
		return OK;
	}
	delete_p->prior->next = delete_p->next;
	delete_p->next->prior = delete_p->prior;
	(link_p->linklength)--;
	freeDefine_f(delete_p);
	//printf("第%d节点删除完成\n",site);
	return OK;
}

OperateReturn_e destoryLink(LinkHome_s *link_p, listLink_f freeDefine_f)
{
	if(link_p == NULL)
	{
		return ILLEGAL_DATA;
	}	

	LinkNode_s *destory_p = link_p->head->next;
	LinkNode_s *tmp_p = NULL;
	while(destory_p != link_p->tail)
	{
		tmp_p = destory_p->next;
		freeDefine_f(destory_p);
		destory_p = tmp_p;
	}
	free(link_p->head);
	free(link_p->tail);
	free(link_p);
	//printf("链表已销毁!\n");
}

static LinkNode_s * sortfun(LinkNode_s *quicklow_p, LinkNode_s *quickhigh_p, compare_f compareSort_f)
{
	LinkNode_s *quickhead_p = quicklow_p;
	LinkNode_s *quicktail_p = quickhigh_p;
	void *midvalue = NULL;
	midvalue = quickhead_p->value;
	
	while(quickhead_p != quicktail_p)
	{
		bool compare_result = false;
		compare_result = compareSort_f(midvalue, quicktail_p->value);
		while( (quickhead_p != quicktail_p) && compare_result)
		{
			quicktail_p = quicktail_p->prior;
			compare_result = compareSort_f(midvalue, quicktail_p->value);
		}
		void * tmp = NULL;
		tmp = quicktail_p->value;
		quicktail_p->value = quickhead_p->value;
		quickhead_p->value = tmp;
		if(quickhead_p != quicktail_p)
		{
			quickhead_p = quickhead_p->next;
		}
		
	}
	return quickhead_p;
}


OperateReturn_e quickSort(LinkNode_s *quickhead_p,  LinkNode_s *quicktail_p, compare_f compareSort_f)
{
	if(quickhead_p == NULL)
	{
		return ILLEGAL_DATA;
	}
	if(quicktail_p == NULL)
	{
		return ILLEGAL_DATA;
	}
		
	if(quickhead_p != quicktail_p)
	{
		LinkNode_s *loop_p = sortfun(quickhead_p, quicktail_p, compareSort_f);
	
		if(loop_p != quickhead_p)
		{
			quickSort(quickhead_p, loop_p, compareSort_f);	
		}
		if(loop_p == quickhead_p)
		{
			quickSort(loop_p->next, quicktail_p, compareSort_f);
		}
		else
		{
			quickSort(loop_p, quicktail_p, compareSort_f);
		}
	}
	
	return OK;

}

