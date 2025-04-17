include("/home/charliechen/imx6ull/qt683_project/showImage/build/Desktop_Qt_6_8_3-Debug/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/showImage-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/charliechen/imx6ull/qt683_project/showImage/build/Desktop_Qt_6_8_3-Debug/showImage
    GENERATE_QT_CONF
)
