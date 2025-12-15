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
├── docs/
│   ├── SETUP.md
│   └── TROUBLESHOOTING.md
└── .gitignore
```

---

## ドキュメント

* [セットアップガイド](docs/SETUP.md) - Slack設定、開発環境構築、ビルド手順
* [トラブルシューティング](docs/TROUBLESHOOTING.md) - よくある問題と解決方法

---

## License

MIT
