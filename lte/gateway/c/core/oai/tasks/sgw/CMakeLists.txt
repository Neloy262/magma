# compile required protos
set(SPGW_LTE_CPP_PROTOS spgw_state common_types std_3gpp_types)
list(APPEND PROTO_SRCS "")
list(APPEND PROTO_HDRS "")

set(STATE_OUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/lte/protos/oai")
generate_cpp_protos("${SPGW_LTE_CPP_PROTOS}" "${PROTO_SRCS}" "${PROTO_HDRS}"
    "${STATE_PROTO_DIR}" "${STATE_OUT_DIR}")

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${STATE_OUT_DIR})

add_library(TASK_SGW
    spgw_config.cpp
    pgw_config.cpp
    sgw_config.cpp
    s11_causes.cpp
    sgw_task.cpp
    sgw_handlers.cpp
    pgw_handlers.cpp
    sgw_context_manager.cpp
    pgw_pco.cpp
    mobilityd_ue_ip_address_alloc.cpp
    sgw_paging.cpp
    pgw_procedures.cpp
    spgw_state.cpp
    spgw_state_manager.cpp
    spgw_state_converter.cpp
    ${PROTO_SRCS}
    ${PROTO_HDRS}
    )
target_compile_definitions(TASK_SGW PRIVATE
    PACKAGE_NAME=\"S/P-GW\"
    PACKAGE_VERSION=\"0.1\"
    PACKAGE_BUGREPORT=\"TBD\"
    )
target_link_libraries(TASK_SGW
    COMMON
    ${GTPNL_LIBRARIES}
    LIB_BSTR LIB_MOBILITY_CLIENT LIB_PCEF
    TASK_GTPV1U
    cpp_redis tacopie protobuf
    )
target_include_directories(TASK_SGW PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${S1AP_C_DIR}
    )
