#ifndef LOCKONCURSOR001_H_
#define LOCKONCURSOR001_H_
#include "VioletVreath.h"
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
        LOCKON001_PROG_FIRST_LOCK ,
        LOCKON001_PROG_LOCK       ,
        LOCKON001_PROG_RELEASE    ,
        PROG_BANPEI,
    };


    GgafDx::GeometricActor* pTarget_;

public:
    LockonCursor001(const char* prm_name, const char* prm_model_id);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onActive() override;

    virtual void onReset() override;

    virtual void onInactive() override;

    virtual void processJudgement() override;

    virtual void releaseLockon() = 0;

    virtual void lockon(GgafDx::GeometricActor* prm_pTarget) = 0;

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
