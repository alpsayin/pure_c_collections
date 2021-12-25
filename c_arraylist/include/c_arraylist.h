

#ifndef _C_ARRAYLIST_H
#define _C_ARRAYLIST_H

#ifndef ARRAYLIST_DEBUG
#define ARRAYLIST_DEBUG 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if ARRAYLIST_DEBUG
#warning ARRAYLIST_DEBUG is set to true, define it as 0 to turn off prints in error conditions
#endif

// TODO: extend into a circulat buffer?

#define ARRAYLIST_DECLARE(_name, _type, _num_max_items) \
  struct _name##_construct \
  { \
    _type arr[_num_max_items]; \
    size_t len; \
  } _name = { { 0 }, 0 }

#define ARRAYLIST_SIZE(_name) (sizeof(_name.arr) / sizeof(_name.arr[0]))

#define ARRAYLIST_ELEM_SIZE(_name) sizeof(_name.arr[0])

#define ARRAYLIST_LEN(_name) (_name.len)

#define ARRAYLIST_APPEND(_name, _item) \
  do \
  { \
    if (ARRAYLIST_LEN(_name) < ARRAYLIST_SIZE(_name)) \
    { \
      _name.arr[ARRAYLIST_LEN(_name)] = _item; \
      ARRAYLIST_LEN(_name)++; \
    } \
    else if (ARRAYLIST_DEBUG) \
    { \
      printf("Append out of bounds %d: " #_name "\n", ARRAYLIST_SIZE(_name)); \
    } \
  } while (0)

#define ARRAYLIST_GET(_name, _index) (_name.arr[_index])

#define ARRAYLIST_REMOVE(_name, _index) \
  do \
  { \
    if (_index >= 0 && _index < ARRAYLIST_LEN(_name)) \
    { \
      for (size_t _name##_ii = _index; \
           _name##_ii + 1 < ARRAYLIST_LEN(_name) && _name##_ii + 1 < ARRAYLIST_SIZE(_name); \
           _name##_ii++) \
      { \
        _name.arr[_name##_ii] = _name.arr[_name##_ii + 1]; \
      } \
      ARRAYLIST_LEN(_name)--; \
    } \
    else if (ARRAYLIST_DEBUG) \
    { \
      printf("Remove index %d out of bounds: " #_name "\n", _index); \
    } \
  } while (0)

// TODO: some sort of iterator implementation for for-example item comparison
// TODO: ARRAYLIST_INSERT(_name, _index, _item) with shifting

#define ARRAYLIST_REPLACE(_name, _index, _item) \
  do \
  { \
    if (_index >= 0 && _index < ARRAYLIST_SIZE(_name)) \
    { \
      _name.arr[_index] = _item; \
      ARRAYLIST_LEN(_name) = _index + 1; \
    } \
    else if (ARRAYLIST_DEBUG) \
    { \
      printf("Insert index %d out of bounds: " #_name "\n", _index); \
    } \
  } while (0)

#define ARRAYLIST_RESET(_name) _name.len = 0

#define ARRAYLIST_CLEAR_INDEX(_name, _index) \
  do \
  { \
    if (_index >= 0 && _index < ARRAYLIST_SIZE(_name)) \
    { \
      _name.arr[_name##_ii] = { 0 }; \
    } \
    else if (ARRAYLIST_DEBUG) \
    { \
      printf("Clear index %d out of bounds: " #_name "\n", _index); \
    } \
  } while (0)

#define ARRAYLIST_CLEAR(_name) memset(&_name, 0, ARRAYLIST_SIZE(_name) * ARRAYLIST_ELEM_SIZE(_name))

void
arraylist_string_test(void);
void
arraylist_int_test(void);

#ifdef __cplusplus
}
#endif // extern C

#endif // #define _C_ARRAYLIST_H