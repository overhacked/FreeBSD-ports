--- src/endianness.c    2018-09-24 09:58:30.000000000 +0000
+++ src/endianness.c     2018-12-03 21:09:02.765637000 +0000
@@ -1,10 +1,16 @@
-#include <byteswap.h>
 #include <errno.h>
 #include <stdlib.h>
 #include <string.h>

 #include "endianness.h"

+#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
+#  include <sys/endian.h>
+#  define bswap_16 bswap16
+#  define bswap_32 bswap32
+#  define bswap_64 bswap64
+#endif
+
 typedef struct
 {
        const endianness_code_t endianness_code;
