#ifndef GGAF_DX_SKINANIMESHALLOCHIERARCHY_H_
#define GGAF_DX_SKINANIMESHALLOCHIERARCHY_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"

namespace GgafDx {

class SkinAniMeshAllocHierarchy : public BoneAniMeshAllocHierarchy {
public:
    SkinAniMeshAllocHierarchy();
public:
    virtual ~SkinAniMeshAllocHierarchy();

protected:
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

    // フレーム構造体を生成する
    virtual D3DXFRAME* createNewFrame();
    // メッシュコンテナ構造体を生成する
    virtual D3DXMESHCONTAINER* createNewMeshContainer();

    // コンテナを削除する
    STDMETHOD(DestroyMeshContainer)(THIS_
        LPD3DXMESHCONTAINER pMeshContainerToFree
    ) override;
};

}
#endif /*GGAF_DX_SKINANIMESHALLOCHIERARCHY_H_*/
