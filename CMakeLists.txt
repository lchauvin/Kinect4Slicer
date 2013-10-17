cmake_minimum_required(VERSION 2.8.9)

project(Kinect4Slicer)

# --- MODULE AVAILABLE ON WINDOWS ONLY ---

if(WIN32)

#-----------------------------------------------------------------------------
set(EXTENSION_HOMEPAGE "http://www.slicer.org/slicerWiki/index.php/Documentation/4.3/Extensions/Kinect4Slicer")
set(EXTENSION_CATEGORY "Examples")
set(EXTENSION_CONTRIBUTORS "Jean-Christophe Fillion-Robin (Kitware)")
set(EXTENSION_DESCRIPTION "This is an example of extension bundling a loadable module")
set(EXTENSION_ICONURL "http://viewvc.slicer.org/viewvc.cgi/Slicer4/trunk/Extensions/Testing/Kinect4Slicer/Kinect4Slicer.png?revision=21746&view=co")
set(EXTENSION_SCREENSHOTURLS "http://wiki.slicer.org/slicerWiki/images/4/42/Slicer-r19441-Kinect4Slicer-screenshot.png")

#-----------------------------------------------------------------------------
find_package(Slicer REQUIRED)
include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
add_subdirectory(Kinect4Slicer)

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})

else(WIN32)
  message(FATAL_ERROR "This extension is only available for Windows platform.")
endif(WIN32)
