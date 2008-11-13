#ifndef GGAFDX9GOD_H_
#define GGAFDX9GOD_H_

class GgafDx9God : public GgafGod {

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
	static bool _deviceLostFlg;

	/** カメラのZ座標初期位置 */
	static double _dCamZ_ini;

	/** カメラのZ座標 */
	static double _dCamZ;
	/** カメラの位置 */
	static D3DXVECTOR3* _pVecCamFromPoint;
	/** カメラの注視点 */
	static D3DXVECTOR3*  _pVecCamLookatPoint;
	/** カメラの上ベクトル */
	static D3DXVECTOR3*  _pVecCamUp;
	/** VIEW変換行列 */
	static D3DXMATRIX _vMatrixView;

	static int _iPxDep;


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
	virtual void makeWorldMaterialize();

 	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void makeWorldVisualize();

	D3DXMATRIX getInvRotateMat();
//    /**
//     * Worldシーンを作成。
//	 * ＜OverRide です＞<BR>
//	 */
//	virtual GgafWorld* createWorld() {
//		return (GgafWorld*)createDx9World();
//	};
//
//
//    /**
//     * Worldシーンを作成。
//	 * ＜OverRide です＞<BR>
//	 */
//	virtual GgafDx9World* createDx9World() = 0;

	void setCam(D3DXVECTOR3* prm_pEye, D3DXVECTOR3* prm_pAt, D3DXVECTOR3* prm_pUp);

	/**
	 * デストラクタ<BR>
	 */
	virtual ~GgafDx9God();
};



#endif /*GGAFDX9GOD_H_*/
