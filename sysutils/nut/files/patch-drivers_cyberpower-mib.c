--- drivers/cyberpower-mib.c.orig
+++ drivers/cyberpower-mib.c
@@ -27,19 +27,40 @@
 #define CYBERPOWER_MIB_VERSION		"0.1"
 #define CYBERPOWER_OID_MODEL_NAME	".1.3.6.1.4.1.3808.1.1.1.1.1.1.0"
 
-#define CYBERPOWER_SYSOID			".1.3.6.1.4.1.3808"
+/* CPS-MIB::ups */
+#define CYBERPOWER_SYSOID			".1.3.6.1.4.1.3808.1.1.1"
 
 static info_lkp_t cyberpower_power_status[] = {
 	{ 2, "OL" },
 	{ 3, "OB" },
-	{ 4, "OL" },
-	{ 5, "OL" },
+	{ 4, "OL BOOST" },
+	{ 5, "OFF" },
 	{ 7, "OL" },
 	{ 1, "NULL" },
-	{ 6, "NULL" },
+	{ 6, "OFF" },
 	{ 0, NULL }
 } ;
 
+static info_lkp_t cyberpower_battery_status[] = {
+	{ 1, "" },	/* unknown */
+	{ 2, "" },	/* batteryNormal */
+	{ 3, "LB" },	/* batteryLow */
+	{ 0, NULL }
+} ;
+
+static info_lkp_t cyberpower_cal_status[] = {
+	{ 1, "" },          /* Calibration Successful */
+	{ 2, "" },          /* Calibration Invalid */
+	{ 3, "CAL" },       /* Calibration in progress */
+	{ 0, NULL }
+};
+
+static info_lkp_t cyberpower_battrepl_status[] = {
+	{ 1, "" },          /* No battery needs replacing */
+	{ 2, "RB" },        /* Batteries need to be replaced */
+	{ 0, NULL }
+};
+
 /* Snmp2NUT lookup table for CyberPower MIB */
 static snmp_info_t cyberpower_mib[] = {
 	/* Device page */
@@ -59,10 +80,18 @@ static snmp_info_t cyberpower_mib[] = {
 		0, NULL },
 
 	{ "ups.status", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.3808.1.1.1.4.1.1.0", "",
-		0 /*SU_STATUS_PWR*/, &cyberpower_power_status[0] },
+		SU_FLAG_OK | SU_STATUS_PWR, &cyberpower_power_status[0] },
+	{ "ups.status", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.3808.1.1.1.2.1.1.0", "",
+		SU_FLAG_OK | SU_STATUS_BATT, &cyberpower_battery_status[0] },
+	{ "ups.status", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.3808.1.1.1.7.2.7.0", "",
+		SU_FLAG_OK | SU_STATUS_CAL, &cyberpower_cal_status[0] },
+	{ "ups.status", ST_FLAG_STRING, SU_INFOSIZE, ".1.3.6.1.4.1.3808.1.1.1.2.2.5.0", "",
+		SU_FLAG_OK | SU_STATUS_RB, &cyberpower_battrepl_status[0] },
+	{ "ups.load", 0, 1.0, ".1.3.6.1.4.1.3808.1.1.1.4.2.3.0", "",
+		0, NULL },
 
-	/* Battery runtime is expressed in minutes */
-	{ "battery.runtime", 0, 60.0, ".1.3.6.1.4.1.3808.1.1.1.2.2.4.0", "",
+	/* Battery runtime is expressed in seconds */
+	{ "battery.runtime", 0, 1.0, ".1.3.6.1.4.1.3808.1.1.1.2.2.4.0", "",
 		0, NULL },
 	/* The elapsed time in seconds since the
 	 * UPS has switched to battery power */
@@ -72,6 +101,46 @@ static snmp_info_t cyberpower_mib[] = {
 		0, NULL },
 	{ "battery.current", 0, 0.1, ".1.3.6.1.4.1.3808.1.1.1.2.2.7.0", "",
 		0, NULL },
+	{ "battery.charge", 0, 1.0, ".1.3.6.1.4.1.3808.1.1.1.2.2.1.0", "",
+		0, NULL },
+
+	{ "input.voltage", 0, 0.1, ".1.3.6.1.4.1.3808.1.1.1.3.2.1.0", "",
+		0, NULL },
+	{ "input.frequency", 0, 0.1, ".1.3.6.1.4.1.3808.1.1.1.3.2.4.0", "",
+		0, NULL },
+
+	{ "output.voltage", 0, 0.1, ".1.3.6.1.4.1.3808.1.1.1.4.2.1.0", "",
+		0, NULL },
+
+	/* Delays affecting instant commands */
+
+	/* upsAdvanceConfigReturnDelay */
+	{ "ups.delay.start", ST_FLAG_RW, 1.0, ".1.3.6.1.4.1.3808.1.1.1.5.2.9.0", "0",
+		SU_FLAG_OK | SU_TYPE_TIME, NULL, NULL },
+	/* Not provided by CPS-MIB */
+	{ "ups.delay.reboot", 0, 1.0, NULL, "0",
+		SU_FLAG_OK | SU_FLAG_ABSENT, NULL, NULL },
+	/* upsAdvanceConfigSleepDelay */
+	{ "ups.delay.shutdown", ST_FLAG_RW, 1.0, ".1.3.6.1.4.1.3808.1.1.1.5.2.11.0", "60",
+		SU_FLAG_OK | SU_TYPE_TIME, NULL, NULL },
+	/* instant commands. */
+	/* upsAdvanceControlUpsOff */
+	{ "load.off", 0, 2, ".1.3.6.1.4.1.3808.1.1.1.6.2.1.0", NULL, SU_TYPE_CMD | SU_FLAG_OK, NULL },
+	/* upsAdvanceControlTurnOnUPS */
+	{ "load.on", 0, 2, ".1.3.6.1.4.1.3808.1.1.1.6.2.6.0", NULL, SU_TYPE_CMD | SU_FLAG_OK, NULL },
+	/* upsAdvanceControlUpsOff */
+	{ "shutdown.stayoff", 0, 3, ".1.3.6.1.4.1.3808.1.1.1.6.2.6.0", NULL, SU_TYPE_CMD | SU_FLAG_OK, NULL },
+	/* upsAdvanceControlUpsSleep */
+	{ "shutdown.return", 0, 3, ".1.3.6.1.4.1.3808.1.1.1.6.2.3.0", NULL, SU_TYPE_CMD | SU_FLAG_OK, NULL },
+	/* upsAdvanceControlSimulatePowerFail */
+	{ "test.failure.start", 0, 2, ".1.3.6.1.4.1.3808.1.1.1.6.2.4.0", NULL, SU_TYPE_CMD | SU_FLAG_OK, NULL },
+	/* upsAdvanceTestIndicators */
+	{ "test.panel.start", 0, 2, ".1.3.6.1.4.1.3808.1.1.1.7.2.5.0", NULL, SU_TYPE_CMD | SU_FLAG_OK, NULL },
+	/* upsAdvanceTestDiagnostics */
+	{ "test.battery.start", 0, 2, ".1.3.6.1.4.1.3808.1.1.1.7.2.2.0", NULL, SU_TYPE_CMD | SU_FLAG_OK, NULL },
+	/* upsAdvanceTestRuntimeCalibration */
+	{ "calibrate.start", 0, 2, ".1.3.6.1.4.1.3808.1.1.1.7.2.6.0", NULL, SU_TYPE_CMD | SU_FLAG_OK, NULL },
+	{ "calibrate.stop", 0, 3, ".1.3.6.1.4.1.3808.1.1.1.7.2.6.0", NULL, SU_TYPE_CMD | SU_FLAG_OK, NULL },
 
 	/* end of structure. */
 	{ NULL, 0, 0, NULL, NULL, 0, NULL, NULL }
