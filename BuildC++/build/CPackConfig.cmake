# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_7Z "OFF")
set(CPACK_BINARY_BUNDLE "")
set(CPACK_BINARY_CYGWIN "")
set(CPACK_BINARY_DEB "")
set(CPACK_BINARY_DRAGNDROP "")
set(CPACK_BINARY_FREEBSD "")
set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_NSIS "ON")
set(CPACK_BINARY_OSXX11 "")
set(CPACK_BINARY_PACKAGEMAKER "")
set(CPACK_BINARY_PRODUCTBUILD "")
set(CPACK_BINARY_RPM "")
set(CPACK_BINARY_STGZ "")
set(CPACK_BINARY_TBZ2 "")
set(CPACK_BINARY_TGZ "")
set(CPACK_BINARY_TXZ "")
set(CPACK_BINARY_TZ "")
set(CPACK_BINARY_WIX "OFF")
set(CPACK_BINARY_ZIP "OFF")
set(CPACK_BUILD_SOURCE_DIRS "D:/Env/GitHubDesktopPortable-master/Repos/Projet_Reseau_RAT/RAT;D:/Env/GitHubDesktopPortable-master/Repos/Projet_Reseau_RAT/BuildC++/build")
set(CPACK_CMAKE_GENERATOR "Visual Studio 14 2015")
set(CPACK_COMPONENTS_ALL "")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_GENERATOR "NSIS")
set(CPACK_INSTALL_CMAKE_PROJECTS "D:/Env/GitHubDesktopPortable-master/Repos/Projet_Reseau_RAT/BuildC++/build;Project_RAT;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/Project_RAT")
set(CPACK_MODULE_PATH "D:/Env/GitHubDesktopPortable-master/Repos/Projet_Reseau_RAT/BuildC++/build/CMakeTools")
set(CPACK_NSIS_DISPLAY_NAME "Project_RAT 0.1.1")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "Project_RAT 0.1.1")
set(CPACK_OUTPUT_CONFIG_FILE "D:/Env/GitHubDesktopPortable-master/Repos/Projet_Reseau_RAT/BuildC++/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "D:/Env/VSCode-win32-x64-1.21.1/C++Utilities/cmake/share/cmake-3.11/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Project_RAT built using CMake")
set(CPACK_PACKAGE_FILE_NAME "Project_RAT-0.1.1-win32")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Project_RAT 0.1.1")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Project_RAT 0.1.1")
set(CPACK_PACKAGE_NAME "Project_RAT")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "0.1.1")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PROJECT_NAME "Project_RAT")
set(CPACK_PROJECT_VERSION "0.0.0")
set(CPACK_RESOURCE_FILE_LICENSE "D:/Env/VSCode-win32-x64-1.21.1/C++Utilities/cmake/share/cmake-3.11/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "D:/Env/VSCode-win32-x64-1.21.1/C++Utilities/cmake/share/cmake-3.11/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "D:/Env/VSCode-win32-x64-1.21.1/C++Utilities/cmake/share/cmake-3.11/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_7Z "ON")
set(CPACK_SOURCE_CYGWIN "")
set(CPACK_SOURCE_GENERATOR "7Z;ZIP")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "D:/Env/GitHubDesktopPortable-master/Repos/Projet_Reseau_RAT/BuildC++/build/CPackSourceConfig.cmake")
set(CPACK_SOURCE_RPM "")
set(CPACK_SOURCE_TBZ2 "")
set(CPACK_SOURCE_TGZ "")
set(CPACK_SOURCE_TXZ "")
set(CPACK_SOURCE_TZ "")
set(CPACK_SOURCE_ZIP "ON")
set(CPACK_SYSTEM_NAME "win32")
set(CPACK_TOPLEVEL_TAG "win32")
set(CPACK_WIX_SIZEOF_VOID_P "4")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "D:/Env/GitHubDesktopPortable-master/Repos/Projet_Reseau_RAT/BuildC++/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
