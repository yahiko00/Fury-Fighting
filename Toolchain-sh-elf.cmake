set( CMAKE_SYSTEM_NAME "Generic" )
set( CMAKE_SYSTEM_PROCESSOR "sh" )

set( KOS_ARCH "dreamcast" )
set( KOS_SUBARCH "pristine" )

set_property( DIRECTORY PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE )

set( TOOLCHAIN_PATH /opt/toolchains/dc/sh-elf )

SET( CMAKE_FIND_ROOT_PATH
	${TOOLCHAIN_PATH}
	$ENV{KOS_BASE}/
	$ENV{KOS_BASE}/addons
	$ENV{KOS_BASE}/../kos-ports
)

set( CMAKE_C_FLAGS "-O2 -fomit-frame-pointer -D_arch_$ENV{KOS_ARCH} -D_arch_sub_$ENV{KOS_SUBARCH} -Wall -g -fno-builtin -fno-strict-aliasing" )
set( CMAKE_CXX_FLAGS "-O2 -fomit-frame-pointer -fno-operator-names -fno-rtti -fno-exceptions" )
set( CMAKE_C_LINK_FLAGS "-nodefaultlibs" )
set( CMAKE_CXX_LINK_FLAGS "-nodefaultlibs" )

set( OBJCOPY ${TOOLCHAIN_PATH}/bin/sh-elf-objcopy )
set( CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/bin/sh-elf-gcc )
SET( CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/bin/sh-elf-g++ )
set( CMAKE_AR ${TOOLCHAIN_PATH}/bin/sh-elf-ar )
set( CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/bin/sh-elf-as )
set( CMAKE_ASM-ATT_COMPILER ${TOOLCHAIN_PATH}/bin/sh-elf-as )
set( CMAKE_LINKER ${TOOLCHAIN_PATH}/bin/sh-elf-ld )
set( CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_COMPILER} <OBJECTS> ${CMAKE_C_FLAGS} <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> -o <TARGET>" )
set( CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_COMPILER} <OBJECTS> ${CMAKE_CXX_FLAGS} <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> -o <TARGET>" )

set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

