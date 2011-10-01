# Copyright (c) 2011 LTSI INSERM U642
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without modification,
# are permitted provided that the following conditions are met:
# 
#     * Redistributions of source code must retain the above copyright notice,
# this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation and/or
# other materials provided with the distribution.
#     * Neither name of LTSI, INSERM nor the names
# of any contributors may be used to endorse or promote products derived from this
# software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
# ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

PROJECT (vtkHausdorffDistancePointSetFilter)

### The following are needed to avoid warnings. See CMake doc. ######
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

if(COMMAND cmake_policy)
cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
#####################################################################


SET (LIBRARY_OUTPUT_PATH ${vtkHausdorffDistancePointSetFilter_BINARY_DIR}/bin
     CACHE 
     PATH
     "Single output directory for building all libraries.")

SET (EXECUTABLE_OUTPUT_PATH ${vtkHausdorffDistancePointSetFilter_BINARY_DIR}/bin
     CACHE
     PATH
     "Single output directory for building all executables.")
     
INCLUDE_DIRECTORIES (${LIBRARY_OUTPUT_PATH})
INCLUDE_DIRECTORIES (${EXECUTABLE_OUTPUT_PATH})

OPTION( BUILD_PARAVIEW_PLUGIN
        "Build paraview plugin"
        OFF )

OPTION( BUILD_EXAMPLE
        "Build example"
        OFF )

IF( BUILD_PARAVIEW_PLUGIN )
   # FILTER PLUGIN --------------------------------------------------
   FIND_PACKAGE(ParaView)
   INCLUDE(${PARAVIEW_USE_FILE})

   # Use the ADD_PARAVIEW_PLUGIN macro to build a plugin
   ADD_PARAVIEW_PLUGIN(
      pvHausdorffDistance          #<--Name for the plugin
      "1.0"                        #<--Version string
      SERVER_MANAGER_XML HausdorffDistancePointSetFilter.xml
      SERVER_MANAGER_SOURCES vtkHausdorffDistancePointSetFilter.cxx
      GUI_RESOURCE_FILES HausdorffDistanceMenu.xml
   )

   TARGET_LINK_LIBRARIES( pvHausdorffDistance vtkIO vtkCommon )

#------------------------------------------------------------------
ENDIF( BUILD_PARAVIEW_PLUGIN )

FIND_PACKAGE(VTK)
INCLUDE( ${VTK_USE_FILE} )


IF( BUILD_EXAMPLE )
   # EXAMPLE ---------------------------------------------------------
   

   ADD_EXECUTABLE( HausdorffDistance HausdorffDistance.cxx vtkHausdorffDistancePointSetFilter.cxx )
   TARGET_LINK_LIBRARIES( HausdorffDistance vtkIO vtkCommon )

#------------------------------------------------------------------
ENDIF( BUILD_EXAMPLE )

INCLUDE( CTest )
ADD_EXECUTABLE( testHausdorffDistance testHausdorffDistance.cxx vtkHausdorffDistancePointSetFilter.cxx )
TARGET_LINK_LIBRARIES( testHausdorffDistance vtkGraphics vtkCommon )

ADD_TEST( testHausdorffDistance ${EXECUTABLE_OUTPUT_PATH}/testHausdorffDistance )

