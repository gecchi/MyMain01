#ifndef EFFECTOPTIONMAGIC001_H_
#define EFFECTOPTIONMAGIC001_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �I�v�V�������@�G�t�F�N�g���̂P .
 * @version 1.00
 * @since 2013/07/31
 * @author Masatoshi Tsuge
 */
class EffectOptionMagic001 : public GgafLib::DefaultMeshSetActor {

public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    EffectOptionMagic001(const char* prm_name);

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

    virtual ~EffectOptionMagic001();
};

}
#endif /*EFFECTOPTIONMAGIC001_H_*/

