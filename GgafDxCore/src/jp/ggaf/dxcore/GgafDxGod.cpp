#include "jp/ggaf/dxcore/GgafDxGod.h"

#include <algorithm>
#include "jp/ggaf/dxcore/actor/camera/GgafDxCamera.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"
#include "jp/ggaf/dxcore/exception/GgafDxCriticalException.h"
#include "jp/ggaf/dxcore/GgafDxConfig.h"
#include "jp/ggaf/dxcore/manager/GgafDxEffectManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxModelManager.h"
#include "jp/ggaf/dxcore/manager/GgafDxTextureManager.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"
#include "jp/ggaf/dxcore/sound/GgafDxSound.h"
#include "jp/ggaf/dxcore/util/GgafDxInput.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"

using namespace GgafCore;
using namespace GgafDxCore;

#define returnWhenFailed(HR, OKVAL, X) { \
    if (HR != OKVAL) { \
        std::stringstream ss; \
        ss << X; \
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT(ss.str().c_str()), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST); \
        return E_FAIL; \
    } \
}

//TODO:コメントとか多すぎる。整理する。


#define PRIMARY_VIEW 0
#define SECONDARY_VIEW 1


HWND GgafDxGod::_pHWndPrimary = nullptr;
HWND GgafDxGod::_pHWndSecondary = nullptr;
HINSTANCE GgafDxGod::_hInstance = nullptr;
IDirect3D9* GgafDxGod::_pID3D9 = nullptr;
IDirect3DDevice9* GgafDxGod::_pID3DDevice9 = nullptr;
D3DLIGHT9 GgafDxGod::_d3dlight9_default;
DWORD GgafDxGod::_ambient_brightness_default = 0xff404040;


D3DFILLMODE GgafDxGod::_d3dfillmode = D3DFILL_SOLID;//D3DFILL_WIREFRAME;//D3DFILL_SOLID;

//GgafDxModelManager* GgafDxGod::_pModelManager = nullptr;
//GgafDxEffectManager* GgafDxGod::_pEffectManager = nullptr;
//GgafDxTextureManager* GgafDxGod::_pCubeMapTextureManager = nullptr;
//GgafDxTextureManager* GgafDxGod::_pBumpMapTextureManager = nullptr;
bool GgafDxGod::_is_device_lost_flg = false;
bool GgafDxGod::_adjustGameWindow = false;
HWND GgafDxGod::_pHWnd_adjustScreen = nullptr;

uint32_t GgafDxGod::_vs_v = 0;
uint32_t GgafDxGod::_ps_v = 0;

GgafDxGod::GgafDxGod() : GgafGod() {
    _is_device_lost_flg = false;
    _adjustGameWindow = false;
    _pHWnd_adjustScreen = nullptr;

    GgafDxGod::_hInstance = GetModuleHandle(0);


    CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 Seed
    GgafRgb rgb_border = GgafRgb(CONFIG::BORDER_COLOR);
    _color_border = D3DCOLOR_RGBA(rgb_border._red, rgb_border._green, rgb_border._blue, 0);
    GgafRgb rgb_bg = GgafRgb(CONFIG::BG_COLOR);
    _color_clear = D3DCOLOR_RGBA(rgb_bg._red, rgb_bg._green, rgb_bg._blue, 0);
    _pRenderTexture = nullptr;
    _pRenderTextureSurface = nullptr;
    _pRenderTextureZ = nullptr;
    _num_adapter = 1;
    _paAvailableAdapter = nullptr;
    _paAdapterRezos = nullptr;
    _apSwapChain[PRIMARY_VIEW] = nullptr;
    _apBackBuffer[PRIMARY_VIEW] = nullptr;
    _apSwapChain[SECONDARY_VIEW] = nullptr;
    _apBackBuffer[SECONDARY_VIEW] = nullptr;

    _can_wddm = true;//とりあえず

    if (CONFIG::FULL_SCREEN && CONFIG::DUAL_VIEW) {
        _primary_adapter_no = CONFIG::PRIMARY_ADAPTER_NO;
        _secondary_adapter_no = CONFIG::SECONDARY_ADAPTER_NO;
    } else {
        _primary_adapter_no = 0;
        _secondary_adapter_no = 1;
    }

    if (CONFIG::SWAP_GAME_VIEW && CONFIG::DUAL_VIEW) {
        int wk = _primary_adapter_no;
        _primary_adapter_no = _secondary_adapter_no;
        _secondary_adapter_no = wk;
    }

    _paPresetPrm = nullptr;
    _paDisplayMode = nullptr;
    _paHWnd = nullptr;
    _pModelManager = nullptr;
    _pEffectManager = nullptr;
    _pCubeMapTextureManager = nullptr;
    _pBumpMapTextureManager = nullptr;
}


void GgafDxGod::resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height) {
    RECT wRect1, cRect1; // ウィンドウ全体の矩形、クライアント領域の矩形
    pixcoord ww1, wh1; // ウィンドウ全体の幅、高さ
    pixcoord cw1, ch1; // クライアント領域の幅、高さ
    pixcoord fw1, fh1; // フレームの幅、高さ
    // ウィンドウ全体の幅・高さを計算
    GetWindowRect(hWnd, &wRect1);
    ww1 = wRect1.right - wRect1.left;
    wh1 = wRect1.bottom - wRect1.top;
    // クライアント領域の幅・高さを計算
    GetClientRect(hWnd, &cRect1);
    cw1 = cRect1.right - cRect1.left;
    ch1 = cRect1.bottom - cRect1.top;
    // クライアント領域以外に必要なサイズを計算
    fw1 = ww1 - cw1;
    fh1 = wh1 - ch1;
    // 計算した幅と高さをウィンドウに設定
    SetWindowPos(
            hWnd,
            HWND_TOP,
            0,
            0,
            client_width + fw1,
            client_height + fh1,
            SWP_NOMOVE
    );
}

void GgafDxGod::chengeViewPos(HWND prm_pHWnd, int pos) {
    if (!CONFIG::FULL_SCREEN) {
        if (CONFIG::DUAL_VIEW) {
            if (prm_pHWnd ==  GgafDxGod::_pHWndPrimary) {
                CONFIG::DUAL_VIEW_DRAW_POSITION1 = pos;
            } else if (prm_pHWnd ==  GgafDxGod::_pHWndSecondary) {
                CONFIG::DUAL_VIEW_DRAW_POSITION2 = pos;
            }
        } else {
            if (prm_pHWnd ==  GgafDxGod::_pHWndPrimary) {
                CONFIG::SINGLE_VIEW_DRAW_POSITION = pos;
            }
        }
        if (!CONFIG::FULL_SCREEN && prm_pHWnd) {
            GgafDxCore::GgafDxGod::_adjustGameWindow = true;
            GgafDxCore::GgafDxGod::_pHWnd_adjustScreen = prm_pHWnd;
        }
    }
}
void GgafDxGod::chengeViewPos1(int pos) {
    GgafDxGod::chengeViewPos(GgafDxGod::_pHWndPrimary, pos);
}
void GgafDxGod::chengeViewPos2(int pos) {
    GgafDxGod::chengeViewPos(GgafDxGod::_pHWndSecondary, pos);
}
void GgafDxGod::chengeViewAspect(bool prm_b) {
    if (!CONFIG::FULL_SCREEN) {
        CONFIG::FIXED_GAME_VIEW_ASPECT = prm_b;
        GgafDxCore::GgafDxGod::_adjustGameWindow = true;
        GgafDxCore::GgafDxGod::_pHWnd_adjustScreen = GgafDxGod::_pHWndPrimary;
    }
}
int GgafDxGod::checkAppropriateDisplaySize(GgafDxGod::RezoInfo* prm_paRezos, int prm_rezo_num,
                                           UINT prm_width, UINT prm_height) {
    _TRACE_("checkAppropriateDisplaySize() 所望解像度、"<<prm_width<<"x"<<prm_height);

    for (int n = 0; n < prm_rezo_num; n++) {
        if (prm_width == prm_paRezos[n].width && prm_height == prm_paRezos[n].height) {
            _TRACE_("["<<n<<"] でBINGO!");
            return n; //ぴったし
        }
    }
    _TRACE_("BINGOなし、近い解像度を探します。");
    int cfg_width  = (int)(prm_width * 1.1);  //解像度の高い方をやや選択しやすくするため
    int cfg_height = (int)(prm_height * 1.1); //10%水増し
    double cfg_aspect = 1.0 * cfg_width / cfg_height;

    int eval_top = INT_MAX; //評価(小さいほど良い)
    int resut_index = 0;
    for (int n = 0; n < prm_rezo_num; n++) {
        int disp_width  = (int)(prm_paRezos[n].width);
        int disp_height = (int)(prm_paRezos[n].height);
        int eval_level = ABS(disp_width-cfg_width) + (int)(ABS(disp_height-cfg_height) * cfg_aspect * 1.5); //アスペクト比をやや重視のため1.5倍
        _TRACE_("["<<n<<"] "<<disp_width<<"x"<<disp_height<<" ・・・ 評価："<<eval_level);
        if (eval_level < eval_top) {
            eval_top = eval_level;
            resut_index = n;
        }
    }
    _TRACE_("checkAppropriateDisplaySize() 結論、["<<resut_index<<"] の "<<
            prm_paRezos[resut_index].width<<"x"<<prm_paRezos[resut_index].height<<" が良さげじゃなかしら！");
    return resut_index;
}

void GgafDxGod::createWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                             const char* prm_title1   , const char* prm_title2,
                             DWORD       prm_dwStyle1 , DWORD       prm_dwStyle2,
                             HWND&       out_hWnd1    , HWND&       out_hWnd2) {

    //2011/09/18 WDDM が使用できるなら使用するように変更。
    // マルチモニタフルスクリーン時のデバイスロスト時の復旧が、
    // XPではうまくいくのにVistaではうまくいかない時があることが発覚。
    // IDirect3D9Ex の存在が気になり、試す事に至った。
    // WDDMつまり IDirect3D9Ex or IDirect3D9 の選択を行う。
    // IDirect3D9Ex を取得する Direct3DCreate9Ex() を使用し、
    // 戻り値の結果で判定すれば良いと安易に考えていたが、
    // IDirect3D9Ex の実態が、Vista 以降 の d3d9.dll にのみ存在するらしく、
    // Direct3DCreate9Ex() 関数のコードを書いた時点で、XPの場合 d3d9.dll ロード時に
    // 「エントリポイントがありません」とかいうエラーになってしまい実行すらできない。
    // コードを両対応させるには、Direct3DCreate9Ex() は使えないと思う。
    // そこで以下のように d3d9.dll から、Direct3DCreate9Ex を直接探して、ポインタを
    // 取得する方法がMSDNにあったので、参考にして実装。
    // __uuid 演算子が GCC には無いので、IDD_IDirect3D9 に変更。
    // TODO::これで正解なのだろうか…。

    HRESULT hr;
    typedef HRESULT (WINAPI *DIRECT3DCREATE9EXFUNCTION)(UINT SDKVersion, IDirect3D9Ex**);
    IDirect3D9* pID3D9 = nullptr;
    IDirect3D9Ex* pID3D9Ex = nullptr;
    HMODULE hD3D = LoadLibrary(TEXT("d3d9.dll"));

    DIRECT3DCREATE9EXFUNCTION pFunc_Direct3DCreate9Ex = (DIRECT3DCREATE9EXFUNCTION)GetProcAddress(hD3D, "Direct3DCreate9Ex");
    if (pFunc_Direct3DCreate9Ex) {
        _TRACE_("d3d9.dllに、Direct3DCreate9Exは存在しました。");
        //d3d9.dll に Direct3DCreate9Ex は存在する。
        hr = ((*pFunc_Direct3DCreate9Ex)(D3D_SDK_VERSION, &pID3D9Ex)); //Direct3DCreate9Ex 実行
        if (FAILED(hr)) {
            FreeLibrary(hD3D);
            throwGgafCriticalException("IDirect3D9Ex コンポーネント取得に失敗しました。(1)"); //失敗
        }
//        hr = pID3D9Ex->QueryInterface(IID_IDirect3D9, reinterpret_cast<void **>(&pID3D9)); //COMとして使用
//        if (FAILED(hr)) {
//            MessageBox(GgafDxGod::_pHWndPrimary, TEXT("IDirect3D9Ex コンポーネント取得に失敗しました。(2)"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
//            FreeLibrary(hD3D);
//            return E_FAIL; //失敗
//        }
        GgafDxGod::_pID3D9 = (IDirect3D9*)pID3D9Ex;
        _can_wddm = true;
        _TRACE_("WDDM モード");
    } else {
        _TRACE_("d3d9.dllに、Direct3DCreate9Exは存在しませんでした。");
        //d3d9.dll に Direct3DCreate9Ex は存在しない。
        pID3D9 = Direct3DCreate9(D3D_SDK_VERSION);
        if (!pID3D9) {
            FreeLibrary(hD3D);
            throwGgafCriticalException("IDirect3D9 コンポーネント取得に失敗しました。");
        }
        GgafDxGod::_pID3D9 = pID3D9;
        _can_wddm = false;
        _TRACE_("XPDM モード");
    }
    FreeLibrary(hD3D);

    //デバイスパラメータ作成
    D3DCAPS9 caps;
    GgafDxGod::_pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] ディスプレイ アダプタを示す序数。
                                      D3DDEVTYPE_HAL,     // [in] デバイスの種類。 D3DDEVTYPE列挙型のメンバ
                                      &caps);             // [out] デバイスの能力が格納される

    _num_adapter = caps.NumberOfAdaptersInGroup;   //使えるアダプタの数取得
    _TRACE_("_num_adapter = "<< _num_adapter);
    if (CONFIG::FULL_SCREEN && CONFIG::DUAL_VIEW) {
        if (_num_adapter < 2) {
            _TRACE_("＜警告＞２画面フルスクリーン設定ですが、マルチモニタを検出できません。強制的に１画面フルスクリーンで起動します");
            MessageBox(GgafDxGod::_pHWndPrimary,
                       "＜警告＞２画面フルスクリーン設定ですが、マルチモニタを検出できません。\n強制的に１画面フルスクリーンで起動します",
                       "WARNING", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
            _primary_adapter_no = 0;
            _secondary_adapter_no = 1;
            CONFIG::DUAL_VIEW = false;
            CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH_BK  = CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH;
            CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT_BK = CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
            CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH     = CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH;
            CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT    = CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
        } else {
            if (_num_adapter < CONFIG::PRIMARY_ADAPTER_NO+1 || _num_adapter < CONFIG::SECONDARY_ADAPTER_NO+1) {
                throwGgafCriticalException("範囲外のディスプレイアダプタ番号を指定しています。アダプタ番号は 0〜"<<_num_adapter-1<<" が有効です。\n"
                                           "PRIMARY_ADAPTER_NO="<<CONFIG::PRIMARY_ADAPTER_NO<<", "
                                           "SECONDARY_ADAPTER_NO="<<CONFIG::SECONDARY_ADAPTER_NO );
            }
        }
    }

    _paPresetPrm = NEW D3DPRESENT_PARAMETERS[_num_adapter > 2 ? _num_adapter : 2];
    ZeroMemory(&_paPresetPrm[_primary_adapter_no], sizeof(D3DPRESENT_PARAMETERS));

    //ウィンドウ時・フルスクリーン時共通
    _paPresetPrm[_primary_adapter_no].BackBufferCount        = 1;            //バックバッファの数
    _paPresetPrm[_primary_adapter_no].EnableAutoDepthStencil = TRUE;         //バックバッファの Zバッファの自動作成
    _paPresetPrm[_primary_adapter_no].AutoDepthStencilFormat = D3DFMT_D24S8; //深度ステンシルバッファ //D3DFMT_D16;
    _paPresetPrm[_primary_adapter_no].Flags                  = 0;            //0にしておく

    if (CONFIG::FULL_SCREEN) {

        //フルスクリーン時
        _paPresetPrm[_primary_adapter_no].BackBufferFormat           = D3DFMT_X8R8G8B8; //D3DFMT_A8R8G8B8; //D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;
        _paPresetPrm[_primary_adapter_no].Windowed                   = false; //フルスクリーンモード時
        _paPresetPrm[_primary_adapter_no].FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //リフレッシュレート
        _paPresetPrm[_primary_adapter_no].PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT; //スワップのタイミング
        _paPresetPrm[_primary_adapter_no].SwapEffect                 = D3DSWAPEFFECT_DISCARD;

        if(CONFIG::DUAL_VIEW) {
            _paPresetPrm[_secondary_adapter_no] = _paPresetPrm[_primary_adapter_no]; //ココまでを複製

            _paPresetPrm[_primary_adapter_no].EnableAutoDepthStencil = FALSE;   //Zバッファの自動作成無効
            _paPresetPrm[_secondary_adapter_no].EnableAutoDepthStencil = FALSE;
            //【メモ】
            //EnableAutoDepthStencil = FALSE;
            //とすると、レンダリングステートの D3DRS_ZENABLE が FALSE になるだけのように見える。
            //従って「無効」にしただけであり、「使用不可」ではないのだろう・・・。
        } else {
            _paPresetPrm[_primary_adapter_no].EnableAutoDepthStencil = FALSE; //Z バッファの自動作成有効
        }
    } else {
        //ウィンドウ時
        _paPresetPrm[_primary_adapter_no].BackBufferFormat           = D3DFMT_UNKNOWN; //現在の表示モードフォーマット
        _paPresetPrm[_primary_adapter_no].Windowed                   = true; //ウィンドウモード時
        _paPresetPrm[_primary_adapter_no].FullScreen_RefreshRateInHz = 0; //リフレッシュレート
        _paPresetPrm[_primary_adapter_no].PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE; //即座
        _paPresetPrm[_primary_adapter_no].SwapEffect                 = D3DSWAPEFFECT_COPY; //TODO:Windowモードはこれ一択なのか？、D3DPRESENT_INTERVAL_ONE とかためす？

        if(CONFIG::DUAL_VIEW) {
            _paPresetPrm[_secondary_adapter_no] = _paPresetPrm[_primary_adapter_no]; //ココまでを複製
            _paPresetPrm[_primary_adapter_no].EnableAutoDepthStencil = TRUE; //Z バッファの自動作成
            _paPresetPrm[_secondary_adapter_no].EnableAutoDepthStencil = TRUE;
        } else {

            _paPresetPrm[_primary_adapter_no].EnableAutoDepthStencil = TRUE; //Z バッファの自動作成
        }

//        //デスプレイモードの取得
//        D3DDISPLAYMODE structD3DDisplayMode0; //結果が格納される構造体
//        hr = GgafDxGod::_pID3D9->GetAdapterDisplayMode(0, &structD3DDisplayMode0);
//        returnWhenFailed(hr, D3D_OK, "GetAdapterDisplayMode に失敗しました。");
//        if(CONFIG::DUAL_VIEW) {
//            D3DDISPLAYMODE structD3DDisplayMode1;
//            hr = GgafDxGod::_pID3D9->GetAdapterDisplayMode(1, &structD3DDisplayMode1);
//            returnWhenFailed(hr, D3D_OK, "2画面目 GetAdapterDisplayMode に失敗しました");
//            _paPresetPrm[_primary_adapter_no].BackBufferFormat = structD3DDisplayMode0.Format; //現在の画面モードを利用
//            _paPresetPrm[_secondary_adapter_no].BackBufferFormat = structD3DDisplayMode1.Format; //現在の画面モードを利用
//        } else {
//            _paPresetPrm[_primary_adapter_no].BackBufferFormat = structD3DDisplayMode0.Format; //現在の画面モードを利用
//            _paPresetPrm[_secondary_adapter_no].BackBufferFormat = D3DFMT_UNKNOWN; //現在の画面モードを利用
//        }
    }

    //アンチアイリアスにできるかチェック
    DWORD qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;
//    if( SUCCEEDED(GgafDxGod::_pID3D9->CheckDeviceMultiSampleType(
//        D3DADAPTER_DEFAULT,
//        D3DDEVTYPE_HAL,
//        _paPresetPrm[_primary_adapter_no].BackBufferFormat,  //TODO:ウィンドウモード時は
//        CONFIG::FULL_SCREEN ? FALSE : TRUE,
//        D3DMULTISAMPLE_2_SAMPLES,
//        &qualityLevels) ) )
//    {
//        if( SUCCEEDED(GgafDxGod::_pID3D9->CheckDeviceMultiSampleType(
//            D3DADAPTER_DEFAULT,
//            D3DDEVTYPE_HAL,
//            _paPresetPrm[_primary_adapter_no].AutoDepthStencilFormat,
//            CONFIG::FULL_SCREEN ? FALSE : TRUE,
//            D3DMULTISAMPLE_2_SAMPLES,
//            nullptr) ) )
//        {
//            multiSampleType = D3DMULTISAMPLE_2_SAMPLES;
//            _TRACE_("ハードウェア MultiSampleType = D3DMULTISAMPLE_2_SAMPLES 有効！！");
//        } else {
//            multiSampleType = D3DMULTISAMPLE_NONE;
//            qualityLevels = D3DMULTISAMPLE_NONE;
//        }
//    } else {
//        multiSampleType = D3DMULTISAMPLE_NONE;
//        qualityLevels = D3DMULTISAMPLE_NONE;
//    }


    if(CONFIG::DUAL_VIEW) {
        //マルチサンプルの数
        _paPresetPrm[_primary_adapter_no].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
        //マルチサンプルの品質レベル
        _paPresetPrm[_primary_adapter_no].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);
        //マルチサンプルの数
        _paPresetPrm[_secondary_adapter_no].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
        //マルチサンプルの品質レベル
        _paPresetPrm[_secondary_adapter_no].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);
    } else {
        //マルチサンプルの数
        _paPresetPrm[_primary_adapter_no].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
        //マルチサンプルの品質レベル
        _paPresetPrm[_primary_adapter_no].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);
    }

    //マルチサンプルの数
    //_paPresetPrm[_primary_adapter_no].MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;//D3DMULTISAMPLE_NONE;
    //マルチサンプルの品質レベル
    //_paPresetPrm[_primary_adapter_no].MultiSampleQuality = 0;//qualityLevels - (qualityLevels > 0 ? 1 : 0);


    //バックバッファサイズ
    if (CONFIG::FULL_SCREEN) {
        if(CONFIG::DUAL_VIEW) {
            //フルスクリーンモード・２画面使用 (フルスクリーンチェックで上書きされるかもしれない)
            _paPresetPrm[_primary_adapter_no].BackBufferWidth  = CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH;
            _paPresetPrm[_primary_adapter_no].BackBufferHeight = CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
            _paPresetPrm[_secondary_adapter_no].BackBufferWidth  = CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH;
            _paPresetPrm[_secondary_adapter_no].BackBufferHeight = CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT;
        } else {
            //フルスクリーンモード・１画面使用 (フルスクリーンチェックで上書きされるかもしれない)
            _paPresetPrm[_primary_adapter_no].BackBufferWidth  = CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH;
            _paPresetPrm[_primary_adapter_no].BackBufferHeight = CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
            _paPresetPrm[_secondary_adapter_no].BackBufferWidth  = 0;
            _paPresetPrm[_secondary_adapter_no].BackBufferHeight = 0;
        }
    } else {
        if(CONFIG::DUAL_VIEW) {
            //ウィンドウモード・２画面使用
            _paPresetPrm[_primary_adapter_no].BackBufferWidth  = CONFIG::RENDER_TARGET_BUFFER_WIDTH;
            _paPresetPrm[_primary_adapter_no].BackBufferHeight = CONFIG::RENDER_TARGET_BUFFER_HEIGHT;
            _paPresetPrm[_secondary_adapter_no].BackBufferWidth  = 0;
            _paPresetPrm[_secondary_adapter_no].BackBufferHeight = 0;
        } else {
            //ウィンドウモード・１画面使用
            _paPresetPrm[_primary_adapter_no].BackBufferWidth  = CONFIG::RENDER_TARGET_BUFFER_WIDTH;
            _paPresetPrm[_primary_adapter_no].BackBufferHeight = CONFIG::RENDER_TARGET_BUFFER_HEIGHT;
            _paPresetPrm[_secondary_adapter_no].BackBufferWidth  = 0;
            _paPresetPrm[_secondary_adapter_no].BackBufferHeight = 0;
        }
    }

    _paDisplayMode = NEW D3DDISPLAYMODEEX[_num_adapter > 2 ? _num_adapter : 2];
    _paDisplayMode[_primary_adapter_no].Size = sizeof(_paDisplayMode[_primary_adapter_no]);
    _paDisplayMode[_primary_adapter_no].Width = _paPresetPrm[_primary_adapter_no].BackBufferWidth;
    _paDisplayMode[_primary_adapter_no].Height = _paPresetPrm[_primary_adapter_no].BackBufferHeight;
    _paDisplayMode[_primary_adapter_no].Format = _paPresetPrm[_primary_adapter_no].BackBufferFormat;
    _paDisplayMode[_primary_adapter_no].RefreshRate = _paPresetPrm[_primary_adapter_no].FullScreen_RefreshRateInHz;
    _paDisplayMode[_primary_adapter_no].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

    _paDisplayMode[_secondary_adapter_no].Size = sizeof(_paDisplayMode[_secondary_adapter_no]);
    _paDisplayMode[_secondary_adapter_no].Width = _paPresetPrm[_secondary_adapter_no].BackBufferWidth;
    _paDisplayMode[_secondary_adapter_no].Height = _paPresetPrm[_secondary_adapter_no].BackBufferHeight;
    _paDisplayMode[_secondary_adapter_no].Format = _paPresetPrm[_secondary_adapter_no].BackBufferFormat;
    _paDisplayMode[_secondary_adapter_no].RefreshRate = _paPresetPrm[_secondary_adapter_no].FullScreen_RefreshRateInHz;
    _paDisplayMode[_secondary_adapter_no].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

    //フルスクリーン時３画面目以降のパラメータを１画面のパラメータのコピーで作成
    for (int i = 0; i < _num_adapter; i++) {
        if (i != _primary_adapter_no && i != _secondary_adapter_no) {
            _paPresetPrm[i] = _paPresetPrm[_primary_adapter_no];
            _paDisplayMode[i] = _paDisplayMode[_primary_adapter_no];
        }
    }

    //アダプタ情報格納
    _paAvailableAdapter = NEW Adapter[_num_adapter];
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        _paAvailableAdapter[adapter_no].hMonitor = GgafDxGod::_pID3D9->GetAdapterMonitor(adapter_no);
        int mode_num = GgafDxGod::_pID3D9->GetAdapterModeCount(adapter_no, D3DFMT_X8R8G8B8);
        _paAvailableAdapter[adapter_no].setModeNum(mode_num);
        D3DDISPLAYMODE* paMode = _paAvailableAdapter[adapter_no].paModes;
        for (int n = 0; n < mode_num; n++) {
            GgafDxGod::_pID3D9->EnumAdapterModes(adapter_no, D3DFMT_X8R8G8B8, n, &(paMode[n]));
        }
    }

    //解像度情報格納
    _paAdapterRezos = NEW AdapterRezos[_num_adapter];
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        std::vector<UINT> vecWidth;
        std::vector<UINT> vecHeight;
        std::vector<std::string> vecRezo;
        int mode_num = _paAvailableAdapter[adapter_no].mode_num;
        D3DDISPLAYMODE* paMode = pGOD->_paAvailableAdapter[adapter_no].paModes;
        _TRACE_("画面["<<adapter_no<<"] mode_num="<<mode_num);
        for (int n = 0; n < mode_num; n++) {
            UINT width = paMode[n].Width;
            UINT height = paMode[n].Height;
            D3DFORMAT format = paMode[n].Format;
            std::ostringstream oss;
            oss << width << "X" << height;
            std::string rezo = oss.str();
            if (std::find(vecRezo.begin(), vecRezo.end(), rezo) == vecRezo.end()) {
                vecRezo.push_back(rezo);
                vecWidth.push_back(width);
                vecHeight.push_back(height);
            }
        }
        _paAdapterRezos[adapter_no].init(vecRezo.size());
        for (int n = 0; n < vecRezo.size(); n++) {
            //存在していない
            _paAdapterRezos[adapter_no].paRezoInfo[n].width = vecWidth[n];
            _paAdapterRezos[adapter_no].paRezoInfo[n].height = vecHeight[n];
            _paAdapterRezos[adapter_no].paRezoInfo[n].item_str = vecRezo[n];
        }
    }

    _TRACE_("利用可能画面解像度一覧");

    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        for (int n = 0; n < _paAdapterRezos[adapter_no].rezo_num; n++) {
            RezoInfo* pMode = _paAdapterRezos[adapter_no].paRezoInfo;
            _TRACE_("["<<adapter_no<<"]["<<n<<"]="<<(pMode[n].width)<<","<<(pMode[n].height)<<" = "<<(pMode[n].item_str));
        }
    }
    _TRACE_("------------------------------------------------");

    //フルスクリーン要求時、指定解像度に出来るか調べ、
    //出来ない場合は、近い解像度を探し、
    //_paPresetPrm[] と、_paDisplayMode[] を上書きする。
    EnumDisplayMonitors(nullptr, nullptr, GgafDxGod::updateMoniterPixcoordCallback, (LPARAM)this);

    if (CONFIG::FULL_SCREEN) {
        for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
            _TRACE_("--- " << adapter_no+1 << "画面目 の解像度設定 --->");
            int rezo_num = _paAdapterRezos[adapter_no].rezo_num;
            RezoInfo* paRezos = _paAdapterRezos[adapter_no].paRezoInfo;

            if (CONFIG::DUAL_VIEW) {
                //２画面フルスクリーン時
                if (adapter_no == _primary_adapter_no) {
                    //ゲーム画面１画面目
                    int n = checkAppropriateDisplaySize(
                                paRezos, rezo_num,
                                (UINT)CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH,
                                (UINT)CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT
                            );
                    CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH  = (pixcoord)(paRezos[n].width);
                    CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT = (pixcoord)(paRezos[n].height);
                    _paPresetPrm[_primary_adapter_no].BackBufferWidth  = CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH;
                    _paPresetPrm[_primary_adapter_no].BackBufferHeight = CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
                    _TRACE_("ゲーム画面１画面目(adapter_no="<<adapter_no<<")は、"<<paRezos[n].width<<"x"<<paRezos[n].height<<" に設定");
                } else if (adapter_no == _secondary_adapter_no) {
                    //ゲーム画面２画面目
                    int n = checkAppropriateDisplaySize(
                                paRezos, rezo_num,
                                (UINT)CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH,
                                (UINT)CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT
                            );
                    CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH  = (pixcoord)(paRezos[n].width);
                    CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT = (pixcoord)(paRezos[n].height);
                    _paPresetPrm[_secondary_adapter_no].BackBufferWidth  = CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH;
                    _paPresetPrm[_secondary_adapter_no].BackBufferHeight = CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT;
                    _TRACE_("ゲーム画面２画面目(adapter_no="<<adapter_no<<")は、"<<paRezos[n].width<<"x"<<paRezos[n].height<<" に設定");
                } else {
                    //メモ：ゲーム画面３画面目以降１画面目・２画面目の解像度は、現状の解像度をそのまま設定。
                    pixcoord width = _paAvailableAdapter[adapter_no].rcMonitor.right -  _paAvailableAdapter[adapter_no].rcMonitor.left;
                    pixcoord height = _paAvailableAdapter[adapter_no].rcMonitor.bottom -  _paAvailableAdapter[adapter_no].rcMonitor.top;
                    _paPresetPrm[adapter_no].BackBufferWidth  = width;
                    _paPresetPrm[adapter_no].BackBufferHeight = height;
                    _TRACE_("adapter_no="<<adapter_no << "の画面は、現状の "<<width<<"x"<<height<<" に設定");
                }

            } else {
                //１画面フルスクリーン時
                if (adapter_no == _primary_adapter_no) {
                    int n = checkAppropriateDisplaySize(
                                paRezos, rezo_num,
                                (UINT)CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH,
                                (UINT)CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT
                            );
                    CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH = (pixcoord)(paRezos[n].width);
                    CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT = (pixcoord)(paRezos[n].height);
                    _paPresetPrm[_primary_adapter_no].BackBufferWidth  = CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH;
                    _paPresetPrm[_primary_adapter_no].BackBufferHeight = CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
                } else {
                    _paPresetPrm[adapter_no].BackBufferWidth  = 0;
                    _paPresetPrm[adapter_no].BackBufferHeight = 0;
                }

            }
            //上書き更新
            _paDisplayMode[adapter_no].Width  = _paPresetPrm[adapter_no].BackBufferWidth;
            _paDisplayMode[adapter_no].Height = _paPresetPrm[adapter_no].BackBufferHeight;
            _TRACE_("<---" << adapter_no+1 << "画面目の解像度は、"<<_paDisplayMode[adapter_no].Width<<"x"<<_paDisplayMode[adapter_no].Height<<"に確定しました。");
        }
    }

    //[メモ：RECT構造体]
    //引数に使用するRECT構造体のメンバ right, bottom は「右下座標」となっているが表現が正確ではない。
    //実際の定義は
    //rect.right = rect.left + 矩形幅;
    //rect.bottom = rect.top + 矩形高さ;
    //つまり (10,10)-(17,17) 領域は、RECT(10,10,18,18) と指定するのが意図した使用方法らしい。
    //ややこしい、しかし、辺の長さを求める場合は便利である。
    //（※本当の右下座標は、right, bottom の -1 の値になる）
    _rectGameBuffer.left   = 0;
    _rectGameBuffer.top    = 0;
    _rectGameBuffer.right  = _rectGameBuffer.left + CONFIG::GAME_BUFFER_WIDTH;
    _rectGameBuffer.bottom = _rectGameBuffer.top  + CONFIG::GAME_BUFFER_HEIGHT;

    _rectRenderTargetBuffer.left   = (CONFIG::RENDER_TARGET_BUFFER_WIDTH / 2.0) - (CONFIG::VIEW_SOURCE_BUFFER_WIDTH / 2.0);
    _rectRenderTargetBuffer.top    = (CONFIG::RENDER_TARGET_BUFFER_HEIGHT / 2.0) - (CONFIG::VIEW_SOURCE_BUFFER_HEIGHT / 2.0);
    _rectRenderTargetBuffer.right  = _rectRenderTargetBuffer.left + CONFIG::VIEW_SOURCE_BUFFER_WIDTH;
    _rectRenderTargetBuffer.bottom = _rectRenderTargetBuffer.top  + CONFIG::VIEW_SOURCE_BUFFER_HEIGHT;

    _aRect_HarfGameBuffer[PRIMARY_VIEW].left   = 0;
    _aRect_HarfGameBuffer[PRIMARY_VIEW].top    = 0;
    _aRect_HarfGameBuffer[PRIMARY_VIEW].right  = _aRect_HarfGameBuffer[PRIMARY_VIEW].left  + CONFIG::GAME_BUFFER_WIDTH/2;
    _aRect_HarfGameBuffer[PRIMARY_VIEW].bottom = _aRect_HarfGameBuffer[PRIMARY_VIEW].top + CONFIG::GAME_BUFFER_HEIGHT;

    _aRect_HarfGameBuffer[SECONDARY_VIEW].left   = CONFIG::GAME_BUFFER_WIDTH/2;
    _aRect_HarfGameBuffer[SECONDARY_VIEW].top    = 0;
    _aRect_HarfGameBuffer[SECONDARY_VIEW].right  = _aRect_HarfGameBuffer[SECONDARY_VIEW].left + CONFIG::GAME_BUFFER_WIDTH/2;
    _aRect_HarfGameBuffer[SECONDARY_VIEW].bottom = _aRect_HarfGameBuffer[SECONDARY_VIEW].top  + CONFIG::GAME_BUFFER_HEIGHT;

    _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left   = (CONFIG::RENDER_TARGET_BUFFER_WIDTH - CONFIG::VIEW_SOURCE_BUFFER_WIDTH) / 2;
    _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top    = (CONFIG::RENDER_TARGET_BUFFER_HEIGHT / 2.0) - (CONFIG::VIEW_SOURCE_BUFFER_HEIGHT / 2.0);
    _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].right  = _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left + CONFIG::VIEW_SOURCE_BUFFER_WIDTH/2;
    _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].bottom = _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top  + CONFIG::VIEW_SOURCE_BUFFER_HEIGHT;

    _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].left   = CONFIG::RENDER_TARGET_BUFFER_WIDTH/2;
    _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].top    = (CONFIG::RENDER_TARGET_BUFFER_HEIGHT / 2.0) - (CONFIG::VIEW_SOURCE_BUFFER_HEIGHT / 2.0);
    _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].right  = _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].left + CONFIG::VIEW_SOURCE_BUFFER_WIDTH/2;
    _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].bottom = _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].top  + CONFIG::VIEW_SOURCE_BUFFER_HEIGHT;

    //表示領域設定
    if (CONFIG::FULL_SCREEN) {
        //フルスクリーンモード
        if (CONFIG::DUAL_VIEW) {
            _aRect_ViewScreen[PRIMARY_VIEW].top    = 0;
            _aRect_ViewScreen[PRIMARY_VIEW].left   = 0;
            _aRect_ViewScreen[PRIMARY_VIEW].right  = CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH;
            _aRect_ViewScreen[PRIMARY_VIEW].bottom = CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
            _aRect_ViewScreen[SECONDARY_VIEW].top    = 0;
            _aRect_ViewScreen[SECONDARY_VIEW].left   = 0;
            _aRect_ViewScreen[SECONDARY_VIEW].right  = CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH;
            _aRect_ViewScreen[SECONDARY_VIEW].bottom = CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT;

            //「フルスクリーンモード・２画面使用・RENDER_TARGET_BUFFERサイズ無視
            if (CONFIG::FIXED_GAME_VIEW_ASPECT) {
                //「フルスクリーンモード・２画面使用・縦横比FIX」の１画面目フロントバッファ描画領域
                LONG fix_width = CONFIG::GAME_BUFFER_WIDTH*CONFIG::VIEW1_WIDTH_RATIO/2;
                LONG fix_height = CONFIG::GAME_BUFFER_HEIGHT*CONFIG::VIEW1_HEIGHT_RATIO;
                if (1.0f * CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH / CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[PRIMARY_VIEW].left   = (CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[PRIMARY_VIEW].top    = 0;
                    _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH / fix_width; //縮小率=横幅の比率
                    _aRect_Present[PRIMARY_VIEW].left   = 0;
                    _aRect_Present[PRIMARY_VIEW].top    = (CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                }
                //「フルスクリーンモード・２画面使用・縦横比FIX」の２画面目フロントバッファ描画領域
                fix_width = CONFIG::GAME_BUFFER_WIDTH*CONFIG::VIEW2_WIDTH_RATIO/2;
                fix_height = CONFIG::GAME_BUFFER_HEIGHT*CONFIG::VIEW2_HEIGHT_RATIO;
                if (1.0f * CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH / CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[SECONDARY_VIEW].left   = (CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[SECONDARY_VIEW].top    = 0;
                    _aRect_Present[SECONDARY_VIEW].right  = _aRect_Present[SECONDARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[SECONDARY_VIEW].bottom = _aRect_Present[SECONDARY_VIEW].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH / fix_width; //縮小率=横幅の比率
                    _aRect_Present[SECONDARY_VIEW].left   = 0;
                    _aRect_Present[SECONDARY_VIEW].top    = (CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[SECONDARY_VIEW].right  = _aRect_Present[SECONDARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[SECONDARY_VIEW].bottom = _aRect_Present[SECONDARY_VIEW].top  + (fix_height * rate);
                }
                setPositionPresentRect(CONFIG::DUAL_VIEW_DRAW_POSITION1, _aRect_Present[PRIMARY_VIEW],
                                       CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH, CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT);
                setPositionPresentRect(CONFIG::DUAL_VIEW_DRAW_POSITION2, _aRect_Present[SECONDARY_VIEW],
                                       CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH, CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT);
            } else {
                //「フルスクリーンモード・２画面使用・縦横比ストレッチ」の１画面目フロントバッファ描画領域
                _aRect_Present[PRIMARY_VIEW].left   = 0;
                _aRect_Present[PRIMARY_VIEW].top    = 0;
                _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + CONFIG::DUAL_VIEW_FULL_SCREEN1_WIDTH;
                _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + CONFIG::DUAL_VIEW_FULL_SCREEN1_HEIGHT;
                //「フルスクリーンモード・２画面使用・縦横比ストレッチ」の２画面目フロントバッファ描画領域
                _aRect_Present[SECONDARY_VIEW].left   = 0;
                _aRect_Present[SECONDARY_VIEW].top    = 0;
                _aRect_Present[SECONDARY_VIEW].right  = _aRect_Present[SECONDARY_VIEW].left + CONFIG::DUAL_VIEW_FULL_SCREEN2_WIDTH;
                _aRect_Present[SECONDARY_VIEW].bottom = _aRect_Present[SECONDARY_VIEW].top  + CONFIG::DUAL_VIEW_FULL_SCREEN2_HEIGHT;
            }
        } else {
            //フルスクリーンモード・１画面使用
            _aRect_ViewScreen[PRIMARY_VIEW].top    = 0;
            _aRect_ViewScreen[PRIMARY_VIEW].left   = 0;
            _aRect_ViewScreen[PRIMARY_VIEW].right  = CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH;
            _aRect_ViewScreen[PRIMARY_VIEW].bottom = CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
            _aRect_ViewScreen[SECONDARY_VIEW] = _aRect_ViewScreen[PRIMARY_VIEW];

            //「フルスクリーンモード・１画面使用・RENDER_TARGET_BUFFERサイズ無視」
            if (CONFIG::FIXED_GAME_VIEW_ASPECT) {
                //「フルスクリーンモード・１画面使用・縦横比FIX」のフロントバッファ描画領域
                LONG fix_width = CONFIG::GAME_BUFFER_WIDTH*CONFIG::VIEW1_WIDTH_RATIO;
                LONG fix_height = CONFIG::GAME_BUFFER_HEIGHT*CONFIG::VIEW1_HEIGHT_RATIO;
                if (1.0f * CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH / CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[PRIMARY_VIEW].left   = (CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[PRIMARY_VIEW].top    = 0;
                    _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH / fix_width; //縮小率=横幅の比率
                    _aRect_Present[PRIMARY_VIEW].left   = 0;
                    _aRect_Present[PRIMARY_VIEW].top    = (CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                }
                _aRect_Present[SECONDARY_VIEW] = _aRect_Present[PRIMARY_VIEW];
                setPositionPresentRect(CONFIG::SINGLE_VIEW_DRAW_POSITION, _aRect_Present[PRIMARY_VIEW],
                                       CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH, CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT);
                setPositionPresentRect(CONFIG::SINGLE_VIEW_DRAW_POSITION, _aRect_Present[SECONDARY_VIEW],
                                       CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH, CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT);
            } else {
                //「フルスクリーンモード・１画面使用・縦横比ストレッチ」のフロントバッファ描画領域
                _aRect_Present[PRIMARY_VIEW].left   = 0;
                _aRect_Present[PRIMARY_VIEW].top    = 0;
                _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + CONFIG::SINGLE_VIEW_FULL_SCREEN_WIDTH;
                _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + CONFIG::SINGLE_VIEW_FULL_SCREEN_HEIGHT;
                _aRect_Present[SECONDARY_VIEW] = _aRect_Present[PRIMARY_VIEW];
            }

        }
    } else {
        //ウィンドウモード
        if (CONFIG::DUAL_VIEW) {
            //ウィンドウモード・２窓使用
            if (CONFIG::FIXED_GAME_VIEW_ASPECT) {
                LONG fix_width = CONFIG::VIEW_SOURCE_BUFFER_WIDTH*CONFIG::VIEW1_WIDTH_RATIO/2;
                LONG fix_height = CONFIG::VIEW_SOURCE_BUFFER_HEIGHT*CONFIG::VIEW1_HEIGHT_RATIO;
                //「ウィンドウモード・２窓使用・縦横比FIX・ピクセルストレッチ」の１窓目フロントバッファ描画領域
                if (1.0f * CONFIG::DUAL_VIEW_WINDOW1_WIDTH / CONFIG::DUAL_VIEW_WINDOW1_HEIGHT > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CONFIG::DUAL_VIEW_WINDOW1_HEIGHT / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[PRIMARY_VIEW].left   = (CONFIG::DUAL_VIEW_WINDOW1_WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[PRIMARY_VIEW].top    = 0;
                    _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CONFIG::DUAL_VIEW_WINDOW1_WIDTH / fix_width; //縮小率=横幅の比率
                    _aRect_Present[PRIMARY_VIEW].left   = 0;
                    _aRect_Present[PRIMARY_VIEW].top    = (CONFIG::DUAL_VIEW_WINDOW1_HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                }

                fix_width = CONFIG::VIEW_SOURCE_BUFFER_WIDTH*CONFIG::VIEW2_WIDTH_RATIO/2;
                fix_height = CONFIG::VIEW_SOURCE_BUFFER_HEIGHT*CONFIG::VIEW2_HEIGHT_RATIO;
                //「ウィンドウモード・２窓使用・縦横比FIX」の２窓目フロントバッファ描画領域
                if (1.0f * CONFIG::DUAL_VIEW_WINDOW2_WIDTH / CONFIG::DUAL_VIEW_WINDOW2_HEIGHT > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CONFIG::DUAL_VIEW_WINDOW2_HEIGHT / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[SECONDARY_VIEW].left   = (CONFIG::DUAL_VIEW_WINDOW2_WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[SECONDARY_VIEW].top    = 0;
                    _aRect_Present[SECONDARY_VIEW].right  = _aRect_Present[SECONDARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[SECONDARY_VIEW].bottom = _aRect_Present[SECONDARY_VIEW].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CONFIG::DUAL_VIEW_WINDOW2_WIDTH / fix_width; //縮小率=横幅の比率
                    _aRect_Present[SECONDARY_VIEW].left   = 0;
                    _aRect_Present[SECONDARY_VIEW].top    = (CONFIG::DUAL_VIEW_WINDOW2_HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[SECONDARY_VIEW].right  = _aRect_Present[SECONDARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[SECONDARY_VIEW].bottom = _aRect_Present[SECONDARY_VIEW].top  + (fix_height * rate);
                }

                setPositionPresentRect(CONFIG::DUAL_VIEW_DRAW_POSITION1, _aRect_Present[PRIMARY_VIEW],
                                       CONFIG::DUAL_VIEW_WINDOW1_WIDTH, CONFIG::DUAL_VIEW_WINDOW1_HEIGHT);
                setPositionPresentRect(CONFIG::DUAL_VIEW_DRAW_POSITION2, _aRect_Present[SECONDARY_VIEW],
                                       CONFIG::DUAL_VIEW_WINDOW2_WIDTH, CONFIG::DUAL_VIEW_WINDOW2_HEIGHT);
            } else {
                //「ウィンドウモード・２窓使用・縦横比ストレッチ」の１窓目フロントバッファ描画領域
                _aRect_Present[PRIMARY_VIEW].left   = 0;
                _aRect_Present[PRIMARY_VIEW].top    = 0;
                _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + CONFIG::DUAL_VIEW_WINDOW1_WIDTH;
                _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + CONFIG::DUAL_VIEW_WINDOW1_HEIGHT;
                //「ウィンドウモード・２窓使用・縦横比ストレッチ」の２窓目フロントバッファ描画領域
                _aRect_Present[SECONDARY_VIEW].left   = 0;
                _aRect_Present[SECONDARY_VIEW].top    = 0;
                _aRect_Present[SECONDARY_VIEW].right  = _aRect_Present[SECONDARY_VIEW].left + CONFIG::DUAL_VIEW_WINDOW2_WIDTH;
                _aRect_Present[SECONDARY_VIEW].bottom = _aRect_Present[SECONDARY_VIEW].top  + CONFIG::DUAL_VIEW_WINDOW2_HEIGHT;
            }
        } else {
            //ウィンドウモード・１窓使用
            if (CONFIG::FIXED_GAME_VIEW_ASPECT) {
                LONG fix_width = CONFIG::VIEW_SOURCE_BUFFER_WIDTH*CONFIG::VIEW2_WIDTH_RATIO;
                LONG fix_height = CONFIG::VIEW_SOURCE_BUFFER_HEIGHT*CONFIG::VIEW2_HEIGHT_RATIO;
                //「ウィンドウモード・１窓使用・縦横比FIX」のフロントバッファ描画領域
                if (1.0f * CONFIG::SINGLE_VIEW_WINDOW_WIDTH / CONFIG::SINGLE_VIEW_WINDOW_HEIGHT > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CONFIG::SINGLE_VIEW_WINDOW_HEIGHT / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[PRIMARY_VIEW].left   = (CONFIG::SINGLE_VIEW_WINDOW_WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[PRIMARY_VIEW].top    = 0;
                    _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CONFIG::SINGLE_VIEW_WINDOW_WIDTH / fix_width; //縮小率=横幅の比率
                    _aRect_Present[PRIMARY_VIEW].left   = 0;
                    _aRect_Present[PRIMARY_VIEW].top    = (CONFIG::SINGLE_VIEW_WINDOW_HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                    _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                }
                _aRect_Present[SECONDARY_VIEW] = _aRect_Present[PRIMARY_VIEW];
                setPositionPresentRect(CONFIG::SINGLE_VIEW_DRAW_POSITION, _aRect_Present[PRIMARY_VIEW],
                                       CONFIG::SINGLE_VIEW_WINDOW_WIDTH, CONFIG::SINGLE_VIEW_WINDOW_HEIGHT);
                setPositionPresentRect(CONFIG::SINGLE_VIEW_DRAW_POSITION, _aRect_Present[SECONDARY_VIEW],
                                       CONFIG::SINGLE_VIEW_WINDOW_WIDTH, CONFIG::SINGLE_VIEW_WINDOW_HEIGHT);
            } else {
                //「ウィンドウモード・１窓使用・縦横比ストレッチ」のフロントバッファ描画領域
                _aRect_Present[PRIMARY_VIEW].left   = 0;
                _aRect_Present[PRIMARY_VIEW].top    = 0;
                _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + CONFIG::SINGLE_VIEW_WINDOW_WIDTH;
                _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + CONFIG::SINGLE_VIEW_WINDOW_HEIGHT;
                _aRect_Present[SECONDARY_VIEW] = _aRect_Present[PRIMARY_VIEW];
            }
        }
    }

#ifdef MY_DEBUG
    _TRACE_("初期設定");
    if (CONFIG::DUAL_VIEW) {
        _TRACE_(" _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left   = "<<_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left  );
        _TRACE_(" _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top    = "<<_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top   );
        _TRACE_(" _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].right  = "<<_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].right );
        _TRACE_(" _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].bottom = "<<_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].bottom);
        _TRACE_(" _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].left   = "<<_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].left  );
        _TRACE_(" _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].top    = "<<_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].top   );
        _TRACE_(" _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].right  = "<<_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].right );
        _TRACE_(" _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].bottom = "<<_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].bottom);
        _TRACE_(" _aRect_Present[PRIMARY_VIEW].left   = "<<_aRect_Present[PRIMARY_VIEW].left  );
        _TRACE_(" _aRect_Present[PRIMARY_VIEW].top    = "<<_aRect_Present[PRIMARY_VIEW].top   );
        _TRACE_(" _aRect_Present[PRIMARY_VIEW].right  = "<<_aRect_Present[PRIMARY_VIEW].right );
        _TRACE_(" _aRect_Present[PRIMARY_VIEW].bottom = "<<_aRect_Present[PRIMARY_VIEW].bottom);
        _TRACE_(" _aRect_Present[SECONDARY_VIEW].left   = "<<_aRect_Present[SECONDARY_VIEW].left  );
        _TRACE_(" _aRect_Present[SECONDARY_VIEW].top    = "<<_aRect_Present[SECONDARY_VIEW].top   );
        _TRACE_(" _aRect_Present[SECONDARY_VIEW].right  = "<<_aRect_Present[SECONDARY_VIEW].right );
        _TRACE_(" _aRect_Present[SECONDARY_VIEW].bottom = "<<_aRect_Present[SECONDARY_VIEW].bottom);
    } else {
        _TRACE_(" _rectRenderTargetBuffer.left   = "<<_rectRenderTargetBuffer.left  );
        _TRACE_(" _rectRenderTargetBuffer.top    = "<<_rectRenderTargetBuffer.top   );
        _TRACE_(" _rectRenderTargetBuffer.right  = "<<_rectRenderTargetBuffer.right );
        _TRACE_(" _rectRenderTargetBuffer.bottom = "<<_rectRenderTargetBuffer.bottom);
        _TRACE_(" _aRect_Present[PRIMARY_VIEW].left   = "<<_aRect_Present[PRIMARY_VIEW].left  );
        _TRACE_(" _aRect_Present[PRIMARY_VIEW].top    = "<<_aRect_Present[PRIMARY_VIEW].top   );
        _TRACE_(" _aRect_Present[PRIMARY_VIEW].right  = "<<_aRect_Present[PRIMARY_VIEW].right );
        _TRACE_(" _aRect_Present[PRIMARY_VIEW].bottom = "<<_aRect_Present[PRIMARY_VIEW].bottom);
    }
#endif

    _paHWnd = NEW HWND[_num_adapter > 2 ? _num_adapter : 2];
    for (int i = 0; i < (_num_adapter > 2 ? _num_adapter : 2); i++) {
        _paHWnd[i] = nullptr;
    }
    GgafCore::GgafRgb rgb = GgafCore::GgafRgb(CONFIG::BORDER_COLOR);
    prm_wndclass1.hbrBackground = CreateSolidBrush(RGB(rgb._red, rgb._green, rgb._blue));
    prm_wndclass2.hbrBackground = CreateSolidBrush(RGB(rgb._red, rgb._green, rgb._blue));
    // ウインドウの生成
    if (CONFIG::FULL_SCREEN) {
        if (CONFIG::DUAL_VIEW) {
            //フルスクリーンモード・２画面使用
            WNDCLASSEX wc = prm_wndclass2;
            wc.lpszClassName = "dummy"; //TODO:４画面時に大丈夫か要確認

            for (int n = 0; n < _num_adapter; n++) {
                if (n == _primary_adapter_no) {

                    RegisterClassEx(&prm_wndclass1);
                    _paHWnd[_primary_adapter_no] =
                            CreateWindowEx(
                                WS_EX_APPWINDOW,
                                prm_wndclass1.lpszClassName,
                                prm_title1,
                                WS_POPUP | WS_VISIBLE,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                _paPresetPrm[_primary_adapter_no].BackBufferWidth,
                                _paPresetPrm[_primary_adapter_no].BackBufferHeight,
                                HWND_DESKTOP,
                                nullptr,
                                prm_wndclass1.hInstance,
                                nullptr
                            );
                } else if (n == _secondary_adapter_no) {
                    RegisterClassEx(&prm_wndclass2);
                    _paHWnd[_secondary_adapter_no] =
                            CreateWindowEx(
                                WS_EX_APPWINDOW,
                                prm_wndclass2.lpszClassName,
                                prm_title2,
                                WS_POPUP | WS_VISIBLE,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                _paPresetPrm[_secondary_adapter_no].BackBufferWidth,
                                _paPresetPrm[_secondary_adapter_no].BackBufferHeight,
                                HWND_DESKTOP,
                                nullptr,
                                prm_wndclass2.hInstance,
                                nullptr
                           );
                } else {
                    RegisterClassEx(&wc);
                    _paHWnd[n] =
                            CreateWindowEx(
                                WS_EX_APPWINDOW,
                                wc.lpszClassName,
                                "dummy",
                                WS_POPUP | WS_VISIBLE,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                _paPresetPrm[n].BackBufferWidth,
                                _paPresetPrm[n].BackBufferHeight,
                                HWND_DESKTOP,
                                nullptr,
                                wc.hInstance,
                                nullptr
                           );
                }
            }
        } else {
            //フルスクリーンモード・１画面使用
            RegisterClassEx(&prm_wndclass1);
            _paHWnd[_primary_adapter_no] =
                    CreateWindowEx(
                        WS_EX_APPWINDOW,
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        _paPresetPrm[_primary_adapter_no].BackBufferWidth,
                        _paPresetPrm[_primary_adapter_no].BackBufferHeight,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                    );
        }
    } else {
        if (CONFIG::DUAL_VIEW) {
            //ウインドモード・２窓使用
            RegisterClassEx(&prm_wndclass1);
            _paHWnd[_primary_adapter_no] =
                    CreateWindow(
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        prm_dwStyle1,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CONFIG::DUAL_VIEW_WINDOW1_WIDTH,
                        CONFIG::DUAL_VIEW_WINDOW1_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                    );

            RegisterClassEx(&prm_wndclass2);
            _paHWnd[_secondary_adapter_no] =
                    CreateWindow(
                        prm_wndclass2.lpszClassName,
                        prm_title2,
                        prm_dwStyle2,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CONFIG::DUAL_VIEW_WINDOW2_WIDTH,
                        CONFIG::DUAL_VIEW_WINDOW2_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass2.hInstance,
                        nullptr
                    );


        } else {
            //ウインドモード・１窓使用
            RegisterClassEx(&prm_wndclass1);
            _paHWnd[_primary_adapter_no] =
                    CreateWindow(
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        prm_dwStyle1,  //枠なし WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CONFIG::SINGLE_VIEW_WINDOW_WIDTH,
                        CONFIG::SINGLE_VIEW_WINDOW_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                    );
        }
    }
    //Windowハンドルを個別指定
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        _paPresetPrm[adapter_no].hDeviceWindow = _paHWnd[adapter_no];
    }
    GgafDxGod::_pHWndSecondary = _paHWnd[_secondary_adapter_no];
    GgafDxGod::_pHWndPrimary   = _paHWnd[_primary_adapter_no];
    //GgafDxGod::_pHWndPrimary の有無が
    //ウィンドウプロシージャの WM_SETFOCUS 時の排他になっているので、
    //２画面目 → １画面目の順で代入すること。
    out_hWnd1 = GgafDxGod::_pHWndPrimary;
    out_hWnd2 = GgafDxGod::_pHWndSecondary;

    if (!GgafDxGod::_pHWndPrimary) {
        throwGgafCriticalException("ウィンドウが作成出来ませんでした。");
    }


    //ウィンドウモード時、クライアント領域を所望の大きさにするため、
    //タイトルバー、リサイズボーダーの厚さを考慮し再設定。
    if (!CONFIG::FULL_SCREEN) {
        //ウィンドウモード時
        if (CONFIG::DUAL_VIEW) {
            resetWindowsize(GgafDxGod::_pHWndPrimary  , CONFIG::DUAL_VIEW_WINDOW1_WIDTH, CONFIG::DUAL_VIEW_WINDOW1_HEIGHT);
            resetWindowsize(GgafDxGod::_pHWndSecondary, CONFIG::DUAL_VIEW_WINDOW2_WIDTH, CONFIG::DUAL_VIEW_WINDOW2_HEIGHT);
        } else {
            resetWindowsize(GgafDxGod::_pHWndPrimary  , CONFIG::SINGLE_VIEW_WINDOW_WIDTH, CONFIG::SINGLE_VIEW_WINDOW_HEIGHT);
        }
    }

    //アクティブに
    ShowWindow(GgafDxGod::_pHWndPrimary, SW_SHOWNORMAL);
    UpdateWindow(GgafDxGod::_pHWndPrimary);
    if (CONFIG::DUAL_VIEW) {
        ShowWindow(GgafDxGod::_pHWndSecondary, SW_SHOWNORMAL);
        UpdateWindow(GgafDxGod::_pHWndSecondary);
    }

    //デバイス作成
    if (FAILED(initDevice())) {
        throwGgafCriticalException("初期化に失敗しました。アプリケーションを起動出来ません。");
    }
}

void GgafDxGod::createWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                             const char* prm_title1   , const char* prm_title2,
                             HWND&       out_hWnd1    , HWND&       out_hWnd2) {
    createWindow( prm_wndclass1, prm_wndclass2,
                  prm_title1, prm_title2,
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  out_hWnd1, out_hWnd2   );
}

void GgafDxGod::createWindow(WNDCLASSEX& prm_wndclass1,
                  const char* prm_title1   ,
                  DWORD       prm_dwStyle1 ,
                  HWND&       out_hWnd1     ) {
    HWND hWnd2;
    WNDCLASSEX wcex2 = prm_wndclass1;
    wcex2.lpszClassName = "Gecchi Game App Framework (window[1])";
    createWindow( prm_wndclass1, wcex2,
                  prm_title1,    "window02",
                  prm_dwStyle1,  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  out_hWnd1,     hWnd2   );
}

void GgafDxGod::createWindow(WNDCLASSEX& prm_wndclass1,
                             const char* prm_title1   ,
                             HWND&       out_hWnd1     ) {
    createWindow( prm_wndclass1,
                  prm_title1,
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  out_hWnd1);
}

void GgafDxGod::createWindow(WNDPROC prm_WndProc,
                             const char* prm_title1, const char* prm_title2,
                             HWND&       out_hWnd1 , HWND&       out_hWnd2  ) {
    //ウィンドウ定義＆作成
    WNDCLASSEX wcex1;
    ZeroMemory(&wcex1, sizeof(WNDCLASSEX));
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    wcex1.lpfnWndProc = (WNDPROC)prm_WndProc;
    wcex1.hInstance = GgafDxGod::_hInstance;
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.lpszClassName = "Gecchi Game App Framework (window[0])";
    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "Gecchi Game App Framework (window[1])";

    createWindow( wcex1, wcex2,
                  prm_title1, prm_title2,
                  WS_OVERLAPPEDWINDOW, WS_OVERLAPPEDWINDOW,
                  out_hWnd1, out_hWnd2   );
}

void GgafDxGod::createWindow(WNDPROC prm_WndProc,
                             const char* prm_title1, const char* prm_title2) {
    HWND hWnd1, hWnd2;
    createWindow(prm_WndProc,
                 prm_title1, prm_title2,
                 hWnd1, hWnd2);
}

HRESULT GgafDxGod::initDevice() {
//    //default
//    UINT AdapterToUse = D3DADAPTER_DEFAULT;
//    D3DDEVTYPE DeviceType = D3DDEVTYPE_HAL;
//    // NVIDIA PerfHUD 用 begin --------------------------------------------->

//#ifdef MY_DEBUG
//
//#if SHIPPING_VERSION
//    // When building a shipping version, disable PerfHUD (opt-out)
//#else
//    _TRACE_("Look for 'NVIDIA PerfHUD' adapter...");
//    // If it is present, override default settings
//    for (UINT Adapter = 0; Adapter < GgafDxGod::_pID3D9->GetAdapterCount(); Adapter++) {
//        D3DADAPTER_IDENTIFIER9 Identifier;
//        HRESULT Res;
//        Res = GgafDxGod::_pID3D9->GetAdapterIdentifier(Adapter, 0, &Identifier);
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

    for (int n = 0; n < _num_adapter; n++) {
        _TRACE_("_paPresetPrm["<<n<<"].BackBufferWidth            = "<<_paPresetPrm[n].BackBufferWidth            );
        _TRACE_("_paPresetPrm["<<n<<"].BackBufferHeight           = "<<_paPresetPrm[n].BackBufferHeight           );
        _TRACE_("_paPresetPrm["<<n<<"].BackBufferFormat           = "<<_paPresetPrm[n].BackBufferFormat           );
        _TRACE_("_paPresetPrm["<<n<<"].BackBufferCount            = "<<_paPresetPrm[n].BackBufferCount            );
        _TRACE_("_paPresetPrm["<<n<<"].MultiSampleType            = "<<_paPresetPrm[n].MultiSampleType            );
        _TRACE_("_paPresetPrm["<<n<<"].MultiSampleQuality         = "<<_paPresetPrm[n].MultiSampleQuality         );
        _TRACE_("_paPresetPrm["<<n<<"].SwapEffect                 = "<<_paPresetPrm[n].SwapEffect                 );
        _TRACE_("_paPresetPrm["<<n<<"].hDeviceWindow              = "<<_paPresetPrm[n].hDeviceWindow              );
        _TRACE_("_paPresetPrm["<<n<<"].Windowed                   = "<<_paPresetPrm[n].Windowed                   );
        _TRACE_("_paPresetPrm["<<n<<"].EnableAutoDepthStencil     = "<<_paPresetPrm[n].EnableAutoDepthStencil     );
        _TRACE_("_paPresetPrm["<<n<<"].AutoDepthStencilFormat     = "<<_paPresetPrm[n].AutoDepthStencilFormat     );
        _TRACE_("_paPresetPrm["<<n<<"].Flags                      = "<<_paPresetPrm[n].Flags                      );
        _TRACE_("_paPresetPrm["<<n<<"].FullScreen_RefreshRateInHz = "<<_paPresetPrm[n].FullScreen_RefreshRateInHz );
        _TRACE_("_paPresetPrm["<<n<<"].PresentationInterval       = "<<_paPresetPrm[n].PresentationInterval       );

        _TRACE_("_paDisplayMode["<<n<<"].Size             = "<<_paDisplayMode[n].Size            );
        _TRACE_("_paDisplayMode["<<n<<"].Width            = "<<_paDisplayMode[n].Width           );
        _TRACE_("_paDisplayMode["<<n<<"].Height           = "<<_paDisplayMode[n].Height          );
        _TRACE_("_paDisplayMode["<<n<<"].RefreshRate      = "<<_paDisplayMode[n].RefreshRate     );
        _TRACE_("_paDisplayMode["<<n<<"].Format           = "<<_paDisplayMode[n].Format          );
        _TRACE_("_paDisplayMode["<<n<<"].ScanLineOrdering = "<<_paDisplayMode[n].ScanLineOrdering);
    }
    _TRACE_("GgafDxGod::_pHWndPrimary="<<GgafDxGod::_pHWndPrimary);
    _TRACE_("GgafDxGod::_pHWndSecondary="<<GgafDxGod::_pHWndSecondary);
    _TRACE_("_primary_adapter_no="<<_primary_adapter_no);
    _TRACE_("_secondary_adapter_no="<<_secondary_adapter_no);
    HRESULT hr;
    //ピクセルシェーダー、頂点シェーダーバージョンチェック
    D3DCAPS9 caps;
    GgafDxGod::_pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] ディスプレイ アダプタを示す序数。
                                      D3DDEVTYPE_HAL,     // [in] デバイスの種類。 D3DDEVTYPE列挙型のメンバ
                                      &caps);             // [out] デバイスの能力が格納される
    _vs_v = caps.VertexShaderVersion;
    _ps_v = caps.PixelShaderVersion;

    _TRACE_("Hardware Vertex Shader Version = "<<D3DSHADER_VERSION_MAJOR(_vs_v)<<"_"<<D3DSHADER_VERSION_MINOR(_vs_v));
    _TRACE_("Hardware Pixel Shader Version  = "<<D3DSHADER_VERSION_MAJOR(_ps_v)<<"_"<<D3DSHADER_VERSION_MINOR(_ps_v));
    if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
        _TRACE_("ビデオカードハードの頂点シェーダー 3_0 、ピンクセルシェーダー 3_0 以上が推奨です。");
        _TRACE_("ご使用のビデオカードでは、正しく動作しない恐れがあります。");
    }

    if (CONFIG::FULL_SCREEN && CONFIG::DUAL_VIEW) {
        //＜フルスクリーン かつ デュアルビュー の場合＞
        //デバイス作成を試み GgafDxGod::_pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
            hr = D3DERR_NOTAVAILABLE;
        } else {
            hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _paPresetPrm[0].hDeviceWindow,
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                 _paPresetPrm, _paDisplayMode);
        }
        if (hr != D3D_OK) {
            if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
                hr = D3DERR_NOTAVAILABLE;
            } else {
                hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _paPresetPrm[0].hDeviceWindow,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                     _paPresetPrm, _paDisplayMode);
            }
            if (hr != D3D_OK) {
                if (_ps_v < D3DPS_VERSION(3, 0)) {
                    hr = D3DERR_NOTAVAILABLE;
                } else {
                    //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
                    hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _paPresetPrm[0].hDeviceWindow,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                         _paPresetPrm, _paDisplayMode);
                }
                if (hr != D3D_OK) {
                    //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                    hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _paPresetPrm[0].hDeviceWindow,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                         _paPresetPrm, _paDisplayMode);
                    if (hr != D3D_OK) {
                        //どのデバイスの作成も失敗した場合
                        _TRACE_(FUNC_NAME<<" DirectXの初期化に失敗しました。マルチヘッドD3DCREATE_SOFTWARE_VERTEXPROCESSING : "<<GgafDxCriticalException::getHresultMsg(hr));
                        MessageBox(GgafDxGod::_pHWndPrimary, "DirectXの初期化に失敗しました。\nマルチヘッドディスプレイ環境が存在していません。", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
                        return E_FAIL;
                    } else {
                        _TRACE_(FUNC_NAME<<" デバイスは MULTI FULLSCRREEN REF で初期化できました。");
                    }
                } else {
                    _TRACE_(FUNC_NAME<<" デバイスは MULTI FULLSCRREEN HAL(soft vp) で初期化できました。");
                }
            } else {
                _TRACE_(FUNC_NAME<<" デバイスは MULTI FULLSCRREEN HAL(hard vp) で初期化できました。");
            }
        } else {
            _TRACE_(FUNC_NAME<<" デバイスは MULTI FULLSCRREEN HAL(pure vp) で初期化できました。");
        }

    } else {
        //＜(フルスクリーン かつ デュアルビュー) 以外の場合＞
        //デバイス作成を試み GgafDxGod::_pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
            hr = D3DERR_NOTAVAILABLE;
        } else {
            hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                 &_paPresetPrm[_primary_adapter_no], &_paDisplayMode[_primary_adapter_no]);
    //                                           D3DCREATE_MIXED_VERTEXPROCESSING|D3DCREATE_MULTITHREADED,
    //                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
        }
        if (hr != D3D_OK) {
            if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
                hr = D3DERR_NOTAVAILABLE;
            } else {
                hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                     &_paPresetPrm[_primary_adapter_no], &_paDisplayMode[_primary_adapter_no]);
            }

            if (hr != D3D_OK) {
                if (_ps_v < D3DPS_VERSION(3, 0)) {
                    hr = D3DERR_NOTAVAILABLE;
                } else {
                    //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
                    hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                         &_paPresetPrm[_primary_adapter_no], &_paDisplayMode[_primary_adapter_no]);
                }
                if (hr != D3D_OK) {
                    //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                    hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDxGod::_pHWndPrimary,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                         &_paPresetPrm[_primary_adapter_no], &_paDisplayMode[_primary_adapter_no]);
                    if (hr != D3D_OK) {
                        //どのデバイスの作成も失敗した場合
                        _TRACE_(FUNC_NAME<<" DirectXの初期化に失敗しました。 "<<GgafDxCriticalException::getHresultMsg(hr));
                        MessageBox(GgafDxGod::_pHWndPrimary, "DirectXの初期化に失敗しました。", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
                        return E_FAIL;
                    } else {
                        _TRACE_(FUNC_NAME<<" デバイスは REF で初期化できました。");
                    }
                } else {
                    _TRACE_(FUNC_NAME<<" デバイスは HAL(soft vp) で初期化できました。");
                }
            } else {
                _TRACE_(FUNC_NAME<<" デバイスは HAL(hard vp) で初期化できました。");
            }
        } else {
            _TRACE_(FUNC_NAME<<" デバイスは HAL(pure vp) で初期化できました。");
        }
    }

    //テスト
    if (_can_wddm) {
        hr = ((IDirect3DDevice9Ex*)GgafDxGod::_pID3DDevice9)->SetMaximumFrameLatency(0);
        checkDxException(hr, D3D_OK, "SetMaximumFrameLatency(0) に失敗しました。");
    }

    //その他必要な初期化
    _pCubeMapTextureManager = NEW GgafDxTextureManager("CubeMapTexManager");
    _pBumpMapTextureManager = NEW GgafDxTextureManager("BumpMapTexManager");
    _pModelManager = NEW GgafDxModelManager("ModelManager");
    _pEffectManager = NEW GgafDxEffectManager("EffectManager");
    GgafDxUtil::init();  //ユーティリティ準備
    GgafDxInput::init(); //DirectInput準備
    GgafDxSound::init(); //DirectSound準備
    GgafDx26DirectionUtil::init();
    //デバイス初期化
    hr = initDx9Device();
    if (hr == E_FAIL) {
        return E_FAIL;
    }
    Sleep(100);
    //フルスクリーン時、レンダリングターゲットテクスチャー作成
    if (CONFIG::FULL_SCREEN) {
        hr = restoreFullScreenRenderTarget();
        if (hr == E_FAIL) {
            return E_FAIL;
        }
    }

    //2011/09/28
    //TODO:VISTAで２画面フルスクリーン時、クリックでフルスクリーンが解除の対策
    //WDDMでデバイス作成し、２画面フルスクリーン時で起動した後、２画面目の領域のうち、
    //もともとの１画面目だった領域(解像度変更により２画面目へはみ出た出た部分）をクリックすると、
    //フルスクリーンが解除されてしまうことが気になった。かなりの時間を費やしたが、解決方法は見つからなかった。
    //しかし、ここでウィンドウを再構築することで、なぜか問題は回避できた。
    //たぶん、正規の方法じゃない。苦肉の策・・・。
    //2015/09/02 追記・要調査
    //あぁ、ひょっとしたら、モニタ座標情報が、フルスクリーン前の物を取得してるからだろうか・・・
    if (_can_wddm && CONFIG::FULL_SCREEN && CONFIG::DUAL_VIEW) {
        hr = releaseFullScreenRenderTarget();
        hr = restoreFullScreenRenderTarget();
    }
    return D3D_OK;
}

BOOL CALLBACK GgafDxGod::updateMoniterPixcoordCallback(HMONITOR hMonitor,
                                                       HDC hdcMonitor,
                                                       LPRECT lprcMonitor,
                                                       LPARAM dwData) {
    GgafDxGod* pGod = (GgafDxGod*)dwData;
    MONITORINFOEX moniter_info;
    moniter_info.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMonitor, &moniter_info);

    for (int adapter_no = 0; adapter_no < pGod->_num_adapter; adapter_no++) {
        Adapter& adpt = pGod->_paAvailableAdapter[adapter_no];
        if (adpt.hMonitor == hMonitor) {
            adpt.rcMonitor = moniter_info.rcMonitor;
        }
    }
    return TRUE; //列挙を続行
}

HRESULT GgafDxGod::createDx9Device(UINT adapter,
                                   D3DDEVTYPE device_type,
                                   HWND hFocusWindow,
                                   DWORD behavior_flags,
                                   D3DPRESENT_PARAMETERS* pPresentationParameters,
                                   D3DDISPLAYMODEEX* pFullscreenDisplayMode
                                  ) {
    HRESULT hr;
    if (_can_wddm) {
        if (!CONFIG::FULL_SCREEN) {
            pFullscreenDisplayMode = nullptr;
        }
        IDirect3D9Ex* pID3D9Ex = (IDirect3D9Ex*)GgafDxGod::_pID3D9;
        IDirect3DDevice9Ex* pID3DDevice9Ex;
        hr = pID3D9Ex->CreateDeviceEx(adapter,
                                      device_type,
                                      hFocusWindow,
                                      behavior_flags,
                                      pPresentationParameters,
                                      pFullscreenDisplayMode,
                                      &pID3DDevice9Ex
                                      );
        GgafDxGod::_pID3DDevice9 = (IDirect3DDevice9Ex*)pID3DDevice9Ex;
    } else {
        hr = GgafDxGod::_pID3D9->CreateDevice(adapter,
                                              device_type,
                                              hFocusWindow,
                                              behavior_flags,
                                              pPresentationParameters,
                                              &GgafDxGod::_pID3DDevice9
                                              );
    }
    return hr;
 }

HRESULT GgafDxGod::initDx9Device() {
    //ライト構造体は、シェーダーのパラメータになる時があるため必要。
    D3DXVECTOR3 vecDirection(-1.0f, -1.0f, 1.0f);
    D3DXVec3Normalize(&vecDirection, &vecDirection); //正規化
    ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9));
    GgafDxGod::_d3dlight9_default.Direction = vecDirection;
    GgafDxGod::_d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL;
    GgafDxGod::_d3dlight9_default.Diffuse.a = 1.0f;
    GgafDxGod::_d3dlight9_default.Diffuse.r = 1.0f;
    GgafDxGod::_d3dlight9_default.Diffuse.g = 1.0f;
    GgafDxGod::_d3dlight9_default.Diffuse.b = 1.0f;

    GgafDxGod::_d3dlight9_default.Ambient.a = 1.0f;
    GgafDxGod::_d3dlight9_default.Ambient.r = 0.3f; //アンビエントライトはSetRenderState(D3DRS_AMBIENT, 0x00303030)で設定
    GgafDxGod::_d3dlight9_default.Ambient.g = 0.3f;
    GgafDxGod::_d3dlight9_default.Ambient.b = 0.3f;

    //GgafDxGod::_d3dlight9_default.Range = 1000.0f;

    //ライトをセット
    //    GgafDxGod::_pID3DDevice9->SetLight(0, &GgafDxGod::_d3dlight9_default);
    //ライトスイッチON
    //    GgafDxGod::_pID3DDevice9->LightEnable(0, TRUE);
    //GgafDxGod::_pID3DDevice9->LightEnable(0, FALSE);
    //レンダ時にライトの影響（陰影）を有効
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);
    //レンダ時にライトの影響（陰影）を無効 (ピクセルシェーダーで行なうため）
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);
    //レンダ時、世界に共通のアンビエントライトを有効にしたように描く
    //   GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, _ambient_brightness_default);

    // Zバッファを有効に
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファを無効に
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    //Zバッファ書き込み可
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //Zバッファ書き込み不可
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    //D3DRENDERSTATE_ZFUNC

    //ステンシルテストの方法
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //常にテストをパス
    //画に失敗した時にステンシルの値をどう変化させるか
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //変化なし
    //Zテストで失敗した場合のステンシル値の変化
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //変化なし


    //左（反時計回り）回りにカリング ∵左手座標系
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //カリングしない
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // ディザリング
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_DITHERENABLE, TRUE );
    // マルチサンプリングアンチエイリアス(といってもフルスクリーンだけ？)↓TODO:まだ謎
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
//    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK, 0x00ffffff);

    //ピクセル単位のアルファテストを有効
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    //α設定はシェーダーに書く事にしたのでコメント
    // アルファブレンドＯＮ
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //2段階目、半透明テクスチャを貼り付けたポリゴンとバックバッファ（レンダーターゲット）との合成
    //色の算出方法の設定
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD); //D3DBLENDOP_ADD=転送元に転送先が加算
    //合成係数
    //    //上に書く画像の合成法(シェーダーに影響)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC,D3DBLEND_SRCALPHA=普通に描く。ポリゴンのアルファ値の濃さで描く。アルファ値の値が高ければ高いほど、濃く描く。
    //    //下地の画像の合成法(シェーダーに影響)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //DIST,D3DBLEND_INVSRCALPHA=上に描くポリゴンのアルファ値の濃さによって、下地の描画を薄くする。



    //頂点カラーを無効にする
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, FALSE );
    // GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, TRUE );
    //    //面のアンビエント反射は、マテリアルを参照するように設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //面のデフューズ反射は、マテリアルを参照するように設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //面のエミッシブ反射は、マテリアルを参照する設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //面のスペキュラ反射は、マテリアルを参照する設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

    //頂点αを使用するとき
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1);

    //
    //
    // アンチエイリアスの指定
    //GgafDxGod::_pID3DDevice9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    //GgafDxGod::_pID3DDevice9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    //  TypeにD3DSAMP_MINFILTER/D3DSAMP_MAGFILTER（拡大/縮小時） ??D3DTSS_MAGFILTER
    //  ValueにD3DTEXTUREFILTERTYPE列挙型を指定する
    //  D3DTEXF_POINT　　　　：フィルタをかけない。高速描画できる
    //  D3DTEXF_LINEAR　　　：リニアフィルタ（線形補完）
    //  D3DTEXF_ANISOTROPIC　：異方性フィルタ。地表面などの、拡大縮小率が手前と奥で異なる場合に使う
    //  D3DTEXF_PYRAMIDALQUAD：テントフィルタ。リニアフィルタとあまり変わんないらしい
    //  D3DTEXF_GAUSSIANQUAD ：ガウシアンフィルタ。またの名をぼかしフィルタ
    //  を指定する。

    //2009/3/4 SetSamplerStateの意味を今ごろ理解する。
    //SetSamplerStateはテクスチャからどうサンプリング（読み取るか）するかの設定。
    //だからアンチエイリアスっていっても、テクスチャしかアンチエイリアスがかかりません。
    //今後ピクセルシェーダーで全部書くので、このあたりの設定は、全部いらなくなるはずだ。


    //アンチエイリアスにかかわるレンダリングステート
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);
    //GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK,0x7fffffff);

    //色合成も全てシェーダーで処理になったのでコメント
    //SetTextureStageStateは廃止？
    //  1段階目ポリゴンとテクスチャの合成方法設定
    //    //テクスチャーの色と、頂点カラーのDIFFUSE色を乗算するように設定
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    //    //テクスチャーのαと、頂点カラーのαを乗算するように設定
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    //    GgafDxGod::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);


    //GgafDxCameraへ移動した
    // VIEW変換（カメラ位置）設定
    //D3DXMATRIX _matView; // ビュー変換行列
    //    GGAF_DELETE_NULLABLE(_pVecCamFromPoint);
    //    GGAF_DELETE_NULLABLE(_pVecCamLookatPoint);
    //    GGAF_DELETE_NULLABLE(_pVecCamUp);

    //GgafDxCameraへ移動した
    // 射影変換（３Ｄ→平面）
    //D3DXMATRIX _matProj; // 射影変換行列
    //GgafDxGod::_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &_matProj);
    //HRESULT hr;
    //バックバッファをウィンドウBG色でクリア
    //ここではRenderTargetはまだ、通常のバックバッファである
//    hr = GgafDxGod::_pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
//    returnWhenFailed(hr, D3D_OK, "背景色(_color_border)の塗りつぶしよる、画面クリアに失敗しました。");
    return D3D_OK;
}


HRESULT GgafDxGod::restoreFullScreenRenderTarget() {
    if (!CONFIG::FULL_SCREEN) {
        _TRACE_("＜警告＞フルスクリーン時意外、呼び出し不要です。");
        return D3D_OK;
    }
    HRESULT hr;
    //描画先となるテクスチャを別途作成（バックバッファ的な使用を行う）
    hr = GgafDxGod::_pID3DDevice9->CreateTexture(
                                        CONFIG::RENDER_TARGET_BUFFER_WIDTH,
                                        CONFIG::RENDER_TARGET_BUFFER_HEIGHT,
                                        1, //MipLevel Mip無し
                                        D3DUSAGE_RENDERTARGET,
                                        _paPresetPrm[_primary_adapter_no].BackBufferFormat,
                                        D3DPOOL_DEFAULT,
                                        &_pRenderTexture,
                                        nullptr);

//    LPDIRECT3DTEXTURE9 pIDirect3DTexture9;
//    HRESULT hr = D3DXCreateTextureFromFileEx(
//                     GgafDxGod::_pID3DDevice9,  // [in] LPDIRECT3DDEVICE9 pDevice,
//                     texture_file_name.c_str(), // [in] LPCTSTR pSrcFile,
//                     D3DX_DEFAULT,              // [in] UINT Widths,
//                     D3DX_DEFAULT,              // [in] UINT Height,
//                     D3DX_DEFAULT,              // [in] UINT MipLevels,  //D3DX_DEFAULT,
//                     0,                         // [in] DWORD Usage,
//                     D3DFMT_UNKNOWN,            // [in] D3DFORMAT Format,
//                     D3DPOOL_DEFAULT,           // [in] D3DPOOL Pool, //D3DPOOL_DEFAULT
//                     D3DX_FILTER_POINT,         // [in] DWORD Filter, D3DX_FILTER_POINTでボヤケナイ. D3DX_FILTER_LINEAR
//                     D3DX_DEFAULT,              // [in] DWORD MipFilter,
//                     0,                         // [in] D3DCOLOR ColorKey,
//                     _pD3DXIMAGE_INFO,          // [out] D3DXIMAGE_INFO *pSrcInfo,
//                     nullptr,                   // [in] PALETTEENTRY *pPalette,
//                     &pIDirect3DTexture9        // [out] LPDIRECT3DTEXTURE9* ppTexture
//                );

    //TODO:アンチエイリアスの実験のため
    //     テクスチャーの代わりにサーフェイスを試す事。
    //    HRESULT CreateRenderTarget(
    //        UINT Width,
    //        UINT Height,
    //        D3DFORMAT Format,
    //        D3DMULTISAMPLE_TYPE MultiSample,
    //        DWORD MultisampleQuality,
    //        BOOL Lockable,
    //        IDirect3DSurface9** ppSurface,
    //        HANDLE* pHandle
    //    );


    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャ("<<CONFIG::RENDER_TARGET_BUFFER_WIDTH<<"x"<<CONFIG::RENDER_TARGET_BUFFER_HEIGHT<<")の作成に失敗。\nサイズを確認して下さい。");
    //RenderTarget(描画先)をテクスチャへ切り替え
    hr = _pRenderTexture->GetSurfaceLevel(0, &_pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャのサーフェイス取得に失敗しました。");
    hr = GgafDxGod::_pID3DDevice9->SetRenderTarget(0, _pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャへ SetRenderTarget 出来ませんでした。");


    //テクスチャに描画する際の深度バッファ用サーフェイスを別途作成
    hr = GgafDxGod::_pID3DDevice9->CreateDepthStencilSurface(
            CONFIG::RENDER_TARGET_BUFFER_WIDTH,
            CONFIG::RENDER_TARGET_BUFFER_HEIGHT,
            _paPresetPrm[_primary_adapter_no].AutoDepthStencilFormat, //D3DFORMAT           Format,
            _paPresetPrm[_primary_adapter_no].MultiSampleType,        //D3DMULTISAMPLE_TYPE MultiSample,
            _paPresetPrm[_primary_adapter_no].MultiSampleQuality,     //DWORD               MultisampleQuality,
            TRUE,                                   //BOOL                Discard, SetDepthStencileSurface関数で深度バッファを変更した時にバッファを破棄するかどうか
            &_pRenderTextureZ,                      //IDirect3DSurface9** ppSurface,
            nullptr                                 //HANDLE*             pHandle 現在未使用
    );
    //深度バッファ作成自動生成の、深度バッファ用サーフェイスを上記に変更
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャのZバッファ作成に失敗しました。");
    hr =  GgafDxGod::_pID3DDevice9->SetDepthStencilSurface(_pRenderTextureZ);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャへ SetDepthStencilSurface 出来ませんでした。");
    //背景色でクリア
    hr = GgafDxGod::_pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    hr = GgafDxGod::_pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    hr = GgafDxGod::_pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    hr = GgafDxGod::_pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK,  "クリア色(_color_border)の塗りつぶしよる、画面クリアに失敗しました。");

    //アダプタに関連付けられたスワップチェーンを取得してバックバッファ取得
    hr = GgafDxGod::_pID3DDevice9->GetSwapChain( _primary_adapter_no, &_apSwapChain[PRIMARY_VIEW] );
    returnWhenFailed(hr, D3D_OK, "スワップチェイン取得に失敗しました。");
    hr = _apSwapChain[PRIMARY_VIEW]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_apBackBuffer[PRIMARY_VIEW] );
    returnWhenFailed(hr, D3D_OK, "スワップチェインから、ターゲットのバックバッファ取得に失敗しました。");
    if (CONFIG::DUAL_VIEW) {
        hr = GgafDxGod::_pID3DDevice9->GetSwapChain( _secondary_adapter_no, &_apSwapChain[SECONDARY_VIEW] );
        returnWhenFailed(hr, D3D_OK, "２画面目のスワップチェイン取得に失敗しました。\nマルチディスプレイ環境に問題発生しました。");
        hr = _apSwapChain[SECONDARY_VIEW]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_apBackBuffer[SECONDARY_VIEW] );
        returnWhenFailed(hr, D3D_OK, "２画面目のスワップチェインから、ターゲットのバックバッファ取得に失敗しました。");
    }

    //フルスクリーン時、バックバッファとフロントバッファを背景色で塗る
    if (CONFIG::DUAL_VIEW) {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW],
                _apBackBuffer[PRIMARY_VIEW], &_aRect_ViewScreen[PRIMARY_VIEW],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1画面目、背景色塗に失敗しました。(1)\n"
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[PRIMARY_VIEW]="<<_apBackBuffer[PRIMARY_VIEW]);

        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW],
                _apBackBuffer[SECONDARY_VIEW], &_aRect_ViewScreen[SECONDARY_VIEW],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 2画面目、背景色塗に失敗しました。(1)\n"
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[PRIMARY_VIEW]="<<_apBackBuffer[PRIMARY_VIEW]);
    } else {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_rectRenderTargetBuffer,
                _apBackBuffer[PRIMARY_VIEW], &_aRect_ViewScreen[PRIMARY_VIEW],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN 背景色塗に失敗しました。(1)");
    }

    hr = GgafDxGod::_pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK, "Present(nullptr, nullptr, nullptr, nullptr)に失敗しました。");
    //フリップしてもう一度背景色で塗る
    if (CONFIG::DUAL_VIEW) {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW],
                _apBackBuffer[PRIMARY_VIEW], &_aRect_ViewScreen[PRIMARY_VIEW],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1画面目、背景色塗に失敗しました。(2)\n"
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[PRIMARY_VIEW]="<<_apBackBuffer[PRIMARY_VIEW]);

        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW],
                _apBackBuffer[SECONDARY_VIEW], &_aRect_ViewScreen[SECONDARY_VIEW],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 2画面目、背景色塗に失敗しました。(2)\n"
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[PRIMARY_VIEW]="<<_apBackBuffer[PRIMARY_VIEW]);
    } else {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_rectRenderTargetBuffer,
                _apBackBuffer[PRIMARY_VIEW], &_aRect_ViewScreen[PRIMARY_VIEW],
                D3DTEXF_NONE
                );
        checkDxException(hr, D3D_OK, "FULL_SCREEN 背景色塗に失敗しました。(2)");
    }
    hr = GgafDxGod::_pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK, "Present(nullptr, nullptr, nullptr, nullptr)に失敗しました。(2)");
    //↑無駄な感じだが、VISTAとXPの２画面目フルスクリーンモード時
    //  両対応させるのはこのようなコードしかないという結論。

    //フルスクリーンのウィンドウ位置を補正
    EnumDisplayMonitors(nullptr, nullptr, GgafDxGod::updateMoniterPixcoordCallback, (LPARAM)this);

    for (int n = 0; n < _num_adapter; n++) {
        pixcoord full_screen_x = _paAvailableAdapter[n].rcMonitor.left;
        pixcoord full_screen_y = _paAvailableAdapter[n].rcMonitor.top;
        _TRACE_("画面 adapter_no="<<n<<" の左上座標("<<full_screen_x<<","<<full_screen_y<<")");
        ShowWindow(_paHWnd[n], SW_SHOWNORMAL);
        UpdateWindow(_paHWnd[n]);
        SetWindowPos(_paHWnd[n],
                     HWND_TOPMOST,
                     full_screen_x, full_screen_y, 0, 0,
                     SWP_NOSIZE);
    }
    return D3D_OK;
}


HRESULT GgafDxGod::releaseFullScreenRenderTarget() {
    GGAF_RELEASE_BY_FROCE(_pRenderTextureSurface);
    GGAF_RELEASE_BY_FROCE(_pRenderTexture);
    GGAF_RELEASE_BY_FROCE(_pRenderTextureZ);
    GGAF_RELEASE_BY_FROCE(_apBackBuffer[PRIMARY_VIEW]);
    GGAF_RELEASE_BY_FROCE(_apSwapChain[PRIMARY_VIEW]);
    if (CONFIG::DUAL_VIEW) {
        GGAF_RELEASE_BY_FROCE(_apBackBuffer[SECONDARY_VIEW]);
        GGAF_RELEASE_BY_FROCE(_apSwapChain[SECONDARY_VIEW]);
    }
    return D3D_OK;
}

void GgafDxGod::chengeToBorderlessFullWindow(HWND prm_pHWnd) {
    LONG lStyle  = GetWindowLong( prm_pHWnd, GWL_STYLE );
    lStyle &= ~WS_OVERLAPPEDWINDOW;
    lStyle |= WS_POPUP;
    lStyle  = SetWindowLong( prm_pHWnd, GWL_STYLE, lStyle );
    SetWindowPos( prm_pHWnd, NULL, 0, 0, 0, 0, (SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED) );
    Sleep(1);
    ShowWindow(prm_pHWnd, SW_SHOWMAXIMIZED );
    UpdateWindow(prm_pHWnd);
    Sleep(1);
    ShowWindow(prm_pHWnd, SW_NORMAL );
    UpdateWindow(prm_pHWnd);
    Sleep(1);
    ShowWindow(prm_pHWnd, SW_SHOWMAXIMIZED );
    UpdateWindow(prm_pHWnd);
    GgafDxCore::GgafDxGod::_adjustGameWindow = true;
    GgafDxCore::GgafDxGod::_pHWnd_adjustScreen = prm_pHWnd;
}

void GgafDxGod::backToNomalWindow(HWND prm_pHWnd) {

    LONG lStyle  = GetWindowLong( prm_pHWnd, GWL_STYLE );
    lStyle &= ~WS_POPUP;
    lStyle |= WS_OVERLAPPEDWINDOW;
    lStyle  = SetWindowLong( prm_pHWnd, GWL_STYLE, lStyle );
    SetWindowPos( prm_pHWnd, NULL, 0, 0, 0, 0, (SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED) );
    ShowWindow(prm_pHWnd, SW_NORMAL);
    UpdateWindow(prm_pHWnd);
    GgafDxCore::GgafDxGod::_adjustGameWindow = true;
    GgafDxCore::GgafDxGod::_pHWnd_adjustScreen = prm_pHWnd;
}

void GgafDxGod::presentSpacetimeMoment() {
    if (GgafDxGod::_is_device_lost_flg) {
        return;
    } else {
        GgafGod::presentSpacetimeMoment();
    }
}

void GgafDxGod::executeSpacetimeJudge() {
    if (GgafDxGod::_is_device_lost_flg) {
        return;
    } else {
        GgafGod::executeSpacetimeJudge();
    }
}
void GgafDxGod::makeSpacetimeMaterialize() {
    if (GgafDxGod::_is_device_lost_flg) {
        return;
    }
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    HRESULT hr;
    //通常時処理
    //バッファクリア
    hr = pDevice->Clear(0, // クリアする矩形領域の数
                        nullptr, // 矩形領域
                        D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                        _color_clear, //クリア色（not 背景色）
                        1.0f,         // Zバッファのクリア値
                        0             // ステンシルバッファのクリア値
                       );
    checkDxException(hr, D3D_OK, "pDevice->Clear() に失敗しました。");

    //描画事前処理
    hr = pDevice->BeginScene();
    checkDxException(hr, D3D_OK, "pDevice->BeginScene() に失敗しました。");
    //全て具現化！（描画）
#ifdef MY_DEBUG
    pDevice->SetRenderState(D3DRS_FILLMODE, GgafDxGod::_d3dfillmode);
#endif
    GgafGod::makeSpacetimeMaterialize(); //スーパーのmaterialize実行
    //描画事後処理
    hr = pDevice->EndScene();
    checkDxException(hr, D3D_OK, "pDevice->EndScene() に失敗しました。");

}

void GgafDxGod::presentSpacetimeVisualize() {
    IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
    //垂直帰線期間
    //if (GgafDxGod::_pID3DDevice9->Present(nullptr,&_aRect_Present[PRIMARY_VIEW],nullptr,nullptr) == D3DERR_DEVICELOST) {
    //        static D3DRASTER_STATUS rs;
    //        while (SUCCEEDED(GgafDxGod::_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
    //            if(rs.InVBlank) {
    //                break; //垂直帰線期間ではない
    //            } else {
    //                Sleep(1);
    //            }
    //        }
    HRESULT hr;
    if (GgafDxGod::_is_device_lost_flg == false) {
        if (_adjustGameWindow && _pHWnd_adjustScreen) {
            adjustGameWindow(_pHWndPrimary);
            adjustGameWindow(_pHWndSecondary);
        }

        //Present
        if (CONFIG::FULL_SCREEN) {
            if (CONFIG::DUAL_VIEW) {
                //２画面使用・フルスクリーン
                //画面０バックバッファを画面１バックバッファへコピーする
                hr = pDevice->StretchRect(
                        _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW],
                        _apBackBuffer[PRIMARY_VIEW], &_aRect_Present[PRIMARY_VIEW],
                        D3DTEXF_LINEAR); //TODO:D3DTEXF_LINEARをオプション指定にするか？
                checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1画面目 StretchRect() に失敗しました。\n_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[PRIMARY_VIEW]="<<_apBackBuffer[PRIMARY_VIEW]);

                hr = pDevice->StretchRect(
                        _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW],
                        _apBackBuffer[SECONDARY_VIEW], &_aRect_Present[SECONDARY_VIEW],
                        D3DTEXF_LINEAR);
                checkDxException(hr, D3D_OK, "StretchRect() に失敗しました。");

                hr = pDevice->Present(nullptr, nullptr, nullptr, nullptr);
            } else {
                //１画面使用・フルスクリーン
                hr = pDevice->StretchRect(
                        _pRenderTextureSurface,
                        &_rectRenderTargetBuffer,
                        _apBackBuffer[PRIMARY_VIEW],
                        &_aRect_Present[PRIMARY_VIEW],
                        D3DTEXF_LINEAR);
                checkDxException(hr, D3D_OK, "FULL 1gamen StretchRect() に失敗しました。");

                hr = pDevice->Present(nullptr, nullptr, nullptr, nullptr);
            }
        } else {
            if (CONFIG::DUAL_VIEW) {
                //２画面使用・ウィンドウモード
                if (CONFIG::FIXED_GAME_VIEW_ASPECT) {
                    //縦横比固定モード
                    if (CONFIG::SWAP_GAME_VIEW) {
                        //画面入れ替えあり
                        hr = pDevice->Present(&_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW], &_aRect_Present[PRIMARY_VIEW], nullptr, nullptr);
                        if (hr == D3D_OK) {
                            hr = pDevice->Present(&_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW], &_aRect_Present[SECONDARY_VIEW], _pHWndSecondary, nullptr);
                        }
                    } else {
                        //画面入れ替えなし
                        hr = pDevice->Present(&_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW], &_aRect_Present[PRIMARY_VIEW], nullptr, nullptr);
                        if (hr == D3D_OK) {
                            hr = pDevice->Present(&_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW], &_aRect_Present[SECONDARY_VIEW], _pHWndSecondary, nullptr);
                        }
                    }
                } else {
                    //縦横ストレッチモード
                    if (CONFIG::SWAP_GAME_VIEW) {
                        //画面入れ替えあり
                        hr = pDevice->Present(&_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW], nullptr, nullptr, nullptr);
                        if (hr == D3D_OK) {
                            hr = pDevice->Present(&_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW], nullptr, _pHWndSecondary, nullptr);
                        }
                    } else {
                        //画面入れ替えなし
                        hr = pDevice->Present(&_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW], nullptr, nullptr, nullptr);
                        if (hr == D3D_OK) {
                            hr = pDevice->Present(&_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW], nullptr, _pHWndSecondary, nullptr);
                        }
                    }
                }
            } else {
                //１画面使用・ウィンドウモード
                if (CONFIG::FIXED_GAME_VIEW_ASPECT) {
                    //縦横比固定モード
                    hr = pDevice->Present(&_rectRenderTargetBuffer, &_aRect_Present[PRIMARY_VIEW], nullptr, nullptr);
                } else {
                    //縦横ストレッチモード
                    hr = pDevice->Present(&_rectRenderTargetBuffer, nullptr, nullptr, nullptr);
                }
            }
        }

        if (hr != D3D_OK) { //hr は Present の戻り値
             //出刃異素露巣斗？
//            _TRACE_("＜警告＞デバイス異常発生!!" <<DXGetErrorString(hr) << " "<< DXGetErrorDescription(hr));
            _TRACE_("＜警告＞デバイス異常発生!! HRESULT="<<hr);
            if (hr == D3DERR_DEVICELOST) {
                _TRACE_("通常の正常デバイスロスト！");
            }

            Sleep(100);
            _TRACE_("【デバイスロスト処理】BEGIN ------>");

            //愛休止
            _TRACE_("【デバイスロスト処理】愛停止 BEGIN ------>");
            GgafGod::beginRest();
            END_SYNCHRONIZED1; // <----- 排他終了
            for (int i = 0; GgafGod::isResting() == false; i++) {
                Sleep(10); //愛が落ち着くまで待つ
                if (i > 10*60*100) {
                    _TRACE_("【デバイスロスト処理/愛停止】 10分待機しましたが、愛から反応がありません。強制breakします。要調査");
                    break;
                }
            }
            BEGIN_SYNCHRONIZED1; // ----->排他開始
            _TRACE_("【デバイスロスト処理】愛停止 <-------- END");

            _TRACE_("【デバイスロスト処理】リソース解放 BEGIN ------>");

            //レンダリングターゲット、デバイスロスト処理
            if (CONFIG::FULL_SCREEN) {
                releaseFullScreenRenderTarget();
            }
            //環境マップテクスチャ、デバイスロスト処理
            _pCubeMapTextureManager->releaseAll();
            _pBumpMapTextureManager->releaseAll();
            //エフェクト、デバイスロスト処理
            _pEffectManager->onDeviceLostAll();
            //モデル解放
            _pModelManager->onDeviceLostAll();
            //全ノードに解放しなさいイベント発令
            getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST);
            _TRACE_("【デバイスロスト処理】リソース解放 <-------- END");
            GgafDxGod::_is_device_lost_flg = true;
        }
    }

    if (GgafDxGod::_is_device_lost_flg) {
        _TRACE_("【デバイスロスト処理/リソース解放】協調性レベルチェック BEGIN ------>");
        //for (int i = 0; i < 300; i++) {
        while (true) {
            if (_can_wddm) {
                hr = ((IDirect3DDevice9Ex*)pDevice)->CheckDeviceState(_paPresetPrm[_primary_adapter_no].hDeviceWindow);
                if (hr == D3DERR_DEVICELOST || hr == S_PRESENT_OCCLUDED) {
                    return;
                } else {
                    break;
                }
            } else {
                hr = pDevice->TestCooperativeLevel();
                if (hr == D3DERR_DEVICELOST) {
                    return;
                } else {
                    break;
                }
            }
        }
        _TRACE_("【デバイスロスト処理/リソース解放】協調性レベルチェック <-------- END");

        //デバイスリセットを試みる
        _TRACE_("【デバイスロスト処理】デバイスリセット BEGIN ------>");
        for (int i = 0; i < 100*60*10; i++) {
            if (CONFIG::FULL_SCREEN && CONFIG::DUAL_VIEW) {
                hr = pDevice->Reset(_paPresetPrm);
            } else {
                hr = pDevice->Reset(&(_paPresetPrm[_primary_adapter_no]));
            }
            if (hr != D3D_OK) {
                if (hr == D3DERR_DRIVERINTERNALERROR) {
                    Sleep(10);
                    return;
                } else if (hr == D3DERR_DRIVERINTERNALERROR) {
                    throwGgafDxCriticalException(hr, "【デバイスロスト処理/デバイスリセット】D3DERR_DRIVERINTERNALERROR。強制終了します。");
                } else if (hr == D3DERR_OUTOFVIDEOMEMORY) {
                    throwGgafDxCriticalException(hr, "【デバイスロスト処理/デバイスリセット】D3DERR_OUTOFVIDEOMEMORY。メモリがありません。強制終了します。");
                } else {
                    Sleep(10);
                    return;
                }
            } else {
                break;
            }
        }
        _TRACE_("【デバイスロスト処理】デバイスリセット <-------- END");


        //デバイス再設定
        _TRACE_("【デバイスロスト処理】デバイス再構築 BEGIN ------>");
        initDx9Device();
        _TRACE_("【デバイスロスト処理】デバイス再構築 <-------- END");

        if (CONFIG::FULL_SCREEN) {
            _TRACE_("【デバイスロスト処理】フルスクリーン時レンダリングターゲットテクスチャ再構築 BEGIN ------>");
            restoreFullScreenRenderTarget();
            _TRACE_("【デバイスロスト処理】フルスクリーン時レンダリングターゲットテクスチャ再構築 <-------- END");
        }

        //リソース再構築
        _TRACE_("【デバイスロスト処理】リソース再構築 BEGIN ------>");
        //環境マップテクスチャ、復帰処理
        _pCubeMapTextureManager->restoreAll();
        _pBumpMapTextureManager->restoreAll();
        //エフェクトリセット
        _pEffectManager->restoreAll();
        //モデル再設定
        _pModelManager->restoreAll();
        //全ノードに再設定しなさいイベント発令
        getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST_RESTORE);
        //前回描画モデル情報を無効にする
        GgafDxModelManager::_pModelLastDraw = nullptr;
        GgafDxGod::_is_device_lost_flg = false;
        _TRACE_("【デバイスロスト処理】リソース再構築 <-------- END");

        //愛再開
        _TRACE_("【デバイスロスト処理】愛再起動 BEGIN ------>");
        GgafGod::finishRest();
        _TRACE_("【デバイスロスト処理】愛再起動 <-------- END");

        _TRACE_("【デバイスロスト処理】<-------- END");

        Sleep(100);
        hr = pDevice->Clear(0,    // クリアする矩形領域の数
                            nullptr, // 矩形領域
                            D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                            _color_border, //背景色      //D3DCOLOR_XRGB( 0, 0, 0 )
                            1.0f, // Zバッファのクリア値
                            0     // ステンシルバッファのクリア値
                           );
    }
}

void GgafDxGod::finalizeSpacetime() {
    if (GgafDxGod::_is_device_lost_flg) {
        return;
    } else {
        GgafGod::finalizeSpacetime();
    }
}

void GgafDxGod::clean() {
    if (!_was_cleaned) {
        _TRACE_(FUNC_NAME<<" begin");
        IDirect3DDevice9* pDevice = GgafDxGod::_pID3DDevice9;
        for (int i = 0; i < 8; ++i) { pDevice->SetTexture( i, nullptr ); }
        for (int i = 0; i < 8; ++i) { pDevice->SetStreamSource( i, nullptr, 0, 0 ); }
        pDevice->SetIndices( nullptr );
        pDevice->SetPixelShader( nullptr );
        pDevice->SetVertexShader( nullptr );
        pDevice->SetVertexDeclaration( nullptr );

        GgafGod::clean();

        CmRandomNumberGenerator::getInstance()->release();
        //保持モデル解放
        GGAF_DELETE(_pCubeMapTextureManager);
        GGAF_DELETE(_pBumpMapTextureManager);
        GGAF_DELETE(_pModelManager);
        GGAF_DELETE(_pEffectManager);
        _TRACE_(FUNC_NAME<<" end");
    }
}

void GgafDxGod::adjustGameWindow(HWND prm_pHWnd) {
    RECT rect;
    if (prm_pHWnd && !CONFIG::FULL_SCREEN ) {
        //ウィンドウモード時
        HRESULT hr;
        hr = GgafDxGod::_pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
        hr = GgafDxGod::_pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
        if (CONFIG::DUAL_VIEW) {
            hr = GgafDxGod::_pID3DDevice9->Present(nullptr, nullptr, _pHWndSecondary, nullptr);
        }
        if (::GetClientRect(prm_pHWnd, &rect)) {
            LONG c_width= rect.right;
            LONG c_height = rect.bottom;

            LONG fix_width, fix_height;
            int pos1, pos2;
            if (CONFIG::DUAL_VIEW) {
                pos1 = CONFIG::DUAL_VIEW_DRAW_POSITION1;
                pos2 = CONFIG::DUAL_VIEW_DRAW_POSITION2;
            } else {
                pos1 = CONFIG::SINGLE_VIEW_DRAW_POSITION;
                pos2 = CONFIG::DUAL_VIEW_DRAW_POSITION2; //とりあえず
            }

            //ウィンドウモード時・RENDER_TARGET_BUFFERサイズ無視
            if (CONFIG::FIXED_GAME_VIEW_ASPECT) {
                //ウィンドウモード時・アスペクト比固定
                if (CONFIG::DUAL_VIEW) {
                    if (prm_pHWnd == _pHWndPrimary) {
                        fix_width  = CONFIG::VIEW_SOURCE_BUFFER_WIDTH  * CONFIG::VIEW1_WIDTH_RATIO / 2.0;
                        fix_height = CONFIG::VIEW_SOURCE_BUFFER_HEIGHT * CONFIG::VIEW1_HEIGHT_RATIO;
                    } else {
                        fix_width  = CONFIG::VIEW_SOURCE_BUFFER_WIDTH  * CONFIG::VIEW2_WIDTH_RATIO / 2.0;
                        fix_height = CONFIG::VIEW_SOURCE_BUFFER_HEIGHT * CONFIG::VIEW2_HEIGHT_RATIO;
                    }
                } else {
                    fix_width  = CONFIG::VIEW_SOURCE_BUFFER_WIDTH  * CONFIG::VIEW1_WIDTH_RATIO;
                    fix_height = CONFIG::VIEW_SOURCE_BUFFER_HEIGHT * CONFIG::VIEW1_HEIGHT_RATIO;
                }

                if (1.0f * c_width / c_height > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * c_height / fix_height; //縮小率=縦幅の比率
                    if (prm_pHWnd == _pHWndPrimary) {
                        _aRect_Present[PRIMARY_VIEW].left   = (c_width / 2.0) - (fix_width * rate / 2.0);
                        _aRect_Present[PRIMARY_VIEW].top    = 0;
                        _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                        _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                        setPositionPresentRect(pos1, _aRect_Present[PRIMARY_VIEW], c_width, c_height);
                    } else {
                        _aRect_Present[SECONDARY_VIEW].left   = (c_width / 2.0) - (fix_width * rate / 2.0);
                        _aRect_Present[SECONDARY_VIEW].top    = 0;
                        _aRect_Present[SECONDARY_VIEW].right  = _aRect_Present[SECONDARY_VIEW].left + (fix_width * rate);
                        _aRect_Present[SECONDARY_VIEW].bottom = _aRect_Present[SECONDARY_VIEW].top  + (fix_height * rate);
                        setPositionPresentRect(pos2, _aRect_Present[SECONDARY_VIEW], c_width, c_height);
                    }

                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * c_width / fix_width; //縮小率=横幅の比率
                    if (prm_pHWnd == _pHWndPrimary) {
                        _aRect_Present[PRIMARY_VIEW].left   = 0;
                        _aRect_Present[PRIMARY_VIEW].top    = (c_height / 2.0) - (fix_height * rate / 2.0);
                        _aRect_Present[PRIMARY_VIEW].right  = _aRect_Present[PRIMARY_VIEW].left + (fix_width * rate);
                        _aRect_Present[PRIMARY_VIEW].bottom = _aRect_Present[PRIMARY_VIEW].top  + (fix_height * rate);
                        setPositionPresentRect(pos1, _aRect_Present[PRIMARY_VIEW], c_width, c_height);
                    } else {
                        _aRect_Present[SECONDARY_VIEW].left   = 0;
                        _aRect_Present[SECONDARY_VIEW].top    = (c_height / 2.0) - (fix_height * rate / 2.0);
                        _aRect_Present[SECONDARY_VIEW].right  = _aRect_Present[SECONDARY_VIEW].left + (fix_width * rate);
                        _aRect_Present[SECONDARY_VIEW].bottom = _aRect_Present[SECONDARY_VIEW].top  + (fix_height * rate);
                        setPositionPresentRect(pos2, _aRect_Present[SECONDARY_VIEW], c_width, c_height);
                    }
                }
            } else {
                //ウィンドウモード時・縦横ストレッチ
                if (::GetClientRect(prm_pHWnd, &rect)) {
                    if (prm_pHWnd == _pHWndPrimary) {
                        _aRect_Present[PRIMARY_VIEW] = rect;
                    } else {
                        _aRect_Present[SECONDARY_VIEW] = rect;
                    }

                }
            }
        }
#ifdef MY_DEBUG
        _TRACE_("GgafDxGod::adjustGameWindow(" << (prm_pHWnd == _pHWndPrimary ? "Primary" : "Secondary") <<") コール");
        if (CONFIG::DUAL_VIEW) {
            _TRACE_(" _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left   = "<<_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].left  );
            _TRACE_(" _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top    = "<<_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].top   );
            _TRACE_(" _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].right  = "<<_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].right );
            _TRACE_(" _aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].bottom = "<<_aRect_HarfRenderTargetBuffer[PRIMARY_VIEW].bottom);
            _TRACE_(" _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].left   = "<<_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].left  );
            _TRACE_(" _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].top    = "<<_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].top   );
            _TRACE_(" _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].right  = "<<_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].right );
            _TRACE_(" _aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].bottom = "<<_aRect_HarfRenderTargetBuffer[SECONDARY_VIEW].bottom);
            _TRACE_(" _aRect_Present[PRIMARY_VIEW].left   = "<<_aRect_Present[PRIMARY_VIEW].left  );
            _TRACE_(" _aRect_Present[PRIMARY_VIEW].top    = "<<_aRect_Present[PRIMARY_VIEW].top   );
            _TRACE_(" _aRect_Present[PRIMARY_VIEW].right  = "<<_aRect_Present[PRIMARY_VIEW].right );
            _TRACE_(" _aRect_Present[PRIMARY_VIEW].bottom = "<<_aRect_Present[PRIMARY_VIEW].bottom);
            _TRACE_(" _aRect_Present[SECONDARY_VIEW].left   = "<<_aRect_Present[SECONDARY_VIEW].left  );
            _TRACE_(" _aRect_Present[SECONDARY_VIEW].top    = "<<_aRect_Present[SECONDARY_VIEW].top   );
            _TRACE_(" _aRect_Present[SECONDARY_VIEW].right  = "<<_aRect_Present[SECONDARY_VIEW].right );
            _TRACE_(" _aRect_Present[SECONDARY_VIEW].bottom = "<<_aRect_Present[SECONDARY_VIEW].bottom);
        } else {
            _TRACE_(" _rectRenderTargetBuffer.left   = "<<_rectRenderTargetBuffer.left  );
            _TRACE_(" _rectRenderTargetBuffer.top    = "<<_rectRenderTargetBuffer.top   );
            _TRACE_(" _rectRenderTargetBuffer.right  = "<<_rectRenderTargetBuffer.right );
            _TRACE_(" _rectRenderTargetBuffer.bottom = "<<_rectRenderTargetBuffer.bottom);
            _TRACE_(" _aRect_Present[PRIMARY_VIEW].left   = "<<_aRect_Present[PRIMARY_VIEW].left  );
            _TRACE_(" _aRect_Present[PRIMARY_VIEW].top    = "<<_aRect_Present[PRIMARY_VIEW].top   );
            _TRACE_(" _aRect_Present[PRIMARY_VIEW].right  = "<<_aRect_Present[PRIMARY_VIEW].right );
            _TRACE_(" _aRect_Present[PRIMARY_VIEW].bottom = "<<_aRect_Present[PRIMARY_VIEW].bottom);
        }
#endif
    } else {
        //フルスクリーン時
    }
    GgafDxCamera* pCam = getSpacetime()->getCamera();
    GgafDxGod::_pID3DDevice9->GetViewport(&(pCam->_viewport));
    _adjustGameWindow = false;
    _pHWnd_adjustScreen = nullptr;
}

void GgafDxGod::setPositionPresentRect(int prm_pos, RECT& inout_rectPresent, pixcoord prm_screen_width, pixcoord prm_screen_height) {
    // ７　８　９
    // 　＼｜／
    // ４―５―６
    // 　／｜＼
    // １　２　３
    //1:左下、2:下、3:右下、4:左、5:真ん中、6:右、7:左上、8:上、9:右上
    if (prm_pos == 5) {
        return;
    }
    if (prm_pos == 7 || prm_pos == 8 || prm_pos == 9) {
        inout_rectPresent.bottom = inout_rectPresent.bottom - inout_rectPresent.top;
        inout_rectPresent.top = 0;
    } else if (prm_pos == 1 || prm_pos == 2 || prm_pos == 3) {
        inout_rectPresent.top = prm_screen_height - (inout_rectPresent.bottom - inout_rectPresent.top);
        inout_rectPresent.bottom = prm_screen_height;
    }

    if (prm_pos == 7 || prm_pos == 4 || prm_pos == 1) {
        inout_rectPresent.right = inout_rectPresent.right - inout_rectPresent.left;
        inout_rectPresent.left = 0;
    } else if (prm_pos == 9 || prm_pos == 6 || prm_pos == 3) {
        inout_rectPresent.left = prm_screen_width - (inout_rectPresent.right - inout_rectPresent.left);
        inout_rectPresent.right = prm_screen_width;
    }
}

GgafDxGod::~GgafDxGod() {
    _TRACE_(FUNC_NAME<<" 解放開始");
    clean();
    _was_cleaned = true;
    //DirectSound解放
    GgafDxSound::release();
    //DirectInput解放
    GgafDxInput::release();

    if(CONFIG::FULL_SCREEN) {
        releaseFullScreenRenderTarget();
    }

    _TRACE_("_pID3DDevice9 解放来たわ");
    Sleep(60);
    GGAF_DELETEARR(_paAvailableAdapter);
    GGAF_DELETEARR(_paAdapterRezos);
    GGAF_DELETEARR(_paPresetPrm);
    GGAF_DELETEARR(_paDisplayMode);
    GGAF_DELETEARR(_paHWnd);
    GGAF_RELEASE(_pID3DDevice9);
    GGAF_RELEASE(_pID3D9);
    _TRACE_(FUNC_NAME<<" 解放終了");
}




//メモ 2011/07/26
//
//【１画面ウィンドウモード】
//                                 ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//                               ／                                        ／
//    フロントバッファ         ／                                        ／
//    (ウインドウ)           ／                                        ／
//                           ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣
//                           SINGLE_VIEW_WINDOW_WIDTH x SINGLE_VIEW_WINDOW_HEIGHT
//
//                                               ↑
//                                               ｜ Present
//                                               ｜(D3DSWAPEFFECT_COPY)
//                                               ｜
//                                  ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//    バックバッファ              ／                                        ／
//                              ／                                        ／ Draw   ＿＿＿
//                            ／                                        ／    ←  ／    ／ゲームバッファ
//                            ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣          ￣￣￣
//                       RENDER_TARGET_BUFFER_WIDTH x RENDER_TARGET_BUFFER_HEIGHT
//
//
//---------------------------------------------------------------------------------------------
//
//
//【２画面ウィンドウモード】
//                            ＿＿＿＿＿＿＿＿＿＿＿             ＿＿＿＿＿＿＿＿＿＿＿
//                          ／                    ／           ／                    ／
//    フロントバッファ    ／                    ／           ／                    ／
//    (ウインドウ)      ／                    ／           ／                    ／
//                      ￣￣￣￣￣￣￣￣￣￣￣             ￣￣￣￣￣￣￣￣￣￣￣
//                     DUAL_VIEW_WINDOW1_WIDTH x            DUAL_VIEW_WINDOW2_WIDTH x
//                       DUAL_VIEW_WINDOW1_HEIGHT             DUAL_VIEW_WINDOW2_HEIGHT
//
//                                 ↑                               ↑
//                                 ｜ Present                       ｜ Present
//                                 ｜(D3DSWAPEFFECT_COPY)           ｜ (D3DSWAPEFFECT_COPY)
//
//                                  ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//    バックバッファ              ／                                        ／
//                              ／                                        ／ Draw   ＿＿＿
//                            ／                                        ／    ←  ／    ／ゲームバッファ
//                            ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣          ￣￣￣
//                    RENDER_TARGET_BUFFER_WIDTH x RENDER_TARGET_BUFFER_HEIGHT
//
//
//---------------------------------------------------------------------------------------------
//
//
//【１画面フルスクリーンモード】
//                                         ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//                                       ／                              ／
//                                     ／                              ／
//    フロントバッファ               ／                              ／
//    (ディスプレイ)               ／                              ／
//                               ／                              ／
//                               ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣
//                                SINGLE_VIEW_FULL_SCREEN_WIDTH x
//                                  SINGLE_VIEW_FULL_SCREEN_HEIGHT
//
//                                                 ↑
//                                                 ｜ Present (flip)
//                                                 ｜(D3DSWAPEFFECT_DISCARD)
//                                                 ↓
//                                        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//                                      ／                              ／
//                                    ／                              ／
//    バックバッファ                ／      _apBackBuffer[0]        ／
//                                ／                              ／
//                              ／                              ／
//                              ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣
//                               SINGLE_VIEW_FULL_SCREEN_WIDTH x
//                                 SINGLE_VIEW_FULL_SCREEN_HEIGHT
//
//                                                 ↑
//                                                 ｜ StretchRect
//                                                 ｜
//                                 ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//    レンダーターゲット         ／                                        ／
//    テクスチャー             ／       _pRenderTextureSurface           ／ Draw   ＿＿＿
//                           ／                                        ／    ←  ／    ／ゲームバッファ
//                           ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣          ￣￣￣
//                     RENDER_TARGET_BUFFER_WIDTH x RENDER_TARGET_BUFFER_HEIGHT
//
//
//---------------------------------------------------------------------------------------------
//
//
//【２画面フルスクリーンモード】
//                            ＿＿＿＿＿＿＿＿＿＿＿     |        ＿＿＿＿＿＿＿＿＿＿＿
//                          ／                    ／     |      ／                    ／
//    フロントバッファ    ／                    ／       |    ／                    ／
//    (ディスプレイ)    ／                    ／         |  ／                    ／
//                      ￣￣￣￣￣￣￣￣￣￣￣           |  ￣￣￣￣￣￣￣￣￣￣￣
//                     DUAL_VIEW_FULL_SCREEN1_WIDTH x    |   DUAL_VIEW_FULL_SCREEN2_WIDTH x
//                       DUAL_VIEW_FULL_SCREEN1_HEIGHT   |     DUAL_VIEW_FULL_SCREEN2_HEIGHT
//
//                               ↑                                 ↑
//                               ｜ Present (flip)                  ｜ Present (flip)
//                               ｜(D3DSWAPEFFECT_DISCARD)          ｜ (D3DSWAPEFFECT_DISCARD)
//                               ↓                                 ↓
//                            ＿＿＿＿＿＿＿＿＿＿＿             ＿＿＿＿＿＿＿＿＿＿＿
//                          ／                    ／           ／                    ／
//    バックバッファ      ／  _apBackBuffer[0]  ／           ／  _apBackBuffer[1]  ／
//                      ／                    ／           ／                    ／
//                      ￣￣￣￣￣￣￣￣￣￣￣             ￣￣￣￣￣￣￣￣￣￣￣
//                     DUAL_VIEW_FULL_SCREEN1_WIDTH x        DUAL_VIEW_FULL_SCREEN2_WIDTH x
//                       DUAL_VIEW_FULL_SCREEN1_HEIGHT         DUAL_VIEW_FULL_SCREEN2_HEIGHT
//
//                                    ↑                            ↑
//                                    ｜ StretchRect                ｜ StretchRect
//                                    ｜                            ｜
//                                  ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//    レンダーターゲット          ／                                        ／
//    テクスチャー              ／       _pRenderTextureSurface           ／ Draw   ＿＿＿
//                            ／                                        ／    ←  ／    ／ゲームバッファ
//                            ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣          ￣￣￣
//                       RENDER_TARGET_BUFFER_WIDTH x RENDER_TARGET_BUFFER_HEIGHT




//案１
//                 <-------------------------------------------- 2048 --------------------------------------------->
//                 <--------- 512 --------->
//                 <------------------------- 1600 ------------------------------------------><------ 448 --------->
//
//         ^       +-----------------------+-----------------------+-----------------------+-+---------------------+
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//        512      |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         |       |                       |                       |                       | |                     |
//         v       +-----------------------+-----------------------+-----------------------+-+---------------------+
//                                                                                         >-<-- 64


//案２
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


