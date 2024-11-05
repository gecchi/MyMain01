#ifndef FORMATIONUNOMIA001B_H_
#define FORMATIONUNOMIA001B_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/FormationUnomia001.h"

namespace VioletVreath {

/**
 * 敵機ウーノミア用フォーメーションその001-b .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia001b : public FormationUnomia001 {

public:
    FormationUnomia001b(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    void onSummonUnomia(EnemyUnomia* pEnemyUnomia, int col) override;

    virtual ~FormationUnomia001b();
};

}
#endif /*FORMATIONUNOMIA001B_H_*/
