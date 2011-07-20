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
    GgafCore::GgafActorStore* _pDP_EffectExplosion001;
    GgafCore::GgafActorStore* _pStore_EffectTurbo002;
    GgafCore::GgafActorStore* _pDP_MagicPointItem001;


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
