#ifndef GGAFDXCORE_GGAFDXSPHEREACTOR_H_
#define GGAFDXCORE_GGAFDXSPHEREACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"

namespace GgafDxCore {

/**
 * ���A�N�^�[.
 * GgafDxGeometricActor ���p�����A����\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A���a�Ppx�����̋�(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2010/10/21
 * @author Masatoshi Tsuge
 */
class GgafDxSphereActor : public GgafDxMeshActor {

public:
    GgafDxSphereActor(const char* prm_name,
                       GgafCore::GgafStatus* prm_pStat,
                       GgafDxChecker* prm_pChecker);

    void drawSphere(coord prm_x, coord prm_y, coord prm_z, coord prm_r);

    virtual ~GgafDxSphereActor(); //�f�X�g���N�^
};

}
#endif /*GGAFDXCORE_GGAFDXSPHEREACTOR_H_*/
