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

if(INPUT_THIRD_PARTY_DIR)
	set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${INPUT_THIRD_PARTY_DIR}/)
else()
	set(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${THIRD_PARTY_DIR}/Catch2/contrib)

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


# Sanitizer options
option(ARBITRARY_PRECISION_WITH_SANITIZERS "Enable sanitizers in compilation targets"   OFF)
option(SANITIZE_ADDRESS                    "Sanitize Address"                           OFF)
option(SANITIZE_MEMORY                     "Sanitize Memory"                            OFF)
option(SANITIZE_THREAD                     "Sanitize Thread"                            OFF)
option(SANITIZE_UNDEFINED                  "Sanitize Undefined"                         OFF)

# Sanitizers
if(ARBITRARY_PRECISION_WITH_SANITIZERS)
	list(APPEND CMAKE_MODULE_PATH ${THIRD_PARTY_DIR}/sanitizers-cmake/cmake)
endif()

# Setup dependencies
include(ArbitraryPrecisionDependencies)

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

# If _INT_PRECESION_FAST_DIV_REM is defined it will use a magnitude faster div and rem integer operation.
target_compile_definitions(${PROJECT_NAME} PUBLIC "-D_INT_PRECISSION_FAST_DIV_REM")


if(ARBITRARY_PRECISION_WITH_SANITIZERS)
	add_sanitizers(${PROJECT_NAME})
endif()



# Catch2
arbitrary_precision_download_catch2()
add_library(catch INTERFACE)
target_include_directories(catch SYSTEM INTERFACE ${THIRD_PARTY_DIR}/Catch2/single_include/catch2)


# Other sources
add_subdirectory(src)

# Compile extras only if this is a top-level project
if(ARBITRARY_PRECISION_TOPLEVEL_PROJECT)
	# Unit tests
	include(CTest)
	enable_testing()
	add_subdirectory(tests)
endif()
