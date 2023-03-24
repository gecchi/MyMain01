#ifndef GGAF_DX_ALLOCHIERARCHY_H_
#define GGAF_DX_ALLOCHIERARCHY_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include <list>

#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 * ID3DXAllocateHierarchy実装クラス .
 */
class AllocHierarchy : public ID3DXAllocateHierarchy
{
protected:
//    class DeleterBase {
//    public:
//        virtual ~DeleterBase() {}
//    };
//
//    template< class T >
//    class Deleter : public DeleterBase {
//    public:
//        T* pObj;
//        bool isAry;
//
//        Deleter( T* deletePtr, bool is_Ary = false ) : pObj(deletePtr), isAry( is_Ary ) {};
//        virtual ~Deleter() {
//            if ( isAry ) {
//                T* pa = (T*)pObj;
//                GGAF_DELETEARR(pa);
//            } else {
//                T* p = (T*)pObj;
//                GGAF_DELETE(p);
//            }
//        }
//    };

protected:
//    std::list<DeleterBase*> m_DelList;   // 消去リスト
//    std::list<IUnknown*> m_ReleaseList;   // リリースリスト

public:
    AllocHierarchy(void);
    virtual ~AllocHierarchy(void);

    // フレームを生成する
    STDMETHOD(CreateFrame)(THIS_
        LPCSTR Name,
        LPD3DXFRAME *ppNewFrame
    ) override;

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
    ) override;

    // フレームを削除する
    STDMETHOD(DestroyFrame)(THIS_
        LPD3DXFRAME pFrameToFree
    ) override;

    // コンテナを削除する
    STDMETHOD(DestroyMeshContainer)(THIS_
        LPD3DXMESHCONTAINER pMeshContainerToFree
    ) override;


protected:
    // 消去リストに登録する
//    virtual void addDelList( DeleterBase* ptr, bool isAry = false );

    // 文字列をコピーする
    virtual LPSTR copyStr(LPCSTR name);

    // フレーム構造体を生成する
    virtual D3DXFRAME* createNewFrame();

    // メッシュコンテナ構造体を生成する
    virtual D3DXMESHCONTAINER* createNewMeshContainer();

//    // メッシュデータを登録
//    virtual void registerMeshData(CONST D3DXMESHDATA *pSrc, D3DXMESHDATA *pDest);

//    // リリースリストに登録
//    virtual void addReleaseList( IUnknown *comptr);

    // マテリアル登録
    virtual void registerMaterial(CONST D3DXMATERIAL *pSrc, DWORD num, D3DXMATERIAL **pDest);

    // エフェクト登録
    virtual void registerEffect(CONST D3DXEFFECTINSTANCE *pSrc, D3DXEFFECTINSTANCE **ppDest);

//    // 隣接ポリゴン登録
//    virtual void registerAdjacency(CONST DWORD *Src, DWORD polynum, DWORD **Dest);
//
//    // スキン登録
//    virtual void registerSkin( CONST LPD3DXSKININFO Src, LPD3DXSKININFO *Dest);
};

}

#endif /*GGAF_DX_ALLOCHIERARCHY_H_*/
