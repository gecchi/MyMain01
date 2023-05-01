#ifndef GGAF_DX_CARETAKER_H_
#define GGAF_DX_CARETAKER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/core/Caretaker.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/dx/scene/Spacetime.h"
#include <map>


/**
 * 管理者が保持する CurveManufactureManager に接続し、コネクションを取得。
 * @param X：曲線移動の情報識別文字列。プロパティ DIR_CURVE 配下の「X + ".ldr"」というファイル名を使用する
 * "FormationOebius002,1" の意味。読み込むファイル=FormationOebius002.ldr
 * 1 は採用するスプラインのインデックス(0～)をあらわす。
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


#undef pCARETAKER
#define pCARETAKER ((GgafDx::Caretaker*)GgafCore::Caretaker::ask())

#define SCREEN01 0
#define SCREEN02 1
#define SCREEN03 2
#define SCREEN04 3
#define SCREEN05 4
#define SCREEN06 5
#define SCREEN07 6
#define SCREEN08 7
#define SCREEN09 8
#define SCREEN10 9
#define SCREEN11 10
#define SCREEN12 11
#define SCREEN13 12
#define SCREEN14 13
#define SCREEN15 14
#define SCREEN16 15

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

    /** デバイス作成時パラメーター配列、添字はディスプレイアダブタ番号(但し、最低 MAX_SCREENS あり) */
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
     */
    void adjustGameWindow();
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
    /** 使用可能なデバイスのディスプレイアダプタ数 */
    int _num_adapter;
    /** 使用可能なデバイスのアダプタの情報セット、要素数は _num_adapter  */
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
    /** 使用可能なデバイスのアダプタの解像度情報セット、要素数は _num_adapter */
    AdapterRezos* _paAdapterRezos;
    ////////////////////////////////////////////////////////////

    TextureManager* _pTextureManager;
    /** モデル(Model)資源管理者 */
    ModelManager* _pModelManager;
    /** エフェクト(Effect)資源管理者 */
    EffectManager* _pEffectManager;
    /** [r] 1画面目のウィンドウハンドル  */
    HWND _pHWndPrimary;
    /** [r] ウィンドウハンドルの配列、要素の添字は D3DPRESENT_PARAMETERS要素番号(アダプタ番号含む) */
    HWND* _paHWnd;
    /** [r] window数。ウインドウモード時は NUMBER_OF_SCREENS_USED、フルスクリーン時はアダプタ数。 */
    int _num_window;

    int _screen_display_no[MAX_SCREENS];
    /** [r]windowインデックス(=フルスクリーン時はアダプタインデックス) → スクリーンプライオリティ。0:SCREEN01/1:SCREEN02/2:TERTIARY */
    int* _paWindowNoToScreenPry;

    /** [r] HWND => スクリーンプライオリティ。0:SCREEN01/1:SCREEN02/2:TERTIARY */
    std::map<HWND, int> _mapHwndToPry;
    /** [r] HWND => アダプタ番号 */
    std::map<HWND, int> _mapHwndToWindowNo;

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
//    RECT _aRectRenderBufferSource[SCREEN01];
    /** [r] フルスクリーン時、レンダリングターゲットテクスチャからのコピー元領域の、[0]:左半分領域、[1]:右半分領域 (ピクセル) */
    RECT _aRectRenderBufferSource[MAX_SCREENS];
    /** [r] 最終表示フロントバッファフレームの領域、[0]:１画面目、[1]:２画面目 (ピクセル) */
    RECT _aRect_FullScreen[MAX_SCREENS];
    /** [r] Present領域(フルスクリーン時、またはウィンドウ＆アスペクトFIXの場合)、[0]:１画面目、[1]:２画面目 (ピクセル) */
    RECT _aRect_Present[MAX_SCREENS];
    /** [r] １画面目アダプタ番号、 _aRectRenderBufferSource[] の序数 0 ～ */
    int _primary_screen_adpter_no;
    /** [r] ２画面目アダプタ番号、 _aRectRenderBufferSource[] の序数 0 ～ */
//    int _secondary_screen_adpter_no;

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
     * @param prm_WndProc ウィンドウプロシージャ
     * @param prm_title ウィンドウタイトル（２画面目以降、タイトル末尾に"(2)"と画面番号が勝手に付与）
     */
    void createWindow(WNDPROC prm_WndProc,
                      const char* prm_title);

    /**
     * ウィンドウ生成処理 .
     * @param prm_wndclass ウィンドウのWNDCLASSEXパラメータ
     * @param prm_title ウィンドウタイトル（２画面目以降、タイトル末尾に"(2)"と画面番号が勝手に付与）
     * @param prm_dwStyle ウィンドウモード時のスタイル定数
     */
    void createWindow(WNDCLASSEX& prm_wndclass,
                      const char* prm_title   ,
                      DWORD       prm_dwStyle );

    int getNumWindow() {
        return _num_window;
    }
    HWND getHWND(int prm_pry) {
        return _paHWnd[prm_pry];
    }
    /**
     * ウィンドウのサイズを再設定 .
     * @param hWnd 再設定するウィンドウのHWND
     * @param client_width クライアント領域横幅（ピクセル）
     * @param client_height クライアント領域縦幅（ピクセル）
     */
    void resetInitWindowsize();
    void resetDotByDotWindowsize(int d);
    void resetWindowsize(HWND hWnd, pixcoord client_width, pixcoord client_height);

    void chengePrimaryScreenPresentPos(int pos);
    void chengeSecondaryScreenPresentPos(int pos);
    void chengeScreenPresentPos(HWND prm_pHWnd, int pos);

    void chengeViewAspect1(bool prm_b);
    void chengeViewAspect2(bool prm_b);
    void chengeViewAspect(HWND prm_pHWnd, bool prm_b);

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
