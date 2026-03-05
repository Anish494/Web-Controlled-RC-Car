#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Motor control pins
int enA = D1;
int in1 = D2;
int in2 = D3;

int in3 = D4;
int in4 = D5;
int enB = D6;

const int buzPin = D7;

#define trigPin D8
#define echoPin D0


int SPEED = 1023;
String command = "";
String currentState = "S";  // default is Stop

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);

  pinMode(buzPin, OUTPUT); 
  digitalWrite(buzPin, LOW);
  pinMode(enA, OUTPUT); 
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT);

  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


  WiFi.mode(WIFI_AP);
  WiFi.softAP("WiFiCar");
  Serial.println("IP: " + WiFi.softAPIP().toString());

  server.on("/", HTTP_handleRoot);
  server.on("/finish", handleFinish);

  server.begin();
}



void loop() {
  server.handleClient();
  command = server.arg("State");

  if (command == "F") Forward();
  else if (command == "B") Backward();
  else if (command == "L") TurnLeft();
  else if (command == "R") TurnRight();
  else if (command == "S") Stop();
  else if (command == "V") BeepHorn();

  long distance = getDistanceCM();
  if (distance > 0 && distance <= 10) {
    BeepHorn();
    delay(1000);  // wait 1 second after horn
  }

}

void Forward() {
  currentState = "F";
  analogWrite(enA, SPEED);
  analogWrite(enB, SPEED);
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
}

void Backward() {
  currentState = "B";
  analogWrite(enA, SPEED);
  analogWrite(enB, SPEED);
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH);
}

void TurnLeft() {
  currentState = "L";
  analogWrite(enA, SPEED);
  analogWrite(enB, SPEED);
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH);
}

void TurnRight() {
  currentState = "R";
  analogWrite(enA, SPEED);
  analogWrite(enB, SPEED);
  digitalWrite(in1, LOW); 
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); 
  digitalWrite(in4, LOW);
}

void Stop() {
  currentState = "S";
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW);
}

void BeepHorn() {
  digitalWrite(buzPin, HIGH);
  delay(150);
  digitalWrite(buzPin, LOW);
}

void handleFinish() {
  String html = "<html><head><title>Farewell</title>";
  html += "<style>body { font-family: Arial; text-align: center; padding-top: 50px; }";
  html += "h1 { font-size: 32px; color: #2c3e50; }";
  html += "p { font-size: 20px; }</style></head><body>";
  html += "<h1>Thank You Sir !</h1>";
  html += "<p>This was a small farewell treat for you through our WiFi-controlled car project.</p>";
  html += "<p>We truly appreciate your support and guidance.</p>";
  html += "<p>Wishing you all the best ahead!</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}


void HTTP_handleRoot() {
  String html = "<html><head><title>WiFi Car</title>";
  html += "<style>body{text-align:center;font-family:Arial;}button{padding:12px 30px;margin:8px;font-size:18px;}</style></head><body>";
  html += "<h1>WiFi Car Control</h1>";
  html += "<a href='?State=F'><button>Forward</button></a><br>";
  html += "<a href='?State=L'><button>Left</button></a>";
  html += "<a href='?State=S'><button>Stop</button></a>";
  html += "<a href='?State=R'><button>Right</button></a><br>";
  html += "<a href='?State=B'><button>Backward</button></a><br><br>";
  html += "<a href=\"?State=V\"><button>Horn</button></a><br><br>";
  html += "<a href=\"/finish\"><button style='background-color:#4CAF50;color:white;'>FINISH</button></a>";


  html += "</body></html>";

  server.send(200, "text/html", html);
}


long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

