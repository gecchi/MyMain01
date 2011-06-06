#ifndef GGAFDX9MVTRANSPORTER_H_
#define GGAFDX9MVTRANSPORTER_H_
namespace GgafDx9Core {


/**
 * �i�r�Q�[�^�[ .
 * �i�r�Q�[�^�[�͕���ɂ͌����Ȃ��ł����A����(�A�N�^�[)�������グ�āA�ړ��A��]������l�X�ł��B<BR>
 * ���҂͎���͓��ɓ��삹���Ƃ��A�i�r�Q�[�^�[�̂������ŕ�����щ�܂�邱�Ƃ��ł��܂��B<BR>
 * ��{�I�ȓ���̓i�r�Q�[�^�[�łقƂ�ǃJ�o�[�ł��܂����A���\�ł͂���܂���B<BR>
 * �i�r�Q�[�^�[���撣���Ă��Ή��ł��Ȃ����G�ȓ���́A����(�A�N�^�[)���g�����͂��Ĉړ��A��]�C��K�v������܂��B<BR>
 * ���҈�l�ɂɂ��A�i�r�Q�[�^�[����l�t���Ă��܂��B<BR>
 * <BR>
 * ����͂��Ēu���A�܂���W�v�Z�x���i���ʉ��j�N���X�ł��B<BR>
 * GgafDx9GeometricActor �̃����o��<BR>
 *  _X ,  _Y,  _Z  �E�E�E �A�N�^�[�̍��W<BR>
 * _RX , _RY, _RZ  �E�E�E �A�N�^�[�̎���]�p�x<BR>
 * ���A�ȒP�ɑ��삷�邽�߂ɍ쐬�B<BR>
 * ��{�I�Ȉړ��A��]�̓i�r�Q�[�^�[�ɔC���A<BR>
 * ����Ȉړ��A��]�̂ݒ��ڃA�N�^�[�� processBehave() �Ɏ����B�Ƃ����݌v�v�z�B<BR>
 * TODO:���̊Ԃɂ���剻�B��������B
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDx9MvTransporter : public GgafCore::GgafObject {
    float _dummy1, _dummy2, _dummy3;

public:
    /** �ΏۃA�N�^�[ */
    GgafDx9GeometricActor* _pActor;
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  �K�pActor
     */
    GgafDx9MvTransporter(GgafDx9GeometricActor* prm_pActor);




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



    //virtual void behave();

    void setVxMvVelo(velo prm_veloVxMv);
    void addVxMvVelo(velo prm_veloVxMv);
    void forceVxMvVeloRange(velo prm_veloVxMv01, velo prm_veloVxMv02);
    void setVxMvAcce(acce prm_acceVxMv);
    void addVxMvAcce(acce prm_acceVxMv);
    void forceVxMvAcceRange(acce prm_acceVxMv01, acce prm_acceVxMv02);
    void setVyMvVelo(velo prm_veloVyMv);
    void addVyMvVelo(velo prm_veloVyMv);
    void forceVyMvVeloRange(velo prm_veloVyMv01, velo prm_veloVyMv02);
    void setVyMvAcce(acce prm_acceVyMv);
    void addVyMvAcce(acce prm_acceVyMv);
    void forceVyMvAcceRange(acce prm_acceVyMv01, acce prm_acceVyMv02);
    void setVzMvVelo(velo prm_veloVzMv);
    void addVzMvVelo(velo prm_veloVzMv);
    void forceVzMvVeloRange(velo prm_veloVzMv01, velo prm_veloVzMv02);
    void setVzMvAcce(acce prm_acceVzMv);
    void addVzMvAcce(acce prm_acceVzMv);
    void forceVzMvAcceRange(acce prm_acceVzMv01, acce prm_acceVzMv02);

    void forceVxyzMvVeloRange(velo prm_veloVxyzMv01, velo prm_veloVxyzMv02);
    void forceVxyzMvAcceRange(acce prm_acceVxyzMv01, acce prm_acceVxyzMv02);

    void setZeroVxyzMvVelo() {
        _veloVxMv = _veloVyMv = _veloVzMv = 0;
    }

    void setZeroVxyzMvAcce() {
        _acceVxMv = _acceVyMv = _acceVzMv = 0;
    }


    void stopGravitationVxyzMvSequence() {
        _gravitation_mv_seq_flg = false;
    }

    void execGravitationVxyzMvSequence(
            int prm_tX, int prm_tY, int prm_tZ,
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
     * �i�r�Q�[�^�[�̎d�������p�� .
     * ���� GgafDx9MvTransporter �I�u�W�F�N�g����Ԃ����g�Ɉ��p�� .
     * @param prm_pMvTransporter ���p��
     */
    void takeoverMvFrom(GgafDx9MvTransporter* prm_pMvTransporter);


    void resetMv();

    /**
     * �i�r�Q�[�^�[������ .
     * �i�r�Q�[�^�[�@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�Ƀi�r�Q�[�^�[��K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~GgafDx9MvTransporter();
};

}
#endif /*GGAFDX9MVTRANSPORTER_H_*/

