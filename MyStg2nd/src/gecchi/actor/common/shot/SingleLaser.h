#ifndef SINGLELASER_H_
#define SINGLELASER_H_
namespace MyStg2nd {

/**
 * îƒópíe003(è¨) .
 * îjâÛïsâ¬î\Ç≈ìôë¨íºê¸à⁄ìÆ<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class SingleLaser : public GgafDx9Core::GgafDx9MeshSetActor {
public:

    D3DXHANDLE _ahMatWorld[24];
    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;
    SingleLaser(const char* prm_name);

    void onCreateModel() override {
    }
    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processDraw() override;

    void processFinal() override {
    }
    void processHappen(int prm_no) override {
    }
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void drawHitArea() override;

    virtual ~SingleLaser();
};

}
#endif /*SINGLELASER_H_*/

