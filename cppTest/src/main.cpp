#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <d3d9.h>
//#include <d3dx9.h>
using namespace std;
#define DEBUG

/* 16 �i������� 10 �i���ɕϊ����� */
unsigned int ToDec(const char str[ ])
{
  short i = 0;        /* �z��̓Y���Ƃ��Ďg�p */
  short n;
  unsigned int x = 0;
  char c;

  while (str[i] != '\0') {        /* ������̖����łȂ���� */

          /* '0' ���� '9' �̕����Ȃ� */
      if ('0' <= str[i] && str[i] <= '9')
          n = str[i] - '0';        /* �����ɕϊ� */

          /* 'a' ���� 'f' �̕����Ȃ� */
      else if ('a' <= (c = tolower(str[i])) && c <= 'f')
          n = c - 'a' + 10;        /* �����ɕϊ� */

      else {        /* ����ȊO�̕����Ȃ� */
          printf("�����ȕ����ł��B\n");
          exit(0);        /* �v���O�������I�������� */
      }
      i++;        /* ���̕������w�� */

      x = x *16 + n;    /* ���オ�� */
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
        printf("�� %d �ߎ��l = %lf\n", i, x);
    }
}





