// Load Wi-Fi library 
#include <WiFi.h> 
// Gantikan Dengan SSID dan Password yang diinginkan 
const char* ssid = "ESP32-Access-Point"; 
const char* password = "123456789"; 
void setup() { 
	Serial.begin(115200); 
	// Mengkonfigurasi access point 	
	Serial.print("Setting AP (Access Point)…"); 
	// Kosongkan password bila ingin open access 
	WiFi.softAP(ssid, password); 
	IPAddress IP = WiFi.softAPIP(); 
	Serial.print("AP IP address: "); 
	Serial.println(IP); 
} 
void loop(){ 
}
