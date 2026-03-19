#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "Your WiFi SSID";
const char* password = "Your WiFi Password";
const char* DeploymentID = "Paste Deployment ID";

bool status = false; 
int D0 = 16; 
int D1 = 5;  
int LDR = 4; // Pin D2

void ConnectToWifi() {
  Serial.print("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nIIOT node Online");
}

void sendDataToCloud(String statusLabel, int sensorVal) {
  int retryCount = 0;
  int maxRetries = 3;
  bool success = false;

  Serial.println(">>> Starting Cloud Sync...");

  while (retryCount < maxRetries && !success) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;
  
    http.setTimeout(5000); // Increased for stability
    String Url = "Paste the URL" + String(DeploymentID) + "/exec?status=" + statusLabel + "&val=" + String(sensorVal);
    
    http.setReuse(false); 
    if (http.begin(client, Url)) {
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
      int httpCode = http.GET();
      
      if (httpCode > 0) {
        Serial.println("Cloud Sync Successful: " + statusLabel);
        success = true; // CRITICAL: Stop the loop on success
      } else {
        Serial.println("Cloud Sync Failed. Code: " + String(httpCode));
        retryCount++; // Increment retry count
        delay(1000);  // Power recovery delay
      }
      http.end();
    }
    client.stop(); 
  } // BRACKET WAS MISSING HERE
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n--- SYSTEM BOOTING ---");
  
  ConnectToWifi();

  pinMode(A0, INPUT);
  pinMode(LDR, INPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  
  digitalWrite(D0, HIGH); 
  digitalWrite(D1, HIGH);
  
  Serial.println("Inventory System Ready.");
}

void loop() {
  int val = analogRead(A0);
  int itemPresent = digitalRead(LDR); // HIGH typically means light is blocked (Dark)

  // 1. PLACED LOGIC: Piezo spike AND LDR confirms item is there (LOW or HIGH depending on module)
  // Check if your LDR module is LOW when covered or HIGH when covered. 
  // Most digital LDR modules are LOW when light is detected and HIGH when blocked.
  if (val > 40 && status == false && itemPresent == LOW) { 
    Serial.println("Motion Detected: PLACING (Val: " + String(val) + ")");
    digitalWrite(D0, LOW);  // Red ON
    digitalWrite(D1, HIGH); 
    status = true;
    delay(1000);

    sendDataToCloud("Placed", val);
    
    delay(2000); 
  }

  // 2. PICKED LOGIC: Small jolt AND LDR confirms item is gone
  else if (val > 4 && status == true && itemPresent == HIGH) {
    Serial.println("Motion Detected: PICKING (Val: " + String(val) + ")");
    digitalWrite(D1, LOW);  // Green ON
    digitalWrite(D0, HIGH); 
    status = false;
    delay(1000);

    sendDataToCloud("Picked", val);

    delay(2000);
  }
}