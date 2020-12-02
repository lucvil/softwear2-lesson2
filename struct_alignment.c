#include <stdio.h>

struct student
{
  int id; //4 
  char name[100]; //100
  int age;//4             -> 124  128
  double height;//8
  double weight;//8
};

struct tagged_student1
{
  int id; //4
  char name[100]; //100
  int age;//4
  double height;//8 -> 125   136
  double weight;//8
  char tag;//1
};

struct tagged_student2
{
  char tag;//1
  int id; //4
  char name[100]; //100
  int age;    //4         ->125    128
  double height;//8
  double weight;//8
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
  printf("point of s_end: %p\n",s_end);
  printf("point of s_end.id: %p\n",s_end.height);
  printf("point of s3: %p\n",s3);
  printf("point of s2: %p\n",s2);
  printf("point of s1: %p\n",s1);
  printf("point of s_begin: %p\n",s_begin);

  /* 以下には各構造体のサイズをsizeof演算子で計算し、表示する */
  /* printf 表示には%ld を用いる*/

  printf("size of s_end: %ld\n",sizeof(struct tagged_student2));
  printf("size of s3: %ld\n",sizeof(struct tagged_student2));
  printf("size of s2: %ld\n",sizeof(struct tagged_student1));
  printf("size of s1: %ld\n",sizeof(struct student));
  printf("size of s_begin: %ld\n",sizeof(struct student));
  
  return 0;
}
