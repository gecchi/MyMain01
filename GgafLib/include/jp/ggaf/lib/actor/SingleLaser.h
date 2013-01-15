#ifndef SINGLELASER_H_
#define SINGLELASER_H_

namespace GgafLib {

/**
 * 単発レーザー .
 * GgafDxCore::GgafDxMeshSetActorと同様に複数モデル描画により、高速化を目論む。 <BR>
 * 但し表示時に、マテリアルカラー、スペキュラーの計算を行わない。<BR>
 * その代わりに、GgafDxCore::GgafDxMeshSetActor よりもさらに多くのセット数（現在26）をサポート。<BR>
 * 大量表示用に最適化されている。<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class SingleLaser : public GgafDxCore::GgafDxMeshSetActor {
public:

    D3DXHANDLE _ah_matWorld[26];
    /** 衝突判定支援オブジェクト */
    CollisionChecker3D* _pColliChecker;
    SingleLaser(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat=nullptr);


    virtual void onCreateModel() override {}

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void drawHitArea() override;

    virtual ~SingleLaser();
};

}
#endif /*SINGLELASER_H_*/

