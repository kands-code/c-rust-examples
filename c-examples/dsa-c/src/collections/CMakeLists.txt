add_library(collections STATIC
    ArrayList.c
    LinkedList.c
)

target_include_directories(collections PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
