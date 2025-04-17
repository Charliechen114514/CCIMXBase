include("/home/charliechen/imx6ull/qt683_project/demo_combo_box/build/ARMQt_6-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/demo_combo_box-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/charliechen/imx6ull/qt683_project/demo_combo_box/build/ARMQt_6-Debug/demo_combo_box
    GENERATE_QT_CONF
)
