--- src/endianness.c.orig	2018-09-24 09:58:30 UTC
+++ src/endianness.c
@@ -1,9 +1,15 @@
-#include <byteswap.h>
 #include <errno.h>
 #include <stdlib.h>
 #include <string.h>
 
 #include "endianness.h"
+
+#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
+#  include <sys/endian.h>
+#  define bswap_16 bswap16
+#  define bswap_32 bswap32
+#  define bswap_64 bswap64
+#endif
 
 typedef struct
 {
