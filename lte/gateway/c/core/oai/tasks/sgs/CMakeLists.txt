find_package(Protobuf REQUIRED)

add_library(TASK_SGS
    sgs_task.cpp
    sgs_service_handler.cpp
    )

target_link_libraries(TASK_SGS
    COMMON
    LIB_BSTR LIB_HASHTABLE LIB_SGS_CLIENT
    ${PROTOBUF_LIBRARIES}
    )
target_include_directories(TASK_SGS PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
