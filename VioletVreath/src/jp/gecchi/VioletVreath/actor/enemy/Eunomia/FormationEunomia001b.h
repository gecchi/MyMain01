#ifndef FORMATIONEUNOMIA001B_H_
#define FORMATIONEUNOMIA001B_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia001.h"

namespace VioletVreath {

/**
 * 敵機エウノミア用フォーメーションその001-b .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia001b : public FormationEunomia001 {

public:
    FormationEunomia001b(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    void onCallUpEunomia(EnemyEunomia* pEnemyEunomia, int col) override;

    virtual ~FormationEunomia001b();
};

}
#endif /*FORMATIONEUNOMIA001B_H_*/
