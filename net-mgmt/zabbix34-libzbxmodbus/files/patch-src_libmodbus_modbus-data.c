--- libmodbus/src/modbus-data.c 2018-09-24 09:58:31.000000000 +0000
+++ libmodbus/src/modbus-data.c  2018-12-03 21:04:36.280902000 +0000
@@ -36,6 +36,13 @@
 #  define bswap_64 OSSwapInt64
 #endif

+#if defined(__FreeBSD__) || defined(__DragonFly__) || defined(__NetBSD__)
+#  include <sys/endian.h>
+#  define bswap_16 bswap16
+#  define bswap_32 bswap32
+#  define bswap_64 bswap64
+#endif
+
 #if defined(__GNUC__)
 #  define GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__ * 10)
 #  if GCC_VERSION >= 430
