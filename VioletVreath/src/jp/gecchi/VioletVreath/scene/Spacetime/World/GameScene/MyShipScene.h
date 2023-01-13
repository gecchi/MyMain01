#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "../GameScene.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/camera/worker/VamSysCamWorker.h"

#ifdef pGAME_SCENE
    #define pMYSHIP_SCENE (pGAME_SCENE->pMyShipScene_)
    #define pMYSHIP (pMYSHIP_SCENE->pMyShip_)
    #define pVAM (pMYSHIP_SCENE->pVamSysCamWorker_)
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
class MyShipScene : public VvScene<GgafLib::DefaultScene> {

public:
    /** ���@ */
    MyShip* pMyShip_;
    /** ���@�����G�t�F�N�g */
    EffectMyShipExplosion* pEffectMyShipExplosion_;
    /** VAMSYSTEM �J�������[�N */
    VamSysCamWorker* pVamSysCamWorker_;
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

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
