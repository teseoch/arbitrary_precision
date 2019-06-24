cmake_minimum_required(VERSION 3.1)
################################################################################

set(test_sources
	main.cpp
	test.cpp
)

add_executable(unit_tests ${test_sources})
arbitrary_precision_set_source_group(${test_sources})

target_link_libraries(unit_tests PUBLIC ArbitraryPrecision catch warnings::all)



if(ARBITRARY_PRECISION_WITH_SANITIZERS)
	add_sanitizers(unit_tests)
endif()

# Register tests
set(PARSE_CATCH_TESTS_ADD_TO_CONFIGURE_DEPENDS ON)
include(Catch)
catch_discover_tests(unit_tests)
