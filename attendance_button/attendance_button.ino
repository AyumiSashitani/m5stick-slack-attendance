#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

// ボタンピンは機種差あり。まずこの2つで試す想定。
// もし反応せんかったら後述の「ボタンが効かない」へ。
#ifndef BTN_A
#define BTN_A 37
#endif
#ifndef BTN_B
#define BTN_B 39
#endif

static unsigned long lastSendMs = 0;

bool postToSlack(const String& text) {
  if (WiFi.status() != WL_CONNECTED) return false;

  HTTPClient http;
  http.begin(SLACK_WEBHOOK_URL);
  http.addHeader("Content-Type", "application/json");

  // Slackに投げるJSON
  String payload = String("{\"text\":\"") + text + "\"}";
  int code = http.POST(payload);
  http.end();

  return (code >= 200 && code < 300);
}

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(200);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);

  connectWiFi();
  postToSlack(":electric_plug: M5Stick 起動したで");
}

void loop() {
  // 二重送信防止（1.5秒）
  if (millis() - lastSendMs < 1500) return;

  if (digitalRead(BTN_A) == LOW) {
    bool ok = postToSlack(":sunny: 出勤したで");
    lastSendMs = millis();
    Serial.println(ok ? "sent: clock-in" : "failed: clock-in");
  }

  if (digitalRead(BTN_B) == LOW) {
    bool ok = postToSlack(":crescent_moon: 退勤したで");
    lastSendMs = millis();
    Serial.println(ok ? "sent: clock-out" : "failed: clock-out");
  }

  delay(50);
}
