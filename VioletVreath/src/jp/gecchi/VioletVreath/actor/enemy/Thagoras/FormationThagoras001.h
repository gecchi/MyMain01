#ifndef FORMATIONTHAGORAS001_H_
#define FORMATIONTHAGORAS001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/FormationThagoras.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * 敵機タゴラス用フォーメーションその001 .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras001 : public FormationThagoras {

public:
    static const char* xpmFormationThagoras001_[];

    GgafLib::SplineManufactureConnection** papSplManufConn_;


    /** [r]出現座標(フォーメーションオブジェクトが設定) */
    GgafDxCore::GgafDxGeoElem entry_pos_;

    FormationThagoras001(const char* prm_name);

    virtual void processBehavior() override;


    virtual void onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) override;

    void position(coord X, coord Y, coord Z) {
        entry_pos_._X = X;
        entry_pos_._Y = Y;
        entry_pos_._Z = Z;
    }


    virtual ~FormationThagoras001();
};

}
#endif /*FORMATIONTHAGORAS001_H_*/
