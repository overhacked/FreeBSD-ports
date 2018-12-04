--- src/modbus.c.orig	2018-09-24 09:58:30 UTC
+++ src/modbus.c
@@ -53,12 +53,9 @@ int MODBUS_SEM_ID = -1;
 
 #define MAX_RETRIES 10
 
-union semun
-{
-	int		 val;
-	struct semid_ds *buf;
-	unsigned short * array;
-};
+#ifndef ETIME
+#  define ETIME ETIMEDOUT
+#endif
 
 /* the variable keeps timeout setting for item processing */
 static int item_timeout = 0;
