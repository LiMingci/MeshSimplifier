SET(THIS_LIB_NAME CcMeshSim)

ADD_DEFINITIONS("-DMAKE_CCMESHSIM_DLL")
########################################### GRAB SOURCE FILES ##########################################
FILE(GLOB THIS_LIB_SRCS RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
									)
																										

############################### GRAB HEADERS #####################################
FILE(GLOB THIS_LIB_HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" 
                                    "${CMAKE_CURRENT_SOURCE_DIR}/../include/*.h"
									)								
                  

FIND_PATH(VCG_INCLUDE_DIR vcg
          DOC "Path to VCG library include directory")

IF(NOT VCG_INCLUDE_DIR)
	MESSAGE(FATAL_ERROR "Please set the vcg include path")
ENDIF()

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../include
                    ${VCG_INCLUDE_DIR})

ADD_LIBRARY(${THIS_LIB_NAME} SHARED ${THIS_LIB_SRCS} ${THIS_LIB_HEADERS})

SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../bin)