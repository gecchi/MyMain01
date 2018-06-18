#ifndef FORMATIONOEBIUS002_H_
#define FORMATIONOEBIUS002_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Oebius/FormationOebius.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機エビウス用フォーメーションその002 .
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class FormationOebius002 : public FormationOebius {

    int num_Oebius_;

    int formation_col_num_;
    int formation_row_num_;
    int call_up_row_idx_;
    frame* pa_frame_of_call_up_;
    XpmConnection* pXpmConnection_;
public:
    GgafLib::SplineManufactureConnection** papSplManufConn_;

    FormationOebius002(const char* prm_name, EnemyOebiusController* prm_pController);

    virtual void onActive() override;
    virtual void processBehavior() override;

    virtual void onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) override;

    virtual void onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) override;

    virtual ~FormationOebius002();
};

}
#endif /*FORMATIONOEBIUS002_H_*/
