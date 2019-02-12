#ifndef GGAF_DX_ALLOCHIERARCHYWORLDFRAME_H_
#define GGAF_DX_ALLOCHIERARCHYWORLDFRAME_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/AllocHierarchy.h"

namespace GgafDx {

// ワールド変換行列付きフレーム構造体
class D3DXFRAME_WORLD : public D3DXFRAME {
public:
   D3DXMATRIX WorldTransMatrix;
};

// D3DXFRAME_WORLD取り扱いAllocateHierarchyクラス
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
