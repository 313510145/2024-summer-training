module top_809960632_810038711_1598227639_893650103 (n72, n4, n35, n75, n78, n80, n57, n34, n2, n18, n67, n22, n48);
input n72, n4, n35, n75, n78, n80, n57, n34, n2, n18, n67, n22;
output n48;
wire n63, n49, n3, n38, n74, n29, n32, n90, n14, n21, n59, n25, n1, n55, n52, n64, n13, n70, n11, n46, n71, n31, n44, n47, n76, n50, n28, n17, n24, n36, n23, n62, n53, n58, n41, n83, n66, n85, n87, n26;
not_8 g26 (n63, n48);
or_6 g71 (n49, n32, n63);
and_6 g43 (n3, n38, n49);
nand_5 g18 (n72, n4, n3);
nor_5 g60 (n35, n74, n38);
nor_5 g34 (n29, n4, n74);
not_8 g33 (n75, n29);
nor_5 g50 (n90, n1, n32);
and_6 g41 (n14, n59, n90);
or_6 g10 (n21, n78, n14);
not_8 g21 (n4, n21);
and_6 g30 (n35, n25, n59);
or_6 g42 (n80, n4, n25);
and_6 g23 (n55, n70, n1);
or_6 g32 (n52, n64, n55);
and_6 g14 (n72, n57, n52);
or_6 g75 (n34, n13, n64);
nor_5 g52 (n29, n57, n13);
or_6 g47 (n11, n47, n70);
and_6 g61 (n46, n31, n11);
or_6 g49 (n71, n78, n46);
not_8 g27 (n57, n71);
and_6 g6 (n34, n44, n31);
or_6 g63 (n80, n57, n44);
not_8 g70 (n76, n47);
or_6 g64 (n50, n62, n76);
and_6 g15 (n28, n36, n50);
or_6 g76 (n17, n24, n28);
not_8 g58 (n72, n17);
not_8 g9 (n2, n24);
nor_5 g48 (n18, n23, n36);
nor_5 g62 (n29, n2, n23);
nor_5 g72 (n53, n66, n62);
or_6 g66 (n58, n41, n53);
and_6 g8 (n72, n67, n58);
or_6 g56 (n22, n83, n41);
nor_5 g68 (n29, n67, n83);
and_6 g65 (n85, n87, n66);
or_6 g67 (n24, n78, n85);
and_6 g25 (n18, n26, n87);
or_6 g7 (n80, n2, n26);
endmodule