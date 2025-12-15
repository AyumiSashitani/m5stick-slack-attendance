# トラブルシューティング

## Wi-Fiに繋がらない

* **ESP32は2.4GHzのみ対応**（5GHz Wi-Fiは接続不可）
* SSID / パスワードが正しいか確認
* ルーターが2.4GHzと5GHzで別のSSIDになっているか確認

---

## Slackに届かない

* Webhook URLが正しいか確認
* Webhook URLの前後に空白や改行が入っていないか
* Wi-Fiに繋がっているか（Serial Monitorでログ確認）
* Webhook作成時の投稿先チャンネルが正しいか

---

## ボタンが反応しない

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

---

## Serial Monitor でデバッグ

Arduino IDE → **Tools** → **Serial Monitor**（115200 baud）で送信ログを確認できる。

```text
sent: clock-in      ← 送信成功
failed: clock-in    ← 送信失敗（Wi-Fi or Webhook問題）
```
