module top_809960632_810038711_1598227639_893650103 (n12, n2, n78, n18, n80, n51, n67, n22, n72, n75, n57, n34, n9);
input n12, n2, n78, n18, n80, n51, n67, n22, n72, n75, n57, n34;
output n9;
wire n61, n7, n84, n0, n66, n85, n24, n87, n26, n10, n15, n45, n54, n88, n43, n20, n76, n50, n28, n17, n36, n23, n29, n62, n53, n58, n41, n83, n30, n11, n46, n71, n31, n44, n55, n52, n64, n13;
xor_4 g2 (n61, n30, n9);
nor_5 g45 (n12, n7, n61);
nor_5 g13 (n84, n76, n7);
and_6 g74 (n0, n10, n84);
not_8 g69 (n66, n0);
and_6 g65 (n85, n87, n66);
or_6 g67 (n24, n78, n85);
not_8 g9 (n2, n24);
and_6 g25 (n18, n26, n87);
or_6 g7 (n80, n2, n26);
and_6 g44 (n51, n15, n10);
not_8 g16 (n45, n15);
and_6 g31 (n54, n43, n45);
or_6 g57 (n88, n78, n54);
not_8 g24 (n67, n88);
and_6 g19 (n22, n20, n43);
or_6 g12 (n80, n67, n20);
or_6 g64 (n50, n62, n76);
and_6 g15 (n28, n36, n50);
or_6 g76 (n17, n24, n28);
not_8 g58 (n72, n17);
nor_5 g48 (n18, n23, n36);
nor_5 g62 (n29, n2, n23);
not_8 g33 (n75, n29);
nor_5 g72 (n53, n66, n62);
or_6 g66 (n58, n41, n53);
and_6 g8 (n72, n67, n58);
or_6 g56 (n22, n83, n41);
nor_5 g68 (n29, n67, n83);
xnor_4 g55 (n11, n55, n30);
and_6 g61 (n46, n31, n11);
or_6 g49 (n71, n78, n46);
not_8 g27 (n57, n71);
and_6 g6 (n34, n44, n31);
or_6 g63 (n80, n57, n44);
or_6 g32 (n52, n64, n55);
and_6 g14 (n72, n57, n52);
or_6 g75 (n34, n13, n64);
nor_5 g52 (n29, n57, n13);
endmodule
