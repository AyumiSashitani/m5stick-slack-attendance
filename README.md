# M5Stick Slack 出退勤ボタン（Attendance Button）

M5Stick（ESP32）で **ボタンを押すだけでSlackに出勤/退勤を投稿**するミニプロジェクト。

* **Aボタン**：出勤メッセージ
* **Bボタン**：退勤メッセージ
* Slack連携は **Incoming Webhook**（最小構成 / OAuth不要）

> ⚠️ Webhook URL は「投稿権限そのもの」。**絶対に公開リポジトリへコミットしないこと**。

---

## できること

* M5Stick起動時にSlackへ「起動した」通知
* A/Bボタン押下でSlackへ投稿
* 二重送信の簡易防止（短いクールダウン）

---

## 必要なもの

* M5Stick（ESP32系：M5StickC / M5StickC Plus など）
* Wi-Fi環境（2.4GHz推奨）
* Slackワークスペース（Incoming Webhook作成権限）
* 開発環境：Claude Code（推奨） or Arduino IDE

---

## リポジトリ構成

```text
.
├── attendance_button/
│   ├── attendance_button.ino
│   ├── config.example.h
│   └── config.h            # ← gitignore対象（秘密情報）
└── .gitignore
```

---

## セットアップ（Slack）

1. Slackで「Create an App（From scratch）」
2. **Incoming Webhooks** を ON
3. **Add New Webhook to Workspace**
4. 投稿先チャンネルを選択
5. Webhook URL を控える（例：`https://hooks.slack.com/services/...`）

---

## セットアップ（コード）

### 1) `config.h` を作成（重要：コミット禁止）

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

## 開発環境セットアップ

### Arduino IDE

1. [Arduino IDE 2.x](https://www.arduino.cc/en/software) をインストール
2. **Settings（Preferences）** → **Additional boards manager URLs** に以下を追加：

   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```

3. **Boards Manager** で `esp32` を検索してインストール

---

## ビルド・書き込み

### Arduino IDE での手順

1. `attendance_button/attendance_button.ino` を開く
2. M5StickをUSBで接続
3. **Tools** メニューで設定：
   * **Board**：`ESP32 Dev Module`（または M5StickC / M5StickC Plus があれば選択）
   * **Port**：接続したシリアルポートを選択
4. **Upload**（→ボタン）で書き込み
5. 成功すると、Slackに `:electric_plug: M5Stick 起動したで` が届く

---

## トラブルシューティング

### Slackに届かない

* Webhook URLが正しいか確認
* Wi-Fiに繋がっているか（Serial Monitorでログ確認）
* Webhook作成時の投稿先チャンネルが正しいか

### ボタンが反応しない

M5Stickの機種によってピン番号が異なる場合がある。

| 機種 | BTN_A | BTN_B |
|------|-------|-------|
| M5StickC | 37 | 39 |
| M5StickC Plus | 37 | 39 |

反応しない場合は `config.h` でピンを上書き：

```cpp
#define BTN_A 37
#define BTN_B 39
```

### Serial Monitor でデバッグ

Arduino IDE → **Tools** → **Serial Monitor**（115200 baud）で送信ログを確認できる。

---

## License

MIT
