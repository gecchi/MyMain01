#ifndef GGAFDX9ALLOCHIERARCHY_H_
#define GGAFDX9ALLOCHIERARCHY_H_

namespace GgafDx9Core {

class GgafDx9AllocHierarchy : public ID3DXAllocateHierarchy
{
protected:
	// 削除人
	class deleterBase {
	public:
		virtual ~deleterBase() {}
	};

	template< class T >
	class deleter : public deleterBase {
	public:
		T* pObj;
		bool isAry;

		deleter( T* deletePtr, bool is_Ary = false ) : pObj(deletePtr), isAry( is_Ary ) {};
		virtual ~deleter(){
			if ( isAry )
				delete[] pObj;
			else
				delete pObj;
		}
	};

protected:
	list<deleterBase*> m_DelList;   // 消去リスト
	list<IUnknown*> m_ReleaseList;   // リリースリスト

public:
	GgafDx9AllocHierarchy(void);
	virtual ~GgafDx9AllocHierarchy(void);

	// フレームを生成する
	STDMETHOD(CreateFrame)(THIS_ 
		LPCSTR Name,
		LPD3DXFRAME *ppNewFrame
	);

	// コンテナを生成する
	STDMETHOD(CreateMeshContainer)(THIS_ 
		LPCSTR Name, 
		CONST D3DXMESHDATA *pMeshData, 
		CONST D3DXMATERIAL *pMaterials, 
		CONST D3DXEFFECTINSTANCE *pEffectInstances, 
		DWORD NumMaterials, 
		CONST DWORD *pAdjacency, 
		LPD3DXSKININFO pSkinInfo, 
		LPD3DXMESHCONTAINER *ppNewMeshContainer
	);

	// フレームを削除する
	STDMETHOD(DestroyFrame)(THIS_
		LPD3DXFRAME pFrameToFree
	);

	// コンテナを削除する
	STDMETHOD(DestroyMeshContainer)(THIS_
		LPD3DXMESHCONTAINER pMeshContainerToFree
	);


protected:
	// 消去リストに登録する
	virtual void AddDelList( deleterBase* ptr, bool isAry = false );

	// 文字列をコピーする
	virtual LPSTR CopyStr(LPCSTR name);

	// フレーム構造体を生成する
	virtual D3DXFRAME* CreateNewFrame();

	// メッシュコンテナ構造体を生成する
	virtual D3DXMESHCONTAINER* CreateNewMeshContainer();

	// メッシュデータを登録
	virtual void RegistMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest);

	// リリースリストに登録
	virtual void AddReleaseList( IUnknown *comptr);

	// マテリアル登録
	virtual void RegistMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **pDest);

	// エフェクト登録
	virtual void RegistEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest);

	// 隣接ポリゴン登録
	virtual void RegistAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest);

	// スキン登録
	virtual void RegistSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest);
};

}

#endif /*GGAFDX9ALLOCHIERARCHY_H_*/
