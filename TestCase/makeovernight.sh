NEK=~/Documents/gitproject/nektar++/build/solvers/IncNavierStokesSolver;
GMSH=~/Documents/gmsh/bin;
case="snake";

#$GMSH/gmsh ${case}_mesh.geo -2
#$NEK/../../utilities/NekMesh/NekMesh-g ${case}_mesh.msh ${case}_mesh.xml
#$NEK/../../utilities/NekMesh/NekMesh-g ${case}_mesh.xml ${case}_mesh.xml:xml:uncompress
#$NEK/../../utilities/FieldConvert/FieldConvert-g ${case}_mesh.xml ${case}_mesh.vtu

#mv ${case}_mesh.xml ./steady2/${case}_mesh.xml

cd base
$NEK/IncNavierStokesSolver-g ${case}_mesh.xml ${case}_nonlinear.xml


j=16000;

while [  $j -lt "20001" ]; do

echo $j
aux=$(bc <<< "$j-16000")
newname=$(printf "%d" $aux)

mv ${case}_mesh_${j}.chk ../adjoint/${case}_nonlinear_${newname}.chk

j=$(($j+1));

done

cd ../adjoint

#cd adjoint
$NEK/IncNavierStokesSolver-g ${case}_mesh.xml ${case}_adjoint.xml

#cd ../fd

#$NEK/IncNavierStokesSolver ${case}_mesh.xml ${case}_ap.xml

#$NEK/IncNavierStokesSolver ${case}_mesh.xml ${case}_am.xml

#$NEK/IncNavierStokesSolver ${case}_mesh.xml ${case}_wp.xml

#$NEK/IncNavierStokesSolver ${case}_mesh.xml ${case}_wm.xml

