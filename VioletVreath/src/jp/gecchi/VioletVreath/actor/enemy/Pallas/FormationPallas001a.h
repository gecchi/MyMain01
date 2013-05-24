#ifndef FORMATIONPALLAS001A_H_
#define FORMATIONPALLAS001A_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001.h"

namespace VioletVreath {

/**
 * 敵機パラス用フォーメーションその001-a .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationPallas001a : public FormationPallas001 {

public:
    FormationPallas001a(const char* prm_name);

    virtual void onCallUpPallas(EnemyPallas* prm_pPallas) override;

    virtual ~FormationPallas001a();
};

}
#endif /*FORMATIONPALLAS001A_H_*/
