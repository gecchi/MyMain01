// auto.cc		Created      : Sat Mar 24 10:40:36 2001
//			Last modified: Sat Mar 24 11:18:13 2001
// Compile:  g++ auto.cc -o auto #
// Execute:  ./auto #
//------------------------------------------------------------
// 自動変数と staticな変数。
//   リテラルはどこに配置されるか
//   自動変数の配列はブロックから出たあとに破棄される。

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <list>
#include <string>
#include <string.h>
using namespace std;
//------------------------------------------------------------
// まずは文字列リテラル。どこに配置されるか。
// ポインタの値に注目。
//
//void Insert_Non_Static_Pointer(char*> &data) {
//  char* element = "takashi";
//  data.push_front(element);
//  printf("Non static pointer: 0x%08X\n",element);
//}
//
//void Insert_Non_Static_Pointer2(list<char*> &data) {
//  char* element = "takashi";
//  data.push_front(element);
//  printf("Non static pointer2: 0x%08X\n",element);
//}
//
//void Insert_Static_Pointer(list<char*> &data) {
//  static char* element = "aki";
//  data.push_front(element);
//  printf("Static pointer    : 0x%08X\n",element);
//}
//
////------------------------------------------------------------
//// 次は文字列を入れた「配列」自動変数として宣言した配列は
//// ブロックを出たあとにどうなるか?
//void Insert_Non_Static_Array(list<char*> &data) {
//  char element[] = "MAMEWO";
//  data.push_front(element);
//  //ここの値に注目。
//  printf("Non static array  : 0x%08X\n",element);
//}
//
//void Insert_Static_Array(list<char*> &data) {
//  static char element[] = "TAK";
//  data.push_front(element);
//  printf("Static array      : 0x%08X\n",element);
//}


char* catstr(char* r, char* a, char* b) {
	  printf("addra : 0x%08X\n",a);
	  printf("addrb : 0x%08X\n",b);
	  printf("addrr : 0x%08X\n",r);
	strcat(r, a);
	strcat(r, b);
	return r;
}
void named(char* aaa) {
	char* sss = aaa;
	char* s = "zz";
	strcat(s, sss);
	printf("addr1 : 0x%08X\n",s);
	//printf("addr2 : 0x%08X\n",s);
}


int main(int argc,char *argv[]) {
  char path[80] = {'\0'};
  catstr(path, "aaa", "bbb");
  cout << path << endl;
  printf("addrpath : 0x%08X\n",path);

  catstr(path, "zzz", "bbb");
  cout << path << endl;
  printf("addrpath : 0x%08X\n",path);

  return 0;
}

