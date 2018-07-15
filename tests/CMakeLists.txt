macro(_add_test name)
    add_executable(${name} ${name}.cpp)
    target_compile_options(${name} PRIVATE -Wall -Wextra -Wpointer-arith)
    target_link_libraries(${name} cst_unx)
    add_test(${name} ${name})
endmacro()

_add_test(file_test)
_add_test(file_descriptor_test)
