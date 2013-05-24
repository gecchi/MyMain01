#ifndef FORMATIONSAPPHO001B_H_
#define FORMATIONSAPPHO001B_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Sappho/FormationSappho001.h"

namespace VioletVreath {

/**
 * 敵機サッフォー用フォーメーションその001-b .
 * @version 1.00
 * @since 2013/03/18
 * @author Masatoshi Tsuge
 */
class FormationSappho001b : public FormationSappho001 {

public:
    FormationSappho001b(const char* prm_name);

    virtual void onCallUpSappho(EnemySappho* prm_pSappho, int prm_index) override;

    virtual ~FormationSappho001b();
};

}
#endif /*FORMATIONSAPPHO001B_H_*/
