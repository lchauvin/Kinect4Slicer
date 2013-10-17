project(vtkSlicer${MODULE_NAME}ModuleMRML)

set(KIT ${PROJECT_NAME})

set(${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${MODULE_NAME_UPPER}_MODULE_MRML_EXPORT")

# Add Kinect library
set(KINECT_DIR "${CMAKE_SOURCE_DIR}/${MODULE_NAME}/Kinect/v1.5")
set(KINECT_INCLUDE_DIR "${KINECT_DIR}/inc")

# Link to the 32/64 bits version of the library
if(CMAKE_SIZEOF_VOID_P EQUAL 8 )
  set( KINECT_LIBRARY "${KINECT_DIR}/lib/amd64/Kinect10.lib" )
else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
  set( KINECT_LIBRARY "${KINECT_DIR}/lib/x86/Kinect10.lib" )
endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )

add_library(KinectLib STATIC IMPORTED)
set_property(TARGET KinectLib PROPERTY IMPORTED_LOCATION ${KINECT_LIBRARY})

set(${KIT}_INCLUDE_DIRECTORIES
  ${KINECT_INCLUDE_DIR}	
  )

set(${KIT}_SRCS
  vtkMRMLKinect4SlicerNode.cxx
  vtkMRMLKinect4SlicerNode.h
  vtkMRMLKinectPositionNode.cxx
  vtkMRMLKinectPositionNode.h
  )

set(${KIT}_TARGET_LIBRARIES
  ${ITK_LIBRARIES}
  ${MRML_LIBRARIES}
  KinectLib
  )

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleMRML(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
