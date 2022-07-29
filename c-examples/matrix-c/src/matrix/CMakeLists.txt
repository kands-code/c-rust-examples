add_library(matrix STATIC
    "matrix.c"
    "matrix-ext.c"
)

target_include_directories(matrix PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")