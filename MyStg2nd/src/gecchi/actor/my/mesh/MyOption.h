#ifndef MYOPTION_H_
#define MYOPTION_H_
namespace MyStg2nd {

class MyOption : public GgafDx9LibStg::DefaultMeshActor {

public:

    GgafDx9Core::angle _angRzMove_ParentPrev;
    GgafDx9Core::angle _angRyMove_ParentPrev;
    GgafDx9Core::angvelo _angveloRzMove_ParentPrev;
    GgafDx9Core::angvelo _angveloRyMove_ParentPrev;
    int _X_ParentPrev;
    int _Y_ParentPrev;
    int _Z_ParentPrev;
    double _vX_ParentPrev;
    double _vY_ParentPrev;
    double _vZ_ParentPrev;

    /** 自機へのポインタ */
    MyDummyOption* _pMyDummyOption;
    /** オプション番号 */
    int _no;

    /** 位置（周囲角） */
    MyOption(const char* prm_name, int prm_no, MyDummyOption* prm_pMyOptionParent);

    /**
     * ＜OverRide です＞
     */
    void initialize();

    /**
     * ＜OverRide です＞
     */
    void processBehavior();

    /**
     * ＜OverRide です＞
     */
    void processJudgement();

    /**
     * ＜OverRide です＞
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


    virtual ~MyOption();
};

}
#endif /*MYOPTION_H_*/

