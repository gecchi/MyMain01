#ifndef MYMAGICENERGYCORE_H_
#define MYMAGICENERGYCORE_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * MP�G�l���M�[�j .
 * @version 1.00
 * @since 2013/10/23
 * @author Masatoshi Tsuge
 */
class MyMagicEnergyCore : public GgafLib::DefaultMeshActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxMver_;

public:
   MyMagicEnergyCore(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    /**
     * �I�v�V�����r���J�n���A�j���[�V���� .
     */
    void execOptionMagic();

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    int isOutOfView() override;

    bool isOutOfUniverse() override;

    virtual ~MyMagicEnergyCore();
};

}
#endif /*MYMAGICENERGYCORE_H_*/

