set( CMAKE_SYSTEM_NAME "Generic" )
set( CMAKE_SYSTEM_PROCESSOR "sh" )

set( DREAMCAST ON )
set( SH_ELF_PREFIX /opt/toolchains/dc/sh-elf )
set( KOS_ARCH "dreamcast" )
set( KOS_SUBARCH "pristine" )
set( KOS_LIB_PATHS "-L$ENV{KOS_BASE}/lib/${KOS_ARCH} -L$ENV{KOS_BASE}/addons/lib/${KOS_ARCH} -L$ENV{KOS_PORTS}/lib" )
set( KOS_LIBS "-Wl,--start-group -lkallisti -lc -lgcc -Wl,--end-group" )
set( KOS_LD_SCRIPT  )

set( KOS_INC_PATHS "-I$ENV{KOS_BASE}/kernel/arch/${KOS_ARCH}/include -I$ENV{KOS_BASE}/addons/include -I$ENV{KOS_PORTS}/include" )

set_property( DIRECTORY PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE )

SET( CMAKE_FIND_ROOT_PATH
	${SH_ELF_PREFIX}
	$ENV{KOS_BASE}/
	$ENV{KOS_BASE}/addons
	$ENV{KOS_PORTS}
)

set( CMAKE_C_FLAGS "-O2 -fomit-frame-pointer -ml -m4-single-only -ffunction-sections -fdata-sections ${KOS_INC_PATHS} -D_arch_${KOS_ARCH} -D_arch_sub_${KOS_SUBARCH} -Wall -g -fno-builtin -fno-strict-aliasing" CACHE STRING "" )
set( CMAKE_CXX_FLAGS "-O2 -fomit-frame-pointer -ml -m4-single-only -ffunction-sections -fdata-sections -fno-operator-names ${KOS_INC_PATHS_CPP} -D_arch_${KOS_ARCH} -D_arch_sub_${KOS_SUBARCH} -fno-rtti" CACHE STRING "" )
set( CMAKE_C_LINK_FLAGS "-nodefaultlibs ${KOS_LD_SCRIPT} ${KOS_LIB_PATHS} -ml -m4-single-only -Wl,-Ttext=0x8c010000 -Wl,--gc-sections ${KOS_LIBS}" CACHE STRING "" )
set( CMAKE_CXX_LINK_FLAGS "-nodefaultlibs ${KOS_LD_SCRIPT} ${KOS_LIB_PATHS} -ml -m4-single-only -Wl,-Ttext=0x8c010000 -Wl,--gc-sections ${KOS_LIBS} -lstdc++" CACHE STRING "" )

set( CMAKE_OBJCOPY ${SH_ELF_PREFIX}/bin/sh-elf-objcopy CACHE FILEPATH "" )
set( CMAKE_C_COMPILER ${SH_ELF_PREFIX}/bin/sh-elf-gcc CACHE FILEPATH "" )
set( CMAKE_CXX_COMPILER ${SH_ELF_PREFIX}/bin/sh-elf-g++ CACHE FILEPATH "" )
set( CMAKE_AR ${SH_ELF_PREFIX}/bin/sh-elf-ar CACHE FILEPATH "" )
set( CMAKE_ASM_COMPILER ${SH_ELF_PREFIX}/bin/sh-elf-as CACHE FILEPATH "" )
set( CMAKE_ASM-ATT_COMPILER ${SH_ELF_PREFIX}/bin/sh-elf-as CACHE FILEPATH "" )
set( CMAKE_LINKER ${SH_ELF_PREFIX}/bin/sh-elf-ld CACHE FILEPATH "" )
set( CMAKE_C_LINK_EXECUTABLE "${CMAKE_C_COMPILER} <OBJECTS> ${CMAKE_C_FLAGS} <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES> -o <TARGET>" )
set( CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_COMPILER} <OBJECTS> ${CMAKE_CXX_FLAGS} ${CMAKE_CXX_LINK_FLAGS} <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES> -o <TARGET>" )

set( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
set( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
set( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )

set( KOS_GENROMFS $ENV{KOS_GENROMFS} )
set( KOS_BIN2O $ENV{KOS_BASE}/utils/bin2o/bin2o )
