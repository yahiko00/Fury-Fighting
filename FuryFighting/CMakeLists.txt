project( FuryFighting )

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
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Bin/Data ${ROMDISK_DATA}
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
	get_filename_component( SDL_IMAGE_PATH ${SDL_IMAGE_LIBRARY} PATH )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/libjpeg-8.dll Debug )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/libjpeg-8.dll Release )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/libpng15-15.dll Debug )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/libpng15-15.dll Release )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/libtiff-5.dll Debug )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/libtiff-5.dll Release )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/libwebp-2.dll Debug )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/libwebp-2.dll Release )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/zlib1.dll Debug )
	copy_dll( ${PROJECT_NAME} ${SDL_IMAGE_PATH}/zlib1.dll Release )
endif ()
