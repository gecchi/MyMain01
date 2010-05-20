#ifndef TORUS_H_
#define TORUS_H_
namespace MyStg2nd {

/**
 * �n�`�g�[���X .
 * �ŏ��ɍ�����n�`
 * @version 1.00
 * @since 2010/05/08
 * @author Masatoshi Tsuge
 */
class Torus : public GroundMeshActor {

public:
    Torus(const char* prm_name);
    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

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
