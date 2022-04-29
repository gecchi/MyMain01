#ifndef MAGIC_H_
#define MAGIC_H_
#include "VioletVreath.h"
#include "jp/ggaf/core/actor/MainActor.h"

namespace VioletVreath {

typedef int_fast32_t magic_point;
typedef frame magic_time;
#define MAX_MAGIC_TIME MAX_FRAME

#define MAGIC_CAST_NG_INVOKING_NOW          (-5)
#define MAGIC_CAST_NG_MP_IS_SHORT           (-4)
#define MAGIC_CAST_CANCEL                   (-3)
#define MAGIC_CAST_LEVELDOWN                (-2)
#define MAGIC_CAST_CANCEL_AND_LEVELDOWN     (-1)
#define MAGIC_CAST_NOTHING                  (0)
#define MAGIC_CAST_OK_LEVELUP               (1)
#define MAGIC_CAST_OK_CANCEL_AND_LEVELUP    (3)

#define MAGIC_INVOKE_NG_INVOKING_NOW (-3)
#define MAGIC_INVOKE_NG_MP_IS_SHORT  (-2)
#define MAGIC_INVOKE_NOTHING         (0)
#define MAGIC_INVOKE_OK_LEVELUP      (1)
#define MAGIC_INVOKE_OK_LEVELDOWN    (2)

#define MAGIC_EFFECT_NG_MP_IS_SHORT (-2)
#define MAGIC_EFFECT_NOTHING        (0)
#define MAGIC_EFFECT_OK_LEVELUP     (1)
#define MAGIC_EFFECT_OK_LEVELDOWN   (2)

#define MMETER_MAX_LEVEL 10

/**
 * ���ۖ��@�N���X .
 * ���@��MP�ɂ��Ă̖{�N���X�̊�{�I�Ȑ����B<BR>
 * �E���@���g�p����Ɗe���@�ɐݒ肳�ꂽMP������܂��B<BR>
 * �E���@�ɂ̓��x���Ƃ����T�O������A�����Ȃ���Ԃ̓��x���O�ł��B���x���P�ɂ���ꍇ�u��{���@�R�X�g�v�������܂��B<BR>
 * �E�e���x���ɃR�X�g���ݒ�o���܂��B���x���ɉ����āA�u��{���@�R�X�g�v�Ɂu���x�����������v ���悶��ꂽ�l���R�X�g�ɂȂ�܂��B<BR>
 * �E�A���A��у��x���A�b�v(�{�Q�ȏ�)�̏ꍇ�AMP����������ɂ���ݒ肪�\�ł��B<BR>
 * �E��у��x���A�b�v�ɂ��āA���Ƃ��΁u�X�s�[�h�v�ƌ������@�Ƀ��x���P�`�T������A
 *   ��{���@�R�X�g = 10, ���x���������� = 1.2 �Ƃ��āA�e���x���ɕK�v�ȃR�X�g�� 10,12,14,17,21 �������Ƃ��܂��B<BR>
 *   �u���������v ���u�X�s�[�h Level1�v���u�X�s�[�h Level2�v �ƂP�i�K�ÂQ�񃌃x���A�b�v���s�����ꍇ�AMP�R�X�g�� 10+12=22 �ł����A<BR>
 *   �����Ȃ� �u���������v ���u�X�s�[�h Level2�v�Ƃ����ꍇ�AMP�R�X�g�� (10+12)*0.8 = 19 �Ƃ����悤�Ȑݒ肪��у��x���A�b�v�ł͉\�ł��B<BR>
 *   ���� 0.8 �̂��Ƃ��u��у��x���팸�����v�ƌĂԎ��Ƃ��܂��B�u��у��x���팸�����v�̓��x�����ɉ����ʐݒ�ł���悤�ɂȂ��Ă��܂��B<BR>
 * �E���x���_�E���̊T�O�����݂��܂��B���x���_�E���͂��ł��s���܂��B<BR>
 *   ���x���_�E�����Ɏg�p���ɉ�����MP�Ɋ�炩�Ҍ�����Ƃ����ݒ���o���܂��B<BR>
 * �E���@�ɂ̓��C�t�T�C�N��������A���̃X�e�b�v�����݂��܂��B�e�p�����[�^���ݒ�\�ł��B<BR>
 *   a) ���@�̃��x���A�b�v���s<BR>
 *   b) �r���F���@�r���J�n���r�������r���I�� (�r���͓r���ŃL�����Z����)  <BR>
 *   c) �����F���@�����J�n�����@�������@�I�� (�����ɂȂ�ƃL�����Z���s��) <BR>
 *   d) �����F���@���ʎ����J�n(�R�X�g�����E���ʔ���) �����ʎ��������ʎ����I���i���@�̃��x���_�E���j<BR>
 * �E���@�̎�ނɂ́A�u���������@�v�A�u���ʎ��������@�v �̂Q��ނ�����܂��B
 *   1)�u���������@�v�� �ud) �����v�̃v���Z�X���������@�ł���A���x���A�b�v�E�_�E���Ƃ����T�O�����݂��܂���B<BR>
 *   2)�u���ʎ��������@�v�́A�ud) �����v���AMP�����u�ێ��R�X�g�L��v�AMP����Ȃ��u�ێ��R�X�g�����v�̂Q��ނ�����܂��B
 *      �܂��A�\�ߐݒ肳�ꂽ���ʎ������Ԃ𒴂���Ǝ����Ń��x���_�E��(�|�P)���܂��B<BR>
 *      2-a)�u�ێ��R�X�g�L�v�� �ud) �����v����MP������A�����r����MP��0�ɂȂ��Ă��܂����ꍇ�A�����I�Ƀ��x��0�ɂ܂Ń��x���_�E�����܂��B<BR>
 *      2-b)�u�ێ��R�X�g���v�� �ud) �����v����MP������܂���B�r����MP��0�ł����x���_�E���͋N����܂���B�i���ʎ������Ԑ؂�݂̂ŋN����j<BR>
 * @version 1.00
 * @since 2009/05/19
 * @author Masatoshi Tsuge
 */
class Magic : public GgafCore::MainActor {
public:
    enum {
        STATE_NOTHING     ,
        STATE_RE_CASTING  ,
        STATE_CASTING     ,
        STATE_INVOKING    ,
        STATE_RE_EFFECT   ,
        STATE_EFFECT_START,
        STATE_ABANDONING  ,
        PHASE_BANPEI,
    };

    /**
     * �e���x���̏�� .
     */
    class LevelInfo {
    public:
        /** [r]���@���ʎ����I���c�莞�� */
        magic_time remained_frame_of_effecting;
        /** [r/w]���@�R�X�g */
        magic_point cost_;
        /** [r/w]�r������ */
        magic_time casting_frames_;
        /** [r/w]�������� */
        magic_time invoking_frames_;
        /** [r/w]���@���ʎ������� */
        magic_time effecting_frames_;
        /** [r/w]���@���ʎ������R�X�g  */
        magic_point keep_cost_;
        /** [r/w]�A�j���p�^�[���ԍ� */
        int pno_;
        LevelInfo() : remained_frame_of_effecting(0),
                      cost_(0),
                      casting_frames_(0),
                      invoking_frames_(0),
                      effecting_frames_(0),
                      keep_cost_(0),
                      pno_(0) {
        }
    };

    /**
     * ���x�����̏�� .
     */
    class LevelDiffInfo {
    public:
        /** [r]��у��x�����̖��@�R�X�g�팸����(0.0�`1.0) */
        double r_cost_lv_diff_;
        /** [r]��у��x�����̉r�����ԍ팸����(0.0�`1.0) */
        double r_casting_frames_lv_diff_;
        /** [r]��у��x�����̔������ԍ팸����(0.0�`1.0) */
        double r_invoking_frames_lv_diff_;

        LevelDiffInfo() : r_cost_lv_diff_(0.0),
                          r_casting_frames_lv_diff_(0.0),
                          r_invoking_frames_lv_diff_(0.0) {
        }
    };

public:
    /** [r]�}�W�b�N�|�C���g */
    int* const pMP_;

    /** [r]���݂̍ō�������x�� */
    int max_level_;
    /** [r]���݂̃��x��(���݌��ʎ������Ă��郌�x���A�����I�������ʎ����J�n�̃^�C�~���O�Ő؂�ւ��) */
    int level_;
    /** [r]�V�������x��(�r�����A�������̎��A�Ɏ��ɂȂ낤�Ƃ��郌�x��) */
    int new_level_;
    /** [r]�O��̃��x��(���ʎ������̎��A���ʎ�������O�̃��x��) */
    int last_level_;
    /** [r]�P�t���[���O�̃��x�� */
    int prev_frame_level_;

    int level_nextframe_;
    int new_level_nextframe_;
    int last_level_nextframe_;

    /** [r]�{���@�����ɕK�v�ȃR�X�g�̊�{�P�� */
    const magic_point cost_base_;
    /** [r]�{���@�r���J�n �` ���@�r���I���̊�{�P�ʎ���  */
    const magic_time casting_frames_base_;
    /** [r]�{���@�����J�n �` ���@�����I���̊�{�P�ʎ��� */
    const magic_time invoking_frames_base_;
    /** [r]�{���@���ʎ����J�n �` ���@���ʎ����I���̊�{�P�ʎ���  */
    const magic_time effecting_frames_base_;
    /** [r]�{���@���ʎ������R�X�g�̊�{�P��  */
    const magic_point keep_cost_base_;

    /** [r]�e���x�����̖��@�R�X�g��������(1.0�`) �ʏ�A�����x���قǖ��@�R�X�g������ */
    const double r_every_lv_cost_;
    /** [r]�e���x�����̉r�����ԑ�������(1.0�`) �ʏ�A�����x���قǉr�����Ԃ����� */
    const double r_every_lv_casting_frames_;
    /** [r]�e���x�����̔������ԑ�������(1.0�`) �ʏ�A�����x���قǔ������Ԃ����� */
    const double r_every_lv_invoking_frames_;
    /** [r]�e���x�����̌��ʎ������ԍ팸����(0.0�`1.0) �ʏ�A�����x���قǌ��ʎ������Ԃ��Z�� */
    const double r_every_lv_effecting_frames_;
    /** [r]�e���x�����̈ێ��R�X�g�������� (1.0�` ) �ʏ�A�����x���قǈێ��R�X�g������ */
    const double r_each_lv_keep_cost_;
    /** [r]�e���x���̏�� �z��C���f�b�N�X��[���x��] */
    LevelInfo lvinfo_[MMETER_MAX_LEVEL+1];

    /** [r]��у��x�����̖��@�R�X�g�팸����(�ʏ� 0.0�`1.0) �ʏ�A���x�����������قǖ��@�R�X�g������ */
    const double r_cost_lv_diff_base_;
    /** [r]��у��x�����̉r�����ԍ팸����(�ʏ� 0.0�`1.0) �ʏ�A���x�����������قǉr�����Ԃ��Z�k */
    const double r_casting_frames_lv_diff_base_;
    /** [r]��у��x�����̔������ԍ팸����(�ʏ� 0.0�`1.0) �ʏ�A���x�����������قǔ������Ԃ��Z�k */
    const double r_invoking_frames_lv_diff_base_;
    /** [r]�e���x�����̏��̔z��A�z��C���f�b�N�X��[���x����] */
    LevelDiffInfo lvdiff_[MMETER_MAX_LEVEL+1];

    /** [r]���x���A�b�v�ɕK�v�ȃR�X�g�̏��Z�b�g�B�z��C���f�b�N�X��[�����x��][�V�������x��] */
    magic_point level_up_cost_[MMETER_MAX_LEVEL+1][MMETER_MAX_LEVEL+1];
    /** [r]���x���A�b�v�ɉr�����Ԃ̏��Z�b�g�B�z��C���f�b�N�X��[�����x��][�V�������x��] */
    magic_time  level_up_casting_frames_[MMETER_MAX_LEVEL+1][MMETER_MAX_LEVEL+1];
    /** [r]���x���A�b�v�ɔ������Ԃ̏��Z�b�g�B�z��C���f�b�N�X��[�����x��][�V�������x��] */
    magic_time  level_up_invoking_frames_[MMETER_MAX_LEVEL+1][MMETER_MAX_LEVEL+1];

    /** [r]���̐i����ԂɂȂ�ׂɕK�v�ȃt���[����(���ꎞ�ێ�) */
    magic_time time_of_next_state_;

    phase temp_hold_status_;
    int temp_hold_new_level_;

    int last_cast_;
    int last_invoke_;
    int last_effect_;

public:
    /**
     * ���@�̒�`���s�� .
     * ��у��x���Ƃ̓��x�������P���傫��(���x�����Q�ȏ�)���w���B
     * @param prm_name ���@��
     * @param prm_pMP �}�W�b�N�|�C���g�̐��ʃo�[
     * @param prm_max_level �{���@�̏����ō����x�� 1�`MMETER_MAX_LEVEL
     * @param prm_cost_base       ��{���@�R�X�g(��{����MP)
     * @param prm_r_every_lv_cost �e���x���̃R�X�g���������B�ʏ�A1.0�` �i1.0���傫���ƍ����x���قǃR�X�g�������ɂȂ�j<br>
     *                      (�y��z1.0:���x���ɂ�鑝�����������i���S���x����{���@�R�X�g�j<br>
     *                             1.2:���x��1�P�̂ŕK�v�ȃR�X�g �� ��{�R�X�g<br>
     *                                 ���x��2�P�̂ŕK�v�ȃR�X�g �� ��{�R�X�g * 1.2<br>
     *                                 ���x��3�P�̂ŕK�v�ȃR�X�g �� ��{�R�X�g * 1.2 * 1.2<br>
     *                                 ���x��4�P�̂ŕK�v�ȃR�X�g �� ��{�R�X�g * 1.2 * 1.2 * 1.2  �R�X�g���ݒ肳���)
     * @param prm_r_cost_lv_diff ��у��x�����̖��@�R�X�g�팸���� 0.0�`1.0 �i1.0��菬�����ƁA��у��x�����R�X�g�������ɂȂ�B�Z�߂Ĕ�Ԃقǂ����j<br>
     *                      (�y��z1.0:�������у��x���ł��R�X�g��������,<br>
     *                             0.8:��у��x����2�̂Ƃ��A���̃��x���A�b�v�ɕK�v�ȃR�X�g * 0.8<br>
     *                                 ��у��x����3�̂Ƃ��A���̃��x���A�b�v�ɕK�v�ȃR�X�g * 0.8 * 0.8<br>
     *                                 ��у��x����4�̂Ƃ��A���̃��x���A�b�v�ɕK�v�ȃR�X�g * 0.8 * 0.8 * 0.8
     * @param prm_casting_frames_base ��{�r������
     * @param prm_r_every_lv_cost �e���x���̉r�����ԑ��������B�ʏ�A1.0�` �i1.0���傫���ƍ����x���قǉr�����Ԃ������j<br>
     *                      (�y��z1.0:���x���ɂ��r�����ԑ������������i���S���x����{�r�����ԁj<br>
     *                             1.2:���x��1�P�̂ŕK�v�ȉr������ �� ��{�r������<br>
     *                                 ���x��2�P�̂ŕK�v�ȉr������ �� ��{�r������ * 1.2<br>
     *                                 ���x��3�P�̂ŕK�v�ȉr������ �� ��{�r������ * 1.2 * 1.2<br>
     *                                 ���x��4�P�̂ŕK�v�ȉr������ �� ��{�r������ * 1.2 * 1.2 * 1.2 ���Ԃ��ݒ肳���)
     * @param prm_r_casting_frames_lv_diff_base ��у��x�����̉r�����ԍ팸���� 0.0�`1.0 �i1.0��菬�����ƁA��у��x�����A�r�����Ԃ��Z�k�ɂȂ�B�Z�߂Ĕ�Ԃقǂ����j<br>
     *                      (�y��z1.0:�������у��x���ł��R�X�g��������,<br>
     *                             0.8:��у��x����2�̂Ƃ��A���̃��x���A�b�v�ɕK�v�ȉr������ * 0.8<br>
     *                                 ��у��x����3�̂Ƃ��A���̃��x���A�b�v�ɕK�v�ȉr������ * 0.8 * 0.8<br>
     *                                 ��у��x����4�̂Ƃ��A���̃��x���A�b�v�ɕK�v�ȉr������ * 0.8 * 0.8 * 0.8
     * @param prm_invoking_frames_base ��{��������
     * @param prm_r_every_lv_invoking_frames �e���x���̔������ԑ��������B�ʏ�A1.0�` �i1.0���傫���ƍ����x���قǔ����܂ł������Ȃ�j<br>
     *                      (�y��z1.0:���x���ɂ�锭�����ԑ������������i���S���x����{�r�����ԁj<br>
     *                             1.2:���x��1�P�̂ŕK�v�Ȕ������� �� ��{��������<br>
     *                                 ���x��2�P�̂ŕK�v�Ȕ������� �� ��{�������� * 1.2<br>
     *                                 ���x��3�P�̂ŕK�v�Ȕ������� �� ��{�������� * 1.2 * 1.2<br>
     *                                 ���x��4�P�̂ŕK�v�Ȕ������� �� ��{�������� * 1.2 * 1.2 * 1.2 ���Ԃ��ݒ肳���)
     * @param prm_r_invoking_frames_lv_diff_base ��у��x�����̔������ԍ팸���� 0.0�`1.0 �i1.0��菬�����ƁA��у��x�����A�������Ԃ��Z�k�ɂȂ�B�Z�߂Ĕ�Ԃقǂ����j<br>
     *                      (�y��z1.0:�������у��x���ł��R�X�g��������,<br>
     *                             0.8:��у��x����2�̂Ƃ��A���̃��x���A�b�v�ɕK�v�Ȕ������� * 0.8<br>
     *                                 ��у��x����3�̂Ƃ��A���̃��x���A�b�v�ɕK�v�Ȕ������� * 0.8 * 0.8<br>
     *                                 ��у��x����4�̂Ƃ��A���̃��x���A�b�v�ɕK�v�Ȕ������� * 0.8 * 0.8 * 0.8
     *
     * @param prm_effecting_frames_base ��{���ʎ������ԁB<br>
     *                                0���w�肷��ƁA�u���������@�v�Ɖ��߂����B<br>
     *                                0���傫���l��ݒ肷��ƁA�u���ʎ��������@�v�Ɖ��߂����B<br>
     * @param prm_r_every_lv_effecting_frames �e���x���̌��ʎ������ԍ팸�����B�ʏ� 0.0�`1.0 �i�����x���قǎ����͒Z���j<br>
     *                      (�y��z1.0:���x���ɂ����ʎ������팸����,<br>
     *                             0.9:���x��1�P�̂œ����鎝������ �� ��{���ʎ�������<br>
     *                                 ���x��2�P�̂œ����鎝������ �� ��{���ʎ������� * 0.9<br>
     *                                 ���x��3�P�̂œ����鎝������ �� ��{���ʎ������� * 0.9 * 0.9<br>
     *                                 ���x��4�P�̂œ����鎝������ �� ��{���ʎ������� * 0.9 * 0.9 * 0.9  �Ƃ����������Ԃ��ݒ肳���)
     * @param prm_keep_cost_base ���ʎ������̊�{�ێ��R�X�g�B0�Ȃ�΁u�ێ��R�X�g�����v0���傫���l��ݒ肷��Ɓu�ێ��R�X�g�L�v�ƂȂ�B
     * @param prm_r_each_lv_keep_cost ���x�����̈ێ��R�X�g�������� �ʏ� 1.0�` (�����x���قǈێ��R�X�g��������j<br>
     *                      (�y��z1.0:���x���ɂ��ێ��R�X�g��������,<br>
     *                             1.1:���x��1�̂Ƃ��̈ێ��R�X�g �� ��{�ێ��R�X�g<br>
     *                                 ���x��2�̂Ƃ��̈ێ��R�X�g �� ��{�ێ��R�X�g * 1.1<br>
     *                                 ���x��3�̂Ƃ��̈ێ��R�X�g �� ��{�ێ��R�X�g * 1.1 * 1.1<br>
     *                                 ���x��4�̂Ƃ��̈ێ��R�X�g �� ��{�ێ��R�X�g * 1.1 * 1.1 * 1.1  �Ƃ����ێ��R�X�g���ݒ肳���)
     * @return
     */
    Magic(const char* prm_name, int* prm_pMP,
          int prm_max_level,
          magic_point prm_cost_base            , double prm_r_every_lv_cost            , double prm_r_cost_lv_diff_base,
          magic_time  prm_casting_frames_base  , double prm_r_every_lv_casting_frames  , double prm_r_casting_frames_lv_diff_base,
          magic_time  prm_invoking_frames_base , double prm_r_every_lv_invoking_frames , double prm_r_invoking_frames_lv_diff_base,
          magic_time  prm_effecting_frames_base, double prm_r_every_lv_effecting_frames,
          magic_point prm_keep_cost_base       , double prm_r_each_lv_keep_cost);

    void init();

    virtual void initialize() override {}

    virtual void onReset() override;

    virtual void nextFrame() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processFinal() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void save(std::stringstream& sts);

    virtual void loadProperties(std::stringstream& sts);

    /**
     * �r���J�n���s .
     * @param prm_new_level �r������V�������x��
     * @return �r�����s�̏�����
     * @retval  MAGIC_CAST_NG_INVOKING_NOW         ���ʔ������̂��߉r���s�������̂ŁA
     *                                             ���������Ȃ������B
     * @retval  MAGIC_CAST_NG_MP_IS_SHORT          MP�����Ȃ��r���s�������̂ŁA
     *                                             ���������Ȃ������B
     * @retval  MAGIC_CAST_NOTHING                 ���݂̃��x���Ɠ������x�����r�����悤�Ƃ��Ă���̂ŁA
     *                                             ���������Ȃ������B
     * @retval  MAGIC_CAST_CANCEL                  ���̃��x�����r�����A���݂̌��ʎ������x���Ɠ������x�����r���w�肵���̂ŁA
     *                                             ���r�����~�B�i���X�e�[�^�X�� STATE_NOTHING �ւ̑J�ڂ����s�����B
     * @retval  MAGIC_CAST_OK_LEVELUP              ���݂̌��ʎ������x����荂�����x�����r�����w��̂ŁA
     *                                             ���r���V�[�N�G���X�J�n�A�i���X�e�[�^�X�� STATE_CASTING �ւ̑J�ڂ����s�����B
     * @retval  MAGIC_CAST_LEVELDOWN               ���݂̌��ʎ������x�����Ⴂ���x�����r�����w��̂ŁA
     *                                             �����@���ʊJ�n effect(prm_new_level) �����s�����B
     * @retval  MAGIC_CAST_OK_CANCEL_AND_LEVELUP   ���̃��x�����r�����ɍĉr�����s�����Ƃ��Ă��āA�ĉr���̃��x�����A���݂̌��ʎ������x����荂�̂ŁA
     *                                             ���ĉr���V�[�N�G���X�J�n�A�i���X�e�[�^�X�� STATE_RE_CASTING �ւ̑J�ڂ����s�����B
     * @retval  MAGIC_CAST_CANCEL_AND_LEVELDOWN    ���̃��x�����r�����ɍĉr�����s�����Ƃ��Ă��āA�ĉr���̃��x�����A���݂̌��ʎ������x�����Ⴂ�̂ŁA
     *                                             �����@���ʊJ�n effect(prm_new_level) �����s�����B
     */
    virtual int cast(int prm_new_level);

    /**
     * ���@�r���J�n�R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * ���̃^�C�~���O�ŌĂяo�����B<BR>
     * �E�r�����ł͂Ȃ���ԁ����ʒ����x���ȊO�̃��x���̖��@�̉r�����s��<BR>
     * �E���݉r���������ʒ����x���ȊO�̃��x���̖��@�̉r�����s��<BR>
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level �r������V�������x��(1�` )
     */
    virtual void processCastBegin(int prm_now_level, int prm_new_level) = 0;

    /**
     * ���@�r�����R�[���o�b�N(���t���[���R�[���o�b�N) .
     * �y���Ӂz���x���_�E�����͂P�񂾂��R�[������ processCastFinish() �����s����܂��B
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level �r�����̐V�������x��(1�` )
     */
    virtual void processCastingBehavior(int prm_now_level, int prm_new_level) = 0;

    /**
     * ���@�r�����A�r���L�����Z�����̃R�[���o�b�N .
     * @param prm_now_level ���݂̃��x��(0�` )
     */
    virtual void processCastingCancel(int prm_now_level) = 0;

    /**
     * ���@�r���I���R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level �r���������������\��̐V�������x��(1�` )
     */
    virtual void processCastFinish(int prm_now_level, int prm_new_level, int prm_result_invoke) = 0;

    /**
     * �����J�n���s(�P�񂾂��R�[���o�b�N) .
     * @param prm_new_level ��������V�������x��
     * @return �������s�̏�����
     */
    virtual int invoke(int prm_new_level);

    /**
     * ���@�����J�n�R�[���o�b�N .
     * �����܂ł���Ɖr���L�����Z���͕s�Ƃ���B(�P�񂾂��R�[���o�b�N)
     * ���x���_�E�������Ăяo����܂��B
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level ���������悤�Ƃ��Ă���V�������x��(1�` )
     */
    virtual void processInvokeBegin(int prm_now_level, int prm_new_level) = 0;

    /**
     * ���@�������R�[���o�b�N(���t���[���R�[���o�b�N) .
     * �y���Ӂz���x���_�E�����͂P�񂾂��R�[������ processInvokeFinish() �����s����܂��B
     * @param prm_now_level ���݂̃��x��(0�` )
     * @param prm_new_level ���ݔ������̐V�������x��(1�` )
     */
    virtual void processInvokingBehavior(int prm_now_level, int prm_new_level) = 0;

    /**
     * ���@�������A�����L�����Z�����̃R�[���o�b�N .
     * �ʏ�͖��@�������ɃL�����Z���͂ł��Ȃ����A��ނ𓾂Ȃ��Ɏ���ɂ�苭���L�����Z�������ꍇ��
     * �Ăяo�����B
     * �Ⴆ�΁A��������MP���͊����Ă��܂����Ƃ��A���񂾂Ƃ��B
     * @param prm_now_level ���݂̃��x��(0�` )
     */
    virtual void processInvokingCancel(int prm_now_level) = 0;

    /**
     * ���@�����I���R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * ���x���_�E�������Ăяo����܂��B
     * @param prm_now_level ���@�����I�����O�́A���݂̃��x���B(0�` )
     * @param prm_new_level ���@�����I������́A���i���ׂ��V�������x���B(1�` )
     * @param prm_result_effect invoke()�̌���
     */
    virtual void processInvokeFinish(int prm_now_level, int prm_new_level, int prm_result_effect) = 0;

    /**
     * ���ʔ������s .
     * @param prm_level ���ʔ��������x��
     */
    virtual int effect(int prm_level);

    /**
     * ���@���ʎ����J�n�R�[���o�b�N(�P�񂾂��R�[���o�b�N) .
     * ���̃^�C�~���O�ŌĂяo�����
     * �E���@�����I�� �� ���@���ʎ����J�n���iprm_last_level < prm_now_level�j<BR>
     * �E���x���_�E�����s�� �i�蓮 or ���ʎ��Ԗ��� or �R�X�g���薂�@��MP�͊��j<BR>
     * @param prm_last_level ���ʎ������J�n�����O�̃��x���B(���x���A�b�v���F0�` �^���x���_�E�����F1�`)
     * @param prm_now_level ���ʎ������J�n���ꂽ���x���B(���x���A�b�v���F1�` �^���x���_�E�����F0�`)
     */
    virtual void processEffectBegin(int prm_last_level, int prm_now_level) = 0;

    /**
     * ���@���ʎ������R�[���o�b�N(���t���[���R�[���o�b�N) .
     * ���������@(effecting_frames_base_==0)�̖��@�͂P�񂾂��R�[���o�b�N����邱�ƂɂȂ�܂��B
     * �y���Ӂz���x��0�ł��A�����I�ɂ̓��x��0�̖��@�����ʎ������ƍl�����{���\�b�h�͌Ăяo���ꑱ���܂��B
     * @param prm_last_level  �ȑO�̃��x���B
     * @param prm_now_level ����(������)�̃��x���B
     */
    virtual void processEffectingBehavior(int prm_last_level, int prm_now_level) = 0;

    /**
     * ���̃��x���̖��@���r�����s�ł��邩���ׂ�
     * @param prm_new_level �r�����郌�x��
     * @retval MAGIC_CAST_NG_INVOKING_NOW       (-3)  ���ݔ������̂��ׁA�s��
     * @retval MAGIC_CAST_NG_MP_IS_SHORT        (-2)  ���x���A�b�v�r���ƂȂ邪�AMP������Ȃ����ׁA�s��
     * @retval MAGIC_CAST_CANCEL                (-1)  ���݉r�����ŁA�����̃��x���́A���݂̃��x���ƈ�v�B�܂�r���L�����Z���w���ɂȂ�B�i�\�E�s�\�Ō����Ή\�j
     * @retval MAGIC_CAST_NOTHING               (0)   �����̃��x���́A���݂̃��x���ƈ�v�B�Ȃɂ��w�����ĂȂ����ƂɂȂ�B�i�\�E�s�\�Ō����Ή\�j
     * @retval MAGIC_CAST_OK_LEVELUP            (1)   ���x���A�b�v�r���ƂȂ�BMP�������׉\
     * @retval MAGIC_CAST_LEVELDOWN             (2)   ���x���_�E���r���ƂȂ�B�������\
     * @retval MAGIC_CAST_OK_CANCEL_AND_LEVELUP (3)   ���݂̉r�����L�����Z�����Ẵ��x���A�b�v�r���ƂȂ�BMP�������׉\
     * @retval MAGIC_CAST_CANCEL_AND_LEVELDOWN  (4)   ���݂̉r�����L�����Z�����Ẵ��x���_�E���r���ƂȂ�B�������\
     */
    int chkCastAble(int prm_new_level);

    /**
     * ���̃��x���̖��@���������s���ł��邩���ׂ�
     * @param prm_new_level �������郌�x��
     * @return
     */
    int chkInvokeAble(int prm_new_level);

    /**
     * ���̃��x���̖��@�����ʂ����s���ł��邩���ׂ�
     * @param prm_level
     * @return
     */
    int chkEffectAble(int prm_level);

    /**
     * �_�E�����x�����s���̊Ҍ�MP���v�Z���ĕԂ� .
     * �c���ʎ����̊������悸��B
     * �������x���_�E�������ق��������ɂ��邽�߁B
     * @param prm_now_level ���݂̃��x��
     * @param prm_target_down_level �_�E�����x��
     * @return
     */
    magic_point calcReduceMp(int prm_now_level, int prm_target_down_level);

    virtual ~Magic();
};

}

#endif /*MAGIC_H_*/
