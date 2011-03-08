#ifndef MAGICPOINTITEM001_H_
#define MAGICPOINTITEM001_H_




namespace MyStg2nd {

/**
 * �A�C�e�� .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class MagicPointItem001 : public Item {
    /** �z���������W */
    int _kDX, _kDY, _kDZ;

public:
    MagicPointItem001(const char* prm_name);

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

//    int isOutOfView() override {
//        //��ʊO���薳��
//        return 0;
//    }
//
//    bool isOutOfUniverse() override {
//        //�Q�[�����W�͈͊O���薳��
//        return false;
//    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MagicPointItem001();
};

}
#endif /*MAGICPOINTITEM001_H_*/

