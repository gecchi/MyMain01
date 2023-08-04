#ifndef FORMATIONERELMAN_H_
#define FORMATIONERELMAN_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機エレルマン用フォーメーションその１ .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class FormationErelman : public VvFormationActor<GgafLib::TreeFormation> {

public:
    EnemyErelmanController* pController_;

    /** [r]出現座標(シーンが設定) */
    GgafDx::GeoElem geo_;

public:
    FormationErelman(const char* prm_name, EnemyErelmanController* prm_pController);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onCalledUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) = 0;

    virtual void onSayonaraAll() override;

    void scatterMember();


    /**
     * 出現座標を設定。
     * @param x
     * @param y
     * @param z
     */
    void setPosition(coord x, coord y, coord z) {
        geo_.x = x;
        geo_.y = y;
        geo_.z = z;
    }

    /**
     * 方向を設定。
     */
    void setAng(angle rx, angle ry, angle rz) {
        geo_.rx = rx;
        geo_.ry = ry;
        geo_.rz = rz;
    }

    virtual ~FormationErelman();
};

}
#endif /*FORMATIONERELMAN_H_*/
