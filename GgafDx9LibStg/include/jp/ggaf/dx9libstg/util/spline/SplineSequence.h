#ifndef SPLINESEQUENCE_H_
#define SPLINESEQUENCE_H_
namespace GgafDx9LibStg {

enum SplinTraceOption {
    ABSOLUTE_COORD,
    RELATIVE_COORD,
    RELATIVE_DIRECTION,
};

/**
 * �X�v���C���Ȑ��ړ������s���邽�߂̃I�u�W�F�N�g .
 * �⊮�_�Ɉړ����邽�߁A���x���r���ƃJ�N�J�N�ł��B
 * @version 1.00
 * @since 2009/10/27
 * @author Masatoshi Tsuge
 */
class SplineSequence : public GgafCore::GgafObject {

public:
    /** �X�v���C�����Z�b�g */
    SplineManufacture* _pManufacture;
    /** exec()����̌o�߃t���[���� */
    frame _execute_frames;
    /** ���݃v���O�������s���ł��邩�ǂ��� */
    bool _is_executing;
    /** ���W�𑀍삷��ΏۂƂȂ�A�N�^�[ */
    GgafDx9Core::GgafDx9GeometricActor* _pActor_target;
    /** �R���X�g���N�^������Spline3D�𐶐������ꍇtrue/�R���X�g���N�^������Spline3D���n���ꂽ�ꍇ�Afalse */
//    bool _is_create_pManufacture;
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

    SplineSequence(SplineManufacture* prm_pManufacture,  GgafDx9Core::GgafDx9KurokoA* prm_pKurokoA);

    /**
     * �e�⊮�_��ǂݍ��ݎ��AX�������AY�������AZ���������ꂼ��ɉ��Z(���s�ړ�)���A�␳���܂� .
     * �f�t�H���g�� adjustCoodOffset(0, 0, 0) �ƂȂ�܂��B<BR>
     * <b>[����]</b><BR>
     * �����ŁAadjustAxisXFlip() adjustAxisYFlip() adjustAxisZFlip() ���l��������
     * adjustCoodOffset()  ���l������܂��܂��B<BR>
     * @param prm_offset_X X�������␳������
     * @param prm_offset_Y Y�������␳������
     * @param prm_offset_Z Z�������␳������
     */
    virtual void adjustCoodOffset(coord prm_offset_X, coord prm_offset_Y, coord prm_offset_Z);

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
     * �ΏۃA�N�^�[(_pActor_target)�̍��W���A�X�v���C���̈�ԍŏ��̊�_���W�Őݒ肷�� .
     * exec(ABSOLUTE_COORD) �̏ꍇ�A�܂�u��΍��W�ړ��X�v���C���v�̏ꍇ�A�L���Ȑݒ�ƂȂ肤��ł��傤�B<BR>
     * �u��΍��W�ړ��X�v���C���v���܂�Ӗ�������܂���B<BR>
     */
    void setAbsoluteBeginCoordinate();

    /**
     * �ォ��X�v���C���I�u�W�F�N�g��ݒ�B
     * @param prm_sp
     */
    virtual void setManufacture(SplineManufacture* prm_pManufacture);

    /**
     * �X�v���C���Ȑ��̕⊮�_���ړ�����v���O���������s�J�n
     * @param prm_option �I�v�V���� ���ɈӖ������B���ʎ����g���p
     */
    virtual void exec(SplinTraceOption prm_option = ABSOLUTE_COORD);

    /**
     * �ړ����s���\�b�h .
     * �ړ����s�����߂ɁA���t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    virtual void behave();

    /**
     * �X�v���C���ړ��v���O�������s����
     * @return true:���s�� / false:���s���I�����Ă���
     */
    bool isExecuting() {
        return _is_executing;
    }

    virtual ~SplineSequence();
};

}
#endif /*SPLINESEQUENCE_H_*/
