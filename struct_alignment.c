#include <stdio.h>

struct student
{
  int id;
  char name[100];
  int age;
  double height;
  double weight;
};

struct tagged_student1
{
  int id;
  char name[100];
  int age;
  double height;
  double weight;
  char tag;
};

struct tagged_student2
{
  char tag;
  int id;
  char name[100];
  int age;
  double height;
  double weight;
};

int main (int argc, char**argv)
{
  struct student s_begin;
  struct student s1;
  struct tagged_student1 s2;
  struct tagged_student2 s3;
  struct tagged_student2 s_end;

  /* 以下に各構造体の中身のポインタを表示するプログラムを書く */
  /* printf で %p フォーマットを指定する*/
  /* 逆順に表示（send, s3, s2, s1, sbegin の順）*/

  // do_something!!

  /* 以下には各構造体のサイズをsizeof演算子で計算し、表示する */
  /* printf 表示には%ld を用いる*/

  // do_something!!
  
  return 0;
}
