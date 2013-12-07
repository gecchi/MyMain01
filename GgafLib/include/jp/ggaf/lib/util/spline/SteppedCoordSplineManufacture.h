#ifndef GGAFLIB_STEPPEDCOORDSPLINEMANUFACTURE_H_
#define GGAFLIB_STEPPEDCOORDSPLINEMANUFACTURE_H_
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

namespace GgafLib {

/**
 * �����ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineManufacture : public SplineManufacture {

public:
    /** [r]���݂̕⊮�_(��_���܂�)����A���̕⊮�_(or��_)�܂ł̋����̃e�[�u�� */
    coord* _paDistance_to;
    /** [r]�n�_����n�Ԗڂ̕⊮�_(��_���܂�)���B�ɕK�v�ȃt���[�����̃e�[�u�� */
    float* _paFrame_need_at;
    /** [rw]������@ */
    int _turn_way;
    /** [rw]����œK���L�� */
    bool _turn_optimize;
    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_source_file �X�v���C�����W���t�@�C��
     * @param prm_angveloRzRyMv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g true)
     */
    SteppedCoordSplineManufacture(const char* prm_source_file,
                                   int prm_turn_way = TURN_CLOSE_TO,
                                   bool prm_turn_optimaize = true );

    /**
     *
     * @param prm_pSplSrc �X�v���C�����W���I�u�W�F�N�g
     * @param prm_angveloRzRyMv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g true)
     */
    SteppedCoordSplineManufacture(SplineSource* prm_pSplSrc,
                                  int prm_turn_way = TURN_CLOSE_TO,
                                  bool prm_turn_optimaize = true );

    /**
     * �������i�v�Z�j���� .
     * �v���p�e�B��ύX�����ꍇ�A�����e�[�u�������X�V���邽�߂�
     * ��x���s����K�v������܂��B
     */
    void calculate() override;

    /**
     * SplineKurokoLeader�I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� SteppedCoordSplineKurokoLeader �ł��B
     * @param prm_pKuroko �X�v���C���ړ�������ΏۃA�N�^�[
     * @return SplineKurokoLeader�I�u�W�F�N�g
     */
    SplineKurokoLeader* createKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko) override;

    virtual ~SteppedCoordSplineManufacture();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEMANUFACTURE_H_*/
