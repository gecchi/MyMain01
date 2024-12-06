#ifndef FORMATIONZAKO_H_
#define FORMATIONZAKO_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/FkFormation.h"

#include "jp/ggaf/dx/util/GeoElem.h"

namespace Mogera {

/**
 * �G�@�G���p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2015/01/23
 * @author Masatoshi Tsuge
 */
class FormationParaCurve : public GgafLib::FkFormation {

public:
    int num_Zako_;

    int formation_col_num_;
    int formation_row_num_;
    frame summon_interval_;
    int summon_row_idx_;

    /** [r]�o�����W(�V�[�����ݒ�) */
    GgafDx::GeoElem entry_pos_;

    void addMember(int prm_formation_col_num, int prm_formation_row_num, frame prm_summon_interval);

public:
    FormationParaCurve(const char* prm_name);

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafDx::GeometricActor* prm_pActor_last_destroyed) override;

    virtual void onSummon(GgafDx::FigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    virtual void onFinshLeading(GgafDx::FigureActor* prm_pActor) = 0;

    virtual void onSayonaraAll() override;


    /**
     * �o�����W��ݒ�B
     * @param x
     * @param y
     * @param z
     */
    void setPosition(coord x, coord y, coord z) {
        entry_pos_.x = x;
        entry_pos_.y = y;
        entry_pos_.z = z;
    }

    /**
     * �o��������ݒ�B
     * @param rz
     * @param ry
     */
    void setRzRyAng(angle rz, angle ry) {
        entry_pos_.rz = rz;
        entry_pos_.ry = ry;
    }

    virtual ~FormationParaCurve();
};

}
#endif /*FORMATIONZAKO_H_*/
