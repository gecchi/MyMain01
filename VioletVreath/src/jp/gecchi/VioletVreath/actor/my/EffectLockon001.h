#ifndef EFFECTLOCKON001_H_
#define EFFECTLOCKON001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"

namespace VioletVreath {



/**
 * ���b�N�I��
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001 : public GgafLib::DefaultMassSpriteActor {

public:
    enum {
        LOCKON001_PROG_FIRST_LOCK ,
        LOCKON001_PROG_LOCK       ,
        LOCKON001_PROG_RELEASE    ,
        PROG_BANPEI,
    };


    GgafDxCore::GgafDxGeometricActor* pTarget_;

public:
    EffectLockon001(const char* prm_name, const char* prm_model_id);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onActive() override;

    virtual void onReset() override;

    virtual void onInactive() override;

    virtual void processJudgement() override;

    virtual void releaseLockon() = 0;

    virtual void lockon(GgafDxGeometricActor* prm_pTarget) = 0;

    virtual ~EffectLockon001();


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
#endif /*EFFECTLOCKON001_H_*/

