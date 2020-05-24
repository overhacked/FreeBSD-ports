--- ipfix.c.orig      2019-08-16 13:42:16.000000000 +0000
+++ ipfix.c   2020-05-24 11:47:58.996607000 +0000
@@ -692,8 +692,8 @@
     }
     if (param->track_level >= TRACK_FULL_VLAN) {
       dv[i] = (struct IPFIX_SOFTFLOWD_DATA_VLAN *) &packet[offset];
-      dv[i]->vlanId = flow->vlanid[i];
-      dv[i]->postVlanId = flow->vlanid[i ^ 1];
+      dv[i]->vlanId = htons (flow->vlanid[i]);
+      dv[i]->postVlanId = htons (flow->vlanid[i ^ 1]);
       offset += sizeof (struct IPFIX_SOFTFLOWD_DATA_VLAN);
     }
     if (param->track_level >= TRACK_FULL_VLAN_ETHER) {
