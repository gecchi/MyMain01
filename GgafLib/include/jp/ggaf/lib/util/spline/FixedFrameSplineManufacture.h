#ifndef GGAFLIB_FIXEDFRAMESPLINEMANUFACTURE_H_
#define GGAFLIB_FIXEDFRAMESPLINEMANUFACTURE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

namespace GgafLib {

/**
 * ��ԌŒ莞�ԁi�t���[���j�ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �S�ẴA�N�^�[�ɋ��ʂ���X�v���C���̏��͂����ɏW��B
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameSplineManufacture : public SplineManufacture {

public:
    /** [r]�P��Ԃ̎g�p�\�t���[�� */
    double _frame_of_segment;
    /** [r]���̕⊮�_���B�ɕK�v�Ȉړ����x�̃e�[�u�� */
    velo* _paSPMvVeloTo;
    /** [rw]1�t���[�����������\�ȉ�]�p�p���x */
    angvelo _angvelo_rzry_mv;
    /** [rw]������@ */
    int _turn_way;
    /** [rw]����œK���L�� */
    bool _turn_optimize;
    /** [r]�ŏI�n�_�����܂ł̃t���[���� */
    frame _spent_frame;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_source_file �X�v���C�����W���t�@�C��
     * @param prm_spent_frame �n�_(�A�N�^�[�̌����W�ł͂Ȃ�)�`�ŏI�n�_�����܂ł̃t���[����
     * @param prm_angvelo_rzry_mv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g false)
     */
    FixedFrameSplineManufacture(const char* prm_source_file,
                                frame prm_spent_frame,
                                angvelo prm_angvelo_rzry_mv = (D90ANG/9),
                                int prm_turn_way = TURN_CLOSE_TO,
                                bool prm_turn_optimaize = false );

    /**
     * �R���X�g���N�^ .
     * @param prm_pSplSrc �X�v���C�����W���I�u�W�F�N�g
     * @param prm_spent_frame �n�_(�A�N�^�[�̌����W�ł͂Ȃ�)�`�ŏI�n�_�����܂ł̃t���[����
     * @param prm_angvelo_rzry_mv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@ (�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g false)
     */
    FixedFrameSplineManufacture(SplineSource* prm_pSplSrc,
                                frame prm_spent_frame,
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
     * SplineKurokoLeader�I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� FixedFrameSplineManufacture �ł��B
     * @param prm_pKuroko �X�v���C���ړ�������ΏۃA�N�^�[
     * @return SplineKurokoLeader�I�u�W�F�N�g
     */
    SplineKurokoLeader* createKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko) override;

    virtual ~FixedFrameSplineManufacture();
};

}
#endif /*GGAFLIB_FIXEDFRAMESPLINEMANUFACTURE_H_*/
