#ifndef GGAFCORE_GGAFGOD_H_
#define GGAFCORE_GGAFGOD_H_
#include "jp/ggaf/core/GgafObject.h"

#include <windows.h>

#undef P_GOD
#define P_GOD (GgafCore::GgafGod::_pGod)

namespace GgafCore {

#define  BEGIN_SYNCHRONIZED1   ::EnterCriticalSection(&(GgafCore::GgafGod::CS1))
#define  END_SYNCHRONIZED1     ::LeaveCriticalSection(&(GgafCore::GgafGod::CS1))
#define  BEGIN_SYNCHRONIZED2   ::EnterCriticalSection(&(GgafCore::GgafGod::CS2))
#define  END_SYNCHRONIZED2     ::LeaveCriticalSection(&(GgafCore::GgafGod::CS2))
#define  SLOWDOWN_MODE_DEFAULT 0
#define  SLOWDOWN_MODE_40FPS 1
#define  SLOWDOWN_MODE_30FPS 2
/**
 * �_�N���X.
 * ��ɂ��̐�(GgafUniverse)���Ǘ������삷�邱�Ƃ�ړI�Ƃ���N���X�ł��B���Ԃ��Ԃ��炢�B<BR>
 * �{�N���X�� be() ���\�b�h���Ăё����邱�ƂŁA���̐����������ƂɂȂ�A�Ƃ����݌v�B<BR>
 * �C���X�^���X�͂P�ł��B<BR>
 * TODO:�O���[�o���ȎQ�Ƃ�ێ�������֗����N���X�ɂȂ����G�B<BR>
 * TODO:�ŏI�I�ɂ� �_���Q�� new ���āA���݂� be() �����s����΁A�Q�[�����Q���s���삷��悤�ɂ��悤���ȁB
 * (����:GdxfwWorld�N���X)
 * @version 1.00
 * @since 2007/11/26
 * @author Masatoshi Tsuge
 */
class GgafGod : public GgafObject {

private:
    /** behave���s�������t���O */
    bool _is_behaved_flg;
    /** materialize���s�������t���O */
    bool _is_materialized_flg;

public:
    /** [r] be() �ł��邩�ǂ��� */
    static volatile bool _can_be;
    /** [r] �N���e�B�J���Z�N�V�������̂P�i�Z�}�t�H�j */
    static CRITICAL_SECTION CS1;
    /** [r] �N���e�B�J���Z�N�V�������̂Q�i�Z�}�t�H�j */
    static CRITICAL_SECTION CS2;
    /** [r] ���g */
    static GgafGod* _pGod;
    /** [r] �����H��(�ʃX���b�h)�̃G���[��ԁBnullptr������ғ����^not nullptr���ُ픭�� */
    static GgafCriticalException* _pException_Factory;
    /** [r] ���ɂ��̐������������鎞�Ԃ̃I�t�Z�b�g */
    static DWORD _aaTime_offset_of_next_view[3][60];

    /** [r] be() �����ǂ��� */
    bool _is_being;
    /** [r] GgafFactory::work �X���b�h�n���h��  */
    HANDLE _handleFactory01;
    /** [r] GgafFactory::work �X���b�hID  */
    unsigned int _thID01;
    /** [r] �_�̃t���[���J�n�V�X�e������ */
    DWORD _time_at_beginning_frame;
    /** [r] ���ɂ��̐�������������V�X�e������ */
    DWORD _time_of_next_view;
    /** [r] �_�a������̃t���[���� */
    frame _frame_of_God;
    int _cnt_frame;

    /** [r] ���̐������o���ł��Ȃ������i�X�L�b�v�����j�� */
    int _skip_count_of_frame;
    /** [r] ���̐� */
    GgafUniverse* _pUniverse;
    /** [r] fps�l�i��1000ms���Ɍv�Z�����j */
    float _fps;

    DWORD _time_calc_fps_next;
    /** [r] �`��t���[���J�E���^ */
    frame _visualize_frames;
    /** [r] �O��fps�v�Z���̕`��t���[���J�E���g�l */
    frame _prev_visualize_frames;
    /** [r] ���t���[���̕`��� */
    static int _num_actor_drawing;
    /** [r] �`�揈���A�ō��X�L�b�v�t���[���� */
    int _max_skip_frames;
    /** [r] ���݂̏����������[�h 0:60fps 1:40fps 2:30fps�B_aaTime_offset_of_next_view�̈�ڂ̗v�f */
    int _slowdown_mode;
    /** [r] ���Ԃƃt���[���̓����������[�h����true */
    bool _sync_frame_time;
    bool _was_cleaned;

public:
    /**
     * �R���X�g���N�^ .
     * �ʃX���b�h�ōH����ғ������܂��B
     */
    GgafGod();

    /**
     * �u���݂���v�Ƃ������\�b�h .
     * �_�����݂���A���Ȃ킿�A���̐�(GgafUniverse)�������A�A�v�����i�s���܂��B<BR>
     * ����Ăяo�����A���̐�(GgafUniverse)���쐬����܂��B<BR>
     * �A�v���P�[�V�����́A�ŏ����ԒP�ʂł��̃��\�b�h���Ђ�����Ăё����Ă��������B<BR>
     */
    void be();

    /**
     * ���̐��ɁA�Ƃ���u�Ԃ�n�� .
     */
    virtual void presentUniversalMoment();

    /**
     * ���̐��̑n�����ꂽ�u�Ԃɂ��ĐR���i�`�F�b�N�j���� .
     */
    virtual void executeUniversalJudge();

    /**
     * ���̐��̑n�����ꂽ�u�Ԃ�`��������� .
     */
    virtual void makeUniversalMaterialize();

    /**
     * ���̐��ɕ`���������A�l�Ԃɂ��F���ł���悤�ɕ\�ʉ����� .
     */
    virtual void presentUniversalVisualize();

    /**
     * ���̐��̎��̏u�Ԃ�n�����邽�߂̏����A��n�� .
     */
    virtual void finalizeUniverse();

    /**
     * ���̐����擾 .
     * ���ʂŃI�[�o�[���C�h�\�B<BR>
     * @return ���̐�
     */
    virtual GgafUniverse* getUniverse() {
        return _pUniverse;
    }

    /**
     * ���̐���n�� .
     * ���ʂł��̐��̑n�����@���������Ă��������B<BR>
     * @return ���̐�
     */
    virtual GgafUniverse* createUniverse() = 0;

    /**
     * �`����ꎞ��~���A�t���[���Ǝ��Ԃ̓������s��
     */
    void syncTimeFrame() {
        _sync_frame_time = true;
    }

    virtual void clean();

    /**
     * �_�u���܂����`�I�v .
     * ��O�������ɃR�[���o�b�N����܂��B
     */
    virtual void oops() {
        _TRACE_("(-_-;) {Oops!");
    }

    virtual ~GgafGod();
};

}
#endif /*GGAFCORE_GGAFGOD_H_*/
