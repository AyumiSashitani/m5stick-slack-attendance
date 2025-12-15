# トラブルシューティング

## Slackに届かない

* Webhook URLが正しいか確認
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
