#ifndef GGAF_DX_FRAMEWORLDMATRIX_H_
#define GGAF_DX_FRAMEWORLDMATRIX_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/AllocHierarchy.h"

namespace GgafDx {

// ���[���h�ϊ��s��t���t���[���\����
class FrameWorldMatrix : public D3DXFRAME {
public:
   D3DXMATRIX WorldTransMatrix;
};

}
#endif /*GGAF_DX_FRAMEWORLDMATRIX_H_*/
