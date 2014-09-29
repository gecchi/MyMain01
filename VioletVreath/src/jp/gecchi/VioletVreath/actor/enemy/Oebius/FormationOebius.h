#ifndef FORMATIONOEBIUS_H_
#define FORMATIONOEBIUS_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�G�r�E�X�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2013/09/17
 * @author Masatoshi Tsuge
 */
class FormationOebius : public GgafLib::TreeFormation {

public:
    int num_Oebius_;

    int formation_col_num_;
    int formation_row_num_;
    frame call_up_interval_;
    int call_up_row_cnt_;

    velo last_average_mv_velo_;
    /** [r]�o�����W(�V�[�����ݒ�) */
    GgafDxCore::GgafDxGeoElem entry_pos_;


public:
    FormationOebius(const char* prm_name, int prm_formation_col_num, int prm_formation_row_num, frame prm_call_up_interval);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_col, int prm_row) = 0;

    int getFormationColNum() {
        return formation_col_num_;
    }
    int getFormationRowNum() {
        return formation_row_num_;
    }

    int getLastAverageMvVelo() {
        return last_average_mv_velo_;
    }

    /**
     * �o�����W��ݒ�B
     * @param x
     * @param y
     * @param z
     */
    void position(coord x, coord y, coord z) {
        entry_pos_.x = x;
        entry_pos_.y = y;
        entry_pos_.z = z;
    }

    /**
     * �o��������ݒ�B
     * @param rz
     * @param ry
     */
    void setRzRyAng(angle rz,
                    angle ry) {
        entry_pos_.rz = rz;
        entry_pos_.ry = ry;
    }

    virtual ~FormationOebius();
};

}
#endif /*FORMATIONOEBIUS_H_*/
