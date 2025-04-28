# Install script for directory: C:/Users/artal/Documents/Visual Studio 2022/RumbleGame/CardRumble/vcpkg_installed/vcpkg/blds/matplotplusplus/src/v1.2.1-c779e4a369.clean/source/matplot

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/artal/Documents/Visual Studio 2022/RumbleGame/CardRumble/vcpkg_installed/vcpkg/pkgs/matplotplusplus_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/matplot/detail" TYPE FILE FILES "C:/Users/artal/Documents/Visual Studio 2022/RumbleGame/CardRumble/vcpkg_installed/vcpkg/blds/matplotplusplus/x64-windows-dbg/source/matplot/matplot/detail/exports.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/artal/Documents/Visual Studio 2022/RumbleGame/CardRumble/vcpkg_installed/vcpkg/blds/matplotplusplus/x64-windows-dbg/source/matplot/matplot.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "C:/Users/artal/Documents/Visual Studio 2022/RumbleGame/CardRumble/vcpkg_installed/vcpkg/blds/matplotplusplus/src/v1.2.1-c779e4a369.clean/source/matplot" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Matplot++/Matplot++Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Matplot++/Matplot++Targets.cmake"
         "C:/Users/artal/Documents/Visual Studio 2022/RumbleGame/CardRumble/vcpkg_installed/vcpkg/blds/matplotplusplus/x64-windows-dbg/source/matplot/CMakeFiles/Export/ed363c85be7c9e3f8311e936e354154f/Matplot++Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Matplot++/Matplot++Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Matplot++/Matplot++Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Matplot++" TYPE FILE FILES "C:/Users/artal/Documents/Visual Studio 2022/RumbleGame/CardRumble/vcpkg_installed/vcpkg/blds/matplotplusplus/x64-windows-dbg/source/matplot/CMakeFiles/Export/ed363c85be7c9e3f8311e936e354154f/Matplot++Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Matplot++" TYPE FILE FILES "C:/Users/artal/Documents/Visual Studio 2022/RumbleGame/CardRumble/vcpkg_installed/vcpkg/blds/matplotplusplus/x64-windows-dbg/source/matplot/CMakeFiles/Export/ed363c85be7c9e3f8311e936e354154f/Matplot++Targets-debug.cmake")
  endif()
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/artal/Documents/Visual Studio 2022/RumbleGame/CardRumble/vcpkg_installed/vcpkg/blds/matplotplusplus/x64-windows-dbg/source/matplot/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
