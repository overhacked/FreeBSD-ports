--- softflowd.c.orig
+++ softflowd.c
@@ -1233,6 +1233,11 @@ datalink_check (int linktype, const u_int8_t * pkt, u_int32_t caplen, int *af,
         *vlanid <<= 8;
         *vlanid |= pkt[j + dl->skiplen];
       }
+      /* 
+       * Mask out the PCP and DEI values,
+       * leaving just the VID.
+       */
+      *vlanid &= 0xFFF;
       vlan_size = 4;
     }
   }
