#ifndef GGAFDX9PUPPETEER_H_
#define GGAFDX9PUPPETEER_H_

namespace GgafDx9Core {

/**
 * �p�y�b�^�[(����l�`����) .
 * �p�y�b�^�[�́A���Œ݂邳�ꂽ�p�y�b�g(GgafDx9D3DXAniMeshActor)�𑀂�_�ő���A<BR>
 * �l�X�Ȍ|(�A�j���[�V����)�����������邱�Ƃ��o����l�ł��B<BR>
 * �c�O�Ȃ���A�p�y�b�g�͓�����2��ނ̌|�܂ł��������鎖���o���܂���B<BR>
 * ���R�́A�p�y�b�^�[�̘r���Q�{������������ł��B�������Ȃ��ł��ˁB<BR>
 * �������g���āA�p�y�b�g�����܂������Ă��������B<BR>
 * <BR>
 * �����āA���̃N���X�́AID3DXAnimationController �̃��b�p�[�N���X�ł��B<BR>
 * �ő�g���b�N���� 2 �ł��B
 * ��ȓ����́A<BR>
 * �@ �g���b�N���������l���AAnimationSet ���Ɏ�������悤�ɂ����B<BR>
 * �A �t�Đ��A���[�v�����A���̋@�\<BR>
 * �ł��B
 * @version 1.00
 * @since 2011/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9Puppeteer : public GgafCore::GgafObject {
private:
    /**
     * �|(���[�V����) .
     */
    struct Performance {
        LPD3DXANIMATIONSET _pAnimationSet;
        double _time_of_one_loop;
        double _local_time;
        double _target_loop;
//        double _loop;
        double _target_speed;
        double _speed;
        double _inc_speed;
        bool   _is_shifting_speed;
        double _target_weight;
        double _weight;
        double _inc_weight;
        bool   _is_shifting_weight;
    };

    struct Stick {
        UINT _no;
        Performance* _pPerformance;
    };
public:
    /** �p�y�b�g */
    GgafDx9D3DXAniMeshActor* _pPuppet;
    GgafDx9D3DXAniMeshModel* _pModel;
    ID3DXAnimationController* _pAc;

    /** �����l�^�| */
    Performance* _paPerformances;
    UINT _num_perform;
    /** �p�y�b�^�[�̑���_  [0]:����p�^[1]:�E��p  */
    Stick _aStick[2];

//    double _advance_time_per_draw;

//    bool _is_shifting_performance;
//    frame _shift_duaration;
//    double _weight_per_frame_for_shift;
//    frame _shifted;
    /**
     * �R���X�g���N�^ .
     * @param prm_pActor �������
     * @return
     */
    GgafDx9Puppeteer(GgafDx9D3DXAniMeshActor* prm_pPuppet);


    virtual ~GgafDx9Puppeteer();

//    void exchangStick();
//    void shift(UINT prm_prm_performance_no, frame prm_shift_duaration, GgafDx9MotionMethod prm_method);
    void play(GgafDx9PuppeteerStick prm_handed,
              UINT prm_prm_performance_no,
              double prm_loopnum,
              double prm_target_speed,
              frame prm_frame_duaration_of_shift_speed,
              double prm_target_weight,
              frame prm_frame_duaration_of_shift_weight
              );




    void unpause(GgafDx9PuppeteerStick prm_handed);
    void pause(GgafDx9PuppeteerStick prm_handed);
    void stop();

    virtual void behave();
    virtual void work();


};

}
#endif /*GGAFDX9PUPPETEER_H_*/
