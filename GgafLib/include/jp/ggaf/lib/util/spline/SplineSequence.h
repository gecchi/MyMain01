#ifndef SPLINESEQUENCE_H_
#define SPLINESEQUENCE_H_
namespace GgafLib {



/**
 * �X�v���C���Ȑ��ړ������s���邽�߂̃I�u�W�F�N�g .
 * �⊮�_�Ɉړ����邽�߁A���x���r���ƃJ�N�J�N�ł��B
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineSequence : public GgafCore::GgafObject {

public:
    enum SplinTraceOption {
        ABSOLUTE_COORD,     //��΍��W�ړ�
        RELATIVE_COORD,     //�X�v���C�����W��(0,0,0)���A�A�N�^�[�̌����W�Ƃ����΍��W�Ōv�Z
        RELATIVE_DIRECTION, //�X�v���C�����W��(0,0,0)���A�A�N�^�[�̌����W�Ƃ����΍��W�Ƃ��A�A�N�^�[�̌��݌����i_pKurokoA �� _angRzMv, _angRyMv)�ŃX�v���C�����W�Q�����[���h�ϊ��B
    };

    /** �X�v���C�����Z�b�g */
    SplineManufacture* _pManufacture;
    /** exec()����̌o�߃t���[���� */
    frame _execute_frames;
    /** ���݃v���O�������s���ł��邩�ǂ��� */
    bool _is_executing;
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

    /** [r]�n�_X���W */
    coord _X_begin;
    /** [r]�n�_Y���W */
    coord _Y_begin;
    /** [r]�n�_Z���W */
    coord _Z_begin;

    coord _offset_X;
    coord _offset_Y;
    coord _offset_Z;

    int _flip_X;
    int _flip_Y;
    int _flip_Z;
    /** [r]�A�N�^�[�̌��݈ʒu����X�v���C���n�_�܂ł̋����Bexec()���_�ōX�V�����B */
    int _distance_to_begin;
    /** [r]���ݏ������̕⊮�_(��_���܂�)�̐� */
    int _point_index;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pKurokoA
     */
    SplineSequence(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKurokoA* prm_pKurokoA);

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
     * exec(SplineSequence::ABSOLUTE_COORD) �̏ꍇ�A�܂�u��΍��W�ړ��X�v���C���v�̏ꍇ�A�L���Ȑݒ�ƂȂ肤��ł��傤�B<BR>
     * �u��΍��W�ړ��X�v���C���v�ȊO���܂�Ӗ�������܂���B<BR>
     */
    void setAbsoluteBeginCoordinate();

    /**
     * �ォ��X�v���C���I�u�W�F�N�g��ݒ�B
     * @param prm_pManufacture
     */
    virtual void setManufacture(SplineManufacture* prm_pManufacture);

    /**
     * �X�v���C���Ȑ��̕⊮�_���ړ�����v���O���������s�J�n
     * @param prm_option �I�v�V���� ���ɈӖ������B���ʎ����g���p
     */
    virtual void exec(SplinTraceOption prm_option = ABSOLUTE_COORD);

    virtual void stop();
    /**
     * �ړ����s���\�b�h .
     * �ړ����s�����߂ɁA���t���[�����̃��\�b�h���Ăяo���K�v������܂��B<BR>
     * exec() ���s��������t���[���Ɏ��s�������Ƃ��������Ƃ͕s�v�B<BR>
     * exec() ���s�����ŏ���behave()�́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave();

    /**
     * �X�v���C���ړ��v���O�������s����
     * @return true:���s�� / false:���s���I�����Ă���
     */
    bool isExecuting() {
        return _is_executing;
    }
    /**
     * �X�v���C���̕⊮�_�ƕ⊮�_�̊Ԃ̋������擾����B
     * SplineManufacture::adjustAxisRate(double,double,double);<BR>
     * �ɂ��␳�ς݂̕⊮�_�ԋ������擾�����B<BR>
     * �����C���f�b�N�X=0 ��exec() �����s��Ɏ擾�o����悤�ɂȂ�B<BR>
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
     * @return
     */
    coord getSegmentDistance(int prm_index);

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

    virtual ~SplineSequence();
};

}
#endif /*SPLINESEQUENCE_H_*/
