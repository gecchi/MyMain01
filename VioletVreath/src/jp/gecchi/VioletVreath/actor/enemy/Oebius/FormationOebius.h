#ifndef FORMATIONOEBIUS_H_
#define FORMATIONOEBIUS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機エビウス用フォーメーションその１ .
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class FormationOebius : public GgafLib::TreeFormation {

public:
    EnemyOebiusController* pController_;


    /** [r]出現座標(シーンが設定) */
    GgafDx::GeoElem geo_;


public:
    FormationOebius(const char* prm_name, EnemyOebiusController* prm_pController);

    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

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

    virtual ~FormationOebius();
};

}
#endif /*FORMATIONOEBIUS_H_*/
