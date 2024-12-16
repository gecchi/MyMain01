#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "../GameScene.h"

#ifdef pGAME_SCENE
    #define pCOMMON_SCENE (pGAME_SCENE->pCommonScene_)
#else
    #undef pCOMMON_SCENE
#endif

/**
 * ���ʃI�u�W�F�N�g�擾�}�N��
 */
#define CommonScene_pCOMMON_DEPO(X)          pDepo_##X##_
#define CommonScene_getDepository(X)         (pCOMMON_SCENE->CommonScene_pCOMMON_DEPO(X))
#define CommonScene_dispatch(X)              ( (X*)(CommonScene_getDepository(X)->dispatch()) )
#define CommonScene_dispatchDelay(X, F)      ( (X*)(CommonScene_getDepository(X)->dispatch((F))) )
#define CommonScene_dispatchForce(X)         ( (X*)(CommonScene_getDepository(X)->dispatchForce()) )

#define CommonScene_pCOMMON_DEPO_STORE(X)    pStore_##X##_
#define CommonScene_getDepoStore(X)          (pCOMMON_SCENE->CommonScene_pCOMMON_DEPO_STORE(X))
#define CommonScene_dispatchDepoStore(X)     ( (GgafCore::ActorDepository*)(CommonScene_getDepoStore(X)->dispatch()) )

namespace VioletVreath {

/**
 * ���ʃV�[���N���X .
 * ��Ȏd���͎��̃X�e�[�W�����肷�邱�Ƃł��B
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class CommonScene : public VvScene<GgafLib::DefaultScene> {

public:
    /** �ėp�����G�t�F�N�g���̂P�p�A����f�|�W�g�� */

    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectExplosion001);
    /** �ėp�����G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectExplosion002);
    /** �ėp�����G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectExplosion003);
    /** �ėp�����G�t�F�N�g���̂S�p�A����f�|�W�g�� */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectExplosion004);


    /** �ėp�o���G�t�F�N�g���̂P�p�A����f�|�W�g�� */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectBlink001);
    /** �ėp�o���G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectBlink002);
    /** �ėp�o���G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(EffectBlink003);


    /** �ėp�o���G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::ActorDepository* CommonScene_pCOMMON_DEPO(Shot004);

    /**  */
    GgafCore::ActorDepositoryStore* CommonScene_pCOMMON_DEPO_STORE(EnemyWateringLaserChip001);
    GgafCore::ActorDepositoryStore* CommonScene_pCOMMON_DEPO_STORE(EnemyStraightLaserChip001);

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
     * @param p1 �X�N���[���X�s�[�h(_feature_p1�ւ̃|�C���^)
     * @param p2 nullptr
     * @param p3 nullptr
     */
    static void scrollX(GgafCore::Object* pThat, void* p1, void* p2, void* p3);

    virtual ~CommonScene();
};

}
#endif /*COMMONSCENE_H_*/
