#ifndef GGAFDXMVTRANSPORTER_H_
#define GGAFDXMVTRANSPORTER_H_
namespace GgafDxCore {


/**
 * ���qB(����B)  .
 * ���qB�͕���ɂ͌����Ȃ��ł����A����(�A�N�^�[)�������グ�A�u���s�ړ��v���s�킹�鐢�b�l�ł��B<BR>
 * �u���s�ړ��v�ɓ������Ă���A���qA�́u�����ړ��v�u�����̉�]�v�Ƃ͐�啪�삪�Ⴂ�܂��B<BR>
 * ���qA�ƍ��qB�����͂���΁A���Ȃ蕡�G�ȓ��������҂ɍs�킹�邱�Ƃ��ł��܂��B
 * ���҈�l�ɂ��A���qB���W���ň�l�t�����Ă��܂��B<BR>
 * <BR>
 * ����͂��Ēu���A�܂���W�v�Z�x���i���ʉ��j�N���X���̂Q�ł��B<BR>
 * GgafDxGeometricActor �̃����o��<BR>
 *  _X, _Y, _Z  �E�E�E �A�N�^�[�̍��W<BR>
 * ���A�e�������ɊȒP�ɑ��삷�邽�߂ɍ쐬�B<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDxKurokoB : public GgafCore::GgafObject {

public:
    /** �ΏۃA�N�^�[ */
    GgafDxGeometricActor* _pActor;

    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    GgafDxKurokoB(GgafDxGeometricActor* prm_pActor);

    /** [r/w]X�������ړ����x */
    velo _veloVxMv;
    /** [r/w]X�������ړ����x��� */
    velo _veloTopVxMv;
    /** [r/w]X�������ړ����x���� */
    velo _veloBottomVxMv;
    /** [r/w]X�������ړ������x */
    acce _acceVxMv;
    /** [r/w]X�������ړ������x���*/
    acce _acceTopVxMv;
    /** [r/w]X�������ړ������x����*/
    acce _acceBottomVxMv;
    /** [r/w]Y�������ړ����x */
    velo _veloVyMv;
    /** [r/w]Y�������ړ����x��� */
    velo _veloTopVyMv;
    /** [r/w]Y�������ړ����x���� */
    velo _veloBottomVyMv;
    /** [r/w]Y�������ړ������x */
    acce _acceVyMv;
    /** [r/w]Y�������ړ������x���*/
    acce _acceTopVyMv;
    /** [r/w]Y�������ړ������x����*/
    acce _acceBottomVyMv;
    /** [r/w]Z�������ړ����x */
    velo _veloVzMv;
    /** [r/w]Z�������ړ����x��� */
    velo _veloTopVzMv;
    /** [r/w]Z�������ړ����x���� */
    velo _veloBottomVzMv;
    /** [r/w]Z�������ړ������x */
    acce _acceVzMv;
    /** [r/w]Z�������ړ������x���*/
    acce _acceTopVzMv;
    /** [r/w]Z�������ړ������x����*/
    acce _acceBottomVzMv;


    coord _gravitation_mv_seq_target_X;
    coord _gravitation_mv_seq_target_Y;
    coord _gravitation_mv_seq_target_Z;
    GgafDxGeometricActor* _gravitation_mv_seq_pActor_target;
    velo _gravitation_mv_seq_max_velo;
    acce _gravitation_mv_seq_acce;
    coord _gravitation_mv_seq_stop_renge;
    bool _gravitation_mv_seq_flg;


    int dot(int prm_vX, int prm_vY, int prm_vZ);
    //virtual void behave();
    /**
     * X�������ړ����x�ݒ� .
     * @param prm_veloVxMv X�������ړ����x
     */
    void setVxMvVelo(velo prm_veloVxMv);

    /**
     * X�������ړ����x���Z .
     * @param prm_veloVxMv X�������ړ����x����
     */
    void addVxMvVelo(velo prm_veloVxMv);

    /**
     * X�������ړ����x�̏������������ .
     * @param prm_veloVxMv01 ���x�P
     * @param prm_veloVxMv02 ���x�Q
     */
    void forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02);

    /**
     * X�������ړ������x�ݒ� .
     * @param prm_acceVxMv X�������ړ������x
     */
    void setVxMvAcce(acce prm_acceVxMv);

    /**
     * X�������ړ������x���Z .
     * @param prm_acceVxMv X�������ړ������x����
     */
    void addVxMvAcce(acce prm_acceVxMv);

    /**
     * X�������ړ������x�̏������������ .
     * @param prm_acceVxMv01 �����x�P
     * @param prm_acceVxMv02 �����x�Q
     */
    void forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02);

    /**
     * Y�������ړ����x�ݒ� .
     * @param prm_veloVyMv Y�������ړ����x
     */
    void setVyMvVelo(velo prm_veloVyMv);

    /**
     * Y�������ړ����x���Z .
     * @param prm_veloVyMv Y�������ړ����x����
     */
    void addVyMvVelo(velo prm_veloVyMv);

    /**
     * Y�������ړ����x�̏������������ .
     * @param prm_veloVyMv01 ���x�P
     * @param prm_veloVyMv02 ���x�Q
     */
    void forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02);

    /**
     * Y�������ړ������x�ݒ� .
     * @param prm_acceVyMv Y�������ړ������x
     */
    void setVyMvAcce(acce prm_acceVyMv);

    /**
     * Y�������ړ������x���Z .
     * @param prm_acceVyMv Y�������ړ������x����
     */
    void addVyMvAcce(acce prm_acceVyMv);

    /**
     * Y�������ړ������x�̏������������ .
     * @param prm_acceVyMv01 �����x�P
     * @param prm_acceVyMv02 �����x�Q
     */
    void forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02);

    /**
     * Z�������ړ����x�ݒ� .
     * @param prm_veloVzMv Z�������ړ����x
     */
    void setVzMvVelo(velo prm_veloVzMv);

    /**
     * Z�������ړ����x���Z .
     * @param prm_veloVzMv Z�������ړ����x����
     */
    void addVzMvVelo(velo prm_veloVzMv);

    /**
     * Z�������ړ����x�̏������������ .
     * @param prm_veloVzMv01 ���x�P
     * @param prm_veloVzMv02 ���x�Q
     */
    void forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02);

    /**
     * Z�������ړ������x�ݒ� .
     * @param prm_acceVzMv Z�������ړ������x
     */
    void setVzMvAcce(acce prm_acceVzMv);

    /**
     * Z�������ړ������x���Z .
     * @param prm_acceVzMv Z�������ړ������x����
     */
    void addVzMvAcce(acce prm_acceVzMv);

    /**
     * Z�������ړ������x�̏������������ .
     * @param prm_acceVzMv01 �����x�P
     * @param prm_acceVzMv02 �����x�Q
     */
    void forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02);

    /**
     * X��Y��Z�������̈ړ����x�̏������������ .
     * @param prm_veloVxyzMv01 ���x�P
     * @param prm_veloVxyzMv02 ���x�P
     */
    void forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02);
    /**
     * X��Y��Z�������̈ړ������x�̏������������ .
     * @param prm_acceVxyzMv01 �����x�P
     * @param prm_acceVxyzMv02 �����x�Q
     */
    void forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02);

    /**
     * X��Y��Z�������̈ړ����x�� 0 �ɐݒ肷��B
     */
    void setZeroVxyzMvVelo() {
        _veloVxMv = _veloVyMv = _veloVzMv = 0;
    }

    /**
     * X��Y��Z�������̈ړ������x�� 0 �ɐݒ肷��B
     */
    void setZeroVxyzMvAcce() {
        _acceVxMv = _acceVyMv = _acceVzMv = 0;
    }

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ�������߂� .
     */
    void stopGravitationMvSequence() {
        _gravitation_mv_seq_flg = false;
    }

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ����̍Œ����ǂ���
     * @return true:�d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ�����/false:�����łȂ�
     */
    bool isGravitationMvSequence() {
        return _gravitation_mv_seq_flg;
    }

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ��������s .
     * �y�A���S���Y���T�v�z<BR>
     * X,Y,Z�̊e���̍��W���ꂼ��ɁA�ڕW�̍��W�ƃA�N�^�[�̍��W���������A<BR>
     * ���̐����ɂ��A�����x�����Z���Z�����ĖڕW�ɋ߂Â����Ƃ��܂��B<BR>
     * �A���A���̂܂܂ł���ƁA�q�������񂷂邪�@���A�i���ɖڕW�̍��W�ɓ��B���܂���B<BR>
     * �����ŁA�ڕW�̍��WX,Y,Z�̊e���ƁA�A�N�^�[�̍��W����<BR>
     * -1*prm_stop_renge �` prm_stop_renge<BR>
     * �͈͓̔��ɂȂ����ꍇ�A���x���ɘa(����)���A�ڕW�̍��W�ɍX�ɋ߂Â������܂��B<BR>
     * �e�����ꂼ��A�ڕW�ɋ߂Â��Ǝ����x��0�ɋ߂Â��A�Ƃ�����ŏd�͂Ƃ͍��{�I�ɓ������قȂ�܂��B<BR>
     * ���w�I�ɂ́A�ڕW�̍��W�Ɍ���Ȃ��߂Â������ŁA�ڕW���W�ƈ�v���邱�Ƃ͂���܂���B<BR>
     * @param prm_tX �����񂹂��ē��B����ڕW��X���W
     * @param prm_tY �����񂹂��ē��B����ڕW��Y���W
     * @param prm_tZ �����񂹂��ē��B����ڕW��Z���W
     * @param prm_max_velo �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ����x����l
     * @param prm_acce �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ������x����l
     * @param prm_stop_renge ���x���}������ڕW���W����̊e���̋���
     */
    void execGravitationMvSequence(coord prm_tX, coord prm_tY, coord prm_tZ,
                                   velo prm_max_velo,
                                   acce prm_acce,
                                   coord prm_stop_renge);

    /**
     * �d�͂ɂ�蕨�̂������񂹂��邩�悤�Ȋ����̓����݂����Ȋ��������s .
     * �����́A
     * execGravitationMvSequence(coord,coord,coord,velo,acce,int)
     * ���Q�ƁB
     * @param prm_pActor_target �����񂹂��ē��B����ڕW���W�ƂȂ�A�N�^�[
     * @param prm_max_velo �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ����x����l
     * @param prm_acce �����񂹂��Ă���Œ��̊e��(XYZ)�̎��ړ������x����l
     * @param prm_stop_renge ���x���}������ڕW���W����̊e���̋���
     */
    void execGravitationMvSequence(GgafDxGeometricActor* prm_pActor_target,
                                   velo prm_max_velo,
                                   acce prm_acce,
                                   coord prm_stop_renge);

    /**
     * ���qB�̎d�������p�� .
     * ���� GgafDxKurokoB �I�u�W�F�N�g����Ԃ����g�Ɉ��p�� .
     * @param prm_pKurokoB ���p��
     */
    void takeoverMvFrom(GgafDxKurokoB* prm_pKurokoB);


    void resetMv();

    /**
     * ���qB���U�镑�� .
     * ���qB�@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɍ��qB��K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~GgafDxKurokoB();
};

}
#endif /*GGAFDXMVTRANSPORTER_H_*/

