#ifndef GGAFDX9PUPPETEER_H_
#define GGAFDX9PUPPETEER_H_

#define LEFT_HANDED 0
#define RIGHT_HANDED 1

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
        GgafDx9MotionMethod _method;
        bool _is_playing;
        double _total_time;
        double _local_time;
        double _target_time;
        double _speed;
        double _weight;
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
    UINT _num_tricks;
    /** �p�y�b�^�[�̑���_  [0]:����p�^[1]:�E��p  */
    Stick _aStick[2];
    /** �A�N�e�B�u�ȑ���_ */
    Stick* _pStickActive;

    double _advance_time_per_draw;

    /**
     * �R���X�g���N�^ .
     * @param prm_pActor �������
     * @return
     */
    GgafDx9Puppeteer(GgafDx9D3DXAniMeshActor* prm_pPuppet);


    virtual ~GgafDx9Puppeteer();

    void setStickSpeed(double prm_speed);

    void play(UINT performance_no, GgafDx9MotionMethod method);

    void play();
    void stop();


    virtual void behave();
    virtual void work();


};

}
#endif /*GGAFDX9PUPPETEER_H_*/
