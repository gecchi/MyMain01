#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <d3d9.h>
//#include <d3dx9.h>
using namespace std;
#define DEBUG

/* 16 進文字列を 10 進数に変換する */
unsigned int ToDec(const char str[ ])
{
  short i = 0;        /* 配列の添字として使用 */
  short n;
  unsigned int x = 0;
  char c;

  while (str[i] != '\0') {        /* 文字列の末尾でなければ */

          /* '0' から '9' の文字なら */
      if ('0' <= str[i] && str[i] <= '9')
          n = str[i] - '0';        /* 数字に変換 */

          /* 'a' から 'f' の文字なら */
      else if ('a' <= (c = tolower(str[i])) && c <= 'f')
          n = c - 'a' + 10;        /* 数字に変換 */

      else {        /* それ以外の文字なら */
          printf("無効な文字です。\n");
          exit(0);        /* プログラムを終了させる */
      }
      i++;        /* 次の文字を指す */

      x = x *16 + n;    /* 桁上がり */
  }
  return (x);
}


int main(int argc, char *argv[]) {
    int a, i;
    double x;

    printf("a = "); scanf("%d", &a);

    x = 1;
    for (i = 1; i <= 10; i++) {
        x = 0.5 * (x + a / x);
        printf("第 %d 近似値 = %lf\n", i, x);
    }
}





