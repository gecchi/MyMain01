#ifndef GGAF_DX_ALLOCHIERARCHYWORLDFRAME_H_
#define GGAF_DX_ALLOCHIERARCHYWORLDFRAME_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/AllocHierarchy.h"
#include "jp/ggaf/dx/util/FrameWorldMatrix.h"

namespace GgafDx {

// FrameWorldMatrix取り扱いAllocateHierarchyクラス
class AllocHierarchyWorldFrame: public AllocHierarchy {
public:
    AllocHierarchyWorldFrame(void);
public:
    virtual ~AllocHierarchyWorldFrame(void);

protected:
    // フレーム構造体を生成する
    virtual D3DXFRAME* createNewFrame();
};

}
#endif /*GGAF_DX_ALLOCHIERARCHYWORLDFRAME_H_*/
