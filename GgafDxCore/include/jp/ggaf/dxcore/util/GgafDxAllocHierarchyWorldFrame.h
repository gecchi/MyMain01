#ifndef GGAFDXALLOCHIERARCHYWORLDFRAME_H_
#define GGAFDXALLOCHIERARCHYWORLDFRAME_H_

namespace GgafDxCore {

// ���[���h�ϊ��s��t���t���[���\����
class D3DXFRAME_WORLD : public D3DXFRAME
{
public:
   D3DXMATRIX WorldTransMatrix;
};


// D3DXFRAME_WORLD��舵��AllocateHierarchy�N���X
class GgafDxAllocHierarchyWorldFrame: public GgafDxAllocHierarchy {
public:
    GgafDxAllocHierarchyWorldFrame(void);
public:
    virtual ~GgafDxAllocHierarchyWorldFrame(void);

protected:
    // �t���[���\���̂𐶐�����
    virtual D3DXFRAME* createNewFrame();
};

}
#endif /*GGAFDXALLOCHIERARCHYWORLDFRAME_H_*/
