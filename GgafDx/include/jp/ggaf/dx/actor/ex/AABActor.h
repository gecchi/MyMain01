#ifndef GGAF_DX_AABACTOR_H_
#define GGAF_DX_AABACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafDx {

/**
 * �L���[�u�A�N�^�[.
 * MeshActor ���p�����A�L���[�u�i�����́j��\�����邽�߂̃A�N�^�[�ł��B<BR>
 * X�t�@�C���́A�����Ppx�����̗�����(���S��(0,0,0))�̃��b�V����ǂݍ��܂��Ă��������B
 * @version 1.00
 * @since 2008/10/10
 * @author Masatoshi Tsuge
 */
class AABActor : public MeshActor {

public:
    AABActor(const char* prm_name, Checker* prm_pChecker);

    void drawBox(coord prm_x1, coord prm_y1, coord prm_z1, coord prm_x2, coord prm_y2, coord prm_z2);

    virtual ~AABActor(); //�f�X�g���N�^
};

}
#endif /*GGAF_DX_BOXACTOR_H_*/
