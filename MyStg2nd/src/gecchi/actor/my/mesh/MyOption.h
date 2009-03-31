#ifndef MYOPTION_H_
#define MYOPTION_H_
namespace MyStg2nd {

class MyOption : public GgafDx9LibStg::DefaultMeshActor {

public:
    /** ���@�ւ̃|�C���^ */
    MyShip* _pMyShip;
    MyOptionParent* _pMyOptionParent;
    /** �I�v�V�����ԍ� */
    int _no;

    /** MyShip����̋��� */
    int _distR;
    /** �ʒu�i���͊p�j */
    GgafDx9Core::angle _angPosRotX;

    GgafDx9Core::angle _sangvelo;
    MyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    /**
     * ��OverRide �ł���
     */
    void processBehavior();

    /**
     * ��OverRide �ł���
     */
    void processJudgement();

    /**
     * ��OverRide �ł���
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


    virtual ~MyOption();
};

}
#endif /*MYOPTION_H_*/

