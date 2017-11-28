#ifndef FORMATIONURYDIKE_H_
#define FORMATIONURYDIKE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�E�����f�B�P�p�t�H�[���[�V�������̂P .
 * @version 1.00
 * @since 2015/01/23
 * @author Masatoshi Tsuge
 */
class FormationUrydike : public GgafLib::TreeFormation {

public:
    int num_Urydike_;

    int formation_col_num_;
    int formation_row_num_;
    frame call_up_interval_;
    int call_up_row_cnt_;

    /** [r]�o�����W(�V�[�����ݒ�) */
    GgafDxCore::GgafDxGeoElem entry_pos_;

    XpmConnection* pXpmConnection_;

public:
    FormationUrydike(const char* prm_name, int prm_formation_col_num, int prm_formation_row_num, frame prm_call_up_interval);
    FormationUrydike(const char* prm_name, const char* prm_xpm_id, frame prm_call_up_interval);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void onCallUp(GgafDxCore::GgafDxFigureActor* prm_pActor, int prm_row, int prm_col) = 0;

    virtual void onFinshLeading(GgafDxCore::GgafDxFigureActor* prm_pActor) = 0;

    virtual void onSayonaraAll() override;

    void scatterMember();

    int getFormationColNum() {
        return formation_col_num_;
    }
    int getFormationRowNum() {
        return formation_row_num_;
    }

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

    virtual ~FormationUrydike();
};

}
#endif /*FORMATIONURYDIKE_H_*/
