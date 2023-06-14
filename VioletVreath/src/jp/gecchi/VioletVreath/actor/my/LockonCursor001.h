#ifndef LOCKONCURSOR001_H_
#define LOCKONCURSOR001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"

namespace VioletVreath {



/**
 * ���b�N�I��
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class LockonCursor001 : public GgafLib::DefaultMassSpriteActor {

public:
    enum {
        LOCKON001_PHASE_FIRST_LOCK ,
        LOCKON001_PHASE_LOCK       ,
        LOCKON001_PHASE_RELEASE    ,
        PHASE_BANPEI,
    };


    GgafDx::GeometricActor* pTarget_;
    GgafDx::GeometricActor* pTarget_prev_;
public:
    LockonCursor001(const char* prm_name, const char* prm_model);

    virtual void initialize() override;

    virtual void onCreateModel() override;

    virtual void processBehavior() override;

    virtual void onActive() override;

    virtual void onReset() override;

    virtual void onInactive() override;

    virtual void processJudgement() override;

    virtual void releaseLockon() = 0;

    virtual void lockon(GgafDx::GeometricActor* prm_pTarget) = 0;


    bool hasJustLockon() {
        if (pTarget_prev_ != pTarget_ && pTarget_ != nullptr) {
            return true;
        } else {
            return false;
        }
    }

    bool hasJustReleaseLockon() {
        if (pTarget_prev_ && pTarget_ == nullptr) {
            return true;
        } else {
            return false;
        }
    }

    virtual ~LockonCursor001();


//DEBUG���[�h�A�v���I�����̃c���[�\�����A
//pTarget_���s���ɂȂ�ꍇ���A�K�v�ȂƂ��ɃR�����g���O���Ďg�p�B
//
//    /**
//     * �^�[�Q�b�g���\������_���v(�f�o�b�O�p) .
//     */
//    void dump();
//
//    /**
//     * �^�[�Q�b�g���\������_���v(�f�o�b�O�p) .
//     */
//    void dump(std::string prm_parent);

};

}
#endif /*LOCKONCURSOR001_H_*/

