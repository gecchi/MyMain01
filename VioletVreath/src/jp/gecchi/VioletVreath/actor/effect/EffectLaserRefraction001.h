#ifndef EFFECTLASERREFRACTION001_H_
#define EFFECTLASERREFRACTION001_H_
namespace VioletVreath {

/**
 * ���[�U�[���܃G�t�F�N�g .
 * @version 1.00
 * @since 2010/07/26
 * @author Masatoshi Tsuge
 */
class EffectLaserRefraction001 : public GgafLib::DefaultMeshSetActor {

public:
    EffectLaserRefraction001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

//    int isOutOfView() override {
//        //��ʊO���薳��
//        return 0;
//    }
//
//    bool isOutOfUniverse() override {
//        //�Q�[�����W�͈͊O���薳��
//        return false;
//    }

    virtual ~EffectLaserRefraction001();
};

}
#endif /*EFFECTLASERREFRACTION001_H_*/
