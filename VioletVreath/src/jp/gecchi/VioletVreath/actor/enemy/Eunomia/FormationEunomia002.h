#ifndef FORMATIONEUNOMIA002_H_
#define FORMATIONEUNOMIA002_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia.h"

namespace VioletVreath {

/**
 * 敵機エウノミア用フォーメーション002グループ .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationEunomia002 : public FormationEunomia {

public:

    FormationEunomia002(const char* prm_name);

    virtual void processBehavior() override;

    virtual ~FormationEunomia002();
};

}
#endif /*FORMATIONEUNOMIA002_H_*/
