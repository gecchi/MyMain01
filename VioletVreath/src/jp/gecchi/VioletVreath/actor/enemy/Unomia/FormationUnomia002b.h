#ifndef FORMATIONUNOMIA002B_H_
#define FORMATIONUNOMIA002B_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/FormationUnomia002.h"

namespace VioletVreath {

/**
 * 敵機ウーノミア用フォーメーションその002-b .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia002b : public FormationUnomia002 {

public:
    FormationUnomia002b(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    void onSummonUnomia(EnemyUnomia* pEnemyUnomia, int col) override;

    virtual ~FormationUnomia002b();
};

}
#endif /*FORMATIONUNOMIA002B_H_*/
