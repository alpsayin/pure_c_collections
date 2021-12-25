

#ifndef _C_LINKEDLIST_H
#define _C_LINKEDLIST_H

#ifndef LINKEDLIST_DEBUG
#define LINKEDLIST_DEBUG 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if LINKEDLIST_DEBUG
#warning LINKEDLIST_DEBUG is set to true, define it as 0 to turn off prints in error conditions
#endif

typedef enum LinkedList_Bool_TYPE
{
  LINKEDLIST_FALSE = 0,
  LINKEDLIST_TRUE
} LinkedList_Bool_e;

typedef enum LinkedList_Error_TYPE
{
  LINKEDLIST_OK = 0,
  LINKEDLIST_INVALID_SIZE,
  LINKEDLIST_IS_NULL,
  LINKEDLIST_NODE_IS_NULL,
  LINKEDLIST_ITEM_IS_NULL,
  LINKEDLIST_ITEM_PARAM_IS_NULL,
  LINKEDLIST_NODE_MALLOC_ERR,
  LINKEDLIST_ITEM_MALLOC_ERR,
  LINKEDLIST_INDEX_OUT_OF_BOUNDS,
} LinkedList_Error_e;

typedef enum LinkedList_CC_TYPE
{
  LINKEDLIST_SHALLOW = 0,
  LINKEDLIST_DEEP = 1,
} LinkedList_CC_e; // copy-compare type

typedef struct LinkedList_Node_TYPE
{
  void* next;
  void* prev;
  void* item;
  LinkedList_Bool_e isDeepCopy;
} LinkedList_Node_t;

typedef struct LinkedList_TYPE
{
  LinkedList_Node_t* first;
  LinkedList_Node_t* last;
  size_t len;
  size_t ELEM_SIZE;
} LinkedList_t;

#pragma weak linkedlist_malloc
void*
linkedlist_malloc(size_t _Size);

#pragma weak linkedlist_free
void
linkedlist_free(void* _Memory);

LinkedList_t
linkedlist_create(const size_t size, LinkedList_Error_e* pErr);

#define LINKEDLIST_NEW_ITEM(_pLinkedlist) linkedlist_malloc(_pLinkedlist->ELEM_SIZE)
#define LINKEDLIST_NODE(_node)            ((LinkedList_Node_t*)_node)

#define LINKEDLIST_DECLARE(_name)                          LinkedList_t _name
#define LINKEDLIST_INITIALISE(_name, _type, _pErr)         _name = linkedlist_create(sizeof(_type), _pErr)
#define LINKEDLIST_DECLARE_INITIALISE(_name, _type, _pErr) LinkedList_t _name = linkedlist_create(sizeof(_type), _pErr)

LinkedList_Node_t*
linkedlist_new_node();

size_t
linkedlist_elem_size(const LinkedList_t* pLinkedlist, LinkedList_Error_e* pErr);

size_t
linkedlist_len(const LinkedList_t* pLinkedlist, LinkedList_Error_e* pErr);

LinkedList_Error_e
linkedlist_append(LinkedList_t* pLinkedlist, void* pItem, LinkedList_CC_e copyType);

LinkedList_Error_e
linkedlist_push_back(LinkedList_t* pLinkedlist, void* pItem, LinkedList_CC_e copyType);

LinkedList_Error_e
linkedlist_push_front(LinkedList_t* pLinkedlist, void* pItem, LinkedList_CC_e copyType);

LinkedList_Error_e
linkedlist_pop_back(LinkedList_t* pLinkedlist, void* pItem, LinkedList_Bool_e freeItem);

LinkedList_Error_e
linkedlist_pop_front(LinkedList_t* pLinkedlist, void* pItem, LinkedList_Bool_e freeItem);

LinkedList_Error_e
linkedlist_peek_back(LinkedList_t* pLinkedlist, void* pItem);

LinkedList_Error_e
linkedlist_peek_front(LinkedList_t* pLinkedlist, void* pItem);

// TODO: push_back, push_front, pop_back, pop_front, peek, indexOf

LinkedList_Error_e
linkedlist_get(LinkedList_t* pLinkedlist, int index, void* pItem);

LinkedList_Error_e
linkedlist_remove(LinkedList_t* pLinkedlist, int index, LinkedList_Bool_e freeItem);

// TODO: iterator implementation so users can do comparison and stuff

LinkedList_Error_e
linkedlist_insert(LinkedList_t* pLinkedlist, int index, void* pItem, LinkedList_CC_e copyType);

LinkedList_Error_e
linkedlist_replace(LinkedList_t* pLinkedlist, int index, void* pItem, LinkedList_CC_e copyType);

LinkedList_Error_e
linkedlist_destroy(LinkedList_t* pLinkedlist, LinkedList_Bool_e freeItems);

void
linkedlist_string_test(void);
void
linkedlist_int_test(void);

#ifdef __cplusplus
}
#endif // extern C

#endif // #define _C_LINKEDLIST_H