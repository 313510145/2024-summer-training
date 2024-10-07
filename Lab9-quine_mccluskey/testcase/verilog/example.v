module top (v1, v2, v3, o1);
input v1, v2, v3;
output o1;
wire n1, n2;
nand_1 g1 (v1, v2, n1);
not_6  g2 (n1, n2);
or_9   g3 (n2, v3, o1);
endmodule
