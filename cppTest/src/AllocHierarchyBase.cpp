#include "AllocHierarchyBase.h"

// v1.01
// ・スキン登録時にAddRefが呼ばれている事によるリークを改善


CAllocHierarchyBase::CAllocHierarchyBase(void)
{
}


// デストラクタ
CAllocHierarchyBase::~CAllocHierarchyBase(void)
{
	// 登録されたオブジェクトを全て削除する
	list<void*>::iterator it = m_DelList.begin();
	for(; it!=m_DelList.end(); it++)
		delete[] (*it);

	list<IUnknown*>::iterator comit = m_ReleaseList.begin();
	for(; comit!=m_ReleaseList.end();comit++){
		if(*comit)
			(*comit)->Release();
	}
}


// フレーム構造体を生成
D3DXFRAME* CAllocHierarchyBase::CreateNewFrame()
{
	D3DXFRAME* tmp = new D3DXFRAME;
	ZeroMemory( tmp, sizeof(D3DXFRAME) );
	AddDelList( tmp );
	return tmp;
}


// メッシュコンテナ構造体を生成
D3DXMESHCONTAINER *CAllocHierarchyBase::CreateNewMeshContainer()
{
	D3DXMESHCONTAINER* tmp = new D3DXMESHCONTAINER;
	ZeroMemory( tmp, sizeof(D3DXMESHCONTAINER) );
	AddDelList( tmp );
	return tmp;
}


// 消去リストに登録
void CAllocHierarchyBase::AddDelList( void* ptr )
{
	m_DelList.push_back( ptr );
}

// リリースリストに登録
void CAllocHierarchyBase::AddReleaseList( IUnknown *comptr)
{
	comptr->AddRef();
	m_ReleaseList.push_back( comptr );
}


// 文字列コピー関数
LPSTR CAllocHierarchyBase::CopyStr(LPCSTR name)
{
	if(!name) return NULL;   // NULLは文字数をカウントできない
	LPSTR Str = new char[strlen(name)+1];
	//strcpy_s(Str, strlen(name)+1, name);
	strcpy(Str, name);
	AddDelList( Str );
	return Str;
}


// メッシュデータ登録
void CAllocHierarchyBase::RegistMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest)
{
	pDest->Type = pSrc->Type;   // メッシュタイプ
	pDest->pMesh = pSrc->pMesh;   // メッシュ（unionなのでどれでも一緒）
	AddReleaseList( pDest->pMesh );  // Releaseリストへ登録
}


// マテリアル登録
void CAllocHierarchyBase::RegistMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **ppDest)
{
	// マテリアル配列の生成
	*ppDest = new D3DXMATERIAL[ num ];
	AddDelList( *ppDest );

	DWORD i;
	for(i=0; i<num; i++)
	{
		(*ppDest)[i].MatD3D = pSrc[i].MatD3D;   // マテリアル登録
		(*ppDest)[i].pTextureFilename = CopyStr( pSrc[i].pTextureFilename );  // テクスチャ名登録
	}
}


// エフェクト登録
void CAllocHierarchyBase::RegistEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest)
{
	*ppDest = new D3DXEFFECTINSTANCE;
	AddDelList( *ppDest );
	(*ppDest)->pEffectFilename = CopyStr(pSrc->pEffectFilename);     // エフェクト名
	(*ppDest)->NumDefaults = pSrc->NumDefaults;                      // エフェクトデフォルト数
	(*ppDest)->pDefaults = new D3DXEFFECTDEFAULT[pSrc->NumDefaults];  // エフェクトデフォルト配列生成
	AddDelList( (*ppDest)->pDefaults );

	// エフェクトデフォルトの登録
	D3DXEFFECTDEFAULT *pEDSrc  = pSrc->pDefaults;   // コピー元
	D3DXEFFECTDEFAULT *pEDDest = (*ppDest)->pDefaults; // コピー先
	unsigned int i=0;
	for(i=0; i<pSrc->NumDefaults; i++)
	{
	   pEDDest[i].pParamName = CopyStr(pEDSrc[i].pParamName);				// パラメータ名
	   DWORD NumBytes		 = pEDDest[i].NumBytes = pEDSrc[i].NumBytes;	// パラメータサイズ
	   pEDDest[i].Type		 = pEDSrc[i].Type;								// パラメータタイプ
	   if(pEDSrc[i].Type <= D3DXEDT_DWORD){
		  pEDDest[i].pValue = (void*)( new BYTE[ NumBytes ] );              // パラメータ配列生成
		  memcpy( pEDDest[i].pValue, pEDSrc[i].pValue, NumBytes );
		  AddDelList( pEDDest[i].pValue );
	   }
	}
}


// 隣接ポリゴン登録
void CAllocHierarchyBase::RegistAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest)
{
	*Dest = new DWORD[ polynum * 3 ];   // 配列生成
	memcpy( *Dest, Src, polynum * 3 * sizeof(DWORD));  // コピー
	AddDelList( *Dest );
}


// スキン登録
void CAllocHierarchyBase::RegistSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest)
{
	if(!Src) return;   // スキンが無ければ何もしない
	*Dest = Src;               // スキンをコピー
//	(*Dest)->AddRef();         // 参照カウンタ増加
	AddReleaseList( *Dest );   // リリースリストに登録
}


// フレーム生成関数
HRESULT CAllocHierarchyBase::CreateFrame(THIS_
   LPCSTR Name,
   LPD3DXFRAME *ppNewFrame)
{
	// フレームを新しく生成
	D3DXFRAME *pFrame = CreateNewFrame();
	pFrame->Name = CopyStr( Name );
	*ppNewFrame = pFrame;

	return D3D_OK;
}


// メッシュコンテナ生成関数
HRESULT CAllocHierarchyBase::CreateMeshContainer(THIS_
   LPCSTR Name,
   CONST D3DXMESHDATA *pMeshData,
   CONST D3DXMATERIAL *pMaterials,
   CONST D3DXEFFECTINSTANCE *pEffectInstances,
   DWORD NumMaterials,
   CONST DWORD *pAdjacency,
   LPD3DXSKININFO pSkinInfo,
   LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	// メッシュコンテナオブジェクトの生成
	D3DXMESHCONTAINER *p = CreateNewMeshContainer();

	// 名前登録
	p->Name = CopyStr( Name );

	// メッシュデータ登録
	RegistMeshData( pMeshData, &p->MeshData );

	// マテリアル登録
	p->NumMaterials = NumMaterials;
	RegistMaterial( pMaterials, NumMaterials, &p->pMaterials);

	// エフェクト登録
	RegistEffect( pEffectInstances, &p->pEffects );

	// 隣接ポリゴン登録
	RegistAdjacency( pAdjacency, pMeshData->pMesh->GetNumFaces(), &p->pAdjacency );

	// スキン登録
	RegistSkin( pSkinInfo, &p->pSkinInfo );

	*ppNewMeshContainer = p;

	return D3D_OK;
}


// フレームを削除
HRESULT CAllocHierarchyBase::DestroyFrame(THIS_
   LPD3DXFRAME pFrameToFree)
{
	// このクラスではデストラクタで削除されるので
	// この関数は使わない
	return D3D_OK;
}


// コンテナを削除
HRESULT CAllocHierarchyBase::DestroyMeshContainer(THIS_
   LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	// このクラスではデストラクタで削除されるので
	// この関数は使わない
	return D3D_OK;
}
