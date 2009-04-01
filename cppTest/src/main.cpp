#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
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
//      LPCTSTR lpApplicationName,                 //���s�\���W���[���̖��O
//      LPTSTR lpCommandLine,                      //�R�}���h���C���̕�����
//      LPSECURITY_ATTRIBUTES lpProcessAttributes, //�Z�L�����e�B�L�q�q
//      LPSECURITY_ATTRIBUTES lpThreadAttributes,  //�Z�L�����e�B�L�q�q
//      BOOL bInheritHandles,                      //�n���h���̌p���I�v�V����
//      DWORD dwCreationFlags,                     //�쐬�̃t���O
//      LPVOID lpEnvironment,                      //�V�������u���b�N
//      LPCTSTR lpCurrentDirectory,                //�J�����g�f�B���N�g���̖��O
//      LPSTARTUPINFO lpStartupInfo,               //�X�^�[�g�A�b�v���
//      LPPROCESS_INFORMATION lpProcessInformation //�v���Z�X���
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

        // �N�����s
        printf("�����ς�\n");
    }

    printf("ptargetVertxBuffer=");

    char name[25];
    scanf("%s",name);
    //�p�����[�^�� ------->
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
        printf("���_ %d : (%f,%f,%f)",(i+1),(pV->x),(pV->y),(pV->z));
    }

    ptargetVertxBuffer->Unlock();

    return 0;
}





