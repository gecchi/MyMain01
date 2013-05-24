#ifndef EFFECTEXPLOSION002_H_
#define EFFECTEXPLOSION002_H_
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"

namespace VioletVreath {

/**
 * �����G�t�F�N�g���̂Q .
 * �ւ������L����
 * @version 1.00
 * @since 2010/03/19
 * @author Masatoshi Tsuge
 */
class EffectExplosion002 : public GgafLib::DefaultSpriteSetActor {

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

    bool isOutOfUniverse() override {
        //�Q�[�����W�͈͊O���薳��
        return false;
    }

    virtual ~EffectExplosion002();
};

}
#endif /*EFFECTEXPLOSION002_H_*/

