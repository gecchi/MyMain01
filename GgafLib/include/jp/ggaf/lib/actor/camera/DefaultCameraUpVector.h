#ifndef GGAF_LIB_DEFAULTCAMERAUPVECTOR_H_
#define GGAF_LIB_DEFAULTCAMERAUPVECTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/camera/CameraUpVector.h"

namespace GgafLib {

/**
 * �J������UP�̂����x�N�g���\���A�N�^�[ .
 * ���_���玩�g�̍��W�ւ̃x�N�g�����J������UP�Ɠ������܂�
 * @version 1.00
 * @since 2014/12/22
 * @author Masatoshi Tsuge
 */
class DefaultCameraUpVector : public GgafDx::CameraUpVector {

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

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    /**
     * �J������UP�ʔԍ��A�����̖ʔԍ��ɃZ�b�g���AUP�x�N�g�����X���C�h�ړ����J�n�����܂��B
     * @param prm_face_no �J������UP�ʔԍ�
     */
//    void moveTo(dir26 prm_dir_no, frame prm_spent);
    void slideMvTo(coord tx, coord ty, coord tz, frame prm_spent, float prm_p1, float prm_p2);

    virtual ~DefaultCameraUpVector();
};

}
#endif /*GGAF_LIB_DEFAULTCAMERAUPVECTOR_H_*/
