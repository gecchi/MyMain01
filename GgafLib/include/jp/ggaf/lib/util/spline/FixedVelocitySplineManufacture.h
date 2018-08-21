#ifndef GGAFLIB_FIXEDVELOCITYSPLINEMANUFACTURE_H_
#define GGAFLIB_FIXEDVELOCITYSPLINEMANUFACTURE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

namespace GgafLib {

/**
 * �����ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �S�ẴA�N�^�[�ɋ��ʂ���X�v���C���̏��͂����ɏW��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocitySplineManufacture : public SplineManufacture {

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
     * @param prm_coord_data_file �X�v���C�����W���t�@�C��
     * @param prm_angvelo_rzry_mv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g false)
     */
    FixedVelocitySplineManufacture(const char* prm_coord_data_file,
                                   angvelo prm_angvelo_rzry_mv = (D90ANG/9),
                                   int prm_turn_way = TURN_CLOSE_TO,
                                   bool prm_turn_optimaize = false );

    /**
     *
     * @param prm_pSplSrc �X�v���C�����W���I�u�W�F�N�g
     * @param prm_angvelo_rzry_mv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g false)
     */
    FixedVelocitySplineManufacture(SplineSource* prm_pSpl,
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
     * SplineLeader �I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� FixedVelocitySplineKurokoLeader �ł��B
     * @param prm_pKuroko �X�v���C���ړ����邽�߂̑��삷��I�u�W�F�N�g
     * @return SplineLeader �I�u�W�F�N�g
     */
    SplineLeader* createKurokoLeader(GgafDxCore::GgafDxKuroko* prm_pKuroko) override;

    virtual ~FixedVelocitySplineManufacture();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEMANUFACTURE_H_*/
