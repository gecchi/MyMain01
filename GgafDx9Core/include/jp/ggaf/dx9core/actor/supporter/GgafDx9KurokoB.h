#ifndef GGAFDX9MVTRANSPORTER_H_
#define GGAFDX9MVTRANSPORTER_H_
namespace GgafDx9Core {


/**
 * ���qB(����B)  .
 * ���qB�͕���ɂ͌����Ȃ��ł����A����(�A�N�^�[)�������グ�A�u���s�ړ��v���s�킹�鐢�b�l�ł��B<BR>
 * �u���s�ړ��v�ɓ������Ă���A���qA�́u�����ړ��v�u�����̉�]�v�Ƃ͐�啪�삪�Ⴂ�܂��B<BR>
 * ���qA�ƍ��qB�����͂���΁A���Ȃ蕡�G�ȓ��������҂ɍs�킹�邱�Ƃ��ł��܂��B
 * ���҈�l�ɂ��A���qB���W���ň�l�t�����Ă��܂��B<BR>
 * <BR>
 * ����͂��Ēu���A�܂���W�v�Z�x���i���ʉ��j�N���X���̂Q�ł��B<BR>
 * GgafDx9GeometricActor �̃����o��<BR>
 *  _X, _Y, _Z  �E�E�E �A�N�^�[�̍��W<BR>
 * ���A�e�������ɊȒP�ɑ��삷�邽�߂ɍ쐬�B<BR>
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDx9KurokoB : public GgafCore::GgafObject {

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9GeometricActor* _pActor;

    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    GgafDx9KurokoB(GgafDx9GeometricActor* prm_pActor);


    /** X�������ړ����x */
    velo _veloVxMv;
    /** X�������ړ����x��� */
    velo _veloTopVxMv;
    /** X�������ړ����x���� */
    velo _veloBottomVxMv;
    /** X�������ړ������x */
    acce _acceVxMv;
    /** X�������ړ������x���*/
    acce _acceTopVxMv;
    /** X�������ړ������x����*/
    acce _acceBottomVxMv;
    /** Y�������ړ����x */
    velo _veloVyMv;
    /** Y�������ړ����x��� */
    velo _veloTopVyMv;
    /** Y�������ړ����x���� */
    velo _veloBottomVyMv;
    /** Y�������ړ������x */
    acce _acceVyMv;
    /** Y�������ړ������x���*/
    acce _acceTopVyMv;
    /** Y�������ړ������x����*/
    acce _acceBottomVyMv;
    /** Z�������ړ����x */
    velo _veloVzMv;
    /** Z�������ړ����x��� */
    velo _veloTopVzMv;
    /** Z�������ړ����x���� */
    velo _veloBottomVzMv;
    /** Z�������ړ������x */
    acce _acceVzMv;
    /** Z�������ړ������x���*/
    acce _acceTopVzMv;
    /** Z�������ړ������x����*/
    acce _acceBottomVzMv;


    int _gravitation_mv_seq_target_X;
    int _gravitation_mv_seq_target_Y;
    int _gravitation_mv_seq_target_Z;
    GgafDx9GeometricActor* _gravitation_mv_seq_pActor_target;
    velo _gravitation_mv_seq_max_velo;
    acce _gravitation_mv_seq_acce;
    int _gravitation_mv_seq_stop_renge;
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
     * X��Y��Z�������̈ړ������x�� 0 �ɐݒ肷��B
     */
    void setZeroVxyzMvVelo() {
        _veloVxMv = _veloVyMv = _veloVzMv = 0;
    }

    void setZeroVxyzMvAcce() {
        _acceVxMv = _acceVyMv = _acceVzMv = 0;
    }


    void stopGravitationVxyzMvSequence() {
        _gravitation_mv_seq_flg = false;
    }

    /**
     *
     * @param prm_tX
     * @param prm_tY
     * @param prm_tZ
     * @param prm_max_velo
     * @param prm_acce
     * @param prm_stop_renge
     */
    void execGravitationVxyzMvSequence(
            coord prm_tX, coord prm_tY, coord prm_tZ,
            velo prm_max_velo,
            acce prm_acce,
            int prm_stop_renge
            );


    void execGravitationVxyzMvSequence(
            GgafDx9GeometricActor* prm_pActor_target,
            velo prm_max_velo,
            acce prm_acce,
            int prm_stop_renge
            );

    /**
     * ���qB�̎d�������p�� .
     * ���� GgafDx9KurokoB �I�u�W�F�N�g����Ԃ����g�Ɉ��p�� .
     * @param prm_pKurokoB ���p��
     */
    void takeoverMvFrom(GgafDx9KurokoB* prm_pKurokoB);


    void resetMv();

    /**
     * ���qB������ .
     * ���qB�@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɍ��qB��K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~GgafDx9KurokoB();
};

}
#endif /*GGAFDX9MVTRANSPORTER_H_*/

