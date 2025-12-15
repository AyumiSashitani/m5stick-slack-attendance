#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>
#include "config.h"

static unsigned long lastSendMs = 0;

// NTP設定（日本時間）
const char* ntpServer = "ntp.nict.jp";
const long gmtOffset_sec = 9 * 3600;  // JST = UTC+9
const int daylightOffset_sec = 0;

// 現在時刻を取得（HH:MM:SS形式）
String getTimeString() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "??:??:??";
  }
  char buf[9];
  sprintf(buf, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  return String(buf);
}

// 画面に状態を表示
void showStatus(const char* line1, const char* line2 = "", uint16_t color = WHITE) {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(color);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 30);
  M5.Lcd.println(line1);
  M5.Lcd.setCursor(10, 60);
  M5.Lcd.println(line2);
}

bool postToSlack(const String& text) {
  if (WiFi.status() != WL_CONNECTED) {
    showStatus("WiFi Error", "Not connected", RED);
    return false;
  }

  HTTPClient http;
  http.begin(SLACK_WEBHOOK_URL);
  http.addHeader("Content-Type", "application/json");

  String payload = String("{\"text\":\"") + text + "\"}";
  int code = http.POST(payload);
  http.end();

  return (code >= 200 && code < 300);
}

void connectWiFi() {
  showStatus("WiFi", "Connecting...", YELLOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(200);
  }

  if (WiFi.status() == WL_CONNECTED) {
    showStatus("WiFi", "Connected!", GREEN);
  } else {
    showStatus("WiFi", "Failed!", RED);
  }
  delay(1000);
}

void syncTime() {
  showStatus("Time", "Syncing...", YELLOW);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  struct tm timeinfo;
  if (getLocalTime(&timeinfo)) {
    showStatus("Time", "Synced!", GREEN);
  } else {
    showStatus("Time", "Failed!", RED);
  }
  delay(1000);
}

void showReady() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 20);
  M5.Lcd.println("Ready!");
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(10, 60);
  M5.Lcd.println("BtnA: Clock In");
  M5.Lcd.setCursor(10, 80);
  M5.Lcd.println("BtnB: Clock Out");
}

void setup() {
  M5.begin();
  Serial.begin(115200);

  M5.Lcd.setRotation(1);
  M5.Lcd.fillScreen(BLACK);

  connectWiFi();
  syncTime();

  // --- 起動時のSlack通知（不要なら以下をコメントアウト） ---
  showStatus("Slack", "Sending...", YELLOW);
  String msg = String(":electric_plug: <@") + SLACK_USER_ID + "> M5Stick 起動しました";
  bool ok = postToSlack(msg);
  if (ok) {
    showStatus("Slack", "Sent!", GREEN);
  } else {
    showStatus("Slack", "Failed!", RED);
  }
  delay(1500);
  // --- ここまで ---

  showReady();
}

void loop() {
  M5.update();

  // 二重送信防止（1.5秒）
  if (millis() - lastSendMs < 1500) return;

  // Aボタン（正面）: 出勤
  if (M5.BtnA.wasPressed()) {
    showStatus("Clock In", "Sending...", YELLOW);
    String timeStr = getTimeString();
    String msg = String(":sunny: <@") + SLACK_USER_ID + "> 出勤しました（" + timeStr + "）";
    bool ok = postToSlack(msg);
    lastSendMs = millis();

    if (ok) {
      showStatus("Clock In", "Sent!", GREEN);
      Serial.println("sent: clock-in");
    } else {
      showStatus("Clock In", "Failed!", RED);
      Serial.println("failed: clock-in");
    }
    delay(1500);
    showReady();
  }

  // Bボタン（側面）: 退勤
  if (M5.BtnB.wasPressed()) {
    showStatus("Clock Out", "Sending...", YELLOW);
    String timeStr = getTimeString();
    String msg = String(":crescent_moon: <@") + SLACK_USER_ID + "> 退勤しました（" + timeStr + "）";
    bool ok = postToSlack(msg);
    lastSendMs = millis();

    if (ok) {
      showStatus("Clock Out", "Sent!", GREEN);
      Serial.println("sent: clock-out");
    } else {
      showStatus("Clock Out", "Failed!", RED);
      Serial.println("failed: clock-out");
    }
    delay(1500);
    showReady();
  }

  delay(10);
}
