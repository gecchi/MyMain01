#ifndef MYOPTIONCONTROLLERDIRECTIONVECTOR_H_
#define MYOPTIONCONTROLLERDIRECTIONVECTOR_H_
namespace MyStg2nd {

/**
 * �I�v�V�����̓Z�ߖ��N���X�̕����x�N�g���\�� .
 * @version 1.00
 * @since 2010/03/18
 * @author Masatoshi Tsuge
 */
class MyOptionControllerDirectionVector : public GgafLib::DefaultMeshActor {

public:
    int _ptn_no;

    MyOptionControllerDirectionVector(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }

    void onInactive() override;

    int isOutOfView() override {
        //��ʊO���薳��
        return 0;
    }

    bool isOutOfUniverse() override {
        //�Q�[�����W�͈͊O���薳��
        return false;
    }


    virtual ~MyOptionControllerDirectionVector();
};

}
#endif /*MYOPTIONCONTROLLERDIRECTIONVECTOR_H_*/

