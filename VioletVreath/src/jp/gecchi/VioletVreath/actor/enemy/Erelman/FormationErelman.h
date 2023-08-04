#ifndef FORMATIONERELMAN_H_
#define FORMATIONERELMAN_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace VioletVreath {

/**
 * �G�@�G�����}���p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2018/06/11
 * @author Masatoshi Tsuge
 */
class FormationErelman : public VvFormationActor<GgafLib::TreeFormation> {

public:
    EnemyErelmanController* pController_;

    /** [r]�o�����W(�V�[�����ݒ�) */
    GgafDx::GeoElem geo_;

public:
    FormationErelman(const char* prm_name, EnemyErelmanController* prm_pController);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void onCalledUp(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) = 0;

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

    virtual ~FormationErelman();
};

}
#endif /*FORMATIONERELMAN_H_*/
