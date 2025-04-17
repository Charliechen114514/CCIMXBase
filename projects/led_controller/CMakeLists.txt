cmake_minimum_required(VERSION 3.19)
project(led_controller LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(led_controller
    WIN32 MACOSX_BUNDLE
    main.cpp
    leddemowindow.cpp
    leddemowindow.h
    leddemowindow.ui
    led.h led_app_adapter.cpp led_app_adapter.h
    image.qrc
)

target_link_libraries(led_controller
    PRIVATE
        Qt::Core
        Qt::Widgets
)

include(GNUInstallDirs)

install(TARGETS led_controller
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET led_controller
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
