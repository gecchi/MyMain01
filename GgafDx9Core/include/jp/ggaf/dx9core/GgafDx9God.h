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
    static HWND _hWnd;
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

    /** Present領域 */
    static RECT _rectPresentDest;
    /* スクリーン高さ（ピクセル） */
    //static int const GAME_SCREEN_HEIGHT;

    static D3DPRESENT_PARAMETERS _structD3dPresent_Parameters;

    /** デバイスロストフラグ (true=ロスト中) */
    static bool _is_device_lost_flg;


//    /** 射影変換魚売れる */
//    static D3DXMATRIX _vMatrixProj;
//    /** 正射影変換魚売れる */
//    static D3DXMATRIX _vMatrixOrthoProj;
//

    static GgafDx9ModelManager* _pModelManager;
    static GgafDx9EffectManager* _pEffectManager;


    /**
     * コンストラクタ<BR>
     */
    GgafDx9God(HINSTANCE prm_hInstance, HWND prm_hWnd);

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


    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9God();
};

}
#endif /*GGAFDX9GOD_H_*/
