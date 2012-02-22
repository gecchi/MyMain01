#ifndef GGAFDXALLOCHIERARCHYWORLDFRAME_H_
#define GGAFDXALLOCHIERARCHYWORLDFRAME_H_

namespace GgafDxCore {

// ワールド変換行列付きフレーム構造体
class D3DXFRAME_WORLD : public D3DXFRAME
{
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
#endif /*GGAFDXALLOCHIERARCHYWORLDFRAME_H_*/
