#ifndef GGAFLIB_DEFAULTCAMERAUPVECTOR_H_
#define GGAFLIB_DEFAULTCAMERAUPVECTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraUpVector.h"

namespace GgafLib {

/**
 * �J������UP�̂����x�N�g���\���A�N�^�[ .
 * ���_���玩�g�̍��W�ւ̃x�N�g�����J������UP�Ɠ������܂�
 * @version 1.00
 * @since 2014/12/22
 * @author Masatoshi Tsuge
 */
class DefaultCameraUpVector : public GgafDxCore::GgafDxCameraUpVector {

public:
    dir26 up_dir_;

public:
    DefaultCameraUpVector(const char* prm_name);

    virtual void initialize() override {
    }

    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {
    }

    /**
     * �J������UP�ʔԍ��A�����̖ʔԍ��ɃZ�b�g���AUP�x�N�g�����X���C�h�ړ����J�n�����܂��B
     * @param prm_face_no �J������UP�ʔԍ�
     */
//    void moveTo(dir26 prm_dir_no, frame prm_spent);
    void moveTo(coord tx, coord ty, coord tz, frame prm_spent);

    virtual ~DefaultCameraUpVector();
};

}
#endif /*GGAFLIB_DEFAULTCAMERAUPVECTOR_H_*/
