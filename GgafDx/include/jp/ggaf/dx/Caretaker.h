#ifndef GGAF_DX_CARETAKER_H_
#define GGAF_DX_CARETAKER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/scene/Spacetime.h"


/**
 * 管理者が保持する CurveManufactureManager に接続し、コネクションを取得。
 * @param X：曲線移動の情報識別文字列。プロパティ DIR_CURVE 配下の「X + ".ldr"」というファイル名を使用する
 * "FormationOebius002,1" の意味。読み込むファイル=FormationOebius002.ldr
 * 1 は採用するスプラインのインデックス(0〜)をあらわす。
 * CURVE=mobius1.spl,mobius3.spl,mobius5.spl
 * 定義されていた場合 1=mobius3.spl のデータを採用
 */
#define connectToCurveManufactureManager(X) ((GgafDx::CurveManufactureConnection*)((pCARETAKER)->_pCurveManufManager->connect((X), this)))

/**
 * 管理者が保持する CurveSourceManager に接続し、コネクションを取得。
 * X：識別文字列（CurveSourceManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) の prm_idstr に渡る)
 */
#define connectToCurveSourceManager(X)   ((GgafDx::CurveSourceConnection*)((pCARETAKER)->_pCurveSrcManager->connect((X), this)))

#define connectToTextureManager(X) ((GgafDx::TextureConnection*)(pCARETAKER)->_pTextureManager->connect((X), this))

#define connectToModelManager(X) ((GgafDx::ModelConnection*)(pCARETAKER)->_pModelManager->connect((X), this))

#define connectToEffectManager(X) ((GgafDx::EffectConnection*)(pCARETAKER)->_pEffectManager->connect((X), this))


#define PRIMARY_SCREEN 0
#define SECONDARY_SCREEN 1

#undef pCARETAKER
#define pCARETAKER ((GgafDx::Caretaker*)GgafCore::Caretaker::ask())

namespace GgafDx {

/**
 * DirectX管理者 .
 * @version 1.00
 * @since 2009/01/10
 * @author Masatoshi Tsuge
 */
class Caretaker : public GgafCore::Caretaker {

private:
    /** Windows Display Driver Model（WDDM）が使用可能か否か */
    bool _can_wddm;
    /** ゲーム表示領域以外のクリップ領域背景色 */
    D3DCOLOR _color_border;
    /** ゲーム表示領域の表示クリア時の背景色 */
    D3DCOLOR _color_clear;
    /** フルスクリーン時、レンダリングターゲットテクスチャのサーフェイス */
    IDirect3DSurface9*  _pRenderTextureSurface;
    /** フルスクリーン時、レンダリングターゲットのZバッファのサーフェイス */
    IDirect3DSurface9*  _pRenderTextureZ;
    /** フルスクリーン時、アダプタに関連付けれられたスワップチェーン、添字はディスプレイアダプタ番号 */
    IDirect3DSwapChain9** _papSwapChain;
    /** フルスクリーン時、DirectXのバックバッファ、添字はディスプレイアダプタ番号  */
    IDirect3DSurface9** _papBackBuffer;

    /** デバイス作成時パラメーター配列、添字はディスプレイアダブタ番号 */
    D3DPRESENT_PARAMETERS* _paPresetPrm;
    /** 今回採用されているデバイス配列、添字はディスプレイアダブタ番号（WDDM使用時のみ必要） */
    D3DDISPLAYMODEEX* _paDisplayMode;


private:
    /**
     * WDDMかどうか判定し、デバイスを作成 .
     * 結果は Caretaker::_pID3D9 と pCARETAKER->_pID3DDevice9に保持される。
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


    void setFullScreenWindowPos();

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
            GGAF_DELETEARR_NULLABLE(paModes);
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
            if (paRezoInfo) {
                GGAF_DELETEARR_NULLABLE(paRezoInfo);
            }
            paRezoInfo = NEW RezoInfo[rezo_num];
        }
        ~AdapterRezos() {
            GGAF_DELETEARR_NULLABLE(paRezoInfo);
        }
    };
    /** 使用可能なデバイスのアダプタの解像度情報セット */
    AdapterRezos* _paAdapterRezos;
    ////////////////////////////////////////////////////////////
    TextureManager* _pTextureManager;
    /** モデル(Model)資源管理者 */
    ModelManager* _pModelManager;
    /** エフェクト(Effect)資源管理者 */
    EffectManager* _pEffectManager;
    /** [r] 1画面目のウィンドウハンドル  */
    HWND _pHWndPrimary;
    /** [r] 2画面目のウィンドウハンドル  */
    HWND _pHWndSecondary;
    /** [r] ウィンドウハンドル  */
    HWND* _paHWnd;
    /** [r] 本アプリケーションのインスタンスハンドル */
    HINSTANCE _hInstance;
    /** [r] デバッグモード時、ワイヤーフレーム表示 */
    D3DFILLMODE _d3dfillmode;
    /** [r] DirectX9のオブジェクト */
    IDirect3D9* _pID3D9;
    /** [r] デバイス */
    IDirect3DDevice9* _pID3DDevice9;
    /** [r] デフォルトのライト */
    D3DLIGHT9 _d3dlight9_default;
    /** [r] デバイスロストフラグ (true=ロスト中) */
    bool _is_device_lost_flg;
    /** [r] 画面アスペクト比調整フラグ (true=ウィンドウがリサイズされ、表示領域を再計算) */
    bool _adjustGameWindow;

    /** [r] 頂点シェーダーのバージョン(D3DVS_VERSION(_Major,_Minor)) */
    uint32_t _vs_v;
    /** [r] ピクセルシェーダーのバージョン(D3DPS_VERSION(_Major,_Minor)) */
    uint32_t _ps_v;

    /** [r] ゲームバッファ領域(ピクセル的な系) */
    RECT _rectGameBuffer;
    /** [r] フルスクリーン時、レンダリングターゲットテクスチャからのコピー元領域(ピクセル) */
    RECT _rectRenderBufferSource;
    /** [r] フルスクリーン時、レンダリングターゲットテクスチャからのコピー元領域の、[0]:左半分領域、[1]:右半分領域 (ピクセル) */
    RECT _aRect_HarfRenderBufferSource[2];
    /** [r] 最終表示フロントバッファフレームの領域、[0]:１画面目、[1]:２画面目 (ピクセル) */
    RECT _aRect_FullScreen[2];
    /** [r] Present領域(フルスクリーン時、またはウィンドウ＆アスペクトFIXの場合)、[0]:１画面目、[1]:２画面目 (ピクセル) */
    RECT _aRect_Present[2];
    /** [r] １画面目アダプタ番号、 _aRect_HarfRenderBufferSource[] の序数 0 〜 */
    int _primary_screen_display_no;
    /** [r] ２画面目アダプタ番号、 _aRect_HarfRenderBufferSource[] の序数 0 〜 */
    int _secondary_screen_display_no;

public:
    CurveSourceManager* _pCurveSrcManager;
    CurveManufactureManager* _pCurveManufManager;

public:
    /**
     * コンストラクタ<BR>
     */
    Caretaker();

    void setDisplaySizeInfo();

    /**
     * 適切な解像度設定を行う .
     * @param allow_chang_rezo true:解像度変更を許可する／false:解像度変更はしない
     */
    void setAppropriateDisplaySize(bool allow_chang_rezo = true);


    /**
     * フルスクリーン時、最も妥当な解像度を探す。
     * @param prm_paRezos 解像度情報配列
     * @param prm_rezo_num 解像度配列の要素数
     * @param prm_width 所望の解像度の幅
     * @param prm_height 所望の解像度の高さ
     * @return 最も妥当な要素インデックス
     */
    int checkAppropriateDisplaySize(Caretaker::RezoInfo* prm_paRezos, int prm_rezo_num,
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
     * @param out_hWnd1 （戻り値）１画面目のウィンドウハンドル
     */
    void createWindow(WNDPROC prm_WndProc,
                      const char* prm_title1,
                      HWND& out_hWnd1);

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
    void resetInitWindowsize();
    void resetDotByDotWindowsize(int d);
    void resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height);

    void chengeViewPos1(int pos);
    void chengeViewPos2(int pos);
    void chengeViewPos(HWND prm_pHWnd, int pos);
    void chengeViewAspect(bool prm_b);

    /**
     * ウィンドウを縁無しの最大化にする（ボーダーレス・フルスクリーン・ウィンドウ） .
     * @param prm_pHWnd 対象のウィンドウハンドル
     */
    void chengeToBorderlessFullWindow(HWND prm_pHWnd);

    /**
     * ボーダーレス・フルスクリーン・ウィンドウを元に戻す .
     * @param prm_pHWnd 対象のウィンドウハンドル
     */
    void backToNomalWindow(HWND prm_pHWnd);

    /**
     * DirectXのデバイスの初期設定を行う。
     * @return E_FAIL:失敗／D3D_OK:成功
     */
    virtual HRESULT initDevice();
    virtual void presentMoment() override;
    virtual void presentBehave() override;
    virtual void presentJudge() override;
    virtual void presentMaterialize() override;
    virtual void presentVisualize() override;
    virtual void presentClosing() override;

    /**
     * この世を取得 .
     * 下位でオーバーライド可能。<BR>
     * @return この世
     */
    virtual Spacetime* getSpacetime() override {  //共変の戻り値
        return (Spacetime*)_pSpacetime;
    }

    virtual TextureManager* getTextureManager() {
        return _pTextureManager;
    }

    virtual ModelManager* getModelManager() {
        return _pModelManager;
    }

    virtual EffectManager* getEffectManager() {
        return _pEffectManager;
    }

    virtual TextureManager* createTextureManager();
    virtual ModelManager* createModelManager();
    virtual EffectManager* createEffectManager();

    virtual CurveSourceManager* createCurveSourceManager();
    virtual CurveManufactureManager* createCurveManufactureManager();

    /**
     * ライトの色（デフォルト：1.0, 1.0, 1.0）を設定 .
     * 【注意】Effectオブジェクトが作成される前に設定しないと反映がされない。
     * @param r
     * @param g
     * @param b
     */
    void setLightDiffuseColor(float r, float g, float b);

    /**
     * 環境光の色を設定（デフォルト：0.2, 0.2, 0.2） .
     * 【注意】Effectオブジェクトが作成される前に設定しないと反映がされない。
     * @param r
     * @param g
     * @param b
     */
    void setLightAmbientColor(float r, float g, float b);

    virtual void clean() override;

    virtual ~Caretaker();
};

}
#endif /*GGAF_DX_CARETAKER_H_*/
