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

private:

    /** 使用可能なデバイスのアダプタ数 */
    int _num_adapter;
    /** Windows Display Driver Model（WDDM）が使用可能か否か */
    bool _can_wddm;
    /** ゲーム表示領域以外のクリップ領域背景色 */
    D3DCOLOR _color_border;
    /** ゲーム表示領域の表示クリア時の背景色 */
    D3DCOLOR _color_clear;

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

    /** デバイス作成時パラメーター */
    D3DPRESENT_PARAMETERS* _paPresetPrm;
    /** デバイス作成時パラメーター（WDDM使用時のみ必要） */
    D3DDISPLAYMODEEX* _paDisplayMode;

    /**
     * WDDMかどうか判定し、デバイスを作成 .
     * 結果は GgafDxGod::_pID3D9 と GgafDxGod::_pID3DDevice9に保持される。
     * @param Adapter
     * @param DeviceType
     * @param hFocusWindow
     * @param BehaviorFlags
     * @param pPresentationParameters
     * @param pFullscreenDisplayMode
     * @return
     */
    HRESULT createDx9Device(UINT Adapter,
                            D3DDEVTYPE DeviceType,
                            HWND hFocusWindow,
                            DWORD BehaviorFlags,
                            D3DPRESENT_PARAMETERS* pPresentationParameters,
                            D3DDISPLAYMODEEX* pFullscreenDisplayMode
                          );
    HRESULT initDx9Device();

    HRESULT restoreFullScreenRenderTarget();

    HRESULT releaseFullScreenRenderTarget();

    void adjustGameScreen(HWND prm_pHWnd);

    /**
     * 表示位置番号に対応する矩形座標範囲(ピクセル)を取得する。
     * @param prm_pos 表示位置番号
     * @param inout_rectPresent [in]中央(pos=5)基準の領域矩形、[out]表示位置に対応する矩形座標範囲
     * @param prm_screen_width 画面幅(ピクセル)
     * @param prm_screen_height 画面高さ(ピクセル)
     */
    void positionPresentRect(int prm_pos, RECT& inout_rectPresent, pixcoord prm_screen_width, pixcoord prm_screen_height);

    /**
     * マルチディスプレイ、フルスクリーンモード時、
     * GgafDxGodのメンバーの _secondary_screen_x, _secondary_screen_y に
     * ２画面目の左上座標を保持させるためだけの、
     * EnumDisplayMonitorsによるコールバック関数。
     */
    static BOOL CALLBACK getSecondaryMoniterPixcoordCallback(HMONITOR hMonitor,
                                                             HDC      hdcMonitor,
                                                             LPRECT   lprcMonitor,
                                                             LPARAM   dwData    );
public:
    /** モデル(GgafDxModel)資源管理者 */
    static GgafDxModelManager* _pModelManager;
    /** エフェクト(GgafDxEffect)資源管理者 */
    static GgafDxEffectManager* _pEffectManager;
    /** 環境マップ用テクスチャー(GgafDxTexture)資源管理者。（※通常のテクスチャはGgafDxModelの内部管理） */
    static GgafDxTextureManager* _pCubeMapTextureManager;
    /** バンプマップ用テクスチャー(GgafDxTexture)資源管理者。（※通常のテクスチャはGgafDxModelの内部管理） */
    static GgafDxTextureManager* _pBumpMapTextureManager;
    /** [r] 1画面目のウィンドウハンドル  */
    static HWND _pHWndPrimary;
    /** [r] 2画面目のウィンドウハンドル  */
    static HWND _pHWndSecondary;

    static HINSTANCE _hInstance;
    /** [r] デバッグモード時、ワイヤーフレーム表示 */
    static D3DFILLMODE _d3dfillmode;
    /** [r] DirectX9のオブジェクト */
    static IDirect3D9* _pID3D9;
    /** [r] デバイス */
    static IDirect3DDevice9* _pID3DDevice9;
    /** [r] デフォルトのライト */
    static D3DLIGHT9 _d3dlight9_default;
    /** [r] アンビエントライトのデフォルトの明るさ */
    static DWORD _dwAmbientBrightness_default;
    /** [r] デバイスロストフラグ (true=ロスト中) */
    static bool _is_device_lost_flg;
    /** [r] 画面アスペクト比調整フラグ (true=ウィンドウがリサイズされ、表示領域を再計算) */
    static bool _adjustGameScreen;
    /** [r] 表示領域を再計算が必要なウィンドウ(のハンドル) */
    static HWND _pHWnd_adjustScreen;


    /** [r] 頂点シェーダーのバージョン(D3DVS_VERSION(_Major,_Minor)) */
    static UINT32 _vs_v;
    /** [r] ピクセルシェーダーのバージョン(D3DPS_VERSION(_Major,_Minor)) */
    static UINT32 _ps_v;

    /** [r] ゲームバッファ領域(ピクセル的な系) */
    RECT _rectGameBuffer;
    /** [r] フルスクリーン時、レンダリングターゲットテクスチャの領域(ピクセル) */
    RECT _rectRenderTargetBuffer;
    /** [r] ゲームバッファ領域の、[0]:左半分領域、[1]:右半分領域 (ピクセル) */
    RECT _aRect_HarfGameBuffer[2];
    /** [r] フルスクリーン時、レンダリングターゲットテクスチャ領域の、[0]:左半分領域、[1]:右半分領域 (ピクセル) */
    RECT _aRect_HarfRenderTargetBuffer[2];
    /** [r] 最終表示フロントバッファフレームの領域、[0]:１画面目、[1]:２画面目 (ピクセル) */
    RECT _aRect_ViewScreen[2];
    /** [r] Present領域、[0]:１画面目、[1]:２画面目 (ピクセル) */
    RECT _aRect_Present[2];
    /** [r] １画面目の _aRect_HarfRenderTargetBuffer[] の序数 0 or 1 */
    int _primary;
    /** [r] ２画面目の _aRect_HarfRenderTargetBuffer[] の序数 0 or 1 */
    int _secondary;
    /** [r] フルスクリーン時２画面目の左上X座標 */
    pixcoord _secondary_screen_x;
    /** [r] フルスクリーン時２画面目の左上Y座標 */
    pixcoord _secondary_screen_y;

    /**
     * コンストラクタ<BR>
     */
    GgafDxGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    HRESULT init();

    virtual void presentUniversalMoment() override;
    virtual void executeUniversalJudge() override;
    virtual void makeUniversalMaterialize() override;
    virtual void presentUniversalVisualize() override;
    virtual void finalizeUniversal() override;

    virtual void clean() override;

    virtual ~GgafDxGod();
};

}
#endif /*GGAFDXGOD_H_*/
