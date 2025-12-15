# CLAUDE.md

このリポジトリは **M5Stick（ESP32）を使った Slack 出退勤ボタン** のサンプルプロジェクト。
Claude Code を使って **安全・最小構成・Public前提** で開発するためのガイドをまとめている。

---

## 🎯 このプロジェクトの目的

* M5Stick の **物理ボタン** から Slack へ出退勤を通知する
* Incoming Webhook を使った **最小構成の Slack 連携** を示す
* 初学者でも追える **シンプルで壊れにくい実装** を提供する
* Qiita 記事・学習用途で **Public公開できる設計** にする

---

## 🧠 Claude Code に期待すること

Claude Code には以下を重視してほしい。

* **可読性優先**（短く・分かりやすく）
* **魔法っぽい抽象化はしない**（Arduino初心者でも追える）
* **ハードコードを避ける**（秘密情報は必ず `config.h`）
* **変更理由が分かる差分** を出す

---

## 📂 リポジトリ構成ルール

```text
.
├── attendance_button/
│   ├── attendance_button.ino   # メインロジック
│   ├── config.example.h         # 公開用サンプル
│   └── config.h                 # ローカル専用（gitignore）
├── .gitignore
├── README.md
└── CLAUDE.md
```

### 🔒 セキュリティルール（最重要）

* `config.h` は **絶対に commit しない**
* Slack Webhook URL をコード・README・Issue・PRに貼らない
* README には必ず **ダミーURL** を記載する

---

## 🔧 実装方針

### Slack連携

* **Incoming Webhook のみ** を使用
* OAuth / Bot Token / 権限管理は扱わない
* HTTP POST + JSON `{ "text": "..." }` のみ

### デバイス制御

* まずは **画面制御なし**（Slack送信に集中）
* ボタン入力は `INPUT_PULLUP`
* 二重送信防止の簡易クールダウンを入れる

---

## 🧪 開発・変更時のチェックリスト

Claude Code が **新規実装・修正・リファクタ** を行う際は、必ず以下を満たすこと。

### セキュリティ

* [ ] `config.h` に秘密情報（Wi-Fi / Webhook）が集約されている
* [ ] Webhook URL・SSID・パスワードが **README / コード / コメント / Issue** に直接書かれていない
* [ ] `.gitignore` に `attendance_button/config.h` が含まれている

### 可読性・初学者配慮

* [ ] Arduino / ESP32 初学者が上から読んで理解できる
* [ ] 処理の流れが `setup()` → `loop()` で追える
* [ ] 1関数が長くなりすぎていない（目安 20〜30行）

### 挙動・安定性

* [ ] ボタン長押し・連打で **二重送信されない**
* [ ] Wi-Fi未接続時にクラッシュしない
* [ ] Slack送信失敗時でも無限ループにならない

### ドキュメント整合性

* [ ] README の手順と実装が乖離していない
* [ ] 新しい設定項目を追加した場合、`config.example.h` にも反映されている

---

## 📝 コーディングスタイル

* Arduino標準APIを優先（`WiFi.h`, `HTTPClient.h`）
* ライブラリ追加は **理由がある場合のみ**
* 関数は短く（20〜30行目安）
* `bool` 戻り値で成否を返す

---

## 🚀 今後の拡張（Claudeへのヒント）

以下は **段階的に** 追加する想定。いきなり全部はやらない。

1. 1ボタンで出勤/退勤トグル（状態はNVS保存）
2. 投稿メッセージのテンプレ化
3. Wi-Fi切断時の再接続処理
4. 画面表示対応（M5Unified）

---

## 🧑‍💻 想定読者

* Arduino / ESP32 初心者
* IoTに興味があるWeb / モバイルエンジニア
* 「物理ボタン × Slack」を試したい人

Claude Code は **「この人たちが置いていかれないか？」** を常に意識すること。

---

## 📌 補足

* 本プロジェクトは業務用勤怠システムの代替ではない
* あくまで **個人用途・デモ・学習用**
* 勤怠管理の法的要件等は扱わない

---

## 📄 License

MIT License（予定）
