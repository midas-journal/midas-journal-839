#!bin/sh
echo "Hausdorff AtoB BtoA" > hausdorff_aliasing;
for i in {0..9};
do
   TestHausdorffDistance -a sphere0.vtp -b contour$i.vtp -t 1 -p -x >> hausdorff_aliasing;
done;
