#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
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

    //system("CMD /C CD C:\\cygwin\\workspace\\MyStg2nd && C:\\cygwin\\workspace\\MyStg2nd\\MyStg2nd.exe 2>&1 >> C:\\temp\\loglog.log");
//    ShellExecute(NULL, "open", "bash.exe", "/cygdrive/c/cygwin/workspace/MyStg2nd/RunMyStg2nd.sh", NULL, SW_SHOW);
    //ShellExecute("bash -c /cygdrive/c/cygwin/workspace/MyStg2nd/RunMyStg2nd.sh");

    STARTUPINFO sinfo;
    PROCESS_INFORMATION pinfo;

    ZeroMemory( &sinfo, sizeof( STARTUPINFO ) );
    ZeroMemory( &pinfo, sizeof( PROCESS_INFORMATION ) );
    sinfo.cb = sizeof( STARTUPINFO );
    sinfo.dwFlags = STARTF_USESHOWWINDOW|DEBUG_PROCESS ;
    sinfo.wShowWindow = SW_SHOWNORMAL;

//    BOOL CreateProcess(
//      LPCTSTR lpApplicationName,                 //実行可能モジュールの名前
//      LPTSTR lpCommandLine,                      //コマンドラインの文字列
//      LPSECURITY_ATTRIBUTES lpProcessAttributes, //セキュリティ記述子
//      LPSECURITY_ATTRIBUTES lpThreadAttributes,  //セキュリティ記述子
//      BOOL bInheritHandles,                      //ハンドルの継承オプション
//      DWORD dwCreationFlags,                     //作成のフラグ
//      LPVOID lpEnvironment,                      //新しい環境ブロック
//      LPCTSTR lpCurrentDirectory,                //カレントディレクトリの名前
//      LPSTARTUPINFO lpStartupInfo,               //スタートアップ情報
//      LPPROCESS_INFORMATION lpProcessInformation //プロセス情報
//    );



    if ( !CreateProcess( NULL,
                         "C:\\cygwin\\workspace\\MyStg2nd\\MyStg2nd.exe",
                         NULL,
                         NULL,
                         FALSE,
                         0,
                         NULL,
                         "C:\\cygwin\\workspace\\MyStg2nd",
                         &sinfo,
                         &pinfo ) ) {

        // 起動失敗
        printf("しっぱい\n");
    }

    printf("ptargetVertxBuffer=");

    char name[25];
    scanf("%s",name);
    //パラメータ部 ------->
    LPDIRECT3DVERTEXBUFFER9 ptargetVertxBuffer = (LPDIRECT3DVERTEXBUFFER9)ToDec(name);
    DWORD dwFVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
    int nVertxs = 10;
    //<------------------






    DWORD dwFVFSize  = D3DXGetFVFVertexSize(dwFVF);
    BYTE* pByteVertexSrc;
    D3DVECTOR* pV;

    ptargetVertxBuffer->Lock(0, 0, (void**)&pByteVertexSrc, D3DLOCK_READONLY);

    for (int i = 0; i < nVertxs; i++) {
        pV = (D3DVECTOR*)(pByteVertexSrc + (dwFVFSize * i) + 0);
        printf("頂点 %d : (%f,%f,%f)",(i+1),(pV->x),(pV->y),(pV->z));
    }

    ptargetVertxBuffer->Unlock();

    return 0;
}





