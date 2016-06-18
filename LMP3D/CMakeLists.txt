project( LMP3D )

include_directories(
	${CMAKE_SOURCE_DIR}
)

file( GLOB_RECURSE ${PROJECT_NAME}_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

file( GLOB_RECURSE ${PROJECT_NAME}_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc
)

add_library( ${PROJECT_NAME} STATIC ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_GFX_HEADER_FILES} ${${PROJECT_NAME}_GFX_SOURCE_FILES} )

target_link_libraries( ${PROJECT_NAME}
	${BASE_LIBRARIES}
)

parse_subdir_files( Graphics "Graphics" )
parse_subdir_files( Platform "Platform" )
parse_subdir_files( Graphics/Platform "Graphics\\\\Platform" )
