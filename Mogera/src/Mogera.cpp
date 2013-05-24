/**
 * �uGecchi Game App Framework ���C�u�����v�g�p�T���v��
 */
#include "stdafx.h"
#include "GgafLibEntry.h" //"GgafLibEntry.h" ���C���N���[�h���A
                          //main�֐� WinMain�֐� �E�B���h�E�v���V�[�W����
                          //�P�̃t�@�C���ɋL�q���܂��B
#include "MgrGod.h"

using namespace Mogera;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * GCC �̃G���g���|�C���g
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv); //����ɁA���̗l�ɌĂяo���ĉ������B
}

/**
 * MSVC �̃G���g���|�C���g
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow); //����ɁA���̗l�ɌĂяo���ĉ������B

    //�v���p�e�B�t�@�C���Ǎ���
    GgafLib::GgafLibProperties::load(".\\config.properties");

    //�E�B���h�E��`���쐬
    WNDCLASSEX wcex1;
    ZeroMemory(&wcex1, sizeof(WNDCLASSEX));
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    wcex1.lpfnWndProc = (WNDPROC)WndProc;
    wcex1.hInstance = hInstance;
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.lpszClassName = "primary";
    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "secondary";
    DWORD dwStyle = WS_OVERLAPPEDWINDOW;
    HWND hWnd1, hWnd2;
    GgafLibCreateWindow(wcex1, wcex2,
                        "Mogera[1]", "Mogera[2]", //�^�C�g��������
                        dwStyle, dwStyle,
                        hWnd1, hWnd2); //HWND���������܂�(�߂�l)

    //�Q�[�����[�v
    MSG msg;
    try {
        //�_�̒a��
        MgrGod* pGod = new MgrGod(hInstance, hWnd1, hWnd2);
        pGod->initDevice();
        timeBeginPeriod(1);
        //���[�v�{��
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    //�I�����b�Z�[�W�̏ꍇ�A�v�����I��
                    if (MgrGod::_can_be) {
                        MgrGod::_can_be = false;
                        while (pGod->_is_being) { Sleep(2); }
                        delete pGod;
                        GgafLib::GgafLibProperties::clean(); //�v���p�e�B���(�Ǎ��񂾏ꍇ�̂ݕK�v)
                    }
                    timeEndPeriod(1);
                    return EXIT_SUCCESS; //�A�v���I��
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                //���̂悤�ɂЂ�����_�� be() ���\�b�h���R�[�����Ă��������B
                if (MgrGod::_can_be) {
                    pGod->be();
                }
            }
        }

    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "Mogera Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[�G���[]:"<<what); //_TRACE_() �̓f�o�b�O���[�h���̂ݕW���o�͂ɏo�͂���܂��B
        timeEndPeriod(1);
        return EXIT_FAILURE; //�ُ�I��
    }
    return (int)msg.wParam;
}

/**
 * �E�B���h�E�v���V�[�W�������� .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam); //����ɁA���̗l�ɌĂяo���ĉ������B
    static HRGN hRgn1,hRgn2;
    switch (message) {
        case WM_CREATE: {
            hRgn1 = CreateRoundRectRgn( 0, 0, 290, 240, 30, 30);
            hRgn2 = CreateRoundRectRgn(70, 130, 350, 300, 60, 60);
            CombineRgn(hRgn1, hRgn1, hRgn2, 3); // fnCombineMode = 3 _
            //hRound = CreateEllipticRgn(0, 0, 350,350);
            SetWindowRgn(hWnd, hRgn1, 1 );
            break;
        }
        case WM_DESTROY: {
            DeleteObject(hRgn1);
            DeleteObject(hRgn2);
            break;
        }
    }
    //�K�v������΁A���b�Z�[�W�������R�R�ɒǉ��L�q
    return DefWindowProc(hWnd, message, wParam, lParam);
}







//
//
//
//HWND    hWnd;       //  �ύX����Window�BWS_EX_LAYERED�ɂ��WM_PAINT���Ă΂�Ȃ��Ȃ�̂Œ��ӁB
//HBITMAP hPicture;   //  32bitDIBSection�ȂǁBARGB8888�ɂȂ��Ă���B
//SIZE    szWnd;      //  �X�V��̃E�C���h�E�̑傫���BHBITMAP�̑傫���ȉ��łȂ���΂Ȃ�Ȃ��B
//POINT   ptSrc;      //  �摜�]���̊J�n�ʒu�BptSrc+szWnd�̒l��HBITMAP�̑傫���ȉ��łȂ���΂Ȃ�Ȃ��B
//
//#if 0 // CreateWindowEx��dwExStyle�p�����[�^��WS_EX_LAYERED���܂܂�Ă���Ƃ��͕K�v�Ȃ�
//DWORD   dwStyleEx = GetWindowLong( hWnd, GWL_EXSTYLE );
//SetWindowLong( hWnd, GWL_EXSTYLE, dwStyleEx | WS_EX_LAYERED );
//#endif
//
//HDC     hdcScreen   = ::GetDC( NULL );
//HDC     hdcMemory   = ::CreateCompatibleDC( hdcScreen );
//HANDLE  hOld        = ::SelectObject( hdcMemory, hPicture );
//
//BLENDFUNCTION cBlend;
//cBlend.BlendOp              = AC_SRC_OVER;
//cBlend.BlendFlags           = 0;
//cBlend.SourceConstantAlpha  = 0xff;
//cBlend.AlphaFormat          = AC_SRC_ALPHA;
//
//RECT    rcWnd;
//::GetWindowRect( hWnd, &rcWnd );
//
//POINT   ptWnd   = { rcWnd.left, rcWnd.top };
//
//::UpdateLayeredWindow( hWnd, hdcScreen, &ptWnd, &szWnd, hdcMemory, &ptSrc, 0, &cBlend, ULW_ALPHA );
//::SelectObject( hdcMemory, hOld );
//::DeleteDC( hdcMemory );
//::ReleaseDC( NULL, hdcScreen );
//
//
//
//
//
//
//
//
//
//#pragma pack( push, 1 )
//struct ARGB { BYTE b, g, r, a; };
//#pragma pack( pop )
//
//static BYTE s_tblBlend[256][256];
//
//void InitializeTable( )
//{
//  for( int a = 0; a < 256; a++ ) {
//    for( int c = 0; c < 256; c++ ) {
//      s_tblBlend[a][c] = c * a / 255;
//    }
//  }
//}
//void ConvertCalcedARGB( ARGB* p, int cx, int cy, int pitch )
//{
//  for( int y = 0; y < cy; y++ ) {
//    for( int x = 0; y < cx; x++ ) {
//      BYTE A = p[x].a;
//      p[x].b = s_tblBlend[ A ][ p[x].b ];
//      p[x].g = s_tblBlend[ A ][ p[x].g ];
//      p[x].r = s_tblBlend[ A ][ p[x].r ];
//    }
//    p = (BYTE*)p + pitch;
//  }
//}

