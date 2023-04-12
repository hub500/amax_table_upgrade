project(amax_table_upgrade)

set(AMAX_WASM_OLD_BEHAVIOR "Off")
find_package(amax.cdt)

add_contract( amax_table_upgrade amax_table_upgrade amax_table_upgrade.cpp )
target_include_directories( amax_table_upgrade PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( amax_table_upgrade ${CMAKE_SOURCE_DIR}/../ricardian )