add_library(wasmvm_core
    core/Store.c
    core/Stack.c
    instance/ExportInst.c
    instance/FuncInst.c
    instance/GlobalInst.c
    instance/MemInst.c
    instance/ModuleInst.c
    instance/TableInst.c
    dataTypes/stack.c
    dataTypes/Value.c
    dataTypes/vector.c
    dataTypes/FuncType.c
)

add_subdirectory(core/runtime)
target_link_libraries(wasmvm_core
    wasmvm_runtime
)

install(TARGETS wasmvm_core
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)