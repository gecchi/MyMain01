#ifndef MYTORPEDOBLAST_H_
#define MYTORPEDOBLAST_H_

#define MyTorpedoBlast_IN_FIRE 1
#define MyTorpedoBlast_RELEASE 2
namespace MyStg2nd {

/**
 * �������� .
 * @version 1.00
 * @since 2010/09/22
 * @author Masatoshi Tsuge
 */
class MyTorpedoBlast : public GgafLib::DefaultMeshSetActor {

public:

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_pMyOptionTorpedoController �e�A�N�^�[�ƂȂ鋛���R�����[���[ .
     * @return
     */
    MyTorpedoBlast(const char* prm_name);

    void onCreateModel() override {
    }
    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyTorpedoBlast();
};

}
#endif /*MYTORPEDO*/

