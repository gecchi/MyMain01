#ifndef MAGICPOINTITEM_H_
#define MAGICPOINTITEM_H_

namespace MyStg2nd {

/**
 * MP�񕜃A�C�e���� .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class MagicPointItem : public Item {
    /** �z���������W */
    int _kDX, _kDY, _kDZ;

public:
    MagicPointItem(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

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
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MagicPointItem();
};

}
#endif /*MAGICPOINTITEM_H_*/

