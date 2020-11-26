// 構造体の初期化についてまとめました

#include <stdio.h>

typedef struct point
{
  double x;
  double y;
} Point;

int main(int argc, char **argv)
{
  // 古いタイプの初期化
  Point p1 = { 1.0 , 2.0};

  printf("p1: (%3.1f %3.1f)\n",p1.x, p1.y);

  // 初期化指示子を用いた場合（こちらが可読性が高くおすすめ）
  Point p2 = {.x = 3.0, .y = 4.0};

  printf("p2: (%3.1f %3.1f)\n",p2.x, p2.y);
  // 複合リテラル: C99 から。
  // 構造体定数を(type-name){ initializer } で作成できる
  Point p3;

  // 一度宣言したあとは、//p3 = { .x = 5.0, .y = 6.0}; だとエラー
  // (typename){} を使ってリテラルを代入
  p3 = (Point){ .x = 5.0, .y = 6.0};

  printf("p3: (%3.1f %3.1f)\n",p3.x, p3.y);

  // p3 に p2 を代入
  p3 = p2;

  printf("p3: (%3.1f %3.1f)\n",p3.x, p3.y);

  // 通常の配列（可変長でない）は、以下で初期化できる
  Point ps1[2] = { { .x = 1, .y = 2}, {.x = 3, .y = 4} };
  // **静的配列**の場合は、以下で配列サイズを取得可能
  size_t num_ps = sizeof ps1 / sizeof(Point);

  for (int i = 0 ; i < num_ps ; i ++)
    printf("ps1[%d]: (%3.1f %3.1f)\n", i,ps1[i].x, ps1[i].y);
  
  
  // 可変長配列の場合は、配列形式初期化が使えない
  size_t num = 2;
  // Point ps2[num] = {{.x=1,.y=1},{.x=2,.y=2}}; // これはダメ
  Point ps2[num];
  ps2[0] = (Point){ .x = 1, .y = 2};
  ps2[1] = (Point){ .x = 3, .y = 4};

  for (int i = 0 ; i < num ; i ++)
    printf("ps2[%d]: (%3.1f %3.1f)\n", i,ps1[i].x, ps1[i].y);
  
}
