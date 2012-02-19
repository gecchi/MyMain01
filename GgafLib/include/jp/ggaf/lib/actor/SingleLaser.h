#ifndef SINGLELASER_H_
#define SINGLELASER_H_

namespace GgafLib {

/**
 * 単発レーザー .
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class SingleLaser : public GgafDxCore::GgafDxMeshSetActor {
public:

    D3DXHANDLE _ah_matWorld[26];
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pCollisionChecker;
    SingleLaser(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat=NULL);


    virtual void onCreateModel() override {}

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void drawHitArea() override;

    virtual ~SingleLaser();
};

}
#endif /*SINGLELASER_H_*/

