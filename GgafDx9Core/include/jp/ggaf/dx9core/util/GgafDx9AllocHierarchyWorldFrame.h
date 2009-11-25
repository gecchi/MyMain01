#ifndef GGAFDX9ALLOCHIERARCHYWORLDFRAME_H_
#define GGAFDX9ALLOCHIERARCHYWORLDFRAME_H_

namespace GgafDx9Core {

// ワールド変換行列付きフレーム構造体
class D3DXFRAME_WORLD : public D3DXFRAME
{
public:
   D3DXMATRIX WorldTransMatrix;
};


// D3DXFRAME_WORLD取り扱いAllocateHierarchyクラス
class GgafDx9AllocHierarchyWorldFrame: public GgafDx9AllocHierarchy {
public:
    GgafDx9AllocHierarchyWorldFrame(void);
public:
    virtual ~GgafDx9AllocHierarchyWorldFrame(void);

protected:
    // フレーム構造体を生成する
    virtual D3DXFRAME* CreateNewFrame();
};

}
#endif /*GGAFDX9ALLOCHIERARCHYWORLDFRAME_H_*/
