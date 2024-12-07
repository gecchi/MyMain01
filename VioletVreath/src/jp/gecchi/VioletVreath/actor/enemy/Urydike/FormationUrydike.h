#ifndef FORMATIONURYDIKE_H_
#define FORMATIONURYDIKE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機ウリュディケ用フォーメーションその１ .
 * @version 1.00
 * @since 2015/01/23
 * @author Masatoshi Tsuge
 */
class FormationUrydike : public VvFormationActor<GgafLib::TreeFormation> {

public:
    int num_Urydike_;

    int formation_col_num_;
    int formation_row_num_;
    frame summon_interval_;
    int summon_row_idx_;

    XpmConnection* pXpmCon_;

public:
    FormationUrydike(const char* prm_name, int prm_formation_col_num, int prm_formation_row_num, frame prm_summon_interval, void* prm_pFuncResetStatus);
    FormationUrydike(const char* prm_name, const char* prm_xpm_id, frame prm_summon_interval, void* prm_pFuncResetStatus);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

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

    virtual ~FormationUrydike();
};

}
#endif /*FORMATIONURYDIKE_H_*/
