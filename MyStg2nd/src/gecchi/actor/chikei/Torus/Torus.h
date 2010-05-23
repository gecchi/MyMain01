#ifndef TORUS_H_
#define TORUS_H_
namespace MyStg2nd {

/**
 * 地形トーラス .
 * 最初に作った地形
 * @version 1.00
 * @since 2010/05/08
 * @author Masatoshi Tsuge
 */
class Torus : public GroundMeshActor {

public:
    /** トーラス半径1(輪) */
    int _r1;
    /** トーラス半径1(太さ) */
    int _r2;



    Torus(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    bool isOffScreen() {
        return 0;
    }

    bool isOutOfGameSpace() {
		if (GgafDx9Core::GgafDx9Universe::_X_goneLeft < _X) {
            return false;
        } else {
            return true;
        }
    }
    virtual ~Torus();
};

}
#endif /*TORUS_H_*/

