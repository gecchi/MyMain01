#ifndef FORMATIONORTUNA001B_H_
#define FORMATIONORTUNA001B_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/FormationOrtuna001.h"

namespace VioletVreath {

/**
 * オルトゥナ用フォーメーションその001-b .
 * @version 1.00
 * @since 2013/08/05
 * @author Masatoshi Tsuge
 */
class FormationOrtuna001b : public FormationOrtuna001 {

public:
    FormationOrtuna001b(const char* prm_name);

    virtual void onSummonOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) override;

    virtual ~FormationOrtuna001b();
};

}
#endif /*FORMATIONORTUNA001B_H_*/
