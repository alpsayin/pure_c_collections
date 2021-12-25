

#include <iostream>
#include <map>
#include <string>
#include "argalparser.hpp"

#ifndef _ARGUTILS_CPP
#define _ARGUTILS_CPP

using std::cout;
using std::endl;
using std::map;
using std::string;

static map<string, arg_callback_f> arg_callback_map;

bool
example_callback(const char* arg_val)
{
  cout << "flag with no args found" << endl;
  return false; // dont skip next
}

bool
example_callback_with_argument(const char* arg_val)
{
  cout << "flag with param found: ";
  if (arg_val == NULL)
  {
    cout << "(NULL)" << endl;
    return true; // skip next arg
  }
  cout << "\"" << arg_val << "\"" << endl;
  return true; // skip next arg
}

void
assign_callback_to_arg(const char* arg, arg_callback_f arg_callback_func, const char* funcname)
{
  string key(arg);
  if (arg_callback_map.find(key) == arg_callback_map.end())
  {
    cout << "arg callback " << key << " assigned to " << funcname << endl;
  }
  else
  {
    cout << "Warning: arg callback " << key << " overwritten with " << funcname << endl;
  }
  arg_callback_map[key] = arg_callback_func;
}

void
assign_callback_to_arg(const char* arg, arg_callback_f arg_callback_func)
{
  string key(arg);
  if (arg_callback_map.find(key) != arg_callback_map.end())
  {
    cout << "Warning: arg callback " << key << " overwritten" << endl;
  }
  arg_callback_map[key] = arg_callback_func;
}

void
process_args(int argc, char const* argv[])
{
  for (int i = 0; i < argc; i++)
  {
    // cout << "Arg #" << i << " : \"" << argv[i] << '\"' << endl;
    auto it = arg_callback_map.find(string(argv[i]));
    if (it == arg_callback_map.end())
    {
      // not a known flag
      continue;
    }
    const char* param = (i + 1 < argc) ? argv[i + 1] : NULL;
    const bool should_skip_next = it->second(param);
    if (!should_skip_next) // return true means skip next argument
    {
      // argument processed. nothing else to do
      continue;
    }
    // parameter check before skipping next argument
    const auto check = arg_callback_map.find(string(argv[i + 1]));
    if (check == arg_callback_map.end())
    {
      i++; // only skip if the next argument is not a known flag
    }
    else
    {
      cout << "Warning: argument " << argv[i] << " entered without parameter" << endl;
    }
  }
}

#endif