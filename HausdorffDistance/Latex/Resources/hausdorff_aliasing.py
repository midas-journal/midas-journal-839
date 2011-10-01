#!/usr/bin/env python
import numpy as np
import matplotlib.pyplot as plt
import os, sys

csvfile = open("hausdorff_aliasing")

hausdorff = []
AtoB = []
BtoA = []

line = csvfile.readline()
while( line != "" ):
   line = csvfile.readline()
   distances = line.split( " " )
   if( len(distances) == 4 ):
      hausdorff.append( distances[0] )
      AtoB.append( distances[1] )
      BtoA.append( distances[2] )

width = 0.65       # the width of the bars

plt.subplot(111)
rects1 = plt.plot( hausdorff )
#rects1 = plt.plot( AtoB )
#rects1 = plt.plot( BtoA )

plt.ylabel('Hausdorff distance')
plt.xlabel('Coarsening factor')

coarseningFactors = range(11,1,-1)

plt.xticks( range(0,10),('10','9','8','7','6','5','4','3','2','1') )

plt.show()

