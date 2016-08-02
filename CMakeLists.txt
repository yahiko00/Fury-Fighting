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

if ( DREAMCAST )
	include_directories(
		$ENV{KOS_BASE}/include
		$ENV{KOS_BASE}/addons/include
		$ENV{KOS_BASE}/../kos-ports/include
	)

	link_directories(
		$ENV{KOS_BASE}/lib/$ENV{KOS_ARCH}
		$ENV{KOS_BASE}/addons/lib/$ENV{KOS_ARCH}
		$ENV{KOS_BASE}/lib
	)
	
	set( BASE_LIBRARIES
		GL
		SDL
		png
		z
		m
		kallisti
		stdc++
		gcc
		c
	)
	
	set( PLATFORM Dreamcast )
	set( IS_OK TRUE )
else ()
	# Look for needed libraries
	find_package( OpenGL )

	set( SDL_BUILDING_LIBRARY ON )
	find_package( SDL )
	find_package( SDL_image )
	

	if( OPENGL_FOUND AND SDL_FOUND )
		add_definitions( "-DUSE_GLFW -D_CRT_SECURE_NO_WARNINGS" )

		include_directories(
			${SDL_INCLUDE_DIR}
			${SDL_INCLUDE_DIR}/SDL
			${SDL_IMAGE_INCLUDE_DIR}
		)

		set( BASE_LIBRARIES
			${OPENGL_gl_LIBRARY}
			${OPENGL_glu_LIBRARY}
			${GLEW_LIBRARY}
			${SDL_LIBRARY}
			${SDL_IMAGE_LIBRARY}
		)

		set( PLATFORM Desktop )		
		set( IS_OK TRUE )
	endif ()
endif ()

if( ${IS_OK} )
	add_definitions( "-DUSE_GLFW -D_CRT_SECURE_NO_WARNINGS" )

	add_subdirectory( LMP3D )

	include_directories(
		${CMAKE_SOURCE_DIR}
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

	if ( "Dreamcast" STREQUAL ${PLATFORM} )
		set( ROMDISK_DATA romdisk )
		set( ROMDISK_IMG ${ROMDISK_DATA}.img )
		set( ROMDISK_OBJ ${ROMDISK_DATA}.o )
		add_custom_command(
			OUTPUT ${ROMDISK_IMG}
			COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Bin/DATA ${ROMDISK_DATA}
			COMMAND ${KOS_GENROMFS} -f ${ROMDISK_IMG} -d ${ROMDISK_DATA} -v
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating ${ROMDISK_IMG}"
		)
		add_custom_command(
			OUTPUT ${ROMDISK_OBJ}
			COMMAND ${KOS_BIN2O} ${ROMDISK_IMG} ${ROMDISK_DATA} ${ROMDISK_OBJ}
			DEPENDS ${ROMDISK_IMG}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating ${ROMDISK_OBJ}"
		)
		add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES} ${CMAKE_CURRENT_BINARY_DIR}/${ROMDISK_OBJ} )
	else ()
		add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES} )
	endif ()

	target_link_libraries( ${PROJECT_NAME}
		${BASE_LIBRARIES}
		LMP3D
	)

	if ( "Desktop" STREQUAL ${PLATFORM} )
		copy_dll( ${PROJECT_NAME} ${SDL_LIBRARY} Debug )
		copy_dll( ${PROJECT_NAME} ${SDL_LIBRARY} Release )
		copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_LIBRARY} Debug )
		copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_LIBRARY} Release )
	endif ()
else()
	if ( NOT OPENGL_FOUND )
		message( SEND_ERROR "OpenGL library not found" )
	endif ()
	if ( NOT SDL_FOUND )
		message( SEND_ERROR "SDL library not found" )
	endif ()
endif()
