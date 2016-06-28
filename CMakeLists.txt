cmake_minimum_required( VERSION 3.0 )

# Used to look for external modules
set( CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/CMake
	${CMAKE_SOURCE_DIR}/CMake/Modules
)
set( CMAKE_TEMPLATES_DIR ${CMAKE_SOURCE_DIR}/CMake/Templates )

project( FuryFighting )

include( ExternalDependencies )

# Organize projects into folders
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

# Prepare binary paths
if("${PROJECTS_BINARIES_OUTPUT_DIR}" STREQUAL "")
    set( PROJECTS_BINARIES_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Bin" CACHE PATH "The path to the built binaries" )
endif()

set( PROJECTS_BINARIES_OUTPUT_DIR_RELEASE ${PROJECTS_BINARIES_OUTPUT_DIR} )
set( PROJECTS_BINARIES_OUTPUT_DIR_DEBUG ${PROJECTS_BINARIES_OUTPUT_DIR} )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECTS_BINARIES_OUTPUT_DIR_DEBUG}" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECTS_BINARIES_OUTPUT_DIR_DEBUG}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECTS_BINARIES_OUTPUT_DIR_DEBUG}" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECTS_BINARIES_OUTPUT_DIR_RELEASE}" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECTS_BINARIES_OUTPUT_DIR_RELEASE}" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECTS_BINARIES_OUTPUT_DIR_RELEASE}" )

# Small macro to add subdirectory files to current target source and header files
macro( parse_subdir_files _FOLDER _GROUP )
	file( GLOB _FOLDER_HEADER_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/${_FOLDER}/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/${_FOLDER}/*.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/${_FOLDER}/*.inl
	)
	file( GLOB _FOLDER_SOURCE_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/${_FOLDER}/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/${_FOLDER}/*.cpp
	)
	source_group( "Header Files\\${_GROUP}" FILES ${_FOLDER_HEADER_FILES} )
	source_group( "Source Files\\${_GROUP}" FILES ${_FOLDER_SOURCE_FILES} )
endmacro()

# Look for needed libraries
find_package( OpenGL )

set( SDL_BUILDING_LIBRARY ON )
find_package( SDL )
find_package( SDL_image )

if( OPENGL_FOUND AND SDL_FOUND )
	add_definitions( "-DUSE_GLFW -D_CRT_SECURE_NO_WARNINGS" )

	include_directories(
		${GLEW_INCLUDE_DIR}
		${SDL_INCLUDE_DIR}
		${SDL_INCLUDE_DIR}/SDL
		${SDL_IMAGE_INCLUDE_DIR}
	)

	add_subdirectory( LMP3D )

	include_directories(
		${CMAKE_SOURCE_DIR}
	)

	set( BASE_LIBRARIES
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
		${GLEW_LIBRARY}
		${SDL_LIBRARY}
		${SDL_IMAGE_LIBRARY}
	)

	file( GLOB ${PROJECT_NAME}_HEADER_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/*.inl
	)

	file( GLOB ${PROJECT_NAME}_SOURCE_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/*.cc
	)

	add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES} )

	target_link_libraries( ${PROJECT_NAME}
		${BASE_LIBRARIES}
		LMP3D
	)

	copy_dll( ${PROJECT_NAME} ${SDL_LIBRARY} Debug )
	copy_dll( ${PROJECT_NAME} ${SDL_LIBRARY} Release )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_LIBRARY} Debug )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_LIBRARY} Release )
else()
	if ( NOT OPENGL_FOUND )
		message( SEND_ERROR "OpenGL library not found" )
	endif ()
	if ( NOT SDL_FOUND )
		message( SEND_ERROR "SDL library not found" )
	endif ()
endif()
