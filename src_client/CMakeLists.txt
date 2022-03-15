cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME msgr_client VERSION 1.0.0 LANGUAGES CXX)
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

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(HEADERS
    main_window/MainWindow.h
    main_window/RegistrationWidget.h
    main_window/AuthorizationWidget.h
    main_window/ChatWidget.h
    main_window/MainWidgets.h
    client/Client.h
    client/ClientThread.h
    message_processor/IMsgProcessor.h
    message_processor/MsgProcessor.h
)

set(SOURCES
    main.cpp
    main_window/MainWindow.cpp
    main_window/RegistrationWidget.cpp
    main_window/AuthorizationWidget.cpp
    main_window/ChatWidget.cpp
    client/Client.cpp
    client/ClientThread.cpp
    message_processor/MsgProcessor.cpp
)

add_executable(msgr_client
    ${SOURCES}
    ${HEADERS}
)

set_target_properties(msgr_client PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(msgr_client
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    ${Boost_LIBRARIES}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(msgr_client)
endif()

if (MSVC)
    target_compile_options(msgr_client PRIVATE
        /W4
    )
else ()
    target_compile_options(msgr_client PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()


install(TARGETS msgr_client RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

include(CPack)

#enable_testing()
