#ifndef _DBLINK_HEAD
#define _DBLINK_HEAD


typedef struct Linknode{
        struct Linknode *prior;
        void *value;
        struct Linknode *next;
}linknd;

typedef struct Linkhead{
        linknd  *head;
        int linklength;
}linkhead;

typedef enum insertreturn{
        INSERT_OK,
        INSERT_FAIL
}instrt;

typedef enum deletereturn{
        DELETE_OK,
        DELETE_FAIL
}delrt;


typedef void (*listlink)(void *);
linkhead *initlink();
static linknd *nodecreate(void *value);
static linknd *getsite(linkhead *headp, int site);
instrt insert(linkhead *headp, int site, void *value);
instrt inserttail(linkhead *headp, void *value);
void *find_site_value(linkhead *headp, int site);
void traverse(linkhead *headp, listlink printlink);
delrt _delete(linkhead *headp, int site);
void _destory(linkhead *headp);

#endif
