#ifndef GGAF_DX_SPHEREACTOR_H_
#define GGAF_DX_SPHEREACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafDx {

/**
 * ���A�N�^�[.
 * ����\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A���a�Ppx�����̋�(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2010/10/21
 * @author Masatoshi Tsuge
 */
class SphereActor : public MeshActor {

public:
    SphereActor(const char* prm_name,
                CollisionChecker* prm_pChecker);

    void drawSphere(coord prm_x, coord prm_y, coord prm_z, coord prm_r);

    virtual ~SphereActor();
};

}
#endif /*GGAF_DX_SPHEREACTOR_H_*/
