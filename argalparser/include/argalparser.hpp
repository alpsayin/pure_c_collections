
#include <iostream>
#include <map>
#include <string>
#include <functional>

#ifndef _ARGUTILS_HPP
#define _ARGUTILS_HPP

using std::function;

/**
 * @brief argument_callback_f function type definition
 * @param arg_val c style string that contains the next argument or NULL if this was the last flag
 * @returns true if argument matcher should skip the next arg or false if it should not
 * (i.e. return true if the processor was expecting an argument)
 *
 */
using arg_callback_f = function<bool(const char*)>;

/**
 * @brief example arg_callback function that doesnt process the argument
 *
 * @param arg_val is not used in this function
 * @return false always because verbose flag doesnt process the next argument
 */
bool
example_callback(const char* arg_val);

/**
 * @brief example arg_callback function that processes the argument
 *
 * @param arg_val is simply printed out
 * @return true always because this flag processes the next argument
 */
bool
example_callback_with_argument(const char* arg_val);

// macro definition that inserts function name into call
#define assign_callback_to_arg_LOG(arg, arg_callback_func) \
  assign_callback_to_arg(arg, arg_callback_func, #arg_callback_func)

/**
 * @brief assigns a function of type arg_callback_f to an argument
 *
 * @param arg const string to be searched as an argument inside all arguments
 * @param arg_callback_func function to be called when argument is found
 * @param funcname function name as a c-string
 */
void
assign_callback_to_arg(const char* arg, arg_callback_f arg_callback_func, const char* funcname);

/**
 * @brief assigns a function of type arg_callback_f to an argument
 *
 * @param arg const string to be searched as an argument inside all arguments
 * @param arg_callback_func function to be called when argument is found
 */
void
assign_callback_to_arg(const char* arg, arg_callback_f arg_callback_func);

/**
 * @brief searches all arguments including the execution command for previously registered arguments and calls assigned
 * callback functions. The order of execution is in no way guaranteed as the map structure is not ordered.
 *
 * @param argc int argc to main
 * @param argv const char*[] to main
 */
void
process_args(int argc, char const* argv[]);

#endif