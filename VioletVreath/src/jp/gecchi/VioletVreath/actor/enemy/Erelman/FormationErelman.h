#ifndef FORMATIONERELMAN_H_
#define FORMATIONERELMAN_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * 敵機エレルマン用フォーメーションその１ .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class FormationErelman : public VvFormationActor<GgafLib::TreeFormation> {

public:
    EnemyErelmanController* pController_;

public:
    FormationErelman(const char* prm_name, EnemyErelmanController* prm_pController, void* prm_pFuncResetStatus);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) = 0;

    virtual void onSayonaraAll() override;

    void scatterMember();

    virtual ~FormationErelman();
};

}
#endif /*FORMATIONERELMAN_H_*/
