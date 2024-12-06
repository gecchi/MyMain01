#ifndef FORMATIONIDA_H_
#define FORMATIONIDA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/FkFormation.h"

namespace VioletVreath {

/**
 * 敵機イーダ用フォーメーション基底 .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class FormationIda : public VvFormationActor<GgafLib::FkFormation> {

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_ldr_id 曲線移動の情報ID(XXX.ldr の XXX)
     */
    FormationIda(const char* prm_name, void* prm_pFuncResetStatus) ;

    virtual void onActive() override;

    virtual void onSummonIda(EnemyIda* pEnemyIda) = 0;

    virtual ~FormationIda();
};

}
#endif /*FORMATIONIDA_H_*/
