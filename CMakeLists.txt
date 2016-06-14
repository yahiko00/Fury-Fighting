cmake_minimum_required( VERSION 3.0 )

# Used to look for external modules
set( CMAKE_MODULE_PATH
	${CMAKE_SOURCE_DIR}/CMake
	${CMAKE_SOURCE_DIR}/CMake/Modules
)
set( CMAKE_TEMPLATES_DIR ${CMAKE_SOURCE_DIR}/CMake/Templates )

project( FuryFighting )

# Organize projects into folders
set_property( GLOBAL PROPERTY USE_FOLDERS ON )

# Detect used platform (x64 ou x86)
set( PROJECTS_PLATFORM "x86" )

if(MSVC)
	if( (CMAKE_CL_64 OR CMAKE_GENERATOR MATCHES Win64) )
		set( PROJECTS_PLATFORM_FLAGS "/MACHINE:X64" )
		set( PROJECTS_PLATFORM "x64" )
	else()
		set( PROJECTS_PLATFORM_FLAGS "/MACHINE:X86" )
	endif()
else()
	if( (${CMAKE_SIZEOF_VOID_P} EQUAL 8) AND NOT MINGW )
		set( PROJECTS_PLATFORM_FLAGS "-m64" )
		set( PROJECTS_PLATFORM "x64" )
	else()
		set( PROJECTS_PLATFORM_FLAGS "-m32" )
	endif()
endif()

# Prepare binary paths
if("${PROJECTS_BINARIES_OUTPUT_DIR}" STREQUAL "")
    set( PROJECTS_BINARIES_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/binaries/${PROJECTS_PLATFORM}" CACHE PATH "The path to the built binaries" )
endif()

set( PROJECTS_BINARIES_OUTPUT_DIR_RELEASE ${PROJECTS_BINARIES_OUTPUT_DIR}/Release )
set( PROJECTS_BINARIES_OUTPUT_DIR_DEBUG ${PROJECTS_BINARIES_OUTPUT_DIR}/Debug )

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${PROJECTS_BINARIES_OUTPUT_DIR_DEBUG}/lib/" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECTS_BINARIES_OUTPUT_DIR_DEBUG}/lib/" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECTS_BINARIES_OUTPUT_DIR_DEBUG}/bin/" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${PROJECTS_BINARIES_OUTPUT_DIR_RELEASE}/lib/" )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECTS_BINARIES_OUTPUT_DIR_RELEASE}/lib/" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECTS_BINARIES_OUTPUT_DIR_RELEASE}/bin/" )

# Look for needed libraries
find_package( OpenGL )
find_package( GLEW )
find_package( GLM )
find_package( GLFW )
find_package( PNG )

if( OPENGL_FOUND AND GLEW_FOUND AND GLFW_FOUND AND GLM_FOUND AND PNG_FOUND )
	add_definitions( "-DUSE_GLFW -D_CRT_SECURE_NO_WARNINGS" )
	include_directories(
		${CMAKE_SOURCE_DIR}/Src
		${GLEW_INCLUDE_DIR}
		${GLFW_INCLUDE_DIR}
		${GLM_INCLUDE_DIR}
		${PNG_INCLUDE_DIRS}
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

	file( GLOB ${PROJECT_NAME}_MNS_HEADER_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/MNS/*.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/MNS/*.h
		${CMAKE_CURRENT_SOURCE_DIR}/MNS/*.inl
	)

	file( GLOB ${PROJECT_NAME}_MNS_SOURCE_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/MNS/*.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/MNS/*.c
		${CMAKE_CURRENT_SOURCE_DIR}/MNS/*.cc
	)

	source_group( "Header Files\\MNS" FILES ${${PROJECT_NAME}_MNS_HEADER_FILES} )
	source_group( "Source Files\\MNS" FILES ${${PROJECT_NAME}_MNS_SOURCE_FILES} )

	add_executable( ${PROJECT_NAME} ${${PROJECT_NAME}_HEADER_FILES} ${${PROJECT_NAME}_SOURCE_FILES} ${${PROJECT_NAME}_MNS_HEADER_FILES} ${${PROJECT_NAME}_MNS_SOURCE_FILES} )

	target_link_libraries( ${PROJECT_NAME}
		${OPENGL_gl_LIBRARY}
		${OPENGL_glu_LIBRARY}
		${GLEW_LIBRARY}
		${GLFW_LIBRARY}
		${PNG_LIBRARIES}
	)
else()
	if ( NOT OPENGL_FOUND )
		message( SEND_ERROR "OpenGL library not found" )
	endif ()
	if ( NOT GLEW_FOUND )
		message( SEND_ERROR "GLEW library not found" )
	endif ()
	if ( NOT GLFW_FOUND )
		message( SEND_ERROR "GLW library not found" )
	endif ()
	if ( NOT GLM_FOUND )
		message( SEND_ERROR "GLM library not found" )
	endif ()
	if ( NOT PNG_FOUND )
		message( SEND_ERROR "PNG library not found" )
	endif ()
endif()
