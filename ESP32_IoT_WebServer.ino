// Load Wi-Fi library
#include <WiFi.h>

// Gantikan Dengan SSID dan Password yang diinginkan
const char* ssid     = "ESP32-Access-Point";
const char* password = "123456789";

// Deklarasikan server HTTP
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  
  // Mengkonfigurasi access point
  Serial.print("Setting AP (Access Point)…");
  // Kosongkan password bila ingin open access
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  //jalankan server http
  server.begin();
}
void loop(){
  //cek status klien
  WiFiClient client = server.available();
  if (client) {                           
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected()) {            
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);  
        if (c == '\n') {                    
      // if c adalah baris baru
          // if masih kosong currentlinenya, 2 kali baris baru
          // itu akhir dari response
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
      // HTTP response diawali dengan blank line
            client.println();
            // Tampilkan HTTP
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.println("<h2>Selamat Datang</h2>");            
            client.println("</body></html>");            
            // HTTP response diakhiri dengan blank line
            client.println();
            // keluar dari while loop
            break;
          } else { // kalau dapat newline, clear line saat ini
            currentLine = "";
          }
        } else if (c != '\r') {  
      // kalau dapat CR, tambahkan ke currentline
          currentLine += c;      
        }
      }
    }
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
