#ifndef GGAFDXCORE_GGAFDXGOD_H_
#define GGAFDXCORE_GGAFDXGOD_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/dxcore/util/GgafDxUtil.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"


#undef pGOD
#define pGOD ((GgafDxCore::GgafDxGod*)GgafCore::GgafGod::ask())

namespace GgafDxCore {

/**
 * DirectX神 .
 * @version 1.00
 * @since 2009/01/10
 * @author Masatoshi Tsuge
 */
class GgafDxGod : public GgafCore::GgafGod {

private:
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
    /** 今回採用されているデバイス（WDDM使用時のみ必要） */
    D3DDISPLAYMODEEX* _paDisplayMode;

    HWND* _paHWnd;

private:
    /**
     * WDDMかどうか判定し、デバイスを作成 .
     * 結果は GgafDxGod::_pID3D9 と GgafDxGod::_pID3DDevice9に保持される。
     * @param adapter
     * @param deviceType
     * @param hFocusWindow
     * @param behavior_flags
     * @param pPresentationParameters
     * @param pFullscreenDisplayMode
     * @return
     */
    HRESULT createDx9Device(UINT adapter,
                            D3DDEVTYPE device_type,
                            HWND hFocusWindow,
                            DWORD behavior_flags,
                            D3DPRESENT_PARAMETERS* pPresentationParameters,
                            D3DDISPLAYMODEEX* pFullscreenDisplayMode
                          );
    HRESULT initDx9Device();

    HRESULT restoreFullScreenRenderTarget();

    HRESULT releaseFullScreenRenderTarget();

    /**
     * ウィンドウモード時、ウィンドウサイズに応じた描画範囲を再設定する。
     * @param prm_pHWnd
     */
    void adjustGameWindow(HWND prm_pHWnd);

    /**
     * 表示位置番号に対応する矩形座標範囲(ピクセル)を取得する。
     * @param prm_pos 表示位置番号
     * @param inout_rectPresent [in]中央(pos=5)基準の領域矩形、[out]表示位置に対応する矩形座標範囲
     * @param prm_screen_width 画面幅(ピクセル)
     * @param prm_screen_height 画面高さ(ピクセル)
     */
    void setPositionPresentRect(int prm_pos, RECT& inout_rectPresent, pixcoord prm_screen_width, pixcoord prm_screen_height);

    /**
     * マルチディスプレイフルスクリーンモード時、モニタ座標情報を取得する .
     * 結果は _paAvailableAdapter[] メンバーに格納される。
     * EnumDisplayMonitorsによるコールバック関数。
     */
    static BOOL CALLBACK updateMoniterPixcoordCallback(HMONITOR hMonitor,
                                                       HDC      hdcMonitor,
                                                       LPRECT   lprcMonitor,
                                                       LPARAM   dwData    );
public:

    ///////////////////////////////////////////////////////////
    class Adapter {
    public:
        int mode_num;
        HMONITOR hMonitor;
        RECT rcMonitor;
        D3DDISPLAYMODE* paModes;
        Adapter() {
            mode_num = 0;
            hMonitor = nullptr;
            paModes = nullptr;
        }
        void setModeNum(int prm_mode_num) {
            mode_num = prm_mode_num;
            paModes = NEW D3DDISPLAYMODE[mode_num];
        }
        ~Adapter() {
            GGAF_DELETEARR_NULLABLE(paModes);
        }
    };

    /** 使用可能なデバイスのアダプタ数 */
    int _num_adapter;
    /** 使用可能なデバイスのアダプタの情報セット */
    Adapter* _paAvailableAdapter;
    ///////////////////////////////////////////////////////////
    struct RezoInfo {
        UINT width;
        UINT height;
        std::string item_str;
    };
    class AdapterRezos {
    public:
        int rezo_num;
        RezoInfo* paRezoInfo;
        AdapterRezos() {
            rezo_num = 0;
            paRezoInfo = nullptr;
        }
        void init(int prm_rezo_num) {
            rezo_num = prm_rezo_num;
            paRezoInfo = NEW RezoInfo[rezo_num];
        }
        ~AdapterRezos() {
            GGAF_DELETEARR_NULLABLE(paRezoInfo);
        }
    };
    /** 使用可能なデバイスのアダプタの解像度情報セット */
    AdapterRezos* _paAdapterRezos;
    ////////////////////////////////////////////////////////////

    /** モデル(GgafDxModel)資源管理者 */
    GgafDxModelManager* _pModelManager;
    /** エフェクト(GgafDxEffect)資源管理者 */
    GgafDxEffectManager* _pEffectManager;
    /** 環境マップ用テクスチャー(GgafDxTexture)資源管理者。（※通常のテクスチャはGgafDxModelの内部管理） */
    GgafDxTextureManager* _pCubeMapTextureManager;
    /** バンプマップ用テクスチャー(GgafDxTexture)資源管理者。（※通常のテクスチャはGgafDxModelの内部管理） */
    GgafDxTextureManager* _pBumpMapTextureManager;
    /** [r] 1画面目のウィンドウハンドル  */
    static HWND _pHWndPrimary;
    /** [r] 2画面目のウィンドウハンドル  */
    static HWND _pHWndSecondary;
    /** [r] 本アプリケーションのインスタンスハンドル */
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
    static DWORD _ambient_brightness_default;
    /** [r] デバイスロストフラグ (true=ロスト中) */
    static bool _is_device_lost_flg;
    /** [r] 画面アスペクト比調整フラグ (true=ウィンドウがリサイズされ、表示領域を再計算) */
    static bool _adjustGameWindow;
    /** [r] 表示領域を再計算が必要なウィンドウ(のハンドル) */
    static HWND _pHWnd_adjustScreen;


    /** [r] 頂点シェーダーのバージョン(D3DVS_VERSION(_Major,_Minor)) */
    static uint32_t _vs_v;
    /** [r] ピクセルシェーダーのバージョン(D3DPS_VERSION(_Major,_Minor)) */
    static uint32_t _ps_v;

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
    /** [r] １画面目アダプタ番号、 _aRect_HarfRenderTargetBuffer[] の序数 0 ～ */
    int _primary_adapter_no;
    /** [r] ２画面目アダプタ番号、 _aRect_HarfRenderTargetBuffer[] の序数 0 ～ */
    int _secondary_adapter_no;

public:
    /**
     * コンストラクタ<BR>
     */
    GgafDxGod();

    /**
     * フルスクリーン時、最も妥当な解像度を探す。
     * @param prm_paRezos 解像度情報配列
     * @param prm_rezo_num 解像度配列の要素数
     * @param prm_width 所望の解像度の幅
     * @param prm_height 所望の解像度の高さ
     * @return 最も妥当な要素インデックス
     */
    static int checkAppropriateDisplaySize(GgafDxGod::RezoInfo* prm_paRezos, int prm_rezo_num,
                                           UINT prm_width, UINT prm_height);
    /**
     * ウィンドウ生成処理 .
     * @param prm_wndclass1 １画面目のWNDCLASSEXパラメータ
     * @param prm_wndclass2 ２画面目のWNDCLASSEXパラメータ
     * @param prm_title1 １画面目のタイトル
     * @param prm_title2 ２画面目のタイトル
     * @param prm_dwStyle1 ウィンドウモード時のウインドウ1のスタイル定数(WS_OVERLAPPEDWINDOW 等)
     * @param prm_dwStyle2 ウィンドウモード時のウインドウ2のスタイル定数(WS_OVERLAPPEDWINDOW 等)
     * @param out_hWnd1 （戻り値）１画面目のウィンドウハンドル
     * @param out_hWnd2 （戻り値）２画面目のウィンドウハンドル
     */
    void createWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                      const char* prm_title1   , const char* prm_title2,
                      DWORD       prm_dwStyle1 , DWORD       prm_dwStyle2,
                      HWND&       out_hWnd1    , HWND&       out_hWnd2);

    /**
     * ウィンドウ生成処理 .
     * @param prm_wndclass1 WNDCLASSEXパラメータ
     * @param prm_title1    タイトル
     * @param prm_dwStyle1  ウィンドウモード時のウインドウ1のスタイル定数
     * @param out_hWnd1     （戻り値）１画面目のウィンドウハンドル
     */
    void createWindow(WNDCLASSEX& prm_wndclass1,
                      const char* prm_title1   ,
                      DWORD       prm_dwStyle1 ,
                      HWND&       out_hWnd1     );

    /**
     * ウィンドウ生成処理 .
     * 標準的なウィンドウを作成します。
     * @param prm_WndProc ウィンドウプロシージャ関数
     * @param prm_title1 １画面目のタイトル
     * @param prm_title2 ２画面目のタイトル
     * @param out_hWnd1 （戻り値）１画面目のウィンドウハンドル
     * @param out_hWnd2 （戻り値）２画面目のウィンドウハンドル
     */
    void createWindow(WNDPROC prm_WndProc,
                      const char* prm_title1, const char* prm_title2,
                      HWND&       out_hWnd1 , HWND&       out_hWnd2  );

    /**
     * ウィンドウ生成処理 .
     * 標準的なウィンドウを作成します。
     * @param prm_WndProc ウィンドウプロシージャ関数
     * @param prm_title1 １画面目のタイトル
     * @param prm_title2 ２画面目のタイトル
     */
    void createWindow(WNDPROC prm_WndProc,
                      const char* prm_title1, const char* prm_title2 = "window02");

    /**
     * ウィンドウ生成処理 .
     * ウィンドウモード時のウインドウスタイル定数は WS_OVERLAPPEDWINDOW が設定されます。
     * @param prm_wndclass1 １画面目のWNDCLASSEXパラメータ
     * @param prm_wndclass2 ２画面目のWNDCLASSEXパラメータ
     * @param prm_title1 １画面目のタイトル
     * @param prm_title2 ２画面目のタイトル
     * @param out_hWnd1 （戻り値）１画面目のウィンドウハンドル
     * @param out_hWnd2 （戻り値）２画面目のウィンドウハンドル
     */
    void createWindow(WNDCLASSEX& prm_wndclass1, WNDCLASSEX& prm_wndclass2,
                      const char* prm_title1   , const char* prm_title2,
                      HWND&       out_hWnd1    , HWND&       out_hWnd2);

    /**
     * ウィンドウ生成処理 .
     * ウィンドウモード時のウインドウスタイル定数は WS_OVERLAPPEDWINDOW が設定されます。
     * @param prm_wndclass1 １画面目のWNDCLASSEXパラメータ
     * @param prm_title1 １画面目のタイトル
     * @param out_hWnd1 （戻り値）１画面目のウィンドウハンドル
     */
    void createWindow(WNDCLASSEX& prm_wndclass1,
                      const char* prm_title1   ,
                      HWND&       out_hWnd1     );

    /**
     * ウィンドウのサイズを再設定 .
     * @param hWnd 再設定するウィンドウのHWND
     * @param client_width クライアント領域横幅（ピクセル）
     * @param client_height クライアント領域縦幅（ピクセル）
     */
    static void resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height);

    static void chengeViewPos1(int pos);
    static void chengeViewPos2(int pos);
    static void chengeViewPos(HWND prm_pHWnd, int pos);
    static void chengeViewAspect(bool prm_b);

    /**
     * ウィンドウを縁無しの最大化にする（ボーダーレス・フルスクリーン・ウィンドウ） .
     * @param prm_pHWnd 対象のウィンドウハンドル
     */
    static void chengeToBorderlessFullWindow(HWND prm_pHWnd);

    /**
     * ボーダーレス・フルスクリーン・ウィンドウを元に戻す .
     * @param prm_pHWnd 対象のウィンドウハンドル
     */
    static void backToNomalWindow(HWND prm_pHWnd);

    /**
     * DirectXのデバイスの初期設定を行う。
     * @return E_FAIL:失敗／D3D_OK:成功
     */
    virtual HRESULT initDevice();
    virtual void presentSpacetimeMoment() override;
    virtual void executeSpacetimeJudge() override;
    virtual void makeSpacetimeMaterialize() override;
    virtual void presentSpacetimeVisualize() override;
    virtual void finalizeSpacetime() override;


    /**
     * この世を取得 .
     * 下位でオーバーライド可能。<BR>
     * @return この世
     */
    virtual GgafDxSpacetime* getSpacetime() override {  //共変の戻り値
        return (GgafDxSpacetime*)_pSpacetime;
    }


    virtual GgafDxModelManager* getModelManager() {
        return _pModelManager;
    }
    virtual GgafDxEffectManager* getEffectManager() {
        return _pEffectManager;
    }

    virtual GgafDxModelManager* createModelManager();
    virtual GgafDxEffectManager* createEffectManager();


    virtual void clean() override;

    virtual ~GgafDxGod();
};

}
#endif /*GGAFDXCORE_GGAFDXGOD_H_*/
