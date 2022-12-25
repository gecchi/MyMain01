#ifndef GGAF_DX_PUPPETEER_H_
#define GGAF_DX_PUPPETEER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/core/util/TransitionValue.hpp"
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
 * �p�y�b�^�[�́A���Œ݂邳�ꂽ�p�y�b�g(Actor)�𑀂�_�ő���A<BR>
 * �l�X�Ȍ|(�A�j���[�V����)�����������邱�Ƃ��o����l(�I�u�W�F�N�g)�ł��B<BR>
 * �c�O�Ȃ���A�p�y�b�g�͓�����2��ނ̌|�܂ł������������鎖���o���܂���B<BR>
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
     * ID3DXAnimationSet���b�p�[
     */
    class Performance {
    public:
        /** �A�j���[�V�����Z�b�g */
        LPD3DXANIMATIONSET _pAnimationSet;
        UINT _animation_set_index;
        double _period;
        /** ���[�J���^�C�� */
//        GgafCore::TrapezoidalVeloValue<double> _local_time;
        double _p1;
        double _p2;
        /** �ڕW���[�v��(1.5��Ȃǂ̎w����\) */
        double _target_loop;

        double _loop_count;
//        GgafCore::TrapezoidalVeloValue<double> _weight;
        /** ���[�v���@ */
        PuppeteerMethod _method;
    public:
        Performance();
        void setAnimationSet(LPD3DXANIMATIONSET prm_pAnimationSet, UINT prm_animation_set_index);
        virtual ~Performance();
    };

    /** �p�y�b�^�[�̑���_ */
    struct Stick {
        /** ����_�ԍ�(�A�j���[�V�����g���b�N�ԍ�) */
        UINT _tno;
        /** �p�y�b�^�[�̑���_�̐�ɂ������Ă鎝���l�^(�|) */
        Performance* _pPerformance;

        GgafCore::TransitionValue<double> _weight;
    };

public:
    /** [r/w]�p�y�b�g�̎����l�^(�|) */
    Performance* _paPerformances;
    /** [r]�p�y�b�g�̎����l�^(�|)�̐��AAnimationSet �̐� */
    UINT _num_perform;
    /** [r/w]����p�A�E��p�̃p�y�b�^�[�̑���_(�A�j���[�V�����g���b�N)  [0]:����p�^[1]:�E��p  */
    Stick*  _pStickMain;
    Stick*  _pStickSub;
    Stick* _apStick[2];
    /** [r]���݂̃g���b�N�ɐݒ肳��Ă���A�j���[�V�����Z�b�g�B���ݒ�̏ꍇ��nullptr�B[0]:�g���b�N0�^[1]�g���b�N1 */
   ID3DXAnimationSet* _apAs[2];

    /** �A�j���[�V�����R���g���[���̃f�t�H���g�̂P�t���[��������̃A�j���[�V�����t���[�� */
    double _ani_time_delta;

    double _advance_time;
public:
    Puppeteer();

    /**
     * �R���X�g���N�^ .
     * @param prm_pAc_cloned �A�j���[�V�����R���g���[���[(clone��������)
     * @param prm_ani_time_delta �A�j���[�V�����ŏ����ԁi�A�j���[�V�����R���g���[���[�̓����̒P�ʁj
     */
    explicit Puppeteer(ID3DXAnimationController* prm_pAc_cloned,
                       double prm_ani_time_delta = 60.0 / 4800);  //����4800�t���[����1�b���Z (60FPS�̏ꍇ)

    /**
     * �|�i���C���j���v���C���Ă��炤�i���p�y�b�g��������j .
     * @param prm_performance_no �v���C����|�ԍ��i�A�j���[�V�����R���g���[���[�̃A�j���[�V�����Z�b�gID�Ɉ�v����j
     */
    void play(UINT prm_performance_no);

    /**
     * ���̌|�Ɉڍs���� .
     * @param prm_performance_no �ڍs����|�ԍ�
     * @param prm_switch_frames �ڍs���鎞��(�t���[����)
     */
    void shiftTo(UINT prm_performance_no, frame prm_switch_frames = 120);

    /**
     * �ꎞ�I�Ȍ|�i�T�u�j���v���C���Ă��炤 .
     * ���C���Łu�����v�� play ���ɁA������ێ������܂܁u���U��v�Ƃ������������ꍇ�Ɏ��s�B
     * @param prm_performance_no �v���C����|�ԍ��i�A�j���[�V�����R���g���[���[�̃A�j���[�V�����Z�b�gID�Ɉ�v����j
     * @param prm_num_loop �J��Ԃ���
     */
    void playPartly(UINT prm_performance_no, double prm_num_loop = 1.0);

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
