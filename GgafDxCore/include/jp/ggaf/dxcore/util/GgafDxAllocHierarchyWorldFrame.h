#ifndef GGAFDXCORE_GGAFDXALLOCHIERARCHYWORLDFRAME_H_
#define GGAFDXCORE_GGAFDXALLOCHIERARCHYWORLDFRAME_H_
#include "jp/ggaf/dxcore/util/GgafDxAllocHierarchy.h"

namespace GgafDxCore {

// ワールド変換行列付きフレーム構造体
class D3DXFRAME_WORLD : public D3DXFRAME {
public:
   D3DXMATRIX WorldTransMatrix;
};

// D3DXFRAME_WORLD取り扱いAllocateHierarchyクラス
class GgafDxAllocHierarchyWorldFrame: public GgafDxAllocHierarchy {
public:
    GgafDxAllocHierarchyWorldFrame(void);
public:
    virtual ~GgafDxAllocHierarchyWorldFrame(void);

protected:
    // フレーム構造体を生成する
    virtual D3DXFRAME* createNewFrame();
};

}
#endif /*GGAFDXCORE_GGAFDXALLOCHIERARCHYWORLDFRAME_H_*/
