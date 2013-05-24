#ifndef FORMATIONEUNOMIA002B_H_
#define FORMATIONEUNOMIA002B_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia002.h"

namespace VioletVreath {

/**
 * 敵機エウノミア用フォーメーションその002-b .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia002b : public FormationEunomia002 {

public:
    FormationEunomia002b(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    void onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) override;

    virtual ~FormationEunomia002b();
};

}
#endif /*FORMATIONEUNOMIA002B_H_*/
