from vtk import *
import sys,os

reader = vtkXMLPolyDataReader()
reader.SetFileName( sys.argv[1] )

reader.Update( )

fdarray = reader.GetOutput().GetFieldData().GetArray(sys.argv[2])

print fdarray.GetTuple(0)

