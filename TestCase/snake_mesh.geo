lc = 0.5;



Point(1) = {-2, -0.25, 0, lc};
Point(2) = {15, -0.25,  0, lc};
Point(3) = {15, 0.25, 0, lc};
Point(4) = {-2,  0.25, 0, lc};
Point(5) = {0, -0.25, 0, lc};
Point(6) = {0,  0.25, 0, lc};


Line(1) = {1, 5};
Line(2) = {5, 2};
Line(3) = {2, 3};
Line(4) = {3, 6};
Line(5) = {6, 4};
Line(6) = {4, 1};
Line(7) = {5, 6};

Transfinite Line{1} = 5;
Transfinite Line{2} = 20;
Transfinite Line{3} = 5;
Transfinite Line{4} = 20;
Transfinite Line{5} = 5;
Transfinite Line{6} = 5;
Transfinite Line{7} = 5;

Curve Loop(1) = {1, 7, 5, 6};
Curve Loop(2) = {2, 3, 4, -7};

Plane Surface(1) = {1};
Transfinite Surface{1} = {1,5,6,4};
Recombine Surface{1};
Plane Surface(2) = {2};
Transfinite Surface{2} = {5,2,3,6};
Recombine Surface{2};

Physical Curve(0) = {2, 4}; //wall
Physical Curve(1) = {3}; //outlet
Physical Curve(2) = {6}; //inlet
Physical Curve(3) = {1,5}; //symmetry

Physical Surface(10) = {1,2}; //domain


Mesh.MshFileVersion = 2.2;


