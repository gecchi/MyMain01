#ifndef GGAF_DX_FIXEDFRAMECURVEMANUFACTURE_H_
#define GGAF_DX_FIXEDFRAMECURVEMANUFACTURE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

namespace GgafDx {

/**
 * ��ԌŒ莞�ԁi�t���[���j�ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * �S�ẴA�N�^�[�ɋ��ʂ���X�v���C���̏��͂����ɏW��B
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameCurveManufacture : public CurveManufacture {

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
    frame _spent_frames;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_coord_spl_file �X�v���C�����W���t�@�C��
     * @param prm_spent_frames �n�_(�A�N�^�[�̌����W�ł͂Ȃ�)�`�ŏI�n�_�����܂ł̃t���[����
     * @param prm_angvelo_rzry_mv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@(�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g false)
     */
    FixedFrameCurveManufacture(const char* prm_coord_spl_file,
                                frame prm_spent_frames,
                                angvelo prm_angvelo_rzry_mv = (D90ANG/9),
                                int prm_turn_way = TURN_CLOSE_TO,
                                bool prm_turn_optimaize = false );

    /**
     * �R���X�g���N�^ .
     * @param prm_pCurveSrc �X�v���C�����W���I�u�W�F�N�g
     * @param prm_spent_frames �n�_(�A�N�^�[�̌����W�ł͂Ȃ�)�`�ŏI�n�_�����܂ł̃t���[����
     * @param prm_angvelo_rzry_mv �A�N�^�[�̐���p�x
     * @param prm_turn_way �A�N�^�[�̐�����@ (�f�t�H���g TURN_CLOSE_TO)
     * @param prm_turn_optimaize �A�N�^�[�̐���̍œK���I�v�V����(�f�t�H���g false)
     */
    FixedFrameCurveManufacture(CurveSource* prm_pCurve,
                               frame prm_spent_frames,
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
     * �ŏI�n�_�����܂ł̃t���[�������擾 .
     * @return
     */
    frame getSpentFrames() {
        return _spent_frames;
    }
    /**
     * �ŏI�n�_�����܂ł̃t���[�������w�肵�A�Čv�Z���� .
     * @param prm_spent_frames
     */
    void recalculateBySpentFrame(frame prm_spent_frames);

    /**
     * VehicleLeader �I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� FixedFrameCurveManufacture �ł��B
     * @param prm_pLocoVehicle �J�[�u�ړ����邽�߂̑��삷��I�u�W�F�N�g
     * @return VehicleLeader �I�u�W�F�N�g
     */
    VehicleLeader* createLocoVehicleLeader(GgafDx::LocoVehicle* prm_pLocoVehicle) override;

    VehicleLeader* createCoordVehicleLeader(GgafDx::CoordVehicle* prm_pCoordVehicle) override;

    virtual ~FixedFrameCurveManufacture();
};

}
#endif /*GGAF_DX_FIXEDFRAMECURVEMANUFACTURE_H_*/
