#ifndef GGAFDX9GOD_H_
#define GGAFDX9GOD_H_
namespace GgafDx9Core {
/**
 * DirectX神 .
 * @version 1.00
 * @since 2009/01/10
 * @author Masatoshi Tsuge
 */
class GgafDx9God : public GgafCore::GgafGod {

public:
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
    /** 一時的なライト（現在未使用） */
    static D3DLIGHT9 _d3dlight9_temp;
    /** アンビエントライトのデフォルトの明るさ */
    static DWORD _dwAmbientBrightness_default;
    /** デバイスロストフラグ (true=ロスト中) */
    static bool _is_device_lost_flg;

    static bool _adjustGameScreen;
    static HWND _pHWnd_adjustScreen;
    static GgafDx9ModelManager* _pModelManager;
    static GgafDx9EffectManager* _pEffectManager;
    static GgafDx9TextureManager* _pCubeMapTextureManager;
    static int _iNumAdapter;
    /** Present領域 */

    RECT _aRect_Present[2];
    int _primary, _secondary;
    /* スクリーン高さ（ピクセル） */
    //static int const GAME_BUFFER_HEIGHT;

    static D3DPRESENT_PARAMETERS* _d3dparam;
//    static LPDIRECT3DSWAPCHAIN9 _paSwapChain;
//    static LPDIRECT3DSWAPCHAIN9 _paBackBuffer;



    RECT _rectGameBuffer;
    RECT _rectRenderTargetBuffer;
    RECT _aRect_HarfGameBuffer[2];
    RECT _aRect_HarfRenderTargetBuffer[2];
    RECT _aRect_ViewScreen[2];
//    static RECT*  _pRectViewScreen;
    IDirect3DTexture9*  _pRenderTexture;   //テクスチャ
//    static IDirect3DSurface9*  _pBackBuffer;      //バックバッファ
    IDirect3DSurface9*  _pRenderTextureSurface;     //サーフェイス
    IDirect3DSurface9*  _pRenderTextureZ;   //テクスチャ

    LPDIRECT3DSWAPCHAIN9 _pSwapChain00;//アダプタに関連付けれられたスワップチェーン
    LPDIRECT3DSURFACE9 _pBackBuffer00;//バックバッファ1画面分
    LPDIRECT3DSWAPCHAIN9 _pSwapChain01;//アダプタに関連付けれられたスワップチェーン
    LPDIRECT3DSURFACE9 _pBackBuffer01;//バックバッファ１画面分


    static UINT32 _vs_v;
    static UINT32 _ps_v;

    static D3DXMACRO _aD3DXMacro_Defines[3];

    D3DCOLOR _color_background;
    D3DCOLOR _color_clear;
    /**
     * コンストラクタ<BR>
     */
    GgafDx9God(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);

    /**
     * 初期化<BR>
     */
    HRESULT init();
    HRESULT initDx9Device();

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void makeUniversalMaterialize();

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void presentUniversalVisualize();

    void adjustGameScreen(HWND prm_pHWnd);

    void positionPresentRect(int prm_pos, RECT& prm_rectPresent, int prm_screen_width, int prm_screen_height);

    D3DXMATRIX getInvRotateMat();
    //    /**
    //     * Worldシーンを作成。
    //	 * ＜OverRide です＞<BR>
    //	 */
    //	virtual GgafUniverse* createUniverse() {
    //		return (GgafUniverse*)createDx9World();
    //	};
    //
    //
    //    /**
    //     * Worldシーンを作成。
    //	 * ＜OverRide です＞<BR>
    //	 */
    //	virtual GgafDx9Universe* createDx9World() = 0;

    virtual void clean() override;
    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9God();
};

}
#endif /*GGAFDX9GOD_H_*/
