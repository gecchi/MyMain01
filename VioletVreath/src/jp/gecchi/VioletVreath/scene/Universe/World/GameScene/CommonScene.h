#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_


#ifdef P_GAME_SCENE
    #define P_COMMON_SCENE (P_GAME_SCENE->pCommonScene_)
#else
    #error P_GAME_SCENE isnt define
#endif

/**
 * ���ʃI�u�W�F�N�g�擾�}�N��
 * EffectExplosion001, EffectTurbo002, MagicPointItem001, MagicPointItem002 �̂݉\
 */
#define employFromCommon(X) ((X*)P_COMMON_SCENE->pDepo_##X##_->dispatch())
#define employDelayFromCommon(X, F) ((X*)P_COMMON_SCENE->pDepo_##X##_->dispatch((F)))

namespace VioletVreath {

/**
 * ���ʃV�[���N���X .
 * 2008/9/8
 */
class CommonScene : public GgafLib::DefaultScene {

public:
    /** �ėp�����G�t�F�N�g���̂P�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_EffectExplosion001_;
    /** �ėp�����G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_EffectExplosion002_;
    /** �ėp�����G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_EffectExplosion003_;
    /** �^�[�{�G�t�F�N�g�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_EffectTurbo002_;
    /** �A�C�e���I�u�W�F�N�g���̂P�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_MagicPointItem001_;
    /** �A�C�e���I�u�W�F�N�g���̂P�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_MagicPointItem002_;

    /** �ėp�o���G�t�F�N�g���̂P�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_EffectEntry001_;
    /** �ėp�o���G�t�F�N�g���̂Q�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_EffectEntry002_;
    /** �ėp�o���G�t�F�N�g���̂R�p�A����f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_EffectEntry003_;


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
