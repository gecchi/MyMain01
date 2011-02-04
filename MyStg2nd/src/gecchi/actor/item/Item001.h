#ifndef ITEM001_H_
#define ITEM001_H_

namespace MyStg2nd {

/**
 * �A�C�e�� .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class Item001 : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    Item001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

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

    virtual ~Item001();
};

}
#endif /*ITEM001_H_*/

