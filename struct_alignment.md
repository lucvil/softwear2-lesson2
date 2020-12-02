# 課題１

## 構造体student
```c
struct student
{
  int id; //4 
  char name[100]; //100
  int age;//4             
  double height;//8
  double weight;//8
};
```

上を見ると

1. int id:   ４バイト
2. name[100]: 100バイト
3. int age:  4バイト　＋　4バイト分パディング
4. double height: 8バイト
5. double weight: 8バイト

合計128バイト

## 構造体tagged_student1

```c
  int id; //4
  char name[100]; //100
  int age;//4
  double height;//8 
  double weight;//8
  char tag;//1
```

1. int id:   ４バイト
2. name[100]: 100バイト
3. int age:  4バイト　＋　4バイト分パディング
4. double height: 8バイト
5. double weight: 8バイト
6. char tag: 1バイト　+ 7バイト

合計136バイト

## 構造体tagged_student2

```c
  char tag;//1
  int id; //4
  char name[100]; //100
  int age;    //4 
  double height;//8
  double weight;//8
```

1. char tag: 1バイト　+ 3バイト分パティング
2. int id:   ４バイト
3. name[100]: 100バイト
4. int age:  4バイト
5. double height: 8バイト
6. double weight: 8バイト

合計128バイト



