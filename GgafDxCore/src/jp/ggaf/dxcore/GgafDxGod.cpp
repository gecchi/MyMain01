#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;

#define returnWhenFailed(HR, OKVAL, X) { \
    if (HR != OKVAL) { \
        std::stringstream ss; \
        ss << X; \
        MessageBox(GgafDxGod::_pHWndPrimary, TEXT(ss.str().c_str()), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND); \
        return E_FAIL; \
    } \
}

//TODO:コメントとか多すぎる。整理する。



HWND GgafDxGod::_pHWndPrimary = NULL;
HWND GgafDxGod::_pHWndSecondary = NULL;

IDirect3D9* GgafDxGod::_pID3D9 = NULL;
IDirect3DDevice9* GgafDxGod::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDxGod::_d3dlight9_default;
DWORD GgafDxGod::_dwAmbientBrightness_default = 0xff404040;


D3DFILLMODE GgafDxGod::_d3dfillmode = D3DFILL_SOLID;//D3DFILL_WIREFRAME;//D3DFILL_SOLID;

GgafDxModelManager* GgafDxGod::_pModelManager = NULL;
GgafDxEffectManager* GgafDxGod::_pEffectManager = NULL;
GgafDxTextureManager* GgafDxGod::_pCubeMapTextureManager = NULL;
GgafDxTextureManager* GgafDxGod::_pBumpMapTextureManager = NULL;
bool GgafDxGod::_is_device_lost_flg = false;
bool GgafDxGod::_adjustGameScreen = false;
HWND GgafDxGod::_pHWnd_adjustScreen = NULL;


UINT32 GgafDxGod::_vs_v = 0;
UINT32 GgafDxGod::_ps_v = 0;


GgafDxGod::GgafDxGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary) :
    GgafGod(prm_hInstance) {
    TRACE("GgafDxGod::GgafDxGod() ");

    GgafDxGod::_pHWndPrimary = prm_pHWndPrimary;
    GgafDxGod::_pHWndSecondary = prm_pHWndSecondary;
    _is_device_lost_flg = false;
    _adjustGameScreen = false;
    _pHWnd_adjustScreen = NULL;
    CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 Seed
    GgafRgb rgb_border = GgafRgb(GGAF_PROPERTY(BORDER_COLOR));
    _color_border = D3DCOLOR_RGBA(rgb_border._R, rgb_border._G, rgb_border._B, 0);
    GgafRgb rgb_bg = GgafRgb(GGAF_PROPERTY(BG_COLOR));
    _color_clear = D3DCOLOR_RGBA(rgb_bg._R, rgb_bg._G, rgb_bg._B, 0);
    _pRenderTexture = NULL;
    _pRenderTextureSurface = NULL;
    _pRenderTextureZ = NULL;
    _num_adapter = 1;
    _apSwapChain[0] = NULL;
    _apBackBuffer[0] = NULL;
    _apSwapChain[1] = NULL;
    _apBackBuffer[1] = NULL;

    _secondary_screen_x = 0;
    _secondary_screen_y = 0;

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
    _rectGameBuffer.right  = _rectGameBuffer.left + GGAF_PROPERTY(GAME_BUFFER_WIDTH);
    _rectGameBuffer.bottom = _rectGameBuffer.top  + GGAF_PROPERTY(GAME_BUFFER_HEIGHT);

    _rectRenderTargetBuffer.left   = 0;
    _rectRenderTargetBuffer.top    = 0;
    _rectRenderTargetBuffer.right  = _rectRenderTargetBuffer.left + GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH);
    _rectRenderTargetBuffer.bottom = _rectRenderTargetBuffer.top  + GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);

    if (GGAF_PROPERTY(SWAP_GAME_VIEW)) {
        _primary = 1;
        _secondary = 0;
    } else {
        _primary = 0;
        _secondary = 1;
    }
    _aRect_HarfGameBuffer[_primary].left   = 0;
    _aRect_HarfGameBuffer[_primary].top    = 0;
    _aRect_HarfGameBuffer[_primary].right  = _aRect_HarfGameBuffer[_primary].left  + GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_primary].bottom = _aRect_HarfGameBuffer[_primary].top + GGAF_PROPERTY(GAME_BUFFER_HEIGHT);

    _aRect_HarfGameBuffer[_secondary].left   = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_secondary].top    = 0;
    _aRect_HarfGameBuffer[_secondary].right  = _aRect_HarfGameBuffer[_secondary].left + GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_secondary].bottom = _aRect_HarfGameBuffer[_secondary].top  + GGAF_PROPERTY(GAME_BUFFER_HEIGHT);

    _aRect_HarfRenderTargetBuffer[_primary].left   = 0;
    _aRect_HarfRenderTargetBuffer[_primary].top    = 0;
    _aRect_HarfRenderTargetBuffer[_primary].right  = _aRect_HarfRenderTargetBuffer[_primary].left  + GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)/2;
    _aRect_HarfRenderTargetBuffer[_primary].bottom = _aRect_HarfRenderTargetBuffer[_primary].top + GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);

    _aRect_HarfRenderTargetBuffer[_secondary].left   = GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)/2;
    _aRect_HarfRenderTargetBuffer[_secondary].top    = 0;
    _aRect_HarfRenderTargetBuffer[_secondary].right  = _aRect_HarfRenderTargetBuffer[_secondary].left + GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)/2;
    _aRect_HarfRenderTargetBuffer[_secondary].bottom = _aRect_HarfRenderTargetBuffer[_secondary].top  + GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);

    //表示領域設定
    if (GGAF_PROPERTY(FULL_SCREEN)) {
        //フルスクリーンモード
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            _aRect_ViewScreen[0].top    = 0;
            _aRect_ViewScreen[0].left   = 0;
            _aRect_ViewScreen[0].right  = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
            _aRect_ViewScreen[0].bottom = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
            _aRect_ViewScreen[1].top    = 0;
            _aRect_ViewScreen[1].left   = 0;
            _aRect_ViewScreen[1].right  = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
            _aRect_ViewScreen[1].bottom = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);

            //フルスクリーンモード・２画面使用
            if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                //「フルスクリーンモード・２画面使用・縦横比FIX」の１画面目フロントバッファ描画領域
                if (1.0f * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[0].left   = (GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }

                //「フルスクリーンモード・２画面使用・縦横比FIX」の２画面目フロントバッファ描画領域
                if (1.0f * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[1].left   = (GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                }
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION1), _aRect_Present[0],
                                    GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH), GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT));
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2), _aRect_Present[1],
                                    GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH), GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT));
            } else {
                //「フルスクリーンモード・２画面使用・縦横比ストレッチ」の１画面目フロントバッファ描画領域
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
                //「フルスクリーンモード・２画面使用・縦横比ストレッチ」の２画面目フロントバッファ描画領域
                _aRect_Present[1].left   = 0;
                _aRect_Present[1].top    = 0;
                _aRect_Present[1].right  = _aRect_Present[1].left + GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
                _aRect_Present[1].bottom = _aRect_Present[1].top  + GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);
            }
        } else {
            //フルスクリーンモード・１画面使用
            _aRect_ViewScreen[0].top    = 0;
            _aRect_ViewScreen[0].left   = 0;
            _aRect_ViewScreen[0].right  = GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
            _aRect_ViewScreen[0].bottom = GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
            _aRect_ViewScreen[1] = _aRect_ViewScreen[0];

            if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = GGAF_PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                //「フルスクリーンモード・１画面使用・縦横比FIX」のフロントバッファ描画領域
                if (1.0f * GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[0].left   = (GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }
                _aRect_Present[1] = _aRect_Present[0];

                positionPresentRect(GGAF_PROPERTY(SINGLE_VIEW_DRAW_POSITION), _aRect_Present[0],
                                    GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT));
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2), _aRect_Present[1],
                                    GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT));
            } else {
                //「フルスクリーンモード・１画面使用・縦横比ストレッチ」のフロントバッファ描画領域
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
                _aRect_Present[1] = _aRect_Present[0];
            }
        }
    } else {
        //ウィンドウモード
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            //ウィンドウモード・２窓使用
            if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                //「ウィンドウモード・２窓使用・縦横比FIX」の１窓目フロントバッファ描画領域
                if (1.0f * GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[0].left   = (GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }

                //「ウィンドウモード・２窓使用・縦横比FIX」の２窓目フロントバッファ描画領域
                if (1.0f * GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[1].left   = (GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                }

                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION1), _aRect_Present[0],
                                    GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT));
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2), _aRect_Present[1],
                                    GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT));
            } else {
                //「ウィンドウモード・２窓使用・縦横比ストレッチ」の１窓目フロントバッファ描画領域
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + GGAF_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + GGAF_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT);
                //「ウィンドウモード・２窓使用・縦横比ストレッチ」の２窓目フロントバッファ描画領域
                _aRect_Present[1].left   = 0;
                _aRect_Present[1].top    = 0;
                _aRect_Present[1].right  = _aRect_Present[1].left + GGAF_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH);
                _aRect_Present[1].bottom = _aRect_Present[1].top  + GGAF_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT);
            }
        } else {
            //ウィンドウモード・１窓使用
            if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = GGAF_PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                //「ウィンドウモード・１窓使用・縦横比FIX」のフロントバッファ描画領域
                if (1.0f * GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[0].left   = (GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }
                _aRect_Present[1] = _aRect_Present[0];

                positionPresentRect(GGAF_PROPERTY(SINGLE_VIEW_DRAW_POSITION), _aRect_Present[0],
                                    GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
                positionPresentRect(GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2), _aRect_Present[1],
                                    GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
            } else {
                //「ウィンドウモード・１窓使用・縦横比ストレッチ」のフロントバッファ描画領域
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + GGAF_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + GGAF_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT);
                _aRect_Present[1] = _aRect_Present[0];
            }
        }
    }
    _TRACE_(" _aRect_Present[0].left   = "<<_aRect_Present[0].left  );
    _TRACE_(" _aRect_Present[0].top    = "<<_aRect_Present[0].top   );
    _TRACE_(" _aRect_Present[0].right  = "<<_aRect_Present[0].right );
    _TRACE_(" _aRect_Present[0].bottom = "<<_aRect_Present[0].bottom);
    _TRACE_(" _aRect_Present[1].left   = "<<_aRect_Present[1].left  );
    _TRACE_(" _aRect_Present[1].top    = "<<_aRect_Present[1].top   );
    _TRACE_(" _aRect_Present[1].right  = "<<_aRect_Present[1].right );
    _TRACE_(" _aRect_Present[1].bottom = "<<_aRect_Present[1].bottom);
}

HRESULT GgafDxGod::init() {
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
    IDirect3D9* pID3D9 = NULL;
    IDirect3D9Ex* pID3D9Ex = NULL;
    HMODULE hD3D = LoadLibrary(TEXT("d3d9.dll"));

    DIRECT3DCREATE9EXFUNCTION pFunc_Direct3DCreate9Ex = (DIRECT3DCREATE9EXFUNCTION)GetProcAddress(hD3D, "Direct3DCreate9Ex");
    if (pFunc_Direct3DCreate9Ex) {
        //d3d9.dll に Direct3DCreate9Ex は存在する。
        hr = ((*pFunc_Direct3DCreate9Ex)(D3D_SDK_VERSION, &pID3D9Ex)); //Direct3DCreate9Ex 実行
        if (FAILED(hr)) {
            MessageBox(GgafDxGod::_pHWndPrimary, TEXT("IDirect3D9Ex コンポーネント取得に失敗しました。(1)"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
            FreeLibrary(hD3D);
            return E_FAIL; //失敗
        }
//        hr = pID3D9Ex->QueryInterface(IID_IDirect3D9, reinterpret_cast<void **>(&pID3D9)); //COMとして使用
//        if (FAILED(hr)) {
//            MessageBox(GgafDxGod::_pHWndPrimary, TEXT("IDirect3D9Ex コンポーネント取得に失敗しました。(2)"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
//            FreeLibrary(hD3D);
//            return E_FAIL; //失敗
//        }
        GgafDxGod::_pID3D9 = (IDirect3D9*)pID3D9Ex;
        _can_wddm = true;
    } else {
        //d3d9.dll に Direct3DCreate9Ex は存在しない。
        pID3D9 = Direct3DCreate9(D3D_SDK_VERSION);
        if (!pID3D9) {
            MessageBox(GgafDxGod::_pHWndPrimary, TEXT("IDirect3D9 コンポーネント取得に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
            FreeLibrary(hD3D);
            return E_FAIL; //失敗
        }
        GgafDxGod::_pID3D9 = pID3D9;
        _can_wddm = false;
    }
    FreeLibrary(hD3D);

    //デバイスパラメータ作成
    D3DCAPS9 caps;
    GgafDxGod::_pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] ディスプレイ アダプタを示す序数。
                                       D3DDEVTYPE_HAL,     // [in] デバイスの種類。 D3DDEVTYPE列挙型のメンバ
                                       &caps);             // [out] デバイスの能力が格納される

    _num_adapter = caps.NumberOfAdaptersInGroup;   //使えるアダプタの数取得
    _paPresetPrm = NEW D3DPRESENT_PARAMETERS[_num_adapter > 2 ? _num_adapter : 2];
    ZeroMemory(&_paPresetPrm[0], sizeof(D3DPRESENT_PARAMETERS));

    //ウィンドウ時・フルスクリーン時共通
    _paPresetPrm[0].BackBufferCount        = 1;            //バックバッファの数
    _paPresetPrm[0].EnableAutoDepthStencil = TRUE;         //バックバッファの Zバッファの自動作成
    _paPresetPrm[0].AutoDepthStencilFormat = D3DFMT_D24S8; //深度ステンシルバッファ //D3DFMT_D16;
    _paPresetPrm[0].Flags                  = 0;            //0にしておく

    if (GGAF_PROPERTY(FULL_SCREEN)) {

        //フルスクリーン時
        _paPresetPrm[0].BackBufferFormat           = D3DFMT_X8R8G8B8; //D3DFMT_A8R8G8B8; //D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;
        _paPresetPrm[0].Windowed                   = false; //フルスクリーンモード時
        _paPresetPrm[0].FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //リフレッシュレート
        _paPresetPrm[0].PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT; //スワップのタイミング
        _paPresetPrm[0].SwapEffect                 = D3DSWAPEFFECT_DISCARD;

        if(GGAF_PROPERTY(DUAL_VIEW)) {
            _paPresetPrm[1] = _paPresetPrm[0]; //ココまでを複製

            _paPresetPrm[0].EnableAutoDepthStencil = FALSE;   //Zバッファの自動作成無効
            _paPresetPrm[1].EnableAutoDepthStencil = FALSE;
            //【メモ】
            //EnableAutoDepthStencil = FALSE;
            //とすると、レンダリングステートの D3DRS_ZENABLE が FALSE になるだけのように見える。
            //従って「無効」にしただけであり、「使用不可」ではないのだろう・・・。
        } else {
            _paPresetPrm[0].EnableAutoDepthStencil = FALSE; //Z バッファの自動作成有効
        }
    } else {
        //ウィンドウ時
        _paPresetPrm[0].BackBufferFormat           = D3DFMT_UNKNOWN; //現在の表示モードフォーマット
        _paPresetPrm[0].Windowed                   = true; //ウィンドウモード時
        _paPresetPrm[0].FullScreen_RefreshRateInHz = 0; //リフレッシュレート
        _paPresetPrm[0].PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE; //即座
        _paPresetPrm[0].SwapEffect                 = D3DSWAPEFFECT_COPY; //TODO:Windowモードはこれ一択なのか？、D3DPRESENT_INTERVAL_ONE とかためす？

        if(GGAF_PROPERTY(DUAL_VIEW)) {
            _paPresetPrm[1] = _paPresetPrm[0]; //ココまでを複製
            _paPresetPrm[0].EnableAutoDepthStencil = TRUE; //Z バッファの自動作成
            _paPresetPrm[1].EnableAutoDepthStencil = TRUE;
        } else {

            _paPresetPrm[0].EnableAutoDepthStencil = TRUE; //Z バッファの自動作成
        }


//        //デスプレイモードの取得
//        D3DDISPLAYMODE structD3DDisplayMode0; //結果が格納される構造体
//        hr = GgafDxGod::_pID3D9->GetAdapterDisplayMode(0, &structD3DDisplayMode0);
//        returnWhenFailed(hr, D3D_OK, "GetAdapterDisplayMode に失敗しました。");
//        if(GGAF_PROPERTY(DUAL_VIEW)) {
//            D3DDISPLAYMODE structD3DDisplayMode1;
//            hr = GgafDxGod::_pID3D9->GetAdapterDisplayMode(1, &structD3DDisplayMode1);
//            returnWhenFailed(hr, D3D_OK, "2画面目 GetAdapterDisplayMode に失敗しました");
//            _paPresetPrm[0].BackBufferFormat = structD3DDisplayMode0.Format; //現在の画面モードを利用
//            _paPresetPrm[1].BackBufferFormat = structD3DDisplayMode1.Format; //現在の画面モードを利用
//        } else {
//            _paPresetPrm[0].BackBufferFormat = structD3DDisplayMode0.Format; //現在の画面モードを利用
//            _paPresetPrm[1].BackBufferFormat = D3DFMT_UNKNOWN; //現在の画面モードを利用
//        }
    }

    //アンチアイリアスにできるかチェック
    DWORD qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;
//    if( SUCCEEDED(GgafDxGod::_pID3D9->CheckDeviceMultiSampleType(
//        D3DADAPTER_DEFAULT,
//        D3DDEVTYPE_HAL,
//        _paPresetPrm[0].BackBufferFormat,  //TODO:ウィンドウモード時は
//        GGAF_PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
//        D3DMULTISAMPLE_2_SAMPLES,
//        &qualityLevels) ) )
//    {
//        if( SUCCEEDED(GgafDxGod::_pID3D9->CheckDeviceMultiSampleType(
//            D3DADAPTER_DEFAULT,
//            D3DDEVTYPE_HAL,
//            _paPresetPrm[0].AutoDepthStencilFormat,
//            GGAF_PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
//            D3DMULTISAMPLE_2_SAMPLES,
//            NULL) ) )
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

    if(GGAF_PROPERTY(DUAL_VIEW)) {
        //マルチサンプルの数
        _paPresetPrm[0].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE; D3DMULTISAMPLE_2_SAMPLES
        //マルチサンプルの品質レベル
        _paPresetPrm[0].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);
        //マルチサンプルの数
        _paPresetPrm[1].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
        //マルチサンプルの品質レベル
        _paPresetPrm[1].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);
    } else {
        //マルチサンプルの数
        _paPresetPrm[0].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
        //マルチサンプルの品質レベル
        _paPresetPrm[0].MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);
    }

//    //マルチサンプルの数
//    _paPresetPrm[0].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
//    //マルチサンプルの品質レベル
//    _paPresetPrm[0].MultiSampleQuality = 0;//qualityLevels - (qualityLevels > 0 ? 1 : 0);





    //Windowハンドルを個別指定
    _paPresetPrm[0].hDeviceWindow = _pHWndPrimary;
    _paPresetPrm[1].hDeviceWindow = _pHWndSecondary;
    //バックバッファサイズ
    if (GGAF_PROPERTY(FULL_SCREEN)) {
        if(GGAF_PROPERTY(DUAL_VIEW)) {
            //フルスクリーンモード・２画面使用
            _paPresetPrm[0].BackBufferWidth  = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
            _paPresetPrm[0].BackBufferHeight = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
            _paPresetPrm[1].BackBufferWidth  = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
            _paPresetPrm[1].BackBufferHeight = GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);
        } else {
            //フルスクリーンモード・１画面使用
            _paPresetPrm[0].BackBufferWidth  = GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
            _paPresetPrm[0].BackBufferHeight = GGAF_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
            _paPresetPrm[1].BackBufferWidth  = 0;
            _paPresetPrm[1].BackBufferHeight = 0;
        }
    } else {
        if(GGAF_PROPERTY(DUAL_VIEW)) {
            //ウィンドウモード・２画面使用
            _paPresetPrm[0].BackBufferWidth  = GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH);
            _paPresetPrm[0].BackBufferHeight = GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);
            _paPresetPrm[1].BackBufferWidth  = 0;
            _paPresetPrm[1].BackBufferHeight = 0;
        } else {
            //ウィンドウモード・１画面使用
            _paPresetPrm[0].BackBufferWidth  = GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH);
            _paPresetPrm[0].BackBufferHeight = GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);
            _paPresetPrm[1].BackBufferWidth  = 0;
            _paPresetPrm[1].BackBufferHeight = 0;
        }
    }

    _paDisplayMode = NEW D3DDISPLAYMODEEX[_num_adapter > 2 ? _num_adapter : 2];
    _paDisplayMode[0].Size = sizeof(_paDisplayMode[0]);
    _paDisplayMode[0].Width = _paPresetPrm[0].BackBufferWidth;
    _paDisplayMode[0].Height = _paPresetPrm[0].BackBufferHeight;
    _paDisplayMode[0].Format = _paPresetPrm[0].BackBufferFormat;
    _paDisplayMode[0].RefreshRate = _paPresetPrm[0].FullScreen_RefreshRateInHz;
    _paDisplayMode[0].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

    _paDisplayMode[1].Size = sizeof(_paDisplayMode[1]);
    _paDisplayMode[1].Width = _paPresetPrm[1].BackBufferWidth;
    _paDisplayMode[1].Height = _paPresetPrm[1].BackBufferHeight;
    _paDisplayMode[1].Format = _paPresetPrm[1].BackBufferFormat;
    _paDisplayMode[1].RefreshRate = _paPresetPrm[1].FullScreen_RefreshRateInHz;
    _paDisplayMode[1].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

    //３画面目以降のパラメータをコピーで作成
    for (int i = 2; i < _num_adapter; i++) {
        _paPresetPrm[i] = _paPresetPrm[1];
        _paDisplayMode[i] = _paDisplayMode[1];
    }

    //フルスクリーンに出来るか調べる
    _TRACE_("_num_adapter = "<< _num_adapter);
    if (GGAF_PROPERTY(FULL_SCREEN)) {
        for (int disp_no = 0; disp_no <= (GGAF_PROPERTY(DUAL_VIEW) ? (_num_adapter-1) : 0); disp_no++) {
            int mode_num = GgafDxGod::_pID3D9->GetAdapterModeCount(disp_no,
                                                                    _paPresetPrm[0].BackBufferFormat);
            if (mode_num) {
                D3DDISPLAYMODE adp;
                for (int i = mode_num-1; i >= 0; i--) {
                    GgafDxGod::_pID3D9->EnumAdapterModes(disp_no,
                                                          _paPresetPrm[0].BackBufferFormat, i, &adp);
                    _TRACE_("disp_no["<<disp_no<<"].mode["<<i<<"]:"<<adp.Width<<"x"<<adp.Height);
                    if (disp_no > 1) {
                        //３画面目以降１画面目・２画面目の解像度以外の無難な解像度を探してそれに設定。
                        if (adp.Format == _paPresetPrm[disp_no].BackBufferFormat) {
                            if ((adp.Width  == _paPresetPrm[0].BackBufferWidth && adp.Height == _paPresetPrm[0].BackBufferHeight) ||
                                (adp.Width  == _paPresetPrm[1].BackBufferWidth && adp.Height == _paPresetPrm[1].BackBufferHeight)
                            ) {
                                //ダメ
                            } else {
                                _TRACE_("...USE!");
                                _paPresetPrm[disp_no].BackBufferWidth  = adp.Width;
                                _paPresetPrm[disp_no].BackBufferHeight = adp.Height;
                                _paDisplayMode[disp_no].Width  = _paPresetPrm[disp_no].BackBufferWidth;
                                _paDisplayMode[disp_no].Height = _paPresetPrm[disp_no].BackBufferHeight;
                                break;
                            }
                        }
                    } else {
                        //１画面目・２画面目は、プロパティ要求の解像度を探す
                        if (adp.Format == _paPresetPrm[disp_no].BackBufferFormat &&
                            adp.Width  == _paPresetPrm[disp_no].BackBufferWidth  &&
                            adp.Height == _paPresetPrm[disp_no].BackBufferHeight ) {
                            //OK
                            _TRACE_("...BINGO!");
                            break;
                        }
                    }
                    if (i == 0) {
                        //要求した使える解像度が見つからない
                        std::stringstream ss;
                        if (GGAF_PROPERTY(DUAL_VIEW)) {
                            ss << _paPresetPrm[disp_no].BackBufferWidth<<"x"<<_paPresetPrm[disp_no].BackBufferHeight<<" フルスクリーンモードにする事ができません。\n"<<
                                   (disp_no+1)<<"画面目の解像度の設定を確認してください。";
                        } else {
                            ss << _paPresetPrm[disp_no].BackBufferWidth<<"x"<<_paPresetPrm[disp_no].BackBufferHeight<<" フルスクリーンモードにする事ができません。\n"<<
                                    "解像度の設定を確認してください。";
                        }
                        MessageBox(GgafDxGod::_pHWndPrimary, TEXT(ss.str().c_str()), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                        return E_FAIL;
                    }
                }
            } else {
                MessageBox(GgafDxGod::_pHWndPrimary, TEXT("フルスクリーンモード可能な解像度情報が取得できませんでした。\nご使用のビデオカードではプログラムを実行できません。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                return E_FAIL;
            }
        }
    }

    //ピクセルシェーダー、頂点シェーダーバージョンチェック
    _vs_v = caps.VertexShaderVersion;
    _ps_v = caps.PixelShaderVersion;
    _TRACE_("Hardware Vertex Shader Version = "<<D3DSHADER_VERSION_MAJOR(_vs_v)<<"_"<<D3DSHADER_VERSION_MINOR(_vs_v));
    _TRACE_("Hardware Pixel Shader Version  = "<<D3DSHADER_VERSION_MAJOR(_ps_v)<<"_"<<D3DSHADER_VERSION_MINOR(_ps_v));
    if (_vs_v < D3DVS_VERSION(2, 0) || _ps_v < D3DPS_VERSION(2, 0)) {
        _TRACE_("ビデオカードハードの頂点シェーダーとピンクセルシェーダーは、共にバージョン 2_0 以上が推奨です。");
        _TRACE_("ご使用のビデオカードでは、正しく動作しない恐れがあります。");
    }

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


    if (GGAF_PROPERTY(FULL_SCREEN) && GGAF_PROPERTY(DUAL_VIEW)) {
        //＜フルスクリーン かつ デュアルビュー の場合＞
        //デバイス作成を試み GgafDxGod::_pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                             D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                             _paPresetPrm, _paDisplayMode);
        if (hr != D3D_OK) {
            _TRACE_("マルチヘッドD3DCREATE_HARDWARE_VERTEXPROCESSING : "<<GgafDxCriticalException::getHresultMsg(hr));

            //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
            hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                                 D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                 _paPresetPrm, _paDisplayMode);
            if (hr != D3D_OK) {
                _TRACE_("マルチヘッドD3DCREATE_HARDWARE_VERTEXPROCESSING : "<<GgafDxCriticalException::getHresultMsg(hr));

                //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDxGod::_pHWndPrimary,
                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                     _paPresetPrm, _paDisplayMode);
                if (hr != D3D_OK) {
                    _TRACE_("マルチヘッドD3DCREATE_SOFTWARE_VERTEXPROCESSING : "<<GgafDxCriticalException::getHresultMsg(hr));

                    //どのデバイスの作成も失敗した場合
                    MessageBox(GgafDxGod::_pHWndPrimary, TEXT("DirectXの初期化に失敗しました。\nマルチヘッドディスプレイ環境が存在していません。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                    return E_FAIL;
                } else {
                    _TRACE_("GgafDxGod::init デバイスは MULTI FULLSCRREEN REF で初期化できました。");
                }

            } else {
                _TRACE_("GgafDxGod::init デバイスは MULTI FULLSCRREEN HAL(soft vp) で初期化できました。");
            }

        } else {
            _TRACE_("GgafDxGod::init デバイスは MULTI FULLSCRREEN HAL(pure vp) で初期化できました。");
        }

    } else {
        //＜(フルスクリーン かつ デュアルビュー) 以外の場合＞
        //デバイス作成を試み GgafDxGod::_pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                             D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                             &_paPresetPrm[0], &_paDisplayMode[0]);
//                                           D3DCREATE_MIXED_VERTEXPROCESSING|D3DCREATE_MULTITHREADED,
//                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
        if (hr != D3D_OK) {
            //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
            hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDxGod::_pHWndPrimary,
                                 D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                 &_paPresetPrm[0], &_paDisplayMode[0]);
            if (hr != D3D_OK) {
                //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDxGod::_pHWndPrimary,
                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                     &_paPresetPrm[0], &_paDisplayMode[0]);
                if (hr != D3D_OK) {
                    //どのデバイスの作成も失敗した場合
                    MessageBox(GgafDxGod::_pHWndPrimary, TEXT("DirectXの初期化に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP | MB_SETFOREGROUND);
                    return E_FAIL;
                } else {
                    _TRACE_("GgafDxGod::init デバイスは REF で初期化できました。");
                }

            } else {
                _TRACE_("GgafDxGod::init デバイスは HAL(soft vp) で初期化できました。");
            }

        } else {
            _TRACE_("GgafDxGod::init デバイスは HAL(pure vp) で初期化できました。");
        }
    }

    //その他必要な初期化
    _pCubeMapTextureManager = NEW GgafDxTextureManager("CubeMapTexManager");
    _pBumpMapTextureManager = NEW GgafDxTextureManager("BumpMapTexManager");
    _pModelManager = NEW GgafDxModelManager("ModelManager");
    _pEffectManager = NEW GgafDxEffectManager("EffectManager");
    GgafDxUtil::init();  //ユーティリティ準備
    GgafDxInput::init(); //DirectInput準備
    GgafDxSound::init(); //DirectSound準備

    //デバイス初期化
    hr = initDx9Device();
    if (hr == E_FAIL) {
        return E_FAIL;
    }
    Sleep(1000);
    //フルスクリーン時、レンダリングターゲットテクスチャー作成
    if (GGAF_PROPERTY(FULL_SCREEN)) {
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
    if (_can_wddm && GGAF_PROPERTY(FULL_SCREEN) && GGAF_PROPERTY(DUAL_VIEW)) {
        hr = releaseFullScreenRenderTarget();
        hr = restoreFullScreenRenderTarget();
    }
    return D3D_OK;
}


//２画面目の左上座標を調べる
BOOL CALLBACK GgafDxGod::getSecondaryMoniterPixcoordCallback(HMONITOR hMonitor,
                                                             HDC hdcMonitor,
                                                             LPRECT lprcMonitor,
                                                             LPARAM dwData) {
    //３画面目以降の解像度は、１画面目・２画面目の解像度以外の無難な解像度に設定されていることが前提
    GgafDxGod* pGod = (GgafDxGod*)dwData;
    MONITORINFOEX moniter_info;
    moniter_info.cbSize = sizeof(MONITORINFOEX);
    GetMonitorInfo(hMonitor, &moniter_info);
    if (moniter_info.dwFlags != MONITORINFOF_PRIMARY) {
        //プライマリモニタでは無い
        if (moniter_info.rcMonitor.right - moniter_info.rcMonitor.left == GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) &&
           moniter_info.rcMonitor.bottom - moniter_info.rcMonitor.top == GGAF_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT)
        ) {
            //プライマリモニタでは無い、かつ２画面目の解像度に一致。
            //よって２画面目と見なす(正攻法でないなぁ・・・)

            //２画面目の左上座標を上書き保存
            pGod->_secondary_screen_x = moniter_info.rcMonitor.left;
            pGod->_secondary_screen_y = moniter_info.rcMonitor.top;
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

HRESULT GgafDxGod::createDx9Device(UINT Adapter,
                                   D3DDEVTYPE DeviceType,
                                   HWND hFocusWindow,
                                   DWORD BehaviorFlags,
                                   D3DPRESENT_PARAMETERS* pPresentationParameters,
                                   D3DDISPLAYMODEEX* pFullscreenDisplayMode
                                  ) {
    HRESULT hr;
    if (_can_wddm) {
        if (!GGAF_PROPERTY(FULL_SCREEN)) {
            pFullscreenDisplayMode = NULL;
        }
        IDirect3D9Ex* pID3D9Ex = (IDirect3D9Ex*)GgafDxGod::_pID3D9;
        IDirect3DDevice9Ex* pID3DDevice9Ex;
        hr = pID3D9Ex->CreateDeviceEx(Adapter,
                                      DeviceType,
                                      hFocusWindow,
                                      BehaviorFlags,
                                      pPresentationParameters,
                                      pFullscreenDisplayMode,
                                      &pID3DDevice9Ex
                                      );
        GgafDxGod::_pID3DDevice9 = (IDirect3DDevice9Ex*)pID3DDevice9Ex;
    } else {
        hr = GgafDxGod::_pID3D9->CreateDevice(Adapter,
                                              DeviceType,
                                              hFocusWindow,
                                              BehaviorFlags,
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
    //   GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, _dwAmbientBrightness_default);

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
    //    DELETE_POSSIBLE_NULL(_pVecCamFromPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamLookatPoint);
    //    DELETE_POSSIBLE_NULL(_pVecCamUp);

    //GgafDxCameraへ移動した
    // 射影変換（３Ｄ→平面）
    //D3DXMATRIX _matProj; // 射影変換行列
    //GgafDxGod::_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &_matProj);
    HRESULT hr;
    //バックバッファをウィンドウBG色でクリア
    //ここではRenderTargetはまだ、通常のバックバッファである
    hr = GgafDxGod::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    returnWhenFailed(hr, D3D_OK, "背景色(_color_border)の塗りつぶしよる、画面クリアに失敗しました。");
    return D3D_OK;
}


HRESULT GgafDxGod::restoreFullScreenRenderTarget() {
    if (!GGAF_PROPERTY(FULL_SCREEN)) {
        _TRACE_("GgafDxGod::restoreFullScreenRenderTarget() ＜警告＞フルスクリーン時意外、呼び出し不要です。");
        return D3D_OK;
    }
    HRESULT hr;
    //描画先となるテクスチャを別途作成（バックバッファ的な使用を行う）
    hr = GgafDxGod::_pID3DDevice9->CreateTexture(
                                        GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH),
                                        GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT),
                                        1, //MipLevel Mip無し
                                        D3DUSAGE_RENDERTARGET,
                                        _paPresetPrm[0].BackBufferFormat,
                                        D3DPOOL_DEFAULT,
                                        &_pRenderTexture,
                                        NULL);

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
//                     NULL,                      // [in] PALETTEENTRY *pPalette,
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


    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャ("<<GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)<<"x"<<GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT)<<")の作成に失敗。\nサイズを確認して下さい。");
    //RenderTarget(描画先)をテクスチャへ切り替え
    hr = _pRenderTexture->GetSurfaceLevel(0, &_pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャのサーフェイス取得に失敗しました。");
    hr = GgafDxGod::_pID3DDevice9->SetRenderTarget(0, _pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャへ SetRenderTarget 出来ませんでした。");


    //テクスチャに描画する際の深度バッファ用サーフェイスを別途作成
    hr = GgafDxGod::_pID3DDevice9->CreateDepthStencilSurface(
            GGAF_PROPERTY(RENDER_TARGET_BUFFER_WIDTH),
            GGAF_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT),
            _paPresetPrm[0].AutoDepthStencilFormat, //D3DFORMAT           Format,
            _paPresetPrm[0].MultiSampleType,        //D3DMULTISAMPLE_TYPE MultiSample,
            _paPresetPrm[0].MultiSampleQuality,     //DWORD               MultisampleQuality,
            TRUE,                                   //BOOL                Discard, SetDepthStencileSurface関数で深度バッファを変更した時にバッファを破棄するかどうか
            &_pRenderTextureZ,                      //IDirect3DSurface9** ppSurface,
            NULL                                    //HANDLE*             pHandle 現在未使用
    );
    //深度バッファ作成自動生成の、深度バッファ用サーフェイスを上記に変更
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャのZバッファ作成に失敗しました。");
    hr =  GgafDxGod::_pID3DDevice9->SetDepthStencilSurface(_pRenderTextureZ);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャへ SetDepthStencilSurface 出来ませんでした。");
    //背景色でクリア
    hr = GgafDxGod::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
    hr = GgafDxGod::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
    returnWhenFailed(hr, D3D_OK,  "クリア色(_color_border)の塗りつぶしよる、画面クリアに失敗しました。");

    //アダプタに関連付けられたスワップチェーンを取得してバックバッファ取得
    hr = GgafDxGod::_pID3DDevice9->GetSwapChain( 0, &_apSwapChain[0] );
    returnWhenFailed(hr, D3D_OK, "スワップチェイン取得に失敗しました。");
    hr = _apSwapChain[0]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_apBackBuffer[0] );
    returnWhenFailed(hr, D3D_OK, "スワップチェインから、ターゲットのバックバッファ取得に失敗しました。");
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        hr = GgafDxGod::_pID3DDevice9->GetSwapChain( 1, &_apSwapChain[1] );
        returnWhenFailed(hr, D3D_OK, "２画面目のスワップチェイン取得に失敗しました。\nマルチディスプレイ環境に問題発生しました。");
        hr = _apSwapChain[1]->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_apBackBuffer[1] );
        returnWhenFailed(hr, D3D_OK, "２画面目のスワップチェインから、ターゲットのバックバッファ取得に失敗しました。");
    }

    //フルスクリーン時、バックバッファとフロントバッファを背景色で塗る
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[0],
                _apBackBuffer[0]      , &_aRect_ViewScreen[0],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1画面目、背景色塗に失敗しました。(1)\n"<<
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);

        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[1],
                _apBackBuffer[1]      , &_aRect_ViewScreen[1],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 2画面目、背景色塗に失敗しました。(1)\n"<<
                                      "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);
    } else {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_rectRenderTargetBuffer,
                _apBackBuffer[0]      , &_aRect_ViewScreen[0],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN 背景色塗に失敗しました。(1)");
    }

    hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
    returnWhenFailed(hr, D3D_OK, "Present(NULL, NULL, NULL, NULL)に失敗しました。");
    //フリップしてもう一度背景色で塗る
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[0],
                _apBackBuffer[0]      , &_aRect_ViewScreen[0],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1画面目、背景色塗に失敗しました。(2)\n"<<
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);

        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[1],
                _apBackBuffer[1]      , &_aRect_ViewScreen[1],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 2画面目、背景色塗に失敗しました。(2)\n"<<
                                      "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);
    } else {
        hr = GgafDxGod::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_rectRenderTargetBuffer,
                _apBackBuffer[0]      , &_aRect_ViewScreen[0],
                D3DTEXF_NONE
                );
        checkDxException(hr, D3D_OK, "FULL_SCREEN 背景色塗に失敗しました。(2)");
    }
    //↑無駄な感じだが、VISTAとXPの２画面目フルスクリーンモード時
    //  両対応させるのはこのようなコードしかないという結論。


    if (GGAF_PROPERTY(DUAL_VIEW)) {
        //２画面目のウィンドウ位置を補正
        EnumDisplayMonitors(NULL, NULL, GgafDxGod::getSecondaryMoniterPixcoordCallback, (LPARAM)this);
        _TRACE_("２画面目の座標("<<_secondary_screen_x<<","<<_secondary_screen_y<<")");
        ShowWindow(_pHWndSecondary, SW_SHOWNORMAL);
        UpdateWindow(_pHWndSecondary);
        SetWindowPos(_pHWndSecondary,
                     HWND_TOPMOST,
                     _secondary_screen_x, _secondary_screen_y, 0, 0,
                     SWP_SHOWWINDOW | SWP_NOSIZE );
        //↑これを行なっておかないと、初回起動時、２画面目の領域をクリックした際、
        //再びフルスクリーンが解除されてしまう。
        //１画面目はフルスクリーンになっても、Windowの左上が(0,0)のためズレないので、
        //SetWindowPosはたぶん不要。しかし念のために同様の処理を行う。
        ShowWindow(_pHWndPrimary, SW_SHOWNORMAL);
        UpdateWindow(_pHWndPrimary);
        SetWindowPos(_pHWndPrimary,
                     HWND_TOPMOST,
                     0, 0, 0, 0,
                     SWP_SHOWWINDOW | SWP_NOSIZE);
    } else {
        ShowWindow(_pHWndPrimary, SW_SHOWNORMAL);
        UpdateWindow(_pHWndPrimary);
        SetWindowPos(_pHWndPrimary,
                     HWND_TOPMOST,
                     0, 0, 0, 0,
                     SWP_SHOWWINDOW | SWP_NOSIZE);
    }

    return D3D_OK;
}



HRESULT GgafDxGod::releaseFullScreenRenderTarget() {
    RELEASE_SAFETY(_pRenderTextureSurface);
    RELEASE_SAFETY(_pRenderTexture);
    RELEASE_SAFETY(_pRenderTextureZ);
    RELEASE_SAFETY(_apBackBuffer[0]);
    RELEASE_SAFETY(_apSwapChain[0]);
    if (GGAF_PROPERTY(DUAL_VIEW)) {
        RELEASE_SAFETY(_apBackBuffer[1]);
        RELEASE_SAFETY(_apSwapChain[1]);
    }
    return D3D_OK;
}

void GgafDxGod::presentUniversalMoment() {
    if (_is_device_lost_flg) {
        return;
    } else {
        GgafGod::presentUniversalMoment();
    }
}

void GgafDxGod::executeUniversalJudge() {
    if (_is_device_lost_flg) {
        return;
    } else {
        GgafGod::executeUniversalJudge();
    }
}
void GgafDxGod::makeUniversalMaterialize() {
    if (_is_device_lost_flg) {
        return;
    }
    TRACE("GgafDxGod::materialize() start");
    HRESULT hr;
        //通常時処理

    //バッファクリア
    hr = GgafDxGod::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                         NULL, // 矩形領域
                                         D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                         _color_clear, //クリア色（not 背景色）
                                         1.0f,         // Zバッファのクリア値
                                         0             // ステンシルバッファのクリア値
                                        );
    checkDxException(hr, D3D_OK, "GgafDxGod::_pID3DDevice9->Clear() に失敗しました。");

    //描画事前処理
    hr = GgafDxGod::_pID3DDevice9->BeginScene();
    checkDxException(hr, D3D_OK, "GgafDxGod::_pID3DDevice9->BeginScene() に失敗しました。");
    //全て具現化！（描画）
#ifdef MY_DEBUG
    GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDxGod::_d3dfillmode);
#endif
    GgafGod::makeUniversalMaterialize(); //スーパーのmaterialize実行
    //描画事後処理
    hr = GgafDxGod::_pID3DDevice9->EndScene();
    checkDxException(hr, D3D_OK, "GgafDxGod::_pID3DDevice9->EndScene() に失敗しました。");

    TRACE("GgafDxGod::makeUniversalMaterialize() end");
}

void GgafDxGod::presentUniversalVisualize() {
    //垂直帰線期間
    //if (GgafDxGod::_pID3DDevice9->Present(NULL,&_aRect_Present[0],NULL,NULL) == D3DERR_DEVICELOST) {
    //        static D3DRASTER_STATUS rs;
    //        while (SUCCEEDED(GgafDxGod::_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
    //            if(rs.InVBlank) {
    //                break; //垂直帰線期間ではない
    //            } else {
    //                Sleep(1);
    //            }
    //        }
    HRESULT hr;
    if (_is_device_lost_flg != true) {
        if (_adjustGameScreen && _pHWnd_adjustScreen) {
            adjustGameScreen(_pHWndPrimary);
            adjustGameScreen(_pHWndSecondary);
        }

        //Present
        if (GGAF_PROPERTY(FULL_SCREEN)) {
            if (GGAF_PROPERTY(DUAL_VIEW)) {
                //２画面使用・フルスクリーン
                //画面０バックバッファを画面１バックバッファへコピーする
                hr = GgafDxGod::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[0],
                        _apBackBuffer[0]      , &_aRect_Present[0],
                        D3DTEXF_LINEAR); //TODO:D3DTEXF_LINEARをオプション指定にするか？
                checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1画面目 StretchRect() に失敗しました。\n_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_apBackBuffer[0]="<<_apBackBuffer[0]);

                hr = GgafDxGod::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[1],
                        _apBackBuffer[1]      , &_aRect_Present[1],
                        D3DTEXF_LINEAR);
                checkDxException(hr, D3D_OK, "StretchRect() に失敗しました。");

                hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
            } else {
                //１画面使用・フルスクリーン
                hr = GgafDxGod::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface,
                        &_rectRenderTargetBuffer,
                        _apBackBuffer[0],
                        &_aRect_Present[0],
                        D3DTEXF_LINEAR);
                checkDxException(hr, D3D_OK, "FULL 1gamen StretchRect() に失敗しました。");

                hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
            }
        } else {
            if (GGAF_PROPERTY(DUAL_VIEW)) {
                //２画面使用・ウィンドウモード
                if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                    //縦横比固定モード
                    hr = GgafDxGod::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[0], &_aRect_Present[0], NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDxGod::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[1], &_aRect_Present[1], _pHWndSecondary, NULL);
                    }
                } else {
                    //縦横ストレッチモード
                    hr = GgafDxGod::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[0], NULL, NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDxGod::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[1], NULL, _pHWndSecondary, NULL);
                    }
                }
            } else {
                //１画面使用・ウィンドウモード
                if (GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                    //縦横比固定モード
                    hr = GgafDxGod::_pID3DDevice9->Present(NULL, &_aRect_Present[0], NULL, NULL);
                } else {
                    //縦横ストレッチモード
                    hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
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

            Sleep(100); // 1秒待つ
            _TRACE_("【デバイスロスト処理】BEGIN ------>");

            //工場休止
            _TRACE_("【デバイスロスト処理】工場停止 BEGIN ------>");
            int cnt = 0;
            GgafFactory::beginRest();
         ___EndSynchronized1; // <----- 排他終了
            for (int i = 0; GgafFactory::isResting() == false; i++) {
                Sleep(10); //工場が落ち着くまで待つ
                if (i > 10*60*100) {
                    _TRACE_("【デバイスロスト処理/工場停止】 10分待機しましたが、工場から反応がありません。強制breakします。要調査");
                    break;
                }
            }
         ___BeginSynchronized1; // ----->排他開始
            _TRACE_("【デバイスロスト処理】工場停止 <-------- END");

            _TRACE_("【デバイスロスト処理】リソース解放 BEGIN ------>");

            //レンダリングターゲット、デバイスロスト処理
            if (GGAF_PROPERTY(FULL_SCREEN)) {
                releaseFullScreenRenderTarget();
            }
            //環境マップテクスチャ、デバイスロスト処理
            GgafDxGod::_pCubeMapTextureManager->releaseAll();
            GgafDxGod::_pBumpMapTextureManager->releaseAll();
            //エフェクト、デバイスロスト処理
            GgafDxGod::_pEffectManager->onDeviceLostAll();
            //モデル解放
            GgafDxGod::_pModelManager->onDeviceLostAll();
            //全ノードに解放しなさいイベント発令
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_ON_DEVICE_LOST, this);
            _TRACE_("【デバイスロスト処理】リソース解放 <-------- END");
            _is_device_lost_flg = true;
        }
    }

    if (_is_device_lost_flg) {
        _TRACE_("【デバイスロスト処理/リソース解放】協調性レベルチェック BEGIN ------>");
        //for(int i = 0; i < 300; i++) {
        while(true) {
            if (_can_wddm) {
                hr = ((IDirect3DDevice9Ex*)GgafDxGod::_pID3DDevice9)->CheckDeviceState(_pHWndPrimary);
                if (hr == D3DERR_DEVICELOST || hr == S_PRESENT_OCCLUDED) {
                    return;
                } else {
                    break;
                }
            } else {
                hr = GgafDxGod::_pID3DDevice9->TestCooperativeLevel();
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
        for(int i = 0; i < 100*60*10; i++) {
            if (GGAF_PROPERTY(FULL_SCREEN) && GGAF_PROPERTY(DUAL_VIEW)) {
                hr = GgafDxGod::_pID3DDevice9->Reset(_paPresetPrm);
            } else {
                hr = GgafDxGod::_pID3DDevice9->Reset(&(_paPresetPrm[0]));
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

        if (GGAF_PROPERTY(FULL_SCREEN)) {
            _TRACE_("【デバイスロスト処理】フルスクリーン時レンダリングターゲットテクスチャ再構築 BEGIN ------>");
            restoreFullScreenRenderTarget();
            _TRACE_("【デバイスロスト処理】フルスクリーン時レンダリングターゲットテクスチャ再構築 <-------- END");
        }

        //リソース再構築
        _TRACE_("【デバイスロスト処理】リソース再構築 BEGIN ------>");
        //環境マップテクスチャ、復帰処理
        GgafDxGod::_pCubeMapTextureManager->restoreAll();
        GgafDxGod::_pBumpMapTextureManager->restoreAll();
        //エフェクトリセット
        GgafDxGod::_pEffectManager->restoreAll();
        //モデル再設定
        GgafDxGod::_pModelManager->restoreAll();
        //全ノードに再設定しなさいイベント発令
        getUniverse()->throwEventToLowerTree(GGAF_EVENT_DEVICE_LOST_REDEPOSITORY, this);
        //前回描画モデル情報を無効にする
        GgafDxModelManager::_pModelLastDraw = NULL;
        _is_device_lost_flg = false;
        _TRACE_("【デバイスロスト処理】リソース再構築 <-------- END");

        //工場再開
        _TRACE_("【デバイスロスト処理】工場再起動 BEGIN ------>");
        GgafFactory::finishRest();
        _TRACE_("【デバイスロスト処理】工場再起動 <-------- END");

        _TRACE_("【デバイスロスト処理】<-------- END");

        Sleep(500);
        hr = GgafDxGod::_pID3DDevice9->Clear(0,    // クリアする矩形領域の数
                                             NULL, // 矩形領域
                                             D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                             _color_border, //背景色      //D3DCOLOR_XRGB( 0, 0, 0 )
                                             1.0f, // Zバッファのクリア値
                                             0     // ステンシルバッファのクリア値
                                            );
    }
}

void GgafDxGod::finalizeUniversal() {
    if (_is_device_lost_flg) {
        return;
    } else {
        GgafGod::finalizeUniversal();
    }
}

void GgafDxGod::clean() {
    if (!_was_cleaned) {
        _TRACE_("GgafDxGod::clean() begin");
        for(int i = 0; i < 8; ++i) { GgafDxGod::_pID3DDevice9->SetTexture( i, NULL ); }
        for(int i = 0; i < 8; ++i) { GgafDxGod::_pID3DDevice9->SetStreamSource( i, NULL, 0, 0 ); }
        GgafDxGod::_pID3DDevice9->SetIndices( NULL );
        GgafDxGod::_pID3DDevice9->SetPixelShader( NULL );
        GgafDxGod::_pID3DDevice9->SetVertexShader( NULL );
        GgafDxGod::_pID3DDevice9->SetVertexDeclaration( NULL );

        GgafGod::clean();

        CmRandomNumberGenerator::getInstance()->release();
        //保持モデル解放
        DELETE_IMPOSSIBLE_NULL(_pCubeMapTextureManager);
        DELETE_IMPOSSIBLE_NULL(_pBumpMapTextureManager);
        DELETE_IMPOSSIBLE_NULL(_pModelManager);
        DELETE_IMPOSSIBLE_NULL(_pEffectManager);
        _TRACE_("GgafDxGod::clean() end");
    }
}

void GgafDxGod::adjustGameScreen(HWND prm_pHWnd) {
    RECT rect;
    if (prm_pHWnd && !GGAF_PROPERTY(FULL_SCREEN) && GGAF_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
        HRESULT hr;
        hr = GgafDxGod::_pID3DDevice9->Clear(0, NULL, D3DCLEAR_TARGET, _color_border, 1.0f, 0);
        hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
        if (GGAF_PROPERTY(DUAL_VIEW)) {
            hr = GgafDxGod::_pID3DDevice9->Present(NULL, NULL, _pHWndSecondary, NULL);
        }
        if (::GetClientRect(prm_pHWnd, &rect)) {
            LONG width = rect.right;
            LONG height = rect.bottom;
            LONG fix_width, fix_height;
            int pos1, pos2;
            if (GGAF_PROPERTY(DUAL_VIEW)) {
                fix_width  = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
                fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                pos1 = GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION1);
                pos2 = GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2);
            } else {
                fix_width  = GGAF_PROPERTY(GAME_BUFFER_WIDTH);
                fix_height = GGAF_PROPERTY(GAME_BUFFER_HEIGHT);
                pos1 = GGAF_PROPERTY(SINGLE_VIEW_DRAW_POSITION);
                pos2 = GGAF_PROPERTY(DUAL_VIEW_DRAW_POSITION2); //とりあえず
            }

            if (1.0f * width / height > 1.0f * fix_width / fix_height) {
                //より横長になってしまっている
                double rate = 1.0 * height / fix_height; //縮小率=縦幅の比率
                if (prm_pHWnd == _pHWndPrimary) {
                    _aRect_Present[0].left   = (width / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                    positionPresentRect(pos1, _aRect_Present[0], width, height);
                } else {
                    _aRect_Present[1].left   = (width / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                    positionPresentRect(pos2, _aRect_Present[1], width, height);
                }

            } else {
                //より縦長になってしまっている
                double rate = 1.0 * width / fix_width; //縮小率=横幅の比率
                if (prm_pHWnd == _pHWndPrimary) {
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (height / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                    positionPresentRect(pos1, _aRect_Present[0], width, height);
                } else {
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (height / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                    positionPresentRect(pos2, _aRect_Present[1], width, height);
                }
            }
        }
    } else {
        if (::GetClientRect(prm_pHWnd, &rect)) {
            if (prm_pHWnd == _pHWndPrimary) {
                _aRect_Present[0] = rect;
            } else {
                _aRect_Present[1] = rect;
            }

        }
    }
    GgafDxGod::_pID3DDevice9->GetViewport(&(P_CAM->_viewport));
    _adjustGameScreen = false;
    _pHWnd_adjustScreen = NULL;
}

void GgafDxGod::positionPresentRect(int prm_pos, RECT& out_rectPresent, pixcoord prm_screen_width, pixcoord prm_screen_height) {
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
        out_rectPresent.bottom = out_rectPresent.bottom - out_rectPresent.top;
        out_rectPresent.top = 0;
    } else if (prm_pos == 1 || prm_pos == 2 || prm_pos == 3) {
        out_rectPresent.top = prm_screen_height - (out_rectPresent.bottom - out_rectPresent.top);
        out_rectPresent.bottom = prm_screen_height;
    }

    if (prm_pos == 7 || prm_pos == 4 || prm_pos == 1) {
        out_rectPresent.right = out_rectPresent.right - out_rectPresent.left;
        out_rectPresent.left = 0;
    } else if (prm_pos == 9 || prm_pos == 6 || prm_pos == 3) {
        out_rectPresent.left = prm_screen_width - (out_rectPresent.right - out_rectPresent.left);
        out_rectPresent.right = prm_screen_width;
    }
}

GgafDxGod::~GgafDxGod() {

    clean();
    _was_cleaned = true;
    //DirectSound解放
    GgafDxSound::release();
    //DirectInput解放
    GgafDxInput::release();

    if(GGAF_PROPERTY(FULL_SCREEN)) {
        releaseFullScreenRenderTarget();
    }

    _TRACE_("_pID3DDevice9 解放きたー");
    Sleep(60);
    DELETEARR_IMPOSSIBLE_NULL(_paPresetPrm);
    DELETEARR_IMPOSSIBLE_NULL(_paDisplayMode);
    RELEASE_IMPOSSIBLE_NULL(_pID3DDevice9);
    RELEASE_IMPOSSIBLE_NULL(_pID3D9);

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
//                                                 ｜ Present
//                                                 ｜(D3DSWAPEFFECT_DISCARD)
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
//                               ｜ Present                         ｜ Present
//                               ｜(D3DSWAPEFFECT_DISCARD)          ｜ (D3DSWAPEFFECT_DISCARD)
//
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


