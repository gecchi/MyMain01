#ifndef FORMATIONGERIA_H_
#define FORMATIONGERIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * フォーメーションアクタークラス .
 * 自身は出現ポイントの中心
 */
class FormationGeria : public GgafLib::DefaultGeometricActor {


public:
    /** ゲリアストック */
    GgafCore::ActorDepository* pDepo_;

public:

    FormationGeria(const char* prm_name, int prm_nGeriaStock);


    EnemyGeria* summonGeria();

    virtual ~FormationGeria();
};

}
#endif /*FORMATIONGERIA_H_*/
