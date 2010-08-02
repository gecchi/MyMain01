#ifndef EFFECTLASERREFRACTION001_H_
#define EFFECTLASERREFRACTION001_H_
namespace MyStg2nd {

/**
 * ���[�U�[���܃G�t�F�N�g .
 * @version 1.00
 * @since 2010/07/26
 * @author Masatoshi Tsuge
 */
class EffectLaserRefraction001 : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    EffectLaserRefraction001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }

    void onInactive() override;

    int isOffscreen() override {
        //��ʊO���薳��
        return 0;
    }

    bool isOutOfGameSpace() override {
        //�Q�[�����W�͈͊O���薳��
        return false;
    }

    virtual ~EffectLaserRefraction001();
};

}
#endif /*EFFECTLASERREFRACTION001_H_*/
