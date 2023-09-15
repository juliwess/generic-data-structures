#----------------------------------------------#
#-----Konfiguration des Buildsystems CMake-----#
#----------------------------------------------#

# Minimale Version des Buildsystems
cmake_minimum_required(VERSION 3.16)
# Name des Projekts
project(ProjektAlpha)

#----------------------------------------------#
#-------------------Optionen-------------------#
#----------------------------------------------#

# Setzte verwendeten C++-Standard auf C++17
set(CMAKE_CXX_STANDARD 17)
# Optional: Baue mit Debugsymbolen / Optimierung
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_BUILD_TYPE Release)
# Optional: Prüfe alle Targets auf Speicherlecks
# add_compile_options(-fsanitize=address)
# add_link_options(-fsanitize=address)

# Füge Includeverzeichnisse hinzu
include_directories(include)
include_directories(external)
# Legt die Variable SRC_FILES an, die alle
# .cpp-Dateien des Projekts benennt,
# die in Verzeichnis src/ liegen.
file(GLOB SRC_FILES
  ${PROJECT_SOURCE_DIR}/src/*.cpp)

#----------------------------------------------#
#-------------Erzeuge Zeitmesser---------------#
#----------------------------------------------#

# Baue das Programm 'demo1' aus den Quellen
# examples/demo1.cpp und allen Quelldateien in
# SRC_FILES (also alle im Verzeichnis src/)
add_executable(zeitmessung
  tests/zeitmessung.cpp
  ${SRC_FILES}
)

#----------------------------------------------#
#---------------Erzeuge Projekt----------------#
#----------------------------------------------#

# Baue das Programm 'demo1' aus den Quellen
# examples/demo1.cpp und allen Quelldateien in
# SRC_FILES (also alle im Verzeichnis src/)
add_executable(demo_1
  examples/demo_1.cpp
  ${SRC_FILES}
)

#----------------------------------------------#
#-------------------Doxygen--------------------#
#----------------------------------------------#

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/./docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

#----------------------------------------------#
#----------Download and use GoogleTest---------#
#----------------------------------------------#

# Use CMakes FetchContent
include(FetchContent)
# Workaround for CMake >= 3.24
# Avoid warning about DOWNLOAD_EXTRACT_TIMESTAMP
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

# Download GoogleTest (we use version 1.12.1)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Workaround for Windows:
# Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Include CMake configuration of GoogleTest
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# Enable GoogleTest
enable_testing()

#----------------------------------------------#
#-------------Erzeuge Testprogramme------------#
#----------------------------------------------#

# Declare test program demo_1_test
add_executable(demo_1_test tests/demo_1_test.cpp ${SRC_FILES})
target_link_libraries(demo_1_test GTest::gtest_main)
gtest_discover_tests(demo_1_test)


# # Declare test program demo_3_test
add_executable(demo_3_test tests/demo_3_test.cpp ${SRC_FILES})
target_link_libraries(demo_3_test GTest::gtest_main)
gtest_discover_tests(demo_3_test)


# # Declare test program demo_3_test
add_executable(test_florian tests/test_florian.cpp ${SRC_FILES})
target_link_libraries(test_florian GTest::gtest_main)
gtest_discover_tests(test_florian)

# # Declare test program demo_3_test
add_executable(test_max tests/test_max.cpp ${SRC_FILES})
target_link_libraries(test_max GTest::gtest_main)
gtest_discover_tests(test_max)

# # Declare test program demo_3_test
add_executable(test_julian tests/test_julian.cpp ${SRC_FILES})
target_link_libraries(test_julian GTest::gtest_main)
gtest_discover_tests(test_julian)


