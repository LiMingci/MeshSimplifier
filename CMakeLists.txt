PROJECT(CcMeshSim)

CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

Message("################## Setting up ${PROJECT_NAME} #########################")
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModule;${CMAKE_MODULE_PATH}")

SET_PROPERTY( GLOBAL PROPERTY USE_FOLDERS ON )
SET_PROPERTY( GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake Targets" )

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)













