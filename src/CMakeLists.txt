set(SOURCES
    complexprecision.h
    fprecision.h
    intervalprecision.h
    iprecision.h
    precisioncore.cpp
)

prepend_current_path(SOURCES)
arbitrary_precision_copy_headers(${SOURCES})
arbitrary_precision_set_source_group(${SOURCES})
target_sources(ArbitraryPrecision PRIVATE ${SOURCES})
