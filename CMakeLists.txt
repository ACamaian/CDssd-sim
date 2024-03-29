#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.8...3.18)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
  cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(CDSSD-sim)

set (CMAKE_CXX_STANDARD 17)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()


#---------------------------------------------------------------------------
#  Load some basic macros which are needed later on
#
include(FindROOT.cmake)

#---------------------------------------------------------------------------
# Create the directory for the ROOT files
#
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/output")
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/analysis/")

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/inc)
include_directories(${ROOT_INCLUDE_DIR})

#----------------------------------------------------------------------------
#Setup ROOT linking directories
#
link_directories( ${ROOT_LIBRARY_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/CDSSD*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/inc/CDSSD*.hh)

#----------------------------------------------------------------------------
# Set everything needed for the root dictonary and create the
# dictionary
#set(DEMO_HEADERS
#		 ${PROJECT_SOURCE_DIR}/include/DEMOData.hh
#		     ${PROJECT_SOURCE_DIR}/include/DEMOTrack.hh
#		     ${PROJECT_SOURCE_DIR}/include/DEMOSimpleTrack.hh
#		     ${PROJECT_SOURCE_DIR}/include/DEMOPrimaryInfo.hh
#		     ${PROJECT_SOURCE_DIR}/include/DEMOBeamInfo.hh
#		     )
#set(DEMO_LINKDEF ${PROJECT_SOURCE_DIR}/src/DEMOLinkDef.hh )
#set(DEMO_DICTIONARY DEMODict.cc)
#ROOT_GENERATE_DICTIONARY("${DEMO_HEADERS}" "${DEMO_LINKDEF}" "${DEMO_DICTIONARY}" "${ROOT_INCLUDE_DIR}")

#----------------------------------------------------------------------------
# Set the library version in the main CMakeLists.txt
SET(CDSSD_MAJOR_VERSION 0)
SET(CDSSD_MINOR_VERSION 0)
SET(CDSSD_PATCH_VERSION 0)
SET(CDSSD_VERSION "${CDSSD_MAJOR_VERSION}.${CDSSD_MINOR_VERSION}.${CDSSD_PATCH_VERSION}")
SET(DEMO_LIBRARY_PROPERTIES ${CDSSD_LIBRARY_PROPERTIES}
    VERSION "${CDSSD_VERSION}"
    SOVERSION "${CDSSD_MAJOR_VERSION}"
    SUFFIX ".sl"
)

add_library(cd SHARED CDSSD.cc ${CDSSD_DICTIONARY} ${sources} ${headers})
target_link_libraries(cd ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
#set_target_properties(actar PROPERTIES ${DEMO_LIBRARY_PROPERTIES})


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(CDssdsim CDSSD.cc ${DEMO_DICTIONARY}  ${sources} ${headers})
target_link_libraries(CDssdsim ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
add_dependencies(CDssdsim cd)


#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(CDSCRIPT
  cd.in
  cd.out
  init_vis.mac
  run.mac
  vis.mac
  EstarNe20.dat
  Ne20_5alpha_bcs_decay_path.dat
    awm95.txt
   )

foreach(_script ${CDSCRIPT})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

