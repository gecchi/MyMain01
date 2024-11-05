#ifndef FORMATIONPARACURVE_H_
#define FORMATIONPARACURVE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace Mogera {

/**
 * 敵機雑魚用フォーメーションその１ .
 * @version 1.00
 * @since 2015/01/23
 * @author Masatoshi Tsuge
 */
class FormationZako : public GgafLib::TreeFormation {

public:
    int num_Zako_;

    int formation_col_num_;
    int formation_row_num_;
    frame summon_interval_;
    int summon_row_idx_;

    /** [r]出現座標(シーンが設定) */
    GgafDx::GeoElem entry_pos_;

    void addMember(int prm_formation_col_num, int prm_formation_row_num, frame prm_summon_interval);

public:
    FormationZako(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual void onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) = 0;

    virtual void onSayonaraAll() override;

    void scatterMember();

    int getFormationColNum() {
        return formation_col_num_;
    }
    int getFormationRowNum() {
        return formation_row_num_;
    }

    /**
     * 出現座標を設定。
     * @param x
     * @param y
     * @param z
     */
    void setPosition(coord x, coord y, coord z) {
        entry_pos_.x = x;
        entry_pos_.y = y;
        entry_pos_.z = z;
    }

    /**
     * 出現方向を設定。
     * @param rz
     * @param ry
     */
    void setRzRyAng(angle rz, angle ry) {
        entry_pos_.rz = rz;
        entry_pos_.ry = ry;
    }

    virtual ~FormationZako();
};

}
#endif /*FORMATIONZAKO_H_*/
