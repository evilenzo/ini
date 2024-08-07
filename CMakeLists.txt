cmake_minimum_required(VERSION 3.12)

###
### PROJECT
### name and version
###
project(Interest VERSION 1.0 LANGUAGES CXX)

###
### CHECK IF MAIN PROJECT
### determine if build as a subproject (using add_subdirectory) or if it is the main project
###
set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(MAIN_PROJECT ON)
endif()

###
### OPTIONS
###
option(BUILD_TESTS        "Build unit tests"          ${MAIN_PROJECT})
option(BUILD_SHARED_LIBS  "Build as shared library."  OFF)

###
### CONFIGURATION
###
include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD                 20)
set(CMAKE_CXX_STANDARD_REQUIRED        ON)
set(CMAKE_CXX_FLAGS_DEBUG              "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG           "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

set(INTEREST_ROOT                      ${CMAKE_CURRENT_SOURCE_DIR})
set(INTEREST_TARGET_NAME               ${PROJECT_NAME})
set(INTEREST_TARGETS_EXPORT_NAME       "${PROJECT_NAME}Targets")
set(INTEREST_INCLUDE_DIR               "include/Interest")
set(INTEREST_CONFIG_INSTALL_DIR        "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(INTEREST_INCLUDE_INSTALL_DIR       "${CMAKE_INSTALL_INCLUDEDIR}")
set(INTEREST_LIBRARY_INSTALL_DIR       "${CMAKE_INSTALL_LIBDIR}")
set(INTEREST_PROJECT_CONFIG_TEMPLATE   "cmake/${PROJECT_NAME}Config.cmake")
set(INTEREST_CMAKE_CONFIG_DIR          "${CMAKE_CURRENT_BINARY_DIR}/cmake")
set(INTEREST_PROJECT_CONFIG_FILE       "${INTEREST_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(INTEREST_PROJECT_TARGETS_FILE      "${INTEREST_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")

###
### BUILD
###
add_library(${INTEREST_TARGET_NAME} INTERFACE)
target_include_directories(${INTEREST_TARGET_NAME} INTERFACE ${INTEREST_INCLUDE_DIR})

###
### BOOST
###
find_package(Boost REQUIRED)

target_link_libraries(${INTEREST_TARGET_NAME} INTERFACE Boost::boost)

###
### TESTS
###
if (${BUILD_TESTS})
        message(STATUS "Testing enabled")

        set(CMAKE_CXX_FLAGS       "-fprofile-arcs -ftest-coverage")
        set(CMAKE_LINKER_FLAGS    "-fprofile-arcs -ftest-coverage")

        enable_testing()
        add_subdirectory(test)
endif()

###
### CONFIGURE AND INSTALL
###
include(CMakePackageConfigHelpers)

configure_file(
        ${INTEREST_PROJECT_CONFIG_TEMPLATE}
        ${INTEREST_PROJECT_CONFIG_FILE}
        COPYONLY)

install(
        DIRECTORY ${INTEREST_INCLUDE_DIR}
        DESTINATION ${INTEREST_INCLUDE_INSTALL_DIR})

install(
        TARGETS ${INTEREST_TARGET_NAME}
        EXPORT ${INTEREST_TARGETS_EXPORT_NAME}
        INCLUDES DESTINATION ${INTEREST_INCLUDE_INSTALL_DIR})

install(
        FILES ${INTEREST_PROJECT_CONFIG_FILE} ${INTEREST_PROJECT_TARGETS_FILE}
        DESTINATION "${INTEREST_CONFIG_INSTALL_DIR}")

export(
        EXPORT ${INTEREST_TARGETS_EXPORT_NAME}
        FILE ${INTEREST_PROJECT_TARGETS_FILE})
