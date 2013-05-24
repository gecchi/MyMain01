/**
 * 「Gecchi Game App Framework ライブラリ」使用サンプル
 */
#include "stdafx.h"
#include "GgafLibEntry.h" //"GgafLibEntry.h" をインクルードし、
                          //main関数 WinMain関数 ウィンドウプロシージャは
                          //１つのファイルに記述します。
#include "MgrGod.h"

using namespace Mogera;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/**
 * GCC のエントリポイント
 */
int main(int argc, char *argv[]) {
    return GgafLibMain(argc, argv); //直後に、この様に呼び出して下さい。
}

/**
 * MSVC のエントリポイント
 */
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    GgafLibWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow); //直後に、この様に呼び出して下さい。

    //プロパティファイル読込み
    GgafLib::GgafLibProperties::load(".\\config.properties");

    //ウィンドウ定義＆作成
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
                        "Mogera[1]", "Mogera[2]", //タイトル文字列
                        dwStyle, dwStyle,
                        hWnd1, hWnd2); //HWNDが代入されます(戻り値)

    //ゲームループ
    MSG msg;
    try {
        //神の誕生
        MgrGod* pGod = new MgrGod(hInstance, hWnd1, hWnd2);
        pGod->initDevice();
        timeBeginPeriod(1);
        //ループ本体
        while (true) {
            if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    //終了メッセージの場合アプリを終了
                    if (MgrGod::_can_be) {
                        MgrGod::_can_be = false;
                        while (pGod->_is_being) { Sleep(2); }
                        delete pGod;
                        GgafLib::GgafLibProperties::clean(); //プロパティ解放(読込んだ場合のみ必要)
                    }
                    timeEndPeriod(1);
                    return EXIT_SUCCESS; //アプリ終了
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            } else {
                //次のようにひたすら神の be() メソッドをコールしてください。
                if (MgrGod::_can_be) {
                    pGod->be();
                }
            }
        }

    } catch (std::exception& e2) {
        std::string what(e2.what());
        MessageBox(nullptr, what.c_str(), "Mogera Error", MB_OK|MB_ICONSTOP|MB_SETFOREGROUND);
        _TRACE_("[エラー]:"<<what); //_TRACE_() はデバッグモード時のみ標準出力に出力されます。
        timeEndPeriod(1);
        return EXIT_FAILURE; //異常終了
    }
    return (int)msg.wParam;
}

/**
 * ウィンドウプロシージャ実装例 .
 */
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    GgafLibWndProc(hWnd, message, wParam, lParam); //直後に、この様に呼び出して下さい。
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
    //必要があれば、メッセージ処理をココに追加記述
    return DefWindowProc(hWnd, message, wParam, lParam);
}







//
//
//
//HWND    hWnd;       //  変更するWindow。WS_EX_LAYEREDによりWM_PAINTが呼ばれなくなるので注意。
//HBITMAP hPicture;   //  32bitDIBSectionなど。ARGB8888になっている。
//SIZE    szWnd;      //  更新後のウインドウの大きさ。HBITMAPの大きさ以下でなければならない。
//POINT   ptSrc;      //  画像転送の開始位置。ptSrc+szWndの値がHBITMAPの大きさ以下でなければならない。
//
//#if 0 // CreateWindowExのdwExStyleパラメータにWS_EX_LAYEREDが含まれているときは必要ない
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

