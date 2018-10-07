#ifndef FORMATIONERELMAN002_H_
#define FORMATIONERELMAN002_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Erelman/FormationErelman.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�G�����}���p�t�H�[���[�V��������002 .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class FormationErelman002 : public FormationErelman {

public:
    int num_Erelman_;

    int formation_col_num_;
    int formation_row_num_;
    int call_up_cnt_;
    frame* pa_spent_frames_;
    frame** papa_frame_of_call_up_;

    int* pa_call_up_row_idx_;
    GgafLib::SplineManufactureConnection** papSplManufConn_;

    FormationErelman002(const char* prm_name, EnemyErelmanController* prm_pController);
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
    virtual ~FormationErelman002();
};

}
#endif /*FORMATIONERELMAN002_H_*/