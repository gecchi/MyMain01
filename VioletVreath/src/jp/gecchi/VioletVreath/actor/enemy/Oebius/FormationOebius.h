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

    int formation_row_num_;
    frame call_up_interval_;

    /** [r]�o�����W(�V�[�����ݒ�) */
    GgafDxCore::GgafDxGeoElem entry_pos_;


public:
    FormationOebius(const char* prm_name, int prm_formation_row_num);

    /**
     * �ґ����쐬 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row) = 0;

    int getFormationRowNum() {
        return formation_row_num_;
    }
    /**
     * �o�����W��ݒ�B
     * @param X
     * @param Y
     * @param Z
     */
    void position(coord x, coord y, coord z) {
        entry_pos_.x = x;
        entry_pos_.y = y;
        entry_pos_.z = z;
    }

    virtual ~FormationOebius();
};

}
#endif /*FORMATIONOEBIUS_H_*/
