#ifndef FORMATIONURYDIKE002_H_
#define FORMATIONURYDIKE002_H_
#include "VioletVreath.h"
#include "FormationUrydike.h"

namespace VioletVreath {

/**
 * �G�@�E�����f�B�P�p�t�H�[���[�V��������002 .
 * @version 1.00
 * @since 2015/01/26
 * @author Masatoshi Tsuge
 */
class FormationUrydike002 : public FormationUrydike {

public:
    GgafLib::SplineManufactureConnection** papSplManufConn_;

    FormationUrydike002(const char* prm_name);

    virtual void processBehavior() override;
    virtual void onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) override;
    virtual void onFinshLeading(GgafDxCore::GgafDxDrawableActor* prm_pActor) override;

    virtual ~FormationUrydike002();
};

}
#endif /*FORMATIONURYDIKE002_H_*/
