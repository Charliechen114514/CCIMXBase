include("/home/charliechen/imx6ull/qt683_project/led_controller/build/ARMQt_6-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/led_controller-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/charliechen/imx6ull/qt683_project/led_controller/build/ARMQt_6-Debug/led_controller
    GENERATE_QT_CONF
)
