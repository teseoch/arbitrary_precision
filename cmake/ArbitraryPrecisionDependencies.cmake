# Prepare dependencies
#
# For each third-party library, if the appropriate target doesn't exist yet,
# download it via external project, and add_subdirectory to build it alongside
# this project.

### Configuration
set(ARBITRARY_PRECISION_ROOT     "${CMAKE_CURRENT_LIST_DIR}/..")
set(ARBITRARY_PRECISION_EXTERNAL ${THIRD_PARTY_DIR})

# Download and update 3rdparty libraries
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
list(REMOVE_DUPLICATES CMAKE_MODULE_PATH)
include(ArbitraryPrecisionDownloadExternal)

################################################################################
# Required libraries
################################################################################

# Sanitizers
if(ARBITRARY_PRECISION_WITH_SANITIZERS)
    arbitrary_precision_download_sanitizers()
    find_package(Sanitizers)
endif()
