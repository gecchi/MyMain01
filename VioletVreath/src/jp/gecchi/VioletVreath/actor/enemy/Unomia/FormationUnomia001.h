#ifndef FORMATIONUNOMIA001_H_
#define FORMATIONUNOMIA001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/FormationUnomia.h"

namespace VioletVreath {

/**
 * 敵機ウーノミア用フォーメーション001グループ .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia001 : public FormationUnomia {

public:
    FormationUnomia001(const char* prm_name);

    virtual void processBehavior() override;

    virtual ~FormationUnomia001();
};

}
#endif /*FORMATIONUNOMIA001_H_*/
