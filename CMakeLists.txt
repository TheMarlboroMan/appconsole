cmake_minimum_required(VERSION 3.5.1)
project(appconsole)

option(BUILD_DEBUG "Build a debug release" ON)
option(BUILD_SHARED "Build a shared library" ON)
option(BUILD_STATIC "Build a static library" OFF)

#library version
set(MAJOR_VERSION 0)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)

if(${BUILD_DEBUG})

	set(CMAKE_BUILD_TYPE Debug)
else()

	set(CMAKE_BUILD_TYPE Release)
endif()

if(${CMAKE_VERSION} VERSION_LESS "3.22.0")

	add_definitions(-DMAJOR_VERSION=${MAJOR_VERSION})
	add_definitions(-DMINOR_VERSION=${MINOR_VERSION})
	add_definitions(-DPATCH_VERSION=${PATCH_VERSION})
	add_definitions(-DRELEASE_VERSION=\"${RELEASE_VERSION}\")
else()

	add_compile_definitions(MAJOR_VERSION=${MAJOR_VERSION})
	add_compile_definitions(MINOR_VERSION=${MINOR_VERSION})
	add_compile_definitions(PATCH_VERSION=${PATCH_VERSION})
	add_compile_definitions(RELEASE_VERSION=\"${RELEASE_VERSION}\")
endif()


#-Werror
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options( -Wall -Wextra -Wundef -Wcast-align -Wwrite-strings -Wlogical-op -Wmissing-declarations -Wredundant-decls -Wshadow -Woverloaded-virtual -Wno-deprecated -ansi -pedantic -fno-rtti)

include_directories("${CMAKE_CURRENT_LIST_DIR}/include")

#Define the library itself.
set(SOURCE "")
add_subdirectory("${PROJECT_SOURCE_DIR}/lib")

#library type and filenames.
if(${BUILD_DEBUG})

	set(CMAKE_BUILD_TYPE DEBUG)
	set(LIB_FILENAME "appconsole_debug")
else()

	set(CMAKE_BUILD_TYPE RELEASE)
	set(LIB_FILENAME "appconsole")
endif()

if(${BUILD_STATIC}) 

	add_library(appconsole_static STATIC ${SOURCE})
	set_target_properties(appconsole_static PROPERTIES OUTPUT_NAME ${LIB_FILENAME})
	target_compile_definitions(appconsole_static PUBLIC "-DLIB_VERSION=\"static\"")
	install(TARGETS appconsole_static DESTINATION lib)

	if(${BUILD_DEBUG})

		target_compile_definitions(appconsole_static PUBLIC "-DLIBDANSDL2_DEBUG")
	endif()

	message("will build ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}-${RELEASE_VERSION}-static")
endif()

if(${BUILD_SHARED})

	add_library(appconsole_shared SHARED ${SOURCE})
	set_target_properties(appconsole_shared PROPERTIES OUTPUT_NAME ${LIB_FILENAME})
	target_compile_definitions(appconsole_shared PUBLIC "-DLIB_VERSION=\"shared\"")
	install(TARGETS appconsole_shared DESTINATION lib)

	if(${BUILD_DEBUG})

		target_compile_definitions(appconsole_shared PUBLIC "-DLIBDANSDL2_DEBUG")
	endif()

	message("will build ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}-${RELEASE_VERSION}-shared")
endif()
