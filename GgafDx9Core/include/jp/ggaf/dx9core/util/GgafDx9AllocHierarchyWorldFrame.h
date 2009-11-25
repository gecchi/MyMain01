#ifndef GGAFDX9ALLOCHIERARCHYWORLDFRAME_H_
#define GGAFDX9ALLOCHIERARCHYWORLDFRAME_H_

namespace GgafDx9Core {

// ���[���h�ϊ��s��t���t���[���\����
class D3DXFRAME_WORLD : public D3DXFRAME
{
public:
   D3DXMATRIX WorldTransMatrix;
};


// D3DXFRAME_WORLD��舵��AllocateHierarchy�N���X
class GgafDx9AllocHierarchyWorldFrame: public GgafDx9AllocHierarchy {
public:
    GgafDx9AllocHierarchyWorldFrame(void);
public:
    virtual ~GgafDx9AllocHierarchyWorldFrame(void);

protected:
    // �t���[���\���̂𐶐�����
    virtual D3DXFRAME* CreateNewFrame();
};

}
#endif /*GGAFDX9ALLOCHIERARCHYWORLDFRAME_H_*/
