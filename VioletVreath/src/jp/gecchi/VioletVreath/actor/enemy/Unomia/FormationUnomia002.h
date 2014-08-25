#ifndef FORMATIONUNOMIA002_H_
#define FORMATIONUNOMIA002_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Unomia/FormationUnomia.h"

namespace VioletVreath {

/**
 * �G�@�E�[�m�~�A�p�t�H�[���[�V����002�O���[�v .
 * @version 1.00
 * @since 2011/02/14
 * @author Masatoshi Tsuge
 */
class FormationUnomia002 : public FormationUnomia {

public:

    FormationUnomia002(const char* prm_name);

    virtual void processBehavior() override;

    virtual ~FormationUnomia002();
};

}
#endif /*FORMATIONUNOMIA002_H_*/
