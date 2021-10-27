#include<stdio.h>
#include<stdlib.h>
#include"dblink.h"
/*
typedef struct Linknode{
	struct Linknode *prior;
	void *value;
	struct Linknode *next;
}linknd;

typedef struct Linkhead{
	linknd  *head;
	char linklength;
}linkhead;

typedef enum insertreturn{
	INSERT_OK,
	INSERT_FIAL
}instrt;

typedef enum deletereturn{
        DELETE_OK,
        DELETE_FIAL
}delrt;

//typedef void (*listlink)(void *);
*/

linkhead *initlink(){
	linkhead *headp = (linkhead *)malloc(sizeof(linkhead));
	headp->head = (linknd *)malloc(sizeof(linknd));
	if(headp == NULL||headp->head == NULL){
		return NULL;
	}
	headp->linklength = 0;
	headp->head->next = NULL;
	return headp;
}


static linknd *nodecreate(void *value){
	linknd *newnode = (linknd *)malloc(sizeof(linknd));
	if(newnode == NULL){
		return NULL;
	}

	newnode->prior = NULL;
	newnode->next = NULL;
	newnode->value = value;
	//printf("nodecreate");
	return newnode;
}


static linknd *getsite(linkhead *headp, int site){
	linknd *sitep = headp->head;
	if(site < 0||site > (headp->linklength)){
		return NULL;
	}
	//printf("site:%d\t",site);
	while(site>0){
		sitep = sitep->next;
		site--;
	}
	
	return sitep;

}


instrt insert(linkhead *headp, int site, void *value){
	linknd *insertp = getsite(headp, site);
	linknd *newinsertnd = nodecreate(value);
	if(insertp == NULL||newinsertnd ==NULL){
		return INSERT_FAIL;
	}

	if(insertp->next == NULL){
		insertp->next = newinsertnd;
		newinsertnd->prior = insertp;
		(headp->linklength)++;
		return INSERT_OK;
	}

	newinsertnd->next = insertp->next;
	insertp->prior = newinsertnd;
	insertp->next = newinsertnd;
	newinsertnd->prior = insertp;
	(headp->linklength)++;
	printf("在第%d节点插入完成!\n",site);
	return INSERT_OK;
}


instrt inserttail(linkhead *headp, void *value){
	linknd *instailp = getsite(headp,(headp->linklength));
	linknd *newnodep = nodecreate(value);
	if(instailp == NULL||newnodep ==NULL){
                return INSERT_FAIL;
        }
	
	instailp->next = newnodep;
	newnodep->prior = instailp;
	(headp->linklength)++;
	return INSERT_OK;

}


void *find_site_value(linkhead *headp, int site){
	linknd *findp = getsite(headp, site);
	return findp->value;
}


void traverse(linkhead *headp, listlink printlink){
	linknd * traverp = headp->head->next;
	int len = (headp->linklength);
	while(len > 0){
		printlink(traverp->value);
		traverp = traverp->next;
		len--;
	}
	printf("链表打印已完成！\n");
}


delrt _delete(linkhead *headp, int site){
	linknd *deletep = getsite(headp,site);
	if(deletep == NULL){
		return DELETE_FAIL;
	}

	if(deletep->next == NULL){
		deletep->prior->next = NULL;
		(headp->linklength)--;
		free(deletep);
		return DELETE_OK;
	}
	deletep->prior->next = deletep->next;
	deletep->next->prior = deletep->prior;
	(headp->linklength)--;
	free(deletep);
	printf("第%d节点删除完成\n",site);
	return DELETE_OK;
}


void _destory(linkhead *headp){
	linknd *dstyp = headp->head->next;
	linknd *tmp = NULL;
	while(dstyp != NULL){
		tmp = dstyp->next;
		free(dstyp);
		dstyp = tmp;
	}
	free(headp->head);
	free(headp);
	printf("链表已销毁!\n");
}

