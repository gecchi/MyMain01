#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_



namespace MyStg2nd {

/**
 * ���ʃV�[���N���X .
 * 2008/9/8
 */
class CommonScene : public GgafDx9LibStg::DefaultScene {


public:
    /** �ėp���� */
    GgafCore::GgafActorDepository* _pDP_EffectExplosion001;
    GgafCore::GgafActorDepository* _pDepo_EffectTurbo002;
    GgafCore::GgafActorDepository* _pDP_MagicPointItem001;


    CommonScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~CommonScene();
};

}
#endif /*COMMONSCENE_H_*/
