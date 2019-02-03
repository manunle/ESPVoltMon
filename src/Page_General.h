//
//  HTML PAGE
//

const char PAGE_AdminGeneralSettings[] PROGMEM =  R"=====(
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<a href="/"  class="btn btn--s"><</a>&nbsp;&nbsp;<strong>General Settings</strong>
<hr>
<form action="" method="post">
<table border="0"  cellspacing="0" cellpadding="3" >
<tr>
	<td align="right">Name of Device</td>
	<td><input type="text" id="devicename" name="devicename" value=""></td>
</tr>
<tr>
  <td align="right">OTA Password</td>
  <td><input type="text" id="OTApwd" name="OTApwd" value=""></td>
</tr>
<tr>
  <td align="right">MQTT Server</td>
  <td><input type="text" id="MQTTServer" name="MQTTServer" value=""></td>
</tr>
<tr>
  <td align="right">MQTT Port</td>
  <td><input type="text" id="MQTTPort" name="MQTTPort" value=""></td>
</tr>
<tr>
  <td align="right">Heartbeat Topic</td>
  <td><input type="text" id="HeartbeatTopic" name="HeartbeatTopic" value=""></td>
</tr>
<tr>
  <td align="right">Heartbeat Every</td>
  <td><input type="text" id="HeartbeatEvery" name="HeartbeatEvery" value=""></td>
</tr>
<tr>
  <td align="right">Sleep Topic</td>
  <td><input type="text" id="SleepTopic" name="SleepTopic" value=""></td>
</tr>
<tr>
  <td align="right">Sleep Duration</td>
  <td><input type="text" id="SleepDuration" name="SleepDuration" value=""></td>
</tr>
<tr><td align="right">Sleep after volts</td><td><input type="checkbox" id="SleepAfterVolts" name="SleepAfterVolts"></td></tr>
<tr>
  <td align="right">Sleep After Volts Duration</td>
  <td><input type="text" id="SleepAfterVoltsDuration" name="SleepAfterVoltsDuration" value=""></td>
</tr>
<tr><td align="right">Sleep if not connected</td><td><input type="checkbox" id="SleepIfNotConnected" name="SleepIfNotConnected"></td></tr>
<tr>
  <td align="right">Sleep if not connected Duration</td>
  <td><input type="text" id="SNCDuration" name="SNCDuration" value=""></td>
</tr>
<tr>
  <td align="right">Voltage calibration value</td>
  <td><input type="text" id="voltcalib" name="voltcalib" value=""></td>
</tr>
<tr>
  <td align="right">Voltage email threshold value</td>
  <td><input type="text" id="VoltEmailThreshold" name="VoltEmailThreshold" value=""></td>
</tr>
<tr>
  <td align="right">Email Address</td>
  <td><input type="text" id="EmailAddress" name="EmailAddress" value=""></td>
</tr>
<tr>
  <td align="right">Relay Pin</td>
  <td><input type="text" id="RelayPin" name="RelayPin" value=""></td>
</tr>
<tr><td colspan="2" align="center"><input type="submit" style="width:150px" class="btn btn--m btn--blue" value="Save"></td></tr>
</table>
</form>
<script>

 

window.onload = function ()
{
	load("style.css","css", function() 
	{
		load("microajax.js","js", function() 
		{
				setValues("/admin/generalvalues");
		});
	});
}
function load(e,t,n){if("js"==t){var a=document.createElement("script");a.src=e,a.type="text/javascript",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}else if("css"==t){var a=document.createElement("link");a.href=e,a.rel="stylesheet",a.type="text/css",a.async=!1,a.onload=function(){n()},document.getElementsByTagName("head")[0].appendChild(a)}}



</script>
)=====";


// Functions for this Page
void send_devicename_value_html()
{
		
	String values ="";
	values += "devicename|" + (String) config.DeviceName + "|div\n";
  values += "OTApwd|" + (String) config.OTApwd + "|div\n";
  values += "MQTTServer|" + (String) config.MQTTServer + "|div\n";
  values += "MQTTPort|" + (String) config.MQTTPort + "|div\n";
  values += "HeartbeatTopic|" + (String) config.HeartbeatTopic + "|div\n";
  values += "HeartbeatEvery|" + (String) config.HeartbeatEvery + "|div\n";
  values += "SleepTopic|" + (String) config.SleepTopic + "|div\n";
  values += "SleepDuration|" + (String) config.SleepDuration + "|div\n";
	values += "SleepAfterVolts|" +  (String) (config.SleepAfterVolts ? "checked" : "") + "|chk\n";
  values += "SleepAfterVoltsDuration|" + (String) config.SleepAfterVoltsDuration + "|div\n";
	values += "SleepIfNotConnected|" +  (String) (config.SleepIfNotConnected ? "checked" : "") + "|chk\n";
  values += "SNCDuration|" + (String) config.SNCDuration + "|div\n";
  values += "voltcalib|" + (String) config.voltcalib + "|div\n";
  values += "VoltEmailThreshold|" + (String) config.VoltEmailThreshold + "|div\n";
  values += "EmailAddress|" + (String) config.EmailAddress + "|div\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
	
}

void send_general_html()
{
	
	if (server.args() > 0 )  // Save Settings
	{	
		String temp = "";
    config.SleepAfterVolts = false;
    config.SleepIfNotConnected = false;
		for ( uint8_t i = 0; i < server.args(); i++ ) {
			if (server.argName(i) == "devicename") config.DeviceName = urldecode(server.arg(i)); 
      if (server.argName(i) == "OTApwd") config.OTApwd = urldecode(server.arg(i));
      if (server.argName(i) == "MQTTServer") config.MQTTServer = urldecode(server.arg(i));
      if (server.argName(i) == "MQTTPort") config.MQTTPort = server.arg(i).toInt();
      if (server.argName(i) == "HeartbeatTopic") config.HeartbeatTopic = urldecode(server.arg(i));
      if (server.argName(i) == "HeartbeatEvery") config.HeartbeatEvery = server.arg(i).toInt();
      if (server.argName(i) == "SleepTopic") config.SleepTopic = urldecode(server.arg(i));
      if (server.argName(i) == "SleepDuration") config.SleepDuration = server.arg(i).toInt();
			if (server.argName(i) == "SleepAfterVolts") config.SleepAfterVolts = true;
      if (server.argName(i) == "SleepAfterVoltsDuration") config.SleepAfterVoltsDuration = server.arg(i).toInt();
			if (server.argName(i) == "SleepIfNotConnected") config.SleepIfNotConnected = true;
      if (server.argName(i) == "SNCDuration") config.SNCDuration = server.arg(i).toInt();
      if (server.argName(i) == "voltcalib") config.voltcalib = server.arg(i).toInt();
      if (server.argName(i) == "VoltEmailThreshold") config.VoltEmailThreshold = server.arg(i).toInt();
      if (server.argName(i) == "EmailAddress") config.EmailAddress = urldecode(server.arg(i));
		}
		WriteConfig();
		firstStart = true;
	}
	server.send_P ( 200, "text/html", PAGE_AdminGeneralSettings ); 
	Serial.println(__FUNCTION__); 
	
	
}

void send_general_configuration_values_html()
{
	String values ="";
	values += "devicename|" +  (String)  config.DeviceName +  "|input\n";
  values += "OTApwd|" +  (String)  config.OTApwd +  "|input\n";
  values += "MQTTServer|" +  (String)  config.MQTTServer +  "|input\n";
  values += "MQTTPort|" +  (String)  config.MQTTPort +  "|input\n";
  values += "HeartbeatTopic|" +  (String)  config.HeartbeatTopic +  "|input\n";
  values += "HeartbeatEvery|" +  (String)  config.HeartbeatEvery +  "|input\n";
  values += "SleepTopic|" +  (String)  config.SleepTopic +  "|input\n";
  values += "SleepDuration|" +  (String)  config.SleepDuration +  "|input\n";
	values += "SleepAfterVolts|" +  (String) (config.SleepAfterVolts ? "checked" : "") + "|chk\n";
  values += "SleepAfterVoltsDuration|" + (String) config.SleepAfterVoltsDuration + "|input\n";
	values += "SleepIfNotConnected|" +  (String) (config.SleepIfNotConnected ? "checked" : "") + "|chk\n";
  values += "voltcalib|" + (String) config.voltcalib + "|input\n";
  values += "VoltEmailThreshold|" + (String) config.VoltEmailThreshold + "|input\n";
  values += "EmailAddress|" + (String) config.EmailAddress + "|input\n";
	server.send ( 200, "text/plain", values);
	Serial.println(__FUNCTION__); 
  AdminTimeOutCounter=0;
}
