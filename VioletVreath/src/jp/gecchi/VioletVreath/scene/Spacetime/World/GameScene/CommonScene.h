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

#define pCOMMON_DEPO_STORE(X)              pStore_##X##_
#define getCommonDepoStore(X)                  (pCOMMON_SCENE->pCOMMON_DEPO_STORE(X))
#define dispatchFromCommonDepositoryStore(X)         ( (GgafCore::GgafActorDepository*)(getCommonDepoStore(X)->dispatch()) )
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

    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectExplosion001);
    /** �ėp�����G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectExplosion002);
    /** �ėp�����G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectExplosion003);
    /** �ėp�����G�t�F�N�g���̂S�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectExplosion004);
    /** �^�[�{�G�t�F�N�g�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectTurbo002);
    /** �A�C�e���I�u�W�F�N�g���A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(MagicPointItem001);
    /** �A�C�e���I�u�W�F�N�g���A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(MagicPointItem002);
    /** �A�C�e���I�u�W�F�N�g��A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(MagicPointItem003);

    /** �ėp�o���G�t�F�N�g���̂P�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectBlink001);
    /** �ėp�o���G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectBlink002);
    /** �ėp�o���G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(EffectBlink003);

    GgafCore::GgafActorDepository* pCOMMON_DEPO(SpriteLabelBonus001);

    /** �ėp�o���G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pCOMMON_DEPO(Shot004);

    /**  */
    GgafCore::GgafActorDepositoryStore* pCOMMON_DEPO_STORE(EnemyWateringLaserChip001);
    GgafCore::GgafActorDepositoryStore* pCOMMON_DEPO_STORE(EnemyStraightLaserChip001);

public:
    CommonScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;
    void onReset() override;

    virtual void processBehavior() override;

    /**
     * X���̕��̕����ɃX�N���[��������֐� .
     * @param pThat �A�N�^�[
     * @param p1 �X�N���[���X�s�[�h(_scroll_speed�ւ̃|�C���^)
     * @param p2 nullptr
     * @param p3 nullptr
     */
    static void scrollX(GgafObject* pThat, void* p1, void* p2, void* p3);

    virtual ~CommonScene();
};

}
#endif /*COMMONSCENE_H_*/
