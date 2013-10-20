#ifndef FORMATIONDELHEID001_H_
#define FORMATIONDELHEID001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Delheid/FormationDelheid.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機デルハイド用フォーメーション001グループ .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationDelheid001 : public FormationDelheid {

public:
    /** [r]設置座標と向き */
    GgafDxCore::GgafDxGeoElem geoLocate_;
    /** [r]スプライン情報オブジェクト資源への接続 */
    GgafLib::SplineManufactureConnection* pSplManufConnection_;

    FormationDelheid001(const char* prm_name);

    /**
     * 設置座標と向きをセット .
     * @param X
     * @param Y
     * @param Z
     * @param RZ
     * @param RY
     */
    void position(coord X, coord Y, coord Z,
                        angle RZ, angle RY) {
        geoLocate_.X = X;
        geoLocate_.Y = Y;
        geoLocate_.Z = Z;
        geoLocate_.RZ = RZ;
        geoLocate_.RY = RY;
    }

    /**
     * 編隊メンバーとして招集された瞬間に呼び出されるコールバック実装、設置座標と向きをセット。
     * @param pEnemyDelheid 招集された編隊メンバー
     */
    void onCallUpDelheid(EnemyDelheid* pEnemyDelheid) override;

    /**
     * スプライン情報オブジェクトを取得 .
     * @return スプライン情報オブジェクト
     */
    GgafLib::SplineManufacture* getSplManuf() override;

    /**
     * 振る舞い実装 .
     */
    virtual void processBehavior() override;

    virtual ~FormationDelheid001();
};

}
#endif /*FORMATIONDELHEID001_H_*/
