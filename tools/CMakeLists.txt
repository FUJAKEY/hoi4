add_executable(map-compiler map-compiler/main.cpp)
target_link_libraries(map-compiler PRIVATE external::json)

add_executable(save-converter save-converter/main.cpp)
target_link_libraries(save-converter PRIVATE external::json)
