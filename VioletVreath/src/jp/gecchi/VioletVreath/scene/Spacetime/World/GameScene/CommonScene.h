#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene.h"

#ifdef pGAME_SCENE
    #define pCOMMON_SCENE (pGAME_SCENE->pCommonScene_)
#else
    #undef pCOMMON_SCENE
#endif

/**
 * ���ʃI�u�W�F�N�g�擾�}�N��
 */
#define pCOMMON_DEPO(X)                   pDepo_##X##_
#define getCommonDepository(X)             (pCOMMON_SCENE->pCOMMON_DEPO(X))
#define dispatchFromCommon(X)              ( (X*)(getCommonDepository(X)->dispatch()) )
#define dispatchDelayFromCommon(X, F)      ( (X*)(getCommonDepository(X)->dispatch((F))) )
#define dispatchForceFromCommon(X)         ( (X*)(getCommonDepository(X)->dispatchForce()) )

#define pCOMMON_STORE(X)                   pStore_##X##_

namespace VioletVreath {

/**
 * ���ʃV�[���N���X .
 * ��Ȏd���͎��̃X�e�[�W�����肷�邱�Ƃł��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CommonScene : public GgafLib::DefaultScene {

public:
    /** �ėp�����G�t�F�N�g���̂P�p�A����f�|�W�g�� */

    GgafCore::GgafActorDepository* const pCOMMON_DEPO(EffectExplosion001);
    /** �ėp�����G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(EffectExplosion002);
    /** �ėp�����G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(EffectExplosion003);
    /** �ėp�����G�t�F�N�g���̂S�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(EffectExplosion004);
    /** �^�[�{�G�t�F�N�g�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(EffectTurbo002);
    /** �A�C�e���I�u�W�F�N�g���A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(MagicPointItem001);
    /** �A�C�e���I�u�W�F�N�g���A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(MagicPointItem002);
    /** �A�C�e���I�u�W�F�N�g��A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(MagicPointItem003);

    /** �ėp�o���G�t�F�N�g���̂P�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(EffectBlink001);
    /** �ėp�o���G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(EffectBlink002);
    /** �ėp�o���G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(EffectBlink003);

    GgafCore::GgafActorDepository* const pCOMMON_DEPO(SpriteLabelBonus001);

    /** �ėp�o���G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const pCOMMON_DEPO(Shot004);

    /**  */
    GgafCore::GgafActorDepositoryStore* const pStore_EnemyWateringLaser001_;
    GgafCore::GgafActorDepositoryStore* const pStore_EnemyStraightLaser001_;

public:
    CommonScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;
    void onReset() override;

    virtual void processBehavior() override;

    virtual ~CommonScene();
};

}
#endif /*COMMONSCENE_H_*/
