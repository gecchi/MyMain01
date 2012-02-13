#ifndef EFFECTMAGIC001_H_
#define EFFECTMAGIC001_H_
namespace VioletVreath {

/**
 * ���@�G�t�F�N�g���̂P .
 * @version 1.00
 * @since 2011/01/18
 * @author Masatoshi Tsuge
 */
class EffectMagic001 : public GgafLib::DefaultMeshSetActor {

public:
    EffectMagic001(const char* prm_name);

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

    virtual ~EffectMagic001();
};

}
#endif /*EFFECTMAGIC001_H_*/

