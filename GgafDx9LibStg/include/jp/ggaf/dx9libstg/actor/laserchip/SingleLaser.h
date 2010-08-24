#ifndef SINGLELASER_H_
#define SINGLELASER_H_

namespace GgafDx9LibStg {

/**
 * 単発レーザー .
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class SingleLaser : public GgafDx9Core::GgafDx9MeshSetActor {
public:

    D3DXHANDLE _ah_matWorld[27];
    CollisionChecker* _pCollisionChecker;
    SingleLaser(const char* prm_name, const char* prm_model_id);


    virtual void onCreateModel() override {}

    virtual void processDraw() override;

    virtual void processFinal() override {
    }

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void drawHitArea() override;

    virtual ~SingleLaser();
};

}
#endif /*SINGLELASER_H_*/

