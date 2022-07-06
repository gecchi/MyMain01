#ifndef GGAF_DX_VEHICLELEADER_H_
#define GGAF_DX_VEHICLELEADER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafDx {

enum SplinTraceOption {
    ABSOLUTE_COORD,     //��΍��W�ړ�
    RELATIVE_COORD,     //�X�v���C�����W��(0,0,0)���A�A�N�^�[�̌����W�Ƃ����΍��W�Ōv�Z
    RELATIVE_COORD_DIRECTION, //�X�v���C�����W��(0,0,0)���A�A�N�^�[�̌����W�Ƃ����΍��W�Ƃ��A�A�N�^�[�̌��݂̌����i_rx > _rz > _ry)�ŃX�v���C�����W�Q�����[���h�ϊ��B
};

/**
 * �X�v���C���Ȑ��ړ������s���邽�߂̃I�u�W�F�N�g .
 * �͎ԂɎw�����o���Ĉړ���擱���܂��B
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class VehicleLeader : public GgafCore::Object {

public:
    /** �X�v���C�����Z�b�g */
    CurveManufacture* _pManufacture;
    /** �擱�J�n���������ǂ��� */
    bool _was_started;
    /** ���ݐ擱���ł��邩�ǂ��� */
    bool _is_leading;
    /** ���W�𑀍삷��ΏۂƂȂ�A�N�^�[ */
    GgafDx::GeometricActor* _pActor_target;
    /**
     * [r]�I�v�V����
     * ABSOLUTE_COORD     : ��΍��W�ړ��B
     * RELATIVE_COORD     : �n�_�������W�Ƃ��A�X�v���C�����W�Q�͑��Έړ��Ōv�Z�B
     * RELATIVE_COORD_DIRECTION : �n�_�������W�Ƃ��A����Ɍ��݂̌����i_pVecVehicle �� _rz_mv, _ry_mv)�ŃX�v���C�����W�Q�����[���h�ϊ��B
     */
    SplinTraceOption _option;
    /** [r] ���[�v�J�E���^ */
    int _cnt_loop;
    /** [r] �ݒ胋�[�v���B-1 �Ŗ��� */
    int _max_loop;

    /** [r]���̃��[�v�ł̎n�_X���W */
    coord _x_start_in_loop;
    /** [r]���̃��[�v�ł̎n�_Y���W */
    coord _y_start_in_loop;
    /** [r]���̃��[�v�ł̎n�_Z���W */
    coord _z_start_in_loop;

    coord _offset_x;
    coord _offset_y;
    coord _offset_z;

    int _flip_x;
    int _flip_y;
    int _flip_z;
    /** [r]�A�N�^�[�̌��݈ʒu����X�v���C���n�_�܂ł̋����Bstart()���_�ōX�V�����B */
    int _distance_to_begin;
    /** [r]�n�_���W���Œ肷��B�i�Œ肵�Ȃ��ꍇ�͎͗Ԃ̃A�N�^�[�̍��W�ɂȂ�j */
    bool _is_force_start_pos;
    bool _is_force_start_ang;
    bool _is_fix_pos;
//    bool _is_loop_ang_by_face;

    double _sinRx_begin;
    double _cosRx_begin;
    double _sinRz_begin;
    double _cosRz_begin;
    double _sinRy_begin;
    double _cosRy_begin;

    bool _turn_smooth;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pVecVehicle
     */
    VehicleLeader(CurveManufacture* prm_pManufacture,  GgafDx::GeometricActor* prm_pActor_target);

    /**
     * �e�⊮�_��ǂݍ��ݎ��AX�������AY�������AZ���������ꂼ��ɉ��Z(���s�ړ�)���A�␳���܂� .
     * �f�t�H���g�� adjustCoordOffset(0, 0, 0) �ƂȂ�܂��B<BR>
     * <b>[����]</b><BR>
     * �����ŁAadjustAxisXFlip() adjustAxisYFlip() adjustAxisZFlip() ���l������A
     * ����� Manufacture ��XYZ�����̕␳�������悶��ꂽ��A��ԍŌ��
     * adjustCoordOffset()  ���l�����ꍷ�����Z����܂��B<BR>
     * @param prm_offset_x X�������␳������
     * @param prm_offset_y Y�������␳������
     * @param prm_offset_z Z�������␳������
     */
    virtual void adjustCoordOffset(coord prm_offset_x, coord prm_offset_y, coord prm_offset_z);

    /**
     * �X�v���C���̊e���W�_���AX�����]���܂��B
     */
    virtual void adjustAxisXFlip() {
        _flip_x = -_flip_x;
    }

    /**
     * �X�v���C���̊e���W�_���AY�����]���܂��B
     */
    virtual void adjustAxisYFlip() {
        _flip_y = -_flip_y;
    }

    /**
     * �X�v���C���̊e���W�_���AZ���]���܂��B
     */
    virtual void adjustAxisZFlip() {
        _flip_z = -_flip_z;
    }

    /**
     * �ΏۃA�N�^�[(_pActor_target)�̍��W���A�X�v���C���̈�ԍŏ��̐���_���W�Őݒ肷�� .
     * start(ABSOLUTE_COORD) �̏ꍇ�A�܂�u��΍��W�ړ��X�v���C���v�̏ꍇ�A
     * �L���Ȑݒ�ƂȂ肤��ł��傤�B<BR>
     */
    void setAbsoluteBeginCoord();

    /**
     * �ォ��X�v���C���I�u�W�F�N�g��ݒ�B
     * @param prm_pManufacture
     */
    virtual void setManufacture(CurveManufacture* prm_pManufacture);

    /**
     * �X�v���C���Ȑ��̕⊮�_���ړ�����擱�J�n .
     * @param prm_option ABSOLUTE_COORD     ��΍��W�ړ�
     *                   RELATIVE_COORD     �X�v���C�����W��(0,0,0)���A�Ώ͎ۗԂ̃A�N�^�[�̌����W�Ƃ��A���΍��W�Ōv�Z
     *                   RELATIVE_COORD_DIRECTION �X�v���C�����W��(0,0,0)���A�Ώ͎ۗԂ̃A�N�^�[�̌����W�Ƃ��A���΍��W�Ōv�Z�B���̌�A���݂̌����i_rx > _rz > _ry)�ŃX�v���C�����W�Q�����[���h�ϊ��B
     * @param prm_max_loop �J��Ԃ��񐔁A�ȗ����͂P���[�v�B
     */
    virtual void start(SplinTraceOption prm_option, int prm_max_loop = 1);

    virtual void restart();

    /**
     * �X�v���C���Ȑ��̕⊮�_���ړ�����擱����߂�i���F�A�N�^�[����~����킯�ł͂Ȃ��j .
     */
    virtual void stop();

    /**
     * �ړ����s���\�b�h .
     * �ړ����s�����߂ɁA�͎Ԃ̏�Ԃ��X�V���܂��B
     * start() ���s��������t���[���Ɏ��s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ���behave()�́A���݂̍��W�`�|�C���g[0] ������Ă���΂��̈ړ������A
     * �����A���݂̍��W�ƃ|�C���g[0]���d�Ȃ��Ă���΁A���݂̍��W�`�|�C���g[1]�ւ̈ړ������ƂȂ�܂��B<BR>
     * �͎�(GgafDx::VecVehicle)��behave();����Ɏ��s���ĉ������B
     */
    virtual void behave() = 0;

    /**
     * �͎Ԃ�擱�����ۂ� .
     * @return true:�擱�� / false:�擱���I�����Ă���
     */
    inline bool isLeading() {
        return _is_leading;
    }

    /**
     * �͎Ԃ�擱���I���������ۂ��B .
     * @return true:�擱���I�����Ă��� / false:�܂��J�n���Ă��Ȃ����A�擱��
     */
    inline bool isFinished() {
        if (_was_started) {
            return _is_leading ? false : true;
        } else {
            return false;
        }
    }

    /**
     * �X�v���C���̕⊮�_�ƕ⊮�_�̊Ԃ̋������擾����B
     * CurveManufacture::adjustAxisRate(double,double,double);<BR>
     * �ɂ��␳�ς݂̕⊮�_�ԋ������擾�����B<BR>
     * �����C���f�b�N�X=0 ��start() �����s��Ɏ擾�o����悤�ɂȂ�B<BR>
     * <pre>
     *
     *   X:����_
     *   o:����_�Ԃ̕⊮�_�i�X�v���C���Ȑ��ʉߓ_�j
     *
     *        getSegmentDistance(0)
     *            ||
     *            ||    getSegmentDistance(1)   getSegmentDistance(5)   getSegmentDistance(8)
     *            ||         ||                     ||                         ||
     *        <-----------> <--->                <------->                  <------->
     *    ���@�E�E�E�E�E�E X----o----o----o-----X--------o---------o--------o-------X
     *                    �n�_
     *                    [0]  [1]  [2]  [3]   [4]      [5]       [6]      [7]     [8]
     *
     *  </pre>
     * @param prm_index �C���f�b�N�X�i0=�A�N�^�[�����W���n�_�Ԃ̋����B1=�n�_���n�_+1�̕⊮�_�ԋ����E�E�E�j
     * @return ���̃Z�O�����g�̋���
     */
    coord getSegmentDistance(int prm_index);

    /**
     * ���݂̍��W�`�n�_[0]�`�I�_�Ԃ̋������擾����B
     * @return ���v����
     */
    coord getTotalDistance();

    /**
     * �X�v���C���̕⊮�_(��_���܂�)�̐���Ԃ��B
     * <pre>
     *
     *   X:����_
     *   o:����_�Ԃ̕⊮�_�i�X�v���C���Ȑ��ʉߓ_�j
     *
     *        getSegmentDistance(0)
     *            ||
     *            ||    getSegmentDistance(1)   getSegmentDistance(5)   getSegmentDistance(8)
     *            ||         ||                     ||                         ||
     *        <-----------> <--->                <------->                  <------->
     *    ���@�E�E�E�E�E�E X----o----o----o-----X--------o---------o--------o-------X
     *                    �n�_
     *                    [0]  [1]  [2]  [3]   [4]      [5]       [6]      [7]     [8]
     *
     * </pre>
     *  ��}�̏ꍇ �⊮�_�C���f�b�N�X���O�`�W�̂X�Ȃ̂ŁA�߂�l��9�ƂȂ�B
     * @return �⊮�_(��_���܂�)�̐�
     */
    int getPointNum();

    /**
     * �⊮�_�̍��W���擾����B
     * @param prm_index �⊮�_�C���f�b�N�X(0�`) <BR>
     *                  �J�n�_�C���f�b�N�X�F0 �` �ŏI�_�C���f�b�N�X�FgetPointNum()-1
     * @param out_x �߂�lX���W
     * @param out_y �߂�lY���W
     * @param out_z �߂�lZ���W
     */
    virtual void getPointCoord(int prm_index, coord& out_x, coord& out_y, coord& out_z);

    /**
     * �X�v���C���̊J�n���W�������̍��W�ɌŒ�ݒ�B
     * �{���\�b�h�����s���Ȃ������ꍇ�A�X�v���C���J�n���W�́A<BR>
     * �u�X�v���C���J�n���W �� start()���̗͎Ԃ̃A�N�^�[�̍��W�v�ƂȂ�̂����A<BR>
     * ������s�킸�ɁA�X�v���C���J�n���W���A�C�ӂ̍��W����̃X�^�[�g�ɐݒ���s���B
     * �z��g�p���@�́A�{���\�b�h���s�ŊJ�n���W��ݒ肵����A<BR>
     * ���ۂ̈ړ�����A�N�^�[�̍��W�͕ʂ̏ꏊ�ɐݒ肵�āA�J�[�u�ړ����J�n�A<BR>
     * ��������ƃX�v���C���Ȑ��O���ɏ��X�ɍ�������悤�Ȍ��ʂ����o���邱�Ƃ��ł���B<BR>
     * @param prm_x
     * @param prm_y
     * @param prm_z
     */
    void setPositionFix(coord prm_x, coord prm_y, coord prm_z) {
        setStartPosition(prm_x, prm_y, prm_z);
        _is_fix_pos = true;
    }

    /**
     * ��ԍŏ��̃X�v���C���̊J�n���W�������̍��W�ɐݒ�B
     * �A���Astart()���A�J�[�u�ړ��J��Ԃ��ݒ�(�Q�T�ȏ�)���s�����ꍇ�A�Q���ڈȍ~�ɂ͓K�p����Ȃ��B<BR>
     * �Q�T�ڈȍ~�́A�J�n���W�́A�O��̘_���ŏI���W���A�J�n���W�ɐݒ肳���B
     * �A���Q�T�ڂɓ���O�ɍēx�ݒ肵���ꍇ�A�Q�T�ڃX�v���C���̊J�n���W�������̍��W�ɐݒ�B
     * @param prm_x
     * @param prm_y
     * @param prm_z
     */
    void setStartPosition(coord prm_x, coord prm_y, coord prm_z) {
        _is_force_start_pos = true;
        _x_start_in_loop = prm_x;
        _y_start_in_loop = prm_y;
        _z_start_in_loop = prm_z;
    }

    /**
     * �X�v���C���̊J�n�ړ��������Œ�ɐݒ�B
     * �{���\�b�h�����s���Ȃ������ꍇ�A�X�v���C���J�n���̃X�v���C�������́A<BR>
     * �u�X�v���C���J�n���� �� start()���̑ΏۃA�N�^�[�̗͎Ԃ̌����̕���(_rz, _ry�j�v�ƂȂ�̂����A<BR>
     * ������s�킸�ɁA�X�v���C���J�n���A�C�ӂ̃X�v���C����������̃X�^�[�g�ɐݒ���s���B<BR>
     * start()���A�J�[�u�ړ��J��Ԃ��ݒ�(�Q�T�ȏ�)���s�����ꍇ�A
     * �Q�T�ڈȍ~�́A�J�n�ړ������͂��̂܂܂ŁA���̒l�����̂܂܈����p����邱�ƂɂȂ�B<BR>
     * �A���Q�T�ڂɓ���O�ɍēx�ݒ肵���ꍇ�A�Q�T�ڃX�v���C���̊J�n�ړ������������̕����ɐݒ�B
     * ���X�v���C�������̐ݒ�́ARELATIVE_COORD_DIRECTION �̏ꍇ�݈̂Ӗ�������B
     * ���ӁFrx > ry > rz �̈������I(rz > ry�ł͂Ȃ�)
     * @param prm_rx
     * @param prm_rz
     * @param prm_ry
     */
    void setStartAngle(angle prm_rx, angle prm_ry, angle prm_rz);

//    /**
//     * �J�[�u�ړ��̊J�n�������A�����������Ă�������ɑ΂��ĊJ�n���� (�f�t�H���g).
//     * start()���̑ΏۃA�N�^�[�̌����̕���(_rz, _ry)�ɍ��W�ϊ�����āA�X�v���C���̋O�Ղ��\�z�����B
//     */
//    void setLoopAngleByFaceAng() {
//        _is_loop_ang_by_face = true;
//    }
//
//    /**
//     * �J�[�u�ړ��̊J�n�������A�������ړ����Ă�������ɑ΂��ĊJ�n���� .
//     * start()���̑ΏۃA�N�^�[�͎Ԃ̈ړ�����(getVecVehicle()->_rz_mv, getVecVehicle()->_ry_mv�j
//     * �ɍ��W�ϊ�����āA�X�v���C���̋O�Ղ��\�z�����B
//     */
//    void setLoopAngleByMvAng() {
//        _is_loop_ang_by_face = false;
//    }



//    void linkedStartPosition() {
//        unsetStartPosition();
//        _is_linked_start_pos = true;
//    }
//
//    void unlinkedStartPosition() {
//        _is_linked_start_pos = false;
//    }
//
//    void linkedStartAngle() {
//        unsetStartAngle();
//        _is_linked_start_ang = true;
//    }
//
//    void unlinkedStartAngle() {
//        _is_linked_start_ang = false;
//    }

    virtual ~VehicleLeader();
};

}
#endif /*GGAF_DX_VEHICLELEADER_H_*/