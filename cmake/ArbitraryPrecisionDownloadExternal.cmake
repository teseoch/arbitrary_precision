################################################################################
include(DownloadProject)

# With CMake 3.8 and above, we can hide warnings about git being in a
# detached head by passing an extra GIT_CONFIG option
if(NOT (${CMAKE_VERSION} VERSION_LESS "3.8.0"))
    set(ARBITRARY_PRECISION_EXTRA_OPTIONS "GIT_CONFIG advice.detachedHead=false")
else()
    set(ARBITRARY_PRECISION_EXTRA_OPTIONS "")
endif()

# Shortcut function
function(arbitrary_precision_download_project name)
    download_project(
        PROJ         ${name}
        SOURCE_DIR   ${ARBITRARY_PRECISION_EXTERNAL}/${name}
        DOWNLOAD_DIR ${ARBITRARY_PRECISION_EXTERNAL}/.cache/${name}
        QUIET
        ${ARBITRARY_PRECISION_EXTRA_OPTIONS}
        ${ARGN}
    )
endfunction()

################################################################################


## Catch2
function(arbitrary_precision_download_catch2)
    arbitrary_precision_download_project(Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.4.2
    )
endfunction()


## Sanitizers
function(arbitrary_precision_download_sanitizers)
    arbitrary_precision_download_project(sanitizers-cmake
        GIT_REPOSITORY https://github.com/arsenm/sanitizers-cmake.git
        GIT_TAG        6947cff3a9c9305eb9c16135dd81da3feb4bf87f
    )
endfunction()
