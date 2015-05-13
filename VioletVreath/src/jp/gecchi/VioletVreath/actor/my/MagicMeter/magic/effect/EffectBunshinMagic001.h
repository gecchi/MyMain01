#ifndef EFFECTBUNSHINMAGIC001_H_
#define EFFECTBUNSHINMAGIC001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * ���g���@�G�t�F�N�g���̂P .
 * @version 1.00
 * @since 2013/07/31
 * @author Masatoshi Tsuge
 */
class EffectBunshinMagic001 : public GgafLib::DefaultMeshSetActor {

public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    EffectBunshinMagic001(const char* prm_name);

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

    virtual ~EffectBunshinMagic001();
};

}
#endif /*EFFECTBUNSHINMAGIC001_H_*/

