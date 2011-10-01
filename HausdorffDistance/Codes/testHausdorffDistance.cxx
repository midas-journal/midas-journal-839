// Copyright (c) 2011 LTSI INSERM U642
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation and/or
// other materials provided with the distribution.
//     * Neither name of LTSI, INSERM nor the names
// of any contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS''
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "vtkHausdorffDistancePointSetFilter.h"

#include <vtkSphereSource.h>
#include <vtkBrownianPoints.h>
#include <vtkWarpVector.h>
#include <vtkSmartPointer.h>
#include <vtkFieldData.h>

int main(int argc,char** argv)
{
  
  vtkSmartPointer<vtkSphereSource> sourceA = vtkSmartPointer<vtkSphereSource>::New();
  vtkSmartPointer<vtkBrownianPoints> randomVectors = vtkSmartPointer<vtkBrownianPoints>::New();
  vtkSmartPointer<vtkWarpVector> warp = vtkSmartPointer<vtkWarpVector>::New();
 
  randomVectors->SetInputConnection( sourceA->GetOutputPort( ) );
  warp->SetInputConnection( randomVectors->GetOutputPort( ) );

  vtkSmartPointer<vtkHausdorffDistancePointSetFilter> filter = vtkSmartPointer<vtkHausdorffDistancePointSetFilter>::New();
  filter->SetInputConnection(0, sourceA->GetOutputPort());
  filter->SetInputConnection(1, warp->GetOutputPort());

  sourceA->SetThetaResolution( 80 );
  sourceA->SetPhiResolution( 80 );
  sourceA->SetRadius( 20 );

  // Test cell-interpolated measure
  filter->SetTargetDistanceMethod( vtkHausdorffDistancePointSetFilter::POINT_TO_POINT );

  for( int i = 0; i < 10; i++ )
  {
     warp->SetScaleFactor( i/10. );
     filter->Update();
     // Test the existence of output distance arrays
     std::cout << static_cast<vtkPointSet*>(filter->GetOutput(0))->GetFieldData()->GetArray("HausdorffDistance")->GetComponent(0,0) << " "
              << filter->GetOutputDataObject(0)->GetFieldData()->GetArray("RelativeDistanceAtoB")->GetComponent(0,0) << " "
              << filter->GetOutputDataObject(1)->GetFieldData()->GetArray("RelativeDistanceBtoA")->GetComponent(0,0) << " "
              << std::endl;
  }

  std::cout << endl;
  // Test cell-interpolated measure
  filter->SetTargetDistanceMethod( vtkHausdorffDistancePointSetFilter::POINT_TO_CELL );

  for( int i = 0; i < 10; i++ )
  {
     warp->SetScaleFactor( i/10. );
     filter->Update();
     // Test the existence of output distance arrays
     std::cout << static_cast<vtkPointSet*>(filter->GetOutput(0))->GetFieldData()->GetArray("HausdorffDistance")->GetComponent(0,0) << " "
              << filter->GetOutputDataObject(0)->GetFieldData()->GetArray("RelativeDistanceAtoB")->GetComponent(0,0) << " "
              << filter->GetOutputDataObject(1)->GetFieldData()->GetArray("RelativeDistanceBtoA")->GetComponent(0,0) << " "
              << std::endl;
  }

return( EXIT_SUCCESS );  
}
