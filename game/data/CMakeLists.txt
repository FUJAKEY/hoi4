file(GLOB DATA_FILES *.json)
add_custom_target(game_data SOURCES ${DATA_FILES})
