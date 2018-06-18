#ifndef FORMATIONOEBIUS_H_
#define FORMATIONOEBIUS_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�G�r�E�X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2014/09/17
 * @author Masatoshi Tsuge
 */
class FormationOebius : public GgafLib::TreeFormation {

public:
    EnemyOebiusController* pController_;


    /** [r]�o�����W(�V�[�����ݒ�) */
    GgafDxCore::GgafDxGeoElem geo_;


public:
    FormationOebius(const char* prm_name, EnemyOebiusController* prm_pController);

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    virtual void onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) = 0;

    virtual void onSayonaraAll() override;

    void scatterMember();

    /**
     * �o�����W��ݒ�B
     * @param x
     * @param y
     * @param z
     */
    void setPosition(coord x, coord y, coord z) {
        geo_.x = x;
        geo_.y = y;
        geo_.z = z;
    }

    /**
     * ������ݒ�B
     */
    void setAng(angle rx, angle ry, angle rz) {
        geo_.rx = rx;
        geo_.ry = ry;
        geo_.rz = rz;
    }

    virtual ~FormationOebius();
};

}
#endif /*FORMATIONOEBIUS_H_*/
