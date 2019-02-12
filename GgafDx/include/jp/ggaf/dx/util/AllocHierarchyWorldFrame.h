#ifndef GGAF_DX_ALLOCHIERARCHYWORLDFRAME_H_
#define GGAF_DX_ALLOCHIERARCHYWORLDFRAME_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/AllocHierarchy.h"

namespace GgafDx {

// ���[���h�ϊ��s��t���t���[���\����
class D3DXFRAME_WORLD : public D3DXFRAME {
public:
   D3DXMATRIX WorldTransMatrix;
};

// D3DXFRAME_WORLD��舵��AllocateHierarchy�N���X
class AllocHierarchyWorldFrame: public AllocHierarchy {
public:
    AllocHierarchyWorldFrame(void);
public:
    virtual ~AllocHierarchyWorldFrame(void);

protected:
    // �t���[���\���̂𐶐�����
    virtual D3DXFRAME* createNewFrame();
};

}
#endif /*GGAF_DX_ALLOCHIERARCHYWORLDFRAME_H_*/
