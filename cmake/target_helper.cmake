function(add_target)
    set(options)
    set(oneValueArgs NAME LANGUAGE DESCRIPTION DIRECTORY)
    set(multiValueArgs FILES LIBS)

    cmake_parse_arguments(TARGET "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    string(TOUPPER ${TARGET_LANGUAGE} TARGET_LANGUAGE)

    # Unless explicitly specify LANGUAGE, otherwise assume that .c is compiling
    if(${TARGET_LANGUAGE} STREQUAL "CXX")
        set(SRC_SUFFIX "cpp")
    else()
        set(SRC_SUFFIX "c")
    endif()

    if(NOT "${TARGET_DESCRIPTION}" STREQUAL "")
        message(STATUS "${TARGET_NAME} - \"${TARGET_DESCRIPTION}\" - Build")
    endif()

    if(NOT "${TARGET_DIRECTORY}" STREQUAL "")
        add_subdirectory(${TARGET_DIRECTORY})
        return()
    endif()

    if(NOT "${TARGET_FILES}" STREQUAL "")
        set(SRC_FILES ${TARGET_FILES}) 
    else()
        set(SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}.${SRC_SUFFIX})
    endif()

    add_executable(${TARGET_NAME} ${SRC_FILES})
    
    if(NOT "${TARGET_LIBS}" STREQUAL "")
        target_link_libraries(${TARGET_NAME} ${TARGET_LIBS})
    endif()
endfunction()

macro(add_target_c name)
    add_target(
        NAME ${name}
        LANGUAGE C
        DESCRIPTION ""
        DIRECTORY ""
        FILES ""
    )
endmacro()

macro(add_target_cxx name)
    add_target(
        NAME ${name}
        LANGUAGE CXX
        DESCRIPTION ""
        DIRECTORY ""
        FILES ""
    )
endmacro()

