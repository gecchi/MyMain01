#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;


//TODO:コメントとか多すぎる。整理する。


HWND GgafDx9God::_hWnd = NULL;
HINSTANCE GgafDx9God::_hInstance = NULL;

IDirect3D9* GgafDx9God::_pID3D9 = NULL;
IDirect3DDevice9* GgafDx9God::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDx9God::_d3dlight9_default;
D3DLIGHT9 GgafDx9God::_d3dlight9_temp;
DWORD GgafDx9God::_dwAmbientBrightness_default = 0xff404040;

RECT GgafDx9God::_rectPresentDest;
RECT*  GgafDx9God::_pRectHarfLeft = NULL;
RECT*  GgafDx9God::_pRectHarfRight = NULL;
//double GgafDx9God::_cameraZ = 0;
//double GgafDx9God::_cameraZ_org = 0;
//double GgafDx9God::_tan_half_fovY = 0;
//double GgafDx9God::_dCamHarfXfovTan = 0;
//double GgafDx9God::_screen_aspect = 0;


D3DFILLMODE GgafDx9God::_d3dfillmode = D3DFILL_SOLID;//D3DFILL_WIREFRAME;//D3DFILL_SOLID;

GgafDx9ModelManager* GgafDx9God::_pModelManager = NULL;
GgafDx9EffectManager* GgafDx9God::_pEffectManager = NULL;
//int const GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)  = 1024;
//int const GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT) = 600;
D3DPRESENT_PARAMETERS* GgafDx9God::_d3dparam;

bool GgafDx9God::_is_device_lost_flg = false;
bool GgafDx9God::_adjustGameScreen = false;
bool GgafDx9God::_FULLSCRREEN = false;
bool GgafDx9God::_MULTI_SCREEN = false;
int GgafDx9God::_iNumAdapter = 1;
GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND _hWnd) :
    GgafGod() {
    TRACE("GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND prmGgafDx9God::_hWnd) ");
    GgafDx9God::_hWnd = _hWnd;
    GgafDx9God::_hInstance = prm_hInstance;
    _is_device_lost_flg = false;
    _adjustGameScreen = false;
    CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 Seed
}

HRESULT GgafDx9God::init() {
    _FULLSCRREEN = GGAFDX9_PROPERTY(FULL_SCREEN);
    _MULTI_SCREEN = GGAFDX9_PROPERTY(MULTI_SCREEN);

    _pRectHarfRight = NEW RECT;
    _pRectHarfRight->left =  GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _pRectHarfRight->top = 0;
    _pRectHarfRight->right = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)-1;
    _pRectHarfRight->bottom = GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT)-1;

    _pRectHarfLeft = NEW RECT;
    _pRectHarfLeft->left = 0;
    _pRectHarfLeft->top = 0;
    _pRectHarfLeft->right = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)/2 - 1;
    _pRectHarfLeft->bottom = GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT)-1;

    _rectPresentDest.left = 0;
    _rectPresentDest.top = 0;
    if (_FULLSCRREEN && _MULTI_SCREEN) {
        _rectPresentDest.right = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)/2;
    } else {
        _rectPresentDest.right = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH);
    }
    _rectPresentDest.bottom = GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT);

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
    _d3dparam = NEW D3DPRESENT_PARAMETERS[_iNumAdapter];


    //デバイス作成
    ZeroMemory(&_d3dparam[0], sizeof(D3DPRESENT_PARAMETERS));
    //バックバッファの縦サイズ
    _d3dparam[0].BackBufferHeight = GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT);
    //_d3dparam[0].BackBufferHeight = GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT);
    //バックバッファの横サイズ
    if (_FULLSCRREEN && _MULTI_SCREEN) {
        _d3dparam[0].BackBufferWidth = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH); // /2
    } else if (_FULLSCRREEN) {
        _d3dparam[0].BackBufferWidth = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH); // /2
    } else {
        _d3dparam[0].BackBufferWidth = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH);
    }

    //_d3dparam[0].BackBufferWidth = GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH);
    //バックバッファのフォーマット
    if (_FULLSCRREEN && _MULTI_SCREEN) {
        _d3dparam[0].BackBufferFormat = D3DFMT_X8R8G8B8;
    } else if (_FULLSCRREEN) {
        _d3dparam[0].BackBufferFormat = D3DFMT_X8R8G8B8;//D3DFMT_A8R8G8B8;//D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;	//フルスクリーン時
    } else {
        _d3dparam[0].BackBufferFormat = structD3DDisplayMode.Format; //ウィンドウ時
        //_d3dparam[0].BackBufferFormat = D3DFMT_UNKNOWN;   //現在の画面モードを利用
    }

    //バックバッファの数
    _d3dparam[0].BackBufferCount = 1;

    //スワップ効果を指定する
    if (_FULLSCRREEN && _MULTI_SCREEN) {
        _d3dparam[0].SwapEffect = D3DSWAPEFFECT_COPY;
    } else if (_FULLSCRREEN) {
        _d3dparam[0].SwapEffect = D3DSWAPEFFECT_DISCARD;
    } else {
        _d3dparam[0].SwapEffect = D3DSWAPEFFECT_COPY;
    }

    //ウィンドウハンドル
    _d3dparam[0].hDeviceWindow = _hWnd;
    //ウィンドウモード
    if (_FULLSCRREEN && _MULTI_SCREEN) {
        _d3dparam[0].Windowed = false; //フルスクリーン時
    } else if (_FULLSCRREEN) {
        _d3dparam[0].Windowed = false; //フルスクリーン時
    } else {
        _d3dparam[0].Windowed = true; //ウィンドウ時
    }
    //深度ステンシルバッファ
    //_d3dparam[0].EnableAutoDepthStencil = FALSE;
    //_d3dparam[0].AutoDepthStencilFormat = 0;
    _d3dparam[0].EnableAutoDepthStencil = TRUE; //Z バッファの自動作成
    _d3dparam[0].AutoDepthStencilFormat = D3DFMT_D24S8;//D3DFMT_D16;
    //0にしておく
    _d3dparam[0].Flags = 0;
    //フルスクリーンでのリフレッシュレート(ウィンドウモードなら0を指定)
    if (_FULLSCRREEN) {
        _d3dparam[0].FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //フルスクリーン時
    } else {
        _d3dparam[0].FullScreen_RefreshRateInHz = 0; //ウィンドウ時
    }
    //スワップのタイミング
    if (_FULLSCRREEN && _MULTI_SCREEN) {
        _d3dparam[0].PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    } else if (_FULLSCRREEN) {
        _d3dparam[0].PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    } else {
        _d3dparam[0].PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //即座
        //TODO:Windowモードはこれ一択なのか？、D3DPRESENT_INTERVAL_ONE とかためす？
    }


    //アンチアイリアスにできるかチェック
    UINT32 qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;

    //	if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //		D3DADAPTER_DEFAULT,
    //		D3DDEVTYPE_HAL,
    //		D3DFMT_A8R8G8B8,
    //		_FULLSCRREEN ? FALSE : TRUE,
    //		D3DMULTISAMPLE_2_SAMPLES,
    //		&qualityLevels) ) )
    //	{
    //		if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //			D3DADAPTER_DEFAULT,
    //			D3DDEVTYPE_HAL,
    //			D3DFMT_D24S8,
    //			_FULLSCRREEN ? FALSE : TRUE,
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

    //フルスクリーンに出来るか調べる
    if (_FULLSCRREEN) {
        int cc = GgafDx9God::_pID3D9->GetAdapterModeCount(D3DADAPTER_DEFAULT,
                                                          _d3dparam[0].BackBufferFormat);
        if (cc) {
            D3DDISPLAYMODE adp;
            for (int i = 0; i < cc; i++) {
                GgafDx9God::_pID3D9->EnumAdapterModes(D3DADAPTER_DEFAULT,
                                                      _d3dparam[0].BackBufferFormat, i, &adp);
                if (adp.Format == _d3dparam[0].BackBufferFormat && adp.Width
                        == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH) && adp.Height
                        == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT)) {
                    //OK
                    break;
                }
                if (cc == i) {
                    //要求した使える解像度が見つからない
                    throwGgafCriticalException(GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH) <<"x"<<GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) << "のフルスクリーンモードにする事ができません。");
                    return E_FAIL;
                }
            }
        } else {
            throwGgafCriticalException("GetAdapterModeCount に失敗しました");
            return E_FAIL;
        }
    }






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


    //2画面の設定
    //http://www.shader.jp/xoops/html/masafumi/directx9/3dtips/d3d15.htm
    if (_FULLSCRREEN && _MULTI_SCREEN) {
        _d3dparam[1] = _d3dparam[0]; //共通が多いため

        WNDCLASSEX wcex;

        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC; //水平・垂直方向にウインドウサイズが変更されたときウインドウを再作画する。
        wcex.lpfnWndProc = (WNDPROC)GetWindowLong(_hWnd, GWL_WNDPROC ); //ウィンドウプロシージャのアドレスを指定する。
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = _hInstance;
        wcex.hIcon = NULL;
        wcex.hCursor = NULL;
        wcex.hbrBackground = CreateSolidBrush(RGB(30, 30, 30)); //0~255
        wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(IDC_MYSTG2ND);//NULL; //MAKEINTRESOURCE(IDC_MTSTG17_031);//メニューバーはなし
        wcex.lpszClassName = "multihead";
        wcex.hIconSm = NULL;

        RegisterClassEx(&wcex);


//        WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, (WNDPROC)GetWindowLong(_hWnd, GWL_WNDPROC ) , 0L, 0L,
//                          GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
//                          "multihead", NULL };
//        RegisterClassEx( &wc );
        //フォーカスウィンドウの指定(ここだけはアダプタごとに違うものを使うこと)

        _d3dparam[1].hDeviceWindow = CreateWindowEx(
            WS_EX_APPWINDOW,
            "multihead", //WINDOW_CLASS,
            "multihead",//WINDOW_TITLE,
            WS_POPUP | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)/2, //ウィンドウの幅、違うのはココのみ
            GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT),
            HWND_DESKTOP,
            NULL,
            _hInstance,
            NULL);

        _d3dparam[1].BackBufferWidth = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)/2; //プライマリ以外はバックバッファは一致して良い


//        _d3dparam[1].hDeviceWindow = CreateWindow(
//            "multihead",
//            "multihead",
//            NULL,
//            CW_USEDEFAULT,
//            CW_USEDEFAULT,
//            GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH/2), //ウィンドウの幅、違うのはココのみ
//            GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT),
//            NULL,
//            NULL,
//            wc.hInstance,
//            NULL );
    }


    if (_FULLSCRREEN && _MULTI_SCREEN) {

        //デバイス作成を試み GgafDx9God::_pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        hr = GgafDx9God::_pID3D9->CreateDevice(AdapterToUse, DeviceType, GgafDx9God::_hWnd,
                                               D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED | D3DCREATE_ADAPTERGROUP_DEVICE,
                                               _d3dparam, &GgafDx9God::_pID3DDevice9);

        if (hr != D3D_OK) {
            _TRACE_(GgafDx9CriticalException::getHresultMsg(hr));

            //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
            hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_hWnd,
                                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_ADAPTERGROUP_DEVICE,
                                                   _d3dparam, &GgafDx9God::_pID3DDevice9);
            if (hr != D3D_OK) {
                _TRACE_(GgafDx9CriticalException::getHresultMsg(hr));

                //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_hWnd,
                                                       D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_ADAPTERGROUP_DEVICE,
                                                       _d3dparam, &GgafDx9God::_pID3DDevice9);
                if (hr != D3D_OK) {
                    _TRACE_(GgafDx9CriticalException::getHresultMsg(hr));

                    //どのデバイスの作成も失敗した場合
                    MessageBox(GgafDx9God::_hWnd, TEXT("MULTI FULLSCRREEN Direct3Dの初期化に失敗"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
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
        hr = GgafDx9God::_pID3D9->CreateDevice(AdapterToUse, DeviceType, GgafDx9God::_hWnd,
                                               D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED,
    //                                           D3DCREATE_MIXED_VERTEXPROCESSING|D3DCREATE_MULTITHREADED,
    //                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                               &_d3dparam[0], &GgafDx9God::_pID3DDevice9);

        if (hr != D3D_OK) {
            //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
            hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_hWnd,
                                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                                   &_d3dparam[0], &GgafDx9God::_pID3DDevice9);
            if (hr != D3D_OK) {
                //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_hWnd,
                                                       D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                                       &_d3dparam[0], &GgafDx9God::_pID3DDevice9);
                if (hr != D3D_OK) {
                    //どのデバイスの作成も失敗した場合
                    MessageBox(GgafDx9God::_hWnd, TEXT("Direct3Dの初期化に失敗"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
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

    UINT32 vs_v = caps.VertexShaderVersion;
    UINT32 ps_v = caps.PixelShaderVersion;
    _TRACE_("Hardware Vertex Shader Version = "<<D3DSHADER_VERSION_MAJOR(vs_v)<<"_"<<D3DSHADER_VERSION_MINOR(vs_v));
    _TRACE_("Hardware Pixel Shader Version  = "<<D3DSHADER_VERSION_MAJOR(ps_v)<<"_"<<D3DSHADER_VERSION_MINOR(ps_v));
    if (vs_v < D3DVS_VERSION(2, 0) || ps_v < D3DPS_VERSION(2, 0)) {
        _TRACE_("ビデオカードハードの頂点シェーダーとピンクセルシェーダーは、共にバージョン 2_0 以上でなければいけません。");
        _TRACE_("ご使用のビデオカードでは、正しく動作しない恐れがあります。");
    }

    //その他必要な初期化
    _pModelManager = NEW GgafDx9ModelManager("ModelManager");
    _pEffectManager = NEW GgafDx9EffectManager("EffectManager");
    GgafDx9Util::init(); //ユーティリティ準備
    GgafDx9Input::init(); //DirectInput準備
    GgafDx9Sound::init(); //DirectSound準備
    _adjustGameScreen = true;
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
     //GgafDx9God::_d3dlight9_default.Position = D3DXVECTOR3(-1*GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH)/2, -1*GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT)/2, -1*GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT)/2);
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
                if (i > 2000) {
                    _TRACE_("GgafDx9God::makeUniversalMaterialize() ２分待機しましたが、工場から反応がありません。要調査");
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
            hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_d3dparam[0]));
            checkDxException(hr, D3D_OK, "GgafDx9God::makeUniversalMaterialize() デバイスロスト後のリセット[0]に失敗しました。");
            if (_FULLSCRREEN && _MULTI_SCREEN) {
                for (int i = 1; i < _iNumAdapter; i++) {
                    hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_d3dparam[i]));
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
        //if (GgafDx9God::_pID3DDevice9->Present(NULL,&_rectPresentDest,NULL,NULL) == D3DERR_DEVICELOST) {
        //        static D3DRASTER_STATUS rs;
        //        while (SUCCEEDED(GgafDx9God::_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
        //            if(rs.InVBlank) {
        //                break; //垂直帰線期間ではない
        //            } else {
        //                Sleep(1);
        //            }
        //        }

        if (_adjustGameScreen) {
            adjustGameScreen();
        }

        HRESULT hr;
//        hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);



        if (_FULLSCRREEN && _MULTI_SCREEN) {
            LPDIRECT3DSWAPCHAIN9 pSwapChain00 = NULL;//アダプタに関連付けれられたスワップチェーン
            LPDIRECT3DSURFACE9 pBackBuffer00 = NULL;//バックバッファ２画面分
            LPDIRECT3DSWAPCHAIN9 pSwapChain01 = NULL;//アダプタに関連付けれられたスワップチェーン
            LPDIRECT3DSURFACE9 pBackBuffer01 = NULL;//バックバッファ１画面分
            //アダプタに関連付けられたスワップチェーンを取得してバックバッファも取得
            hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 1, &pSwapChain00 );
            checkDxException(hr, D3D_OK, "0GetSwapChain() に失敗しました。");
            hr = pSwapChain01->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer00 );
            checkDxException(hr, D3D_OK, "0GetBackBuffer() に失敗しました。");

            hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 1, &pSwapChain01 );
            checkDxException(hr, D3D_OK, "1GetSwapChain() に失敗しました。");
            hr = pSwapChain01->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer01 );
            checkDxException(hr, D3D_OK, "1GetBackBuffer() に失敗しました。");


            //プライマリバックバッファの右半分をセカンダリバックバッファへコピー
            hr = GgafDx9God::_pID3DDevice9->UpdateSurface( pBackBuffer00, _pRectHarfRight, pBackBuffer01, NULL);
            checkDxException(hr, D3D_OK, "UpdateSurface() に失敗しました。");
            //コピーフリップ
            hr = pSwapChain00->Present(_pRectHarfLeft, NULL, NULL, NULL,0);
            checkDxException(hr, D3D_OK, "0Present() に失敗しました。");
            hr = pSwapChain01->Present(NULL, NULL, NULL, NULL,0);
            checkDxException(hr, D3D_OK, "1Present() に失敗しました。");
//            //バックバッファとZバッファを取得する
//            if(FAILED(m_pd3dDevice->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&m_pBackBuffer))){
//            }
//            if(FAILED(m_pd3dDevice->GetDepthStencilSurface(&m_pZBuffer))){
//            }
            RELEASE_SAFETY(pBackBuffer00);
            RELEASE_SAFETY(pBackBuffer01);
            RELEASE_SAFETY(pSwapChain00);
            RELEASE_SAFETY(pSwapChain01);

        } else if (_FULLSCRREEN) {
            //フルスクリーン
            hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
        } else {
            //ウィンドウモード
            if (GGAFDX9_PROPERTY(FIXED_VIEW_ASPECT)) {
                //縦横比固定モード
                hr = GgafDx9God::_pID3DDevice9->Present(NULL, &_rectPresentDest, NULL, NULL);
            } else {
                //縦横ストレッチモード
                hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
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
            if (_FULLSCRREEN && _MULTI_SCREEN) {
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

void GgafDx9God::adjustGameScreen() {
     RECT rect;
    if (GGAFDX9_PROPERTY(FIXED_VIEW_ASPECT)) {
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
        if (::GetClientRect(_hWnd, &rect)) {
            if (1.0f * rect.right / rect.bottom > 1.0f * GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) / GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT)) {
                //より横長になってしまっている
                float rate = 1.0f * rect.bottom / GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT); //縮小率=縦幅の比率
                GgafDx9God::_rectPresentDest.left = (rect.right / 2.0f)
                        - (GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) * rate / 2.0f);
                GgafDx9God::_rectPresentDest.top = 0;
                GgafDx9God::_rectPresentDest.right = (rect.right / 2.0f)
                        + (GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) * rate / 2.0f);
                GgafDx9God::_rectPresentDest.bottom = GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT) * rate;
            } else {
                //より縦長になってしまっている
                float rate = 1.0f * rect.right / GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH); //縮小率=横幅の比率
                GgafDx9God::_rectPresentDest.left = 0;
                GgafDx9God::_rectPresentDest.top = (rect.bottom / 2.0f)
                        - (GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT) * rate / 2.0f);
                GgafDx9God::_rectPresentDest.right = GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) * rate;
                GgafDx9God::_rectPresentDest.bottom = (rect.bottom / 2.0f)
                        + (GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT) * rate / 2.0f);
            }
            _adjustGameScreen = false;
        }
    } else {
        if (::GetClientRect(_hWnd, &rect)) {
            GgafDx9God::_rectPresentDest.top = rect.top;
            GgafDx9God::_rectPresentDest.left = rect.left;
            GgafDx9God::_rectPresentDest.right = rect.right;
            GgafDx9God::_rectPresentDest.bottom = rect.bottom;
            _adjustGameScreen = false;
        }
    }
    GgafDx9God::_pID3DDevice9->GetViewport(&(P_CAM->_viewport));
}

//void GgafDx9God::adjustGameScreen() {
//     RECT rect;
//    if (GGAFDX9_PROPERTY(FIXED_VIEW_ASPECT)) {
//
//        D3DVIEWPORT9 vClient;
//        vClient.MinZ = 0.0f;
//        vClient.MaxZ = 1.0f;
//        vClient.X = (DWORD)0;
//        vClient.Y = (DWORD)0;
//        vClient.Width = (DWORD)(GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH));
//        vClient.Height = (DWORD)(GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT));
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
//        if (::GetClientRect(_hWnd, &rect)) {
//            D3DVIEWPORT9 vp;    //ビューポート
//            vp.MinZ = 0.0f;
//            vp.MaxZ = 1.0f;
//            double aspect_client = 1.0 * rect.right / rect.bottom;
//            double aspect_buffer = 1.0 * GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) / GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT);
////            _TRACE_("aspect_client = "<<aspect_client<<" aspect_buffer="<<aspect_buffer);
//            if (aspect_client > aspect_buffer) {
//                //より横長になってしまっている
//                float rate = (1.0 * GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) / GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT) / (1.0 *rect.right / rect.bottom));
//                vp.X = (DWORD)((GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) / 2.0) - (GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) * rate / 2.0)) ;
//                vp.Y = (DWORD)0;
//                vp.Width = (DWORD)(GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) * rate);
//                vp.Height = (DWORD)(GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT));
//            } else {
//                //より縦長になってしまっている
//                float rate = (1.0 * GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT) / GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH) / (1.0 *rect.bottom / rect.right));
//                vp.X = (DWORD)0;
//                vp.Y = (DWORD)((GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT) / 2.0) - (GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT) * rate / 2.0)) ;;
//                vp.Width = (DWORD)(GGAFDX9_PROPERTY(GAME_BUFFER_WIDTH));
//                vp.Height = (DWORD)(GGAFDX9_PROPERTY(GAME_BUFFER_HEIGHT) * rate);
//
//            }
////            _TRACE_("new vp="<<vp.X<<","<<vp.Y<<","<<vp.Width<<","<<vp.Height);
//            _pID3DDevice9->SetViewport(&vp);
//            _adjustGameScreen = false;
//        }
//    } else {
//        if (::GetClientRect(_hWnd, &rect)) {
//            GgafDx9God::_rectPresentDest.top = rect.top;
//            GgafDx9God::_rectPresentDest.left = rect.left;
//            GgafDx9God::_rectPresentDest.right = rect.right;
//            GgafDx9God::_rectPresentDest.bottom = rect.bottom;
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
    DELETEARR_IMPOSSIBLE_NULL(_d3dparam);
    RELEASE_IMPOSSIBLE_NULL(_pID3DDevice9); //本来はこれが必要
    RELEASE_IMPOSSIBLE_NULL(_pID3D9);
//    フルスクリーンで終了時、極まれにブルースクリーンになる。
//    かなりの時間を使って調査したが結局原因不明もういやだ。
//    VISTA, GeForce go 7600 （開発マシン、HP DV9200) で起こる。
//    他の環境では起こったことがない。ビデオカードドライバのせいなのか、DV9200固有の問題なのか？！


}
