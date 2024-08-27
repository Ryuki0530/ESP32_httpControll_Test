#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "XXX";
const char* password = "XXX";
const int led = 33;
WebServer server(80);

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
}

  Serial.println("Connected");
  Serial.print("IP=");
  Serial.println(WiFi.localIP());
  server.on("/", Index);                       //  IPアドレス直下にアクセスされたときの処理"Index"を定義
  server.on("/CTRL", LampSW);                   //  "IPアドレス/LED"にアクセスされたときの処理"LampSW"を定義
  server.onNotFound(NotFound);                 //  存在しない場所にアクセスされたときの処理"NotFound"を定義
  server.begin();
}

void loop() {
  server.handleClient();
}

void Index() {
  server.send(200, "text/plain", "Hello,work");
}

void NotFound() {
  server.send(200, "text/plain", "Sorry, page was not found in this server.");
}

void LampSW() {
  String LampSwitch;                           //  String型の変数"LampSwitch"を定義
  LampSwitch = "<!DOCTYPE html>";              //  以下しばらく"LampSwitch"内にHTMLを記述していく
  LampSwitch += "<html lang=\"ja\">";
  LampSwitch += "<head>";
  LampSwitch += "<meta charset=\"utf - 8\" />";
  LampSwitch += "<title>ESP32_WebServeSystem</title>";
  LampSwitch += "</head>";
  LampSwitch += "<body>";
  LampSwitch += "<p>ESP32_Http</p>";
  LampSwitch += "<button type=\"button\" >";
  LampSwitch += "<a href=\"/CTRL\" >";
  LampSwitch += "button</a >";
  LampSwitch += "</body>";
  server.send(200, "text/html", LampSwitch);  //  HTMLのテキスト"LampSwitch"を送信
  digitalWrite(led, !digitalRead(led));       //  ledピンの出力を現在と反転
  Serial.println("Switch pushed!");
}