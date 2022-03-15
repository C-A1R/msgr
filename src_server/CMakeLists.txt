cmake_minimum_required(VERSION 3.2)

set(PROJECT_NAME msgr_server VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(${PROJECT_NAME})

# find_package(Boost COMPONENTS unit_test_framework REQUIRED)

# find_package(Doxygen)
# if (DOXYGEN_FOUND)
#     # set input and output files
#     set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
#     set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#     # request to configure the file
#     configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#     message("Doxygen build started")

#     # note the option ALL which allows to build the docs together with the application
#     add_custom_target(doc_doxygen ALL
#         COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#         COMMENT "Generating API documentation with Doxygen"
#         VERBATIM )
# else (DOXYGEN_FOUND)
#   message("Doxygen need to be installed to generate the doxygen documentation")
# endif (DOXYGEN_FOUND)

set(SOURCE_FILES
    main.cpp
    server.cpp
    session.cpp
)

add_executable(msgr_server ${SOURCE_FILES})

# add_executable(test_ICommand 
#     src/_tests/test_ICommand.cpp 
#     src/command/Cmd.cpp 
#     src/command/MacroCmd.cpp
# )
# add_executable(test_ICommandQueue
#     src/_tests/test_ICommandQueue.cpp 
#     src/command_queue/CmdQueue.cpp 
#     src/command/Cmd.cpp 
#     src/command/MacroCmd.cpp
# )

set_target_properties(msgr_server 
    # test_ICommand 
    # test_ICommandQueue
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(msgr_server
    ${Boost_LIBRARIES}
)
# target_link_libraries(test_ICommand
#     ${Boost_LIBRARIES}
# )
# target_link_libraries(test_ICommandQueue
#     ${Boost_LIBRARIES}
# )

if (MSVC)
    target_compile_options(msgr_server PRIVATE
        /W4
    )
    # target_compile_options(test_ICommand PRIVATE
    #     /W4
    # )
    # target_compile_options(test_ICommandQueue PRIVATE
    #     /W4
    # )
else ()
    target_compile_options(msgr_server PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    # target_compile_options(test_ICommand PRIVATE
    #     -Wall -Wextra -pedantic -Werror
    # )
    # target_compile_options(test_ICommandQueue PRIVATE
    #     -Wall -Wextra -pedantic -Werror
    # )
endif()


install(TARGETS msgr_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)

enable_testing()

# add_test(test_Version test_Version)
# add_test(test_ICommand test_ICommand)
# add_test(test_ICommandQueue test_ICommandQueue)
