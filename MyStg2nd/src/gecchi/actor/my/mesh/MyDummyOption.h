#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

class MyDummyOption : public GgafDx9LibStg::DefaultMeshActor {

public:

    int _X_ParentPrev;
    int _Y_ParentPrev;
    int _Z_ParentPrev;

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


    GgafDx9Core::angvelo _angvelo;
    MyDummyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent);

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


    virtual ~MyDummyOption();
};

}
#endif /*MYDUMMYOPTION_H_*/

