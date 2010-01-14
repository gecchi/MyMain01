#ifndef SHOT001_H_
#define SHOT001_H_
namespace MyStg2nd {

/**
 * �ėp�G�e001(��) .
 * ���������ړ�<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot001 : public GgafDx9LibStg::DefaultMeshSetActor {
public:
    Shot001(const char* prm_name);

    void initialize();

    void onActive();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pOtherActor);

    virtual ~Shot001();
};

}
#endif /*SHOT001_H_*/

