set J1;
set J2;
set J;
set I1;
set I2;
set I3;

param b1{I1};
param b2{I2};
param b3{I3};

param c{J};

param a1{I1, J};
param a2{I2, J};
param a3{I3, J}; 

var x{J};

minimize z: sum{j in J} c[j]*x[j];

s.t. v1 {i in I1}: sum{j in J} a1[i,j]*x[j] <= b1[i];
s.t. v2 {i in I2}: sum{j in J} a2[i,j]*x[j] >= b2[i];
s.t. v3 {i in I3}: sum{j in J} a3[i,j]*x[j] == b3[i];

s.t. vj1 {j in J1}: x[j] >= 0;
s.t. vj2 {j in J2}: x[j] <= 0;




