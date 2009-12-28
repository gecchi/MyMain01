#ifndef SHOT002_H_
#define SHOT002_H_
namespace MyStg2nd {

/**
 * 3D“G’e002 .
 * “™‘¬‚Å‚Ü‚Á‚·‚®”ò‚Ô<BR>
 */
class Shot002 : public GgafDx9LibStg::DefaultMeshSetActor {
public:
    Shot002(const char* prm_name);

    void initialize();

    void onActive();

    void processBehavior();

    void processJudgement();

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    virtual ~Shot002();
};

}
#endif /*SHOT002_H_*/

