# セットアップガイド

## 1. Slack Incoming Webhook の作成

1. Slackで「Create an App（From scratch）」
2. **Incoming Webhooks** を ON
3. **Add New Webhook to Workspace**
4. 投稿先チャンネルを選択
5. Webhook URL を控える（例：`https://hooks.slack.com/services/...`）

---

## 2. config.h の作成（重要：コミット禁止）

`attendance_button/config.example.h` をコピーして `attendance_button/config.h` を作り、値を自分の環境に合わせて更新。

```bash
cp attendance_button/config.example.h attendance_button/config.h
```

`attendance_button/config.h`

```cpp
#pragma once

// Wi-Fi
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"

// Slack Incoming Webhook URL（絶対に公開しない）
#define SLACK_WEBHOOK_URL "https://hooks.slack.com/services/XXX/YYY/ZZZ"
```

---

## 3. Arduino IDE セットアップ

1. [Arduino IDE 2.x](https://www.arduino.cc/en/software) をインストール
2. **Settings（Preferences）** → **Additional boards manager URLs** に以下を追加：

   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```

3. **Boards Manager** で `esp32` を検索してインストール

---

## 4. ビルド・書き込み

1. `attendance_button/attendance_button.ino` を開く
2. M5StickをUSBで接続
3. **Tools** メニューで設定：
   * **Board**：`ESP32 Dev Module`（または M5StickC / M5StickC Plus があれば選択）
   * **Port**：接続したシリアルポートを選択
4. **Upload**（→ボタン）で書き込み
5. 成功すると、Slackに `:electric_plug: M5Stick 起動したで` が届く
