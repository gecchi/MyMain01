#ifndef GGAF_DX_SKINANIMESHALLOCHIERARCHY_H_
#define GGAF_DX_SKINANIMESHALLOCHIERARCHY_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/BoneAniMeshAllocHierarchy.h"

namespace GgafDx {

class SkinAniMeshAllocHierarchy : public BoneAniMeshAllocHierarchy {
public:
    SkinAniMeshAllocHierarchy();
public:
    virtual ~SkinAniMeshAllocHierarchy();

protected:
    // �R���e�i�𐶐�����
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

    // �t���[���\���̂𐶐�����
    virtual D3DXFRAME* createNewFrame();
    // ���b�V���R���e�i�\���̂𐶐�����
    virtual D3DXMESHCONTAINER* createNewMeshContainer();

    // �R���e�i���폜����
    STDMETHOD(DestroyMeshContainer)(THIS_
        LPD3DXMESHCONTAINER pMeshContainerToFree
    ) override;
};

}
#endif /*GGAF_DX_SKINANIMESHALLOCHIERARCHY_H_*/
