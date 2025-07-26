#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials
const char* ssid = "eduroam";
const char* password = "Bravan157.";

// Create a web server on port 80
WebServer server(80);

// Pin to control the transistor (which switches the LEDs)
const int ledControlPin = 23; //(D23)

void handleRoot() {
  String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <title>BRAVAN Home Lighting</title>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        body { font-family: Arial; text-align: center; padding: 20px; background: #f0f0f0; }
        h1 { color: #333; }
        .btn { padding: 15px 30px; font-size: 18px; margin: 10px; cursor: pointer; border: none; border-radius: 5px; }
        .on { background-color: #4CAF50; color: white; }
        .off { background-color: #f44336; color: white; }
      </style>
    </head>
    <body>
      <h1>Engineering Team 2 Lighting Control</h1>
      <button class="btn on" onclick="toggleLED('on')">Turn ON</button>
      <button class="btn off" onclick="toggleLED('off')">Turn OFF</button>

      <script>
        function toggleLED(state) {
          fetch('/led?state=' + state)
            .then(response => response.text())
            .then(data => console.log(data));
        }
      </script>
    </body>
    </html>
  )rawliteral";

  server.send(200, "text/html", html);
}

void handleLEDControl() {
  String state = server.arg("state");
  if (state == "on") {
    digitalWrite(ledControlPin, HIGH);
    server.send(200, "text/plain", "LEDs turned ON");
  } else if (state == "off") {
    digitalWrite(ledControlPin, LOW);
    server.send(200, "text/plain", "LEDs turned OFF");
  } else {
    server.send(400, "text/plain", "Invalid command");
  }
}

void setup() {
  Serial.begin(115200);

  // Configure the LED control pin
  pinMode(ledControlPin, OUTPUT);
  digitalWrite(ledControlPin, LOW); // Initially OFF

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Route handling
  server.on("/", handleRoot);
  server.on("/led", handleLEDControl);

  // Start the server
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
