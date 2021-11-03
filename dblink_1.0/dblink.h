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
	INIT_FAIL
}OperateReturn_e;
/*
typedef enum deletereturn{
        DELETE_OK,
        DELETE_FAIL
}DeleteReturn_e;
*/
typedef bool (*_Compare_f)(void *, void *);
typedef void (*_ListLink_f)(void *);
LinkHome_s *_InitLink();
static LinkNode_s *_NodeCreate(void *value);
static LinkNode_s *_GetSite(LinkHome_s *head_p, int site);
OperateReturn_e _InsertSite(LinkHome_s *head_p, int site, void *value);
OperateReturn_e _InsertTail(LinkHome_s *head_p, void *value);
OperateReturn_e _FindSiteValue(LinkHome_s *head_p, int site, _ListLink_f _PrintLink_f);
OperateReturn_e _ShowHeadLink(LinkHome_s *link_p,  _ListLink_f _PrintLink_f);
OperateReturn_e _ShowTailLink(LinkHome_s *link_p,  _ListLink_f _PrintLink_f);
OperateReturn_e _DeleteNode(LinkHome_s *head_p, int site, _ListLink_f _FreeDefine_f);
OperateReturn_e _DestoryLink(LinkHome_s *head_p, _ListLink_f _FreeDefine_f);
static LinkNode_s * _Sortfun(LinkNode_s *quicklow_p, LinkNode_s *quickhigh_p, _Compare_f _CompareSort_f);
OperateReturn_e _QuickSort(LinkNode_s *quickhead_p,  LinkNode_s *quicktail_p, _Compare_f _CompareSort_f);

#endif
