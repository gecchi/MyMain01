#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


//TODO:コメントとか多すぎる。整理する。


HWND GgafDx9God::_pHWndPrimary = NULL;
HWND GgafDx9God::_pHWndSecondary = NULL;
HINSTANCE GgafDx9God::_hInstance = NULL;

IDirect3D9* GgafDx9God::_pID3D9 = NULL;
IDirect3DDevice9* GgafDx9God::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDx9God::_d3dlight9_default;
D3DLIGHT9 GgafDx9God::_d3dlight9_temp;
DWORD GgafDx9God::_dwAmbientBrightness_default = 0xff404040;

RECT GgafDx9God::_rectPresent_Primary;
RECT GgafDx9God::_rectPresent_Secondary;

//RECT GgafDx9God::_rectDualDisplayWindow_Primary;
//RECT GgafDx9God::_rectDualDisplayWindow_Secondary;
//RECT GgafDx9God::_rectDualDisplayFullScreen_Primary;
//RECT GgafDx9God::_rectDualDisplayFullScreen_Secondary;


RECT GgafDx9God::_rectGameBuffer_HarfLeft;
RECT GgafDx9God::_rectGameBuffer_HarfRight;
RECT GgafDx9God::_rectGameBuffer;



//RECT*  GgafDx9God::_pRectViewScreen = NULL;

//double GgafDx9God::_cameraZ = 0;
//double GgafDx9God::_cameraZ_org = 0;
//double GgafDx9God::_tan_half_fovY = 0;
//double GgafDx9God::_dCamHarfXfovTan = 0;
//double GgafDx9God::_screen_aspect = 0;


D3DFILLMODE GgafDx9God::_d3dfillmode = D3DFILL_SOLID;//D3DFILL_WIREFRAME;//D3DFILL_SOLID;

GgafDx9ModelManager* GgafDx9God::_pModelManager = NULL;
GgafDx9EffectManager* GgafDx9God::_pEffectManager = NULL;
//int const PROPERTY(GAME_BUFFER_WIDTH)  = 1024;
//int const PROPERTY(GAME_BUFFER_HEIGHT) = 600;
D3DPRESENT_PARAMETERS* GgafDx9God::_d3dparam;

bool GgafDx9God::_is_device_lost_flg = false;
bool GgafDx9God::_adjustGameScreen = false;
HWND GgafDx9God::_pHWnd_adjustScreen = NULL;

int GgafDx9God::_iNumAdapter = 1;

UINT32 GgafDx9God::_vs_v = 0;
UINT32 GgafDx9God::_ps_v = 0;

D3DXMACRO GgafDx9God::_effectmacro_sm[3] =
{
    { "VS_VERSION", "vs_3_0" },
    { "PS_VERSION", "ps_3_0" },
    { NULL, NULL }
};


IDirect3DTexture9*  GgafDx9God::_pRenderTexture = NULL;   //テクスチャ
//IDirect3DSurface9*  GgafDx9God::_pBackBuffer = NULL;      //バックバッファ
IDirect3DSurface9*  GgafDx9God::_pRenderTextureSurface = NULL;     //サーフェイス
IDirect3DSurface9* GgafDx9God::_pRenderTextureZ = NULL;


GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary) :
    GgafGod() {
    TRACE("GgafDx9God::GgafDx9God() ");
    GgafDx9God::_pHWndPrimary = prm_pHWndPrimary;
    GgafDx9God::_pHWndSecondary = prm_pHWndSecondary;
    GgafDx9God::_hInstance = prm_hInstance;
    _is_device_lost_flg = false;
    _adjustGameScreen = false;
    _pHWnd_adjustScreen = NULL;
    CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 Seed


    pSwapChain00 = NULL;//アダプタに関連付けれられたスワップチェーン
    pBackBuffer00 = NULL;//バックバッファ1画面分
    pSwapChain01 = NULL;//アダプタに関連付けれられたスワップチェーン
    pBackBuffer01 = NULL;//バックバッファ１画面分
}

HRESULT GgafDx9God::init() {
    //[メモ]
    //引数に使用するRECT構造体のメンバ right, bottom は「右下座標」となっているが、これは正確ではない。
    //実際の定義は
    //rect.right = rect.left + 矩形幅;
    //rect.bottom = rect.top + 矩形高さ;
    //らしい。
    //よって、例えば (10,10)-(17,17)領域は、RECT(10,10,18,18) と指定しなければいけないらしい。ややこしい。
    //（※本当の右下座標は、right, bottom の -1 の値になる）

    _rectGameBuffer.left   = 0;
    _rectGameBuffer.top    = 0;
    _rectGameBuffer.right  = _rectGameBuffer.left + PROPERTY(GAME_BUFFER_WIDTH);
    _rectGameBuffer.bottom = _rectGameBuffer.top  + PROPERTY(GAME_BUFFER_HEIGHT);

    _rectGameBuffer_HarfLeft.left   = 0;
    _rectGameBuffer_HarfLeft.top    = 0;
    _rectGameBuffer_HarfLeft.right  = _rectGameBuffer_HarfLeft.left  + PROPERTY(GAME_BUFFER_WIDTH)/2;
    _rectGameBuffer_HarfLeft.bottom = _rectGameBuffer_HarfLeft.top + PROPERTY(GAME_BUFFER_HEIGHT);

    _rectGameBuffer_HarfRight.left   = PROPERTY(GAME_BUFFER_WIDTH)/2;
    _rectGameBuffer_HarfRight.top    = 0;
    _rectGameBuffer_HarfRight.right  = _rectGameBuffer_HarfRight.left + PROPERTY(GAME_BUFFER_WIDTH)/2;
    _rectGameBuffer_HarfRight.bottom = _rectGameBuffer_HarfRight.top  + PROPERTY(GAME_BUFFER_HEIGHT);

    //表示領域設定
    if (PROPERTY(FULL_SCREEN)) {
        //フルスクリーンモード
        if (PROPERTY(DUAL_DISPLAY)) {
            //フルスクリーンモード・２画面使用
            if (PROPERTY(FIXED_VIEW_ASPECT)) {
                LONG fix_width = PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = PROPERTY(GAME_BUFFER_HEIGHT);
                //「フルスクリーンモード・２画面使用・縦横比FIX」の１画面目フロントバッファ描画領域
                if (1.0f * PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_WIDTH) / PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _rectPresent_Primary.left   = (PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _rectPresent_Primary.top    = 0;
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_WIDTH) / fix_width; //縮小率=横幅の比率
                    _rectPresent_Primary.left   = 0;
                    _rectPresent_Primary.top    = (PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                }

                //「フルスクリーンモード・２画面使用・縦横比FIX」の２画面目フロントバッファ描画領域
                if (1.0f * PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_WIDTH) / PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _rectPresent_Secondary.left   = (PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _rectPresent_Secondary.top    = 0;
                    _rectPresent_Secondary.right  = _rectPresent_Secondary.left + (fix_width * rate);
                    _rectPresent_Secondary.bottom = _rectPresent_Secondary.top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_WIDTH) / fix_width; //縮小率=横幅の比率
                    _rectPresent_Secondary.left   = 0;
                    _rectPresent_Secondary.top    = (PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _rectPresent_Secondary.right  = _rectPresent_Secondary.left + (fix_width * rate);
                    _rectPresent_Secondary.bottom = _rectPresent_Secondary.top  + (fix_height * rate);
                }
            } else {
                //「フルスクリーンモード・２画面使用・縦横比ストレッチ」の１画面目フロントバッファ描画領域
                _rectPresent_Primary.left   = 0;
                _rectPresent_Primary.top    = 0;
                _rectPresent_Primary.right  = _rectPresent_Primary.left + PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_WIDTH);
                _rectPresent_Primary.bottom = _rectPresent_Primary.top  + PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_HEIGHT);
                //「フルスクリーンモード・２画面使用・縦横比ストレッチ」の２画面目フロントバッファ描画領域
                _rectPresent_Secondary.left   = 0;
                _rectPresent_Secondary.top    = 0;
                _rectPresent_Secondary.right  = _rectPresent_Secondary.left + PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_WIDTH);
                _rectPresent_Secondary.bottom = _rectPresent_Secondary.top  + PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_HEIGHT);
            }
        } else {
            //フルスクリーンモード・１画面使用
            if (PROPERTY(FIXED_VIEW_ASPECT)) {
                LONG fix_width = PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = PROPERTY(GAME_BUFFER_HEIGHT);
                //「フルスクリーンモード・１画面使用・縦横比FIX」のフロントバッファ描画領域
                if (1.0f * PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_WIDTH) / PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _rectPresent_Primary.left   = (PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _rectPresent_Primary.top    = 0;
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_WIDTH) / fix_width; //縮小率=横幅の比率
                    _rectPresent_Primary.left   = 0;
                    _rectPresent_Primary.top    = (PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                }
                _rectPresent_Secondary.left   = 0;
                _rectPresent_Secondary.top    = 0;
                _rectPresent_Secondary.right  = 0;
                _rectPresent_Secondary.bottom = 0;
            } else {
                //「フルスクリーンモード・１画面使用・縦横比ストレッチ」のフロントバッファ描画領域
                _rectPresent_Primary.left   = 0;
                _rectPresent_Primary.top    = 0;
                _rectPresent_Primary.right  = _rectPresent_Primary.left + PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_WIDTH);
                _rectPresent_Primary.bottom = _rectPresent_Primary.top  + PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_HEIGHT);
                _rectPresent_Secondary.left   = 0;
                _rectPresent_Secondary.top    = 0;
                _rectPresent_Secondary.right  = 0;
                _rectPresent_Secondary.bottom = 0;
            }
        }
    } else {
        //ウィンドウモード
        if (PROPERTY(DUAL_DISPLAY)) {
            //ウィンドウモード・２窓使用
            if (PROPERTY(FIXED_VIEW_ASPECT)) {
                LONG fix_width = PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = PROPERTY(GAME_BUFFER_HEIGHT);
                //「ウィンドウモード・２窓使用・縦横比FIX」の１窓目フロントバッファ描画領域
                if (1.0f * PROPERTY(DUAL_DISPLAY_WINDOW1_WIDTH) / PROPERTY(DUAL_DISPLAY_WINDOW1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * PROPERTY(DUAL_DISPLAY_WINDOW1_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _rectPresent_Primary.left   = (PROPERTY(DUAL_DISPLAY_WINDOW1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _rectPresent_Primary.top    = 0;
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * PROPERTY(DUAL_DISPLAY_WINDOW1_WIDTH) / fix_width; //縮小率=横幅の比率
                    _rectPresent_Primary.left   = 0;
                    _rectPresent_Primary.top    = (PROPERTY(DUAL_DISPLAY_WINDOW1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                }

                //「ウィンドウモード・２窓使用・縦横比FIX」の２窓目フロントバッファ描画領域
                if (1.0f * PROPERTY(DUAL_DISPLAY_WINDOW2_WIDTH) / PROPERTY(DUAL_DISPLAY_WINDOW2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * PROPERTY(DUAL_DISPLAY_WINDOW2_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _rectPresent_Secondary.left   = (PROPERTY(DUAL_DISPLAY_WINDOW2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _rectPresent_Secondary.top    = 0;
                    _rectPresent_Secondary.right  = _rectPresent_Secondary.left + (fix_width * rate);
                    _rectPresent_Secondary.bottom = _rectPresent_Secondary.top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * PROPERTY(DUAL_DISPLAY_WINDOW2_WIDTH) / fix_width; //縮小率=横幅の比率
                    _rectPresent_Secondary.left   = 0;
                    _rectPresent_Secondary.top    = (PROPERTY(DUAL_DISPLAY_WINDOW2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _rectPresent_Secondary.right  = _rectPresent_Secondary.left + (fix_width * rate);
                    _rectPresent_Secondary.bottom = _rectPresent_Secondary.top  + (fix_height * rate);
                }
            } else {
                //「ウィンドウモード・２窓使用・縦横比ストレッチ」の１窓目フロントバッファ描画領域
                _rectPresent_Primary.left   = 0;
                _rectPresent_Primary.top    = 0;
                _rectPresent_Primary.right  = _rectPresent_Primary.left + PROPERTY(DUAL_DISPLAY_WINDOW1_WIDTH);
                _rectPresent_Primary.bottom = _rectPresent_Primary.top  + PROPERTY(DUAL_DISPLAY_WINDOW1_HEIGHT);
                //「ウィンドウモード・２窓使用・縦横比ストレッチ」の２窓目フロントバッファ描画領域
                _rectPresent_Secondary.left   = 0;
                _rectPresent_Secondary.top    = 0;
                _rectPresent_Secondary.right  = _rectPresent_Secondary.left + PROPERTY(DUAL_DISPLAY_WINDOW2_WIDTH);
                _rectPresent_Secondary.bottom = _rectPresent_Secondary.top  + PROPERTY(DUAL_DISPLAY_WINDOW2_HEIGHT);
            }
        } else {
            //ウィンドウモード・１窓使用
            if (PROPERTY(FIXED_VIEW_ASPECT)) {
                LONG fix_width = PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = PROPERTY(GAME_BUFFER_HEIGHT);
                //「ウィンドウモード・１窓使用・縦横比FIX」のフロントバッファ描画領域
                if (1.0f * PROPERTY(SINGLE_DISPLAY_WINDOW_WIDTH) / PROPERTY(SINGLE_DISPLAY_WINDOW_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * PROPERTY(SINGLE_DISPLAY_WINDOW_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _rectPresent_Primary.left   = (PROPERTY(SINGLE_DISPLAY_WINDOW_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _rectPresent_Primary.top    = 0;
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * PROPERTY(SINGLE_DISPLAY_WINDOW_WIDTH) / fix_width; //縮小率=横幅の比率
                    _rectPresent_Primary.left   = 0;
                    _rectPresent_Primary.top    = (PROPERTY(SINGLE_DISPLAY_WINDOW_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                }
                _rectPresent_Secondary.left   = 0;
                _rectPresent_Secondary.top    = 0;
                _rectPresent_Secondary.right  = 0;
                _rectPresent_Secondary.bottom = 0;
            } else {
                //「ウィンドウモード・１窓使用・縦横比ストレッチ」のフロントバッファ描画領域
                _rectPresent_Primary.left   = 0;
                _rectPresent_Primary.top    = 0;
                _rectPresent_Primary.right  = _rectPresent_Primary.left + PROPERTY(SINGLE_DISPLAY_WINDOW_WIDTH);
                _rectPresent_Primary.bottom = _rectPresent_Primary.top  + PROPERTY(SINGLE_DISPLAY_WINDOW_HEIGHT);
                _rectPresent_Secondary.left   = 0;
                _rectPresent_Secondary.top    = 0;
                _rectPresent_Secondary.right  = 0;
                _rectPresent_Secondary.bottom = 0;
            }
        }
    }
    _TRACE_(" _rectPresent_Primary.left     = "<<_rectPresent_Primary.left    );
    _TRACE_(" _rectPresent_Primary.top      = "<<_rectPresent_Primary.top     );
    _TRACE_(" _rectPresent_Primary.right    = "<<_rectPresent_Primary.right   );
    _TRACE_(" _rectPresent_Primary.bottom   = "<<_rectPresent_Primary.bottom  );
    _TRACE_(" _rectPresent_Secondary.left   = "<<_rectPresent_Secondary.left  );
    _TRACE_(" _rectPresent_Secondary.top    = "<<_rectPresent_Secondary.top   );
    _TRACE_(" _rectPresent_Secondary.right  = "<<_rectPresent_Secondary.right );
    _TRACE_(" _rectPresent_Secondary.bottom = "<<_rectPresent_Secondary.bottom);



    HRESULT hr;

    //IDirect3D9コンポーネントの取得
    if (!(GgafDx9God::_pID3D9 = Direct3DCreate9(D3D_SDK_VERSION))) {
        throwGgafCriticalException("Direct3DCreate9 に失敗しました");
        return E_FAIL; //失敗
    }
    //    //参照カウンタを余分増やす。理由はデストラクタのデバイス解放処理参照。
    //    GgafDx9God::_pID3D9->AddRef();
    //    GgafDx9God::_pID3D9->AddRef();

    //デスプレイモードの取得
    D3DDISPLAYMODE structD3DDisplayMode; //結果が格納される構造体
    hr = GgafDx9God::_pID3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &structD3DDisplayMode);
    checkDxException(hr, D3D_OK, "GetAdapterDisplayMode に失敗しました");

    D3DCAPS9 caps___;
    GgafDx9God::_pID3D9->GetDeviceCaps(0, D3DDEVTYPE_HAL, &caps___);
    _iNumAdapter = caps___.NumberOfAdaptersInGroup;   //使えるアダプタの数取得
    _TRACE_("_iNumAdapter = "<< _iNumAdapter);

    //デバイスパラメータ作成
    _d3dparam = NEW D3DPRESENT_PARAMETERS[2];
    ZeroMemory(&_d3dparam[0], sizeof(D3DPRESENT_PARAMETERS));
    //バックバッファの数
    _d3dparam[0].BackBufferCount = 1;
    //深度ステンシルバッファ
    //_d3dparam[0].EnableAutoDepthStencil = FALSE;
    //_d3dparam[0].AutoDepthStencilFormat = 0;
    _d3dparam[0].EnableAutoDepthStencil = TRUE; //Z バッファの自動作成
    _d3dparam[0].AutoDepthStencilFormat = D3DFMT_D24S8;//D3DFMT_D16;
    //0にしておく
    _d3dparam[0].Flags = 0;

    if (PROPERTY(FULL_SCREEN)) {
        //フルスクリーン時
        _d3dparam[0].BackBufferFormat = D3DFMT_X8R8G8B8;
                                        //D3DFMT_A8R8G8B8; //D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;
        _d3dparam[0].Windowed = false; //フルスクリーンモード時
        _d3dparam[0].FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //リフレッシュレート
        _d3dparam[0].PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //スワップのタイミング
        if (PROPERTY(DUAL_DISPLAY)) {
            _d3dparam[0].SwapEffect = D3DSWAPEFFECT_COPY;
        } else {
            _d3dparam[0].SwapEffect = D3DSWAPEFFECT_DISCARD;
        }
    } else {
        //ウィンドウ時
        _d3dparam[0].BackBufferFormat = structD3DDisplayMode.Format;
                                      // D3DFMT_UNKNOWN;   //現在の画面モードを利用
        _d3dparam[0].Windowed = true; //ウィンドウモード時
        _d3dparam[0].FullScreen_RefreshRateInHz = 0; //リフレッシュレート
        _d3dparam[0].PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //即座
        //TODO:Windowモードはこれ一択なのか？、D3DPRESENT_INTERVAL_ONE とかためす？
        _d3dparam[0].SwapEffect = D3DSWAPEFFECT_COPY;
    }

    //アンチアイリアスにできるかチェック
    UINT32 qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;

    //	if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //		D3DADAPTER_DEFAULT,
    //		D3DDEVTYPE_HAL,
    //		D3DFMT_A8R8G8B8,
    //		PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
    //		D3DMULTISAMPLE_2_SAMPLES,
    //		&qualityLevels) ) )
    //	{
    //		if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //			D3DADAPTER_DEFAULT,
    //			D3DDEVTYPE_HAL,
    //			D3DFMT_D24S8,
    //			PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
    //			D3DMULTISAMPLE_2_SAMPLES,
    //			NULL) ) )
    //		{
    //			multiSampleType = D3DMULTISAMPLE_2_SAMPLES;
    //			_TRACE_("MultiSampleType = D3DMULTISAMPLE_2_SAMPLES");
    //		}
    //	}
    //マルチサンプルの数
    _d3dparam[0].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
    //マルチサンプルの品質レベル
    _d3dparam[0].MultiSampleQuality = 0;//qualityLevels - (qualityLevels > 0 ? 1 : 0);

    //２画面使用時の差分修正
    _d3dparam[1] = _d3dparam[0]; //共通が多いためコピー
    //Windowハンドルを個別指定
    _d3dparam[0].hDeviceWindow = _pHWndPrimary;
    _d3dparam[1].hDeviceWindow = _pHWndSecondary;
    //バックバッファサイズ
    if (PROPERTY(FULL_SCREEN)) {
        if(PROPERTY(DUAL_DISPLAY)) {
            //フルスクリーンモード・２画面使用
            _d3dparam[0].BackBufferWidth  = PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_WIDTH);
            _d3dparam[0].BackBufferHeight = PROPERTY(DUAL_DISPLAY_FULL_SCREEN1_HEIGHT);
            _d3dparam[1].BackBufferWidth  = PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_WIDTH);
            _d3dparam[1].BackBufferHeight = PROPERTY(DUAL_DISPLAY_FULL_SCREEN2_HEIGHT);
        } else {
            //フルスクリーンモード・１画面使用
            _d3dparam[0].BackBufferWidth  = PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_WIDTH);
            _d3dparam[0].BackBufferHeight = PROPERTY(SINGLE_DISPLAY_FULL_SCREEN_HEIGHT);
            _d3dparam[1].BackBufferWidth  = 0;
            _d3dparam[1].BackBufferHeight = 0;
        }
    } else {
        if(PROPERTY(DUAL_DISPLAY)) {
            //ウィンドウモード・２画面使用
            _d3dparam[0].BackBufferWidth  = PROPERTY(GAME_BUFFER_WIDTH);
            _d3dparam[0].BackBufferHeight = PROPERTY(GAME_BUFFER_HEIGHT);
            _d3dparam[1].BackBufferWidth  = 0;
            _d3dparam[1].BackBufferHeight = 0;
        } else {
            //ウィンドウモード・１画面使用
            _d3dparam[0].BackBufferWidth  = PROPERTY(GAME_BUFFER_WIDTH);
            _d3dparam[0].BackBufferHeight = PROPERTY(GAME_BUFFER_HEIGHT);
            _d3dparam[1].BackBufferWidth  = 0;
            _d3dparam[1].BackBufferHeight = 0;
        }
    }



    //    //フルスクリーンに出来るか調べる
    //    if (PROPERTY(FULL_SCREEN)) {
    //        int cc = GgafDx9God::_pID3D9->GetAdapterModeCount(D3DADAPTER_DEFAULT,
    //                                                          _d3dparam[0].BackBufferFormat);
    //        if (cc) {
    //            D3DDISPLAYMODE adp;
    //            for (int i = 0; i < cc; i++) {
    //                GgafDx9God::_pID3D9->EnumAdapterModes(D3DADAPTER_DEFAULT,
    //                                                      _d3dparam[0].BackBufferFormat, i, &adp);
    //                if (adp.Format == _d3dparam[0].BackBufferFormat && adp.Width
    //                        == (UINT)PROPERTY(GAME_BUFFER_WIDTH) && adp.Height
    //                        == (UINT)PROPERTY(GAME_BUFFER_HEIGHT)) {
    //                    //OK
    //                    break;
    //                }
    //                if (cc == i) {
    //                    //要求した使える解像度が見つからない
    //                    throwGgafCriticalException(PROPERTY(GAME_BUFFER_WIDTH) <<"x"<<PROPERTY(GAME_BUFFER_HEIGHT) << "のフルスクリーンモードにする事ができません。");
    //                    return E_FAIL;
    //                }
    //            }
    //        } else {
    //            throwGgafCriticalException("GetAdapterModeCount に失敗しました");
    //            return E_FAIL;
    //        }
    //    }


    //default
    UINT AdapterToUse = D3DADAPTER_DEFAULT;
    D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;
    // NVIDIA PerfHUD 用 begin --------------------------------------------->

//#ifdef MY_DEBUG
//
//#if SHIPPING_VERSION
//    // When building a shipping version, disable PerfHUD (opt-out)
//#else
//    _TRACE_("Look for 'NVIDIA PerfHUD' adapter...");
//    // If it is present, override default settings
//    for (UINT Adapter = 0; Adapter < GgafDx9God::_pID3D9->GetAdapterCount(); Adapter++) {
//        D3DADAPTER_IDENTIFIER9 Identifier;
//        HRESULT Res;
//        Res = GgafDx9God::_pID3D9->GetAdapterIdentifier(Adapter, 0, &Identifier);
//        if (strstr(Identifier.Description, "PerfHUD") != 0) {
//            _TRACE_("found NVIDIA PerfHUD!");
//            AdapterToUse = Adapter;
//            DeviceType = D3DDEVTYPE_REF;
//            break;
//        }
//    }
//#endif
//
//#endif
    // <------------------------------------------------ NVIDIA PerfHUD 用 end

    if (PROPERTY(FULL_SCREEN) && PROPERTY(DUAL_DISPLAY)) {

        //デバイス作成を試み GgafDx9God::_pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                                               D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_ADAPTERGROUP_DEVICE  ,
                                               _d3dparam, &GgafDx9God::_pID3DDevice9);
        //checkDxException(hr, D3D_OK, "CreateDevice() に失敗しました。");
        if (hr != D3D_OK) {
            _TRACE_("D3DCREATE_PUREDEVICE: "<<GgafDx9CriticalException::getHresultMsg(hr));

            //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
            hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_ADAPTERGROUP_DEVICE,
                                                   _d3dparam, &GgafDx9God::_pID3DDevice9);
            if (hr != D3D_OK) {
                _TRACE_("D3DCREATE_SOFTWARE_VERTEXPROCESSING: "<<GgafDx9CriticalException::getHresultMsg(hr));

                //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_pHWndPrimary,
                                                       D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_ADAPTERGROUP_DEVICE,
                                                       _d3dparam, &GgafDx9God::_pID3DDevice9);
                if (hr != D3D_OK) {
                    _TRACE_("D3DCREATE_SOFTWARE_VERTEXPROCESSING: "<<GgafDx9CriticalException::getHresultMsg(hr));

                    //どのデバイスの作成も失敗した場合
                    MessageBox(GgafDx9God::_pHWndPrimary, TEXT("MULTI FULLSCRREEN Direct3Dの初期化に失敗"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
                    return E_FAIL;
                } else {
                    _TRACE_("GgafDx9God::init デバイスは MULTI FULLSCRREEN REF で初期化できました。");
                }

            } else {
                _TRACE_("GgafDx9God::init デバイスは MULTI FULLSCRREEN HAL(soft vp) で初期化できました。");
            }

        } else {
            _TRACE_("GgafDx9God::init デバイスは MULTI FULLSCRREEN HAL(pure vp) で初期化できました。");
        }

    } else {
        //デバイス作成を試み GgafDx9God::_pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        hr = GgafDx9God::_pID3D9->CreateDevice(AdapterToUse, DeviceType, GgafDx9God::_pHWndPrimary,
                                               D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED,
    //                                           D3DCREATE_MIXED_VERTEXPROCESSING|D3DCREATE_MULTITHREADED,
    //                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                               &_d3dparam[0], &GgafDx9God::_pID3DDevice9);

        if (hr != D3D_OK) {
            //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
            hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                                   &_d3dparam[0], &GgafDx9God::_pID3DDevice9);
            if (hr != D3D_OK) {
                //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_pHWndPrimary,
                                                       D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                                       &_d3dparam[0], &GgafDx9God::_pID3DDevice9);
                if (hr != D3D_OK) {
                    //どのデバイスの作成も失敗した場合
                    MessageBox(GgafDx9God::_pHWndPrimary, TEXT("Direct3Dの初期化に失敗"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
                    return E_FAIL;
                } else {
                    _TRACE_("GgafDx9God::init デバイスは REF で初期化できました。");
                }

            } else {
                _TRACE_("GgafDx9God::init デバイスは HAL(soft vp) で初期化できました。");
            }

        } else {
            _TRACE_("GgafDx9God::init デバイスは HAL(pure vp) で初期化できました。");
        }
    }

    //ピクセルシェーダー、頂点シェーダーバージョンチェック
    D3DCAPS9 caps;
    GgafDx9God::_pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] ディスプレイ アダプタを示す序数。
                                       //      D3DADAPTER_DEFAULT は常に
                                       //      プライマリ ディスプレイ アダプタ
                                       D3DDEVTYPE_HAL, // [in] デバイスの種類。 D3DDEVTYPE列挙型のメンバ
                                       &caps); // [out] デバイスの能力が格納される

    _vs_v = caps.VertexShaderVersion;
    _ps_v = caps.PixelShaderVersion;
    _TRACE_("Hardware Vertex Shader Version = "<<D3DSHADER_VERSION_MAJOR(_vs_v)<<"_"<<D3DSHADER_VERSION_MINOR(_vs_v));
    _TRACE_("Hardware Pixel Shader Version  = "<<D3DSHADER_VERSION_MAJOR(_ps_v)<<"_"<<D3DSHADER_VERSION_MINOR(_ps_v));
    if (_vs_v < D3DVS_VERSION(2, 0) || _ps_v < D3DPS_VERSION(2, 0)) {
        _TRACE_("ビデオカードハードの頂点シェーダーとピンクセルシェーダーは、共にバージョン 2_0 以上でなければいけません。");
        _TRACE_("ご使用のビデオカードでは、正しく動作しない恐れがあります。");
    }

    //その他必要な初期化
    _pModelManager = NEW GgafDx9ModelManager("ModelManager");
    _pEffectManager = NEW GgafDx9EffectManager("EffectManager");
    GgafDx9Util::init(); //ユーティリティ準備
    GgafDx9Input::init(); //DirectInput準備
    GgafDx9Sound::init(); //DirectSound準備

//ココで呼ぶとメモリ違反
//    adjustGameScreen(_pHWndPrimary);
//    if (_pHWndSecondary) {
//        adjustGameScreen(_pHWndSecondary);
//    }


//    _adjustGameScreen = true;
    return initDx9Device();

}

HRESULT GgafDx9God::initDx9Device() {
    // デフォルトのライト
    /*
     ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9) );
     GgafDx9God::_d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL; //平行光、色と方向だけでよい
     GgafDx9God::_d3dlight9_default.Direction = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
     GgafDx9God::_d3dlight9_default.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
     GgafDx9God::_d3dlight9_default.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
     //下は平行光では関係ない
     //GgafDx9God::_d3dlight9_default.Position = D3DXVECTOR3(-1*PROPERTY(GAME_BUFFER_WIDTH)/2, -1*PROPERTY(GAME_BUFFER_HEIGHT)/2, -1*PROPERTY(GAME_BUFFER_HEIGHT)/2);
     //GgafDx9God::_d3dlight9_default.Range = 1000;
     */

    //ライト構造体は、シェーダーのパラメータになる時があるため必要。
    D3DXVECTOR3 vecDirection(-1.0f, -1.0f, 1.0f);
    D3DXVec3Normalize(&vecDirection, &vecDirection);
    ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9));
    GgafDx9God::_d3dlight9_default.Direction = vecDirection;
    GgafDx9God::_d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL;
    GgafDx9God::_d3dlight9_default.Diffuse.a = 1.0f;
    GgafDx9God::_d3dlight9_default.Diffuse.r = 1.0f;
    GgafDx9God::_d3dlight9_default.Diffuse.g = 1.0f;
    GgafDx9God::_d3dlight9_default.Diffuse.b = 1.0f;

    GgafDx9God::_d3dlight9_default.Ambient.a = 1.0f;
    GgafDx9God::_d3dlight9_default.Ambient.r = 0.3f; //アンビエントライトはSetRenderState(D3DRS_AMBIENT, 0x00303030)で設定
    GgafDx9God::_d3dlight9_default.Ambient.g = 0.3f;
    GgafDx9God::_d3dlight9_default.Ambient.b = 0.3f;

    //GgafDx9God::_d3dlight9_default.Range = 1000.0f;


    //ライトをセット
    //    GgafDx9God::_pID3DDevice9->SetLight(0, &GgafDx9God::_d3dlight9_default);
    //ライトスイッチON
    //    GgafDx9God::_pID3DDevice9->LightEnable(0, TRUE);
    //GgafDx9God::_pID3DDevice9->LightEnable(0, FALSE);
    //レンダ時にライトの影響（陰影）を有効
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);
    //レンダ時にライトの影響（陰影）を無効 (ピクセルシェーダーで行なうため）
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);
    //レンダ時、世界に共通のアンビエントライトを有効にしたように描く
    //   GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, _dwAmbientBrightness_default);

    // Zバッファを有効に
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファを無効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    //Zバッファ書き込み可
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //Zバッファ書き込み不可
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    //D3DRENDERSTATE_ZFUNC

    //ステンシルテストの方法
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //常にテストをパス
    //画に失敗した時にステンシルの値をどう変化させるか
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //変化なし
    //Zテストで失敗した場合のステンシル値の変化
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //変化なし


    //左（反時計回り）回りにカリング ∵左手座標系
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //カリングしない
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // ディザリング
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DITHERENABLE, TRUE );
    // マルチサンプリングアンチエイリアス(といってもフルスクリーンだけ？)↓TODO:まだ謎
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
//    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK, 0x00ffffff);

    //ピクセル単位のアルファテストを有効
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    //α設定はシェーダーに書く事にしたのでコメント
    // アルファブレンドＯＮ
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //2段階目、半透明テクスチャを貼り付けたポリゴンとバックバッファ（レンダーターゲット）との合成
    //色の算出方法の設定
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD); //D3DBLENDOP_ADD=転送元に転送先が加算
    //合成係数
    //    //上に書く画像の合成法(シェーダーに影響)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC,D3DBLEND_SRCALPHA=普通に描く。ポリゴンのアルファ値の濃さで描く。アルファ値の値が高ければ高いほど、濃く描く。
    //    //下地の画像の合成法(シェーダーに影響)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //DIST,D3DBLEND_INVSRCALPHA=上に描くポリゴンのアルファ値の濃さによって、下地の描画を薄くする。


    //頂点カラーを無効にする
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, FALSE );
    // GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, TRUE );
    //    //面のアンビエント反射は、マテリアルを参照するように設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //面のデフューズ反射は、マテリアルを参照するように設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //面のエミッシブ反射は、マテリアルを参照する設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //面のスペキュラ反射は、マテリアルを参照する設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

    //頂点αを使用するとき
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1);

    //
    //
    // アンチエイリアスの指定
    //GgafDx9God::_pID3DDevice9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    //GgafDx9God::_pID3DDevice9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    //	TypeにD3DSAMP_MINFILTER/D3DSAMP_MAGFILTER（拡大/縮小時） ??D3DTSS_MAGFILTER
    //	ValueにD3DTEXTUREFILTERTYPE列挙型を指定する
    //	D3DTEXF_POINT　　　　：フィルタをかけない。高速描画できる
    //	D3DTEXF_LINEAR　　　：リニアフィルタ（線形補完）
    //	D3DTEXF_ANISOTROPIC　：異方性フィルタ。地表面などの、拡大縮小率が手前と奥で異なる場合に使う
    //	D3DTEXF_PYRAMIDALQUAD：テントフィルタ。リニアフィルタとあまり変わんないらしい
    //	D3DTEXF_GAUSSIANQUAD ：ガウシアンフィルタ。またの名をぼかしフィルタ
    //	を指定する。

    //2009/3/4 SetSamplerStateの意味を今ごろ理解する。
    //SetSamplerStateはテクスチャからどうサンプリング（読み取るか）するかの設定。
    //だからアンチエイリアスっていっても、テクスチャしかアンチエイリアスがかかりません。
    //今後ピクセルシェーダーで全部書くので、このあたりの設定は、全部いらなくなるはずだ。


    //アンチエイリアスにかかわるレンダリングステート
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK,0x7fffffff);

    //色合成も全てシェーダーで処理になったのでコメント
    //SetTextureStageStateは廃止？
    //  1段階目ポリゴンとテクスチャの合成方法設定
    //    //テクスチャーの色と、頂点カラーのDIFFUSE色を乗算するように設定
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    //    //テクスチャーのαと、頂点カラーのαを乗算するように設定
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);


    //GgafDx9Cameraへ移動した
    // VIEW変換（カメラ位置）設定
    //D3DXMATRIX _matView; // ビュー変換行列
    //    DELETE_POSSIBLE_NULL(_pVecCamFromPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamLookatPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamUp);

    //GgafDx9Cameraへ移動した
    // 射影変換（３Ｄ→平面）
    //D3DXMATRIX _matProj; // 射影変換行列
    //GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &_matProj);


    if (PROPERTY(FULL_SCREEN)) {
        HRESULT hr;
        //描画先となるテクスチャを別途作成（バックバッファ的な使用を行う）
        hr = GgafDx9God::_pID3DDevice9->CreateTexture(
                                                PROPERTY(GAME_BUFFER_WIDTH),
                                                PROPERTY(GAME_BUFFER_HEIGHT),
                                                 1, //MipLevel Mip無し
                                                 D3DUSAGE_RENDERTARGET,
                                                 _d3dparam[0].BackBufferFormat,
                                                 D3DPOOL_DEFAULT,
                                                 &_pRenderTexture,
                                                 NULL);
        checkDxException(hr, D3D_OK, "バックバッファ・テクスチャ作成失敗");
        //描画先をテクスチャへ変更
        hr = _pRenderTexture->GetSurfaceLevel(0, &_pRenderTextureSurface);
        checkDxException(hr, D3D_OK, "テクスチャのサーフェイスポインタ取得失敗");
        hr = GgafDx9God::_pID3DDevice9->SetRenderTarget(0, _pRenderTextureSurface);
        checkDxException(hr, D3D_OK, "SetRenderTarget テクスチャのサーフェイス失敗");

        //テクスチャに描画する際の深度バッファ用サーフェイスを別途作成
        hr = GgafDx9God::_pID3DDevice9->CreateDepthStencilSurface(
                PROPERTY(GAME_BUFFER_WIDTH),
                PROPERTY(GAME_BUFFER_HEIGHT),
                _d3dparam[0].AutoDepthStencilFormat,   //D3DFORMAT   Format,
                _d3dparam[0].MultiSampleType,          //D3DMULTISAMPLE_TYPE     MultiSample,
                _d3dparam[0].MultiSampleQuality,       //DWORD   MultisampleQuality,
                TRUE,                                  //BOOL    Discard, SetDepthStencileSurface関数で深度バッファを変更した時にバッファを破棄するかどうか
                &_pRenderTextureZ,                     //IDirect3DSurface9**     ppSurface,
                NULL                                   //HANDLE*     pHandle 現在未使用
        );
        //深度バッファ作成自動生成の、深度バッファ用サーフェイスを上記に変更
        checkDxException(hr, D3D_OK, "バックバッファ・テクスチャのZバッファ作成失敗");
        hr =  GgafDx9God::_pID3DDevice9->SetDepthStencilSurface(_pRenderTextureZ);
        checkDxException(hr, D3D_OK, "SetDepthStencilSurfaceバックバッファ・テクスチャのZバッファ失敗");
        //クリア
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                              NULL, // 矩形領域
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
                                              D3DCOLOR_RGBA(0, 0, 0, 0), //背景黒にクリア //D3DCOLOR_XRGB( 0, 0, 0 ), //背景黒にクリア
                                              1.0f, // Zバッファのクリア値
                                              0 // ステンシルバッファのクリア値
                );
        checkDxException(hr, D3D_OK, "PROPERTY(FULL_SCREEN)初期化のGgafDx9God::_pID3DDevice9->Clear() に失敗しました。");

        //            //アダプタに関連付けられたスワップチェーンを取得してバックバッファも取得
                hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 0, &pSwapChain00 );
                checkDxException(hr, D3D_OK, "0GetSwapChain() に失敗しました。");
                hr = pSwapChain00->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer00 );
                checkDxException(hr, D3D_OK, "0GetBackBuffer() に失敗しました。");

        if (PROPERTY(DUAL_DISPLAY)) {


    //
            hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 1, &pSwapChain01 );
            checkDxException(hr, D3D_OK, "1GetSwapChain() に失敗しました。");
            hr = pSwapChain01->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer01 );
            checkDxException(hr, D3D_OK, "1GetBackBuffer() に失敗しました。");
        }
    }

    return S_OK;
}

// カメラと対峙する回転行列を取得
// ビルボードのVIEW変換行列を取得
D3DXMATRIX GgafDx9God::getInvRotateMat() {
    D3DXMATRIX Inv;
    //   D3DXMatrixIdentity(&Inv);
    //   D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
    //   D3DXMatrixInverse(&Inv, NULL, &Inv);

    return Inv;
}

void GgafDx9God::makeUniversalMaterialize() {
    TRACE("GgafDx9God::materialize() start");
    HRESULT hr;
    if (_is_device_lost_flg) {
        //正常デバイスロスト処理。デバイスリソースの解放→復帰処理を試みる。
        if (GgafDx9God::_pID3DDevice9->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            //工場休止
            GgafFactory::beginRest();
            ___EndSynchronized; // <----- 排他終了
            for (int i = 0; GgafFactory::isResting() == false; i++) {
                Sleep(60); //工場が落ち着くまで待つ
                if (i > 3000) {
                    _TRACE_("GgafDx9God::makeUniversalMaterialize() 3分待機しましたが、工場から反応がありません。強制breakします。要調査");
                    break;
                }
            }
            //            while (GgafFactory::isResting() == false) { //工場が落ち着くまで待つ
            //                Sleep(10);
            //            }
            ___BeginSynchronized; // ----->排他開始
            _TRACE_("正常デバイスロスト処理。Begin");
            //エフェクト、デバイスロスト処理
            GgafDx9God::_pEffectManager->onDeviceLostAll();
            //モデル解放
            GgafDx9God::_pModelManager->onDeviceLostAll();
            //全ノードに解放しなさいイベント発令
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_ON_DEVICE_LOST, this);

            //デバイスリセットを試みる
            hr = GgafDx9God::_pID3DDevice9->Reset(&(_d3dparam[0]));
            checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() デバイスロスト後のリセット[0]に失敗しました。");
            if (PROPERTY(DUAL_DISPLAY)) {
                for (int i = 1; i < _iNumAdapter; i++) {
                    hr = GgafDx9God::_pID3DDevice9->Reset(&(_d3dparam[i]));
                    checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() デバイスロスト後のリセット[1]に失敗しました。");
                }
            }

            //デバイス再設定
            GgafDx9God::initDx9Device();
            //エフェクトリセット
            GgafDx9God::_pEffectManager->restoreAll();
            //モデル再設定
            GgafDx9God::_pModelManager->restoreAll();
            //全ノードに再設定しなさいイベント発令
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_DEVICE_LOST_RESTORE, this);
            //前回描画モデル情報を無効にする
            GgafDx9God::_pModelManager->_pModelLastDraw = NULL;
            _is_device_lost_flg = false;

            //工場再開
            GgafFactory::finishRest();
            _TRACE_("正常デバイスロスト処理。End");
        }
    } else {
        //通常時（デバイスロストではない）の処理

        //バッファクリア
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                              NULL, // 矩形領域
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
                                              D3DCOLOR_RGBA(0, 0, 0, 0), //背景黒にクリア //D3DCOLOR_XRGB( 0, 0, 0 ), //背景黒にクリア
                                              1.0f, // Zバッファのクリア値
                                              0 // ステンシルバッファのクリア値
                );
        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->Clear() に失敗しました。");

        //描画事前処理
        hr = GgafDx9God::_pID3DDevice9->BeginScene();
        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->BeginScene() に失敗しました。");
        //全て具現化！（描画）
#ifdef MY_DEBUG
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
#endif
        GgafGod::makeUniversalMaterialize(); //スーパーのmaterialize実行
        //描画事後処理
        hr = GgafDx9God::_pID3DDevice9->EndScene();
        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->EndScene() に失敗しました。");

    }
    TRACE("GgafDx9God::makeUniversalMaterialize() end");
}

void GgafDx9God::presentUniversalVisualize() {
    if (_is_device_lost_flg != true) {
        //バックバッファをプライマリバッファに転送
        //if (GgafDx9God::_pID3DDevice9->Present(NULL,&_rectPresent_Primary,NULL,NULL) == D3DERR_DEVICELOST) {
        //        static D3DRASTER_STATUS rs;
        //        while (SUCCEEDED(GgafDx9God::_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
        //            if(rs.InVBlank) {
        //                break; //垂直帰線期間ではない
        //            } else {
        //                Sleep(1);
        //            }
        //        }

        if (_adjustGameScreen && _pHWnd_adjustScreen) {
            adjustGameScreen(_pHWnd_adjustScreen);
        }

        HRESULT hr;
//        hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
        if (PROPERTY(FULL_SCREEN)) {
            if (PROPERTY(DUAL_DISPLAY)) {
    //
                //画面０バックバッファを画面１バックバッファへコピーする
                hr = GgafDx9God::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface,  &_rectGameBuffer_HarfLeft,
                        pBackBuffer00,           &_rectPresent_Primary,
                        D3DTEXF_NONE);
                checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_DISPLAY 1画面目 StretchRect() に失敗しました。\n_pRenderTextureSurface="<<_pRenderTextureSurface<<"/pBackBuffer00="<<pBackBuffer00);

                hr = GgafDx9God::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface,  &_rectGameBuffer_HarfRight,
                        pBackBuffer01,           &_rectPresent_Secondary,
                        D3DTEXF_NONE);
                checkDxException(hr, D3D_OK, "StretchRect() に失敗しました。");

                hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);

    //            //プライマリバックバッファの右半分をセカンダリバックバッファへコピー
                //hr = GgafDx9God::_pID3DDevice9->UpdateSurface( pBackBuffer00, &_rectGameBuffer_HarfRight, pBackBuffer01, _pPoint);
                //checkDxException(hr, D3D_OK, "UpdateSurface() に失敗しました。");
    //            //コピーフリップ
//                hr = pSwapChain00->Present(NULL, NULL, NULL, NULL,0);
//    //            hr = pSwapChain00->Present(&_rectGameBuffer_HarfLeft, NULL, NULL, NULL,0);
//                checkDxException(hr, D3D_OK, "0Present() に失敗しました。");
//                hr = pSwapChain01->Present(NULL, NULL, NULL, NULL,0);
//                checkDxException(hr, D3D_OK, "1Present() に失敗しました。");
    ////            //バックバッファとZバッファを取得する
    ////            if(FAILED(m_pd3dDevice->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&m_pBackBuffer))){
    ////            }
    ////            if(FAILED(m_pd3dDevice->GetDepthStencilSurface(&m_pZBuffer))){
    ////            }

            } else {
                //１画面使用・フルスクリーンモード
//                LPDIRECT3DSWAPCHAIN9 pSwapChain00 = NULL;//アダプタに関連付けれられたスワップチェーン
//                LPDIRECT3DSURFACE9 pBackBuffer00 = NULL;//バックバッファ1画面分
                //フルスクリーン
//                hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 0, &pSwapChain00 );
//                checkDxException(hr, D3D_OK, "0GetSwapChain() に失敗しました。");
//                hr = pSwapChain00->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer00 );
//                checkDxException(hr, D3D_OK, "FULL 1gamen GetBackBuffer() に失敗しました。");

                hr = GgafDx9God::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface,
                        &_rectGameBuffer,
                        pBackBuffer00,
                        &_rectPresent_Primary,
                        D3DTEXF_NONE
                        );
                checkDxException(hr, D3D_OK, "FULL 1gamen StretchRect() に失敗しました。");

                hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);

//                //コピーフリップ
//                hr = pSwapChain00->Present(NULL, NULL, NULL, NULL,0);
//                checkDxException(hr, D3D_OK, "FULL 1gamen Present() に失敗しました。");


//                RELEASE_SAFETY(pBackBuffer00);
//                RELEASE_SAFETY(pSwapChain00);

            }
        } else {
            if (PROPERTY(DUAL_DISPLAY)) {
                //２画面使用・ウィンドウモード
                if (PROPERTY(FIXED_VIEW_ASPECT)) {
                    //縦横比固定モード
                    hr = GgafDx9God::_pID3DDevice9->Present(&_rectGameBuffer_HarfLeft, &_rectPresent_Primary, NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDx9God::_pID3DDevice9->Present(&_rectGameBuffer_HarfRight, &_rectPresent_Secondary, _pHWndSecondary, NULL);
                    }
                } else {
                    //縦横ストレッチモード
                    hr = GgafDx9God::_pID3DDevice9->Present(&_rectGameBuffer_HarfLeft, NULL, NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDx9God::_pID3DDevice9->Present(&_rectGameBuffer_HarfRight, NULL, _pHWndSecondary, NULL);
                    }
                }
            } else {
                //１画面使用・ウィンドウモード
                if (PROPERTY(FIXED_VIEW_ASPECT)) {
                    //縦横比固定モード
                    hr = GgafDx9God::_pID3DDevice9->Present(NULL, &_rectPresent_Primary, NULL, NULL);
                } else {
                    //縦横ストレッチモード
                    hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
                }
            }
        }
        if (hr == D3DERR_DEVICELOST) {
            //出刃異素露巣斗！
            _TRACE_("通常デバイスロスト！Present()");
            _is_device_lost_flg = true;
        } else if (hr == D3DERR_DRIVERINTERNALERROR) {
            //Present異常時、無駄かもしれないがデバイスロストと同じ処理を試みる。
            _TRACE_("Present() == D3DERR_DRIVERINTERNALERROR!! Reset()を試みます。（駄目かもしれません）");
            //工場休止
            GgafFactory::beginRest();
            ___EndSynchronized; // <----- 排他終了
            for (int i = 0; GgafFactory::isResting() == false; i++) {
                Sleep(60); //工場が落ち着くまで待つ
                if (i > 1000) {
                    _TRACE_("GgafDx9God::presentUniversalVisualize() 1分待機しましたが、工場から反応がありません。breakします。要調査");
                }
            }
            ___BeginSynchronized; // ----->排他開始
            _TRACE_("D3DERR_DRIVERINTERNALERROR！ 処理Begin");
            //エフェクト、デバイスロスト処理
            GgafDx9God::_pEffectManager->onDeviceLostAll();
            //モデル解放
            GgafDx9God::_pModelManager->onDeviceLostAll();
            //全ノードに解放しなさいイベント発令
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_ON_DEVICE_LOST, this);
            //デバイスリセットを試みる
            hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_d3dparam[0]));
            checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() D3DERR_DRIVERINTERNALERROR のため Reset([0]) を試しましが、駄目でした。");
            if (PROPERTY(DUAL_DISPLAY)) {
                for (int i = 1; i < _iNumAdapter; i++) {
                    hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_d3dparam[i]));
                    checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() D3DERR_DRIVERINTERNALERROR のため Reset([1]) を試しましが、駄目でした。");
                }
            }
            //デバイス再設定
            GgafDx9God::initDx9Device();
            //エフェクトリセット
            GgafDx9God::_pEffectManager->restoreAll();
            //モデル再設定
            GgafDx9God::_pModelManager->restoreAll();
            //全ノードに再設定しなさいイベント発令
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_DEVICE_LOST_RESTORE, this);
            //前回描画モデル情報を無効にする
            GgafDx9God::_pModelManager->_pModelLastDraw = NULL;

            //工場再開
            GgafFactory::finishRest();
            _TRACE_("D3DERR_DRIVERINTERNALERROR！ 処理End");
        }
    }
}

void GgafDx9God::clean() {
    if (!_was_cleaned) {
        _TRACE_("GgafDx9God::clean() begin");

        for( int i=0; i<8; ++i ) { GgafDx9God::_pID3DDevice9->SetTexture( i, NULL ); }
        for( int i=0; i<8; ++i ) { GgafDx9God::_pID3DDevice9->SetStreamSource( i, NULL, 0, 0 ); }
        GgafDx9God::_pID3DDevice9->SetIndices( NULL );
        GgafDx9God::_pID3DDevice9->SetPixelShader( NULL );
        GgafDx9God::_pID3DDevice9->SetVertexShader( NULL );
        GgafDx9God::_pID3DDevice9->SetVertexDeclaration( NULL );

        GgafGod::clean();

        CmRandomNumberGenerator::getInstance()->release();
        //保持モデル解放
        DELETE_IMPOSSIBLE_NULL(_pModelManager);
        DELETE_IMPOSSIBLE_NULL(_pEffectManager);

        _TRACE_("GgafDx9God::clean() end");
    }
}

void GgafDx9God::adjustGameScreen(HWND prm_pHWnd) {
     RECT rect;
    if (!PROPERTY(FULL_SCREEN) && PROPERTY(FIXED_VIEW_ASPECT)) {
        HRESULT hr;
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                              NULL, // 矩形領域
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
                                              D3DCOLOR_RGBA(0, 0, 0, 0), //背景黒にクリア //D3DCOLOR_XRGB( 0, 0, 0 ), //背景黒にクリア
                                              1.0f, // Zバッファのクリア値
                                              0 // ステンシルバッファのクリア値
                );
        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->Clear() に失敗しました。");
        if (::GetClientRect(prm_pHWnd, &rect)) {
            LONG width = rect.right + 1;
            LONG height = rect.bottom + 1;
            LONG fix_width, fix_height;
            if (PROPERTY(DUAL_DISPLAY)) {
                fix_width = PROPERTY(GAME_BUFFER_WIDTH)/2;
                fix_height = PROPERTY(GAME_BUFFER_HEIGHT);
            } else {
                fix_width = PROPERTY(GAME_BUFFER_WIDTH);
                fix_height = PROPERTY(GAME_BUFFER_HEIGHT);
            }

            if (1.0f * width / height > 1.0f * fix_width / fix_height) {
                //より横長になってしまっている
                double rate = 1.0 * height / fix_height; //縮小率=縦幅の比率
                if (prm_pHWnd == _pHWndPrimary) {
                    _rectPresent_Primary.left = (width / 2.0) - (fix_width * rate / 2.0);
                    _rectPresent_Primary.top = 0;
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                } else {
                    _rectPresent_Secondary.left = (width / 2.0) - (fix_width * rate / 2.0);
                    _rectPresent_Secondary.top = 0;
                    _rectPresent_Secondary.right  = _rectPresent_Secondary.left + (fix_width * rate);
                    _rectPresent_Secondary.bottom = _rectPresent_Secondary.top  + (fix_height * rate);
                }
            } else {
                //より縦長になってしまっている
                double rate = 1.0 * width / fix_width; //縮小率=横幅の比率
                if (prm_pHWnd == _pHWndPrimary) {
                    _rectPresent_Primary.left = 0;
                    _rectPresent_Primary.top = (height / 2.0) - (fix_height * rate / 2.0);
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                } else {
                    _rectPresent_Secondary.left = 0;
                    _rectPresent_Secondary.top = (height / 2.0) - (fix_height * rate / 2.0);
                    _rectPresent_Primary.right  = _rectPresent_Primary.left + (fix_width * rate);
                    _rectPresent_Primary.bottom = _rectPresent_Primary.top  + (fix_height * rate);
                }
            }
        }
    } else {
        if (::GetClientRect(prm_pHWnd, &rect)) {
            if (prm_pHWnd == _pHWndPrimary) {
                _rectPresent_Primary = rect;
            } else {
                _rectPresent_Secondary = rect;
            }

        }
    }
    GgafDx9God::_pID3DDevice9->GetViewport(&(P_CAM->_viewport));
    _adjustGameScreen = false;
    _pHWnd_adjustScreen = NULL;
}

//void GgafDx9God::adjustGameScreen() {
//     RECT rect;
//    if (PROPERTY(FIXED_VIEW_ASPECT)) {
//
//        D3DVIEWPORT9 vClient;
//        vClient.MinZ = 0.0f;
//        vClient.MaxZ = 1.0f;
//        vClient.X = (DWORD)0;
//        vClient.Y = (DWORD)0;
//        vClient.Width = (DWORD)(PROPERTY(GAME_BUFFER_WIDTH));
//        vClient.Height = (DWORD)(PROPERTY(GAME_BUFFER_HEIGHT));
//        _pID3DDevice9->SetViewport(&vClient);
//        HRESULT hr;
//        hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
//                                              NULL, // 矩形領域
//                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
//                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
//                                              D3DCOLOR_RGBA(0, 0, 0, 0), //背景黒にクリア //D3DCOLOR_XRGB( 0, 0, 0 ), //背景黒にクリア
//                                              1.0f, // Zバッファのクリア値
//                                              0 // ステンシルバッファのクリア値
//                );
//        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->Clear() に失敗しました。");
//
//
//        if (::GetClientRect(_pHWndPrimary, &rect)) {
//            D3DVIEWPORT9 vp;    //ビューポート
//            vp.MinZ = 0.0f;
//            vp.MaxZ = 1.0f;
//            double aspect_client = 1.0 * rect.right / rect.bottom;
//            double aspect_buffer = 1.0 * PROPERTY(GAME_BUFFER_WIDTH) / PROPERTY(GAME_BUFFER_HEIGHT);
////            _TRACE_("aspect_client = "<<aspect_client<<" aspect_buffer="<<aspect_buffer);
//            if (aspect_client > aspect_buffer) {
//                //より横長になってしまっている
//                double rate = (1.0 * PROPERTY(GAME_BUFFER_WIDTH) / PROPERTY(GAME_BUFFER_HEIGHT) / (1.0 *rect.right / rect.bottom));
//                vp.X = (DWORD)((PROPERTY(GAME_BUFFER_WIDTH) / 2.0) - (PROPERTY(GAME_BUFFER_WIDTH) * rate / 2.0)) ;
//                vp.Y = (DWORD)0;
//                vp.Width = (DWORD)(PROPERTY(GAME_BUFFER_WIDTH) * rate);
//                vp.Height = (DWORD)(PROPERTY(GAME_BUFFER_HEIGHT));
//            } else {
//                //より縦長になってしまっている
//                double rate = (1.0 * PROPERTY(GAME_BUFFER_HEIGHT) / PROPERTY(GAME_BUFFER_WIDTH) / (1.0 *rect.bottom / rect.right));
//                vp.X = (DWORD)0;
//                vp.Y = (DWORD)((PROPERTY(GAME_BUFFER_HEIGHT) / 2.0) - (PROPERTY(GAME_BUFFER_HEIGHT) * rate / 2.0)) ;;
//                vp.Width = (DWORD)(PROPERTY(GAME_BUFFER_WIDTH));
//                vp.Height = (DWORD)(PROPERTY(GAME_BUFFER_HEIGHT) * rate);
//
//            }
////            _TRACE_("new vp="<<vp.X<<","<<vp.Y<<","<<vp.Width<<","<<vp.Height);
//            _pID3DDevice9->SetViewport(&vp);
//            _adjustGameScreen = false;
//        }
//    } else {
//        if (::GetClientRect(_pHWndPrimary, &rect)) {
//            _rectPresent_Primary.top = rect.top;
//            _rectPresent_Primary.left = rect.left;
//            _rectPresent_Primary.right = rect.right;
//            _rectPresent_Primary.bottom = rect.bottom;
//            _adjustGameScreen = false;
//        }
//    }
//}

GgafDx9God::~GgafDx9God() {

    clean();
    _was_cleaned = true;

    //DirectSound解放
    GgafDx9Sound::release();
    //DirectInput解放
    GgafDx9Input::release();
    _TRACE_("_pID3DDevice9 解放きたー");
    Sleep(60);
    RELEASE_SAFETY(pBackBuffer00);
    RELEASE_SAFETY(pBackBuffer01);
    RELEASE_SAFETY(pSwapChain00);
    RELEASE_SAFETY(pSwapChain01);
    DELETEARR_IMPOSSIBLE_NULL(_d3dparam);
    RELEASE_IMPOSSIBLE_NULL(_pID3DDevice9); //本来はこれが必要
    RELEASE_IMPOSSIBLE_NULL(_pID3D9);
//    D3DCREATE_HARDWARE_VERTEXPROCESSING でフルスクリーンで終了時、まれにブルースクリーンになる。
//    開発マシンの、VISTA, GeForce go 7600 （HP DV9200) で起こる。
//    しかし、他のマシンでは起らない事は確認出来た。
//    ビデオカードドライバのせいなのか、DV9200固有の問題なのか？！
//    ということにしておこう。ブルースクリーンになった方、大変申し訳ない。
//    かなりの時間を使って調査したが結局原因不明。・・もういやだやめて～


}



//                 <-------------------------------------------- 2048 --------------------------------------------->
//                 <--------- 512 --------->
//                 <------------------------- 1280 ----------------------------><-------------- 768 --------------->
//
//         ^   ^   +-----------------------+-----------------------+-----------+-----------+-----------------------+
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//        512 480  |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   |   |                       |                       |           |           |                       |
//         |   v   +-----------------------+-----------------------+-----------+           |                       |
//         v  32   +-----------------------+-----------------------+-----------------------+-----------------------+
//
//                                                                 <----256----><---256---->

