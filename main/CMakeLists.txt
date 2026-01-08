FILE(GLOB_RECURSE app_sources *.*)
FILE(GLOB_RECURSE lib_sources ../lib/*.c)
idf_component_register(
  SRCS ${app_sources} ${lib_sources}
  INCLUDE_DIRS "." ".." "../lib"
)