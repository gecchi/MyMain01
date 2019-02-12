#ifndef FORMATIONTHAGORAS002_H_
#define FORMATIONTHAGORAS002_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/FormationThagoras.h"
#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�^�S���X�p�t�H�[���[�V��������002 .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras002 : public FormationThagoras {

public:
    GgafLib::SplineManufactureConnection** papSplManufConn_;

    FormationThagoras002(const char* prm_name);

    virtual void processBehavior() override;

    virtual void onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) override;

    virtual ~FormationThagoras002();
};

}
#endif /*FORMATIONTHAGORAS002_H_*/
