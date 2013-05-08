#ifndef FORMATIONADELHEID001_H_
#define FORMATIONADELHEID001_H_

namespace VioletVreath {

/**
 * 敵機アーデルハイド用フォーメーション001グループ .
 * @version 1.00
 * @since 2013/04/15
 * @author Masatoshi Tsuge
 */
class FormationAdelheid001 : public FormationAdelheid {

public:
    /** [r]設置座標と向き */
    GgafDxCore::GgafDxGeoElem geoLocate_;
    /** [r]スプライン情報オブジェクト資源への接続 */
    GgafLib::SplineManufactureConnection* pSplManufConnection_;

    FormationAdelheid001(const char* prm_name);

    /**
     * 設置座標と向きをセット .
     * @param X
     * @param Y
     * @param Z
     * @param RZ
     * @param RY
     */
    void locate(coord X, coord Y, coord Z,
                        angle RZ, angle RY) {
        geoLocate_._X = X;
        geoLocate_._Y = Y;
        geoLocate_._Z = Z;
        geoLocate_._RZ = RZ;
        geoLocate_._RY = RY;
    }

    /**
     * 編隊メンバーとして招集された瞬間に呼び出されるコールバック実装、設置座標と向きをセット。
     * @param pEnemyAdelheid 招集された編隊メンバー
     */
    void onCallUpAdelheid(EnemyAdelheid* pEnemyAdelheid) override;

    /**
     * スプライン情報オブジェクトを取得 .
     * @return スプライン情報オブジェクト
     */
    GgafLib::SplineManufacture* getSplManuf() override;

    /**
     * 振る舞い実装 .
     */
    virtual void processBehavior() override;

    virtual ~FormationAdelheid001();
};

}
#endif /*FORMATIONADELHEID001_H_*/
