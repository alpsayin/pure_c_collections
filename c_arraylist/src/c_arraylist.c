

#include <stdio.h>
#include <string.h>

#define ARRAYLIST_DEBUG 1
#include "c_arraylist.h"

#ifndef _C_ARRAYLIST_C
#define _C_ARRAYLIST_C

typedef struct string_type
{
#define MAX_STRING_SIZE 64
  char buf[MAX_STRING_SIZE];
  int len;
} string_t;

void
arraylist_string_test()
{
  printf("\nDECLARE stringlist\n");
  ARRAYLIST_DECLARE(stringlist, string_t, 16);

  printf("Size = %d\n", ARRAYLIST_SIZE(stringlist));
  printf("Element size = %d ?= %d\n", ARRAYLIST_ELEM_SIZE(stringlist), sizeof(string_t));
  const size_t raw_size = sizeof(stringlist);
  const size_t storage_size = ARRAYLIST_SIZE(stringlist) * ARRAYLIST_ELEM_SIZE(stringlist);
  printf("Raw size = %d\n", raw_size);
  printf("Storage size = %d\n", storage_size);
  printf("Overhead = %d\n", raw_size - storage_size);
  printf("Len = %d\n%d\n", ARRAYLIST_LEN(stringlist));

  string_t new_item = { 0 };
  snprintf(new_item.buf, MAX_STRING_SIZE, "%s", "Hello World");
  new_item.len = strnlen(new_item.buf, MAX_STRING_SIZE);
  printf("\nAPPEND hello world\n");
  ARRAYLIST_APPEND(stringlist, new_item);
  printf("Len = %d\n%d\n", ARRAYLIST_LEN(stringlist));

  const string_t foobar = { "foobar", strlen("foobar") };
  printf("\nAPPEND foobar\n");
  ARRAYLIST_APPEND(stringlist, foobar);
  printf("Len = %d\n%d\n", ARRAYLIST_LEN(stringlist));

  printf("index 0: %s\n", ARRAYLIST_GET(stringlist, 0).buf);
  printf("index 1: %s\n", ARRAYLIST_GET(stringlist, 1).buf);
  printf("\nREMOVE\n");
  ARRAYLIST_REMOVE(stringlist, 0);
  printf("Len = %d\n", ARRAYLIST_LEN(stringlist));
  printf("index 0: %s\n", ARRAYLIST_GET(stringlist, 0).buf);
  printf("index 1: %s\n", ARRAYLIST_GET(stringlist, 1).buf);

  printf("\nREPLACE hello world to 2\n");
  ARRAYLIST_REPLACE(stringlist, 2, new_item);
  printf("Len = %d\n", ARRAYLIST_LEN(stringlist));
  printf("index 0: %s\n", ARRAYLIST_GET(stringlist, 0).buf);
  printf("index 1: %s\n", ARRAYLIST_GET(stringlist, 1).buf);
  printf("index 2: %s\n", ARRAYLIST_GET(stringlist, 2).buf);

  printf("\nIndexed remove\n");
  ARRAYLIST_REMOVE(stringlist, 1);
  printf("Len = %d\n", ARRAYLIST_LEN(stringlist));
  printf("index 0: %s\n", ARRAYLIST_GET(stringlist, 0).buf);
  printf("index 1: %s\n", ARRAYLIST_GET(stringlist, 1).buf);
  printf("index 2: %s\n", ARRAYLIST_GET(stringlist, 2).buf);

  printf("\nRESET\n");
  ARRAYLIST_RESET(stringlist);
  printf("Len = %d\n", ARRAYLIST_LEN(stringlist));
  printf("index 0: %s\n", ARRAYLIST_GET(stringlist, 0).buf);
  printf("index 1: %s\n", ARRAYLIST_GET(stringlist, 1).buf);
  printf("index 2: %s\n", ARRAYLIST_GET(stringlist, 2).buf);

  printf("\nCLEAR\n");
  ARRAYLIST_CLEAR(stringlist);
  printf("index 0: %s\n", ARRAYLIST_GET(stringlist, 0).buf);
  printf("index 1: %s\n", ARRAYLIST_GET(stringlist, 1).buf);
  printf("index 2: %s\n", ARRAYLIST_GET(stringlist, 2).buf);
}

void
arraylist_int_test()
{
  printf("\nDECLARE intlist\n");
  ARRAYLIST_DECLARE(intlist, int, 3);

  printf("Size = %d\n", ARRAYLIST_SIZE(intlist));
  const size_t raw_size = sizeof(intlist);
  const size_t storage_size = ARRAYLIST_SIZE(intlist) * ARRAYLIST_ELEM_SIZE(intlist);
  printf("Raw size = %d\n", raw_size);
  printf("Storage size = %d\n", storage_size);
  printf("Overhead = %d\n", raw_size - storage_size);
  printf("Len = %d\n", ARRAYLIST_LEN(intlist));

  int new_item = 42;
  printf("\nAPPEND 42\n");
  ARRAYLIST_APPEND(intlist, new_item);
  printf("Len = %d\n", ARRAYLIST_LEN(intlist));

  const int foobar = 314;
  printf("\nAPPEND %d\n", foobar);
  ARRAYLIST_APPEND(intlist, foobar);
  printf("Len = %d\n", ARRAYLIST_LEN(intlist));

  printf("index 0: %d\n", ARRAYLIST_GET(intlist, 0));
  printf("index 1: %d\n", ARRAYLIST_GET(intlist, 1));
  printf("REMOVE");
  ARRAYLIST_REMOVE(intlist, 0);
  printf("Len = %d\n", ARRAYLIST_LEN(intlist));
  printf("index 0: %d\n", ARRAYLIST_GET(intlist, 0));
  printf("index 1: %d\n", ARRAYLIST_GET(intlist, 1));

  printf("\nREPLACE 42 to 2\n");
  ARRAYLIST_REPLACE(intlist, 2, new_item);
  printf("Len = %d\n", ARRAYLIST_LEN(intlist));
  printf("index 0: %d\n", ARRAYLIST_GET(intlist, 0));
  printf("index 1: %d\n", ARRAYLIST_GET(intlist, 1));
  printf("index 2: %d\n", ARRAYLIST_GET(intlist, 2));

  printf("\nRESET\n");
  ARRAYLIST_RESET(intlist);
  printf("Len = %d\n", ARRAYLIST_LEN(intlist));
  printf("index 0: %d\n", ARRAYLIST_GET(intlist, 0));
  printf("index 1: %d\n", ARRAYLIST_GET(intlist, 1));
  printf("index 2: %d\n", ARRAYLIST_GET(intlist, 2));

  printf("\nCLEAR\n");
  ARRAYLIST_CLEAR(intlist);
  printf("index 0: %d\n", ARRAYLIST_GET(intlist, 0));
  printf("index 1: %d\n", ARRAYLIST_GET(intlist, 1));
  printf("index 2: %d\n", ARRAYLIST_GET(intlist, 2));

  printf("\nOUT OF BOUNDS REPLACE\n");
  ARRAYLIST_REPLACE(intlist, 18, 18);

  printf("\nFULL LIST\n");
  ARRAYLIST_APPEND(intlist, 1);
  ARRAYLIST_APPEND(intlist, 2);
  ARRAYLIST_APPEND(intlist, 3);
  ARRAYLIST_APPEND(intlist, 4);
  ARRAYLIST_APPEND(intlist, 5);
}

#endif // #define _C_ARRAYLIST_C