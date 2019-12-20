#ifndef GGAF_DX_BONEANIMESHALLOCHIERARCHY_H_
#define GGAF_DX_BONEANIMESHALLOCHIERARCHY_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/AllocHierarchy.h"
#include "jp/ggaf/dx/util/BoneAniMeshFrame.h"

namespace GgafDx {

// BoneAniMeshFrame取り扱いAllocateHierarchyクラス
class BoneAniMeshAllocHierarchy: public AllocHierarchy {
public:
    BoneAniMeshAllocHierarchy(void);
public:
    virtual ~BoneAniMeshAllocHierarchy(void);

protected:
    // フレーム構造体を生成する
    virtual D3DXFRAME* createNewFrame();
};

}
#endif /*GGAF_DX_BONEANIMESHALLOCHIERARCHY_H_*/
