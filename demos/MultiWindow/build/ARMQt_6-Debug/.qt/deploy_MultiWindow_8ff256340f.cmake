include("/home/charliechen/imx6ull/qt683_project/MultiWindow/build/ARMQt_6-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MultiWindow-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/charliechen/imx6ull/qt683_project/MultiWindow/build/ARMQt_6-Debug/MultiWindow
    GENERATE_QT_CONF
)
