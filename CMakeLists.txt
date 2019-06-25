################################################################################
cmake_minimum_required(VERSION 3.1)
project(ArbitraryPrecision)
################################################################################

# cmake_policy(SET CMP0063 NEW)
# set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Detects whether this is a top-level project
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
	set(ARBITRARY_PRECISION_TOPLEVEL_PROJECT ON)
else()
	set(ARBITRARY_PRECISION_TOPLEVEL_PROJECT OFF)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Color output
include(UseColors)

# Prepend function
include(PrependCurrentPath)

# ArbitraryPrecision utils
include(ArbitraryPrecisionUtils)

# Extra warnings
include(Warnings)

# Use C++11/14
include(CXXFeatures)

# Sort projects inside the solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Generate position independent code by default
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

################################################################################

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	foreach(config ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${config} config)
		string(REPLACE /MD /MT CMAKE_C_FLAGS_${config} "${CMAKE_C_FLAGS_${config}}")
		string(REPLACE /MD /MT CMAKE_CXX_FLAGS_${config} "${CMAKE_CXX_FLAGS_${config}}")
	endforeach()
endif()

################################################################################


################################################################################
# ArbitraryPrecision library
################################################################################

# add_library() can only be called without any source since CMake 3.11 ...
add_library(${PROJECT_NAME} src/precisioncore.cpp)

# Public include directory for ArbitraryPrecision
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}/include)

# Extra warnings
target_link_libraries(${PROJECT_NAME} PRIVATE warnings::all)

# Use C++14
target_compile_features(${PROJECT_NAME} PUBLIC ${CXX14_FEATURES})

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	# If _INT_PRECESION_FAST_DIV_REM is defined it will use a magnitude faster div and rem integer operation.
	target_compile_definitions(${PROJECT_NAME} PUBLIC "-D_INT_PRECISSION_FAST_DIV_REM")
endif()


# Other sources
add_subdirectory(src)

# Compile extras only if this is a top-level project
if(ARBITRARY_PRECISION_TOPLEVEL_PROJECT)
	# Unit tests
	add_subdirectory(tests)
endif()
