#ifndef FORMATIONORTUNA001B_H_
#define FORMATIONORTUNA001B_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/FormationOrtuna001.h"
#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * オルトゥナ用フォーメーションその001-b .
 * @version 1.00
 * @since 2013/08/05
 * @author Masatoshi Tsuge
 */
class FormationOrtuna001b : public FormationOrtuna001 {

public:
    /** フォーメーション基点座標 */
    GgafDx::GeoElem pos_;

public:
    FormationOrtuna001b(const char* prm_name);

    /**
     * 基点座標セット。
     * onSummonOrtuna() の初回時一回実行される
     * @param X
     * @param Y
     * @param Z
     */
    void setPosition(coord x, coord y, coord z) {
        pos_.x = x;
        pos_.y = y;
        pos_.z = z;
    }

    virtual void onSummonOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) override;

    virtual ~FormationOrtuna001b();
};

}
#endif /*FORMATIONORTUNA001B_H_*/
