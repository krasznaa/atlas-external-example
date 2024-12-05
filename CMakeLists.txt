# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration

# Set up the project.
cmake_minimum_required(VERSION 3.25)
project(AtlasExternalExample VERSION 1.0.0 LANGUAGES CXX)

# CMake include(s).
include(CMakePackageConfigHelpers)
include(CPack)
include(GNUInstallDirs)

# Set the default library type to build.
option(BUILD_SHARED_LIBS
   "Flag for building shared/static libraries" TRUE)

# Collect the header and source file(s).
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*/*.h")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx")

# Build a shared library with them.
add_library(atlas_library ${HEADERS} ${SOURCES})
target_include_directories(atlas_library PUBLIC
   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

# Make it visible as atlas::library both during the build, and when importing
# the installed target.
add_library(atlas::library ALIAS atlas_library)
set_target_properties(atlas_library PROPERTIES
   EXPORT_NAME "library")

# Specify the (SO)VERSION of the library.
set_target_properties(atlas_library PROPERTIES
   VERSION "${PROJECT_VERSION}"
   SOVERSION "${PROJECT_VERSION_MAJOR}" )

# Install the library.
install(TARGETS atlas_library
   EXPORT AtlasExternalExampleExports
   LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
   ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
   RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

# Install the header(s).
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
   DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

# Export the target(s).
set(CMAKE_INSTALL_CMAKEDIR
   "${CMAKE_INSTALL_LIBDIR}/cmake/atlas-external-example-${PROJECT_VERSION}")
install(EXPORT AtlasExternalExampleExports
   NAMESPACE "atlas::"
   FILE "atlas-external-example-targets.cmake"
   DESTINATION "${CMAKE_INSTALL_CMAKEDIR}" )
configure_package_config_file(
   "${CMAKE_CURRENT_SOURCE_DIR}/cmake/atlas-external-example-config.cmake.in"
   "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/atlas-external-example-config.cmake"
   INSTALL_DESTINATION "${CMAKE_INSTALL_CMAKEDIR}"
   PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR
             CMAKE_INSTALL_CMAKEDIR
   NO_CHECK_REQUIRED_COMPONENTS_MACRO )
write_basic_package_version_file(
   "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/atlas-external-example-config-version.cmake"
   COMPATIBILITY "AnyNewerVersion" )
install( FILES
   "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/atlas-external-example-config.cmake"
   "${CMAKE_CURRENT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/atlas-external-example-config-version.cmake"
   DESTINATION "${CMAKE_INSTALL_CMAKEDIR}" )
