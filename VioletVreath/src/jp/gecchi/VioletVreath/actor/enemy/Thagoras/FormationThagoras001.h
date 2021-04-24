#ifndef FORMATIONTHAGORAS001_H_
#define FORMATIONTHAGORAS001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/FormationThagoras.h"
#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�^�S���X�p�t�H�[���[�V��������001 .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras001 : public FormationThagoras {

public:
    GgafDx::CurveManufactureConnection** papCurveManufConn_;

    FormationThagoras001(const char* prm_name);

    virtual void processBehavior() override;


    virtual void onCallUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) override;

    virtual ~FormationThagoras001();
};

}
#endif /*FORMATIONTHAGORAS001_H_*/
