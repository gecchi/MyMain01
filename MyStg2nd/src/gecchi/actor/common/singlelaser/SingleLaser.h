#ifndef SINGLELASER_H_
#define SINGLELASER_H_
namespace MyStg2nd {

/**
 * ”Ä—p’e003(¬) .
 * ”j‰ó•s‰Â”\‚Å“™‘¬’¼üˆÚ“®<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class SingleLaser : public GgafDx9Core::GgafDx9MeshSetActor {
public:

    D3DXHANDLE _ahMatWorld[24];
    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;
    SingleLaser(const char* prm_name, const char* prm_model_id);

    virtual void onCreateModel() override {
    }

    virtual void processDraw() override;

    virtual void processFinal() override {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void drawHitArea() override;

    virtual ~SingleLaser();
};

}
#endif /*SINGLELASER_H_*/

