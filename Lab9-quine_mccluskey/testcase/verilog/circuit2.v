module top_809960632_810038711_1598227639_893650103 (n12, n72, n67, n22, n75, n51, n78, n80, n2, n18, n42);
input n12, n72, n67, n22, n75, n51, n78, n80, n2, n18;
output n42;
wire n40, n27, n53, n58, n41, n83, n29, n16, n10, n15, n45, n54, n88, n43, n20, n69, n0, n66, n85, n24, n87, n26, n50, n28, n17, n36, n23;
xor_4 g37 (n40, n69, n42);
nor_5 g3 (n12, n27, n40);
and_6 g20 (n53, n16, n27);
or_6 g66 (n58, n41, n53);
and_6 g8 (n72, n67, n58);
or_6 g56 (n22, n83, n41);
nor_5 g68 (n29, n67, n83);
not_8 g33 (n75, n29);
not_8 g4 (n10, n16);
and_6 g44 (n51, n15, n10);
not_8 g16 (n45, n15);
and_6 g31 (n54, n43, n45);
or_6 g57 (n88, n78, n54);
not_8 g24 (n67, n88);
and_6 g19 (n22, n20, n43);
or_6 g12 (n80, n67, n20);
xnor_4 g17 (n0, n50, n69);
not_8 g69 (n66, n0);
and_6 g65 (n85, n87, n66);
or_6 g67 (n24, n78, n85);
not_8 g9 (n2, n24);
and_6 g25 (n18, n26, n87);
or_6 g7 (n80, n2, n26);
and_6 g15 (n28, n36, n50);
or_6 g76 (n17, n24, n28);
not_8 g58 (n72, n17);
nor_5 g48 (n18, n23, n36);
nor_5 g62 (n29, n2, n23);
endmodule
