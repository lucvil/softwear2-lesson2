#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
//#include "physics2.h"

// シミュレーション条件を格納する構造体
// 反発係数CORを追加
typedef struct condition
{
  const int width; // 見えている範囲の幅
  const int height; // 見えている範囲の高さ
  const double G; // 重力定数
  const double dt; // シミュレーションの時間幅
  const double corx;
  const double cory; // 壁の反発係数
} Condition;

// 個々の物体を表す構造体
typedef struct object
{
  double m;
  double x;
  double y;
  double prev_x;
  double prev_y; // 壁からの反発に使用
  double vx;
  double vy;
} Object;

void my_plot_objects(Object objs[], const size_t numobj, const double t, const Condition cond);
void my_update_velocities(Object objs[], const size_t numobj, const Condition cond);
void my_update_positions(Object objs[], const size_t numobj, const Condition cond);
void my_bounce(Object objs[], const size_t numobj, const Condition cond);


int main(int argc, char **argv){
  const Condition cond = {
		    .width  = 75,
		    .height = 40,
		    .G = 1.0,
		    .dt = 1.0,
        .corx  = 0.5,
		    .cory = 0.8
  };
  
  size_t objnum = 3;
  Object objects[objnum];

  // objects[1] は巨大な物体を画面外に... 地球のようなものを想定
  objects[0] = (Object){ .m = 100.0, .x = 10.0, .y = -19.9, .vx = 0.5, .vy = 0.2};
  objects[1] = (Object){ .m = 100000.0, .x = 20.0, .y =  1000.0, .vx = 0.0, .vy = 0.0};
  objects[2] = (Object){ .m = 100.0, .x = 30.0, .y = -10.9, .vx = 0.7, .vy = 0.6};

  // シミュレーション. ループは整数で回しつつ、実数時間も更新する
  const double stop_time = 400;
  double t = 0;
  printf("\n");
  my_plot_objects(objects, objnum, t, cond);
  for (int i = 0 ; t <= stop_time ; i++){
    t = i * cond.dt;
    my_update_velocities(objects, objnum, cond);
    my_update_positions(objects, objnum, cond);
    my_bounce(objects, objnum, cond);
    
    // 表示の座標系は width/2, height/2 のピクセル位置が原点となるようにする
    my_plot_objects(objects, objnum, t, cond);
    
    usleep(200 * 1000); // 200 x 1000us = 200 ms ずつ停止
    printf("\e[%dA", cond.height+3+(int)objnum);// 壁とパラメータ表示分で3行
  }
  return EXIT_SUCCESS;
}

// 実習: 以下に my_ で始まる関数を実装する
// 最終的に phisics2.h 内の事前に用意された関数プロトタイプをコメントアウト

//枠及び物体のプロット
void my_plot_objects(Object objs[], const size_t numobj, const double t, const Condition cond){
  //一番上の壁
  printf("+");
  for(int x = 0; x < cond.width; x++){
    printf("-");
  }
  printf("+\n");

  //中
  //xが横軸yが縦軸
  int y0 = cond.height/2 ;
  int x0 = cond.width/2 ;
  int zahyou[numobj][2];
  for(int i = 0; i < numobj; i++){
      zahyou[i][0] = objs[i].x;
      zahyou[i][1] = objs[i].y;
  }
  for(int j = 0; j < cond.height; j++){
    printf("|");
    for(int i = 0; i < cond.width; i++){
      int check = 0;
      for( int k = 0; k < numobj;k++){
        if( i == (int)(zahyou[k][0] + x0) && j == (int)(zahyou[k][1] + y0) ){
          printf("\e[%dmo\e[0m",k + 31);
          //printf("%d",k);
          check = 1;
          break;
        }
      }
      if(check == 0){
        printf(" ");
      }
    }
    printf("|\n");
  }

  //下の壁
  printf("+");
  for(int y = 0; y < cond.width; y++){
    printf("-");
  }
  printf("+\n");

  //説明文
  printf(" t = %6.1f\n",t);
  for(int i = 0; i < numobj;i++){
      printf(" objs[%d].x = %8.2f, objs[%d].y = %8.2f\n",i,objs[i].x,i,objs[i].y);
  } 
}

//速度を変更する関数
void my_update_velocities(Object objs[], const size_t numobj, const Condition cond){
  //加速度の決定
  double a[numobj][2];
  for( int n = 0; n < numobj; n++){
    a[n][0] = 0;
    a[n][1] = 0;
  }
  for(int n = 0; n < numobj; n++){
    for( int m = 0; m < numobj; m++){//重力の発生源
      if( n != m){
        double distance_zettaiti =sqrt(pow((objs[m].y - objs[n].y),2) +pow((objs[m].x - objs[n].x),2));
        a[n][0] += cond.G * objs[m].m * (objs[m].x - objs[n].x) / pow(distance_zettaiti, 3);
        a[n][1] += cond.G * objs[m].m * (objs[m].y - objs[n].y) / pow(distance_zettaiti, 3);
      }
    }
  }

  //速度の変更
  for(int n = 0; n < numobj; n++){
    objs[n].vx += a[n][0] * cond.dt;
    objs[n].vy += a[n][1] * cond.dt;
  }

}

//位置を変更する関数
void my_update_positions(Object objs[], const size_t numobj, const Condition cond){
  for (int n = 0; n < numobj; n++){
    objs[n].prev_x = objs[n].x;
    objs[n].x += objs[n].vx * cond.dt;
    objs[n].prev_y = objs[n].y;
    objs[n].y += objs[n].vy * cond.dt;
  }
}

//バウンドさせる関数
void my_bounce(Object objs[], const size_t numobj, const Condition cond){
  //上と下の上限を設定
  int y_up_boarder ;
  int y_down_boarder;
  if(cond.height % 2 ==1){
    y_up_boarder =  1 + (cond.height / 2);
    y_down_boarder = -1 * cond.height / 2;
  }else if(cond.height % 2 == 0){
    y_up_boarder = cond.height / 2 ;
    y_down_boarder = -1 * cond.height / 2;
  }

  int x_up_boarder ;
  int x_down_boarder;
  if(cond.width % 2 ==1){
    x_up_boarder =  1 + (cond.width / 2);
    x_down_boarder = -1 * cond.width / 2;
  }else if(cond.width % 2 == 0){
    x_up_boarder = cond.width / 2 ;
    x_down_boarder = -1 * cond.width / 2;
  }
  
  int check = 0;
  for(int i = 0; i < numobj; i++){
    if((objs[i].y <= y_down_boarder && objs[i].prev_y > y_down_boarder) || (objs[i].y >= y_up_boarder && objs[i].prev_y < y_up_boarder) || (objs[i].x <= x_down_boarder && objs[i].prev_x > x_down_boarder) || (objs[i].x >= x_up_boarder && objs[i].prev_x < x_up_boarder)){
      check = 1;
    }
  }


  while(check == 1){
    check = 0;
    for(int i = 0; i < numobj; i++){
      if(objs[i].y <= y_down_boarder && objs[i].prev_y > y_down_boarder){
        double dis_ywall = y_down_boarder - objs[i].y;  
        objs[i].y = y_down_boarder + cond.cory * dis_ywall;    
        objs[i].vy = -1 * objs[i].vy * cond.cory;
      }else if(objs[i].y >= y_up_boarder && objs[i].prev_y < y_up_boarder){
        double dis_ywall = objs[i].y - y_up_boarder;
        objs[i].y = y_up_boarder - dis_ywall * cond.cory;
        objs[i].vy = -1 * objs[i].vy * cond.cory;
      }
    }

    for(int i = 0; i < numobj; i++){
      if(objs[i].x <= x_down_boarder && objs[i].prev_x > x_down_boarder){
        double dis_xwall = x_down_boarder - objs[i].x;  
        objs[i].x = x_down_boarder + cond.corx * dis_xwall;    
        objs[i].vx = -1 * objs[i].vx * cond.corx;
      }else if(objs[i].x >= x_up_boarder && objs[i].prev_x < x_up_boarder){
        double dis_xwall = objs[i].x - x_up_boarder;
        objs[i].x = x_up_boarder - dis_xwall * cond.corx;
        objs[i].vx = -1 * objs[i].vx * cond.corx;
      }
    } 
    for(int i = 0; i < numobj; i++){
      if((objs[i].y <= y_down_boarder && objs[i].prev_y > y_down_boarder) || (objs[i].y >= y_up_boarder && objs[i].prev_y < y_up_boarder) || (objs[i].x <= x_down_boarder && objs[i].prev_x > x_down_boarder) || (objs[i].x >= x_up_boarder && objs[i].prev_x < x_up_boarder)){
        check = 1;
      }
    }  
  }
}