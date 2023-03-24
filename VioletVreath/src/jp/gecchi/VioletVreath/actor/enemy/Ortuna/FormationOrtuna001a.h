#ifndef FORMATIONORTUNA001A_H_
#define FORMATIONORTUNA001A_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ortuna/FormationOrtuna001.h"

namespace VioletVreath {

/**
 * オルトゥナ用フォーメーションその001-a .
 * @version 1.00
 * @since 2013/08/05
 * @author Masatoshi Tsuge
 */
class FormationOrtuna001a : public FormationOrtuna001 {

public:
    FormationOrtuna001a(const char* prm_name);

    virtual void onCalledUpOrtuna(EnemyOrtuna* prm_pOrtuna, int prm_index) override;

    virtual ~FormationOrtuna001a();
};

}
#endif /*FORMATIONORTUNA001A_H_*/
