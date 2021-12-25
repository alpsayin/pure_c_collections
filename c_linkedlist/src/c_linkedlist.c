

#include <stdio.h>
#include <string.h>
#if __has_include("malloc.h")
#include "malloc.h"
#define _TARGET_HAS_MALLOC 1
#else
#define _TARGET_HAS_MALLOC 0
#warning malloc.h couldnt be found. You have to implement linkedlist_malloc & linkedlist_free yourself.
#endif

#define LINKEDLIST_DEBUG 1
#include "c_linkedlist.h"

#ifndef _C_LINKEDLIST_C
#define _C_LINKEDLIST_C

void*
linkedlist_malloc(size_t _Size)
{
#if _TARGET_HAS_MALLOC
  return malloc(_Size);
#endif
}

void
linkedlist_free(void* _Memory)
{
#if _TARGET_HAS_MALLOC
  return free(_Memory);
#endif
}

LinkedList_Node_t*
linkedlist_new_node()
{
  LinkedList_Node_t* new_node = linkedlist_malloc(sizeof(LinkedList_Node_t));
  if (new_node == NULL)
  {
    return NULL;
  }
  new_node->item = NULL;
  new_node->next = NULL;
  new_node->prev = NULL;
  new_node->isDeepCopy = LINKEDLIST_FALSE;
  return new_node;
}

LinkedList_t
linkedlist_create(const size_t size, LinkedList_Error_e* pErr)
{
  if (size == 0)
  {
    if (pErr != NULL)
    {
      *pErr = LINKEDLIST_INVALID_SIZE;
    }
  }
  LinkedList_t new_linkedlist = { NULL, NULL, 0, size };
  return new_linkedlist;
}

size_t
linkedlist_elem_size(const LinkedList_t* pLinkedlist, LinkedList_Error_e* pErr)
{
  if (pLinkedlist == NULL)
  {
    if (pErr != NULL)
    {
      *pErr = LINKEDLIST_IS_NULL;
    }
  }
  return pLinkedlist->ELEM_SIZE;
}

size_t
linkedlist_len(const LinkedList_t* pLinkedlist, LinkedList_Error_e* pErr)
{
  if (pLinkedlist == NULL)
  {
    if (pErr != NULL)
    {
      *pErr = LINKEDLIST_IS_NULL;
    }
  }
  return pLinkedlist->len;
}

LinkedList_Error_e
linkedlist_append(LinkedList_t* pLinkedlist, void* pItem, LinkedList_CC_e copyType)
{
  LinkedList_Node_t* new_node = NULL;
  if (pLinkedlist == NULL)
  {
    return LINKEDLIST_IS_NULL;
  }
  if (copyType == LINKEDLIST_DEEP && pItem == NULL)
  {
    return LINKEDLIST_ITEM_PARAM_IS_NULL;
  }
  new_node = linkedlist_new_node();
  if (new_node == NULL)
  {
    return LINKEDLIST_NODE_MALLOC_ERR;
  }
  if (copyType == LINKEDLIST_DEEP)
  {
    new_node->item = LINKEDLIST_NEW_ITEM(pLinkedlist);
    if (new_node->item == NULL)
    {
      linkedlist_free(new_node);
      return LINKEDLIST_ITEM_MALLOC_ERR;
    }
    memcpy(new_node->item, pItem, pLinkedlist->ELEM_SIZE);
    new_node->isDeepCopy = LINKEDLIST_TRUE;
  }
  else
  {
    new_node->item = pItem;
  }
  if (pLinkedlist->len == 0)
  {
    pLinkedlist->first = new_node;
    pLinkedlist->last = new_node;
  }
  else
  {
    new_node->prev = pLinkedlist->last;
    pLinkedlist->last->next = new_node;
    pLinkedlist->last = new_node;
  }

  pLinkedlist->len++;
  return LINKEDLIST_OK;
}

LinkedList_Error_e
linkedlist_push_back(LinkedList_t* pLinkedlist, void* pItem, LinkedList_CC_e copyType)
{
  LinkedList_Error_e sizeErr = LINKEDLIST_OK;
  int lastIndex = linkedlist_len(pLinkedlist, &sizeErr);
  if (sizeErr != LINKEDLIST_OK)
  {
    return sizeErr;
  }
  return linkedlist_insert(pLinkedlist, lastIndex, pItem, copyType);
}

LinkedList_Error_e
linkedlist_push_front(LinkedList_t* pLinkedlist, void* pItem, LinkedList_CC_e copyType)
{
  return linkedlist_insert(pLinkedlist, 0, pItem, copyType);
}

LinkedList_Error_e
linkedlist_pop_back(LinkedList_t* pLinkedlist, void* pItem, LinkedList_Bool_e freeItem)
{
  LinkedList_Error_e err = LINKEDLIST_OK;
  int lastIndex = linkedlist_len(pLinkedlist, &err);
  if (err != LINKEDLIST_OK)
  {
    return err;
  }
  err = linkedlist_get(pLinkedlist, lastIndex - 1, pItem);
  if (err != LINKEDLIST_OK)
  {
    return err;
  }
  return linkedlist_remove(pLinkedlist, lastIndex - 1, freeItem);
}

LinkedList_Error_e
linkedlist_pop_front(LinkedList_t* pLinkedlist, void* pItem, LinkedList_Bool_e freeItem)
{
  LinkedList_Error_e err = LINKEDLIST_OK;
  err = linkedlist_get(pLinkedlist, 0, pItem);
  if (err != LINKEDLIST_OK)
  {
    return err;
  }
  return linkedlist_remove(pLinkedlist, 0, freeItem);
}

LinkedList_Error_e
linkedlist_peek_back(LinkedList_t* pLinkedlist, void* pItem)
{
  LinkedList_Error_e err = LINKEDLIST_OK;
  int lastIndex = linkedlist_len(pLinkedlist, &err);
  if (err != LINKEDLIST_OK)
  {
    return err;
  }
  return linkedlist_get(pLinkedlist, lastIndex - 1, pItem);
}

LinkedList_Error_e
linkedlist_peek_front(LinkedList_t* pLinkedlist, void* pItem)
{
  return linkedlist_get(pLinkedlist, 0, pItem);
}

LinkedList_Error_e
linkedlist_get(LinkedList_t* pLinkedlist, int index, void* pItem)
{
  LinkedList_Node_t* ptr = NULL;
  if (pLinkedlist == NULL)
  {
    return LINKEDLIST_IS_NULL;
  }
  if (pItem == NULL)
  {
    return LINKEDLIST_ITEM_PARAM_IS_NULL;
  }
  if (index < 0 || index >= pLinkedlist->len)
  {
    return LINKEDLIST_INDEX_OUT_OF_BOUNDS;
  }
  ptr = pLinkedlist->first;
  for (size_t ii = 0; ii < index; ii++)
  {
    ptr = ptr->next;
  }
  if (ptr->item == NULL)
  {
    return LINKEDLIST_ITEM_IS_NULL;
  }
  memcpy(pItem, ptr->item, pLinkedlist->ELEM_SIZE);
  return LINKEDLIST_OK;
}

LinkedList_Error_e
linkedlist_remove(LinkedList_t* pLinkedlist, int index, LinkedList_Bool_e freeItem)
{
  LinkedList_Node_t* ptr = NULL;
  if (pLinkedlist == NULL)
  {
    return LINKEDLIST_IS_NULL;
  }
  if (index < 0 || index >= pLinkedlist->len)
  {
    return LINKEDLIST_INDEX_OUT_OF_BOUNDS;
  }
  ptr = pLinkedlist->first;
  for (size_t ii = 0; ii < index; ii++)
  {
    ptr = ptr->next;
  }
  if (index == 0)
  {
    pLinkedlist->first = pLinkedlist->first->next;
  }
  else if (index == pLinkedlist->len - 1)
  {
    pLinkedlist->last = pLinkedlist->last->prev;
  }
  if (ptr->prev != NULL)
  {
    LINKEDLIST_NODE(ptr->prev)->next = ptr->next;
  }
  if (ptr->next != NULL)
  {
    LINKEDLIST_NODE(ptr->next)->prev = ptr->prev;
  }
  if (freeItem != 0)
  {
    if (ptr->isDeepCopy)
    {
      linkedlist_free(ptr->item);
    }
  }
  linkedlist_free(ptr);
  pLinkedlist->len--;
  return LINKEDLIST_OK;
}

LinkedList_Error_e
linkedlist_insert(LinkedList_t* pLinkedlist, int index, void* pItem, LinkedList_CC_e copyType)
{
  LinkedList_Node_t* ptr = NULL;
  if (index == pLinkedlist->len)
  {
    return linkedlist_append(pLinkedlist, pItem, copyType);
  }
  if (pLinkedlist == NULL)
  {
    return LINKEDLIST_IS_NULL;
  }
  if (index < 0 || index > pLinkedlist->len)
  {
    return LINKEDLIST_INDEX_OUT_OF_BOUNDS;
  }
  if (copyType == LINKEDLIST_DEEP && pItem == NULL)
  {
    return LINKEDLIST_ITEM_PARAM_IS_NULL;
  }
  ptr = pLinkedlist->first;
  for (size_t ii = 0; ii < index; ii++)
  {
    ptr = ptr->next;
  }
  LinkedList_Node_t* new_node = linkedlist_new_node();
  if (new_node == NULL)
  {
    return LINKEDLIST_NODE_MALLOC_ERR;
  }
  if (copyType == LINKEDLIST_DEEP)
  {
    new_node->item = LINKEDLIST_NEW_ITEM(pLinkedlist);
    if (new_node->item == NULL)
    {
      linkedlist_free(new_node);
      return LINKEDLIST_ITEM_MALLOC_ERR;
    }
    memcpy(new_node->item, pItem, pLinkedlist->ELEM_SIZE);
    new_node->isDeepCopy = LINKEDLIST_TRUE;
  }
  else
  {
    new_node->item = pItem;
  }
  if (ptr != pLinkedlist->first)
  {
    LINKEDLIST_NODE(ptr->prev)->next = new_node;
  }
  new_node->prev = ptr->prev;
  new_node->next = ptr;
  ptr->prev = new_node;
  if (index == 0)
  {
    pLinkedlist->first = new_node;
  }
  pLinkedlist->len++;
  return LINKEDLIST_OK;
}

LinkedList_Error_e
linkedlist_replace(LinkedList_t* pLinkedlist, int index, void* pItem, LinkedList_CC_e copyType)
{
  LinkedList_Node_t* ptr = NULL;
  if (pLinkedlist == NULL)
  {
    return LINKEDLIST_IS_NULL;
  }
  if (index < 0 || index >= pLinkedlist->len)
  {
    return LINKEDLIST_INDEX_OUT_OF_BOUNDS;
  }
  if (copyType == LINKEDLIST_DEEP && pItem == NULL)
  {
    return LINKEDLIST_ITEM_PARAM_IS_NULL;
  }
  ptr = pLinkedlist->first;
  for (size_t ii = 0; ii < index; ii++)
  {
    ptr = ptr->next;
  }
  if (copyType == LINKEDLIST_DEEP)
  {
    if (ptr->item == NULL)
    {
      return LINKEDLIST_ITEM_IS_NULL;
    }
    memcpy(ptr->item, pItem, pLinkedlist->ELEM_SIZE);
  }
  else
  {
    ptr->item = pItem;
  }
  return LINKEDLIST_OK;
}

LinkedList_Error_e
linkedlist_destroy(LinkedList_t* pLinkedlist, LinkedList_Bool_e freeItems)
{
  LinkedList_Node_t* ptr = NULL;
  LinkedList_Node_t* nextPtr = NULL;
  if (pLinkedlist->len == 0)
  {
    return LINKEDLIST_OK;
  }

  ptr = pLinkedlist->first;
  while (ptr != NULL)
  {
    if (freeItems != 0)
    {
      if (ptr->isDeepCopy)
      {
        linkedlist_free(ptr->item);
      }
    }
    nextPtr = ptr->next;
    linkedlist_free(ptr);
    ptr = nextPtr;
  }
  pLinkedlist->len = 0;
  pLinkedlist->first = NULL;
  pLinkedlist->last = NULL;
  return LINKEDLIST_OK;
}

LINKEDLIST_DECLARE(genericList);

void
linkedlist_string_test()
{
  LinkedList_Error_e err = LINKEDLIST_OK;
  int result = -1;
  LINKEDLIST_INITIALISE(genericList, char[64], &err);
  linkedlist_append(&genericList, "alp sayin", LINKEDLIST_DEEP);
  char can[64] = "can sayin\0";
  linkedlist_append(&genericList, can, LINKEDLIST_SHALLOW);
  linkedlist_append(&genericList, can, LINKEDLIST_DEEP);

  printf("\nPRINT\n");
  for (int ii = 0; ii < linkedlist_len(&genericList, NULL); ii++)
  {
    char buf[64];
    err = linkedlist_get(&genericList, ii, &buf);
    printf("index %d: %s, err = %x\n", ii, buf, err);
  }
  can[0] = 'C';
  can[4] = 'S';
  printf("%s\n", can);
  for (int ii = 0; ii < linkedlist_len(&genericList, NULL); ii++)
  {
    char buf[64];
    err = linkedlist_get(&genericList, ii, &buf);
    printf("index %d: %s, err = %x\n", ii, buf, err);
  }

  linkedlist_destroy(&genericList, LINKEDLIST_TRUE);
}

void
linkedlist_int_test()
{
  LinkedList_Error_e err = LINKEDLIST_OK;
  int result = -1;

  printf("\nDECLARE & INITIALISE intlist\n");
  LINKEDLIST_DECLARE_INITIALISE(intlist, int, &err);

  const size_t raw_size = sizeof(intlist);
  printf("Raw size = %d\n", raw_size);
  printf("Len = %d\n", linkedlist_len(&intlist, &err));

  int new_item = 42;
  printf("\nAPPEND 42\n");
  err = linkedlist_append(&intlist, &new_item, LINKEDLIST_SHALLOW);
  if (err != LINKEDLIST_OK)
  {
    printf("err = %d\n", err);
  }
  printf("Len = %d\n", linkedlist_len(&intlist, &err));

  int foobar = 314;
  printf("\nAPPEND %d\n", foobar);
  err = linkedlist_append(&intlist, &foobar, LINKEDLIST_DEEP);
  if (err != LINKEDLIST_OK)
  {
    printf("err = %d\n", err);
  }
  printf("Len = %d\n", linkedlist_len(&intlist, &err));

  err = linkedlist_get(&intlist, 0, &result);
  if (err != LINKEDLIST_OK)
  {
    printf("err = %d\n", err);
  }
  printf("index 0: %d\n", result);
  err = linkedlist_get(&intlist, 1, &result);
  printf("index 1: %d\n", result);

  printf("\nChange shallow copied items value\n");
  new_item = 420;
  err = linkedlist_get(&intlist, 0, &result);
  printf("index 0: %d\n", result);
  err = linkedlist_get(&intlist, 1, &result);
  printf("index 1: %d\n", result);

  printf("\nChange deep copied items value\n");
  foobar = 1618;
  err = linkedlist_get(&intlist, 0, &result);
  printf("index 0: %d\n", result);
  err = linkedlist_get(&intlist, 1, &result);
  printf("index 1: %d\n", result);

  printf("\nREMOVE\n");
  err = linkedlist_remove(&intlist, 0, 0);
  printf("Len = %d\n", linkedlist_len(&intlist, &err));
  err = linkedlist_get(&intlist, 0, &result);
  printf("index 0: %d\n", result);
  err = linkedlist_get(&intlist, 1, &result);
  if (err != LINKEDLIST_OK)
  {
    printf("err = %d\n", err);
  }
  printf("index 1: %d\n", result);

  printf("\nINSERT 11 to 1\n");
  foobar = 11;
  err = linkedlist_insert(&intlist, 1, &foobar, LINKEDLIST_DEEP);
  printf("\nINSERT 22 to 2\n");
  foobar = 22;
  err = linkedlist_insert(&intlist, 2, &foobar, LINKEDLIST_DEEP);
  printf("Len = %d\n", linkedlist_len(&intlist, &err));
  err = linkedlist_get(&intlist, 0, &result);
  printf("index 0: %d\n", result);
  err = linkedlist_get(&intlist, 1, &result);
  printf("index 1: %d\n", result);
  err = linkedlist_get(&intlist, 2, &result);
  printf("index 2: %d\n", result);

  printf("\nINSERT 1122 to 2\n");
  foobar = 1122;
  err = linkedlist_insert(&intlist, 1, &foobar, LINKEDLIST_DEEP);
  err = linkedlist_get(&intlist, 0, &result);
  printf("index 0: %d\n", result);
  err = linkedlist_get(&intlist, 1, &result);
  printf("index 1: %d\n", result);
  err = linkedlist_get(&intlist, 2, &result);
  printf("index 2: %d\n", result);
  err = linkedlist_get(&intlist, 3, &result);
  printf("index 3: %d\n", result);

  printf("\nINSERT 3344 to 3\n");
  foobar = 3344;
  err = linkedlist_insert(&intlist, 3, &foobar, LINKEDLIST_DEEP);
  err = linkedlist_get(&intlist, 0, &result);
  printf("index 0: %d\n", result);
  err = linkedlist_get(&intlist, 1, &result);
  printf("index 1: %d\n", result);
  err = linkedlist_get(&intlist, 2, &result);
  printf("index 2: %d\n", result);
  err = linkedlist_get(&intlist, 3, &result);
  printf("index 3: %d\n", result);
  err = linkedlist_get(&intlist, 4, &result);
  printf("index 4: %d\n", result);
  printf("Len = %d, err=%x\n", linkedlist_len(&intlist, &err), err);

  printf("\nRESET\n");
  linkedlist_destroy(&intlist, LINKEDLIST_TRUE);
  printf("Len = %d, err=%x\n", linkedlist_len(&intlist, &err), err);

  foobar = 3;
  err = linkedlist_append(&intlist, &foobar, LINKEDLIST_DEEP);
  printf("err = %x\n", err);
  foobar = 2;
  err = linkedlist_push_front(&intlist, &foobar, LINKEDLIST_DEEP);
  printf("err = %x\n", err);
  err = linkedlist_peek_front(&intlist, &foobar);
  printf("front peek: %d, correct? %x\n", foobar, foobar == 2);

  foobar = 4;
  err = linkedlist_push_back(&intlist, &foobar, LINKEDLIST_DEEP);
  printf("err = %x\n", err);
  err = linkedlist_peek_back(&intlist, &foobar);
  printf("back peek: %d, correct? %x\n", foobar, foobar == 4);

  foobar = 1;
  err = linkedlist_push_front(&intlist, &foobar, LINKEDLIST_DEEP);
  printf("err = %x\n", err);

  for (int ii = 0; ii < 5; ii++)
  {
    err = linkedlist_get(&intlist, ii, &result);
    printf("index %d: %d, err = %x\n", ii, result, err);
  }

  printf("\nPRINT\n");
  for (int ii = 0; ii < 5; ii++)
  {
    err = linkedlist_get(&intlist, ii, &result);
    printf("index %d: %d, err = %x\n", ii, result, err);
  }

  printf("\nRESET\n");
  linkedlist_destroy(&intlist, LINKEDLIST_TRUE);
  printf("Len = %d, err=%x\n", linkedlist_len(&intlist, &err), err);

  printf("\nPUSH-PEEK FRONT\n");
  for (int ii = 0; ii < 5; ii++)
  {
    err = linkedlist_push_front(&intlist, &ii, LINKEDLIST_DEEP);
    printf("err = %x\n", err);
    err = linkedlist_peek_front(&intlist, &foobar);
    printf("err = %x, front peek: %d, correct? %x\n", err, foobar, foobar == ii);
  }

  printf("\nPRINT\n");
  for (int ii = 0; ii < 5; ii++)
  {
    err = linkedlist_get(&intlist, ii, &result);
    printf("index %d: %d, err = %x\n", ii, result, err);
  }

  printf("\nPOP FRONT\n");
  for (int ii = 4; ii >= 0; ii--)
  {
    err = linkedlist_pop_front(&intlist, &foobar, LINKEDLIST_TRUE);
    printf("err = %x, front pop: %d, correct? %x\n", err, foobar, foobar == ii);
  }

  printf("\nPUSH-PEEK BACK\n");
  for (int ii = 0; ii < 5; ii++)
  {
    err = linkedlist_push_back(&intlist, &ii, LINKEDLIST_DEEP);
    printf("err = %x\n", err);
    err = linkedlist_peek_back(&intlist, &foobar);
    printf("err = %x, back peek: %d, correct? %x\n", err, foobar, foobar == ii);
  }

  printf("\nPRINT\n");
  for (int ii = 0; ii < 5; ii++)
  {
    err = linkedlist_get(&intlist, ii, &result);
    printf("index %d: %d, err = %x\n", ii, result, err);
  }

  printf("\nPOP BACK\n");
  for (int ii = 4; ii >= 0; ii--)
  {
    err = linkedlist_pop_back(&intlist, &foobar, LINKEDLIST_TRUE);
    printf("err = %x, back pop: %d, correct? %x\n", err, foobar, foobar == ii);
  }

  printf("\nOUT OF BOUNDS INSERT\n");
  foobar = 18;
  err = linkedlist_insert(&intlist, 18, &foobar, LINKEDLIST_DEEP);
  printf("err = %x\n", err);

  // printf("\nFULL LIST\n");
  // LINKEDLIST_APPEND(intlist, 1);
  // LINKEDLIST_APPEND(intlist, 2);
  // LINKEDLIST_APPEND(intlist, 3);
  // LINKEDLIST_APPEND(intlist, 4);
  // LINKEDLIST_APPEND(intlist, 5);
}

#endif // #define _C_LINKEDLIST_C