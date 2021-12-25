
#include <stdio.h>
#include <string.h>
#include "c_arraylist.h"
#include "c_linkedlist.h"
#include "argalparser.hpp"
#include "malloc.h"

static int num_mallocs = 0;
static int num_frees = 0;

void*
linkedlist_malloc(size_t _Size)
{
  num_mallocs++;
  return malloc(_Size);
}

void
linkedlist_free(void* _Memory)
{
  num_frees++;
  return free(_Memory);
}

int
main(int argc, char const* argv[])
{
  assign_callback_to_arg("-ex1", example_callback);
  assign_callback_to_arg("-ex2", example_callback_with_argument);

  process_args(argc, argv);

  // arraylist_string_test();
  // arraylist_int_test();

  linkedlist_int_test();
  linkedlist_string_test();

  printf("# malloc calls = %d\n", num_mallocs);
  printf("# free calls = %d\n", num_frees);

  return 0;
}