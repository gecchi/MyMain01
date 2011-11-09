#ifndef GGAFDXPUPPETEER_H_
#define GGAFDXPUPPETEER_H_

namespace GgafDxCore {

/**
 * �p�y�b�^�[(����l�`����) .
 * �p�y�b�^�[�́A���Œ݂邳�ꂽ�p�y�b�g(GgafDxD3DXAniMeshActor)�𑀂�_�ő���A<BR>
 * �l�X�Ȍ|(�A�j���[�V����)�����������邱�Ƃ��o����l(�I�u�W�F�N�g)�ł��B<BR>
 * �c�O�Ȃ���A�p�y�b�g�͓�����2��ނ̌|�܂ł������������鎖���o���܂���B<BR>
 * ���R�́A�p�y�b�^�[�̘r���Q�{������������ł��B�������Ȃ��ł��ˁB<BR>
 * �������g���āA�p�y�b�g�����܂������Ă��������B<BR>
 * <BR>
 * �����I�ɂ́A���̃N���X�́AID3DXAnimationController �̃��b�p�[�N���X�ł��B<BR>
 * �ő�g���b�N���� 2 �ł��B
 * ��ȓ����́A<BR>
 * �@ �A�j���[�V�����u�X�s�[�h�v�y�сu�d�݁v�́A�{���A�j���[�V�����g���b�N���������l�����A<BR>
 *    ������AAnimationSet ���ɕR�t���ĊǗ��B<BR>
 *    �A�j���[�V�����ؑ֎��ɁA�A�j���[�V�����ɕR�Â��u�X�s�[�h�v�y�сu�d�݁v��
 *    �g���b�N�ɐݒ肷��悤�ɂ��Ă���B<BR>
 * �A �t�Đ��A���[�v���̋@�\����<BR>
 * �ł��B
 * @version 1.00
 * @since 2011/02/22
 * @author Masatoshi Tsuge
 */
class GgafDxPuppeteer : public GgafCore::GgafObject {
private:
    /**
     * �|(���[�V����) .
     */
    struct Performance {
        /** �A�j���[�V�����Z�b�g */
        LPD3DXANIMATIONSET _pAnimationSet;
        /** �P���[�v�̎��� */
        double _time_of_one_loop;
        /** ���[�J���^�C�� */
        double _local_time;
        /** �ڕW���[�v��(1.5��Ȃǂ̎w����\) */
        double _target_loop;
        /** �ڕW���B�X�s�[�h����(1.0�Œʏ�X�s�[�h�A���ŋt�A�j���[�V����) */
        double _target_speed;
        /** ���݂̃X�s�[�h���� */
        double _speed;
        /** �X�s�[�h�����̉��Z�l */
        double _inc_speed;
        /** �X�s�[�h���������Z���Ȃ�� true */
        bool   _is_shifting_speed;
        /** �ڕW���B�d�� 0.0�`1.0(���͕s��) */
        double _target_weight;
        /** ���݂̏d�� */
        double _weight;
        /** �d�݂̉��Z�l */
        double _inc_weight;
        /** �d�݂����Z���Ȃ�� true */
        bool   _is_shifting_weight;
        /** ���[�v���@ */
        GgafDxPuppeteerMethod _method;
    };

    /** �p�y�b�^�[�̑���_ */
    struct Stick {
        UINT _no;
        Performance* _pPerformance;
    };

    /** �p�y�b�g�̃��f�� */
    GgafDxD3DXAniMeshModel* _pModel;
    /** �p�y�b�g�̃A�j���[�V�����R���g���[���[ */
    ID3DXAnimationController* _pAc;

public:
    /** �p�y�b�g */
    GgafDxD3DXAniMeshActor* _pPuppet;
    /** �p�y�b�g�̎����l�^(�|) */
    Performance* _paPerformances;
    /** �p�y�b�g�̎����l�^(�|)�̐� */
    UINT _num_perform;
    /** ����p�A�E��p�̃p�y�b�^�[�̑���_  [0]:����p�^[1]:�E��p  */
    Stick _aStick[2];

    /**
     * �R���X�g���N�^ .
     * @param prm_pPuppet �������
     * @return
     */
    GgafDxPuppeteer(GgafDxD3DXAniMeshActor* prm_pPuppet);


    /**
     * �v���C���Ă��炤�i���p�y�b�g��������j .
     * @param prm_handed �v���C����p�y�b�^�[�̑���_ (LEFT_HAND or RIGHT_HAND)
     * @param prm_prm_performance_no �v���C����|�ԍ��i�A�j���[�V�����R���g���[���[�̃A�j���[�V�����Z�b�gID�Ɉ�v����j
     * @param prm_loopnum ���̌|�̃��[�v�� 0.0 �` (�P�񔼃��[�v��1.5�Ƃ����悤�ɂ��w��\�B���̐��w��(-1)�Ŗ������[�v�A�j���[�V����)
     * @param prm_target_speed �ڕW�X�s�[�h���� �ʏ�� -1.0 �` 0.0 �` 1.0 (1.0�Œʏ�X�s�[�h�A����ȏ���\�B���̒l�w��ŋt�A�j���[�V�����ɂȂ�)
     * @param prm_shift_speed_frames �ڕW�X�s�[�h�����ւ̓��B�t���[�����B���X�ɃX�s�[�h�ω����܂��B(0 ���w��ő��� prm_target_speed �ɂȂ�)
     * @param prm_target_weight �ڕW�d�݁i���A�j���[�V�������������j 0.0 �` 1.0 (���̐��s��)
     * @param prm_shift_weight_frames �ڕW�d�ւݓ��B�t���[�����A���X�ɏd�݂��ω�����B(0 ���w��ő��� prm_target_weight �ɂȂ�)
     * @param prm_method
     */
    void play(GgafDxPuppeteerStick prm_handed,
              UINT prm_prm_performance_no,
              double prm_loopnum,
              double prm_target_speed,
              frame prm_shift_speed_frames,
              double prm_target_weight,
              frame prm_shift_weight_frames,
              GgafDxPuppeteerMethod prm_method = NO_CHENGE
    );

    /**
     * �p�y�b�^�[�̉E��|�ƍ���|������ .
     */
    void exchangPerformance();

    void unpause(GgafDxPuppeteerStick prm_handed);
    void pause(GgafDxPuppeteerStick prm_handed);
    void stop();

    virtual void behave();
    virtual void work();
    virtual ~GgafDxPuppeteer();

};

}
#endif /*GGAFDXPUPPETEER_H_*/