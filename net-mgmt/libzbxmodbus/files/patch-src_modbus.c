--- src/modbus.c.orig	2018-12-15 02:00:43 UTC
+++ src/modbus.c
@@ -60,6 +60,10 @@ union semun
 	unsigned short * array;
 };
 
+#ifndef ETIME
+#  define ETIME ETIMEDOUT
+#endif
+
 /* the variable keeps timeout setting for item processing */
 static int item_timeout = 0;
 
