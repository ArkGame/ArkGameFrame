#Define server plugin building macro
function(BUILD_PLUGIN_MACRO project_name)
    aux_source_directory(. PLUGIN_SRC)

    if(UNIX AND (NOT APPLE))
        #Set rpath
        set(CMAKE_INSTALL_RPATH ".")
        set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    endif(UNIX AND (NOT APPLE))

    add_library(${project_name} SHARED ${PLUGIN_SRC})

    add_dependencies(${project_name} AFProto)

    if(WIN32)
        add_definitions(-D_USRDLL)

        target_link_libraries(${project_name} 
            debug AFProto_d.lib
            optimized AFProto.lib
            ${PROTOBUF_LIBRARIES})
    elseif(APPLE)
        target_link_libraries(${project_name} 
            debug ${BIN_OUTPUT_DIR}/AFProto_d.a
            optimized ${BIN_OUTPUT_DIR}/AFProto.a
            ${PROTOBUF_LIBRARIES})
    else(UNIX)
        target_link_libraries(${project_name} 
            debug :AFProto_d.a
            optimized :AFProto.a
            ${PROTOBUF_LIBRARIES}
            pthread
            dl)
    endif()

    set_target_properties(${project_name} PROPERTIES PREFIX "")
    set_target_properties(${project_name} PROPERTIES
        FOLDER "examples"
        ARCHIVE_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR}
        RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR}
        LIBRARY_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR})
endfunction(BUILD_PLUGIN_MACRO project_name)

###################################################################################################
add_subdirectory(sample1)
add_subdirectory(sample2)
add_subdirectory(sample3)
#add_subdirectory(sample4)
#add_subdirectory(sample5)
#add_subdirectory(redis_sample)

#add_subdirectory(http_client)
#add_subdirectory(kcptool)
#add_subdirectory(mysql_sample)
