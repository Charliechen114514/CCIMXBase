cmake_minimum_required(VERSION 3.19)
project(CCIMX_Desktop LANGUAGES CXX)
set(CMAKE_AUTORCC ON)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets Network)

qt_standard_project_setup()

get_filename_component(COMPILER_NAME ${CMAKE_CXX_COMPILER} NAME)

# This part aims to find the Cross compile
# If you only get the arm mupdf compiles, do notice to select the
# correct kits with correct arch and compilers
if(COMPILER_NAME MATCHES "arm.*-g\\+\\+")
    add_compile_definitions(ARM_BUILD)
endif()


include_directories(
    .
    ./ui
    ./builtin/ui
)

set(DesktopMain
    ui/desktopmainwindow.cpp
    ui/desktopmainwindow.h
    ui/desktopmainwindow.ui)

set(AppWrapper
    app_wrapper/applicationwrapper.h
    app_wrapper/applicationwrapper.cpp
    app_wrapper/pagesetuper.h app_wrapper/pagesetuper.cpp)

set(UiSubs
    ui/appwidget.h ui/appwidget.cpp ui/appwidget.ui
    ui/stackpage_switcher_animation.h
    ui/stackpage_switcher_animation.cpp
    ui/downdockwidget.h ui/downdockwidget.cpp
    ui/downdockwidget.ui
    ui/desktoptoast.h ui/desktoptoast.cpp
    ui/wallpaperanimationhandler.h ui/wallpaperanimationhandler.cpp)

set(CoreSubs
    core/coretools.h core/coretools.cpp)

set(BuiltInPackage
    builtin/page/homepage.h builtin/page/homepage.cpp builtin/page/homepage.ui
    builtin/ui/pagefactory.h builtin/ui/pagefactory.cpp
    builtin/ui/clockwidget.h builtin/ui/clockwidget.cpp builtin/ui/clockwidget.ui
    builtin/ui/digitaltimewidget.h builtin/ui/digitaltimewidget.cpp)

qt_add_executable(CCIMX_Desktop
    WIN32 MACOSX_BUNDLE
    main.cpp
    ${DesktopMain}
    ${AppWrapper}
    ${UiSubs}
    ${CoreSubs}
    ${BuiltInPackage}
    icons.qrc
)

target_link_libraries(CCIMX_Desktop
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Network
)

include(GNUInstallDirs)

install(TARGETS CCIMX_Desktop
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET CCIMX_Desktop
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
