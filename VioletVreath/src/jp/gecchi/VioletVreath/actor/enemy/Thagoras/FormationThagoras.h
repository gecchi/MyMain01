#ifndef FORMATIONTHAGORAS_H_
#define FORMATIONTHAGORAS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機タゴラス用フォーメーションその１ .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras : public VvFormationActor<GgafLib::TreeFormation> {

public:
    int cnt_summon_row_;
    frame summon_interval_;

    GgafDx::Scaler* pScaler4Sc_;
    GgafLib::DefaultGeometricActor* pActor4Sc_;

    XpmConnection* pXpmCon_;

public:
    FormationThagoras(const char* prm_name, const char* prm_xpm_id, void* prm_pFuncResetStatus);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    GgafCore::Xpm* getXpm();

    virtual ~FormationThagoras();
};

}
#endif /*FORMATIONTHAGORAS_H_*/
