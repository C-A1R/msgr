cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
set(PROJECT_NAME msgr_client VERSION ${PROJECT_VESRION} LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

project(${PROJECT_NAME})

# find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(../src_shared)


#LIB

set(SOURCES_LIB
    client_lib/client/Client.cpp
    client_lib/client/ClientThread.cpp
    client_lib/client_processor/ClientProcessor.cpp
    ../src_shared/Notification.cpp
)
set(HEADERS_LIB
    client_lib/client/Client.h
    client_lib/client/ClientThread.h
    client_lib/client_processor/IClientProcessor.h
    client_lib/client_processor/ClientProcessor.h
    ../src_shared/UserInfo.h
    ../src_shared/MessageInfo.h
    ../src_shared/Notification.h
)

add_library(${PROJECT_NAME}_lib SHARED
    ${HEADERS_LIB}
    ${SOURCES_LIB}
)
target_include_directories(${PROJECT_NAME}_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME}_lib
    PRIVATE
        Qt5::Widgets
        ${Boost_LIBRARIES}
)
set_target_properties(${PROJECT_NAME}_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


#BIN

set(HEADERS
    main_window/MainWindow.h
    main_window/RegistrationWidget.h
    main_window/AuthorizationWidget.h
    main_window/messenger_widget/MessengerWidget.h
    main_window/messenger_widget/ChatWidget.h
    main_window/messenger_widget/StackedChatWidget.h
    main_window/MainWidgets.h
)
set(SOURCES
    main.cpp
    main_window/MainWindow.cpp
    main_window/RegistrationWidget.cpp
    main_window/AuthorizationWidget.cpp
    main_window/messenger_widget/MessengerWidget.cpp
    main_window/messenger_widget/ChatWidget.cpp
    main_window/messenger_widget/StackedChatWidget.cpp
)

add_executable(msgr_client
    ${HEADERS}
    ${SOURCES}
)
set_target_properties(msgr_client PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    WIN32_EXECUTABLE TRUE
)
target_link_libraries(msgr_client
    PRIVATE
        Qt5::Widgets
        ${Boost_LIBRARIES}
        ${PROJECT_NAME}_lib
)

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

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

#enable_testing()
