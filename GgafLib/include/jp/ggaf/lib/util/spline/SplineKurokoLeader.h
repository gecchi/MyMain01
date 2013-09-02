#ifndef GGAFLIB_SPLINEKUROKOLEADER_H_
#define GGAFLIB_SPLINEKUROKOLEADER_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafLib {

/**
 * �X�v���C���Ȑ��ړ������s���邽�߂̃I�u�W�F�N�g .
 * ����A�Ɏw�����o���Ĉړ���擱���܂��B
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineKurokoLeader : public GgafCore::GgafObject {

public:
    enum SplinTraceOption {
        ABSOLUTE_COORD,     //��΍��W�ړ�
        RELATIVE_COORD,     //�X�v���C�����W��(0,0,0)���A�A�N�^�[�̌����W�Ƃ����΍��W�Ōv�Z
        RELATIVE_DIRECTION, //�X�v���C�����W��(0,0,0)���A�A�N�^�[�̌����W�Ƃ����΍��W�Ƃ��A�A�N�^�[�̌��݌����i_pKurokoA �� _angRzMv, _angRyMv)�ŃX�v���C�����W�Q�����[���h�ϊ��B
    };

    /** �X�v���C�����Z�b�g */
    SplineManufacture* _pManufacture;
    /** start()����̌o�߃t���[���� */
    frame _leading_frames;
    /** �擱�J�n���������ǂ��� */
    bool _was_started;
    /** ���ݐ擱���ł��邩�ǂ��� */
    bool _is_leading;
    /** ���W�𑀍삷��ΏۂƂȂ�A�N�^�[ */
    GgafDxCore::GgafDxGeometricActor* _pActor_target;
    /** �R���X�g���N�^������SplineLine�𐶐������ꍇtrue/�R���X�g���N�^������SplineLine���n���ꂽ�ꍇfalse�B�ꎞ���̂�����������B*/
    bool _is_created_pManufacture;
    /**
     * [r]�I�v�V����
     * ABSOLUTE_COORD     : ��΍��W�ړ��B
     * RELATIVE_COORD     : �n�_�������W�Ƃ��A�X�v���C�����W�Q�͑��Έړ��Ōv�Z�B
     * RELATIVE_DIRECTION : �n�_�������W�Ƃ��A����Ɍ��݂̌����i_pKurokoA �� _angRzMv, _angRyMv)�ŃX�v���C�����W�Q�����[���h�ϊ��B
     */
    SplinTraceOption _option;
    /** [r] ���[�v�J�E���^ */
    int _cnt_loop;
    /** [r] �ݒ胋�[�v���B-1 �Ŗ��� */
    int _max_loop;

    /** [r]�n�_X���W */
    coord _X_start;
    /** [r]�n�_Y���W */
    coord _Y_start;
    /** [r]�n�_Z���W */
    coord _Z_start;

    coord _offset_X;
    coord _offset_Y;
    coord _offset_Z;

    int _flip_X;
    int _flip_Y;
    int _flip_Z;
    /** [r]�A�N�^�[�̌��݈ʒu����X�v���C���n�_�܂ł̋����Bstart()���_�ōX�V�����B */
    int _distance_to_begin;
    /** [r]���݌������Ă���Œ��̕⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** [r]�n�_���W���Œ肷��B�i�Œ肵�Ȃ��ꍇ�͍��qA�̃A�N�^�[�̍��W�ɂȂ�j */
    bool _is_fix_start_pos;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pKurokoA
     */
    SplineKurokoLeader(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKurokoA* const prm_pKurokoA);

    /**
     * �e�⊮�_��ǂݍ��ݎ��AX�������AY�������AZ���������ꂼ��ɉ��Z(���s�ړ�)���A�␳���܂� .
     * �f�t�H���g�� adjustCoordOffset(0, 0, 0) �ƂȂ�܂��B<BR>
     * <b>[����]</b><BR>
     * �����ŁAadjustAxisXFlip() adjustAxisYFlip() adjustAxisZFlip() ���l������A
     * ����� Manufacture ��XYZ�����̕␳�������悶��ꂽ��A��ԍŌ��
     * adjustCoordOffset()  ���l�����ꍷ�����Z����܂��B<BR>
     * @param prm_offset_X X�������␳������
     * @param prm_offset_Y Y�������␳������
     * @param prm_offset_Z Z�������␳������
     */
    virtual void adjustCoordOffset(coord prm_offset_X, coord prm_offset_Y, coord prm_offset_Z);

    /**
     * �X�v���C���̊e���W�_���AX�����]���܂��B
     */
    virtual void adjustAxisXFlip() {
        _flip_X = -_flip_X;
    }

    /**
     * �X�v���C���̊e���W�_���AY�����]���܂��B
     */
    virtual void adjustAxisYFlip() {
        _flip_Y = -_flip_Y;
    }

    /**
     * �X�v���C���̊e���W�_���AZ���]���܂��B
     */
    virtual void adjustAxisZFlip() {
        _flip_Z = -_flip_Z;
    }

    /**
     * �ΏۃA�N�^�[(_pActor_target)�̍��W���A�X�v���C���̈�ԍŏ��̐���_���W�Őݒ肷�� .
     * start(SplineKurokoLeader::ABSOLUTE_COORD) �̏ꍇ�A�܂�u��΍��W�ړ��X�v���C���v�̏ꍇ�A
     * �L���Ȑݒ�ƂȂ肤��ł��傤�B<BR>
     */
    void setAbsoluteBeginCoord();

    /**
     * �ォ��X�v���C���I�u�W�F�N�g��ݒ�B
     * @param prm_pManufacture
     */
    virtual void setManufacture(SplineManufacture* prm_pManufacture);

    /**
     * �X�v���C���Ȑ��̕⊮�_���ړ�����擱�J�n .
     */
    virtual void start(SplinTraceOption prm_option, int prm_max_loop = 1);

    /**
     * �X�v���C���Ȑ��̕⊮�_���ړ�����擱����߂�i���F�A�N�^�[����~����킯�ł͂Ȃ��j .
     */
    virtual void stop();

    /**
     * �ړ����s���\�b�h .
     * �ړ����s�����߂ɁA���t���[�����̃��\�b�h���Ăяo���K�v������܂��B<BR>
     * start() ���s��������t���[���Ɏ��s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ���behave()�́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave();

    /**
     * ����A��擱�����ۂ� .
     * @return true:�擱�� / false:�擱���I�����Ă���
     */
    inline bool isLeading() {
        return _is_leading;
    }

    /**
     * ����A��擱���I���������ۂ��B .
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
     * SplineManufacture::adjustAxisRate(double,double,double);<BR>
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
     * @param out_X �߂�lX���W
     * @param out_Y �߂�lY���W
     * @param out_Z �߂�lZ���W
     */
    virtual void getPointCoord(int prm_index, coord &out_X, coord&out_Y, coord &out_Z);

    /**
     * �X�v���C���̊J�n���W�������̍��W�ɌŒ�istart()���ɉe�����Ȃ��j�B
     * �f�t�H���g�̊J�n���W���Œ肵�Ȃ��ꍇ�́A<BR>
     * �u�X�v���C���J�n���W��start()���̍��qA�̃A�N�^�[�̍��W�v�ƂȂ�B<BR>
     * �z��g�p���@�́A�{���\�b�h���s�ŊJ�n���W��ݒ肵����A<BR>
     * ���ۂ̈ړ�����A�N�^�[�̍��W�͕ʂ̏ꏊ�ɐݒ肵�āA�X�v���C���ړ����J�n�A<BR>
     * ��������ƃX�v���C���Ȑ��O���ɏ��X�ɍ�������悤�Ȍ��ʂ����o���邱�Ƃ��ł���B<BR>
     * @param prm_X
     * @param prm_Y
     * @param prm_Z
     */
    void fixStartPosition(coord prm_X, coord prm_Y, coord prm_Z) {
        _is_fix_start_pos = true;
        _X_start = prm_X;
        _Y_start = prm_Y;
        _Z_start = prm_Z;
    }

    /**
     * �X�v���C���̊J�n���W�Œ����������B
     */
    void unfixStartPosition() {
        _is_fix_start_pos = false;
    }
    virtual ~SplineKurokoLeader();
};

}
#endif /*GGAFLIB_SPLINEKUROKOLEADER_H_*/
