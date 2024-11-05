#ifndef FORMATIONERELMAN003_H_
#define FORMATIONERELMAN003_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/FormationErelman.h"
#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機エレルマン用フォーメーションその003 .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class FormationErelman003 : public FormationErelman {

public:
    int num_Erelman_;

    int formation_col_num_;
    int formation_row_num_;
    int summon_cnt_;
    frame* pa_spent_frames_;
    frame** papa_frame_of_summon_;

    int* pa_summon_row_idx_;
    GgafDx::CurveManufactureConnection** papCurveManufConn_;

    FormationErelman003(const char* prm_name, EnemyErelmanController* prm_pController);
    virtual void onActive() override;
    virtual void processBehavior() override;
    virtual void onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) override;
    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) override;
    int getFormationColNum() {
        return formation_col_num_;
    }
    int getFormationRowNum() {
        return formation_row_num_;
    }

    void freeMenber(frame prm_free_interval);

    virtual ~FormationErelman003();
};

}
#endif /*FORMATIONERELMAN003_H_*/
