#ifndef GGAF_DX_PUPPETEER_H_
#define GGAF_DX_PUPPETEER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include <vector>
#include <d3dx9.h>
#include <d3dx9anim.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafDx {

/**
 * �p�y�b�^�[(����l�`����) .
 * �p�y�b�^�[�́A���Œ݂邳�ꂽ�p�y�b�g(AniMeshActor)�𑀂�_�ő���A<BR>
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
class Puppeteer : public GgafCore::Object {
private:
    /** [r]�p�y�b�g�̃A�j���[�V�����R���g���[���[ */
    ID3DXAnimationController* _pAc;

    /**
     * �|(���[�V����) .
     */
    class Performance {
    public:
        /** �A�j���[�V�����Z�b�g */
        LPD3DXANIMATIONSET _pAnimationSet;
        UINT _animation_set_index;

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
        bool  _is_shifting_weight;
        /** ���[�v���@ */
        PuppeteerMethod _method;
    public:
        Performance() {
            _pAnimationSet = nullptr;
            _animation_set_index = 0;
            _time_of_one_loop   = 0.0;
            _local_time         = 0.0;
            _target_loop        = -1;
            _target_speed       = 1.0;
            _speed              = 1.0;
            _inc_speed          = 0.0;
            _is_shifting_speed  = false;
            _target_weight      = 1.0;
            _weight             = 1.0;
            _inc_weight         = 0.0;
            _is_shifting_weight = false;
            _method             = NO_CHENGE;
        }
        void setAnimationSet(LPD3DXANIMATIONSET prm_pAnimationSet, UINT prm_animation_set_index) {
            _pAnimationSet = prm_pAnimationSet;
            _animation_set_index = prm_animation_set_index;
        }
        virtual ~Performance() {
        }
    };

    /** �p�y�b�^�[�̑���_ */
    struct Stick {
        /** ����_�ԍ�(�A�j���[�V�����g���b�N�ԍ�) */
        UINT _tno;
        /** ���[�V�����u�����h�L������ */
        BOOL _enable_motion_blend;
        /** �p�y�b�^�[�̑���_�̐�ɂ������Ă鎝���l�^(�|) */
        Performance* _pPerformance;
    };

public:
    /** [r/w]�p�y�b�g�̎����l�^(�|) */
    Performance* _paPerformances;
    /** [r]�p�y�b�g�̎����l�^(�|)�̐� */
    UINT _num_perform;
    /** [r/w]����p�A�E��p�̃p�y�b�^�[�̑���_(�A�j���[�V�����g���b�N)  [0]:����p�^[1]:�E��p  */
    Stick _aStick[2];
    ID3DXAnimationSet* _paAs[2];
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pPuppet �������
     * @return
     */
    explicit Puppeteer(ID3DXAnimationController* prm_pAc_cloned);

    /**
     * �v���C���Ă��炤�i���p�y�b�g��������j .
     * @param prm_handed �v���C����p�y�b�^�[�̑���_ (LEFT_HAND or RIGHT_HAND)
     * @param prm_performance_no �v���C����|�ԍ��i�A�j���[�V�����R���g���[���[�̃A�j���[�V�����Z�b�gID�Ɉ�v����j
     * @param prm_loopnum ���̌|�̃��[�v�� 0.0 �` (�P�񔼃��[�v��1.5�Ƃ����悤�ɂ��w��\�B���̐��w��(-1)�Ŗ������[�v�A�j���[�V����)
     * @param prm_target_speed �ڕW�X�s�[�h���� �ʏ�� -1.0 �` 0.0 �` 1.0 (1.0�Œʏ�X�s�[�h�A����ȏ���\�B���̒l�w��ŋt�A�j���[�V�����ɂȂ�)
     * @param prm_shift_speed_frames �ڕW�X�s�[�h�����ւ̓��B�t���[�����B���X�ɃX�s�[�h�ω����܂��B(0 ���w��ő��� prm_target_speed �ɂȂ�)
     * @param prm_target_weight �ڕW�d�݁i���A�j���[�V�������������j 0.0 �` 1.0 (���̐��s��)
     * @param prm_shift_weight_frames �ڕW�d�ւݓ��B�t���[�����A���X�ɏd�݂��ω�����B(0 ���w��ő��� prm_target_weight �ɂȂ�)
     * @param prm_method
     */
    void play(PuppeteerStick prm_handed,
              UINT prm_performance_no,
              double prm_loopnum,
              double prm_target_speed,
              frame prm_shift_speed_frames,
              double prm_target_weight,
              frame prm_shift_weight_frames,
              PuppeteerMethod prm_method = PLAY_LOOPING
    );

    /**
     * �p�y�b�^�[�̉E��|�ƍ���|������ .
     */
    void exchangPerformance();

    void stop();

    virtual void behave();
    virtual void updateAnimationTrack();

    virtual int getPerformanceNum() {
        return _num_perform;
    }

    virtual ~Puppeteer();

};

}
#endif /*GGAF_DX_PUPPETEER_H_*/
