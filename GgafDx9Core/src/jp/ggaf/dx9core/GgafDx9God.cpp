#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;

HWND GgafDx9God::_hWnd = NULL;
HINSTANCE GgafDx9God::_hInstance = NULL;

IDirect3D9* GgafDx9God::_pID3D9 = NULL;
IDirect3DDevice9* GgafDx9God::_pID3DDevice9 = NULL;
D3DLIGHT9 GgafDx9God::_d3dlight9_default;
D3DLIGHT9 GgafDx9God::_d3dlight9_temp;
DWORD GgafDx9God::_dwAmbientBrightness_default = 0xff404040;

RECT GgafDx9God::_rectPresentDest;

double GgafDx9God::_dCamZ = 0;
double GgafDx9God::_dCamZ_ini = 0;
D3DXVECTOR3* GgafDx9God::_pVecCamFromPoint = NULL;
D3DXVECTOR3* GgafDx9God::_pVecCamLookatPoint = NULL;
D3DXVECTOR3* GgafDx9God::_pVecCamUp = NULL;
D3DXMATRIX GgafDx9God::_vMatrixView;
D3DXMATRIX GgafDx9God::_vMatrixProj;
D3DXMATRIX GgafDx9God::_vMatrixOrthoProj;

int GgafDx9God::_iPxDep = 0;
D3DFILLMODE GgafDx9God::_d3dfillmode = D3DFILL_SOLID;//D3DFILL_WIREFRAME;//D3DFILL_SOLID;

GgafDx9ModelManager* GgafDx9God::_pModelManager = NULL;
GgafDx9EffectManager* GgafDx9God::_pEffectManager = NULL;
//int const GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)  = 1024;
//int const GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) = 600;
D3DPRESENT_PARAMETERS GgafDx9God::_structD3dPresent_Parameters;
bool GgafDx9God::_deviceLostFlg = false;

GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND _hWnd) :
    GgafGod() {
    TRACE("GgafDx9God::GgafDx9God(HINSTANCE prm_hInstance, HWND prmGgafDx9God::_hWnd) ");
    GgafDx9God::_hWnd = _hWnd;
    GgafDx9God::_hInstance = prm_hInstance;
    _deviceLostFlg = false;
    CmRandomNumberGenerator::getInstance()->changeSeed(19740722UL); //19740722 は乱数のSeed
}

HRESULT GgafDx9God::init() {
    bool FULLSCRREEN = GGAFDX9_PROPERTY(FULL_SCREEN);
    _rectPresentDest.left = 0;
    _rectPresentDest.top = 0;
    _rectPresentDest.right = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH);
    _rectPresentDest.bottom = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT);

    HRESULT hr;

    //IDirect3D9コンポーネントの取得
    if (!(GgafDx9God::_pID3D9 = Direct3DCreate9(D3D_SDK_VERSION))) {
        throwGgafCriticalException("Direct3DCreate9 に失敗しました");
        return E_FAIL; //失敗
    }

    //デスプレイモードの取得
    D3DDISPLAYMODE structD3DDisplayMode; //結果が格納される構造体
    hr = GgafDx9God::_pID3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &structD3DDisplayMode);
    whetherGgafDx9CriticalException(hr, D3D_OK, "GetAdapterDisplayMode に失敗しました");

    //デバイス作成
    ZeroMemory(&_structD3dPresent_Parameters, sizeof(D3DPRESENT_PARAMETERS));
    //バックバッファの縦サイズ
    //_structD3dPresent_Parameters.BackBufferHeight = GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT);
    _structD3dPresent_Parameters.BackBufferHeight = GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT);
    //バックバッファの横サイズ
    //_structD3dPresent_Parameters.BackBufferWidth = GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH);
    _structD3dPresent_Parameters.BackBufferWidth = GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH);
    //バックバッファのフォーマット
    if (FULLSCRREEN) {
        _structD3dPresent_Parameters.BackBufferFormat = D3DFMT_X8R8G8B8;//D3DFMT_A8R8G8B8;//D3DFMT_X8R8G8B8; //D3DFMT_R5G6B5;	//フルスクリーン時
    } else {
        _structD3dPresent_Parameters.BackBufferFormat = structD3DDisplayMode.Format; //ウィンドウ時
    }
    //_structD3dPresent_Parameters.BackBufferFormat = D3DFMT_UNKNOWN;	//現在の画面モードを利用
    //バックバッファの数
    _structD3dPresent_Parameters.BackBufferCount = 1;

    //スワップ効果を指定する
    _structD3dPresent_Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
    //ウィンドウハンドル
    _structD3dPresent_Parameters.hDeviceWindow = NULL;
    //ウィンドウモード
    if (FULLSCRREEN) {
        _structD3dPresent_Parameters.Windowed = false; //フルスクリーン時
    } else {
        _structD3dPresent_Parameters.Windowed = true; //ウィンドウ時
    }
    //深度ステンシルバッファ
    //_structD3dPresent_Parameters.EnableAutoDepthStencil = FALSE;
    //_structD3dPresent_Parameters.AutoDepthStencilFormat = 0;
    _structD3dPresent_Parameters.EnableAutoDepthStencil = 1; //Z バッファの自動作成
    _structD3dPresent_Parameters.AutoDepthStencilFormat = D3DFMT_D16;
    //0にしておく
    _structD3dPresent_Parameters.Flags = 0;
    //フルスクリーンでのリフレッシュレート(ウィンドウモードなら0を指定)
    if (FULLSCRREEN) {
        _structD3dPresent_Parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT; //フルスクリーン時
    } else {
        _structD3dPresent_Parameters.FullScreen_RefreshRateInHz = 0; //ウィンドウ時
    }
    //スワップのタイミング
    if (FULLSCRREEN) {
        _structD3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
    } else {
        _structD3dPresent_Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; //即座(Windowモードはこちらが良いらしい）
    }

    //アンチアイリアスにできるかチェック
    DWORD qualityLevels = D3DMULTISAMPLE_NONE;
    D3DMULTISAMPLE_TYPE multiSampleType = D3DMULTISAMPLE_NONE;

    //	if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //		D3DADAPTER_DEFAULT,
    //		D3DDEVTYPE_HAL,
    //		D3DFMT_A8R8G8B8,
    //		FULLSCRREEN ? FALSE : TRUE,
    //		D3DMULTISAMPLE_2_SAMPLES,
    //		&qualityLevels) ) )
    //	{
    //		if( SUCCEEDED(GgafDx9God::_pID3D9->CheckDeviceMultiSampleType(
    //			D3DADAPTER_DEFAULT,
    //			D3DDEVTYPE_HAL,
    //			D3DFMT_D24S8,
    //			FULLSCRREEN ? FALSE : TRUE,
    //			D3DMULTISAMPLE_2_SAMPLES,
    //			NULL) ) )
    //		{
    //			multiSampleType = D3DMULTISAMPLE_2_SAMPLES;
    //			_TRACE_("MultiSampleType = D3DMULTISAMPLE_2_SAMPLES");
    //		}
    //	}
    //マルチサンプルの数
    _structD3dPresent_Parameters.MultiSampleType = multiSampleType;//D3DMULTISAMPLE_NONE;
    //マルチサンプルの品質レベル
    _structD3dPresent_Parameters.MultiSampleQuality = qualityLevels - (qualityLevels > 0 ? 1 : 0);

    //フルスクリーンに出来るか調べる
    if (FULLSCRREEN) {
        int cc = GgafDx9God::_pID3D9->GetAdapterModeCount(D3DADAPTER_DEFAULT,
                                                          _structD3dPresent_Parameters.BackBufferFormat);
        if (cc) {
            D3DDISPLAYMODE adp;
            for (int i = 0; i < cc; i++) {
                GgafDx9God::_pID3D9->EnumAdapterModes(D3DADAPTER_DEFAULT,
                                                      _structD3dPresent_Parameters.BackBufferFormat, i, &adp);
                if (adp.Format == _structD3dPresent_Parameters.BackBufferFormat && adp.Width == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH) && adp.Height == (UINT)GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT)) {
                    //OK
                    break;
                }
                if (cc == i) {
                    //要求した使える解像度が見つからない
                    throwGgafCriticalException(GGAFDX9_PROPERTY(VIEW_SCREEN_WIDTH) <<"x"<<GGAFDX9_PROPERTY(VIEW_SCREEN_HEIGHT) << "のフルスクリーンモードにする事ができません。");
                    return E_FAIL;
                }
            }
        } else {
            throwGgafCriticalException("GetAdapterModeCount に失敗しました");
            return E_FAIL;
        }
    }


    //デバイス作成を試み GgafDx9God::_pID3DDevice9 へ設定する。
    //ハードウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。HAL(pure vp)
    hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_hWnd,
                                           D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                           &_structD3dPresent_Parameters, &GgafDx9God::_pID3DDevice9);
    if (hr != D3D_OK) {
        //ソフトウェアによる頂点処理、ハードウェアによるラスタライズを行うデバイス作成を試みる。HAL(soft vp)
        hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, GgafDx9God::_hWnd,
                                               D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                               &_structD3dPresent_Parameters, &GgafDx9God::_pID3DDevice9);
        if (hr != D3D_OK) {

			//ソフトウェアによる頂点処理、ラスタライズを行うデバイス作成を試みる。REF
            hr = GgafDx9God::_pID3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GgafDx9God::_hWnd,
                                                   D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED,
                                                   &_structD3dPresent_Parameters, &GgafDx9God::_pID3DDevice9);

			if (hr != D3D_OK) {
                //どのデバイスの作成も失敗した場合
                MessageBox(GgafDx9God::_hWnd, TEXT("Direct3Dの初期化に失敗"), TEXT("ERROR"), MB_OK | MB_ICONSTOP);
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

    //ピクセルシェーダー、頂点シェーダーバージョンチェック
    D3DCAPS9 caps;
    GgafDx9God::_pID3D9->GetDeviceCaps( D3DADAPTER_DEFAULT, // [in] ディスプレイ アダプタを示す序数。
                                                            //      D3DADAPTER_DEFAULT は常に
                                                            //      プライマリ ディスプレイ アダプタ
                                        D3DDEVTYPE_HAL,     // [in] デバイスの種類。 D3DDEVTYPE列挙型のメンバ
                                        &caps );            // [out] デバイスの能力が格納される

    DWORD vs_v = caps.VertexShaderVersion;
    DWORD ps_v = caps.PixelShaderVersion;
    _TRACE_("Hardware Vertex Shader Version = "<<D3DSHADER_VERSION_MAJOR(vs_v)<<"_"<<D3DSHADER_VERSION_MINOR(vs_v));
    _TRACE_("Hardware Pixel Shader Version  = "<<D3DSHADER_VERSION_MAJOR(ps_v)<<"_"<<D3DSHADER_VERSION_MINOR(ps_v));
    if( vs_v < D3DVS_VERSION(2, 0) || ps_v < D3DPS_VERSION(2, 0)) {
        _TRACE_("ビデオカードハードの頂点シェーダーとピンクセルシェーダーは、共にバージョン 2_0 以上でなければいけません。");
        _TRACE_("ご使用のビデオカードでは、正しく動作しない恐れがあります。");
    }

    //その他必要な初期化
    _pModelManager = NEW GgafDx9ModelManager("ModelManager");
    _pEffectManager = NEW GgafDx9EffectManager("EffectManager");
    GgafDx9Util::init(); //ユーティリティ準備
    GgafDx9Input::init(); //DirectInput準備
    GgafDx9Sound::init(); //DirectSound準備

    return initDx9Device();

}

HRESULT GgafDx9God::initDx9Device() {
    // デフォルトのライト
    /*
     ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9) );
     GgafDx9God::_d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL; //平行光、色と方向だけでよい
     GgafDx9God::_d3dlight9_default.Direction = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
     GgafDx9God::_d3dlight9_default.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
     GgafDx9God::_d3dlight9_default.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
     //下は平行光では関係ない
     //GgafDx9God::_d3dlight9_default.Position = D3DXVECTOR3(-1*GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)/2, -1*GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)/2, -1*GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)/2);
     //GgafDx9God::_d3dlight9_default.Range = 1000;
     */
    D3DXVECTOR3 vecDirection(-1.0f, -1.0f, 1.0f);
    D3DXVec3Normalize( &vecDirection, &vecDirection);
    ZeroMemory(&_d3dlight9_default, sizeof(D3DLIGHT9));
    GgafDx9God::_d3dlight9_default.Direction = vecDirection;
    GgafDx9God::_d3dlight9_default.Type = D3DLIGHT_DIRECTIONAL;
    GgafDx9God::_d3dlight9_default.Diffuse.a = 1.0f;
    GgafDx9God::_d3dlight9_default.Diffuse.r = 1.0f;
    GgafDx9God::_d3dlight9_default.Diffuse.g = 1.0f;
    GgafDx9God::_d3dlight9_default.Diffuse.b = 1.0f;

    GgafDx9God::_d3dlight9_default.Ambient.a = 1.0f;
    GgafDx9God::_d3dlight9_default.Ambient.r = 0.3f; //アンビエントライトはSetRenderState(D3DRS_AMBIENT, 0x00303030)で設定
    GgafDx9God::_d3dlight9_default.Ambient.g = 0.3f;
    GgafDx9God::_d3dlight9_default.Ambient.b = 0.3f;
    //GgafDx9God::_d3dlight9_default.Range = 1000.0f;


    //ライトをセット
    GgafDx9God::_pID3DDevice9->SetLight(0, &GgafDx9God::_d3dlight9_default);
    //ライトスイッチON
    GgafDx9God::_pID3DDevice9->LightEnable(0, TRUE);
    //レンダ時にライトの影響（陰影）を有効
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_LIGHTING, TRUE);
    //レンダ時、世界に共通のアンビエントライトを有効にしたように描く
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENT, _dwAmbientBrightness_default);

    // Zバッファを有効に
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
    // Zバッファを無効に
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
    //Zバッファ書き込み可
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
    //Zバッファ書き込み不可
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ZWRITEENABLE, FALSE );
    //左（反時計回り）回りにカリング ∵左手座標系
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    //カリングしない
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    // ディザリング
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DITHERENABLE, TRUE );
    // マルチサンプリングアンチエイリアス(といってもフルスクリーンだけ？)
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK, 0x00ffffff);

    // アルファブレンドＯＮ
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    //ピクセル単位のアルファテストを有効
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

    //2段階目、半透明テクスチャを貼り付けたポリゴンとバックバッファ（レンダーターゲット）との合成
    //色の算出方法の設定
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD); //D3DBLENDOP_ADD=転送元に転送先が加算
    //合成係数
    //上に書く画像の合成法
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); //SRC,D3DBLEND_SRCALPHA=普通に描く。ポリゴンのアルファ値の濃さで描く。アルファ値の値が高ければ高いほど、濃く描く。
    //下地の画像の合成法
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA); //DIST,D3DBLEND_INVSRCALPHA=上に描くポリゴンのアルファ値の濃さによって、下地の描画を薄くする。




    //頂点カラーを無効にする
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_COLORVERTEX, FALSE );
    //面のアンビエント反射は、マテリアルを参照するように設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);
    //面のデフューズ反射は、マテリアルを参照するように設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
    //面のエミッシブ反射は、マテリアルを参照する設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);
    //面のスペキュラ反射は、マテリアルを参照する設定する。（頂点カラーを参照する場合は D3DMCS_COLOR1)
    GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

    //頂点αを使用するとき
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE , D3DMCS_COLOR1);

   //
    //
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

    //2009/3/4 SetSamplerStateの意味が今ごろわかった。
    //SetSamplerStateはテクスチャからどうサンプリング（読み取るか）するかの設定。
    //だからアンチエイリアスつっても、テクスチャしかアンチエイリアスがかかりません。
    //多分s0レジスタをなんやら設定するのだろう。
    //今後ピクセルシェーダーで全部設定するので、このあたりの設定は、将来全部いらなくなるはずだ。


    //アンチエイリアスにかかわるレンダリングステート
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);
    //GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_MULTISAMPLEMASK,0x7fffffff);

    //SetTextureStageStateは廃止？
    //  1段階目ポリゴンとテクスチャの合成方法設定
    //    //テクスチャーの色と、頂点カラーのDIFFUSE色を乗算するように設定
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
    //    //テクスチャーのαと、頂点カラーのαを乗算するように設定
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
    //    GgafDx9God::_pID3DDevice9->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);



    // VIEW変換（カメラ位置）設定
    _dCamZ = -1.0 * (GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT) / PX_UNIT / 2.0) / tan(PI / 9);
    _dCamZ_ini = _dCamZ;
    _iPxDep = abs(_dCamZ_ini * PX_UNIT * 2);

    _TRACE_("カメラの位置(0,0,"<<_dCamZ<<")");
    //D3DXMATRIX _vMatrixView; // ビュー変換行列

    DELETE_POSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_POSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_POSSIBLE_NULL(_pVecCamUp);
    _pVecCamFromPoint = NEW D3DXVECTOR3( 0.0f, 0.0f, (FLOAT)_dCamZ); //位置
    _pVecCamLookatPoint = NEW D3DXVECTOR3( 0.0f, 0.0f, 0.0f ); //注視する方向
    _pVecCamUp = NEW D3DXVECTOR3( 0.0f, 1.0f, 0.0f ); //上方向
    updateCam();

    // 射影変換（３Ｄ→平面）
    //D3DXMATRIX _vMatrixProj; // 射影変換行列
    D3DXMatrixPerspectiveFovLH(
            &_vMatrixProj,
            2.0*(PI/9), //y方向視野角ラディアン(0～π)
            (FLOAT)(1.0 * GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH) / GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)), //アスペクト比  640×480 の場合  640/480
            1.0, //zn:カメラから近くのクリップ面までの距離(どこからの距離が表示対象か）≠0
            2000.0 //zf:カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn
            //(FLOAT)(-1.0*dCam*4)
            //(-1.0*fCam)-30,
            //(-1.0*fCam)+30
    );
    /*
     //左手座標系正射影
     D3DXMatrixOrthoLH(
     &_vMatrixProj,
     GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH),
     GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT),
     1.0f,
     GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)
     );
     */


    //GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_PROJECTION, &_vMatrixProj);

    D3DXMatrixOrthoLH(
        &_vMatrixOrthoProj,
        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_WIDTH)) ,    //w ビュー ボリュームの幅
        (FLOAT)(GGAFDX9_PROPERTY(GAME_SCREEN_HEIGHT)) ,   //h ビュー ボリュームの高さ
        1.0,    //zn ビュー ボリュームの最小 z 値 (z 近ともいう)
        2000.0  //zf ビュー ボリュームの最大 z 値 (z 遠ともいう)
    );



    return S_OK;
}

void GgafDx9God::updateCam() {
    D3DXMatrixLookAtLH(&_vMatrixView, _pVecCamFromPoint, _pVecCamLookatPoint, _pVecCamUp);
    //GgafDx9God::_pID3DDevice9->SetTransform(D3DTS_VIEW, &_vMatrixView);
}

// カメラと対峙する回転行列を取得
// ビルボードのVIEW変換行列を取得
D3DXMATRIX GgafDx9God::getInvRotateMat() {
    D3DXMATRIX Inv;
    //   D3DXMatrixIdentity(&Inv);
    //   D3DXMatrixLookAtLH(&Inv, &D3DXVECTOR3(0,0,0), &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ), &D3DXVECTOR3( 0.0f, 1.0f, 0.0f ));
    //   D3DXMatrixInverse(&Inv, NULL, &Inv);

    return Inv;
}

void GgafDx9God::makeWorldMaterialize() {
    TRACE("GgafDx9God::materialize() start");

    //カメラ設定
    updateCam();
    HRESULT hr;
    if (_deviceLostFlg) {
        //正常デバイスロスト処理。デバイスリソースの解放→復帰処理を試みる。
        if (GgafDx9God::_pID3DDevice9->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
            //工場休止
            GgafFactory::beginRest();
         ___EndSynchronized; // <----- 排他終了
            while (GgafFactory::isResting() == false) { //工場が落ち着くまで待つ
                Sleep(10);
            }
         ___BeginSynchronized; // ----->排他開始
            _TRACE_("正常デバイスロスト処理。Begin");
            //エフェクト、デバイスロスト処理
            GgafDx9God::_pEffectManager->onDeviceLostAll();
            //モデル解放
            GgafDx9God::_pModelManager->onDeviceLostAll();
            //全ノードに解放しなさいイベント発令
            getWorld()->happen(GGAF_EVENT_ON_DEVICE_LOST);

            //デバイスリセットを試みる
            hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_structD3dPresent_Parameters));
            whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9God::makeWorldMaterialize() デバイスロスト後のリセットでに失敗しました。");

            //デバイス再設定
            GgafDx9God::initDx9Device();
            //エフェクトリセット
            GgafDx9God::_pEffectManager->restoreAll();
            //モデル再設定
            GgafDx9God::_pModelManager->restoreAll();
            //全ノードに再設定しなさいイベント発令
            getWorld()->happen(GGAF_EVENT_DEVICE_LOST_RESTORE);
            //前回描画モデル情報を無効にする
            GgafDx9God::_pModelManager->_id_lastdraw = -1;
            _deviceLostFlg = false;

            //工場再開
            GgafFactory::finishRest();
            _TRACE_("正常デバイスロスト処理。End");
        }
    }

    if (_deviceLostFlg != true) {
        //バッファクリア
        hr = GgafDx9God::_pID3DDevice9->Clear(0, // クリアする矩形領域の数
                                              NULL, // 矩形領域
                                              D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, // レンダリングターゲットと深度バッファをクリア
                                              //D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, // レンダリングターゲットと深度バッファをクリア
                                              D3DCOLOR_XRGB( 0, 0, 0 ), //背景黒にクリア
                                              1.0f, // Zバッファのクリア値
                                              0 // ステンシルバッファのクリア値
                );
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->Clear() に失敗しました。");

        //描画事前処理
        hr = GgafDx9God::_pID3DDevice9->BeginScene();
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->BeginScene() に失敗しました。");
        //全て具現化！（描画）
        GgafDx9God::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDx9God::_d3dfillmode);
        GgafGod::makeWorldMaterialize(); //スーパーのmaterialize実行
        //描画事後処理
        hr = GgafDx9God::_pID3DDevice9->EndScene();
        whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9God::_pID3DDevice9->EndScene() に失敗しました。");

    }
    TRACE("GgafDx9God::makeWorldMaterialize() end");
}

void GgafDx9God::makeWorldVisualize() {
    if (_deviceLostFlg != true) {
        //バックバッファをプライマリバッファに転送
        //if (GgafDx9God::_pID3DDevice9->Present(NULL,&_rectPresentDest,NULL,NULL) == D3DERR_DEVICELOST) {

        HRESULT hr = GgafDx9God::_pID3DDevice9->Present(NULL, NULL, NULL, NULL);

        if (hr == D3DERR_DEVICELOST) {
            //出刃異巣露酢斗！
            _TRACE_("通常デバイスロスト！Present()");
            _deviceLostFlg = true;
        } else if (hr == D3DERR_DRIVERINTERNALERROR) {
            //Present以上時、無駄かもしれないがデバイスロストと同じ処理を試みる。
            _TRACE_("Present() == D3DERR_DRIVERINTERNALERROR!! Reset()を試みます。（駄目かもしれません）");
            //工場休止
            GgafFactory::beginRest();
         ___EndSynchronized; // <----- 排他終了
            while (GgafFactory::isResting() == false) { //工場が落ち着くまで待つ
                Sleep(10);
            }
         ___BeginSynchronized; // ----->排他開始
            _TRACE_("D3DERR_DRIVERINTERNALERROR！ 処理Begin");
            //エフェクト、デバイスロスト処理
            GgafDx9God::_pEffectManager->onDeviceLostAll();
            //モデル解放
            GgafDx9God::_pModelManager->onDeviceLostAll();
            //全ノードに解放しなさいイベント発令
            getWorld()->happen(GGAF_EVENT_ON_DEVICE_LOST);
            //デバイスリセットを試みる
            hr = GgafDx9God::_pID3DDevice9->Reset(&(GgafDx9God::_structD3dPresent_Parameters));
            whetherGgafDx9CriticalException(hr, D3D_OK, "GgafDx9God::makeWorldMaterialize() D3DERR_DRIVERINTERNALERROR のため Reset() を試しましが、駄目でした。");
            //デバイス再設定
            GgafDx9God::initDx9Device();
            //エフェクトリセット
            GgafDx9God::_pEffectManager->restoreAll();
            //モデル再設定
            GgafDx9God::_pModelManager->restoreAll();
            //全ノードに再設定しなさいイベント発令
            getWorld()->happen(GGAF_EVENT_DEVICE_LOST_RESTORE);
            //前回描画モデル情報を無効にする
            GgafDx9God::_pModelManager->_id_lastdraw = -1;

            //工場再開
            GgafFactory::finishRest();
            _TRACE_("D3DERR_DRIVERINTERNALERROR！ 処理End");
        }
    }
}

GgafDx9God::~GgafDx9God() {
    _TRACE_("GgafDx9God::~GgafDx9God() start -->");
    if (_pWorld != NULL) {
        //工場を止める
        Sleep(20);
        GgafFactory::_isWorkingFlg = false;
        while (GgafFactory::_isFinishFlg == false) {
            Sleep(10); //工場が落ち着くまで待つ
        }

        //工場掃除
     ___BeginSynchronized; // ----->排他開始
        GgafFactory::clean();
        //ゴミ箱
        GgafFactory::_pGarbageBox->_pGarbageRootScene->dump();
        GgafFactory::_pGarbageBox->_pGarbageRootActor->dump();
        DELETE_IMPOSSIBLE_NULL(GgafFactory::_pGarbageBox);
     ___EndSynchronized; // <----- 排他終了

        //世界で生きている物も掃除
        Sleep(20);
     ___BeginSynchronized; // ----->排他開始
        DELETE_IMPOSSIBLE_NULL(_pWorld);
     ___EndSynchronized; // <----- 排他終了
    }
    //いろいろ解放
    DELETE_IMPOSSIBLE_NULL(_pVecCamFromPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamLookatPoint);
    DELETE_IMPOSSIBLE_NULL(_pVecCamUp);

    CmRandomNumberGenerator::getInstance()->release();
    //保持モデル解放
    DELETE_IMPOSSIBLE_NULL(_pModelManager);
    DELETE_IMPOSSIBLE_NULL(_pEffectManager);
    //DirectInput解放
    GgafDx9Input::release();
    //DirectSound解放
    GgafDx9Sound::release();
    //デバイス解放
    RELEASE_IMPOSSIBLE_NULL(_pID3DDevice9);
    RELEASE_IMPOSSIBLE_NULL(_pID3D9);
    _TRACE_("GgafDx9God::~GgafDx9God() end <--");
}
