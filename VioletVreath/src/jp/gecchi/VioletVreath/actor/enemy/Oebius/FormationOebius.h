#ifndef FORMATIONOEBIUS_H_
#define FORMATIONOEBIUS_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機エビウス用フォーメーションその１ .
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class FormationOebius : public VvFormationActor<GgafLib::TreeFormation> {

public:
    EnemyOebiusController* pController_;

public:
    FormationOebius(const char* prm_name, EnemyOebiusController* prm_pController, void* prm_pFuncResetStatus);

    virtual void onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) = 0;

    virtual void onSayonaraAll() override;

    void scatterMember();

    virtual ~FormationOebius();
};

}
#endif /*FORMATIONOEBIUS_H_*/
