#ifndef SHOT002_H_
#define SHOT002_H_
namespace MyStg2nd {

/**
 * ”Ä—p“G’e001(¬) .
 * “™‘¬’¼üˆÚ“®<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot002 : public GgafDx9LibStg::DefaultMeshSetActor {
public:
    DWORD _my_frame;

    Shot002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~Shot002();
};

}
#endif /*SHOT002_H_*/

