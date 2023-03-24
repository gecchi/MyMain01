#ifndef FORMATIONTHAGORAS_H_
#define FORMATIONTHAGORAS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機タゴラス用フォーメーションその１ .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras : public GgafLib::TreeFormation {

public:
    int cnt_called_up_row_;
    frame called_up_interval_;

    /** [r]出現座標(シーンが設定) */
    GgafDx::GeoElem entry_pos_;

    GgafDx::Scaler* pScaler4Sc_;
    GgafLib::DefaultGeometricActor* pActor4Sc_;

    XpmConnection* pXpmCon_;

public:
    FormationThagoras(const char* prm_name, const char* prm_xpm_id);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual void onCalledUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    /**
     * 出現座標を設定。
     * @param X
     * @param Y
     * @param Z
     */
    void setPosition(coord x, coord y, coord z) {
        entry_pos_.x = x;
        entry_pos_.y = y;
        entry_pos_.z = z;
    }

    GgafCore::Xpm* getXpm();

    virtual ~FormationThagoras();
};

}
#endif /*FORMATIONTHAGORAS_H_*/
