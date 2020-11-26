// シミュレーション条件を格納する構造体
typedef struct condition
{
  const int width; // 見えている範囲の幅
  const int height; // 見えている範囲の高さ
  const double G; // 重力定数
  const double dt; // シミュレーションの時間幅
} Condition;

// 個々の物体を表す構造体
typedef struct object
{
  double m;
  double y;
  double vy;
} Object;

// 授業で用意した関数のプロトタイプ宣言

void plot_objects(Object objs[], const size_t numobj, const double t, const Condition cond);
void update_velocities(Object objs[], const size_t numobj, const Condition cond);
void update_positions(Object objs[], const size_t numobj, const Condition cond);

// To do: 以下に上記と同じ引数で実行される my_* を作成
// 実装できたらmain関数で上記と入れ替えていく
// my_plot_objects(), my_update_velocities(), my_update_positions() の3つ 
