--- drivers/snmp-ups.c.orig
+++ drivers/snmp-ups.c
@@ -2006,7 +2006,12 @@ int su_setvar(const char *varname, const char *val)
 			value = atof(val) / su_info_p->info_len;
 		}
 		/* Actually apply the new value */
-		status = nut_snmp_set_int(su_info_p->OID, value);
+		if (su_info_p->flags & SU_TYPE_TIME) {
+			status = nut_snmp_set_time(su_info_p->OID, value);
+		}
+		else {
+			status = nut_snmp_set_int(su_info_p->OID, value);
+		}
 	}
 
 	if (status == FALSE)
