# ソフトウェア2（第2回）サンプルプログラム

## はじめに
万有引力に基づく物理シミュレーションのためのプログラムです。

## ライブラリの準備
環境に応じてシンボリックリンクを貼ります。

```bash
# (e.g) Macの場合。その他の場合も第一引数を読み替えてください。
ln -s libfall-mac.a libfall.a
ln -s libbounce-mac.a libbounce.a
```
## サンプルプログラムのコンパイルと実行
2つプログラムがあります。それぞれ実行してみましょう。

```bash
# 自由落下のプログラム
gcc -o falling -Wall falling.c -L. -lfall -lm
./falling
```

```bash
# 反射のプログラム
gcc -o bouncing -Wall bouncing.c -L. -lbounce -lm
./bouncing
```