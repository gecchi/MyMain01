// 固定アニメーションテストサンプルプログラム

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <windows.h>
#include <tchar.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "AllocHierWorldFrame.h"
#include "WorldTransMatStack.h"

using namespace std;

TCHAR gName[100] = "固定アニメーションテストサンプルプログラム";
TCHAR Filename[128] = "CubeAndSphere1.x";

LRESULT CALLBACK WndProc(HWND hWnd, UINT mes, WPARAM wParam, LPARAM lParam){
   if(mes == WM_DESTROY) {PostQuitMessage(0); return 0;}
   return DefWindowProc(hWnd, mes, wParam, lParam);
}

int main(int argc,char *argv[]) {
	STARTUPINFO	StatUpInfo;
	HINSTANCE		hInstance;
	HANDLE		hPrevInstance;
	LPSTR		lpCmdLine;
	int			nCmdShow;
	//WNDCLASS	wc;
	HWND		hWnd;
//	MSG			msg;

	GetStartupInfo(&StatUpInfo);
	hInstance = GetModuleHandle(0);
	hPrevInstance = 0;
	lpCmdLine = GetCommandLine();
	nCmdShow = (StatUpInfo.dwFlags & STARTF_USESHOWWINDOW)?
				StatUpInfo.wShowWindow:SW_SHOWNORMAL;
	/* GetCommandLineからプログラム名を抜きます。 */
	while(*lpCmdLine != ' ' && *lpCmdLine != '\0') lpCmdLine++;
	while(*lpCmdLine == ' ') lpCmdLine++;

	/* ここからが、本来の処理 */
	//wc.lpszClassName = "MySTG2nd";
	/* 二重起動防止 (バグあり...)*/
//	if((hWnd=FindWindow(WINDOW_CLASS, NULL))!=0) {
//		if (IsIconic(hWnd)) {
//			ShowWindow(hWnd, SW_RESTORE);
//		}
//		SetForegroundWindow(hWnd);
//		return 0;
//	}

	//本来のWinMainへ
	WinMain((HINSTANCE)hInstance, (HINSTANCE)hPrevInstance, lpCmdLine, nCmdShow);
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
   // アプリケーションの初期化
   MSG msg; HWND hWnd;
   WNDCLASSEX wcex ={sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance, NULL, NULL,
                                    (HBRUSH)(COLOR_WINDOW+1), NULL, (TCHAR*)gName, NULL};
   if(!RegisterClassEx(&wcex)) {
      //return 0;
   }

   if(!(hWnd = CreateWindow(gName, gName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800,600,
                                    NULL, NULL, hInstance, NULL))) {
      //return 0;
   }

   // Direct3Dの初期化
   LPDIRECT3D9 g_pD3D;
   LPDIRECT3DDEVICE9 g_pD3DDev;
   if( !(g_pD3D = Direct3DCreate9( D3D_SDK_VERSION )) ) return 0;

   D3DPRESENT_PARAMETERS d3dpp = {0,0,D3DFMT_UNKNOWN,0,D3DMULTISAMPLE_NONE,0,
                                  D3DSWAPEFFECT_DISCARD,NULL,TRUE,TRUE,D3DFMT_D24S8,0,D3DPRESENT_RATE_DEFAULT,D3DPRESENT_INTERVAL_DEFAULT};

   if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev ) ) )
   if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDev ) ) )
   {
      g_pD3D->Release();
      return 0;
   }

   // メッシュオブジェクトの読み込み
   CAllocHierWorldFrame AH;         // CAllocHierarchyBaseの派生クラス
   D3DXFRAME_WORLD* pFR;            // ワールド変換行列付きフレーム構造体
   ID3DXAnimationController* pAC;   // アニメーションコントローラ
   if(FAILED(D3DXLoadMeshHierarchyFromX(
		           Filename,
		           D3DXMESH_MANAGED,
		           g_pD3DDev,
		           &AH,
		           NULL,
		           (D3DXFRAME**)(&pFR),
		           &pAC))){
      g_pD3DDev->Release(); g_pD3D->Release();
      return 0;
   }

   // ビュー変換
   D3DXMATRIX View;
   D3DXMatrixLookAtLH(
      &View,
      &D3DXVECTOR3(4.0f, 3.0f, 2.0f),
      &D3DXVECTOR3(0.0f, 0.0f, 0.0f),
      &D3DXVECTOR3( 0.0f, 1.0f, 0.0f)
     );

   // 射影変換
   D3DXMATRIX Persp;
   D3DXMatrixPerspectiveFovLH( &Persp, D3DXToRadian(45), 640.0f/480.0f, 1.0f, 10000.0f);

   // 行列登録
   g_pD3DDev->SetTransform(D3DTS_VIEW, &View);
   g_pD3DDev->SetTransform(D3DTS_PROJECTION, &Persp);

   // ライト
   D3DLIGHT9 light;
   ZeroMemory(&light, sizeof(D3DLIGHT9) );
   light.Direction = D3DXVECTOR3(-1, -1, -1);
   light.Type = D3DLIGHT_DIRECTIONAL;
   light.Diffuse.r = 0.8f;
   light.Diffuse.g = 0.8f;
   light.Diffuse.b = 0.8f;
   g_pD3DDev->SetLight( 0, &light );
   g_pD3DDev->LightEnable( 0, true );
   g_pD3DDev->SetRenderState( D3DRS_LIGHTING, TRUE );

   ShowWindow(hWnd, nCmdShow);

   // メッセージループ
   CWorldTransMatStack WTMStack;
   list< D3DXFRAME_WORLD* > *pDrawList;
   D3DXMATRIX WorldMat, Rot;

   pAC->SetTrackSpeed(0, 1000.0f);   // アニメーションスピードを調整
   FLOAT Ang = 0.0f;

   do{
      Sleep(1);
      if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) ){ DispatchMessage(&msg);}

        // アニメーションをフレーム分進める
        pAC->AdvanceTime( 6.0f, NULL );
        //pAC->SetTime(pAnimationSet->GetPeriod()+6.0f )SDKが古い
         // ワールド変換行列スタックによるワールド変換行列の計算
         Ang += 0.004f;
         D3DXMatrixIdentity( &WorldMat );
         D3DXMatrixRotationYawPitchRoll( &Rot, Ang, Ang/2.37f, 0);
         D3DXMatrixMultiply( &WorldMat, &WorldMat, &Rot );
         WTMStack.SetWorldMatrix( &WorldMat );

         // フレームのワールド変換行列を計算
         WTMStack.UpdateFrame( pFR );

         // 描画プロセス
         g_pD3DDev->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(40,40,80), 1.0f, 0 );
         g_pD3DDev->BeginScene();

            pDrawList = WTMStack.GetDrawList();              // 描画リストを取得

            list< D3DXFRAME_WORLD* >::iterator it = pDrawList->begin();
            int materialnum;
            int i;
            for( ; it!=pDrawList->end(); it++)
            {
               g_pD3DDev->SetTransform( D3DTS_WORLD, &(*it)->WorldTransMatrix );   // ワールド変換行列を設定
               materialnum = (*it)->pMeshContainer->NumMaterials;
               for(i=0; i<materialnum; i++)
               {
                  g_pD3DDev->SetMaterial( &(*it)->pMeshContainer->pMaterials[i].MatD3D );
                  (*it)->pMeshContainer->MeshData.pMesh->DrawSubset(i);
               }
            }

         g_pD3DDev->EndScene();
         g_pD3DDev->Present( NULL, NULL, NULL, NULL );
   }while(msg.message != WM_QUIT);

   pAC->Release();
   g_pD3DDev->Release();
   g_pD3D->Release();

   return 0;
}
