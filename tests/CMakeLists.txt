cmake_minimum_required(VERSION 3.1)
################################################################################

set(test_sources
	test.cpp
)

add_executable(unit_tests ${test_sources})
arbitrary_precision_set_source_group(${test_sources})

target_link_libraries(unit_tests PUBLIC ArbitraryPrecision warnings::all)
