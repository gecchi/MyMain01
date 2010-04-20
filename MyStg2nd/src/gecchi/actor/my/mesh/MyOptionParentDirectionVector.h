#ifndef MYOPTIONPARENTDIRECTIONVECTOR_H_
#define MYOPTIONPARENTDIRECTIONVECTOR_H_
namespace MyStg2nd {

/**
 * �I�v�V�����̓Z�ߖ��N���X�̕����x�N�g���\�� .
 * @version 1.00
 * @since 2010/03/18
 * @author Masatoshi Tsuge
 */
class MyOptionParentDirectionVector : public GgafDx9LibStg::DefaultMeshActor {

public:
    int _ptn_no;

    MyOptionParentDirectionVector(const char* prm_name);

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


    virtual ~MyOptionParentDirectionVector();
};

}
#endif /*MYOPTIONPARENTDIRECTIONVECTOR_H_*/

