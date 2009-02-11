#ifndef FORMATIONJUNO001_H_
#define FORMATIONJUNO001_H_
namespace MyStg2nd {

#define NUM_JUNO_FORMATION001 20
/**
 * フォーメーションアクタークラス .
 */
class FormationJuno001 : public GgafDx9LibStg::FormationActor {

    EnemyJuno* _pEnemyJuno[NUM_JUNO_FORMATION001];
public:

    /** 全体のX */
    static int _X_FormationWhole;
    /** 全体のX増分 */
    static int _incX;

    FormationJuno001(const char* prm_name, const char* prm_model);

    virtual void initialize();

    void processBehavior();

    virtual ~FormationJuno001();
};

}
#endif /*FORMATIONJUNO001_H_*/
