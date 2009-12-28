#ifndef SHOT001_H_
#define SHOT001_H_
namespace MyStg2nd {

/**
 * 3D“G’e001 .
 * “™‘¬‚Å‚Ü‚Á‚·‚®”ò‚Ô<BR>
 */
class Shot001 : public GgafDx9LibStg::DefaultMeshSetActor {
public:
    Shot001(const char* prm_name);

    void initialize();

    void onActive();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    virtual ~Shot001();
};

}
#endif /*SHOT001_H_*/

