#include "stdafx.h"


HWND GgafDx9God::_hWnd = NULL;
HINSTANCE GgafDx9God::_hInstance = NULL;

IDirect3D9* GgafDx9God::_pID3D9 = NULL;
IDirect3DDevice9* GgafDx9God::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDx9God::_d3dlight9;
RECT GgafDx9God::_rectPresentDest;


//int const GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)  = 1024;
//int const GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) = 600;
D3DPRESENT_PARAMETERS GgafDx9God::_structD3dPresent_Parameters;
bool GgafDx9God::_deviceLostFlg = false;

GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND _hWnd) : GgafGod() {
	TRACE("GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND prmGgafDx9God::_hWnd) ");
	GgafDx9God::_hWnd = _hWnd;
	GgafDx9God::_hInstance = prm_hInstance;
	_deviceLostFlg = false;
	CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 は Seed

}

HRESULT GgafDx9God::init() {
	bool FULLSCRREEN = GGAFDX9_PROPERTY(FULL_SCREEN);
	_rectPresentDest.left = 0;
	_rectPresentDest.top = 0;
	_rectPresentDest.right = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH);
	_rectPresentDest.bottom = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT);

	HRESULT hr;

	//IDirect3D9コンポーネントの取得
	if (!(GgafDx9God::_pID3D9 = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		throw_GgafCriticalException("Direct3DCreate9 に失敗しました");
		return E_FAIL;  //失敗
	}



	//デスプレイモードの取得
	D3DDISPLAYMODE structD3DDisplayMode;  //結果が格納される構造体
	hr = GgafDx9God::_pID3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&structD3DDisplayMode);
	if (FAILED(hr))	{
		throw_GgafCriticalException("GetAdapterDisplayMode に失敗しました");
		return E_FAIL;
	}

	//デバイス作成
	ZeroMemory(&_structD3dPresent_Parameters,sizeof(D3DPRESENT_PARAMETERS));
	//バックバッファの縦サイズ
	//_structD3dPresent_Parameters.BackBufferHeight = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT);
	_structD3dPresent_Parameters.BackBufferHeight = GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT);
	//バックバッファの横サイズ
	//_structD3dPresent_Parameters.BackBufferWidth = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH);
	_structD3dPresent_Parameters.BackBufferWidth = GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH);
	//バックバッファのフォーマット
	if (FULLSCRREEN) {
		_structD3dPresent_Parameters.BackBufferFormat = D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;	//フルスクリーン時
	} else {
		_structD3dPresent_Parameters.BackBufferFormat = structD3DDisplayMode.Format; //ウィンドウ時
	}
	//_structD3dPresent_Parameters.BackBufferFormat = D3DFMT_UNKNOWN;	//現在の画面モードを利用
	//バックバッファの数
	_structD3dPresent_Parameters.BackBufferCount = 1;
	//マルチサンプルの数
	_structD3dPresent_Parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	//マルチサンプルの品質レベル
	_structD3dPresent_Parameters.MultiSampleQuality = 0;
	//スワップ効果を指定する
	_structD3dPresent_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//ウィンドウハンドル
	_structD3dPresent_Parameters.hDeviceWindow = NULL;
	//ウィンドウモード
	if (FULLSCRREEN) {
		_structD3dPresent_Parameters.Windowed = false;  //フルスクリーン時
	} else {
		_structD3dPresent_Parameters.Windowed = true;     //ウィンドウ時
	}
	//深度ステンシルバッファ
	//_structD3dPresent_Parameters.EnableAutoDepthStencil = FALSE;
	//_structD3dPresent_Parameters.AutoDepthStencilFormat = 0;
	_structD3dPresent_Parameters.EnableAutoDepthStencil = 1;   //Z バッファの自動作成
	_structD3dPresent_Parameters.AutoDepthStencilFormat = D3DFMT_D16;
	//0にしておく
	_structD3dPresent_Parameters.Flags = 0;
	//フルスクリーンでのリフレッシュレート(ウィンドウモードなら0を指定)
	if (FULLSCRREEN) {
		_structD3dPresent_Parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;    //フルスクリーン時
	} else {
		_structD3dPresent_Parameters.FullScreen_RefreshRateInHz = 0;                          //ウィンドウ時
	}
	//スワップのタイミング
	if (FULLSCRREEN) {
		_structD3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	} else {
		_structD3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //即座(Windowモードはこちらが良いらしい）
	}

	//フルスクリーンに出来るか調べる
	if (FULLSCRREEN) {
		int cc = GgafDx9God::_pID3D9->GetAdapterModeCount(D3DADAPTER_DEFAULT, _structD3dPresent_Parameters.BackBufferFormat);
	    if(cc){
	        D3DDISPLAYMODE adp;
	        for(int i = 0; i < cc; i++){
	        	GgafDx9God::_pID3D9->EnumAdapterModes(D3DADAPTER_DEFAULT, _structD3dPresent_Parameters.BackBufferFormat, i, &adp);
	            if (adp.Format == _structD3dPresent_Parameters.BackBufferFormat &&
	                adp.Width  == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH)     &&
	                adp.Height == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) )
	            {
	            	//OK
	            	break;
	            }
	            if (cc == i) {
	            	//要求した使える解像度が見つからない
	            	throw_GgafCriticalException(GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH) <<"x"<<GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) << "のフルスクリーンモードにする事ができません。");
	            	return E_FAIL;
	            }
	        }
	    } else {
			throw_GgafCriticalException("GetAdapterModeCount に失敗しました");
			return E_FAIL;
		}
	}

	//デバイス作成を試み GgafDx9God::_pID3DDevice9 へ設定する。
	//ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
	hr = GgafDx9God::_pID3D9->CreateDevice(
								D3DADAPTER_DEFAULT,
								D3DDEVTYPE_HAL,
								GgafDx9God::_hWnd,
								D3DCREATE_HARDWARE_VERTEXPROCESSING,
								&_structD3dPresent_Parameters,
								&GgafDx9God::_pID3DDevice9);
	if (FAILED(hr)) {
		//ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
		hr = GgafDx9God::_pID3D9->CreateDevice(
									D3DADAPTER_DEFAULT,
									D3DDEVTYPE_HAL,
									GgafDx9God::_hWnd,
									D3DCREATE_SOFTWARE_VERTEXPROCESSING,
									&_structD3dPresent_Parameters,
									&GgafDx9God::_pID3DDevice9);
		if (FAILED(hr)) {
			//ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
			hr = GgafDx9God::_pID3D9->CreateDevice(
										D3DADAPTER_DEFAULT,
										D3DDEVTYPE_REF,
										GgafDx9God::_hWnd,
										D3DCREATE_SOFTWARE_VERTEXPROCESSING,
										&_structD3dPresent_Parameters,
										&GgafDx9God::_pID3DDevice9);
			if (FAILED(hr)) {
				//どのデバイスの作成も失敗した場合
				MessageBox(GgafDx9God::_hWnd,TEXT("Direct3Dの初期化に失敗"),TEXT("ERROR"),MB_OK | MB_ICONSTOP);
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
	return initDx9Device();

}





HRESULT GgafDx9God::initDx9Device() {
	 // デフォルトのライト
/*
	ZeroMemory(&_d3dlight9, sizeof(D3DLIGHT9) );
	GgafDx9God::_d3dlight9.Type = D3DLIGHT_DIRECTIONAL; //平行光、色と方向だけでよい
	GgafDx9God::_d3dlight9.Direction = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	GgafDx9God::_d3dlight9.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	GgafDx9God::_d3dlight9.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	//下は平行光では関係ない
	//GgafDx9God::_d3dlight9.Position = D3DXVECTOR3(-1*GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)/2, -1*GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)/2, -1*GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)/2);
	//GgafDx9God::_d3dlight9.Range = 1000;
*/
	ZeroMemory(&_d3dlight9, sizeof(D3DLIGHT9) );
	GgafDx9God::_d3dlight9.Direction = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	GgafDx9God::_d3dlight9.Type = D3DLIGHT_DIRECTIONAL;
	GgafDx9God::_d3dlight9.Diffuse.r = 1.0f;
	GgafDx9God::_d3dlight9.Diffuse.g = 1.0f;
	GgafDx9God::_d3dlight9.Diffuse.b = 1.0f;
	GgafDx9God::_d3dlight9.Ambient.r = 0.0f; //アンビエントライトはSetRenderState(D3DRS_AMBIENT, 0x00303030)で設定
	GgafDx9God::_d3dlight9.Ambient.g = 0.0f;
	GgafDx9God::_d3dlight9.Ambient.b = 0.0f;
	//GgafDx9God::_d3dlight9.Range = 1000.0f;



	//ライトをセット
	GgafDx9God::_pID3DDevice9->SetLight( 0, &GgafDx9God::_d3dlight9 );
	//ライトスイッチON
	GgafDx9God::_pID3DDevice9->LightEnable( 0, TRUE );
	//レンダ時にライトの影響（陰影）を有効
	GgafDx9God::_pID3DDevice9->SetRenderState( D3DRS_LIGHTING, TRUE);
	//世界に共通のアンビエントライト
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, 0x00303030);

	// Zバッファを有効に
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	// Zバッファを無効に
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
	//Zバッファ書き込み可
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE );
	//Zバッファ書き込み不可
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
	//左（反時計回り）回りにカリング ∵左手座標系
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//カリングしない
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// アルファブレンドＯＮ
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// 色の算出方法の設定
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// ディザリングOFF
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DITHERENABLE, TRUE );
	// マルチサンプリングアンチエイリアスOFF
	GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);


	// テクスチャ処理方法の設定
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	// テクスチャと頂点色を乗算するように設定
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);




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

	//アンチエイリアスにかかわるレンダリングステート
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);
	//GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK,0x7fffffff);


	// ビュー変換（カメラ位置）設定
	double dCam = -1.0*(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)/PX_UNIT/2)/tan(PI/9);
	_TRACE_("カメラの位置(0,0,"<<dCam<<")");
	D3DXMATRIX matrixView;   // ビュー変換行列
	D3DXVECTOR3 vFromPt   = D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)dCam); //位置
	D3DXVECTOR3 vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //注視する方向
	D3DXVECTOR3 vUpVec    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //上方向
	D3DXMatrixLookAtLH(
				&matrixView,
				&vFromPt,
				&vLookatPt,
				&vUpVec
	);
	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_VIEW, &matrixView);


	// 射影変換（３Ｄ→平面）
	D3DXMATRIX matrixProjrction;   // 射影変換行列
	D3DXMatrixPerspectiveFovLH(
		&matrixProjrction,
		2.0*(PI/9),     //y方向視野角ラディアン(0～π)
		(FLOAT)(1.0 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)), //アスペクト比  640×480 の場合  640/480
		1.0,            //zn:カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0
		2000.0          //zf:カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn
		//(FLOAT)(-1.0*dCam*4)
		//(-1.0*fCam)-30,
		//(-1.0*fCam)+30
	);
/*
	//左手座標系正射影
	D3DXMatrixOrthoLH(
		&matrixProjrction,
		GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH),
		GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT),
		1.0f,
		GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)
	);
*/
	GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &matrixProjrction);

	//その他必要な初期化
	GgafDx9Util::init(); //ユーティリティ準備
	GgafDx9Input::init(); //DirectInput準備
	GgafDx9Sound::init(); //DirectSound準備
	return S_OK;
}


void GgafDx9God::makeWorldMaterialize() {
	TRACE("GgafDx9God::materialize() start");


	if (_deviceLostFlg) {
		//デバイスロスと復帰を試みる
		if (GgafDx9God::_pID3DDevice9->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			//復帰
			_TRACE_("デバイスロストから復帰処理！");
			//モデル開放
			GgafDx9ModelManager::onDeviceLostAll();
			HRESULT hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_structD3dPresent_Parameters));
			if ( hr != D3D_OK ) {
				throw_GgafCriticalException("GgafDx9God::visualize() デバイスロスト後のリセットでダメでした。");
			}
			//デバイス再設定
			initDx9Device();
			//モデル再設定
			GgafDx9ModelManager::restoreAll();
			//前回描画モデル情報を無効にする
			GgafDx9Model::_s_modelname_lastdraw = "";
			_deviceLostFlg = false;
		}
	}

	if (_deviceLostFlg != true) {
		//バッファクリア
		GgafDx9God::_pID3DDevice9 -> Clear(
										 0, // クリアする矩形領域の数
										 NULL, // 矩形領域
										 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
										 //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
										 D3DCOLOR_XRGB( 0, 0, 0 ), //背景黒にクリア
										 1.0f, // Zバッファのクリア値
										 0 // ステンシルバッファのクリア値
									 );

		//描画事前処理
		GgafDx9God::_pID3DDevice9->BeginScene();
		//全て具現化！（描画）
		GgafGod::makeWorldMaterialize(); //スーパーのmaterialize実行
		//描画事後処理
		GgafDx9God::_pID3DDevice9->EndScene();
	}
	TRACE("GgafDx9God::makeWorldMaterialize() end");
}

void GgafDx9God::makeWorldVisualize() {
	if (_deviceLostFlg != true) {
		//バックバッファをプライマリバッファに転送
		//if (GgafDx9God::_pID3DDevice9 -> Present(NULL,&_rectPresentDest,NULL,NULL) == D3DERR_DEVICELOST) {
		if (GgafDx9God::_pID3DDevice9 -> Present(NULL,NULL,NULL,NULL) == D3DERR_DEVICELOST) {
			//出刃異巣露酢斗！
			_TRACE_("デバイスロスト！");
			_deviceLostFlg = true;
		}
	}
}

GgafDx9God::~GgafDx9God() {
	TRACE("GgafDx9God::~GgafDx9God() start -->");

	::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
	Sleep(20);
	//工場掃除
	GgafFactory::_isWorking = false;
	GgafFactory::clean();
	::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
	//工場が落ち着くまで待つ
	while (GgafFactory::_isFinish == false) {
		Sleep(10);
	}

	CmRandomNumberGenerator::getInstance()->release();
	//保持モデル解放
	GgafDx9ModelManager::clear();
	//DirectInput解放
	GgafDx9Input::release();
	//DirectSound解放
	GgafDx9Sound::release();
	//デバイス解放
	_pID3DDevice9->Release();
	_pID3D9->Release();
	TRACE("GgafDx9God::~GgafDx9God() end <--");
}
