# セットアップガイド

## 1. Slack Incoming Webhook の作成

1. [Slack API](https://api.slack.com/apps) にアクセス
2. **Create New App** → **From scratch**
3. App名とワークスペースを選択 → **Create App**
4. 左メニュー → **Incoming Webhooks** → **On**
5. **Add New Webhook to Workspace** → チャンネル選択 → **許可**
6. Webhook URL をコピー

---

## 2. SlackユーザーIDの確認

1. Slackで自分のプロフィールを開く
2. **︙（その他）** → **メンバーIDをコピー**

※ `U0123456789` のような形式

---

## 3. config.h の作成（重要：コミット禁止）

`attendance_button/config.example.h` をコピーして `attendance_button/config.h` を作成。

```bash
cp attendance_button/config.example.h attendance_button/config.h
```

`attendance_button/config.h` を編集：

```cpp
#pragma once

// Wi-Fi（2.4GHzのみ対応）
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"

// Slack Incoming Webhook URL（絶対に公開しない）
#define SLACK_WEBHOOK_URL "https://hooks.slack.com/services/XXX/YYY/ZZZ"

// SlackユーザーID（プロフィールからコピー）
#define SLACK_USER_ID "UXXXXXXXXXX"
```

---

## 4. Arduino IDE セットアップ

### ESP32ボードを追加

1. [Arduino IDE 2.x](https://www.arduino.cc/en/software) をインストール
2. **Settings（Preferences）** → **Additional boards manager URLs** に追加：

   ```text
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```

3. **Boards Manager** で `esp32` を検索 → **Install**

### M5StickCPlus2ライブラリをインストール

1. **Tools** → **Manage Libraries...**
2. `M5StickCPlus2` を検索 → **Install**

---

## 5. ビルド・書き込み

1. `attendance_button/attendance_button.ino` を開く
2. M5StickをUSBで接続
3. **Tools** メニューで設定：
   * **Board**：`ESP32 Dev Module`
   * **Port**：接続したシリアルポートを選択
   * **Upload Speed**：`115200`（重要）
4. **Upload**（→ボタン）で書き込み

---

## 6. 動作確認

| 操作 | Slackメッセージ |
|------|----------------|
| 起動 | `:electric_plug: @名前 M5Stick 起動しました` |
| Aボタン（正面） | `:sunny: @名前 出勤しました（09:15:30）` |
| Bボタン（側面） | `:crescent_moon: @名前 退勤しました（18:30:45）` |
