#ifndef _DBLINK_HEAD
#define _DBLINK_HEAD


typedef struct Linknode{
        struct Linknode *prior;
        void *value;
        struct Linknode *next;
}LinkNode_s;

typedef struct Linkhome{
        LinkNode_s *head;
        int linklength;
	LinkNode_s *tail;
}LinkHome_s;

typedef enum operatereturn{
	OK,
        APPLY_FAIL,   //内存申请失败
	ILLEGAL_DATA, //位置参数或头指针非法
	INIT_FAIL //初始化失败
}OperateReturn_e;
/*
typedef enum deletereturn{
        DELETE_OK,
        DELETE_FAIL
}DeleteReturn_e;
*/
typedef bool (*compare_f)(void *, void *);
typedef void (*listLink_f)(void *);
LinkHome_s *initLink();
static LinkNode_s *nodeCreate(void *value);
static LinkNode_s *getSite(LinkHome_s *head_p, int site);
OperateReturn_e insertSite(LinkHome_s *head_p, int site, void *value);
OperateReturn_e insertTail(LinkHome_s *head_p, void *value);
OperateReturn_e findSiteValue(LinkHome_s *head_p, int site, listLink_f printLink_f);
OperateReturn_e showHeadLink(LinkHome_s *link_p,  listLink_f printLink_f);
OperateReturn_e showTailLink(LinkHome_s *link_p,  listLink_f printLink_f);
OperateReturn_e deleteNode(LinkHome_s *head_p, int site, listLink_f freeDefine_f);
OperateReturn_e destoryLink(LinkHome_s *head_p, listLink_f freeDefine_f);
static LinkNode_s * sortfun(LinkNode_s *quicklow_p, LinkNode_s *quickhigh_p, compare_f compareSort_f);
OperateReturn_e quickSort(LinkNode_s *quickhead_p,  LinkNode_s *quicktail_p, compare_f compareSort_f);

#endif
