--- src/modbus.c        2018-09-24 09:58:30.000000000 +0000
+++ src/modbus.c 2018-12-03 21:13:58.828691000 +0000
@@ -53,12 +53,9 @@

 #define MAX_RETRIES 10

-union semun
-{
-       int              val;
-       struct semid_ds *buf;
-       unsigned short * array;
-};
+#ifndef ETIME
+#  define ETIME ETIMEDOUT
+#endif

 /* the variable keeps timeout setting for item processing */
 static int item_timeout = 0;
