#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

#define returnWhenFailed(HR, OKVAL, X) { \
    if (HR != OKVAL) { \
        std::stringstream ss; \
        ss << X; \
        MessageBox(GgafDx9God::_pHWndPrimary, TEXT(ss.str().c_str()), TEXT("ERROR"), MB_OK | MB_ICONSTOP); \
        return E_FAIL; \
    } \
}

//TODO:コメントとか多すぎる。整理する。


HWND GgafDx9God::_pHWndPrimary = NULL;
HWND GgafDx9God::_pHWndSecondary = NULL;
HINSTANCE GgafDx9God::_hInstance = NULL;

IDirect3D9* GgafDx9God::_pID3D9 = NULL;
IDirect3DDevice9* GgafDx9God::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDx9God::_d3dlight9_default;
D3DLIGHT9 GgafDx9God::_d3dlight9_temp;
DWORD GgafDx9God::_dwAmbientBrightness_default = 0xff404040;


D3DFILLMODE GgafDx9God::_d3dfillmode = D3DFILL_SOLID;//D3DFILL_WIREFRAME;//D3DFILL_SOLID;

GgafDx9ModelManager* GgafDx9God::_pModelManager = NULL;
GgafDx9EffectManager* GgafDx9God::_pEffectManager = NULL;
GgafDx9TextureManager* GgafDx9God::_pCubeMapTextureManager = NULL;

bool GgafDx9God::_is_device_lost_flg = false;
bool GgafDx9God::_adjustGameScreen = false;
HWND GgafDx9God::_pHWnd_adjustScreen = NULL;

int GgafDx9God::_iNumAdapter = 1;

UINT32 GgafDx9God::_vs_v = 0;
UINT32 GgafDx9God::_ps_v = 0;

D3DXMACRO GgafDx9God::_aD3DXMacro_Defines[3] =
{
    { "VS_VERSION", "vs_3_0" },
    { "PS_VERSION", "ps_3_0" },
    { NULL, NULL }
};



#define IFC(x) { hr = (x); if (FAILED(hr)) goto Cleanup; }
#define IFCOOM(x) { if ((x) == NULL) { hr = E_OUTOFMEMORY; IFC(hr); } }
#define SAFE_RELEASE(x) { if (x) { x->Release(); x = NULL; } }


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
    GgafRgb rgb = GgafRgb(CFG_PROPERTY(BG_COLOR));
    _color_background = D3DCOLOR_RGBA(rgb._R, rgb._G, rgb._B, 0);
    _color_clear = D3DCOLOR_RGBA(0, 0, 0, 0);

    _pRenderTexture = NULL;   //テクスチャ
    //_pBackBuffer = NULL;      //バックバッファ
    _pRenderTextureSurface = NULL;     //サーフェイス
    _pRenderTextureZ = NULL;

    _pSwapChain00 = NULL;//アダプタに関連付けれられたスワップチェーン
    _pBackBuffer00 = NULL;//バックバッファ1画面分
    _pSwapChain01 = NULL;//アダプタに関連付けれられたスワップチェーン
    _pBackBuffer01 = NULL;//バックバッファ１画面分


    //[メモ：RECT構造体]
    //引数に使用するRECT構造体のメンバ right, bottom は「右下座標」となっているが、これは正確ではない。
    //実際の定義は
    //rect.right = rect.left + 矩形幅;
    //rect.bottom = rect.top + 矩形高さ;
    //らしい。
    //よって、例えば (10,10)-(17,17)領域は、RECT(10,10,18,18) と指定しなければいけないらしい。ややこしい。
    //ただ、辺の長さを求める場合は便利である。
    //（※本当の右下座標は、right, bottom の -1 の値になる）

    _rectGameBuffer.left   = 0;
    _rectGameBuffer.top    = 0;
    _rectGameBuffer.right  = _rectGameBuffer.left + CFG_PROPERTY(GAME_BUFFER_WIDTH);
    _rectGameBuffer.bottom = _rectGameBuffer.top  + CFG_PROPERTY(GAME_BUFFER_HEIGHT);

    _rectRenderTargetBuffer.left   = 0;
    _rectRenderTargetBuffer.top    = 0;
    _rectRenderTargetBuffer.right  = _rectRenderTargetBuffer.left + CFG_PROPERTY(RENDER_TARGET_BUFFER_WIDTH);
    _rectRenderTargetBuffer.bottom = _rectRenderTargetBuffer.top  + CFG_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);

    if (CFG_PROPERTY(SWAP_GAME_VIEW)) {
        _primary = 1;
        _secondary = 0;
    } else {
        _primary = 0;
        _secondary = 1;
    }
    _aRect_HarfGameBuffer[_primary].left   = 0;
    _aRect_HarfGameBuffer[_primary].top    = 0;
    _aRect_HarfGameBuffer[_primary].right  = _aRect_HarfGameBuffer[_primary].left  + CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_primary].bottom = _aRect_HarfGameBuffer[_primary].top + CFG_PROPERTY(GAME_BUFFER_HEIGHT);

    _aRect_HarfGameBuffer[_secondary].left   = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_secondary].top    = 0;
    _aRect_HarfGameBuffer[_secondary].right  = _aRect_HarfGameBuffer[_secondary].left + CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
    _aRect_HarfGameBuffer[_secondary].bottom = _aRect_HarfGameBuffer[_secondary].top  + CFG_PROPERTY(GAME_BUFFER_HEIGHT);

    _aRect_HarfRenderTargetBuffer[_primary].left   = 0;
    _aRect_HarfRenderTargetBuffer[_primary].top    = 0;
    _aRect_HarfRenderTargetBuffer[_primary].right  = _aRect_HarfRenderTargetBuffer[_primary].left  + CFG_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)/2;
    _aRect_HarfRenderTargetBuffer[_primary].bottom = _aRect_HarfRenderTargetBuffer[_primary].top + CFG_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);

    _aRect_HarfRenderTargetBuffer[_secondary].left   = CFG_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)/2;
    _aRect_HarfRenderTargetBuffer[_secondary].top    = 0;
    _aRect_HarfRenderTargetBuffer[_secondary].right  = _aRect_HarfRenderTargetBuffer[_secondary].left + CFG_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)/2;
    _aRect_HarfRenderTargetBuffer[_secondary].bottom = _aRect_HarfRenderTargetBuffer[_secondary].top  + CFG_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);

    //表示領域設定
    if (CFG_PROPERTY(FULL_SCREEN)) {
        //フルスクリーンモード
        if (CFG_PROPERTY(DUAL_VIEW)) {
            _aRect_ViewScreen[0].top    = 0;
            _aRect_ViewScreen[0].left   = 0;
            _aRect_ViewScreen[0].right  = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
            _aRect_ViewScreen[0].bottom = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
            _aRect_ViewScreen[1].top    = 0;
            _aRect_ViewScreen[1].left   = 0;
            _aRect_ViewScreen[1].right  = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
            _aRect_ViewScreen[1].bottom = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);

            //フルスクリーンモード・２画面使用
            if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
                //「フルスクリーンモード・２画面使用・縦横比FIX」の１画面目フロントバッファ描画領域
                if (1.0f * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[0].left   = (CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }

                //「フルスクリーンモード・２画面使用・縦横比FIX」の２画面目フロントバッファ描画領域
                if (1.0f * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[1].left   = (CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                }
                positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0],
                                    CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH), CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT));
                positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1],
                                    CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH), CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT));
            } else {
                //「フルスクリーンモード・２画面使用・縦横比ストレッチ」の１画面目フロントバッファ描画領域
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
                //「フルスクリーンモード・２画面使用・縦横比ストレッチ」の２画面目フロントバッファ描画領域
                _aRect_Present[1].left   = 0;
                _aRect_Present[1].top    = 0;
                _aRect_Present[1].right  = _aRect_Present[1].left + CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
                _aRect_Present[1].bottom = _aRect_Present[1].top  + CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);
            }
        } else {
            //フルスクリーンモード・１画面使用
            _aRect_ViewScreen[0].top    = 0;
            _aRect_ViewScreen[0].left   = 0;
            _aRect_ViewScreen[0].right  = CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
            _aRect_ViewScreen[0].bottom = CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
            _aRect_ViewScreen[1] = _aRect_ViewScreen[0];

            if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
                //「フルスクリーンモード・１画面使用・縦横比FIX」のフロントバッファ描画領域
                if (1.0f * CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[0].left   = (CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }
                _aRect_Present[1] = _aRect_Present[0];

                positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0],
                                    CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH), CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT));
                positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1],
                                    CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH), CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT));
            } else {
                //「フルスクリーンモード・１画面使用・縦横比ストレッチ」のフロントバッファ描画領域
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
                _aRect_Present[1] = _aRect_Present[0];
            }
        }
    } else {
        //ウィンドウモード
        if (CFG_PROPERTY(DUAL_VIEW)) {
            //ウィンドウモード・２窓使用
            if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
                LONG fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
                //「ウィンドウモード・２窓使用・縦横比FIX」の１窓目フロントバッファ描画領域
                if (1.0f * CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[0].left   = (CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }

                //「ウィンドウモード・２窓使用・縦横比FIX」の２窓目フロントバッファ描画領域
                if (1.0f * CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[1].left   = (CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top    = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[1].left   = 0;
                    _aRect_Present[1].top    = (CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                }

                positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0],
                                    CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH), CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT));
                positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1],
                                    CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH), CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT));
            } else {
                //「ウィンドウモード・２窓使用・縦横比ストレッチ」の１窓目フロントバッファ描画領域
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + CFG_PROPERTY(DUAL_VIEW_WINDOW1_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + CFG_PROPERTY(DUAL_VIEW_WINDOW1_HEIGHT);
                //「ウィンドウモード・２窓使用・縦横比ストレッチ」の２窓目フロントバッファ描画領域
                _aRect_Present[1].left   = 0;
                _aRect_Present[1].top    = 0;
                _aRect_Present[1].right  = _aRect_Present[1].left + CFG_PROPERTY(DUAL_VIEW_WINDOW2_WIDTH);
                _aRect_Present[1].bottom = _aRect_Present[1].top  + CFG_PROPERTY(DUAL_VIEW_WINDOW2_HEIGHT);
            }
        } else {
            //ウィンドウモード・１窓使用
            if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                LONG fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH);
                LONG fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
                //「ウィンドウモード・１窓使用・縦横比FIX」のフロントバッファ描画領域
                if (1.0f * CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) > 1.0f * fix_width / fix_height) {
                    //より横長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) / fix_height; //縮小率=縦幅の比率
                    _aRect_Present[0].left   = (CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top    = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                } else {
                    //より縦長になってしまっている
                    double rate = 1.0 * CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH) / fix_width; //縮小率=横幅の比率
                    _aRect_Present[0].left   = 0;
                    _aRect_Present[0].top    = (CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT) / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                }
                _aRect_Present[1] = _aRect_Present[0];

                positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0],
                                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
                positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1],
                                    CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH), CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT));
            } else {
                //「ウィンドウモード・１窓使用・縦横比ストレッチ」のフロントバッファ描画領域
                _aRect_Present[0].left   = 0;
                _aRect_Present[0].top    = 0;
                _aRect_Present[0].right  = _aRect_Present[0].left + CFG_PROPERTY(SINGLE_VIEW_WINDOW_WIDTH);
                _aRect_Present[0].bottom = _aRect_Present[0].top  + CFG_PROPERTY(SINGLE_VIEW_WINDOW_HEIGHT);
                _aRect_Present[1] = _aRect_Present[0];
            }
        }
    }
    _TRACE_(" _aRect_Present[0].left     = "<<_aRect_Present[0].left    );
    _TRACE_(" _aRect_Present[0].top      = "<<_aRect_Present[0].top     );
    _TRACE_(" _aRect_Present[0].right    = "<<_aRect_Present[0].right   );
    _TRACE_(" _aRect_Present[0].bottom   = "<<_aRect_Present[0].bottom  );
    _TRACE_(" _aRect_Present[1].left   = "<<_aRect_Present[1].left  );
    _TRACE_(" _aRect_Present[1].top    = "<<_aRect_Present[1].top   );
    _TRACE_(" _aRect_Present[1].right  = "<<_aRect_Present[1].right );
    _TRACE_(" _aRect_Present[1].bottom = "<<_aRect_Present[1].bottom);


}

HRESULT GgafDx9God::init() {


    //2011/09/18 WDDM が使用できるなら使用するように変更。
	// マルチモニタフルスクリーン時のデバイスロスト時の復旧が、
    // XPではうまくいくのにVistaではうまくいかない時があるため、
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
            MessageBox(GgafDx9God::_pHWndPrimary, TEXT("IDirect3D9Ex コンポーネント取得に失敗しました。(1)"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
            FreeLibrary(hD3D);
            return E_FAIL; //失敗
        }
		/*
        hr = pID3D9Ex->QueryInterface(IID_IDirect3D9, reinterpret_cast<void **>(&pID3D9)); //COMとして使用
        if (FAILED(hr)) {
            MessageBox(GgafDx9God::_pHWndPrimary, TEXT("IDirect3D9Ex コンポーネント取得に失敗しました。(2)"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
            FreeLibrary(hD3D);
            return E_FAIL; //失敗
        }
		*/
        GgafDx9God::_pID3D9 = (IDirect3D9*)pID3D9Ex;
        _can_wddm = true;
    } else {
		//d3d9.dll に Direct3DCreate9Ex は存在しない。
        pID3D9 = Direct3DCreate9(D3D_SDK_VERSION);
        if (!pID3D9) {
            MessageBox(GgafDx9God::_pHWndPrimary, TEXT("IDirect3D9 コンポーネント取得に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
            FreeLibrary(hD3D);
            return E_FAIL; //失敗
        }
        GgafDx9God::_pID3D9 = pID3D9;
        _can_wddm = false;
    }
	FreeLibrary(hD3D);



//    if (!(GgafDx9God::_pID3D9 = Direct3DCreate9(D3D_SDK_VERSION))) {
//        MessageBox(GgafDx9God::_pHWndPrimary, TEXT("DirectX コンポーネント取得に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
//        return E_FAIL; //失敗
//    }



    //デバイスパラメータ作成
    _paPresetParam = NEW D3DPRESENT_PARAMETERS[2];
    ZeroMemory(&_paPresetParam[0], sizeof(D3DPRESENT_PARAMETERS));
    //バックバッファの数
    _paPresetParam[0].BackBufferCount = 1;
    //深度ステンシルバッファ
    //_paPresetParam[0].EnableAutoDepthStencil = FALSE;
    //_paPresetParam[0].AutoDepthStencilFormat = 0;
    _paPresetParam[0].EnableAutoDepthStencil = TRUE; //Z バッファの自動作成
    _paPresetParam[0].AutoDepthStencilFormat = D3DFMT_D24S8;//D3DFMT_D16;
    //0にしておく
    _paPresetParam[0].Flags = 0;

    if (CFG_PROPERTY(FULL_SCREEN)) {
        //フルスクリーン時
        _paPresetParam[0].BackBufferFormat = D3DFMT_X8R8G8B8;
                                        //D3DFMT_A8R8G8B8; //D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;
        _paPresetParam[0].Windowed = false; //フルスクリーンモード時
        _paPresetParam[0].FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //リフレッシュレート
        _paPresetParam[0].PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT; //スワップのタイミング
        _paPresetParam[0].SwapEffect = D3DSWAPEFFECT_DISCARD;
//        if (CFG_PROPERTY(DUAL_VIEW)) {
//            _paPresetParam[0].SwapEffect = D3DSWAPEFFECT_COPY;
//        } else {
//            _paPresetParam[0].SwapEffect = D3DSWAPEFFECT_DISCARD; //1画面フルスクリーン時のみ
//        }


//        if (_can_wddm) {
//            D3DDISPLAYMODEEX DisplayMode;
//            ZeroMemory(&DisplayMode, sizeof(DisplayMode));
//            DisplayMode.Size = sizeof(DisplayMode);
//            ((IDirect3D9Ex*)GgafDx9God::_pID3D9)->GetAdapterDisplayModeEx(0, &DisplayMode, NULL);
//            DisplayMode.Format = _paPresetParam[0].BackBufferFormat;
//            _paPresetParam[0].FullScreen_RefreshRateInHz = DisplayMode.RefreshRate;
//        }
    } else {
        //ウィンドウ時
        _paPresetParam[0].Windowed = true; //ウィンドウモード時
        _paPresetParam[0].FullScreen_RefreshRateInHz = 0; //リフレッシュレート
        _paPresetParam[0].PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //即座
        _paPresetParam[0].SwapEffect = D3DSWAPEFFECT_COPY; //TODO:Windowモードはこれ一択なのか？、D3DPRESENT_INTERVAL_ONE とかためす？
    }




    //アンチアイリアスにできるかチェック
    UINT32 qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;

    //	if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //		D3DADAPTER_DEFAULT,
    //		D3DDEVTYPE_HAL,
    //		D3DFMT_A8R8G8B8,
    //		CFG_PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
    //		D3DMULTISAMPLE_2_SAMPLES,
    //		&qualityLevels) ) )
    //	{
    //		if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //			D3DADAPTER_DEFAULT,
    //			D3DDEVTYPE_HAL,
    //			D3DFMT_D24S8,
    //			CFG_PROPERTY(FULL_SCREEN) ? FALSE : TRUE,
    //			D3DMULTISAMPLE_2_SAMPLES,
    //			NULL) ) )
    //		{
    //			multiSampleType = D3DMULTISAMPLE_2_SAMPLES;
    //			_TRACE_("MultiSampleType = D3DMULTISAMPLE_2_SAMPLES");
    //		}
    //	}
    //マルチサンプルの数
    _paPresetParam[0].MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
    //マルチサンプルの品質レベル
    _paPresetParam[0].MultiSampleQuality = 0;//qualityLevels - (qualityLevels > 0 ? 1 : 0);

    //２画面使用時の D3DPRESENT_PARAMETERS 差分上書き
    _paPresetParam[1] = _paPresetParam[0]; //共通が多いためコピー

    if (CFG_PROPERTY(FULL_SCREEN)) {
        if(CFG_PROPERTY(DUAL_VIEW)) {
            _paPresetParam[0].BackBufferFormat = D3DFMT_X8R8G8B8; //D3DFMT_A8R8G8B8; //D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;
            _paPresetParam[1].BackBufferFormat = _paPresetParam[0].BackBufferFormat;
        } else {
            _paPresetParam[0].BackBufferFormat = D3DFMT_X8R8G8B8;
            _paPresetParam[1].BackBufferFormat = D3DFMT_UNKNOWN;
        }
    } else {
        //デスプレイモードの取得
        D3DDISPLAYMODE structD3DDisplayMode0; //結果が格納される構造体
        hr = GgafDx9God::_pID3D9->GetAdapterDisplayMode(0, &structD3DDisplayMode0);
        returnWhenFailed(hr, D3D_OK, "GetAdapterDisplayMode に失敗しました。");
        if(CFG_PROPERTY(DUAL_VIEW)) {
            D3DDISPLAYMODE structD3DDisplayMode1;
            hr = GgafDx9God::_pID3D9->GetAdapterDisplayMode(1, &structD3DDisplayMode1);
            returnWhenFailed(hr, D3D_OK, "2画面目 GetAdapterDisplayMode に失敗しました");
            _paPresetParam[0].BackBufferFormat = structD3DDisplayMode0.Format; //現在の画面モードを利用
            _paPresetParam[1].BackBufferFormat = structD3DDisplayMode1.Format; //現在の画面モードを利用
        } else {
            _paPresetParam[0].BackBufferFormat = structD3DDisplayMode0.Format; //現在の画面モードを利用
            _paPresetParam[1].BackBufferFormat = D3DFMT_UNKNOWN; //現在の画面モードを利用
        }
    }

    //Windowハンドルを個別指定
    _paPresetParam[0].hDeviceWindow = _pHWndPrimary;
    _paPresetParam[1].hDeviceWindow = _pHWndSecondary;
    //バックバッファサイズ
    if (CFG_PROPERTY(FULL_SCREEN)) {
        if(CFG_PROPERTY(DUAL_VIEW)) {
            //フルスクリーンモード・２画面使用
            _paPresetParam[0].BackBufferWidth  = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_WIDTH);
            _paPresetParam[0].BackBufferHeight = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN1_HEIGHT);
            _paPresetParam[1].BackBufferWidth  = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_WIDTH);
            _paPresetParam[1].BackBufferHeight = CFG_PROPERTY(DUAL_VIEW_FULL_SCREEN2_HEIGHT);
        } else {
            //フルスクリーンモード・１画面使用
            _paPresetParam[0].BackBufferWidth  = CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_WIDTH);
            _paPresetParam[0].BackBufferHeight = CFG_PROPERTY(SINGLE_VIEW_FULL_SCREEN_HEIGHT);
            _paPresetParam[1].BackBufferWidth  = 0;
            _paPresetParam[1].BackBufferHeight = 0;
        }
    } else {
        if(CFG_PROPERTY(DUAL_VIEW)) {
            //ウィンドウモード・２画面使用
            _paPresetParam[0].BackBufferWidth  = CFG_PROPERTY(RENDER_TARGET_BUFFER_WIDTH);
            _paPresetParam[0].BackBufferHeight = CFG_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);
            _paPresetParam[1].BackBufferWidth  = 0;
            _paPresetParam[1].BackBufferHeight = 0;
        } else {
            //ウィンドウモード・１画面使用
            //テステス
            _paPresetParam[0].BackBufferWidth  = CFG_PROPERTY(RENDER_TARGET_BUFFER_WIDTH);
            _paPresetParam[0].BackBufferHeight = CFG_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT);
            _paPresetParam[1].BackBufferWidth  = 0;
            _paPresetParam[1].BackBufferHeight = 0;
        }
    }

    _paDisplayMode = NEW D3DDISPLAYMODEEX[2];
    _paDisplayMode[0].Size = sizeof(_paDisplayMode[0]);
    _paDisplayMode[0].Width = _paPresetParam[0].BackBufferWidth;
    _paDisplayMode[0].Height = _paPresetParam[0].BackBufferHeight;
    _paDisplayMode[0].Format = _paPresetParam[0].BackBufferFormat;
    _paDisplayMode[0].RefreshRate = _paPresetParam[0].FullScreen_RefreshRateInHz;
    _paDisplayMode[0].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

    _paDisplayMode[1].Size = sizeof(_paDisplayMode[1]);
    _paDisplayMode[1].Width = _paPresetParam[1].BackBufferWidth;
    _paDisplayMode[1].Height = _paPresetParam[1].BackBufferHeight;
    _paDisplayMode[1].Format = _paPresetParam[1].BackBufferFormat;
    _paDisplayMode[1].RefreshRate = _paPresetParam[1].FullScreen_RefreshRateInHz;
    _paDisplayMode[1].ScanLineOrdering = D3DSCANLINEORDERING_PROGRESSIVE;

    //フルスクリーンに出来るか調べる
    D3DCAPS9 caps;
    GgafDx9God::_pID3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, // [in] ディスプレイ アダプタを示す序数。
                                       D3DDEVTYPE_HAL, // [in] デバイスの種類。 D3DDEVTYPE列挙型のメンバ
                                       &caps); // [out] デバイスの能力が格納される

    _iNumAdapter = caps.NumberOfAdaptersInGroup;   //使えるアダプタの数取得
    _TRACE_("_iNumAdapter = "<< _iNumAdapter);
    if (CFG_PROPERTY(FULL_SCREEN)) {
        for (int disp_no = 0; disp_no <= (CFG_PROPERTY(DUAL_VIEW) ? 1 : 0); disp_no++) {
            int mode_num = GgafDx9God::_pID3D9->GetAdapterModeCount(disp_no,
                                                                    _paPresetParam[0].BackBufferFormat);
            if (mode_num) {
                D3DDISPLAYMODE adp;
                for (int i = 0; i < mode_num; i++) {
                    GgafDx9God::_pID3D9->EnumAdapterModes(disp_no,
                                                          _paPresetParam[0].BackBufferFormat, i, &adp);
                    _TRACE_("["<<disp_no<<"]"<<adp.Width<<"x"<<adp.Height);
                    if (adp.Format == _paPresetParam[disp_no].BackBufferFormat &&
                        adp.Width  == _paPresetParam[disp_no].BackBufferWidth  &&
                        adp.Height == _paPresetParam[disp_no].BackBufferHeight ) {
                        //OK
                        _TRACE_("BINGO!");
                        break;
                    }
                    if (mode_num-1 == i) {
                        //要求した使える解像度が見つからない
                        stringstream ss;
                        if (CFG_PROPERTY(DUAL_VIEW)) {
                            ss << _paPresetParam[disp_no].BackBufferWidth<<"x"<<_paPresetParam[disp_no].BackBufferHeight<<" フルスクリーンモードにする事ができません。\n"<<
                                   (disp_no+1)<<"画面目の解像度の設定を確認してください。";
                        } else {
                            ss << _paPresetParam[disp_no].BackBufferWidth<<"x"<<_paPresetParam[disp_no].BackBufferHeight<<" フルスクリーンモードにする事ができません。\n"<<
                                    "解像度の設定を確認してください。";
                        }
                        MessageBox(GgafDx9God::_pHWndPrimary, TEXT(ss.str().c_str()), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
                        return E_FAIL;
                    }
                }
            } else {
                MessageBox(GgafDx9God::_pHWndPrimary, TEXT("フルスクリーンモード可能な解像度情報が取得できませんでした。\nご使用のビデオカードではプログラムを実行できません。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
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


    if (CFG_PROPERTY(FULL_SCREEN) && CFG_PROPERTY(DUAL_VIEW)) {
        //＜フルスクリーン かつ マルチビュー＞

        //デバイス作成を試み GgafDx9God::_pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                             D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                             _paPresetParam, _paDisplayMode);
        //checkDxException(hr, D3D_OK, "CreateDevice() に失敗しました。");
        if (hr != D3D_OK) {
            _TRACE_("D3DCREATE_PUREDEVICE: "<<GgafDx9CriticalException::getHresultMsg(hr));

            //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
            hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                                 D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                 _paPresetParam, _paDisplayMode);
            if (hr != D3D_OK) {
                _TRACE_("D3DCREATE_SOFTWARE_VERTEXPROCESSING: "<<GgafDx9CriticalException::getHresultMsg(hr));

                //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_pHWndPrimary,
                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE | D3DCREATE_ADAPTERGROUP_DEVICE,
                                     _paPresetParam, _paDisplayMode);
                if (hr != D3D_OK) {
                    _TRACE_("D3DCREATE_SOFTWARE_VERTEXPROCESSING: "<<GgafDx9CriticalException::getHresultMsg(hr));

                    //どのデバイスの作成も失敗した場合
                    MessageBox(GgafDx9God::_pHWndPrimary, TEXT("DirectXの初期化に失敗しました。\nマルチヘッドディスプレイ環境が存在していません。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
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
        //＜(フルスクリーン かつ マルチビュー) 以外の場合＞

        //デバイス作成を試み GgafDx9God::_pID3DDevice9 へ設定する。
        //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
        hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                             D3DCREATE_PUREDEVICE | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                             &_paPresetParam[0], &_paDisplayMode[0]);
//                                           D3DCREATE_MIXED_VERTEXPROCESSING|D3DCREATE_MULTITHREADED,
//                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,


        if (hr != D3D_OK) {
            //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
            hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_pHWndPrimary,
                                 D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                 &_paPresetParam[0], &_paDisplayMode[0]);
            if (hr != D3D_OK) {
                //ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
                hr = createDx9Device(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_pHWndPrimary,
                                     D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED | D3DCREATE_FPU_PRESERVE,
                                     &_paPresetParam[0], &_paDisplayMode[0]);
                if (hr != D3D_OK) {
                    //どのデバイスの作成も失敗した場合
                    MessageBox(GgafDx9God::_pHWndPrimary, TEXT("DirectXの初期化に失敗しました。"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
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


    //その他必要な初期化
    _pCubeMapTextureManager = NEW GgafDx9TextureManager("CMTexManager");
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
    hr = initDx9Device();
    if (hr == E_FAIL) {
        return E_FAIL;
    }
    if (CFG_PROPERTY(FULL_SCREEN)) {
        hr = restoreFullScreenRenderTarget();
        if (hr == E_FAIL) {
            return E_FAIL;
        }
    }
    return D3D_OK;

}
HRESULT GgafDx9God::createDx9Device(UINT Adapter,
                                    D3DDEVTYPE DeviceType,
                                    HWND hFocusWindow,
                                    DWORD BehaviorFlags,
                                    D3DPRESENT_PARAMETERS* pPresentationParameters,
                                    D3DDISPLAYMODEEX *pFullscreenDisplayMode
                                  ) {




    HRESULT hr;
    if (_can_wddm) {
        if (!CFG_PROPERTY(FULL_SCREEN)) {
            pFullscreenDisplayMode = NULL;
        }
        IDirect3D9Ex* pID3D9Ex = (IDirect3D9Ex*)GgafDx9God::_pID3D9;
        IDirect3DDevice9Ex* pID3DDevice9Ex;
        hr = pID3D9Ex->CreateDeviceEx(Adapter,
                                       DeviceType,
									   hFocusWindow,
                                       BehaviorFlags,
                                       pPresentationParameters,
                                       pFullscreenDisplayMode,
                                       &pID3DDevice9Ex
                                       );
        GgafDx9God::_pID3DDevice9 = (IDirect3DDevice9Ex*)pID3DDevice9Ex;

    } else {
        hr = GgafDx9God::_pID3D9->CreateDevice(Adapter,
                                               DeviceType,
											   hFocusWindow,
                                               BehaviorFlags,
                                               pPresentationParameters,
                                               &GgafDx9God::_pID3DDevice9
                                               );
    }
    return hr;
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
     //GgafDx9God::_d3dlight9_default.Position = D3DXVECTOR3(-1*CFG_PROPERTY(GAME_BUFFER_WIDTH)/2, -1*CFG_PROPERTY(GAME_BUFFER_HEIGHT)/2, -1*CFG_PROPERTY(GAME_BUFFER_HEIGHT)/2);
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
    HRESULT hr;
    //バックバッファをウィンドウBG色でクリア
    //ここではRenderTargetはまだ、通常のバックバッファである
    hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                          NULL, // 矩形領域
                                          D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                          //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
                                          _color_background, //ウィンドウ背景色とそろえる
                                          1.0f, // Zバッファのクリア値
                                          0 // ステンシルバッファのクリア値
            );
    returnWhenFailed(hr, D3D_OK, "背景色(_color_background)の塗りつぶしよる、画面クリアに失敗しました。");
    return D3D_OK;
}


HRESULT GgafDx9God::restoreFullScreenRenderTarget() {
    if (!CFG_PROPERTY(FULL_SCREEN)) {
        _TRACE_("GgafDx9God::restoreFullScreenRenderTarget() ＜警告＞フルスクリーン時意外、呼び出し不要です。");
        return D3D_OK;
    }

    HRESULT hr;
    //描画先となるテクスチャを別途作成（バックバッファ的な使用を行う）
    hr = GgafDx9God::_pID3DDevice9->CreateTexture(
                                            CFG_PROPERTY(RENDER_TARGET_BUFFER_WIDTH),
                                            CFG_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT),
                                             1, //MipLevel Mip無し
                                             D3DUSAGE_RENDERTARGET,
                                             _paPresetParam[0].BackBufferFormat,
                                             D3DPOOL_DEFAULT,
                                             &_pRenderTexture,
                                             NULL);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャ("<<CFG_PROPERTY(RENDER_TARGET_BUFFER_WIDTH)<<"x"<<CFG_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT)<<")の作成に失敗。\nサイズを確認して下さい。");
    //RenderTarget(描画先)をテクスチャへ切り替え
    hr = _pRenderTexture->GetSurfaceLevel(0, &_pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャのサーフェイス取得に失敗しました。");
    hr = GgafDx9God::_pID3DDevice9->SetRenderTarget(0, _pRenderTextureSurface);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャへ SetRenderTarget 出来ませんでした。");


    //テクスチャに描画する際の深度バッファ用サーフェイスを別途作成
    hr = GgafDx9God::_pID3DDevice9->CreateDepthStencilSurface(
            CFG_PROPERTY(RENDER_TARGET_BUFFER_WIDTH),
            CFG_PROPERTY(RENDER_TARGET_BUFFER_HEIGHT),
            _paPresetParam[0].AutoDepthStencilFormat,   //D3DFORMAT   Format,
            _paPresetParam[0].MultiSampleType,          //D3DMULTISAMPLE_TYPE     MultiSample,
            _paPresetParam[0].MultiSampleQuality,       //DWORD   MultisampleQuality,
            TRUE,                                  //BOOL    Discard, SetDepthStencileSurface関数で深度バッファを変更した時にバッファを破棄するかどうか
            &_pRenderTextureZ,                     //IDirect3DSurface9**     ppSurface,
            NULL                                   //HANDLE*     pHandle 現在未使用
    );
    //深度バッファ作成自動生成の、深度バッファ用サーフェイスを上記に変更
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャのZバッファ作成に失敗しました。");
    hr =  GgafDx9God::_pID3DDevice9->SetDepthStencilSurface(_pRenderTextureZ);
    returnWhenFailed(hr, D3D_OK, "レンダリングターゲットテクスチャへ SetDepthStencilSurface 出来ませんでした。");
    //背景色でクリア
    hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                          NULL, // 矩形領域
                                          D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                          _color_background, //背景黒にクリア
                                          1.0f, // Zバッファのクリア値
                                          0 // ステンシルバッファのクリア値
                                          );
    returnWhenFailed(hr, D3D_OK,  "クリア色(_color_background)の塗りつぶしよる、画面クリアに失敗しました。");

    //アダプタに関連付けられたスワップチェーンを取得してバックバッファ取得
    hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 0, &_pSwapChain00 );
    returnWhenFailed(hr, D3D_OK, "スワップチェイン取得に失敗しました。");
    hr = _pSwapChain00->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_pBackBuffer00 );
    returnWhenFailed(hr, D3D_OK, "スワップチェインから、ターゲットのバックバッファ取得に失敗しました。");
    if (CFG_PROPERTY(DUAL_VIEW)) {
        hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 1, &_pSwapChain01 );
        returnWhenFailed(hr, D3D_OK, "２画面目のスワップチェイン取得に失敗しました。\nマルチディスプレイ環境に問題発生しました。");
        hr = _pSwapChain01->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_pBackBuffer01 );
        returnWhenFailed(hr, D3D_OK, "２画面目のスワップチェインから、ターゲットのバックバッファ取得に失敗しました。");
    }

    //フルスクリーン時、バックバッファとフロントバッファを背景色で塗る
    if (CFG_PROPERTY(DUAL_VIEW)) {
        hr = GgafDx9God::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[0],
                _pBackBuffer00,         &_aRect_ViewScreen[0],
                D3DTEXF_NONE); //TODO:D3DTEXF_LINEARをオプション指定にするか？
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1画面目、背景色塗に失敗しました。(1)\n"<<
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_pBackBuffer00="<<_pBackBuffer00);

        hr = GgafDx9God::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[1],
                _pBackBuffer01,         &_aRect_ViewScreen[1],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 2画面目、背景色塗に失敗しました。(1)\n"<<
                                      "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_pBackBuffer00="<<_pBackBuffer00);
    } else {
        hr = GgafDx9God::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_rectRenderTargetBuffer,
                _pBackBuffer00, &_aRect_ViewScreen[0],
                D3DTEXF_NONE
                );
        checkDxException(hr, D3D_OK, "FULL_SCREEN 背景色塗に失敗しました。(1)");
    }

    hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
    returnWhenFailed(hr, D3D_OK, "Present(NULL, NULL, NULL, NULL)に失敗しました。");
    //フリップしてもう一度背景色で塗る
    if (CFG_PROPERTY(DUAL_VIEW)) {
        hr = GgafDx9God::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[0],
                _pBackBuffer00,         &_aRect_ViewScreen[0],
                D3DTEXF_NONE); //TODO:D3DTEXF_LINEARをオプション指定にするか？
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1画面目、背景色塗に失敗しました。(2)\n"<<
                                     "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_pBackBuffer00="<<_pBackBuffer00);

        hr = GgafDx9God::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[1],
                _pBackBuffer01,         &_aRect_ViewScreen[1],
                D3DTEXF_NONE);
        checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 2画面目、背景色塗に失敗しました。(2)\n"<<
                                      "_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_pBackBuffer00="<<_pBackBuffer00);
    } else {
        hr = GgafDx9God::_pID3DDevice9->StretchRect(
                _pRenderTextureSurface, &_rectRenderTargetBuffer,
                _pBackBuffer00, &_aRect_ViewScreen[0],
                D3DTEXF_NONE
                );
        checkDxException(hr, D3D_OK, "FULL_SCREEN 背景色塗に失敗しました。(2)");
    }

    return D3D_OK;
}

HRESULT GgafDx9God::releaseFullScreenRenderTarget() {
    RELEASE_SAFETY(_pRenderTextureSurface);
    RELEASE_SAFETY(_pRenderTexture);
    RELEASE_SAFETY(_pRenderTextureZ);
    RELEASE_SAFETY(_pBackBuffer00);
    RELEASE_SAFETY(_pSwapChain00);
    if (CFG_PROPERTY(DUAL_VIEW)) {
        RELEASE_SAFETY(_pBackBuffer01);
        RELEASE_SAFETY(_pSwapChain01);
    }
    return D3D_OK;
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
void GgafDx9God::presentUniversalMoment() {
    if (_is_device_lost_flg) {
        return;
    } else {
        GgafGod::presentUniversalMoment();
    }
}

void GgafDx9God::executeUniversalJudge() {
    if (_is_device_lost_flg) {
        return;
    } else {
        GgafGod::executeUniversalJudge();
    }
}
void GgafDx9God::makeUniversalMaterialize() {
    if (_is_device_lost_flg) {
        return;
    }
    TRACE("GgafDx9God::materialize() start");
    HRESULT hr;
        //通常時処理

    //バッファクリア
    hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                          NULL, // 矩形領域
                                          D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                          //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
                                          _color_clear, //背景黒にクリア //D3DCOLOR_XRGB( 0, 0, 0 ), //背景黒にクリア
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

    TRACE("GgafDx9God::makeUniversalMaterialize() end");
}

void GgafDx9God::presentUniversalVisualize() {
//    if (_is_device_lost_flg != true) {
    //バックバッファをプライマリバッファに転送
    //if (GgafDx9God::_pID3DDevice9->Present(NULL,&_aRect_Present[0],NULL,NULL) == D3DERR_DEVICELOST) {
    //        static D3DRASTER_STATUS rs;
    //        while (SUCCEEDED(GgafDx9God::_pID3DDevice9->GetRasterStatus(0, &rs)) ) {
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


    //        hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
        if (CFG_PROPERTY(FULL_SCREEN)) {
            if (CFG_PROPERTY(DUAL_VIEW)) {
                //２画面使用・フルスクリーン
                //画面０バックバッファを画面１バックバッファへコピーする
                hr = GgafDx9God::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[0],
                        _pBackBuffer00,         &_aRect_Present[0],
                        D3DTEXF_LINEAR); //TODO:D3DTEXF_LINEARをオプション指定にするか？
                checkDxException(hr, D3D_OK, "FULL_SCREEN DUAL_VIEW 1画面目 StretchRect() に失敗しました。\n_pRenderTextureSurface="<<_pRenderTextureSurface<<"/_pBackBuffer00="<<_pBackBuffer00);

                hr = GgafDx9God::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface, &_aRect_HarfRenderTargetBuffer[1],
                        _pBackBuffer01,         &_aRect_Present[1],
                        D3DTEXF_LINEAR);
                checkDxException(hr, D3D_OK, "StretchRect() に失敗しました。");

                hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);

    //            //プライマリバックバッファの右半分をセカンダリバックバッファへコピー
                //hr = GgafDx9God::_pID3DDevice9->UpdateSurface( _pBackBuffer00, &_aRect_HarfRenderTargetBuffer[1], _pBackBuffer01, _pPoint);
                //checkDxException(hr, D3D_OK, "UpdateSurface() に失敗しました。");
    //            //コピーフリップ
    //                hr = _pSwapChain00->Present(NULL, NULL, NULL, NULL,0);
    //    //            hr = _pSwapChain00->Present(&_aRect_HarfRenderTargetBuffer[0], NULL, NULL, NULL,0);
    //                checkDxException(hr, D3D_OK, "0Present() に失敗しました。");
    //                hr = _pSwapChain01->Present(NULL, NULL, NULL, NULL,0);
    //                checkDxException(hr, D3D_OK, "1Present() に失敗しました。");
    ////            //バックバッファとZバッファを取得する
    ////            if(FAILED(m_pd3dDevice->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO,&m_pBackBuffer))){
    ////            }
    ////            if(FAILED(m_pd3dDevice->GetDepthStencilSurface(&m_pZBuffer))){
    ////            }

            } else {
                //１画面使用・フルスクリーンモード
    //                LPDIRECT3DSWAPCHAIN9 _pSwapChain00 = NULL;//アダプタに関連付けれられたスワップチェーン
    //                LPDIRECT3DSURFACE9 _pBackBuffer00 = NULL;//バックバッファ1画面分
                //フルスクリーン
    //                hr = GgafDx9God::_pID3DDevice9->GetSwapChain( 0, &_pSwapChain00 );
    //                checkDxException(hr, D3D_OK, "0GetSwapChain() に失敗しました。");
    //                hr = _pSwapChain00->GetBackBuffer( 0, D3DBACKBUFFER_TYPE_MONO, &_pBackBuffer00 );
    //                checkDxException(hr, D3D_OK, "FULL 1gamen GetBackBuffer() に失敗しました。");

                hr = GgafDx9God::_pID3DDevice9->StretchRect(
                        _pRenderTextureSurface,
                        &_rectRenderTargetBuffer,
                        _pBackBuffer00,
                        &_aRect_Present[0],
                        D3DTEXF_LINEAR
                        );
                checkDxException(hr, D3D_OK, "FULL 1gamen StretchRect() に失敗しました。");

                hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);

    //                //コピーフリップ
    //                hr = _pSwapChain00->Present(NULL, NULL, NULL, NULL,0);
    //                checkDxException(hr, D3D_OK, "FULL 1gamen Present() に失敗しました。");


    //                RELEASE_SAFETY(_pBackBuffer00);
    //                RELEASE_SAFETY(_pSwapChain00);

            }
        } else {
            if (CFG_PROPERTY(DUAL_VIEW)) {
                //２画面使用・ウィンドウモード
                if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                    //縦横比固定モード
                    hr = GgafDx9God::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[0], &_aRect_Present[0], NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDx9God::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[1], &_aRect_Present[1], _pHWndSecondary, NULL);
                    }
                } else {
                    //縦横ストレッチモード
                    hr = GgafDx9God::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[0], NULL, NULL, NULL);
                    if (hr == D3D_OK) {
                        hr = GgafDx9God::_pID3DDevice9->Present(&_aRect_HarfRenderTargetBuffer[1], NULL, _pHWndSecondary, NULL);
                    }
                }
            } else {
                //１画面使用・ウィンドウモード
                if (CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
                    //縦横比固定モード
                    hr = GgafDx9God::_pID3DDevice9->Present(NULL, &_aRect_Present[0], NULL, NULL);
                } else {
                    //縦横ストレッチモード
                    hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);
                }
            }
        }



        if (hr != D3D_OK) { //hr は通常描画時は Present の戻り値
//            if (hr == D3DERR_DEVICELOST) {
                //出刃異素露巣斗！
            _TRACE_("＜警告＞デバイス異常発生!!" <<DXGetErrorString(hr) << " "<< DXGetErrorDescription(hr));
            if (hr == D3DERR_DEVICELOST) {
                _TRACE_("通常の正常デバイスロスト！");
//                _TRACE_("【デバイスロスト処理/リソース解放】協調性レベルチェック BEGIN ------>");
                //for(int i = 0; i < 300; i++) {
//                while(true) {
//                    hr = GgafDx9God::_pID3DDevice9->TestCooperativeLevel();
//                    if (hr == D3DERR_DEVICENOTRESET) {
//                        break;
//                    } else if (hr == D3DERR_DEVICELOST) {
//                        return;
//                    } else {
//                        throwGgafDxCriticalException(hr, "【デバイスロスト処理/リソース解放】TestCooperativeLevelの異常。強制終了します。");
//                    }
//                }
//                _TRACE_("【デバイスロスト処理/リソース解放】協調性レベルチェック <-------- END");
            }

            Sleep(1000); // 1秒待つ
            _TRACE_("【デバイスロスト処理】BEGIN ------>");

            //工場休止
            _TRACE_("【デバイスロスト処理】工場停止 BEGIN ------>");
            int cnt = 0;
            GgafFactory::beginRest();
            ___EndSynchronized; // <----- 排他終了
            for (int i = 0; GgafFactory::isResting() == false; i++) {
                Sleep(10); //工場が落ち着くまで待つ
                if (i > 3*60*1000) {
                    _TRACE_("【デバイスロスト処理/工場停止】 3分待機しましたが、工場から反応がありません。強制breakします。要調査");
                    break;
                }
            }
            ___BeginSynchronized; // ----->排他開始
            _TRACE_("【デバイスロスト処理】工場停止 <-------- END");

            _TRACE_("【デバイスロスト処理】リソース解放 BEGIN ------>");
            int c_again_cnt = 0;

            //レンダリングターゲット、デバイスロスト処理
            if (CFG_PROPERTY(FULL_SCREEN)) {
                releaseFullScreenRenderTarget();
            }
            //環境マップテクスチャ、デバイスロスト処理
            GgafDx9God::_pCubeMapTextureManager->releaseAll();
            //エフェクト、デバイスロスト処理
            GgafDx9God::_pEffectManager->onDeviceLostAll();
            //モデル解放
            GgafDx9God::_pModelManager->onDeviceLostAll();
            //全ノードに解放しなさいイベント発令
            getUniverse()->throwEventToLowerTree(GGAF_EVENT_ON_DEVICE_LOST, this);
            _TRACE_("【デバイスロスト処理】リソース解放 <-------- END");
            _is_device_lost_flg = true;
//            } else {
//                //Present異常時、デバイスロストと同じ処理を試みる。
//                _TRACE_("＜警告＞デバイス異常発生!!" <<DXGetErrorString(hr) << " "<< DXGetErrorDescription(hr) << "\n" <<
//                        "もう駄目かもしれないが、デバイスロストと同じ処理のReset()を試みます。");
//                _is_device_lost_flg = true;
//            }
        }
    }

    if (_is_device_lost_flg) {


//        if (CFG_PROPERTY(FULL_SCREEN)) {
//            HWND p;
//            while(true) {
////                p = GetActiveWindow();
//                if (CFG_PROPERTY(DUAL_VIEW)) {
//                    if (IsIconic(_pHWndPrimary) && IsIconic(_pHWndSecondary) ) {
//                        return;
//                    } else {
////                        ShowWindow(_pHWndSecondary, SW_SHOWNORMAL);
////                        ShowWindow(_pHWndPrimary, SW_SHOWNORMAL);
//                        break;
//                    }
//                } else {
//                    if (IsIconic(_pHWndPrimary) ) {
//                        return;
//                    } else {
//                        ShowWindow(_pHWndPrimary, SW_SHOWNORMAL);
//                        break;
//                    }
//                }
////                _TRACE_("p="<<p<<" _pHWndPrimary="<<_pHWndPrimary);
//
//                Sleep(5);
//            }
////        }

//        if (CFG_PROPERTY(FULL_SCREEN)) {
//			//MessageBox(GgafDx9God::_pHWndPrimary, TEXT("デバイスロスト検出。「 O K 」クリックで続行。"), TEXT("ERROR"), MB_OK | MB_ICONINFORMATION);
//
//
////            SetActiveWindow(_pHWndPrimary);
//            if (CFG_PROPERTY(DUAL_VIEW)) {
////                SetActiveWindow(_pHWndSecondary);
//                ShowWindow(_pHWndSecondary, SW_SHOWNORMAL);
//            }
//			ShowWindow(_pHWndPrimary, SW_SHOWNORMAL);
//        }


        _TRACE_("【デバイスロスト処理/リソース解放】協調性レベルチェック BEGIN ------>");
        //for(int i = 0; i < 300; i++) {
        while(true) {
            if (_can_wddm) {
                hr = ((IDirect3DDevice9Ex*)GgafDx9God::_pID3DDevice9)->CheckDeviceState(_pHWndPrimary);
                if (hr == D3DERR_DEVICELOST || hr == S_PRESENT_OCCLUDED) {
                    return;
                } else {
                    break;
                }
            } else {
                hr = GgafDx9God::_pID3DDevice9->TestCooperativeLevel();
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
        int again_cnt = 0;
        //for(int i = 0; i < 5; i++) {
        while(true) {

//          //for(int j = 0; j < 100; j++) {
//          while(true) {
//                hr = GgafDx9God::_pID3DDevice9->TestCooperativeLevel();
//                if (hr == D3DERR_DEVICENOTRESET) {
//                    break;
//                } else if (hr == D3DERR_DEVICELOST) {
//                  return;
//                } else {
//                    throwGgafDxCriticalException(hr, "【デバイスロスト処理/デバイスリセット】TestCooperativeLevelの異常。強制終了します。");
//                }
//            }
            if (CFG_PROPERTY(FULL_SCREEN) && CFG_PROPERTY(DUAL_VIEW)) {
                hr = GgafDx9God::_pID3DDevice9->Reset(_paPresetParam);
            } else {
                hr = GgafDx9God::_pID3DDevice9->Reset(&(_paPresetParam[0]));
            }
            if (hr != D3D_OK) {
                if (hr == D3DERR_DRIVERINTERNALERROR) {
                    Sleep(20);
                    return;
                } else if (hr == D3DERR_DRIVERINTERNALERROR) {
                    throwGgafDxCriticalException(hr, "【デバイスロスト処理/デバイスリセット】D3DERR_DRIVERINTERNALERROR。強制終了します。");
                } else if (hr == D3DERR_OUTOFVIDEOMEMORY) {
                    throwGgafDxCriticalException(hr, "【デバイスロスト処理/デバイスリセット】D3DERR_OUTOFVIDEOMEMORY。メモリがありません。強制終了します。");
                } else {
                    Sleep(20);
                    return;
//                    throwGgafDxCriticalException(hr, "【デバイスロスト処理/デバイスリセット】リセットに失敗しました。");
                }
            } else {
                break;
            }
        }
        _TRACE_("【デバイスロスト処理】デバイスリセット <-------- END");




        //デバイス再設定
        _TRACE_("【デバイスロスト処理】レンダリングターゲット再構築 BEGIN ------>");
        initDx9Device();
        if (CFG_PROPERTY(FULL_SCREEN)) {
            restoreFullScreenRenderTarget();
        }
        _TRACE_("【デバイスロスト処理】レンダリングターゲット描画先再構築 <-------- END");

		_TRACE_("【デバイスロスト処理】フルスクリーン時ウィンドウアクティブ BEGIN ------>");
		if (CFG_PROPERTY(FULL_SCREEN)) {
            if (CFG_PROPERTY(DUAL_VIEW)) {
                ShowWindow(_pHWndSecondary, SW_SHOWNORMAL);
				ShowWindow(_pHWndPrimary, SW_SHOWNORMAL);
			} else {
				ShowWindow(_pHWndPrimary, SW_SHOWNORMAL);
			}
        }
		Sleep(1000);
		_TRACE_("【デバイスロスト処理】フルスクリーン時ウィンドウアクティブ BEGIN ------>");

        //リソース再構築
        _TRACE_("【デバイスロスト処理】リソース再構築 BEGIN ------>");
        //環境マップテクスチャ、復帰処理
        GgafDx9God::_pCubeMapTextureManager->restoreAll();
        //エフェクトリセット
        GgafDx9God::_pEffectManager->restoreAll();
        //モデル再設定
        GgafDx9God::_pModelManager->restoreAll();
        //全ノードに再設定しなさいイベント発令
        getUniverse()->throwEventToLowerTree(GGAF_EVENT_DEVICE_LOST_REDEPOSITORY, this);
        //前回描画モデル情報を無効にする
        GgafDx9God::_pModelManager->_pModelLastDraw = NULL;
        _is_device_lost_flg = false;
        _TRACE_("【デバイスロスト処理】リソース再構築 <-------- END");

        //工場再開
        _TRACE_("【デバイスロスト処理】工場再起動 BEGIN ------>");
        GgafFactory::finishRest();
        _TRACE_("【デバイスロスト処理】工場再起動 <-------- END");

        _TRACE_("【デバイスロスト処理】<-------- END");

        Sleep(5000);
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                              NULL, // 矩形領域
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
                                              _color_background, //背景黒にクリア //D3DCOLOR_XRGB( 0, 0, 0 ), //背景黒にクリア
                                              1.0f, // Zバッファのクリア値
                                              0 // ステンシルバッファのクリア値
                                              );
    }

//    }
}

void GgafDx9God::finalizeUniversal() {
    if (_is_device_lost_flg) {
        return;
    } else {
		GgafGod::finalizeUniversal();
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
        DELETE_IMPOSSIBLE_NULL(_pCubeMapTextureManager);
        DELETE_IMPOSSIBLE_NULL(_pModelManager);
        DELETE_IMPOSSIBLE_NULL(_pEffectManager);
        _TRACE_("GgafDx9God::clean() end");
    }
}

void GgafDx9God::adjustGameScreen(HWND prm_pHWnd) {
     RECT rect;
    if (prm_pHWnd && !CFG_PROPERTY(FULL_SCREEN) && CFG_PROPERTY(FIXED_GAME_VIEW_ASPECT)) {
        HRESULT hr;
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                              NULL, // 矩形領域
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
                                              _color_background, //背景黒にクリア //D3DCOLOR_XRGB( 0, 0, 0 ), //背景黒にクリア
                                              1.0f, // Zバッファのクリア値
                                              0 // ステンシルバッファのクリア値
                );
        checkDxException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->Clear() に失敗しました。");
        if (::GetClientRect(prm_pHWnd, &rect)) {
            LONG width = rect.right;
            LONG height = rect.bottom;
            LONG fix_width, fix_height;
            if (CFG_PROPERTY(DUAL_VIEW)) {
                fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH)/2;
                fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
            } else {
                fix_width = CFG_PROPERTY(GAME_BUFFER_WIDTH);
                fix_height = CFG_PROPERTY(GAME_BUFFER_HEIGHT);
            }

            if (1.0f * width / height > 1.0f * fix_width / fix_height) {
                //より横長になってしまっている
                double rate = 1.0 * height / fix_height; //縮小率=縦幅の比率
                if (prm_pHWnd == _pHWndPrimary) {
                    _aRect_Present[0].left = (width / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[0].top = 0;
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                    positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0], width, height);
                } else {
                    _aRect_Present[1].left = (width / 2.0) - (fix_width * rate / 2.0);
                    _aRect_Present[1].top = 0;
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                    positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1], width, height);
                }


            } else {
                //より縦長になってしまっている
                double rate = 1.0 * width / fix_width; //縮小率=横幅の比率
                if (prm_pHWnd == _pHWndPrimary) {
                    _aRect_Present[0].left = 0;
                    _aRect_Present[0].top = (height / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[0].right  = _aRect_Present[0].left + (fix_width * rate);
                    _aRect_Present[0].bottom = _aRect_Present[0].top  + (fix_height * rate);
                    positionPresentRect(CFG_PROPERTY(GAME_VIEW1_POSITION), _aRect_Present[0], width, height);
                } else {
                    _aRect_Present[1].left = 0;
                    _aRect_Present[1].top = (height / 2.0) - (fix_height * rate / 2.0);
                    _aRect_Present[1].right  = _aRect_Present[1].left + (fix_width * rate);
                    _aRect_Present[1].bottom = _aRect_Present[1].top  + (fix_height * rate);
                    positionPresentRect(CFG_PROPERTY(GAME_VIEW2_POSITION), _aRect_Present[1], width, height);
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
    GgafDx9God::_pID3DDevice9->GetViewport(&(P_CAM->_viewport));
    _adjustGameScreen = false;
    _pHWnd_adjustScreen = NULL;
}

void GgafDx9God::positionPresentRect(int prm_pos, RECT& prm_rectPresent, int prm_screen_width, int prm_screen_height) {
//789
//456
//123
    if (prm_pos == 5) {
        return;
    }

    if (prm_pos == 7 || prm_pos == 8 || prm_pos == 9) {
        prm_rectPresent.bottom = prm_rectPresent.bottom - prm_rectPresent.top;
        prm_rectPresent.top = 0;
    } else if (prm_pos == 1 || prm_pos == 2 || prm_pos == 3) {
        prm_rectPresent.top = prm_screen_height - (prm_rectPresent.bottom - prm_rectPresent.top);
        prm_rectPresent.bottom = prm_screen_height;
    }

    if (prm_pos == 7 || prm_pos == 4 || prm_pos == 1) {
        prm_rectPresent.right = prm_rectPresent.right - prm_rectPresent.left;
        prm_rectPresent.left = 0;
    } else if (prm_pos == 9 || prm_pos == 6 || prm_pos == 3) {
        prm_rectPresent.left = prm_screen_width - (prm_rectPresent.right - prm_rectPresent.left);
        prm_rectPresent.right = prm_screen_width;
    }
}



//HRESULT
//GgafDx9God::EnsureD3DObjects()
//{
//	    UINT m_cAdapters;
//    HRESULT hr = S_OK;
// IDirect3D9    *m_pD3D;
//    IDirect3D9Ex  *m_pD3DEx;
//    HMODULE hD3D = NULL;
//    if (!m_pD3D)
//    {
//        hD3D = LoadLibrary(TEXT("d3d9.dll"));
//        DIRECT3DCREATE9EXFUNCTION pfnCreate9Ex = (DIRECT3DCREATE9EXFUNCTION)GetProcAddress(hD3D, "Direct3DCreate9Ex");
//        if (pfnCreate9Ex)
//        {
//            IFC((*pfnCreate9Ex)(D3D_SDK_VERSION, &m_pD3DEx));
//            IFC(m_pD3DEx->QueryInterface(IID_IDirect3D9, reinterpret_cast<void **>(&m_pD3D)));
//        }
//        else
//        {
//            m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
//            if (!m_pD3D)
//            {
//                IFC(E_FAIL);
//            }
//        }
//
//        m_cAdapters = m_pD3D->GetAdapterCount();
//    }
//
//Cleanup:
//    if (hD3D)
//    {
//        FreeLibrary(hD3D);
//    }
//
//    return hr;
//}
GgafDx9God::~GgafDx9God() {

    clean();
    _was_cleaned = true;

    //DirectSound解放
    GgafDx9Sound::release();
    //DirectInput解放
    GgafDx9Input::release();

    if(CFG_PROPERTY(FULL_SCREEN)) {
        releaseFullScreenRenderTarget();
    }

    _TRACE_("_pID3DDevice9 解放きたー");
    Sleep(60);
    DELETEARR_IMPOSSIBLE_NULL(_paPresetParam);
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
//                                                                     |
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
//    バックバッファ                ／      _pBackBuffer00          ／
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
//    バックバッファ      ／  _pBackBuffer00    ／           ／  _pBackBuffer01    ／
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


//D3DPTEXTURECAPS_POW2
//テクスチャの縦横のサイズは２の累乗である必要がある
//D3DPTEXTURECAPS_SQUAREONLY
//テクスチャの縦横のサイズは同じ、つまりテクスチャは正方形である必要がある
//MaxTextureWidth
//テクスチャの横幅の最大数
//MaxTextureHeight
//テクスチャの縦幅の最大数
