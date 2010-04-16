#ifndef SHOT002_H_
#define SHOT002_H_
namespace MyStg2nd {

/**
 * 汎用弾002(小) .
 * 破壊可能で等速直線移動後、自機へ方向転換<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot002 : public GgafDx9LibStg::DefaultMeshSetActor {
public:
    /** 自機へ方向転換開始フレーム */
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

