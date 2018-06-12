#ifndef FORMATIONERELMAN001_H_
#define FORMATIONERELMAN001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/FormationErelman.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機エレルマン用フォーメーションその001 .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class FormationErelman001 : public FormationErelman {

public:
    int num_Erelman_;

    int formation_col_num_;
    int formation_row_num_;
    frame call_up_interval_base_;
    int call_up_cnt_;

    frame* pa_call_up_interval_;
    int* pa_call_up_row_idx_;

    GgafLib::SplineManufactureConnection** papSplManufConn_;

    FormationErelman001(const char* prm_name, EnemyErelmanController* prm_pController);
    virtual void onActive() override;
    virtual void processBehavior() override;
    virtual void onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) override;
    virtual void onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) override;
    int getFormationColNum() {
        return formation_col_num_;
    }
    int getFormationRowNum() {
        return formation_row_num_;
    }
    virtual ~FormationErelman001();
};

}
#endif /*FORMATIONERELMAN001_H_*/
