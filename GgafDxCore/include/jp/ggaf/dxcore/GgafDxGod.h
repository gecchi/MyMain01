#ifndef GGAFDXGOD_H_
#define GGAFDXGOD_H_


namespace GgafDxCore {
/**
 * DirectX神 .
 * @version 1.00
 * @since 2009/01/10
 * @author Masatoshi Tsuge
 */
class GgafDxGod : public GgafCore::GgafGod {

public:
    static GgafDxModelManager* _pModelManager;
    static GgafDxEffectManager* _pEffectManager;
    static GgafDxTextureManager* _pCubeMapTextureManager;

    static HWND _pHWndPrimary;
    static HWND _pHWndSecondary;
    static HINSTANCE _hInstance;

    static D3DFILLMODE _d3dfillmode;

    /** DirectX9のオブジェクト */
    static IDirect3D9* _pID3D9;
    /** デバイス */
    static IDirect3DDevice9* _pID3DDevice9;
    /** デフォルトのライト */
    static D3DLIGHT9 _d3dlight9_default;
    /** アンビエントライトのデフォルトの明るさ */
    static DWORD _dwAmbientBrightness_default;
    /** デバイスロストフラグ (true=ロスト中) */
    static bool _is_device_lost_flg;


    static bool _adjustGameScreen;
    static HWND _pHWnd_adjustScreen;

    /** 使用可能なデバイスのアダプタ数 */
    int _num_adapter;


    /** Windows Display Driver Model（WDDM）が使用可能か否か */
    bool _can_wddm;

    /** デバイス作成時パラメーター */
    D3DPRESENT_PARAMETERS* _paPresetParam;
    /** デバイス作成時パラメーター（WDDM使用時のみ必要） */
    D3DDISPLAYMODEEX* _paDisplayMode;

    /** ゲームバッファ領域 */
    RECT _rectGameBuffer;
    /** フルスクリーン時、レンダリングターゲットテクスチャの領域 */
    RECT _rectRenderTargetBuffer;
    /** ゲームバッファ領域の、[0]:左半分領域、[1]:右半分領域 */
    RECT _aRect_HarfGameBuffer[2];
    /** フルスクリーン時、レンダリングターゲットテクスチャ領域の、[0]:左半分領域、[1]:右半分領域 */
    RECT _aRect_HarfRenderTargetBuffer[2];
    /** 最終表示フロントバッファフレームの領域、[0]:１画面目、[1]:２画面目 */
    RECT _aRect_ViewScreen[2];
    /** Present領域、[0]:１画面目、[1]:２画面目  */
    RECT _aRect_Present[2];
    /** １画面目の _aRect_HarfRenderTargetBuffer[] の序数 */
    int _primary;
    /** ２画面目の _aRect_HarfRenderTargetBuffer[] の序数 */
    int _secondary;
    /** フルスクリーン時２画面目の左上X座標 */
    pixcoord _secondary_screen_x;
    /** フルスクリーン時２画面目の左上Y座標 */
    pixcoord _secondary_screen_y;

    /** フルスクリーン時、レンダリングターゲットテクスチャ */
    IDirect3DTexture9*  _pRenderTexture;
    /** フルスクリーン時、レンダリングターゲットテクスチャのサーフェイス */
    IDirect3DSurface9*  _pRenderTextureSurface;
    /** フルスクリーン時、レンダリングターゲットのZバッファのサーフェイス */
    IDirect3DSurface9*  _pRenderTextureZ;
    /** フルスクリーン時、アダプタに関連付けれられたスワップチェーン、[0]:１画面目、[1]:２画面目 */
    IDirect3DSwapChain9* _apSwapChain[2];
    /** フルスクリーン時、DirectXのバックバッファ、[0]:１画面目、[1]:２画面目 */
    IDirect3DSurface9* _apBackBuffer[2];

    /** 頂点シェーダーのバージョン(D3DVS_VERSION(_Major,_Minor)) */
    static UINT32 _vs_v;
    /** ピクセルシェーダーのバージョン(D3DPS_VERSION(_Major,_Minor)) */
    static UINT32 _ps_v;


    /** ゲーム表示領域以外のクリップ領域背景色 */
    D3DCOLOR _color_background;
    /** ゲーム表示領域の表示クリア時の背景色 */
    D3DCOLOR _color_clear;
    /**
     * コンストラクタ<BR>
     */
    GgafDxGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    /**
     * 初期化<BR>
     */
    HRESULT init();
    HRESULT createDx9Device(UINT Adapter,
                            D3DDEVTYPE DeviceType,
                            HWND hFocusWindow,
                            DWORD BehaviorFlags,
                            D3DPRESENT_PARAMETERS* pPresentationParameters,
                            D3DDISPLAYMODEEX *pFullscreenDisplayMode
                          );
    HRESULT initDx9Device();
    HRESULT restoreFullScreenRenderTarget();
    HRESULT releaseFullScreenRenderTarget();

    virtual void presentUniversalMoment() override;
    virtual void executeUniversalJudge() override;
    virtual void makeUniversalMaterialize() override;
    virtual void presentUniversalVisualize() override;
    virtual void finalizeUniversal() override;

    void adjustGameScreen(HWND prm_pHWnd);

    void positionPresentRect(int prm_pos, RECT& prm_rectPresent, int prm_screen_width, int prm_screen_height);

    HRESULT restoreRenderSurface();

    virtual void clean() override;

    virtual ~GgafDxGod();
};

}
#endif /*GGAFDXGOD_H_*/
