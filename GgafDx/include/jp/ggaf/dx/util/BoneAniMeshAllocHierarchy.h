#ifndef GGAF_DX_BONEANIMESHALLOCHIERARCHY_H_
#define GGAF_DX_BONEANIMESHALLOCHIERARCHY_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/AllocHierarchy.h"

namespace GgafDx {

// BoneAniMeshFrame��舵��AllocateHierarchy�N���X
class BoneAniMeshAllocHierarchy : public AllocHierarchy {
public:
    BoneAniMeshAllocHierarchy();
    virtual ~BoneAniMeshAllocHierarchy();

protected:
    // �t���[���\���̂𐶐�����
    virtual D3DXFRAME* createNewFrame();
    virtual D3DXMESHCONTAINER* createNewMeshContainer();
};

}
#endif /*GGAF_DX_BONEANIMESHALLOCHIERARCHY_H_*/
