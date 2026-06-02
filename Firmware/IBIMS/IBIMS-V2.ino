#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "Redmi Note 13 5G";
const char* password = "24b695@2006";
const char* DeploymentID = "AKfycbzhHGg7l6Qzm3SLArlyy92WtWsgTO_DOJpBip42DnZ3nVb3clcTAArvqEswfvYB3TgU";

bool status = false; 
int D0 = 16; 
int D1 = 5;  
int LDR = 4; // Pin D2

// --- HEARTBEAT VARIABLES ADDED HERE ---
unsigned long lastHeartbeat = 0;
const unsigned long heartbeatInterval = 3500; // 45 seconds

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
  
    http.setTimeout(5000); 
    String Url = "https://script.google.com/macros/s/" + String(DeploymentID) + "/exec?status=" + statusLabel + "&val=" + String(sensorVal);
    
    http.setReuse(false); 
    if (http.begin(client, Url)) {
      http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
      int httpCode = http.GET();
      
      if (httpCode > 0) {
        Serial.println("Cloud Sync Successful: " + statusLabel);
        success = true; 
        lastHeartbeat = millis(); // Reset heartbeat timer on every successful sync
      } else {
        Serial.println("Cloud Sync Failed. Code: " + String(httpCode));
        retryCount++; 
        delay(1000);  
      }
      http.end();
    }
    client.stop(); 
  } 
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

  Serial.println("System Boot: Syncing Initial State...");
  int initialPresence = digitalRead(LDR);
  // Matches your logic: LOW = Item Present, HIGH = Item Absent
  String bootStatus = (initialPresence == LOW) ? "Placed" : "Picked";
  status = (initialPresence == LOW) ? true : false; 
  sendDataToCloud(bootStatus, 0);
  
  Serial.println("Inventory System Ready.");
}

void loop() {
  int val = analogRead(A0);
  int itemPresent = digitalRead(LDR); 

  // 1. PLACED LOGIC
  if (val > 30 && status == false && itemPresent == LOW) { 
    Serial.println("Motion Detected: PLACING (Val: " + String(val) + ")");
    digitalWrite(D0, LOW);  // Red ON
    digitalWrite(D1, HIGH); 
    status = true;
    delay(1000);
    sendDataToCloud("Placed", val);
    delay(2000); 
  }

  // 2. PICKED LOGIC
  else if (val > 5 && status == true && itemPresent == HIGH) {
    Serial.println("Motion Detected: PICKING (Val: " + String(val) + ")");
    digitalWrite(D1, LOW);  // Green ON
    digitalWrite(D0, HIGH); 
    status = false;
    delay(1000);
    sendDataToCloud("Picked", val);
    delay(2000);
  }

  // --- 3. HEARTBEAT LOGIC ADDED HERE ---
  // If no action happens for 45 seconds, send the current status to keep the twin online
if (millis() - lastHeartbeat > heartbeatInterval) {
    String currentLabel = (status == true) ? "Placed" : "Picked";
    sendDataToCloud(currentLabel, 0); 
    lastHeartbeat = millis();
  }
}