#ifndef FORMATIONUNOMIA002A_H_
#define FORMATIONUNOMIA002A_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/FormationUnomia002.h"

namespace VioletVreath {

/**
 * 敵機ウーノミア用フォーメーションその002-a .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia002a : public FormationUnomia002 {

public:
    FormationUnomia002a(const char* prm_name);

    /**
     * 調整 .
     */
    void onSummonUnomia(EnemyUnomia* pEnemyUnomia, int col) override;

    virtual ~FormationUnomia002a();
};

}
#endif /*FORMATIONUNOMIA002A_H_*/
