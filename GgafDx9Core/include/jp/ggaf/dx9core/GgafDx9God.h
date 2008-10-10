#ifndef GGAFDX9GOD_H_
#define GGAFDX9GOD_H_

class GgafDx9God : public GgafGod {

public:
	static HWND _hWnd;
	static HINSTANCE _hInstance;



	/** DirectX9のオブジェクト */
	static IDirect3D9* _pID3D9;
	/** デバイス */
	static IDirect3DDevice9* _pID3DDevice9;
	/** デフォルトのライト */
	static D3DLIGHT9 _d3dlight9;
	/** Present領域 */
	static RECT _rectPresentDest;
	/* スクリーン高さ（ピクセル） */
	//static int const GAME_SCREEN_HEIGHT;

    static D3DPRESENT_PARAMETERS _structD3dPresent_Parameters;

	/** デバイスロストフラグ (true=ロスト中) */
	static bool _deviceLostFlg;

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

	/**
	 * デストラクタ<BR>
	 */
	virtual ~GgafDx9God();
};



#endif /*GGAFDX9GOD_H_*/
