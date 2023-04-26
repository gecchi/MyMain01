#include "jp/ggaf/dx/Caretaker.h"

#include <algorithm>
#include "jp/ggaf/dx/actor/camera/Camera.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/Config.h"
#include "jp/ggaf/dx/manager/EffectManager.h"
#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/TextureManager.h"
#include "jp/ggaf/dx/manager/CurveSourceManager.h"
#include "jp/ggaf/dx/manager/CurveManufactureManager.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include "jp/ggaf/dx/sound/Sound.h"
#include "jp/ggaf/dx/util/Input.h"

using namespace GgafDx;

#define returnWhenFailed(HR, OKVAL, X) { \
    if (HR != OKVAL) { \
        std::stringstream ss; \
        ss << X; \
        MessageBox(pCARETAKER->_pHWndPrimary, TEXT(ss.str().c_str()), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST); \
        return E_FAIL; \
    } \
}

//TODO:コメントとか多すぎる。整理する。

Caretaker::Caretaker() : GgafCore::Caretaker() {
    _pID3D9 = nullptr;
    _pID3DDevice9 = nullptr;
    _d3dfillmode = D3DFILL_SOLID;

    _is_device_lost_flg = false;
    _adjustGameWindow = false;

    _pHWndPrimary = nullptr;
    _pHWndSecondary = nullptr;
    if (CONFIG::FULL_SCREEN) {
        _primary_screen_display_no = CONFIG::PRIMARY_SCREEN_DISPLAY_NO;
        _secondary_screen_display_no = CONFIG::SECONDARY_SCREEN_DISPLAY_NO;
    } else {
        _primary_screen_display_no = 0;
        _secondary_screen_display_no = 1;
    }
//    if (CONFIG::SWAP_SCREEN && CONFIG::DUAL_SCREEN) {
//        int wk = _primary_screen_display_no;
//        _primary_screen_display_no = _secondary_screen_display_no;
//        _secondary_screen_display_no = wk;
//    }

    _hInstance = GetModuleHandle(0);
    _vs_v = 0;
    _ps_v = 0;
    GgafCore::CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 Seed
    GgafCore::Rgb rgb_border = GgafCore::Rgb(CONFIG::BORDER_COLOR);
    _color_border = D3DCOLOR_RGBA(rgb_border._red, rgb_border._green, rgb_border._blue, 0);
    GgafCore::Rgb rgb_bg = GgafCore::Rgb(CONFIG::BG_COLOR);
    _color_clear = D3DCOLOR_RGBA(rgb_bg._red, rgb_bg._green, rgb_bg._blue, 0);
    _pRenderTextureSurface = nullptr;
    _pRenderTextureZ = nullptr;
    _num_adapter = 1;
    _num_PresetPrm = _num_adapter > MAX_SCREENS ? _num_adapter : MAX_SCREENS;
    _paAvailableAdapter = nullptr;
    _paAdapterRezos = nullptr;

    _can_wddm = true;//とりあえず
    _papSwapChain = nullptr;
    _papBackBuffer = nullptr;

    _paPresetPrm = nullptr;
    _paDisplayMode = nullptr;
    _paHWnd = nullptr;
    _pTextureManager = nullptr;
    _pModelManager = nullptr;
    _pEffectManager = nullptr;

    //ライト構造体は、シェーダーのパラメータになる時があるため必要。
    D3DXVECTOR3 vecDirection(-1.0f, -1.0f, 1.0f);
    D3DXVec3Normalize(&vecDirection, &vecDirection); //正規化
    ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9));
    _d3dlight9_default.Direction = vecDirection;
    _d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL;
    _d3dlight9_default.Diffuse.a = 1.0f;
    _d3dlight9_default.Diffuse.r = 1.0f;
    _d3dlight9_default.Diffuse.g = 1.0f;
    _d3dlight9_default.Diffuse.b = 1.0f;
    _d3dlight9_default.Ambient.a = 1.0f;
    _d3dlight9_default.Ambient.r = 0.2f;
    _d3dlight9_default.Ambient.g = 0.2f;
    _d3dlight9_default.Ambient.b = 0.2f;

    //_d3dlight9_default.Range = 1000.0f

    _pCurveSrcManager = nullptr;
    _pCurveManufManager = nullptr;
}
void Caretaker::resetDotByDotWindowsize(int d) {
    if (!CONFIG::FULL_SCREEN) {
        for (int pry = PRIMARY_SCREEN; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
            int adapter = CONFIG::SCREEN_DISPLAY_NO[pry];
            resetWindowsize(_paHWnd[adapter], CONFIG::RENDER_TARGET_BUFFER_WIDTH/CONFIG::NUMBER_OF_SCREENS_USED*d, CONFIG::RENDER_TARGET_BUFFER_HEIGHT*d);
        }
    }
}
void Caretaker::resetInitWindowsize() {
    //初期ウィンドウサイズにリセット
    if (!CONFIG::FULL_SCREEN) {
        for (int pry = PRIMARY_SCREEN; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
            int adapter = CONFIG::SCREEN_DISPLAY_NO[pry];
            resetWindowsize(_paHWnd[adapter],
                            CONFIG::SCREEN_WINDOW[pry].WIDTH, CONFIG::SCREEN_WINDOW[pry].HEIGHT);
        }
    }
}
void Caretaker::resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height) {
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

void Caretaker::chengeScreenPresentPos(HWND prm_pHWnd, int pos) {
    if (!CONFIG::FULL_SCREEN) {
        int pry = _mapHwndToPry[prm_pHWnd];
        CONFIG::SCREEN_PRESENT_POSITION[pry] = pos;
        _adjustGameWindow = true;
    }
}
void Caretaker::chengePrimaryScreenPresentPos(int pos) {
    if (!CONFIG::FULL_SCREEN) {
        CONFIG::PRIMARY_SCREEN_PRESENT_POSITION = pos;
        _adjustGameWindow = true;
    }
}
void Caretaker::chengeSecondaryScreenPresentPos(int pos) {
    if (!CONFIG::FULL_SCREEN) {
        CONFIG::SECONDARY_SCREEN_PRESENT_POSITION = pos;
        _adjustGameWindow = true;
    }
}
void Caretaker::chengeViewAspect(HWND prm_pHWnd, bool prm_b) {
    if (!CONFIG::FULL_SCREEN) {
        int pry = _mapHwndToPry[prm_pHWnd];
        CONFIG::SCREEN_ASPECT_RATIO_FIXED[pry] = prm_b;
        _adjustGameWindow = true;
    }
}

void Caretaker::chengeViewAspect1(bool prm_b) {
    if (!CONFIG::FULL_SCREEN) {
        CONFIG::PRIMARY_SCREEN_ASPECT_RATIO_FIXED = prm_b;
        _adjustGameWindow = true;
    }
}
void Caretaker::chengeViewAspect2(bool prm_b) {
    if (!CONFIG::FULL_SCREEN) {
        CONFIG::SECONDARY_SCREEN_ASPECT_RATIO_FIXED = prm_b;
        _adjustGameWindow = true;
    }
}

void Caretaker::setDisplaySizeInfo() {
    //アダプタ情報格納
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        _paAvailableAdapter[adapter_no].hMonitor = _pID3D9->GetAdapterMonitor(adapter_no);
        int mode_num = _pID3D9->GetAdapterModeCount(adapter_no, D3DFMT_X8R8G8B8);
        _paAvailableAdapter[adapter_no].setModeNum(mode_num);
        D3DDISPLAYMODE* paMode = _paAvailableAdapter[adapter_no].paModes;
        for (int n = 0; n < mode_num; n++) {
            _pID3D9->EnumAdapterModes(adapter_no, D3DFMT_X8R8G8B8, n, &(paMode[n]));
        }
    }

    //解像度情報格納
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        std::vector<UINT> vecWidth;
        std::vector<UINT> vecHeight;
        std::vector<std::string> vecRezo;
        int mode_num = _paAvailableAdapter[adapter_no].mode_num;
        D3DDISPLAYMODE* paMode = pCARETAKER->_paAvailableAdapter[adapter_no].paModes;
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
}
void Caretaker::setAppropriateDisplaySize(bool allow_chang_rezo) {
    //フルスクリーン要求時、指定解像度に出来るか調べ、
    //出来ない場合は、近い解像度を探し、
    //_paPresetPrm[] と、_paDisplayMode[] を上書きする。
    EnumDisplayMonitors(nullptr, nullptr, Caretaker::updateMoniterPixcoordCallback, (LPARAM)this);
    HRESULT hr;
    if (CONFIG::FULL_SCREEN) {
        for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
            _TRACE_("--- " << adapter_no+1 << "画面目 の解像度設定 --->");
            int rezo_num = _paAdapterRezos[adapter_no].rezo_num;
            RezoInfo* paRezos = _paAdapterRezos[adapter_no].paRezoInfo;
            int pry = _mapAdpToPry[adapter_no];
            if (pry >= 0) {
                if (allow_chang_rezo && CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH > 0) {
                    //解像度変更許可
                    int n = checkAppropriateDisplaySize(
                                paRezos, rezo_num,
                                (UINT)CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH,
                                (UINT)CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT
                            );
                    CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH = (pixcoord)(paRezos[n].width);
                    CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT = (pixcoord)(paRezos[n].height);
                } else {
                    //解像度変更無し
                    D3DDISPLAYMODE structD3DDisplayMode0;
                    hr = _pID3D9->GetAdapterDisplayMode(adapter_no, &structD3DDisplayMode0);
                    checkDxException(hr, D3D_OK, "GetAdapterDisplayMode に失敗しました。5");
                    CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH  = (pixcoord)(structD3DDisplayMode0.Width);
                    CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT = (pixcoord)(structD3DDisplayMode0.Height);
                }
                _paPresetPrm[adapter_no].BackBufferWidth  = CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
                _paPresetPrm[adapter_no].BackBufferHeight = CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;
            } else {
                //映らないダミー画面
                //メモ：ゲーム画面３画面目以降１画面目・２画面目の解像度は、現状の解像度をそのまま設定。
                D3DDISPLAYMODE structD3DDisplayMode;
                hr = _pID3D9->GetAdapterDisplayMode(adapter_no, &structD3DDisplayMode);
                _paPresetPrm[adapter_no].BackBufferWidth  = (pixcoord)(structD3DDisplayMode.Width);
                _paPresetPrm[adapter_no].BackBufferHeight = (pixcoord)(structD3DDisplayMode.Height);
                checkDxException(hr, D3D_OK, "GetAdapterDisplayMode に失敗しました。4");
                _TRACE_("adapter_no="<<adapter_no << "の画面は、現状の "<<
                        _paPresetPrm[adapter_no].BackBufferWidth<<"x"<<_paPresetPrm[adapter_no].BackBufferHeight<<" に設定");
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

    for (int pry = PRIMARY_SCREEN; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
        _aRectRenderBufferSource[pry].left   = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].LEFT;
        _aRectRenderBufferSource[pry].top    = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].TOP;
        _aRectRenderBufferSource[pry].right  = _aRectRenderBufferSource[pry].left + CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH;
        _aRectRenderBufferSource[pry].bottom = _aRectRenderBufferSource[pry].top  + CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT;
    }

    //表示領域設定
    if (CONFIG::FULL_SCREEN) {

        for (int pry = PRIMARY_SCREEN; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
            //フルスクリーンモード使用
            _aRect_FullScreen[pry].top    = 0;
            _aRect_FullScreen[pry].left   = 0;
            _aRect_FullScreen[pry].right  = CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
            _aRect_FullScreen[pry].bottom = CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;

            //「フルスクリーンモード使用・RENDER_TARGET_BUFFERサイズ無視」
            if (CONFIG::SCREEN_ASPECT_RATIO_FIXED[pry]) {
                //「フルスクリーンモード使用・縦横比FIX」のフロントバッファ描画領域
                LONG fix_width  = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH  * CONFIG::SCREEN_RATIO[pry].WIDTH;
                LONG fix_height = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT * CONFIG::SCREEN_RATIO[pry].HEIGHT;
                if (1.0f * CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH / CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[pry].left   = (CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[pry].top    = 0;
                    _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                    _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH / fix_width; //縮小率=横幅の比率
                    _aRect_Present[pry].left   = 0;
                    _aRect_Present[pry].top    = (CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                    _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                }
                setPositionPresentRect(CONFIG::SCREEN_PRESENT_POSITION[pry], _aRect_Present[pry],
                                       CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH, CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT);
            } else {
                //「フルスクリーンモード使用・縦横比ストレッチ」のフロントバッファ描画領域
                _aRect_Present[pry].left   = 0;
                _aRect_Present[pry].top    = 0;
                _aRect_Present[pry].right  = _aRect_Present[pry].left + CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
                _aRect_Present[pry].bottom = _aRect_Present[pry].top  + CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;
            }
        }

    } else {
        //ウィンドウモード
        for (int pry = PRIMARY_SCREEN; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
            //ウィンドウモード使用
            if (CONFIG::PRIMARY_SCREEN_ASPECT_RATIO_FIXED) {
                //「ウィンドウモード使用・縦横比FIX」のフロントバッファ描画領域
                LONG fix_width  = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].WIDTH  * CONFIG::SCREEN_RATIO[pry].WIDTH;
                LONG fix_height = CONFIG::SCREEN_RENDER_BUFFER_SOURCE[pry].HEIGHT * CONFIG::SCREEN_RATIO[pry].HEIGHT;
                if (1.0f * CONFIG::SCREEN_WINDOW[pry].WIDTH / CONFIG::SCREEN_WINDOW[pry].HEIGHT > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CONFIG::SCREEN_WINDOW[pry].HEIGHT / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[pry].left   = (CONFIG::SCREEN_WINDOW[pry].WIDTH / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[pry].top    = 0;
                    _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                    _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CONFIG::SCREEN_WINDOW[pry].WIDTH / fix_width; //縮小率=横幅の比率
                    _aRect_Present[pry].left   = 0;
                    _aRect_Present[pry].top    = (CONFIG::SCREEN_WINDOW[pry].HEIGHT / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[pry].right  = _aRect_Present[pry].left + (fix_width * rate);
                    _aRect_Present[pry].bottom = _aRect_Present[pry].top  + (fix_height * rate);
                }
                setPositionPresentRect(CONFIG::SCREEN_PRESENT_POSITION[pry], _aRect_Present[pry],
                                       CONFIG::SCREEN_WINDOW[pry].WIDTH, CONFIG::SCREEN_WINDOW[pry].HEIGHT);
            } else {
                //「ウィンドウモード使用・縦横比ストレッチ」のフロントバッファ描画領域
                _aRect_Present[pry].left   = 0;
                _aRect_Present[pry].top    = 0;
                _aRect_Present[pry].right  = _aRect_Present[pry].left + CONFIG::PRIMARY_SCREEN_WINDOW_WIDTH;
                _aRect_Present[pry].bottom = _aRect_Present[pry].top  + CONFIG::PRIMARY_SCREEN_WINDOW_HEIGHT;
            }
        }
    }

#ifdef MY_DEBUG
    _TRACE_("初期設定");
    _TRACE_(" _primary_screen_display_no = "<<_primary_screen_display_no );
    _TRACE_(" _secondary_screen_display_no = "<<_secondary_screen_display_no );
    if (Config::NUMBER_OF_SCREENS_USED > 1) {
        _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].left   = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].left  );
        _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].top    = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].top   );
        _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].right  = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].right );
        _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].bottom = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].bottom);
        _TRACE_(" _aRectRenderBufferSource[SECONDARY_SCREEN].left   = "<<_aRectRenderBufferSource[SECONDARY_SCREEN].left  );
        _TRACE_(" _aRectRenderBufferSource[SECONDARY_SCREEN].top    = "<<_aRectRenderBufferSource[SECONDARY_SCREEN].top   );
        _TRACE_(" _aRectRenderBufferSource[SECONDARY_SCREEN].right  = "<<_aRectRenderBufferSource[SECONDARY_SCREEN].right );
        _TRACE_(" _aRectRenderBufferSource[SECONDARY_SCREEN].bottom = "<<_aRectRenderBufferSource[SECONDARY_SCREEN].bottom);
        _TRACE_(" _aRect_Present[PRIMARY_SCREEN].left   = "<<_aRect_Present[PRIMARY_SCREEN].left  );
        _TRACE_(" _aRect_Present[PRIMARY_SCREEN].top    = "<<_aRect_Present[PRIMARY_SCREEN].top   );
        _TRACE_(" _aRect_Present[PRIMARY_SCREEN].right  = "<<_aRect_Present[PRIMARY_SCREEN].right );
        _TRACE_(" _aRect_Present[PRIMARY_SCREEN].bottom = "<<_aRect_Present[PRIMARY_SCREEN].bottom);
        _TRACE_(" _aRect_Present[SECONDARY_SCREEN].left   = "<<_aRect_Present[SECONDARY_SCREEN].left  );
        _TRACE_(" _aRect_Present[SECONDARY_SCREEN].top    = "<<_aRect_Present[SECONDARY_SCREEN].top   );
        _TRACE_(" _aRect_Present[SECONDARY_SCREEN].right  = "<<_aRect_Present[SECONDARY_SCREEN].right );
        _TRACE_(" _aRect_Present[SECONDARY_SCREEN].bottom = "<<_aRect_Present[SECONDARY_SCREEN].bottom);
    } else {
        _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].left   = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].left  );
        _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].top    = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].top   );
        _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].right  = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].right );
        _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].bottom = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].bottom);
        _TRACE_(" _aRect_Present[PRIMARY_SCREEN].left   = "<<_aRect_Present[PRIMARY_SCREEN].left  );
        _TRACE_(" _aRect_Present[PRIMARY_SCREEN].top    = "<<_aRect_Present[PRIMARY_SCREEN].top   );
        _TRACE_(" _aRect_Present[PRIMARY_SCREEN].right  = "<<_aRect_Present[PRIMARY_SCREEN].right );
        _TRACE_(" _aRect_Present[PRIMARY_SCREEN].bottom = "<<_aRect_Present[PRIMARY_SCREEN].bottom);
    }
#endif
}


int Caretaker::checkAppropriateDisplaySize(Caretaker::RezoInfo* prm_paRezos, int prm_rezo_num,
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

void Caretaker::createWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
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
            throwCriticalException("IDirect3D9Ex コンポーネント取得に失敗しました。(1)"); //失敗
        }
//        hr = pID3D9Ex->QueryInterface(IID_IDirect3D9, reinterpret_cast<void **>(&pID3D9)); //COMとして使用
//        if (FAILED(hr)) {
//            MessageBox(_pHWndPrimary, TEXT("IDirect3D9Ex コンポーネント取得に失敗しました。(2)"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
//            FreeLibrary(hD3D);
//            return E_FAIL; //失敗
//        }
        _pID3D9 = (IDirect3D9*)pID3D9Ex;
        _can_wddm = true;
        _TRACE_("WDDM モード");
    } else {
        _TRACE_("d3d9.dllに、Direct3DCreate9Exは存在しませんでした。");
        //d3d9.dll に Direct3DCreate9Ex は存在しない。
        pID3D9 = Direct3DCreate9(D3D_SDK_VERSION);
        if (!pID3D9) {
            FreeLibrary(hD3D);
            throwCriticalException("IDirect3D9 コンポーネント取得に失敗しました。");
        }
        _pID3D9 = pID3D9;
        _can_wddm = false;
        _TRACE_("XPDM モード");
    }
    FreeLibrary(hD3D);

    //デバイスパラメータ作成
    D3DCAPS9 caps;
    _pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] ディスプレイ アダプタを示す序数。
                           D3DDEVTYPE_HAL,     // [in] デバイスの種類。 D3DDEVTYPE列挙型のメンバ
                           &caps);             // [out] デバイスの能力が格納される

    _num_adapter = caps.NumberOfAdaptersInGroup;   //使えるアダプタの数取得
    _num_PresetPrm = _num_adapter > MAX_SCREENS ? _num_adapter : MAX_SCREENS; //D3DPRESENT_PARAMETERS数
    _TRACE_("_num_adapter = "<< _num_adapter);

    if (CONFIG::FULL_SCREEN) {
        if (Config::NUMBER_OF_SCREENS_USED > 1) {
            if (_num_adapter < Config::NUMBER_OF_SCREENS_USED) {
                throwCriticalException("NUMBER_OF_SCREENS_USED="<<(Config::NUMBER_OF_SCREENS_USED)<<"が範囲外です。"<<_num_adapter<<"画面のマルチモニタしか検出できません。");
            } else {
                if (_num_adapter < CONFIG::PRIMARY_SCREEN_DISPLAY_NO+1 || _num_adapter < CONFIG::SECONDARY_SCREEN_DISPLAY_NO+1) {
                    throwCriticalException("範囲外のディスプレイアダプタ番号を指定しています。アダプタ番号は 0～"<<_num_adapter-1<<" が有効です。\n"
                                               "PRIMARY_SCREEN_DISPLAY_NO="<<CONFIG::PRIMARY_SCREEN_DISPLAY_NO<<", "
                                               "SECONDARY_SCREEN_DISPLAY_NO="<<CONFIG::SECONDARY_SCREEN_DISPLAY_NO );
                } else if(_primary_screen_display_no == _secondary_screen_display_no) {
                    throwCriticalException("１画面目、２画面目とも、同じディスプレイアダプタ番号を指定しています。\n"
                                               "PRIMARY_SCREEN_DISPLAY_NO="<<CONFIG::PRIMARY_SCREEN_DISPLAY_NO<<", "
                                               "SECONDARY_SCREEN_DISPLAY_NO="<<CONFIG::SECONDARY_SCREEN_DISPLAY_NO );
                }
            }
        } else {
            if (_num_adapter < CONFIG::PRIMARY_SCREEN_DISPLAY_NO+1 ) {
                throwCriticalException("範囲外のディスプレイアダプタ番号を指定しています。アダプタ番号は 0～"<<_num_adapter-1<<" が有効です。\n"
                                           "PRIMARY_SCREEN_DISPLAY_NO="<<CONFIG::PRIMARY_SCREEN_DISPLAY_NO);
            } else {
                //_secondary_screen_display_no は、_primary_screen_display_no とかぶらないようにしておく
                //TODO:NUMBER_OF_SCREENS_USED化
                if (_secondary_screen_display_no == 0) {
                    _secondary_screen_display_no = _primary_screen_display_no + 1;
                } else {
                    _secondary_screen_display_no = _primary_screen_display_no - 1;
                }
            }
        }
    }

    //_paPresetPrm[] を設定していきます。
    _paPresetPrm = NEW D3DPRESENT_PARAMETERS[_num_PresetPrm];

    for (int pre_adp = 0; pre_adp < _num_PresetPrm; pre_adp++) {
        ZeroMemory(&_paPresetPrm[pre_adp], sizeof(D3DPRESENT_PARAMETERS));
    }
    for (int pre_adp = 0; pre_adp < _num_PresetPrm; pre_adp++) {
        //ウィンドウ時・フルスクリーン時共通
        _paPresetPrm[pre_adp].BackBufferCount        = 1;            //バックバッファの数
        _paPresetPrm[pre_adp].EnableAutoDepthStencil = TRUE;         //バックバッファの Zバッファの自動作成
        _paPresetPrm[pre_adp].AutoDepthStencilFormat = D3DFMT_D24S8; //深度ステンシルバッファ //D3DFMT_D16;
        _paPresetPrm[pre_adp].Flags                  = 0;            //0にしておく
        if (CONFIG::FULL_SCREEN) {
            //フルスクリーン時共通（全画面）
            _paPresetPrm[pre_adp].BackBufferFormat           = D3DFMT_X8R8G8B8; //D3DFMT_A8R8G8B8; //D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;
            _paPresetPrm[pre_adp].Windowed                   = false; //フルスクリーンモード時
            _paPresetPrm[pre_adp].FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //リフレッシュレート
            _paPresetPrm[pre_adp].PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT; //スワップのタイミング
            _paPresetPrm[pre_adp].SwapEffect                 = D3DSWAPEFFECT_DISCARD;
            _paPresetPrm[pre_adp].EnableAutoDepthStencil     = FALSE; //Zバッファの自動作成無効
            //【メモ】
            //EnableAutoDepthStencil = FALSE;
            //とすると、レンダリングステートの D3DRS_ZENABLE が FALSE になるだけのように見える。
            //従って「無効」にしただけであり、「使用不可」ではないのだろう・・・。
        } else {
            //ウィンドウ時共通（全ウィンドウ）
            _paPresetPrm[pre_adp].BackBufferFormat           = D3DFMT_UNKNOWN; //現在の表示モードフォーマット
            _paPresetPrm[pre_adp].Windowed                   = true; //ウィンドウモード時
            _paPresetPrm[pre_adp].FullScreen_RefreshRateInHz = 0; //リフレッシュレート
            _paPresetPrm[pre_adp].PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE; //即座
            _paPresetPrm[pre_adp].SwapEffect                 = D3DSWAPEFFECT_COPY; //TODO:Windowモードはこれ一択なのか？、D3DPRESENT_INTERVAL_ONE とかためす？
            _paPresetPrm[pre_adp].EnableAutoDepthStencil = TRUE; //Z バッファの自動作成
        }
    }

    //アンチアイリアスにできるかチェック
    DWORD qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;
//    if( SUCCEEDED(_pID3D9->CheckDeviceMultiSampleType(
//        D3DADAPTER_DEFAULT,
//        D3DDEVTYPE_HAL,
//        _paPresetPrm[_primary_screen_display_no].BackBufferFormat,  //TODO:ウィンドウモード時は
//        CONFIG::FULL_SCREEN ? FALSE : TRUE,
//        D3DMULTISAMPLE_2_SAMPLES,
//        &qualityLevels) ) )
//    {
//        if( SUCCEEDED(_pID3D9->CheckDeviceMultiSampleType(
//            D3DADAPTER_DEFAULT,
//            D3DDEVTYPE_HAL,
//            _paPresetPrm[_primary_screen_display_no].AutoDepthStencilFormat,
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

    //マルチサンプル
    for (int pre_adp = 0; pre_adp < _num_PresetPrm; pre_adp++) {
        if (pre_adp == _primary_screen_display_no || pre_adp == _secondary_screen_display_no) {
            _paPresetPrm[pre_adp].MultiSampleType = multiSampleType; //マルチサンプルの数
            _paPresetPrm[pre_adp].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0); //マルチサンプルの品質レベル
        } else {
            _paPresetPrm[pre_adp].MultiSampleType = D3DMULTISAMPLE_NONE;//D3DMULTISAMPLE_NONE;
            _paPresetPrm[pre_adp].MultiSampleQuality = 0;
        }
    }

    //バックバッファサイズ
    for (int pre_adp = 0; pre_adp < _num_PresetPrm; pre_adp++) {
        int pry = _mapAdpToPry[pre_adp];
        if (CONFIG::FULL_SCREEN) {
            //フルスクリーン時（フルスクリーンチェックで上書きされるかもしれないけどデフォルト値を設定)
            if (pry >= 0) {
                _paPresetPrm[pre_adp].BackBufferWidth  = CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
                _paPresetPrm[pre_adp].BackBufferHeight = CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;
            } else {
                //あまりの画面
                _paPresetPrm[pre_adp].BackBufferWidth  = CONFIG::PRIMARY_SCREEN_FULL_SCREEN_WIDTH;
                _paPresetPrm[pre_adp].BackBufferHeight = CONFIG::PRIMARY_SCREEN_FULL_SCREEN_HEIGHT;
            }
        } else {
            //ウィンドウ時 （実際には_paPresetPrm[_primary_screen_display_no] しか使用されない）
            _paPresetPrm[pre_adp].BackBufferWidth  = CONFIG::RENDER_TARGET_BUFFER_WIDTH;
            _paPresetPrm[pre_adp].BackBufferHeight = CONFIG::RENDER_TARGET_BUFFER_HEIGHT;
        }
    }

    _paDisplayMode = NEW D3DDISPLAYMODEEX[_num_PresetPrm];
    for (int pre_adp = 0; pre_adp < _num_PresetPrm; pre_adp++) {
        _paDisplayMode[pre_adp].Size = sizeof(_paDisplayMode[pre_adp]);
        _paDisplayMode[pre_adp].Width = _paPresetPrm[pre_adp].BackBufferWidth;
        _paDisplayMode[pre_adp].Height = _paPresetPrm[pre_adp].BackBufferHeight;
        _paDisplayMode[pre_adp].Format = _paPresetPrm[pre_adp].BackBufferFormat;
        _paDisplayMode[pre_adp].RefreshRate = _paPresetPrm[pre_adp].FullScreen_RefreshRateInHz;
        _paDisplayMode[pre_adp].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;
    }

    _papSwapChain = NEW IDirect3DSwapChain9*[_num_adapter];
    _papBackBuffer =NEW IDirect3DSurface9*[_num_adapter];
    for (int adp = 0; adp < _num_adapter; adp++) {
        _papSwapChain[adp] = nullptr;
        _papBackBuffer[adp] = nullptr;
    }
    _paAvailableAdapter = NEW Adapter[_num_adapter];
    _paAdapterRezos = NEW AdapterRezos[_num_adapter];
    pCARETAKER->setDisplaySizeInfo();
    pCARETAKER->setAppropriateDisplaySize();
    _paHWnd = NEW HWND[_num_PresetPrm];
    for (int pre_adp = 0; pre_adp < _num_PresetPrm; pre_adp++) {
        _paHWnd[pre_adp] = nullptr;
        _mapAdpToPry[pre_adp] = -1;
    }
    GgafCore::Rgb rgb = GgafCore::Rgb(CONFIG::BORDER_COLOR);
    prm_wndclass1.hbrBackground = CreateSolidBrush(RGB(rgb._red, rgb._green, rgb._blue));
    prm_wndclass2.hbrBackground = CreateSolidBrush(RGB(rgb._red, rgb._green, rgb._blue));
    // ウインドウの生成
    if (CONFIG::FULL_SCREEN) {
        if (Config::NUMBER_OF_SCREENS_USED > 1) {
            //フルスクリーンモード・２画面使用
            WNDCLASSEX wc = prm_wndclass2;
            wc.lpszClassName = "dummy"; //TODO:４画面時に大丈夫か要確認

            for (int adp = 0; adp < _num_adapter; adp++) {
                if (adp == _primary_screen_display_no) {
                    RegisterClassEx(&prm_wndclass1);
                    _paHWnd[_primary_screen_display_no] =
                            CreateWindowEx(
                                WS_EX_APPWINDOW,
                                prm_wndclass1.lpszClassName,
                                prm_title1,
                                WS_POPUP | WS_VISIBLE,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                _paPresetPrm[_primary_screen_display_no].BackBufferWidth,
                                _paPresetPrm[_primary_screen_display_no].BackBufferHeight,
                                HWND_DESKTOP,
                                nullptr,
                                prm_wndclass1.hInstance,
                                nullptr
                            );
                } else if (adp == _secondary_screen_display_no) {
                    RegisterClassEx(&prm_wndclass2);
                    _paHWnd[_secondary_screen_display_no] =
                            CreateWindowEx(
                                WS_EX_APPWINDOW,
                                prm_wndclass2.lpszClassName,
                                prm_title2,
                                WS_POPUP | WS_VISIBLE,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                _paPresetPrm[_secondary_screen_display_no].BackBufferWidth,
                                _paPresetPrm[_secondary_screen_display_no].BackBufferHeight,
                                HWND_DESKTOP,
                                nullptr,
                                prm_wndclass2.hInstance,
                                nullptr
                           );
                } else {
                    RegisterClassEx(&wc);
                    _paHWnd[adp] =
                            CreateWindowEx(
                                WS_EX_APPWINDOW,
                                wc.lpszClassName,
                                "dummy",
                                WS_POPUP | WS_VISIBLE,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                _paPresetPrm[adp].BackBufferWidth,
                                _paPresetPrm[adp].BackBufferHeight,
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
            _paHWnd[_primary_screen_display_no] =
                    CreateWindowEx(
                        WS_EX_APPWINDOW,
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        _paPresetPrm[_primary_screen_display_no].BackBufferWidth,
                        _paPresetPrm[_primary_screen_display_no].BackBufferHeight,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                    );
        }
    } else {
        if (Config::NUMBER_OF_SCREENS_USED > 1) {
            //ウインドモード・２窓使用
            RegisterClassEx(&prm_wndclass1);
            _paHWnd[_primary_screen_display_no] =
                    CreateWindow(
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        prm_dwStyle1,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CONFIG::PRIMARY_SCREEN_WINDOW_WIDTH,
                        CONFIG::PRIMARY_SCREEN_WINDOW_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                    );

            RegisterClassEx(&prm_wndclass2);
            _paHWnd[_secondary_screen_display_no] =
                    CreateWindow(
                        prm_wndclass2.lpszClassName,
                        prm_title2,
                        prm_dwStyle2,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CONFIG::SECONDARY_SCREEN_WINDOW_WIDTH,
                        CONFIG::SECONDARY_SCREEN_WINDOW_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass2.hInstance,
                        nullptr
                    );


        } else {
            //ウインドモード・１窓使用
            RegisterClassEx(&prm_wndclass1);
            _paHWnd[_primary_screen_display_no] =
                    CreateWindow(
                        prm_wndclass1.lpszClassName,
                        prm_title1,
                        prm_dwStyle1,  //枠なし WS_POPUP | WS_VISIBLE,
                        CW_USEDEFAULT,
                        CW_USEDEFAULT,
                        CONFIG::PRIMARY_SCREEN_WINDOW_WIDTH,
                        CONFIG::PRIMARY_SCREEN_WINDOW_HEIGHT,
                        HWND_DESKTOP,
                        nullptr,
                        prm_wndclass1.hInstance,
                        nullptr
                    );
        }
    }
    //Windowハンドルを個別指定
    _mapHwndToPry[nullptr] = -1;
    _mapHwndToDisplayNo[nullptr] = -1;

    for (int pre_adp = 0; pre_adp < _num_PresetPrm; pre_adp++) {
        HWND hwnd = _paHWnd[pre_adp]; //注意：アダプタ以上の要素には null が入っている
        _paPresetPrm[pre_adp].hDeviceWindow = hwnd;

        _mapAdpToPry[pre_adp] = -1;
        if (hwnd) {
            _mapHwndToDisplayNo[hwnd] = pre_adp;
            if (pre_adp == _primary_screen_display_no) {
                _mapAdpToPry[pre_adp] = PRIMARY_SCREEN;
                _mapHwndToPry[hwnd] = PRIMARY_SCREEN;
            } else if  (pre_adp == _secondary_screen_display_no) {
                _mapAdpToPry[pre_adp] = SECONDARY_SCREEN;
                _mapHwndToPry[hwnd] = SECONDARY_SCREEN;
            }
        }


        if (pre_adp == _primary_screen_display_no) {
            _mapPreAdpToPry[pre_adp] = PRIMARY_SCREEN;
        } else if (pre_adp == _secondary_screen_display_no) {
            _mapPreAdpToPry[pre_adp] = SECONDARY_SCREEN;
        }
    }
    _pHWndPrimary   = _paHWnd[_primary_screen_display_no];
    _pHWndSecondary = _paHWnd[_secondary_screen_display_no];

    //_pHWndPrimary の有無が
    //ウィンドウプロシージャの WM_SETFOCUS 時の排他になっているので、
    //２画面目 → １画面目の順で代入すること。
    out_hWnd1 = _pHWndPrimary;
    out_hWnd2 = _pHWndSecondary;

    if (!_pHWndPrimary) {
        throwCriticalException("プライマリウィンドウが作成出来ませんでした。");
    }
    if (CONFIG::FULL_SCREEN) {
        setFullScreenWindowPos();
    } else {
        //ウィンドウモード時、クライアント領域を所望の大きさにするため、
        //タイトルバー、リサイズボーダーの厚さを考慮し再設定。
        //ウィンドウモード時
        for (int pry = PRIMARY_SCREEN; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
            int adpter = CONFIG::SCREEN_DISPLAY_NO[pry];
            resetWindowsize(_paHWnd[adpter],
                    CONFIG::SCREEN_WINDOW[pry].WIDTH, CONFIG::SCREEN_WINDOW[pry].HEIGHT);
        }
    }

    //アクティブに
    for (int pry = PRIMARY_SCREEN; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
        int adpter = CONFIG::SCREEN_DISPLAY_NO[pry];
        ShowWindow(_paHWnd[adpter], SW_SHOWNORMAL);
        UpdateWindow(_paHWnd[adpter]);
    }

    _pCurveSrcManager = createCurveSourceManager();
    _pCurveManufManager = createCurveManufactureManager();

    //デバイス作成
    if (FAILED(initDevice())) {
        throwCriticalException("初期化に失敗しました。アプリケーションを起動出来ません。");
    }
}

void Caretaker::createWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                             const char* prm_title1   , const char* prm_title2,
                             HWND&       out_hWnd1    , HWND&       out_hWnd2) {
    createWindow( prm_wndclass1, prm_wndclass2,
                  prm_title1, prm_title2,
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  out_hWnd1, out_hWnd2   );
}

void Caretaker::createWindow(WNDCLASSEX& prm_wndclass1,
                             const char* prm_title1   ,
                             DWORD       prm_dwStyle1 ,
                             HWND&       out_hWnd1     ) {
    HWND hWnd2;
    WNDCLASSEX wcex2 = prm_wndclass1;
    wcex2.lpszClassName = "Gecchi Game App Framework (window[1])";
    createWindow( prm_wndclass1, wcex2,
                  prm_title1,    "Window_02",
                  prm_dwStyle1,  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  out_hWnd1,     hWnd2   );
}

void Caretaker::createWindow(WNDCLASSEX& prm_wndclass1,
                             const char* prm_title1   ,
                             HWND&       out_hWnd1     ) {
    createWindow( prm_wndclass1,
                  prm_title1,
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  out_hWnd1);
}

void Caretaker::createWindow(WNDPROC prm_WndProc,
                             const char* prm_title1, const char* prm_title2,
                             HWND&       out_hWnd1 , HWND&       out_hWnd2  ) {
    //ウィンドウ定義＆作成
    WNDCLASSEX wcex1;
    ZeroMemory(&wcex1, sizeof(WNDCLASSEX));
    wcex1.cbSize = sizeof(WNDCLASSEX);
    wcex1.style = CS_HREDRAW | CS_VREDRAW | CS_CLASSDC;
    wcex1.lpfnWndProc = (WNDPROC)prm_WndProc;
    wcex1.hInstance = _hInstance;
    wcex1.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex1.lpszClassName = "Gecchi Game App Framework (window[0])";
    WNDCLASSEX wcex2 = wcex1;
    wcex2.lpszClassName = "Gecchi Game App Framework (window[1])";

    createWindow( wcex1, wcex2,
                  prm_title1, prm_title2,
                  WS_OVERLAPPEDWINDOW, WS_OVERLAPPEDWINDOW,
                  out_hWnd1, out_hWnd2   );
}

void Caretaker::createWindow(WNDPROC prm_WndProc,
                      const char* prm_title1,
                      HWND& out_hWnd1) {
    HWND hWnd2;
    createWindow(prm_WndProc,
                 prm_title1, "Window_02",
                 out_hWnd1, hWnd2);
}

HRESULT Caretaker::initDevice() {

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
//    for (UINT Adapter = 0; Adapter < _pID3D9->GetAdapterCount(); Adapter++) {
//        D3DADAPTER_IDENTIFIER9 Identifier;
//        HRESULT Res;
//        Res = _pID3D9->GetAdapterIdentifier(Adapter, 0, &Identifier);
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
    _TRACE_("_primary_screen_display_no="<<_primary_screen_display_no);
    _TRACE_("_secondary_screen_display_no="<<_secondary_screen_display_no);
    for (int n = 0; n < _num_PresetPrm; n++) {
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
    _TRACE_("_pHWndPrimary="<<_pHWndPrimary);
    _TRACE_("_pHWndSecondary="<<_pHWndSecondary);

    HRESULT hr;
    //ピクセルシェーダー、頂点シェーダーバージョンチェック
    D3DCAPS9 caps;
    _pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] ディスプレイ アダプタを示す序数。
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
    UINT adapter = _primary_screen_display_no;
    if (CONFIG::FULL_SCREEN && Config::NUMBER_OF_SCREENS_USED > 1) {
        //＜フルスクリーン かつ デュアルビュー の場合＞
        //デバイス作成を試み _pID3DDevice9 へ設定する。
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
                        _TRACE_(FUNC_NAME<<" DirectXの初期化に失敗しました。マルチヘッドD3DCREATE_SOFTWARE_VERTEXPROCESSING : "<<CriticalException::getHresultMsg(hr));
                        MessageBox(_pHWndPrimary, "DirectXの初期化に失敗しました。\nマルチヘッドディスプレイ環境が存在していません。", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
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

        D3DDISPLAYMODEEX* pDISPLAYMODE = nullptr;
        if (CONFIG::FULL_SCREEN) {
            pDISPLAYMODE = &_paDisplayMode[_primary_screen_display_no];
        }

        //デバイス作成を試み _pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
            hr = D3DERR_NOTAVAILABLE;
        } else {
            hr = createDx9Device(adapter, D3DDEVTYPE_HAL, _pHWndPrimary,
                                 D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                 &_paPresetPrm[_primary_screen_display_no], pDISPLAYMODE);
    //                                           D3DCREATE_MIXED_VERTEXPROCESSING|D3DCREATE_MULTITHREADED,
    //                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
        }
        if (hr != D3D_OK) {
            if (_vs_v < D3DVS_VERSION(3, 0) || _ps_v < D3DPS_VERSION(3, 0)) {
                hr = D3DERR_NOTAVAILABLE;
            } else {
                hr = createDx9Device(adapter, D3DDEVTYPE_HAL, _pHWndPrimary,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                     &_paPresetPrm[_primary_screen_display_no], pDISPLAYMODE);
            }

            if (hr != D3D_OK) {
                if (_ps_v < D3DPS_VERSION(3, 0)) {
                    hr = D3DERR_NOTAVAILABLE;
                } else {
                    //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
                    hr = createDx9Device(adapter, D3DDEVTYPE_HAL, _pHWndPrimary,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                         &_paPresetPrm[_primary_screen_display_no], pDISPLAYMODE);
                }
                if (hr != D3D_OK) {
                    //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                    hr = createDx9Device(adapter, D3DDEVTYPE_REF, _pHWndPrimary,
                                         D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                         &_paPresetPrm[_primary_screen_display_no], pDISPLAYMODE);
                    if (hr != D3D_OK) {
                        //どのデバイスの作成も失敗した場合
                        _TRACE_(FUNC_NAME<<" DirectXの初期化に失敗しました。 "<<CriticalException::getHresultMsg(hr));
                        MessageBox(_pHWndPrimary, "DirectXの初期化に失敗しました。", "ERROR", MB_OK | MB_ICONSTOP | MB_SETFOREGROUND | MB_TOPMOST);
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
        hr = ((IDirect3DDevice9Ex*)_pID3DDevice9)->SetMaximumFrameLatency(0);
        checkDxException(hr, D3D_OK, "SetMaximumFrameLatency(0) に失敗しました。");
    }
    _pTextureManager = createTextureManager();
    _pModelManager = createModelManager();
    _pEffectManager = createEffectManager();
    Util::init();  //ユーティリティ準備
    Input::init(); //DirectInput準備
    Sound::init(); //DirectSound準備
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
    if (_can_wddm && CONFIG::FULL_SCREEN && Config::NUMBER_OF_SCREENS_USED > 1) {
        hr = releaseFullScreenRenderTarget();
        hr = restoreFullScreenRenderTarget();
    }
    return D3D_OK;
}

BOOL CALLBACK Caretaker::updateMoniterPixcoordCallback(HMONITOR hMonitor,
                                                       HDC hdcMonitor,
                                                       LPRECT lprcMonitor,
                                                       LPARAM dwData) {
    Caretaker* pCaretaker = (Caretaker*)dwData;
    MONITORINFOEX moniter_info;
    moniter_info.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMonitor, &moniter_info);

    for (int adapter_no = 0; adapter_no < pCaretaker->_num_adapter; adapter_no++) {
        Adapter& adpt = pCaretaker->_paAvailableAdapter[adapter_no];
        if (adpt.hMonitor == hMonitor) {
            adpt.rcMonitor = moniter_info.rcMonitor;
        }
    }
    return TRUE; //列挙を続行
}

HRESULT Caretaker::createDx9Device(UINT adapter,
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
        IDirect3D9Ex* pID3D9Ex = (IDirect3D9Ex*)_pID3D9;
        IDirect3DDevice9Ex* pID3DDevice9Ex;
        hr = pID3D9Ex->CreateDeviceEx(adapter,
                                      device_type,
                                      hFocusWindow,
                                      behavior_flags,
                                      pPresentationParameters,
                                      pFullscreenDisplayMode,
                                      &pID3DDevice9Ex
                                      );
        _pID3DDevice9 = (IDirect3DDevice9Ex*)pID3DDevice9Ex;
    } else {
        hr = _pID3D9->CreateDevice(adapter,
                                       device_type,
                                       hFocusWindow,
                                       behavior_flags,
                                       pPresentationParameters,
                                       &_pID3DDevice9
                                       );
    }
    return hr;
 }

HRESULT Caretaker::initDx9Device() {

    //【注意】本フレームワークのデフォルトのRenderStateを設定。
    //変更時は以下に影響がないか確認。
    // void Spacetime::draw() の描画時
    //FigureActor コンストラクタの以下のメンバの初期値
    // _zenable = true;
    // _zwriteenable = true;
    // _cull_enable = true;
    // _cull_mode_default = D3DCULL_CCW;
    // _cull_mode = _cull_mode_default

    //ライトをセット
    //    _pID3DDevice9->SetLight(0, &Caretaker::_d3dlight9_default);
    //ライトスイッチON
    //    _pID3DDevice9->LightEnable(0, TRUE);
    //_pID3DDevice9->LightEnable(0, FALSE);
    //レンダ時にライトの影響（陰影）を有効
    //    _pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);
    //レンダ時にライトの影響（陰影）を無効 (ピクセルシェーダーで行なうため）
    _pID3DDevice9->SetRenderState(D3DRS_LIGHTING, FALSE);
    //レンダ時、世界に共通のアンビエントライトを有効にしたように描く
    //   _pID3DDevice9->SetRenderState(D3DRS_AMBIENT, _ambient_brightness_default);

    // Zバッファを有効に
    _pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファを無効に
    //_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

    //Zバッファ書き込み可
    _pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //Zバッファ書き込み不可
    //_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );

    //D3DRENDERSTATE_ZFUNC

    //ステンシルテストの方法
    _pID3DDevice9->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS); //常にテストをパス
    //画に失敗した時にステンシルの値をどう変化させるか
    _pID3DDevice9->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); //変化なし
    //Zテストで失敗した場合のステンシル値の変化
    _pID3DDevice9->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); //変化なし


    //左（反時計回り）回りにカリング ∵左手座標系
    _pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //カリングしない
    //_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // ディザリング
    //_pID3DDevice9->SetRenderState(D3DRS_DITHERENABLE, TRUE );
    // マルチサンプリングアンチエイリアス(といってもフルスクリーンだけ？)↓TODO:まだ謎
    _pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
//    _pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK, 0x00ffffff);

    //ピクセル単位のアルファテストを有効
    _pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    //α設定はシェーダーに書く事にしたのでコメント
    // アルファブレンドＯＮ
    //    _pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //2段階目、半透明テクスチャを貼り付けたポリゴンとバックバッファ（レンダーターゲット）との合成
    //色の算出方法の設定
    //_pID3DDevice9->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD); //D3DBLENDOP_ADD=転送元に転送先が加算
    //合成係数
    //    //上に書く画像の合成法(シェーダーに影響)
    //    _pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC,D3DBLEND_SRCALPHA=普通に描く。ポリゴンのアルファ値の濃さで描く。アルファ値の値が高ければ高いほど、濃く描く。
    //    //下地の画像の合成法(シェーダーに影響)
    //    _pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //DIST,D3DBLEND_INVSRCALPHA=上に描くポリゴンのアルファ値の濃さによって、下地の描画を薄くする。



    //頂点カラーを無効にする
    //_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, FALSE );
    // _pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, TRUE );
    //    //面のアンビエント反射は、マテリアルを参照するように設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    _pID3DDevice9->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //面のデフューズ反射は、マテリアルを参照するように設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    _pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //面のエミッシブ反射は、マテリアルを参照する設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    _pID3DDevice9->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    //    //面のスペキュラ反射は、マテリアルを参照する設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    //    _pID3DDevice9->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

    //頂点αを使用するとき
    //_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1);

    //
    //
    // アンチエイリアスの指定
    //_pID3DDevice9->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    //_pID3DDevice9->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
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
    //_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);
    //_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK,0x7fffffff);

    //色合成も全てシェーダーで処理になったのでコメント
    //SetTextureStageStateは廃止？
    //  1段階目ポリゴンとテクスチャの合成方法設定
    //    //テクスチャーの色と、頂点カラーのDIFFUSE色を乗算するように設定
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    //    //テクスチャーのαと、頂点カラーのαを乗算するように設定
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    //    _pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);


    //Cameraへ移動した
    // VIEW変換（カメラ位置）設定
    //D3DXMATRIX _matView; // ビュー変換行列
    //    GGAF_DELETE_NULLABLE(_pVecCamFromPoint);
    //    GGAF_DELETE_NULLABLE(_pVecCamLookatPoint);
    //    GGAF_DELETE_NULLABLE(_pVecCamUp);

    //Cameraへ移動した
    // 射影変換（３Ｄ→平面）
    //D3DXMATRIX _matProj; // 射影変換行列
    //_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &_matProj);
    //HRESULT hr;
    //バックバッファをウィンドウBG色でクリア
    //ここではRenderTargetはまだ、通常のバックバッファである
//    hr = _pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
//    returnWhenFailed(hr, D3D_OK, "背景色(_color_border)の塗りつぶしよる、画面クリアに失敗しました。");
    return D3D_OK;
}


HRESULT Caretaker::restoreFullScreenRenderTarget() {
_TRACE_("restoreFullScreenRenderTarget() 1");

    if (!CONFIG::FULL_SCREEN) {
        _TRACE_("【警告】フルスクリーン時意外、呼び出し不要です。");
        return D3D_OK;
    }
    HRESULT hr;
    //描画先となるサーフェイスを別途作成（バックバッファ的な使用を行う）
    hr = _pID3DDevice9->CreateRenderTarget(
        CONFIG::RENDER_TARGET_BUFFER_WIDTH,
        CONFIG::RENDER_TARGET_BUFFER_HEIGHT,
        _paPresetPrm[_primary_screen_display_no].BackBufferFormat,
        D3DMULTISAMPLE_NONE, //D3DMULTISAMPLE_TYPE MultiSample,
        0, //DWORD MultisampleQuality,
        true, //BOOL Lockable,
        &_pRenderTextureSurface,
        nullptr //HANDLE* pHandle
    );
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャのサーフェイス取得に失敗しました。");
    hr = _pID3DDevice9->SetRenderTarget(0, _pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャへ SetRenderTarget 出来ませんでした。");

    //テクスチャに描画する際の深度バッファ用サーフェイスを別途作成
    hr = _pID3DDevice9->CreateDepthStencilSurface(
            CONFIG::RENDER_TARGET_BUFFER_WIDTH,
            CONFIG::RENDER_TARGET_BUFFER_HEIGHT,
            _paPresetPrm[_primary_screen_display_no].AutoDepthStencilFormat, //D3DFORMAT           Format,
            _paPresetPrm[_primary_screen_display_no].MultiSampleType,        //D3DMULTISAMPLE_TYPE MultiSample,
            _paPresetPrm[_primary_screen_display_no].MultiSampleQuality,     //DWORD               MultisampleQuality,
            TRUE,                                   //BOOL                Discard, SetDepthStencileSurface関数で深度バッファを変更した時にバッファを破棄するかどうか
            &_pRenderTextureZ,                      //IDirect3DSurface9** ppSurface,
            nullptr                                 //HANDLE*             pHandle 現在未使用
    );
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャのZバッファ作成に失敗しました。");
    //深度バッファ作成自動生成の、深度バッファ用サーフェイスを上記に変更
    hr =  _pID3DDevice9->SetDepthStencilSurface(_pRenderTextureZ);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャへ SetDepthStencilSurface 出来ませんでした。");
    //背景色でクリア
    hr = _pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    returnWhenFailed(hr, D3D_OK,  "クリア色(_color_border)の塗りつぶしよる、画面クリアに失敗しました。1");
    hr = _pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK,  "クリア色(_color_border)の塗りつぶしよる、画面クリアに失敗しました。2");
    hr = _pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    returnWhenFailed(hr, D3D_OK,  "クリア色(_color_border)の塗りつぶしよる、画面クリアに失敗しました。3");
    hr = _pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK,  "クリア色(_color_border)の塗りつぶしよる、画面クリアに失敗しました。4");

    //アダプタに関連付けられたスワップチェーンを取得してバックバッファ取得
    //ここは、 adapter 0, 1, 2, ･･･の順で GetSwapChain() すること
    if (Config::NUMBER_OF_SCREENS_USED > 1) {
        for (int adapter = 0; adapter < _num_adapter; adapter++) {
            hr = _pID3DDevice9->GetSwapChain( adapter, &_papSwapChain[adapter] );
            returnWhenFailed(hr, D3D_OK, "スワップチェイン取得に失敗しました(2)。adapter="<<adapter);
            hr = _papSwapChain[adapter]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_papBackBuffer[adapter] );
            returnWhenFailed(hr, D3D_OK, "スワップチェインから、ターゲットのバックバッファ取得に失敗しました(2)。adapter="<<adapter);
        }
    } else {
        hr = _pID3DDevice9->GetSwapChain( 0, &_papSwapChain[_primary_screen_display_no] );
        returnWhenFailed(hr, D3D_OK, "スワップチェイン取得に失敗しました。");
        hr = _papSwapChain[_primary_screen_display_no]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_papBackBuffer[_primary_screen_display_no] );
        returnWhenFailed(hr, D3D_OK, "スワップチェインから、ターゲットのバックバッファ取得に失敗しました。(3)");
    }

    //フルスクリーン時、バックバッファとフロントバッファを背景色で塗る
    if (Config::NUMBER_OF_SCREENS_USED > 1) {
        for (int adapter = 0; adapter < _num_adapter; adapter++) {
            int pry = _mapAdpToPry[adapter];
            if (pry >= 0) {
                hr = _pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRectRenderBufferSource[pry],
                        _papBackBuffer[adapter], &_aRect_FullScreen[pry],
                        D3DTEXF_NONE);
                checkDxException(hr, D3D_OK, "FULL_SCREEN "<<adapter<<"画面目、背景色塗に失敗しました。(1)\n"
                                             "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_papBackBuffer[adapter]="<<_papBackBuffer[adapter]);
            }
        }
    } else {
        hr = _pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRectRenderBufferSource[PRIMARY_SCREEN],
                _papBackBuffer[_primary_screen_display_no], &_aRect_FullScreen[PRIMARY_SCREEN],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN 背景色塗に失敗しました。(1)");
    }

    hr = _pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK, "Present(nullptr, nullptr, nullptr, nullptr)に失敗しました。");
    //フリップしてもう一度背景色で塗る
    if (Config::NUMBER_OF_SCREENS_USED > 1) {
        for (int adapter = 0; adapter < _num_adapter; adapter++) {
            int pry = _mapAdpToPry[adapter];
            if (pry >= 0) {
                hr = _pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRectRenderBufferSource[pry],
                        _papBackBuffer[adapter], &_aRect_FullScreen[pry],
                        D3DTEXF_NONE);
                checkDxException(hr, D3D_OK, "FULL_SCREEN "<<adapter<<"画面目、背景色塗に失敗しました。(2)\n"
                                             "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_papBackBuffer[adapter]="<<_papBackBuffer[adapter]);
            }
        }
    } else {
        hr = _pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRectRenderBufferSource[PRIMARY_SCREEN],
                _papBackBuffer[_primary_screen_display_no], &_aRect_FullScreen[PRIMARY_SCREEN],
                D3DTEXF_NONE
                );
        checkDxException(hr, D3D_OK, "FULL_SCREEN 背景色塗に失敗しました。(2)");
    }
    hr = _pID3DDevice9->Present(nullptr, nullptr, nullptr, nullptr);
    returnWhenFailed(hr, D3D_OK, "Present(nullptr, nullptr, nullptr, nullptr)に失敗しました。(2)");
    //↑無駄な感じだが、VISTAとXPの２画面目フルスクリーンモード時
    //  両対応させるのはこのようなコードしかないという結論。

    //フルスクリーンのウィンドウ位置を補正
    setFullScreenWindowPos();
    return D3D_OK;
}
void Caretaker::setFullScreenWindowPos() {
    EnumDisplayMonitors(nullptr, nullptr, Caretaker::updateMoniterPixcoordCallback, (LPARAM)this);
    if (Config::NUMBER_OF_SCREENS_USED > 1) {
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
            if (n == _primary_screen_display_no) {
                SetCursorPos(full_screen_x, full_screen_y);
            }
        }
    } else { //TODO:上と融合したい
        for (int n = 0; n < _num_adapter; n++) {
            if (n == _primary_screen_display_no) {
                pixcoord full_screen_x = _paAvailableAdapter[n].rcMonitor.left;
                pixcoord full_screen_y = _paAvailableAdapter[n].rcMonitor.top;
                _TRACE_("画面 adapter_no="<<n<<" の左上座標("<<full_screen_x<<","<<full_screen_y<<")");
                ShowWindow(_paHWnd[n], SW_SHOWNORMAL);
                UpdateWindow(_paHWnd[n]);
                SetWindowPos(_paHWnd[n],
                             HWND_TOPMOST,
                             full_screen_x, full_screen_y, 0, 0,
                             SWP_NOSIZE);
                SetCursorPos(full_screen_x, full_screen_y);
                break;
            }
        }
    }
}

HRESULT Caretaker::releaseFullScreenRenderTarget() {
    GGAF_RELEASE_BY_FROCE(_pRenderTextureSurface);
    GGAF_RELEASE_BY_FROCE(_pRenderTextureZ);
    for (int adapter_no = 0; adapter_no < _num_adapter; adapter_no++) {
        IDirect3DSurface9* p1 = _papBackBuffer[adapter_no];
        GGAF_RELEASE_BY_FROCE(p1);
        IDirect3DSwapChain9* p2 = _papSwapChain[adapter_no];
        GGAF_RELEASE_BY_FROCE(p2);
    }
    return D3D_OK;
}

void Caretaker::chengeToBorderlessFullWindow(HWND prm_pHWnd) {
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
    _adjustGameWindow = true;
}

void Caretaker::backToNomalWindow(HWND prm_pHWnd) {

    LONG lStyle  = GetWindowLong( prm_pHWnd, GWL_STYLE );
    lStyle &= ~WS_POPUP;
    lStyle |= WS_OVERLAPPEDWINDOW;
    lStyle  = SetWindowLong( prm_pHWnd, GWL_STYLE, lStyle );
    SetWindowPos( prm_pHWnd, NULL, 0, 0, 0, 0, (SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER|SWP_FRAMECHANGED) );
    ShowWindow(prm_pHWnd, SW_NORMAL);
    UpdateWindow(prm_pHWnd);
    _adjustGameWindow = true;
}

void Caretaker::presentMoment() {
#ifdef MY_DEBUG
    if (GgafDx::Input::isPushedDownKey(DIK_T)) {
        _TRACE_("ツリー構造 -->");
        _pSpacetime->dump();
        _TRACE_("<-- ツリー構造");
    }

#endif

    if (pCARETAKER->_is_device_lost_flg) {
        return;
    } else {
        GgafCore::Caretaker::presentMoment();
    }
}
void Caretaker::presentBehave() {
    if (pCARETAKER->_is_device_lost_flg) {
        return;
    } else {
        GgafCore::Caretaker::presentBehave();
    }
}
void Caretaker::presentJudge() {
    if (pCARETAKER->_is_device_lost_flg) {
        return;
    } else {
        GgafCore::Caretaker::presentJudge();
    }
}
void Caretaker::presentMaterialize() {
    if (pCARETAKER->_is_device_lost_flg) {
        return;
    }
    IDirect3DDevice9* pDevice = _pID3DDevice9;
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
    pDevice->SetRenderState(D3DRS_FILLMODE, pCARETAKER->_d3dfillmode);
#endif
    GgafCore::Caretaker::presentMaterialize(); //スーパーのmaterialize実行
    //描画事後処理
    hr = pDevice->EndScene();
    checkDxException(hr, D3D_OK, "pDevice->EndScene() に失敗しました。");

}

void Caretaker::presentVisualize() {
    IDirect3DDevice9* pDevice = _pID3DDevice9;
    //垂直帰線期間
    //if (_pID3DDevice9->Present(nullptr,&_aRect_Present[PRIMARY_SCREEN],nullptr,nullptr) == D3DERR_DEVICELOST) {
    //        static D3DRASTER_STATUS rs;
    //        while (SUCCEEDED(_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
    //            if(rs.InVBlank) {
    //                break; //垂直帰線期間ではない
    //            } else {
    //                Sleep(1);
    //            }
    //        }
    HRESULT hr;
    if (pCARETAKER->_is_device_lost_flg == false) {
        if (_adjustGameWindow) {
//            adjustGameWindow(_pHWndPrimary);
//            adjustGameWindow(_pHWndSecondary);
            adjustGameWindow();
        }

        //Present
        if (CONFIG::FULL_SCREEN) {
            //フルスクリーン
            for (int pry = PRIMARY_SCREEN; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
                int adapter = Config::SCREEN_DISPLAY_NO[pry];
                hr = pDevice->StretchRect(
                        _pRenderTextureSurface, &_aRectRenderBufferSource[pry],
                        _papBackBuffer[adapter], &_aRect_Present[pry],
                        D3DTEXF_LINEAR);
                //checkDxException(hr, D3D_OK, "FULL_SCREEN StretchRect() に失敗しました。");
            }
            hr = pDevice->Present(nullptr, nullptr, nullptr, nullptr);
//            if (CONFIG::DUAL_SCREEN) {
//                //２画面使用・フルスクリーン
//                hr = pDevice->StretchRect(
//                        _pRenderTextureSurface, &_aRectRenderBufferSource[PRIMARY_SCREEN],
//                        _papBackBuffer[_primary_screen_display_no], &_aRect_Present[PRIMARY_SCREEN],
//                        D3DTEXF_LINEAR); //TODO:D3DTEXF_LINEARをオプション指定にするか？
//                //checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_SCREEN 1画面目 StretchRect() に失敗しました。");
//                hr = pDevice->StretchRect(
//                        _pRenderTextureSurface, &_aRectRenderBufferSource[SECONDARY_SCREEN],
//                        _papBackBuffer[_secondary_screen_display_no], &_aRect_Present[SECONDARY_SCREEN],
//                        D3DTEXF_LINEAR);
//                //checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_SCREEN 2画面目 StretchRect() に失敗しました。");
//                hr = pDevice->Present(nullptr, nullptr, nullptr, nullptr);
//            } else {
//                //１画面使用・フルスクリーン
//                hr = pDevice->StretchRect(
//                        _pRenderTextureSurface, &_aRectRenderBufferSource[PRIMARY_SCREEN],
//                        _papBackBuffer[_primary_screen_display_no], &_aRect_Present[PRIMARY_SCREEN],
//                        D3DTEXF_LINEAR);
//                //checkDxException(hr, D3D_OK, "FULL_SCREEN StretchRect() に失敗しました。");
//                hr = pDevice->Present(nullptr, nullptr, nullptr, nullptr);
//            }
        } else {
            //ウィンドウモード
            for (int pry = PRIMARY_SCREEN; pry < CONFIG::NUMBER_OF_SCREENS_USED; ++pry) {
                int adapter = Config::SCREEN_DISPLAY_NO[pry];
                hr = pDevice->Present(&_aRectRenderBufferSource[pry], &_aRect_Present[pry], _paHWnd[adapter], nullptr);
            }
//            if (CONFIG::DUAL_SCREEN) {
//                //２画面使用・ウィンドウモード
//                hr = pDevice->Present(&_aRectRenderBufferSource[PRIMARY_SCREEN], &_aRect_Present[PRIMARY_SCREEN], _pHWndPrimary, nullptr);
//                if (hr == D3D_OK) {
//                    hr = pDevice->Present(&_aRectRenderBufferSource[SECONDARY_SCREEN], &_aRect_Present[SECONDARY_SCREEN], _pHWndSecondary, nullptr);
//                }
//            } else {
//                //１画面使用・ウィンドウモード
//                hr = pDevice->Present(&_aRectRenderBufferSource[PRIMARY_SCREEN], &_aRect_Present[PRIMARY_SCREEN], nullptr, nullptr);
//            }
        }
        if (hr == S_PRESENT_OCCLUDED) {
            _TRACE_("【情報】HRESULT = S_PRESENT_OCCLUDED ");
        }

        //S_PRESENT_OCCLUDEDは除外？
        if (hr != S_PRESENT_OCCLUDED && hr != D3D_OK) { //hr は Present の戻り値
             //出刃異素露巣斗？
//            _TRACE_("【警告】デバイス異常発生!!" <<DXGetErrorString(hr) << " "<< DXGetErrorDescription(hr));
            _TRACE_("【警告】デバイス異常発生!! HRESULT="<<hr);
            if (hr == D3DERR_DEVICELOST) {
                _TRACE_("通常の正常デバイスロスト！");
            } else {
                _TRACE_("通常のデバイスロストではないかも！");
            }

            Sleep(100);
            _TRACE_("【デバイスロスト処理】BEGIN ------>");

            //愛休止
            _TRACE_("【デバイスロスト処理】愛停止 BEGIN ------>");

            GgafCore::Caretaker::beginRest();
            for (int i = 0; GgafCore::Caretaker::isResting() == false; i++) {
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
            //エフェクト、デバイスロスト処理
            _TRACE_("【デバイスロスト処理】_pEffectManager->onDeviceLostAll() BEGIN ------>");
            _pEffectManager->onDeviceLostAll();
            _TRACE_("【デバイスロスト処理】_pEffectManager->onDeviceLostAll() <-------- END");
            //モデル解放
            _TRACE_("【デバイスロスト処理】_pModelManager->onDeviceLostAll() BEGIN ------>");
            _pModelManager->onDeviceLostAll();
            _TRACE_("【デバイスロスト処理】_pModelManager->onDeviceLostAll() <-------- END");
            //テクスチャ（モデルから生成されてないテクスチャ）、デバイスロスト処理。これはモデルより後に開放する必要がある。
            _TRACE_("【デバイスロスト処理】_pTextureManager->releaseAll() (モデルから生成されてないテクスチャ) BEGIN ------>");
            _pTextureManager->releaseAll();
            _TRACE_("【デバイスロスト処理】_pTextureManager->releaseAll() (モデルから生成されてないテクスチャ) <-------- END");
            //全ノードに解放しなさいイベント発令
            _TRACE_("【デバイスロスト処理】getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST) BEGIN ------>");
            getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST);
            _TRACE_("【デバイスロスト処理】getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST) <-------- END");
            _TRACE_("【デバイスロスト処理】リソース解放 <-------- END");
            pCARETAKER->_is_device_lost_flg = true;
            END_SYNCHRONIZED1; // <----- 排他終了
        }
    }

    if (pCARETAKER->_is_device_lost_flg) {
        _TRACE_("【デバイスロスト処理/リソース解放】協調性レベルチェック BEGIN ------>");
        //for (int i = 0; i < 300; i++) {
        while (true) {
            if (_can_wddm) {
                hr = ((IDirect3DDevice9Ex*)pDevice)->CheckDeviceState(_paPresetPrm[_primary_screen_display_no].hDeviceWindow);
                if (hr == D3DERR_DEVICELOST || hr == S_PRESENT_OCCLUDED) {
                    return; //D3DERR_DEVICELOST じゃなくなるまで待つ
                } else {
                    break;
                }
            } else {
                hr = pDevice->TestCooperativeLevel();
                if (hr == D3DERR_DEVICELOST) {
                    return; //D3DERR_DEVICELOST じゃなくなるまで待つ
                } else {
                    break;
                }
            }
        }
        _TRACE_("【デバイスロスト処理/リソース解放】協調性レベルチェック <-------- END");

        BEGIN_SYNCHRONIZED1; // ----->排他開始
        //解像度変更を考慮
        if (CONFIG::FULL_SCREEN) {
            //一旦戻す
            for (int pry = PRIMARY_SCREEN; pry < MAX_SCREENS; ++pry) {
                CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH = CONFIG::SCREEN_FULL_SCREEN_BK[pry].WIDTH;
                CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT = CONFIG::SCREEN_FULL_SCREEN_BK[pry].HEIGHT;
            }
            pCARETAKER->setDisplaySizeInfo();
            pCARETAKER->setAppropriateDisplaySize(false);
            //checkAppropriateDisplaySize() による解像度変更はしない
            //理由：画面ローテートで解像度を変更された場合、
            //その解像度から CONFIGの解像度へ、更に解像度を変更しようとすると
            //アプリ終了時に変更後の解像度のまま残るため？

            //バックバッファサイズ
            for (int pry = PRIMARY_SCREEN; pry < MAX_SCREENS; ++pry) {
                int adpter = Config::SCREEN_DISPLAY_NO[pry];
                _paPresetPrm[adpter].BackBufferWidth  = CONFIG::SCREEN_FULL_SCREEN[pry].WIDTH;
                _paPresetPrm[adpter].BackBufferHeight = CONFIG::SCREEN_FULL_SCREEN[pry].HEIGHT;
            }
            //下のrestoreFullScreenRenderTarget() で似たようなことをやってるのでいらんかも
            for (int pry = PRIMARY_SCREEN; pry < MAX_SCREENS; ++pry) {
                int adpter = Config::SCREEN_DISPLAY_NO[pry];
                SetWindowPos(_paHWnd[adpter], NULL, 0, 0,
                        _paPresetPrm[adpter].BackBufferWidth,
                        _paPresetPrm[adpter].BackBufferHeight,
                        SWP_NOMOVE | SWP_NOZORDER);
            }
        }
        //デバイスリセットを試みる
        _TRACE_("【デバイスロスト処理】デバイスリセット BEGIN ------>");
        for (int i = 0; i < 100*60*10; i++) {
            if (CONFIG::FULL_SCREEN && Config::NUMBER_OF_SCREENS_USED > 1) {
                hr = pDevice->Reset(_paPresetPrm);
            } else {
                hr = pDevice->Reset(&(_paPresetPrm[_primary_screen_display_no]));
            }
            if (hr != D3D_OK) {
                if (hr == D3DERR_DRIVERINTERNALERROR) {
                    Sleep(10);
                    return;
                } else if (hr == D3DERR_DRIVERINTERNALERROR) {
                    throwCriticalDxException(hr, "【デバイスロスト処理/デバイスリセット】D3DERR_DRIVERINTERNALERROR。強制終了します。");
                } else if (hr == D3DERR_OUTOFVIDEOMEMORY) {
                    throwCriticalDxException(hr, "【デバイスロスト処理/デバイスリセット】D3DERR_OUTOFVIDEOMEMORY。メモリがありません。強制終了します。");
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
        //テクスチャ（モデルからのテクスチャ以外）再設定（これはモデルより先にrestoreAll()する必要がある）
        _TRACE_("【デバイスロスト処理】_pTextureManager->restoreAll() (モデルから生成されてないテクスチャ) BEGIN ------>");
        _pTextureManager->restoreAll();
        _TRACE_("【デバイスロスト処理】_pTextureManager->restoreAll() (モデルから生成されてないテクスチャ) <-------- END");
        //エフェクトリセット
        _TRACE_("【デバイスロスト処理】_pEffectManager->restoreAll() BEGIN ------>");
        _pEffectManager->restoreAll();
        _TRACE_("【デバイスロスト処理】_pEffectManager->restoreAll() <-------- END");
        //モデル再設定
        _TRACE_("【デバイスロスト処理】_pModelManager->restoreAll() BEGIN ------>");
        _pModelManager->restoreAll();
        _TRACE_("【デバイスロスト処理】_pModelManager->restoreAll() <-------- END");

        //全ノードに再設定しなさいイベント発令
        _TRACE_("【デバイスロスト処理】getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST_RESTORE) BEGIN ------>");
        getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST_RESTORE);
        _TRACE_("【デバイスロスト処理】getSpacetime()->throwEventLowerTree(GGAF_EVENT_ON_DEVICE_LOST_RESTORE) <-------- END");
        //前回描画モデル情報を無効にする
        ModelManager::_pModelLastDraw = nullptr;
        pCARETAKER->_is_device_lost_flg = false;
        _TRACE_("【デバイスロスト処理】リソース再構築 <-------- END");
        END_SYNCHRONIZED1; // <----- 排他終了
        //愛再開
        _TRACE_("【デバイスロスト処理】愛再起動 BEGIN ------>");
        GgafCore::Caretaker::finishRest();
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

void Caretaker::presentClosing() {
    if (pCARETAKER->_is_device_lost_flg) {
        return;
    } else {
        GgafCore::Caretaker::presentClosing();
    }
}

void Caretaker::setLightDiffuseColor(float r, float g, float b) {
    _d3dlight9_default.Diffuse.r = r;
    _d3dlight9_default.Diffuse.g = g;
    _d3dlight9_default.Diffuse.b = b;
    //_d3dlight9_default.Range = 1000.0f;

}
void Caretaker::setLightAmbientColor(float r, float g, float b) {
    _d3dlight9_default.Ambient.r = r;
    _d3dlight9_default.Ambient.g = g;
    _d3dlight9_default.Ambient.b = b;
}

void Caretaker::clean() {
    _TRACE_(FUNC_NAME<<" begin");
    if (!_was_cleaned) {
        IDirect3DDevice9* pDevice = _pID3DDevice9;
        if (pDevice) {
            for (int i = 0; i < 8; ++i) { pDevice->SetTexture( i, nullptr ); }
            for (int i = 0; i < 8; ++i) { pDevice->SetStreamSource( i, nullptr, 0, 0 ); }
            pDevice->SetIndices( nullptr );
            pDevice->SetPixelShader( nullptr );
            pDevice->SetVertexShader( nullptr );
            pDevice->SetVertexDeclaration( nullptr );
        }
        _TRACE_(FUNC_NAME<<" GgafCore::Caretaker::clean() 開始");
        GgafCore::Caretaker::clean();
        _TRACE_(FUNC_NAME<<" GgafCore::Caretaker::clean() 終了");
        GgafCore::CmRandomNumberGenerator::getInstance()->release();
        //保持モデル解放

        _TRACE_(FUNC_NAME<<" _pModelManager 開放開始");
        GGAF_DELETE(_pModelManager);
        _TRACE_(FUNC_NAME<<" _pModelManager 開放終了");

        _TRACE_(FUNC_NAME<<" _pTextureManager(モデルから生成されてないテクスチャ) 開放開始");
        GGAF_DELETE(_pTextureManager);
        _TRACE_(FUNC_NAME<<" _pTextureManager(モデルから生成されてないテクスチャ) 開放終了");

        _TRACE_(FUNC_NAME<<" _pEffectManager 開放開始");
        GGAF_DELETE(_pEffectManager);
        _TRACE_(FUNC_NAME<<" _pModelManager 開放終了");


        _TRACE_(FUNC_NAME<<" _pCurveSrcManager 開放開始");
        GGAF_DELETE(_pCurveSrcManager);
        _TRACE_(FUNC_NAME<<" _pCurveSrcManager 開放終了");

        _TRACE_(FUNC_NAME<<" _pCurveManufManager 開放開始");
        GGAF_DELETE(_pCurveManufManager);
        _TRACE_(FUNC_NAME<<" _pCurveManufManager 開放終了");
    }
    _TRACE_(FUNC_NAME<<" end");
}

//void Caretaker::adjustGameWindow(HWND prm_pHWnd) {
void Caretaker::adjustGameWindow() {

    if (!CONFIG::FULL_SCREEN ) {
        //ウィンドウモード時
        HRESULT hr;
        hr = _pID3DDevice9->Clear(0, nullptr, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
        for (int n = 0; n < _num_PresetPrm; n++) {
            if (!_paHWnd[n]) {
                continue;
            }
            hr = _pID3DDevice9->Present(nullptr, nullptr, _paHWnd[n], nullptr);
        }

        for (int n = 0; n < _num_PresetPrm; n++) {
            if (!_paHWnd[n]) {
                continue;
            }
            RECT rect;
            if (::GetClientRect(_paHWnd[n], &rect)) {
                LONG c_width= rect.right;
                LONG c_height = rect.bottom;
                LONG fix_width, fix_height;
                int pos;
                if (_paHWnd[n] == _pHWndPrimary) {
                     pos = CONFIG::PRIMARY_SCREEN_PRESENT_POSITION;
                } else if (_paHWnd[n] == _pHWndSecondary) {
                     pos = CONFIG::SECONDARY_SCREEN_PRESENT_POSITION;
                }

                if ((_paHWnd[n] == _pHWndPrimary && CONFIG::PRIMARY_SCREEN_ASPECT_RATIO_FIXED) ||
                    (_paHWnd[n] == _pHWndSecondary && CONFIG::SECONDARY_SCREEN_ASPECT_RATIO_FIXED)	)
                {
                    //ウィンドウモード時・アスペクト比固定
                    if (_paHWnd[n] == _pHWndPrimary) {
                        fix_width  = CONFIG::PRIMARY_SCREEN_RENDER_BUFFER_SOURCE_WIDTH  * CONFIG::PRIMARY_SCREEN_WIDTH_RATIO;
                        fix_height = CONFIG::PRIMARY_SCREEN_RENDER_BUFFER_SOURCE_HEIGHT * CONFIG::PRIMARY_SCREEN_HEIGHT_RATIO;
                    } else if (_paHWnd[n] == _pHWndSecondary) {
                        fix_width  = CONFIG::SECONDARY_SCREEN_RENDER_BUFFER_SOURCE_WIDTH  * CONFIG::SECONDARY_SCREEN_WIDTH_RATIO;
                        fix_height = CONFIG::SECONDARY_SCREEN_RENDER_BUFFER_SOURCE_HEIGHT * CONFIG::SECONDARY_SCREEN_HEIGHT_RATIO;
                    }

                    if (1.0f * c_width / c_height > 1.0f * fix_width / fix_height) {
                        //より横長になってしまっている
                        double rate = 1.0 * c_height / fix_height; //縮小率=縦幅の比率

                        if (_paHWnd[n] == _pHWndPrimary) {
                            _aRect_Present[PRIMARY_SCREEN].left   = (c_width / 2.0) - (fix_width * rate / 2.0);
                            _aRect_Present[PRIMARY_SCREEN].top    = 0;
                            _aRect_Present[PRIMARY_SCREEN].right  = _aRect_Present[PRIMARY_SCREEN].left + (fix_width * rate);
                            _aRect_Present[PRIMARY_SCREEN].bottom = _aRect_Present[PRIMARY_SCREEN].top  + (fix_height * rate);
                            setPositionPresentRect(pos, _aRect_Present[PRIMARY_SCREEN], c_width, c_height);
                        } else if (_paHWnd[n]  == _pHWndSecondary) {
                            _aRect_Present[SECONDARY_SCREEN].left   = (c_width / 2.0) - (fix_width * rate / 2.0);
                            _aRect_Present[SECONDARY_SCREEN].top    = 0;
                            _aRect_Present[SECONDARY_SCREEN].right  = _aRect_Present[SECONDARY_SCREEN].left + (fix_width * rate);
                            _aRect_Present[SECONDARY_SCREEN].bottom = _aRect_Present[SECONDARY_SCREEN].top  + (fix_height * rate);
                            setPositionPresentRect(pos, _aRect_Present[SECONDARY_SCREEN], c_width, c_height);
                        }

                    } else {
                        //より縦長になってしまっている
                        double rate = 1.0 * c_width / fix_width; //縮小率=横幅の比率
                        if (_paHWnd[n] == _pHWndPrimary) {
                            _aRect_Present[PRIMARY_SCREEN].left   = 0;
                            _aRect_Present[PRIMARY_SCREEN].top    = (c_height / 2.0) - (fix_height * rate / 2.0);
                            _aRect_Present[PRIMARY_SCREEN].right  = _aRect_Present[PRIMARY_SCREEN].left + (fix_width * rate);
                            _aRect_Present[PRIMARY_SCREEN].bottom = _aRect_Present[PRIMARY_SCREEN].top  + (fix_height * rate);
                            setPositionPresentRect(pos, _aRect_Present[PRIMARY_SCREEN], c_width, c_height);
                        } else if (_paHWnd[n] == _pHWndSecondary) {
                            _aRect_Present[SECONDARY_SCREEN].left   = 0;
                            _aRect_Present[SECONDARY_SCREEN].top    = (c_height / 2.0) - (fix_height * rate / 2.0);
                            _aRect_Present[SECONDARY_SCREEN].right  = _aRect_Present[SECONDARY_SCREEN].left + (fix_width * rate);
                            _aRect_Present[SECONDARY_SCREEN].bottom = _aRect_Present[SECONDARY_SCREEN].top  + (fix_height * rate);
                            setPositionPresentRect(pos, _aRect_Present[SECONDARY_SCREEN], c_width, c_height);
                        }

                    }
                } else {
                    //ウィンドウモード時・縦横ストレッチ
                    if (::GetClientRect(_paHWnd[n], &rect)) {
                        if (_paHWnd[n] == _pHWndPrimary) {
                            _aRect_Present[PRIMARY_SCREEN] = rect;
                        } else if (_paHWnd[n] == _pHWndSecondary) {
                            _aRect_Present[SECONDARY_SCREEN] = rect;
                        }

                    }
                }

            }
        }

#ifdef MY_DEBUG
        //_TRACE_("Caretaker::adjustGameWindow(" << (prm_pHWnd == _pHWndPrimary ? "Primary" : "Secondary") <<") コール");
        if (Config::NUMBER_OF_SCREENS_USED > 1) {
            _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].left   = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].left  );
            _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].top    = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].top   );
            _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].right  = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].right );
            _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].bottom = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].bottom);
            _TRACE_(" _aRectRenderBufferSource[SECONDARY_SCREEN].left   = "<<_aRectRenderBufferSource[SECONDARY_SCREEN].left  );
            _TRACE_(" _aRectRenderBufferSource[SECONDARY_SCREEN].top    = "<<_aRectRenderBufferSource[SECONDARY_SCREEN].top   );
            _TRACE_(" _aRectRenderBufferSource[SECONDARY_SCREEN].right  = "<<_aRectRenderBufferSource[SECONDARY_SCREEN].right );
            _TRACE_(" _aRectRenderBufferSource[SECONDARY_SCREEN].bottom = "<<_aRectRenderBufferSource[SECONDARY_SCREEN].bottom);
            _TRACE_(" _aRect_Present[PRIMARY_SCREEN].left   = "<<_aRect_Present[PRIMARY_SCREEN].left  );
            _TRACE_(" _aRect_Present[PRIMARY_SCREEN].top    = "<<_aRect_Present[PRIMARY_SCREEN].top   );
            _TRACE_(" _aRect_Present[PRIMARY_SCREEN].right  = "<<_aRect_Present[PRIMARY_SCREEN].right );
            _TRACE_(" _aRect_Present[PRIMARY_SCREEN].bottom = "<<_aRect_Present[PRIMARY_SCREEN].bottom);
            _TRACE_(" _aRect_Present[SECONDARY_SCREEN].left   = "<<_aRect_Present[SECONDARY_SCREEN].left  );
            _TRACE_(" _aRect_Present[SECONDARY_SCREEN].top    = "<<_aRect_Present[SECONDARY_SCREEN].top   );
            _TRACE_(" _aRect_Present[SECONDARY_SCREEN].right  = "<<_aRect_Present[SECONDARY_SCREEN].right );
            _TRACE_(" _aRect_Present[SECONDARY_SCREEN].bottom = "<<_aRect_Present[SECONDARY_SCREEN].bottom);
        } else {
            _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].left   = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].left  );
            _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].top    = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].top   );
            _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].right  = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].right );
            _TRACE_(" _aRectRenderBufferSource[PRIMARY_SCREEN].bottom = "<<_aRectRenderBufferSource[PRIMARY_SCREEN].bottom);
            _TRACE_(" _aRect_Present[PRIMARY_SCREEN].left   = "<<_aRect_Present[PRIMARY_SCREEN].left  );
            _TRACE_(" _aRect_Present[PRIMARY_SCREEN].top    = "<<_aRect_Present[PRIMARY_SCREEN].top   );
            _TRACE_(" _aRect_Present[PRIMARY_SCREEN].right  = "<<_aRect_Present[PRIMARY_SCREEN].right );
            _TRACE_(" _aRect_Present[PRIMARY_SCREEN].bottom = "<<_aRect_Present[PRIMARY_SCREEN].bottom);
        }
#endif
    } else {
        //フルスクリーン時
    }
    Camera* pCam = getSpacetime()->getCamera();
    _pID3DDevice9->GetViewport(&(pCam->_viewport));
    _adjustGameWindow = false;
//    _pHWnd_adjustScreen = nullptr;
}

void Caretaker::setPositionPresentRect(int prm_pos, RECT& inout_rectPresent, pixcoord prm_screen_width, pixcoord prm_screen_height) {
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

TextureManager* Caretaker::createTextureManager() {
    TextureManager* p =  NEW TextureManager("TextureManager");
    return p;
}

ModelManager* Caretaker::createModelManager() {
    ModelManager* p =  NEW ModelManager("ModelManager");
    return p;
}

EffectManager* Caretaker::createEffectManager() {
    EffectManager* p = NEW EffectManager("EffectManager");
    return p;
}

CurveSourceManager* Caretaker::createCurveSourceManager() {
    CurveSourceManager* p = NEW CurveSourceManager("CurveSourceManager");
    return p;
}

CurveManufactureManager* Caretaker::createCurveManufactureManager() {
    CurveManufactureManager* p = NEW CurveManufactureManager("CurveManufactureManager");
    return p;
}

Caretaker::~Caretaker() {
    _TRACE_(FUNC_NAME<<" 解放開始");
    calmDown();
    clean();
    _was_cleaned = true;
    //DirectSound解放
    Sound::release();
    //DirectInput解放
    Input::release();

    if(CONFIG::FULL_SCREEN) {
        releaseFullScreenRenderTarget();
    }

    _TRACE_("_pID3DDevice9 解放来たわ");
    Sleep(60);
    GGAF_DELETEARR(_papSwapChain);
    GGAF_DELETEARR(_papBackBuffer);
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
//                           PRIMARY_SCREEN_WINDOW_WIDTH x PRIMARY_SCREEN_WINDOW_HEIGHT
//
//                                               ↑
//                                               ｜ Present
//                                               ｜(D3DSWAPEFFECT_COPY)
//                                               ｜
//                                  ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//    バックバッファ              ／                                        ／
//                              ／ _paPresetPrm[0].BackBufferWidthxHeight ／ 全面にDraw   ＿＿＿
//                            ／                                        ／       ←     ／    ／ゲームバッファ
//                            ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣                ￣￣￣GAME_BUFFER_WIDTH x GAME_BUFFER_HEIGHT
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
//                     PRIMARY_SCREEN_WINDOW_WIDTH x            SECONDARY_SCREEN_WINDOW_WIDTH x
//                       PRIMARY_SCREEN_WINDOW_HEIGHT             SECONDARY_SCREEN_WINDOW_HEIGHT
//
//                                 ↑                               ↑
//                                 ｜ Present                       ｜ Present
//                                 ｜(D3DSWAPEFFECT_COPY)           ｜ (D3DSWAPEFFECT_COPY)
//
//                                  ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//    バックバッファ              ／                                        ／
//                              ／ _paPresetPrm[0].BackBufferWidthxHeight ／ 全面にDraw   ＿＿＿
//                            ／                                        ／       ←     ／    ／ゲームバッファ
//                            ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣                ￣￣￣GAME_BUFFER_WIDTH x GAME_BUFFER_HEIGHT
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
//                                PRIMARY_SCREEN_FULL_SCREEN_WIDTH x
//                                  PRIMARY_SCREEN_FULL_SCREEN_HEIGHT
//
//                                                 ↑
//                                                 ｜ Present (flip)
//                                                 ｜(D3DSWAPEFFECT_DISCARD)
//                                                 ↓
//                                        ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//                                      ／                              ／
//                                    ／                              ／
//    バックバッファ                ／     _papBackBuffer[0]        ／
//                                ／                              ／
//                              ／                              ／
//                              ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣
//                               PRIMARY_SCREEN_FULL_SCREEN_WIDTH x
//                                 PRIMARY_SCREEN_FULL_SCREEN_HEIGHT
//
//                                                 ↑
//                                                 ｜ StretchRect
//                                                 ｜
//                                 ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//    レンダーターゲット         ／                                        ／
//    テクスチャー             ／       _pRenderTextureSurface           ／ 全面にDraw   ＿＿＿
//                           ／                                        ／       ←     ／    ／ゲームバッファ
//                           ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣                ￣￣￣GAME_BUFFER_WIDTH x GAME_BUFFER_HEIGHT
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
//                   PRIMARY_SCREEN_FULL_SCREEN_WIDTH x  |   SECONDARY_SCREEN_FULL_SCREEN_WIDTH x
//                     PRIMARY_SCREEN_FULL_SCREEN_HEIGHT |     SECONDARY_SCREEN_FULL_SCREEN_HEIGHT
//
//                               ↑                                 ↑
//                               ｜ Present (flip)                  ｜ Present (flip)
//                               ｜(D3DSWAPEFFECT_DISCARD)          ｜ (D3DSWAPEFFECT_DISCARD)
//                               ↓                                 ↓
//                            ＿＿＿＿＿＿＿＿＿＿＿             ＿＿＿＿＿＿＿＿＿＿＿
//                          ／                    ／           ／                    ／
//    バックバッファ      ／  _papBackBuffer[0] ／           ／ _papBackBuffer[1]  ／
//                      ／                    ／           ／                    ／
//                      ￣￣￣￣￣￣￣￣￣￣￣             ￣￣￣￣￣￣￣￣￣￣￣
//                     PRIMARY_SCREEN_FULL_SCREEN_WIDTH x        SECONDARY_SCREEN_FULL_SCREEN_WIDTH x
//                       PRIMARY_SCREEN_FULL_SCREEN_HEIGHT         SECONDARY_SCREEN_FULL_SCREEN_HEIGHT
//
//                                    ↑                            ↑
//                                    ｜ StretchRect                ｜ StretchRect
//                                    ｜                            ｜
//                                  ＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿＿
//    レンダーターゲット          ／                                        ／
//    テクスチャー              ／       _pRenderTextureSurface           ／ 全面にDraw   ＿＿＿
//                            ／                                        ／       ←     ／    ／ゲームバッファ
//                            ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣                ￣￣￣  GAME_BUFFER_WIDTH x GAME_BUFFER_HEIGHT
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


