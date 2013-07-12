#ifndef FORMATIONTHAGORAS001_H_
#define FORMATIONTHAGORAS001_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/FormationThagoras.h"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �G�@�^�S���X�p�t�H�[���[�V��������001 .
 * @version 1.00
 * @since 2013/07/10
 * @author Masatoshi Tsuge
 */
class FormationThagoras001 : public FormationThagoras {

public:
    static uint32_t bitmap_[96];

    static char pixmap_[8][9];

    GgafLib::SplineManufactureConnection* apSplManufConn_[8];

    /** �s�Ԋu */
    frame row_interval_frames_;
    /** ��Ԋu */
    coord column_dY_;


    int cnt_call_up_line_;

    /** [r]�o�����W(�t�H�[���[�V�����I�u�W�F�N�g���ݒ�) */
    GgafDxCore::GgafDxGeoElem entry_pos_;

    FormationThagoras001(const char* prm_name);

    virtual void processBehavior() override;

    void position(coord X, coord Y, coord Z) {
        entry_pos_._X = X;
        entry_pos_._Y = Y;
        entry_pos_._Z = Z;
    }


    virtual ~FormationThagoras001();
};

}
#endif /*FORMATIONTHAGORAS001_H_*/
