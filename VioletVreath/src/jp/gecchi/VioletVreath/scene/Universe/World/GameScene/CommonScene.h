#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene.h"

#ifdef P_GAME_SCENE
    #define P_COMMON_SCENE (P_GAME_SCENE->pCommonScene_)
#else
    #undef P_COMMON_SCENE
#endif

/**
 * ���ʃI�u�W�F�N�g�擾�}�N��
 */
#define P_COMMON_DEPO(X)                   pDepo_##X##_
#define getCommonDepository(X)             (P_COMMON_SCENE->P_COMMON_DEPO(X))
#define dispatchFromCommon(X)              ( (X*)(getCommonDepository(X)->dispatch()) )
#define dispatchDelayFromCommon(X, F)      ( (X*)(getCommonDepository(X)->dispatch((F))) )
#define dispatchForceFromCommon(X)         ( (X*)(getCommonDepository(X)->dispatchForce()) )
#define dispatchForceDelayFromCommon(X, F) ( (X*)(getCommonDepository(X)->dispatchForce((F))) )

#define P_COMMON_STORE(X)                   pStore_##X##_

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

    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectExplosion001);
    /** �ėp�����G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectExplosion002);
    /** �ėp�����G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectExplosion003);
    /** �ėp�����G�t�F�N�g���̂S�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectExplosion004);
    /** �^�[�{�G�t�F�N�g�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectTurbo002);
    /** �A�C�e���I�u�W�F�N�g���A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(MagicPointItem001);
    /** �A�C�e���I�u�W�F�N�g���A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(MagicPointItem002);
    /** �A�C�e���I�u�W�F�N�g��A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(MagicPointItem003);

    /** �ėp�o���G�t�F�N�g���̂P�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectEntry001);
    /** �ėp�o���G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectEntry002);
    /** �ėp�o���G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(EffectEntry003);

    GgafCore::GgafActorDepository* const P_COMMON_DEPO(SpriteLabelBonus001);

    /** �ėp�o���G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* const P_COMMON_DEPO(Shot004);

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
