# See original header on https://github.com/Saalvage/doctest/blob/dev/doctest/extensions/stl_stringifier.h

add_library(doctest_stl_stringifier INTERFACE)

add_library(doctest::stl_stringifier ALIAS doctest_stl_stringifier)

target_include_directories(doctest_stl_stringifier INTERFACE include)
