#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "../GameScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/VamSysCamWorker2.h"

#ifdef pGAME_SCENE
    #define pMYSHIP_SCENE (pGAME_SCENE->pMyShipScene_)
    #define pMYSHIP (pMYSHIP_SCENE->pMyShip_)
    #define pVAM (pMYSHIP_SCENE->pVamSysCamWorker2_)
#else
    #undef pMYSHIP_SCENE
    #undef pMYSHIP
    #undef pVAM
#endif

namespace VioletVreath {

/**
 * ���@�֘A�V�[�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class MyShipScene : public GgafLib::DefaultScene {

public:
    /** ���@ */
    MyShip* pMyShip_;
    /** ���@�����G�t�F�N�g */
    EffectMyShipExplosion* pEffectMyShipExplosion_;
    /** VAMSYSTEM �J�������[�N */
    VamSysCamWorker2* pVamSysCamWorker2_;
    /** �c�@�\�� */
    LabelGecchi16Font* pLabelZanki_;

    /** ���@���g�y�� */
    MyBunshinBase** papBunshinBase_;

public:
    MyShipScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;
    void onReset() override;
    void onActive() override;
    void processBehavior() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
