#ifndef EFFECTEXPLOSION002_H_
#define EFFECTEXPLOSION002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"
#include "jp/gecchi/VioletVreath/actor/VvEffectActor.hpp"

namespace VioletVreath {

/**
 * �����G�t�F�N�g���̂Q .
 * �ւ������L����
 * @version 1.00
 * @since 2010/03/19
 * @author Masatoshi Tsuge
 */
class EffectExplosion002 : public VvEffectActor<GgafLib::DefaultMassSpriteActor> {

public:
    EffectExplosion002(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    int isOutOfView() override {
        //��ʊO���薳��
        return 0;
    }

    bool isOutOfSpacetime() const override {
        //�Q�[�����W�͈͊O���薳��
        return false;
    }

    virtual ~EffectExplosion002();
};

}
#endif /*EFFECTEXPLOSION002_H_*/

