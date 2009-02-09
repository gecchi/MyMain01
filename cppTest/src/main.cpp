// ディフューズシェーダテストプログラム

#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib" )

#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>

TCHAR gName[100] = _T("ディフューズシェーダテストプログラム");
D3DXVECTOR2 g_Def = D3DXVECTOR2( 0, 0 );
D3DXVECTOR2 g_ClickPos = D3DXVECTOR2( 0, 0 );
D3DXVECTOR2 g_RotAngle = D3DXVECTOR2( 0, 0 );
bool isClick = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
   if(mes == WM_DESTROY) {PostQuitMessage(0); return 0;}

   if(mes == WM_LBUTTONDOWN ) {
	   isClick = true;
	   g_Def.x = g_Def.y = 0;
	   g_ClickPos.x = LOWORD( lParam );	   g_ClickPos.y = HIWORD( lParam );
   }
   if(mes == WM_LBUTTONUP ) {
	   isClick = false;
	   g_Def.x = g_Def.y = 0;
   }
   if(mes == WM_MOUSEMOVE && isClick == true ) {
	   D3DXVECTOR2 CurPos( LOWORD( lParam ), HIWORD( lParam ) );
	   g_Def = CurPos - g_ClickPos;
	   g_RotAngle += g_Def;
	   g_ClickPos = CurPos;
   }

   return DefWindowProc(hWnd, mes, wParam, lParam);
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
   MSG msg; HWND hWnd;
   WNDCLASSEX wcex ={sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, NULL, NULL,
                                  (HBRUSH)(COLOR_WINDOW+1), NULL, (TCHAR*)gName, NULL};
   if(!RegisterClassEx(&wcex)) return 0;

   if(!(hWnd = CreateWindow(gName, gName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
         NULL, NULL, hInstance, NULL)))
      return 0;

   // Direct3Dの初期化
   LPDIRECT3D9 g_pD3D;
   LPDIRECT3DDEVICE9 g_pD3DDev;
   if( !(g_pD3D = Direct3DCreate9( D3D_SDK_VERSION )) ) return 0;

	D3DPRESENT_PARAMETERS d3dpp = {0,0,D3DFMT_A8R8G8B8,0,D3DMULTISAMPLE_NONE,0,
         D3DSWAPEFFECT_DISCARD,NULL,TRUE,TRUE,D3DFMT_D24S8,0,D3DPRESENT_RATE_DEFAULT,D3DPRESENT_INTERVAL_DEFAULT};

	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev ) ) ) {
		if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev ) ) ) {
			g_pD3D->Release(); return 0;
		}
	}

   // モデル読み込み
	ID3DXBuffer *pMaterials = 0;
	DWORD NumMaterials = 0;
	ID3DXMesh *pMesh = 0;

	HRESULT hr = D3DXLoadMeshFromX(
		_T("sphere.x"),
		D3DXMESH_MANAGED,
		g_pD3DDev,
		NULL,
		&pMaterials,
		NULL,
		&NumMaterials,
		&pMesh
	);

	if( FAILED(hr) )
	return 0;

   // テクスチャ生成
   IDirect3DTexture9 *pTex0 = 0;
	D3DXCreateTextureFromFile( g_pD3DDev, _T("earth_diffuse.dds"), &pTex0 );

	D3DXMATRIX View, Persp, World;

	// ビュー変換
	D3DXMatrixLookAtLH(
		  &View,
		  &D3DXVECTOR3(0, 0, -4),
		  &D3DXVECTOR3(0, 0, 0),
		  &D3DXVECTOR3(0, 1, 0)
		  );

	ID3DXEffect *pEffect = 0;
	ID3DXBuffer *pError = 0;
	if ( FAILED( D3DXCreateEffectFromFile(
	               g_pD3DDev,
	               _T("diffuse.fx"),
	               0,
	               0,
	               0,
	               0,
	               &pEffect,
	               &pError
	             )
	           )
	   ) {
		if ( pError ) {
			OutputDebugStringA( (const char*)pError->GetBufferPointer() );
			OutputDebugStringA( "\n" );
		}
		else
			OutputDebugStringA( "なんかエフェクト読み込みでエラー出たよ。\n" );
		return 0;
	}

	// 射影変換
	D3DXMatrixPerspectiveFovLH( &Persp, D3DXToRadian(45), 640.0f/480.0f, 1.0f, 10000.0f );

   ShowWindow(hWnd, nCmdShow);

   // メッセージ ループ
   float val = 0.0f;
   do{
      Sleep(1);
      if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ){ DispatchMessage(&msg);}
      else{
		  val += 0.01;
               // Direct3Dの処理
               g_pD3DDev->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(20,40,200), 1.0f, 0 );
               g_pD3DDev->BeginScene();

			   // 行列更新
			   D3DXMATRIX Rot_x, Rot_y;
			   D3DXMatrixRotationY( &Rot_y, -g_RotAngle.x * 0.01f );
			   D3DXMatrixRotationX( &Rot_x, -g_RotAngle.y * 0.01f );
			   World = Rot_y * Rot_x;

			   // ライトと視線方向を設定
			   D3DXVECTOR3 LightVec( cos(val), -0.5, sin(val) );
			   D3DXVec3TransformNormal( &LightVec, &LightVec, &View );

			   // エフェクト設定
			   D3DXMATRIX worldView = World * View;
			   pEffect->SetMatrix( "g_worldView", &worldView );
			   pEffect->SetMatrix( "g_viewMat", &View );
			   pEffect->SetMatrix( "g_projMat", &Persp );
			   pEffect->SetTexture( "g_diffuseMap", pTex0 );
			   pEffect->SetVector( "g_LD", &D3DXVECTOR4(LightVec, 0.0f) );
			   pEffect->SetVector( "g_LC", &D3DXVECTOR4( 1, 1, 1, 1 ) );

			   // 描画
			   pEffect->SetTechnique( "Diffuse" );
			   UINT numPass;
				pEffect->Begin( &numPass, 0 );
				pEffect->BeginPass( 0 );

                  // 描画
			   for( unsigned int i = 0; i < NumMaterials; i++ ) {
				   D3DXMATERIAL *pMat = (D3DXMATERIAL*)pMaterials->GetBufferPointer();
				   g_pD3DDev->SetMaterial( &pMat->MatD3D );
				   pMesh->DrawSubset( i );
			   }

				pEffect->EndPass();
				pEffect->End();

			   g_pD3DDev->EndScene();
               g_pD3DDev->Present( NULL, NULL, NULL, NULL );
            }
   } while(msg.message != WM_QUIT);

   pEffect->Release();
   pMesh->Release();
   pMaterials->Release();
   pTex0->Release();
   g_pD3DDev->Release();
   g_pD3D->Release();

   return 0;
}
