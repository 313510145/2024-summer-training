module top_809960632_810038711_1598227639_893650103 (n51, n12, n67, n78, n22, n80, n72, n75, n6);
input n51, n12, n67, n78, n22, n80, n72, n75;
output n6;
wire n60, n37, n5, n45, n54, n88, n43, n20, n53, n58, n41, n83, n29;
xnor_4 g28 (n60, n5, n6);
or_6 g22 (n37, n12, n60);
not_8 g40 (n51, n37);
xnor_4 g1 (n45, n53, n5);
and_6 g31 (n54, n43, n45);
or_6 g57 (n88, n78, n54);
not_8 g24 (n67, n88);
and_6 g19 (n22, n20, n43);
or_6 g12 (n80, n67, n20);
or_6 g66 (n58, n41, n53);
and_6 g8 (n72, n67, n58);
or_6 g56 (n22, n83, n41);
nor_5 g68 (n29, n67, n83);
not_8 g33 (n75, n29);
endmodule
