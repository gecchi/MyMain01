#ifndef EFFECTRATISLAVIAEYE001_H_
#define EFFECTRATISLAVIAEYE001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVreath {

/**
 * �g�[���X�ڋʃ��[�U�[���ˑO�`���[�W�G�t�F�N�g
 * @version 1.00
 * @since 2012/10/19
 * @author Masatoshi Tsuge
 */
class EffectRatislaviaEye001 : public GgafLib::DefaultSpriteActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

    int cnt_;

public:
    EffectRatislaviaEye001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectRatislaviaEye001();
};

}
#endif /*EFFECTRATISLAVIAEYE001_H_*/

