cmake_minimum_required (VERSION 3.16)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)

  cmake_policy(SET CMP0141 NEW)
  
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
  
endif()

project ("RayTracer" VERSION 0.1 LANGUAGES CXX)

set( RayTracer_DataDir "${CMAKE_CURRENT_LIST_DIR}/Data" )

message( AAA ${RayTracer_DataDir})

add_subdirectory(Code)