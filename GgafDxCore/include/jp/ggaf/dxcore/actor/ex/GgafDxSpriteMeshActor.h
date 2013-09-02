#ifndef GGAFDXCORE_GGAFDXSPRITEMESHACTOR_H_
#define GGAFDXCORE_GGAFDXSPRITEMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxMeshActor.h"

namespace GgafDxCore {

/**
 * �X�v���C�g���b�V���Z�b�g�A�N�^�[.
 * GgafDxMeshActor ���p�����A
 * �����UV��؂�ւ���@�\��L�����A�N�^�[
 * ���b�V���RD�I�u�W�F�N�g�̕\�ʂ̃e�N�X�`�����A�j���[�V�����ł��܂��B
 * @version 1.00
 * @since 2009/02/09
 * @author Masatoshi Tsuge
 */
class GgafDxSpriteMeshActor : public GgafDxMeshActor {

public:
    /** UV�t���b�p�[(�p���p���A�j��) */
    GgafDxUvFlipper* _pUvFlipper;

public:
    /**
     * �R���X�g���N�^.
     * GgafDxSpriteMeshSetActor �Ŏg�p���郂�f��ID�͔����ĉ������B
     * @param prm_name
     * @param prm_model
     * @param prm_pStat
     * @param prm_pChecker
     */
    GgafDxSpriteMeshActor(const char* prm_name,
                           const char* prm_model,
                           GgafCore::GgafStatus* prm_pStat,
                           GgafDxChecker* prm_pChecker );

    virtual void processDraw() override;

    virtual ~GgafDxSpriteMeshActor();
};

}
#endif /*GGAFDXCORE_GGAFDXSPRITEMESHACTOR_H_*/
