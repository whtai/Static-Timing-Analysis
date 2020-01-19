
`timescale 1ns/1ps
`celldefine
module NOT1 (Y, A);
output Y;
input A;

  not I0(Y, A);
  specify
    
    specparam
      tplh$A$Y = 1,
      tphl$A$Y = 1;

    
    (A *> Y) = (tplh$A$Y, tphl$A$Y);
  endspecify

endmodule 
`endcelldefine

`timescale 1ns/1ps
`celldefine
module NAND2 (Y, A, B);
output Y;
input A, B;

  nand (Y, A, B);

  specify
    
    specparam
      tplh$A$Y = 1,
      tphl$A$Y = 1,
      tplh$B$Y = 1,
      tphl$B$Y = 1;

    
    (A *> Y) = (tplh$A$Y, tphl$A$Y);
    (B *> Y) = (tplh$B$Y, tphl$B$Y);
  endspecify

endmodule 
`endcelldefine

`timescale 1ns/1ps
`celldefine
module NOR2 (Y, A, B);
output Y;
input A, B;

  nor (Y, A, B);

  specify
    
    specparam
      tplh$A$Y = 1,
      tphl$A$Y = 1,
      tplh$B$Y = 1,
      tphl$B$Y = 1;

    
    (A *> Y) = (tplh$A$Y, tphl$A$Y);
    (B *> Y) = (tplh$B$Y, tphl$B$Y);
  endspecify

endmodule 
`endcelldefine
