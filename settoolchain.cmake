
macro(auto_set_toolchain)
  
if(NOT DEFINED IS_TOOLCHAIN_SET)

message("Starting auto set toolchain")

set(CMAKE_SYSTEM_NAME Generic CACHE INTERNAL "")
set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "")
#  specify the cross compiler
if(WIN32)
set(toolchain "c:/SysGCC/mingw32" CACHE INTERNAL "")
set(TOOLCHAIN_EXECUTABLE_EXTENSION .exe CACHE INTERNAL "")
set(CMAKE_MAKE_PROGRAM "${toolchain}/bin/mingw32-make${TOOLCHAIN_EXECUTABLE_EXTENSION}" CACHE INTERNAL "")
elseif(UNIX)
set(toolchain "/usr/bin/" CACHE INTERNAL "")
set(TOOLCHAIN_EXECUTABLE_EXTENSION CACHE INTERNAL "")
set(CMAKE_MAKE_PROGRAM "${toolchain}/bin/make${TOOLCHAIN_EXECUTABLE_EXTENSION}" CACHE INTERNAL "")
else()
message(FATAL_ERROR "Unsupported platform.")
endif()

set(CMAKE_C_COMPILER "${toolchain}/bin/gcc${TOOLCHAIN_EXECUTABLE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_CXX_COMPILER "${toolchain}/bin/g++${TOOLCHAIN_EXECUTABLE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_OBJSIZE "${toolchain}/bin/size${TOOLCHAIN_EXECUTABLE_EXTENSION}" CACHE INTERNAL "")
set(CMAKE_OBJCOPY "${toolchain}/bin/objcopy${TOOLCHAIN_EXECUTABLE_EXTENSION}" CACHE INTERNAL "")

set(IS_TOOLCHAIN_SET true CACHE INTERNAL "")

endif()

message("Make program is " ${CMAKE_MAKE_PROGRAM})

endmacro()