file(GLOB_RECURSE SRC_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

add_executable(filemgr ${SRC_FILES})
target_link_libraries(filemgr raylib raygui)
target_include_directories(filemgr PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_target_properties(filemgr PROPERTIES LINK_SEARCH_START_STATIC ON)
set_target_properties(filemgr PROPERTIES LINK_SEARCH_END_STATIC ON)