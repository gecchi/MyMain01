#ifndef GGAF_DX_FIXEDVELOCITYCURVEMANUFACTURE_H_
#define GGAF_LDX_FIXEDVELOCITYCURVEMANUFACTURE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

namespace GgafDx {

/**
 * �����ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �S�ẴA�N�^�[�ɋ��ʂ���X�v���C���̏��͂����ɏW��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocityCurveManufacture : public CurveManufacture {

public:
    /** [r]�n�_����n�Ԗڂ̕⊮�_(��_���܂�)���B�ɕK�v�ȃt���[�����̃e�[�u�� */
    float* _paFrame_need_at;
    /** [r]����x */
    velo _velo_mvUnit;
    /** [rw]1�t���[�����������\�ȉ�]�p�p���x */
    angvelo _angvelo_rzry_mv;
        /** [rw]������@ */
    int _turn_way;
    /** [rw]����œK���L�� */
    bool _turn_optimize;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_coord_spl_file �X�v���C�����W���t�@�C��
     * @param prm_angvelo_rzry_mv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g false)
     */
    FixedVelocityCurveManufacture(const char* prm_coord_spl_file,
                                  angvelo prm_angvelo_rzry_mv = (D90ANG/9),
                                  int prm_turn_way = TURN_CLOSE_TO,
                                  bool prm_turn_optimaize = false );

    /**
     *
     * @param prm_pCurveSrc �X�v���C�����W���I�u�W�F�N�g
     * @param prm_angvelo_rzry_mv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g false)
     */
    FixedVelocityCurveManufacture(CurveSource* prm_pCurve,
                                  angvelo prm_angvelo_rzry_mv = (D90ANG/9),
                                  int prm_turn_way = TURN_CLOSE_TO,
                                  bool prm_turn_optimaize = false );

    /**
     * �������i�v�Z�j���� .
     * �v���p�e�B��ύX�����ꍇ�A�����e�[�u�������X�V���邽�߂�
     * ��x���s����K�v������܂��B
     */
    void calculate() override;

    /**
     * VehicleLeader �I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� FixedVelocityCurveVecVehicleLeader �ł��B
     * @param prm_pVecVehicle �J�[�u�ړ����邽�߂̑��삷��I�u�W�F�N�g
     * @return VehicleLeader �I�u�W�F�N�g
     */
    VehicleLeader* createVecVehicleLeader(GgafDx::VecVehicle* prm_pVecVehicle) override;

    virtual ~FixedVelocityCurveManufacture();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVEMANUFACTURE_H_*/
