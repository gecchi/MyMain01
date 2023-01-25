#ifndef GGAF_LIB_MENUACTOR_H_
#define GGAF_LIB_MENUACTOR_H_
#include "GgafLibCommonHeader.h"

#include "jp/ggaf/core/util/RingLinkedList.hpp"
#include "jp/ggaf/core/actor/GroupHead.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicle.h"
#include "jp/ggaf/dx/actor/supporter/VecVehicleMvAssistant.h"
#include "jp/ggaf/dx/util/Util.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/actor/DefaultBoardSetActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"
#include "jp/ggaf/lib/actor/DefaultFramedBoardActor.h"
#include "jp/ggaf/lib/actor/menu/MenuActor.hpp"
#include "jp/ggaf/lib/actor/FontBoardActor.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"


namespace GgafLib {

/**
 * ���j���[ .
 * GUI�ȈՃ��j���[���ȒP�Ɏ������邽�߂̃e���v���[�g�ł��B<BR>
 * <b>�y�p��z</b><BR>
 * �E���j���[�A�C�e��              �c �J�[�\���őI�����\�ȃI�u�W�F�N�g�i�{�^������GUI���i�j���w���܂��B
 * �E���j���[���x��                �c �J�[�\���őI�����s�̕\���p�I�u�W�F�N�g�i�{�^������GUI���i�j���w���܂��B
 * �E�L�����Z���i���j���[�A�C�e���j�c �u�L�����Z���v�̓��삪���҂����GUI���i�̎����w���B�i��F [Cancel] �� [������] �A[�~] �{�^�����́j<BR>
 * �E����i�U�镑���j              �c ���[�U�[����ŁA���j���[�A�C�e���́u����v�̈ӎv��\��������w���B�i��F [ENTER]�L�[���������j<BR>
 * �E�L�����Z���i�U�镑���j        �c ���[�U�[����ŁA���j���[�A�C�e���́u�L�����Z���v�̈ӎv��\��������w���B�i��F [ESC]�L�[�������j<BR>
 * ���Ɂu�L�����Z�������v�ƌ����鎖�ɂ��āA�{�e�ł̐����ł́A<BR>
 * �w�u�L�����Z���i���j���[�A�C�e���j�v�ŁA�u����i�U�镑���j �v�����B�x<BR>
 * �Ƃ����\���ɂȂ�܂��B<BR>
 * �܂��A�Ⴆ�� [Yes][No] �{�^��������A[Yes] �{�^����I��������ԂŁAESC���͂�[No]�{�^���ɃJ�[�\���I�����ړ�����ꍇ�A<BR>
 *�wYes�̃��j���[�A�C�e���ŁA�u�L�����Z���i�U�镑���j�v�����̂ŁA�u�L�����Z���i���j���[�A�C�e���j�v�ɃJ�[�\���I�����ړ�����x
 * �Ƃ����\���ɂȂ�܂��B<BR>
 * �{�N���X�́u�L�����Z���i���j���[�A�C�e���j�v�u����i�U�镑���j�v�u�L�����Z���i�U�镑���j�v����ʈ������A
 * �����ɂ��ċ@�\���T�|�[�g���܂��B<BR>
 * �i��[OK]�{�^�����́u����i���j���[�A�C�e���j�v�ɂ��ē��ʈ������Ă��܂���j<BR>
 * @tparam T ��̂̃��j���[�ƂȂ�A�N�^�[�̌^
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
template<class T>
class MenuActor : public T {

protected:

    enum MenuItemWay {
        ITEM_RELATION_EX_NEXT = 0,
        ITEM_RELATION_EX_PREV,
        ITEM_RELATION_TO_CANCEL,
    };

    /** �t�F�[�h�C������ true */
    bool _with_rising;
    /** �t�F�[�h�A�E�g���� true */
    bool _with_sinking;
    /** �t�F�[�h�C�����J�n�����u�Ԃ̃t���[������ true */
    bool _is_just_risen;
    /** �t�F�[�h�A�E�g���J�n�����u�Ԃ̃t���[������ true */
    bool _is_just_sunk;
    /** �u����i�U�镑���j�v�����u�Ԃ̃t���[������ true */
    bool _is_just_decided;
    /** �u�L�����Z���i�U�镑���j�v�����u�Ԃ̃t���[������ true */
    bool _is_just_cancelled;

    bool _will_be_rising_next_frame;

    bool _will_be_sinking_next_frame;

    bool _will_be_just_decided_next_frame;

    bool _will_be_just_cancelled_next_frame;

    bool _can_controll;

    bool _will_be_able_to_controll;

    /** ���C���J�[�\���̕␳X���W */
    coord _x_cursor_adjust;
    /** ���C���J�[�\���̕␳Y���W */
    coord _y_cursor_adjust;
    /** ���C���J�[�\���̕␳Z���W */
    coord _z_cursor_adjust;
    /** ���C���J�[�\���ړ��惁�j���[�A�C�e���̑O�t���[����X���W */
    coord _x_cursor_target_prev;
    /** ���C���J�[�\���ړ��惁�j���[�A�C�e���̑O�t���[����Y���W */
    coord _y_cursor_target_prev;
    /** ���C���J�[�\���ړ��惁�j���[�A�C�e���̑O�t���[����Z���W */
    coord _z_cursor_target_prev;
    /** [r]���C���J�[�\�����A���j���[�A�C�e���Ԃ��ړ�����ۂɔ�₷�X�t���[���� */
    int _cursor_move_frames;
    /** [r]���C���J�[�\�����ړ����A���j���[�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊��� */
    float _cursor_move_p1;
    /** [r]���C���J�[�\�����ړ����A���j���[�A�C�e���Ԉړ������̍ō������猸�����J�n���銄�� */
    float _cursor_move_p2;
    /** [r]���C�����j���[�J�[�\�� */
    GgafDx::FigureActor* _pCursorActor;

    /**
     * �⏕�J�[�\�� .
     */
    class SubCursor {
    public:
        /** [r]�⏕�J�[�\���A�N�^�[ */
        GgafDx::FigureActor* _pActor;
        /** �I�𒆃C���f�b�N�X  */
        int _select_index;
        /** �⏕�J�[�\���̕␳X���W */
        coord _x_adjust;
        /** �⏕�J�[�\���̕␳Y���W */
        coord _y_adjust;
        /** �⏕�J�[�\���̕␳Z���W */
        coord _z_adjust;
        /** �⏕�J�[�\���ړ��惁�j���[�A�C�e���̑O�t���[����X���W */
        coord _x_target_prev;
        /** �⏕�J�[�\���ړ��惁�j���[�A�C�e���̑O�t���[����Y���W */
        coord _y_target_prev;
        /** �⏕�J�[�\���ړ��惁�j���[�A�C�e���̑O�t���[����Z���W */
        coord _z_target_prev;
        /** [r]�⏕�J�[�\�����A���j���[�A�C�e���Ԃ��ړ�����ۂɔ�₷�X�t���[���� */
        int _move_frames;
        /** [r]�⏕�J�[�\�����ړ����A���j���[�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊��� */
        float _move_p1;
        /** [r]�⏕�J�[�\�����ړ����A���j���[�A�C�e���Ԉړ������̍ō������猸�����J�n���銄�� */
        float _move_p2;
    public:
        SubCursor() {
            _select_index = 0;
            _move_frames = 10;
            _move_p1 = 0.2;
            _move_p2 = 0.7;
            _x_target_prev = 0;
            _y_target_prev = 0;
            _z_target_prev = 0;
            _pActor = nullptr;
            _x_adjust = 0;
            _y_adjust = 0;
            _z_adjust = 0;
        }
        virtual ~SubCursor() {
        }
    };

protected:
    /**
     * ���C���J�[�\����I�����j���[�A�C�e��(_lstItems �̃A�N�e�B�u�v�f)�ֈړ������� .
     * �u�I���v�Ɓu�J�[�\���̈ړ��v�́A�ʁX�ōl���ĉ������B<BR>
     * �{���\�b�h�͗\�ߑI���ς݂̃��j���[�A�C�e���ցu�J�[�\���̈ړ��v�����ł���A���o���ʂ̏����ɓ������Ă��܂��B<BR>
     * �u�I���v���̂��s�����̂ł͂���܂���B�u�I���v�� selectItem() �ōs���܂��B<BR>
     * �܂��AselectItem() �������ŁA���� moveCursor() �͎��s����܂��B<BR>
     * �]���āAmoveCursor() �P�̂ŌĂяo�����͖w�Ǒz�肵�ĂȂ��̂Œ��ӂ��ĉ������B<BR>
     * �J�[�\���ړ����̌��ʉ���炷�ꍇ���́A�I�[�o�[���C�h���čĒ�`���邱�ƂŎ������Ă��������B<BR>
     * ���̏������ɏ�� moveCursor() ���Ăяo���̂�Y��Ȃ��悤�ɁB<BR>
     * @param prm_smooth �X���[�Y�ړ����邩�ۂ�
     */
    virtual void moveCursor(bool prm_smooth = true);

    /**
     * �⏕�J�[�\����I�����j���[�A�C�e���ֈړ������� .
     * �u�I���v�Ɓu�J�[�\���̈ړ��v�́A�ʁX�ōl���ĉ������B<BR>
     * �{���\�b�h�͗\�ߑI���ς݃��j���[�A�C�e���ցu�J�[�\���̈ړ��v�����ł���A���o���ʂ̏����ɓ������Ă��܂��B<BR>
     * �u�I���v���̂��s�����̂ł͂���܂���B�u�I���v�� selectItemBySubCursor() �ōs���܂��B<BR>
     * �܂��AselectItemBySubCursor() �������ŁA���� moveSubCursor() �͎��s����܂��B<BR>
     * �]���āAmoveCursor() �P�̂ŌĂяo�����͖w�Ǒz�肵�ĂȂ��̂Œ��ӂ��ĉ������B<BR>
     * �J�[�\���ړ����̌��ʉ���炷�ꍇ���́A�I�[�o�[���C�h���čĒ�`���邱�ƂŎ������Ă��������B<BR>
     * ���̏������ɏ�� moveSubCursor() ���Ăяo���̂�Y��Ȃ��悤�ɁB<BR>
     * @param prm_subcur_no
     * @param prm_smooth
     */
    virtual void moveSubCursor(int prm_subcur_no, bool prm_smooth = true);

public:
    /** [r]���j���[�A�C�e���̃��X�g�A�A�N�e�B�u�̓��C���J�[�\�����I������Ă��� */
    GgafCore::RingLinkedList<GgafDx::FigureActor> _lstItems;
    /** [r]���̑��\�����j���[�A�C�e���̃��X�g */
    GgafCore::RingLinkedList<GgafDx::FigureActor> _lstLabelActors;
    /** [r]���C���J�[�\�����ړ��������j���[�A�C�e���C���f�b�N�X�̃q�X�g���[(0�`N�A�A�������͑S�� -1 ) */
    GgafCore::RingLinkedList<int> _lstMvCursorHistory;
    /** [r]�I���������j���[�A�C�e���C���f�b�N�X�̃q�X�g���[(0�`N�A�A�������͑S�� -1 ) */
    GgafCore::RingLinkedList<int> _lstMvSelectHistory;
    /** [r]���j���[�t�F�C�h�C���E�A�E�g���̃t���[���� */
    frame _fade_frames;
    /** [r]���j���[�t�F�C�h�C���E�A�E�g���̃A���t�@���x */
    float _velo_alpha_fade;
    /** [r]�T�u���j���[�̃��X�g */
    GgafCore::RingLinkedList<MenuActor<T> > _lstSubMenu;
    /** [r]�T�u�J�[�\���̃��X�g */
    GgafCore::RingLinkedList<SubCursor> _lstSubCursor;

public:
    /**
     * �R���X�g���N�^ .
     * �y���Ӂz��������񊈓���Ԃ��f�t�H���g�Ƃ��Ă��܂��B<BR>
     * ��̓I�ɂ� T::inactivateImmed(); ���R�[�����Ă��܂��B
     * @param prm_name
     * @param prm_model ���f�����ʖ�
     */
    MenuActor(const char* prm_name, const char* prm_model);

    /**
     * ���ݓ��͂��󂯕t�����Ă����Ԃ���Ԃ� .
     * �T�u���j���[���\������Ă���ԓ��́A����s�ɂȂ�A�{���\�b�h��false��Ԃ��܂��B
     * @return true:�R���g���[���\���/false:�R���g���[���s�\���
     */
    virtual bool canControll() {
        return _can_controll;
    }

    /**
     * ���͂��󂯕t���𖳌� .
     * �I��������ɌĂяo���A���̎g�p��z��B
     */
    virtual void disableControll() {
        _will_be_able_to_controll = false;
    }

    /**
     * ���͂��󂯕t����L�� .
     */
    virtual void enableControll() {
        _will_be_able_to_controll = true;
    }

    /**
     * ���j���[�t�F�C�h�C���E�A�E�g���̃A���t�@���x��ݒ� .
     * @param prm_menu_fade_frames �t�F�[�h�t���[������
     */
    virtual void setFadeFrames(frame prm_menu_fade_frames) {
        _fade_frames = prm_menu_fade_frames;
        if (prm_menu_fade_frames == 0) {
            _velo_alpha_fade = 1.0;
        } else {
            _velo_alpha_fade = 1.0 / prm_menu_fade_frames;
        }
    }

    /**
     * �I���\�ȃ��j���[�A�C�e����ǉ����A���j���[�A�C�e���Ԃ̃I�[�_�[���A���ǉ����� .
     * �ǉ����ꂽ���j���[�A�C�e���̓��j���[�A�C�e��(this)�̎q�ɓo�^����邽�߁A
     * ���j���[�A�C�e�����^�X�N�c���[�ɓo�^�����Ȃ�� delete ����K�v�͂Ȃ��B
     * �y���Ӂz<BR>
     * ����Z���W�Ȃ�΁A��� addItem() ���������A����O�ɕ\���ƂȂ�B<BR>
     * @param prm_pItem ���j���[�A�C�e��
     * @param prm_x_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_y_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     * @param prm_z_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuZ���W
     */
    virtual void addItem(GgafDx::FigureActor* prm_pItem,
                         coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * �I���\���j���[�A�C�e���ǉ����A���j���[�A�C�e���Ԃ̃I�[�_�[���A���ǉ����� .
     * �ǉ����ꂽ���j���[�A�C�e���̓��j���[�A�C�e��(this)�̎q�ɓo�^����邽�߁A
     * ���j���[�A�C�e�����^�X�N�c���[�ɓo�^�����Ȃ�� delete ����K�v�͂Ȃ��B<BR>
     * �y���Ӂz<BR>
     * ����Z���W�Ȃ�΁A��� addItem() ���������A����O�ɕ\���ƂȂ�B<BR>
     * Z���W�́A�I�t�Z�b�g0���ݒ肳���B�܂胁�j���[�A�C�e���̐��Z���W�́A���݂̃��j���[��Z���W�ƈ�v����B<BR>
     * �������j���[��2D�ŁA���j���[�A�C�e���̕\���v���C�I���e�B�̍l�����K�v�ȏꍇ�́A�I�t�Z�b�g��-1���ɖ����ݒ���\�B
     * @param prm_pItem ���j���[�A�C�e��
     * @param prm_x_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_y_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     */
    virtual void addItem(GgafDx::FigureActor* prm_pItem,
                         coord prm_x_local, coord prm_y_local) {
        addItem(prm_pItem, prm_x_local, prm_y_local, 0);
    }

    /**
     * �I���\���j���[�A�C�e���ǉ����� .
     * �ʒu�͌ォ�� setPositionItem() �ŕύX�ł���B
     * @param prm_pItem ���j���[�A�C�e��
     */
    virtual void addItem(GgafDx::FigureActor* prm_pItem) {
        addItem(prm_pItem, 0, 0, 0);
    }

    /**
     * �ǉ����ꂽ�I���\���j���[�A�C�e���̍��W�ʒu��ݒ� .
     * @param prm_index_of_item ���j���[�A�C�e���̃C���f�b�N�X
     * @param prm_x_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_y_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     * @param prm_z_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuZ���W
     */
    virtual void setPositionItem(int prm_index_of_item, coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * �ǉ����ꂽ���j���[�A�C�e���̍��W�ʒu��ݒ� .
     * @param prm_index_of_item ���j���[�A�C�e���̃C���f�b�N�X
     * @param prm_x_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_y_local ���j���[�A�C�e���̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     */
    virtual void setPositionItem(int prm_index_of_item, coord prm_x_local, coord prm_y_local) {
        setPositionItem(prm_index_of_item, prm_x_local, prm_y_local, 0);
    }

    /**
     * �I��s�̕\���p���j���[���x��(���j���[���x��)��ǉ����� .
     * �y���Ӂz<BR>
     * ����Z���W�Ȃ�΁A����̏��� addLabel() ���������A����O�ɕ\���ƂȂ�B<BR>
     * @param prm_pItem �\���p���j���[���x���̃A�N�^�[
     * @param prm_x_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_y_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     * @param prm_z_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuZ���W
     */
    virtual void addLabel(GgafDx::FigureActor* prm_pLabel,
                          coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * �I��s�̕\���p���j���[���x����ǉ����� .
     * �y���Ӂz<BR>
     * ����Z���W�Ȃ�΁A����̏��� addLabel() ���������A����O�ɕ\���ƂȂ�B<BR>
     * Z���W�́A�I�t�Z�b�g0���ݒ肳���B�܂�\���p�A�N�^�[�̐��Z���W�́A���݂̃��j���[��Z���W�ƈ�v����B
     * �������j���[��2D�ŁA���j���[�A�C�e���̕\���v���C�I���e�B�̍l�����K�v�ȏꍇ�́A�I�t�Z�b�g��-1���ɖ����ݒ���\�B
     * @param prm_pItem �\���p���j���[���x���̃A�N�^�[
     * @param prm_x_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_y_local �\���p�I�u�W�F�N�g�̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     */
    virtual void addLabel(GgafDx::FigureActor* prm_pLabel,
                          coord prm_x_local, coord prm_y_local) {
        addLabel(prm_pLabel, prm_x_local, prm_y_local, 0);
    }

    /**
     * �I��s�̕\���p���j���[���x���ǉ����� .
     * �ʒu�͌ォ�� setPositionLabel() �ŕύX�ł���B
     * @param prm_pLabel �\���p���j���[���x���̃A�N�^�[
     */
    virtual void addLabel(GgafDx::FigureActor* prm_pLabel) {
        addLabel(prm_pLabel, 0, 0, 0);
    }

    /**
     * �ǉ����ꂽ�I��s�̕\���p���j���[���x���̍��W�ʒu��ݒ� .
     * @param prm_index_of_label ���j���[���x���̃C���f�b�N�X
     * @param prm_x_local ���j���[���x���̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_y_local ���j���[���x���̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     * @param prm_z_local ���j���[���x���̃��[�J�����W(0,0,0)����̑��ΈʒuZ���W
     */
    virtual void setPositionLabel(int prm_index_of_label, coord prm_x_local, coord prm_y_local, coord prm_z_local);

    /**
     * �ǉ����ꂽ�I��s�̕\���p���j���[���x���̍��W�ʒu��ݒ� .
     * @param prm_index_of_label ���j���[���x���̃C���f�b�N�X
     * @param prm_x_local ���j���[���x���̃��[�J�����W(0,0,0)����̑��ΈʒuX���W
     * @param prm_y_local ���j���[���x���̃��[�J�����W(0,0,0)����̑��ΈʒuY���W
     */
    virtual void setPositionLabel(int prm_index_of_label, coord prm_x_local, coord prm_y_local) {
        setPositionLabel(prm_index_of_label, prm_x_local, prm_y_local, 0);
    }

    /**
     * ���C���J�[�\���I�u�W�F�N�g��ݒ肷�� .
     * �y���Ӂz<BR>
     * �J�[�\���ړ��𐧌䂷�邽�߁AMenuActor<T>::processBehavior() ���ŁA<BR>
     * _pCursorActor->getVecVehicle()->behave(); <BR>
     * �����s���Ă��܂��B���������āA�����̃J�[�\���N���X�ŁA<BR>
     * getVecVehicle()->behave(); <BR>
     * �����s����K�v�͂���܂���B<BR>
     * @param prm_pCursorActor ���C���J�[�\��
     * @param prm_x_cursor_adjust ���j���[�A�C�e���Ƃ̏d�Ȃ��␳���邽�߂̉��Z����鍷��X���W
     * @param prm_y_cursor_adjust ���j���[�A�C�e���Ƃ̏d�Ȃ��␳���邽�߂̉��Z����鍷��Y���W
     * @param prm_z_cursor_adjust ���j���[�A�C�e���Ƃ̏d�Ȃ��␳���邽�߂̉��Z����鍷��Z���W
     * @param prm_cursor_move_frames ���C���J�[�\�������j���[�A�C�e���Ԉړ��ɔ�₷�t���[��(�f�t�H���g8�t���[��)
     * @param prm_cursor_move_p1 ���C���J�[�\�����ړ����A���j���[�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊���(�f�t�H���g0.2)
     * @param prm_cursor_move_p2 ���C���J�[�\�����ړ����A���j���[�A�C�e���Ԉړ������̍ō������猸�����J�n���銄��(�f�t�H���g0.6)
     */
    virtual void setMainCursor(GgafDx::FigureActor* prm_pCursorActor,
                               coord prm_x_cursor_adjust = 0,
                               coord prm_y_cursor_adjust = 0,
                               coord prm_z_cursor_adjust = 0,
                               int prm_cursor_move_frames = 10,
                               float prm_cursor_move_p1 = 0.2,
                               float prm_cursor_move_p2 = 0.6);

    /**
     * �⏕�J�[�\���I�u�W�F�N�g��ݒ肷�� .
     * �y���Ӂz<BR>
     * �J�[�\���ړ��𐧌䂷�邽�߁AMenuActor<T>::processBehavior() ���ŁA<BR>
     * _lstSubCursor.getFromFirst(i)->_pActor->getVecVehicle()->behave(); <BR>
     * �����s���Ă��܂��B���������āA�����̃J�[�\���N���X�ŁA<BR>
     * getVecVehicle()->behave(); <BR>
     * �����s����K�v�͂���܂���B<BR>
     * @param prm_pCursorActor �⏕�J�[�\��
     * @param prm_x_cursor_adjust ���j���[�A�C�e���Ƃ̏d�Ȃ��␳���邽�߂̉��Z����鍷��X���W
     * @param prm_y_cursor_adjust ���j���[�A�C�e���Ƃ̏d�Ȃ��␳���邽�߂̉��Z����鍷��Y���W
     * @param prm_z_cursor_adjust ���j���[�A�C�e���Ƃ̏d�Ȃ��␳���邽�߂̉��Z����鍷��Z���W
     * @param prm_cursor_move_frames �⏕�J�[�\�������j���[�A�C�e���Ԉړ��ɔ�₷�t���[��(�f�t�H���g8�t���[��)
     * @param prm_cursor_move_p1 �⏕�J�[�\�����ړ����A���j���[�A�C�e���Ԉړ������̑��x�O�`�ō����ɒB���鎞�_�̊���(�f�t�H���g0.2)
     * @param prm_cursor_move_p2 �⏕�J�[�\�����ړ����A���j���[�A�C�e���Ԉړ������̍ō������猸�����J�n���銄��(�f�t�H���g0.6)
     */
    virtual void addSubCursor(GgafDx::FigureActor* prm_pCursorActor,
                              coord prm_x_cursor_adjust = 0,
                              coord prm_y_cursor_adjust = 0,
                              coord prm_z_cursor_adjust = 0,
                              int prm_cursor_move_frames = 10,
                              float prm_cursor_move_p1 = 0.2,
                              float prm_cursor_move_p2 = 0.6);

    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(���g��From �� To) .
     * addItem(GgafDx::FigureActor*) �ɂ��A�ǉ����s�����ƂŁA�����I��<BR>
     * ���A�O�A�̐��`�I�[�_�[���\�z����Ă��邪�A<BR>
     * ���̃��\�b�h�͂���Ƃ͕ʂɃ��j���[�A�C�e���Ԃ́u���v�A�u�O�v�A�̊֌W��ǉ��ݒ肷��B<BR>
     * �Ⴆ�΁A�u���v�L�[�Łu���v�A�u���v�L�[�Łu�߂�v�Ƃ�������ɂȂ��Ă���Ƃ���ɁA
     * ����Ɂu���v�u���v�̈ړ����ʓr�ݒ肷��Ƃ������g�p���@��z��B<BR>
     * @param prm_index_of_from_item �A�����̃��j���[�A�C�e���̃C���f�b�N�X
     * @param prm_index_of_to_item �A�����̃��j���[�A�C�e���̃C���f�b�N�X����
     *                            �u���v�ɑΉ�����A����̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual void relateItemToExNext(int prm_index_of_from_item, int prm_index_of_to_item);

    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(item1 �� item2  �� item3) .
     * @param prm_index_of_item1 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X1
     * @param prm_index_of_item2 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X2
     * @param prm_index_of_item3 �g���A�����郁�j���[�A�C�e���̃C���f�b�N�X3
     */
    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3 );

    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4 );

    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4,
                                    int prm_index_of_item5 );

    virtual void relateItemToExNext(int prm_index_of_item1,
                                    int prm_index_of_item2,
                                    int prm_index_of_item3,
                                    int prm_index_of_item4,
                                    int prm_index_of_item5,
                                    int prm_index_of_item6 );

//    virtual void relateItemToExNext(int prm_index_of_fromitem, ...);

    /**
     * ���j���[�A�C�e���Ԃ̃I�[�_�[�A�����g���ݒ�(From �� ���g��To) .
     * addItem(GgafDx::FigureActor*) �ɂ��A�ǉ����s�����ƂŁA�����I��<BR>
     * ���A�O�A�̐��`�I�[�_�[���\�z����Ă��邪�A<BR>
     * ���̃��\�b�h�͂���Ƃ͕ʂɃ��j���[�A�C�e���Ԃ́u�O�v�A�u���v�A�̊֌W��ǉ��ݒ肷��B<BR>
     * �Ⴆ�΁A�u���v�L�[�Łu���v�A�u���v�L�[�Łu�߂�v�Ƃ�������ɂ����ꍇ��
     * �u���v�u���v�̈ړ����ݒ肷��Ƃ������g�p���@��z��B<BR>
     * @param prm_index_of_fromitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X
     * @param prm_index_of_toitem �A�����̃��j���[�A�C�e���̃C���f�b�N�X����
     *                            �u�O�v�ɑΉ�����A����̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual void relateItemToExPrev(int prm_index_of_fromitem, int prm_index_of_toitem);

    /**
     * �������j���[�A�C�e���S�Ăɑ΂��A�u�L�����Z���i���j���[�A�C�e���j�v�ւ̃I�[�_�[�A�����g���ݒ肷�� .
     * @param prm_index_of_cancel_item �L�����Z���i���j���[�A�C�e���j�ւ̃��j���[�A�C�e���C���f�b�N�X
     */
    virtual void relateAllItemToCancel(int prm_index_of_cancel_item);

    /**
     * ���j���[�ɐݒ肳��Ă��郁�C���J�[�\�����擾 .
     * @return ���C���J�[�\���I�u�W�F�N�g
     */
    virtual GgafDx::FigureActor* getMainCursor();

    /**
     * ���j���[�ɐݒ肳��Ă���⏕�J�[�\�����擾 .
     * @param prm_subcur_no �⏕�J�[�\���ԍ�
     * @return �⏕�J�[�\���I�u�W�F�N�g
     */
    virtual GgafDx::FigureActor* getSubCursor(int prm_subcur_no);

    /**
     * ���C���J�[�\���Łu���v�̃��j���[�A�C�e��(�A��isActive())�I�������C���J�[�\�����ړ� .
     * onSelect() �R�[���o�b�N�͕K���������܂��B<BR>
     */
    virtual void selectNext(bool prm_smooth = true);

    /**
     * ���C���J�[�\���Łu�O�v�̃��j���[�A�C�e��(�A��isActive())�I�������C���J�[�\�����ړ� .
     * onSelect() �R�[���o�b�N�͕K���������܂��B<BR>
     */
    virtual void selectPrev(bool prm_smooth = true);

    /**
     * ���C���J�[�\���Łu�i�ʂ́j���v�̃��j���[�A�C�e��(�A��isActive())�I�������C���J�[�\�����ړ� .
     * onSelect() �R�[���o�b�N�͕K���������܂��B<BR>
     */
    virtual void selectExNext(bool prm_smooth = true);

    /**
     * ���C���J�[�\���Łu�i�ʂ́j�O�v�̃��j���[�A�C�e��(�A��isActive())�I�������C���J�[�\�����ړ� .
     * onSelect() �R�[���o�b�N�͕K���������܂��B<BR>
     */
    virtual void selectExPrev(bool prm_smooth = true);

    /**
     * ���C���J�[�\���Łu�L�����Z���v���j���[�A�C�e���I�������C���J�[�\�����ړ� .
     * onSelect() �R�[���o�b�N�͕K���������܂��B<BR>
     */
    virtual void selectCancel(bool prm_smooth = true);

    /**
     * ���C���J�[�\���Ŏw��̃C���f�b�N�X�̃��j���[�A�C�e�����u�I���v���A���C���J�[�\�����ړ������� .
     * onSelect() �R�[���o�b�N�͕K���������܂��B<BR>
     * ������ moveCursor() ���R�[���o�b�N����A���C���J�[�\�����ړ����邱�ƂɂȂ�B<BR>
     * ���Ɏw��̃C���f�b�N�X�I�𒆂̏ꍇ�̓��C���J�[�\���͉����ړ������B<BR>
     * ���łɁA�����C���f�b�N�X�̃��j���[�A�C�e���I�u�W�F�N�g���Q�b�g�o����B<BR>
     * @param prm_index �^�[�Q�b�g�̃��j���[�A�C�e���C���f�b�N�X
     * @return prm_index�̃��j���[�A�C�e���I�u�W�F�N�g
     */
    virtual GgafDx::FigureActor* selectItem(int prm_index, bool prm_smooth = true);

    /**
     * �⏕�J�[�\���Ŏw��̃C���f�b�N�X�̃��j���[�A�C�e�����u�I���v���A�⏕�J�[�\�����ړ������� .
    * onSelect() �R�[���o�b�N�͔������܂���B<BR>
     * ������ moveSubCursor() ���R�[���o�b�N����A���C���J�[�\�����ړ����邱�ƂɂȂ�B<BR>
     * ���Ɏw��̃C���f�b�N�X�I�𒆂̏ꍇ�̓��C���J�[�\���͉����ړ������B<BR>
     * ���łɁA�����C���f�b�N�X�̃��j���[�A�C�e���I�u�W�F�N�g���Q�b�g�o����B<BR>
     * @param prm_subcur_no �⏕�J�[�\���ԍ�
     * @param prm_index �^�[�Q�b�g�̃��j���[�A�C�e���C���f�b�N�X
     * @return prm_index�̃��j���[�A�C�e���I�u�W�F�N�g
     */
    virtual GgafDx::FigureActor* selectItemBySubCursor(int prm_subcur_no, int prm_item_index, bool prm_smooth = true);

    /**
     * ���C���J�[�\���Ŏw��̃��j���[�A�C�e�����u�I���v���A���C���J�[�\�����ړ������� .
     * �����̃^�[�Q�b�g���j���[�A�C�e���̃C���f�b�N�X�𒲂ׂāAselectItem(index); �����s���܂��B
     * @param prm_item �^�[�Q�b�g���j���[�A�C�e��
     * @return �^�[�Q�b�g�̃��j���[�A�C�e���C���f�b�N�X
     */
    virtual int selectItem(GgafDx::FigureActor* prm_item, bool prm_smooth = true);

    virtual int selectItemIfPossible(GgafDx::FigureActor* prm_item, bool prm_smooth = true);

    /**
     * �⏕�J�[�\���Ŏw��̃��j���[�A�C�e�����u�I���v���A�⏕�J�[�\�����ړ������� .
     * ������ moveSubCursor() ���R�[���o�b�N����A�J�[�\�����ړ����邱�ƂɂȂ�B<BR>
     * ���Ɏw��̃C���f�b�N�X�I�𒆂̏ꍇ�̓J�[�\���͉����ړ������B<BR>
     * ���łɁA�������j���[�A�C�e���I�u�W�F�N�g�̃C���f�b�N�X���Q�b�g�o����B<BR>
     * @param prm_subcur_no �⏕�J�[�\���ԍ�
     * @param prm_item �^�[�Q�b�g�̃��j���[�A�C�e��
     * @return
     */
    virtual int selectItemBySubCursor(int prm_subcur_no, GgafDx::FigureActor* prm_item, bool prm_smooth = true);

    /**
     * ���݃��C���J�[�\�����I�𒆂̃��j���[�A�C�e���̃C���f�b�N�X���擾 .
     * @return �I�𒆂̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual int getSelectedIndex();

    /**
     * ���ݕ⏕�J�[�\�����I�𒆂̃��j���[�A�C�e���̃C���f�b�N�X���擾 .
     * @param prm_subcur_no �⏕�J�[�\���ԍ�
     * @return �I�𒆂̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual int getSelectedIndexOnSubCursor(int prm_subcur_no);

    /**
     * ���݃��C���J�[�\�����I�𒆂̃��j���[�A�C�e���̃I�u�W�F�N�g���擾 .
     * @return �I�𒆂̃��j���[�A�C�e���I�u�W�F�N�g
     */
    virtual GgafDx::FigureActor* getSelectedItem();

    /**
     * ���ݕ⏕�J�[�\�����I�𒆂̃��j���[�A�C�e���̃I�u�W�F�N�g���擾 .
     * @param prm_subcur_no �⏕�J�[�\���ԍ�
     * @return �I�𒆂̃��j���[�A�C�e���I�u�W�F�N�g
     */
    virtual GgafDx::FigureActor* getSelectedItemOnSubCursor(int prm_subcur_no);

    /**
     * �ߋ��Ƀ��C���J�[�\�����I�𒆂��������j���[�A�C�e���̃C���f�b�N�X���擾 .
     * getMvCursorHistoryIndex(0) �� getSelectedIndex() �Ɠ����ł��B
     * �w��̉ߋ����Ȃ��ꍇ�� -1 ��Ԃ��܂��B
     * @param prm_n ��ߋ��̃J�[�\���ʒu��(0 �`)
     * @return �I�𒆂������̃��j���[�A�C�e���I�u�W�F�N�g�̃C���f�b�N�X�i�����ꍇ�� -1�j
     */
    virtual int getMvCursorHistoryIndex(int prm_n);

    /**
     * �u����i�U�镑���j�v���s��ꂽ���ɁA���̃��j���[�A�C�e���̃C���f�b�N�X��Ԃ��܂� .
     * ����ȊO�̎��� ��� -1 ��Ԃ��܂�<BR>
     * �����j���[�̑I�����ڂ����肳�ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �� getOnDecidedIndex() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA���莞�̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onDecision() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B<BR>
     * @return ���肳�ꂽ���F���̃��j���[�A�C�e���̃C���f�b�N�X(>=0)�^�������肳��Ă��Ȃ��ꍇ�F��� -1
     */
    virtual int getOnDecidedIndex();

    /**
     * �u����i�U�镑���j�v���s��ꂽ���ɁA���̃��j���[�A�C�e����Ԃ��܂� .
     * ����ȊO�̎��� ��� nullptr ��Ԃ��܂�<BR>
     * �����j���[�̑I�����ڂ����肳�ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �� getOnDecidedItem() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA���莞�̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onDecision() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B<BR>
     * @return ���肳�ꂽ���F���̃��j���[�A�C�e���^�������肳��Ă��Ȃ��ꍇ�F��� nullptr
     */
    virtual GgafDx::FigureActor* getOnDecidedItem();

    /**
     * �u�L�����Z���i�U�镑���j�v���s��ꂽ���ɁA���̃��j���[�A�C�e���̃C���f�b�N�X��Ԃ��܂� .
     * ����ȊO�̎��� ��� -1 ��Ԃ��܂�<BR>
     * �����j���[�̑I�����ڂ��L�����Z�����ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �� getOnCancelledIndex() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA�L�����Z�����̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onCancel() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B<BR>
     * @return �L�����Z�����ꂽ���F���̃��j���[�A�C�e���̃C���f�b�N�X(>=0)�^�����L�����Z������Ă��Ȃ��ꍇ�F��� -1
     */
    virtual int getOnCancelledIndex();

    /**
     * �u�L�����Z���i�U�镑���j�v���s��ꂽ���ɁA���̃��j���[�A�C�e����Ԃ��܂� .
     * ����ȊO�̎��� ��� -1 ��Ԃ��܂�<BR>
     * �����j���[�̑I�����ڂ��L�����Z�����ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �� getOnCancelledItem() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA�L�����Z�����̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onCancel() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B<BR>
     * @return �L�����Z�����ꂽ���F���̃��j���[�A�C�e���^�����L�����Z������Ă��Ȃ��ꍇ�F��� nullptr
     */
    virtual GgafDx::FigureActor* getOnCancelledItem();

    /**
     * �I��Ώۃ��j���[�A�C�e���̃I�u�W�F�N�g���擾 .
     * @param prm_index �擾�������I��Ώۃ��j���[�A�C�e���̃C���f�b�N�X(0�`)
     * @return ���j���[�A�C�e���I�u�W�F�N�g
     */
    virtual GgafDx::FigureActor* getItem(int prm_index);

    /**
     * �\���p���j���[�A�C�e���̃I�u�W�F�N�g���擾 .
     * @param prm_index �擾�������\���p���j���[�A�C�e���̃C���f�b�N�X(0�`)
     * @return �\���p���j���[�A�C�e���I�u�W�F�N�g
     */
    virtual GgafDx::FigureActor* getLabel(int prm_index);

    /**
     * �u����i�U�镑���j�v�����A�Ƃ������̐����������������� .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B <BR>
     * (�Ⴆ�� Enter�L�[�������ꂽ��true��Ԃ� ���W�b�N��) <BR>
     * ����t���[���� condDecision() �� condCancel() �̏��������͂ǂ��炩������������A
     * ����D�揇�ʂ́AcondDecision() �̕�����ł��B<BR>
     * @return true:�u����i�U�镑���j�v�̏������� / false:�s����
     */
    virtual bool condDecision() = 0;

    /**
     * �u�L�����Z���i�U�镑���j�v�����A�Ƃ������̐����������������� .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B<BR>
     * (�Ⴆ�� ESC�L�[�������ꂽ��true��Ԃ� ���W�b�N��) <BR>
     * ����t���[���� condDecision() �� condCancel() �̏��������͂ǂ��炩������������A
     * ����D�揇�ʂ́AcondDecision() �̕�����ł��B<BR>
     * @return true:�u�L�����Z���i�U�镑���j�v�̏������� / false:�s����
     */
    virtual bool condCancel() = 0;

    /**
     * ���C���J�[�\�����u���̃��j���[�A�C�e���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * (�Ⴆ�� ���L�[�������ꂽ��true��Ԃ� ���W�b�N��) <BR>
     * @return true:�u���̃��j���[�A�C�e���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectNext() = 0;

    /**
     * ���C���J�[�\�����u�O�̃��j���[�A�C�e���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * (�Ⴆ�� ���L�[�������ꂽ��true��Ԃ� ���W�b�N��) <BR>
     * @return true:�u�O�̃��j���[�A�C�e���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectPrev() = 0;

    /**
     * ���C���J�[�\�����u������̕ʂ̎��̃��j���[�A�C�e���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u������̕ʂ̎��̃��j���[�A�C�e���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectExNext() = 0;

    /**
     * ���C���J�[�\�����u������̕ʂ̑O�̃��j���[�A�C�e���v�ֈړ������������������ .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u������̕ʂ̑O�̃��j���[�A�C�e���v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectExPrev() = 0;

    /**
     * ���C���J�[�\�����u�L�����Z���i���j���[�A�C�e���j�v�֔�ԏ������������� .
     * ���ʃN���X�ŃI�[�o�[���C�h���āA�������������Ă��������B
     * @return true:�u�L�����Z���i���j���[�A�C�e���j�v�ֈړ��̏������� / false:�s����
     */
    virtual bool condSelectCancel() = 0;

    /**
     * ����́u���j���[�A�C�e���v���I�������������������� .
     * �}�E�X�|�C���^�Ŏw���A�V���[�g�J�b�L�[�������ȂǂŁA
     * ����̏����Ń��j���[�A�C�e����I���������ꍇ�A�����Ɏ�������B
     * @return �I�����ꂽ���j���[�A�C�e���B nullptr �̏ꍇ�́A���j���[�A�C�e���I���͎��s����Ȃ��B�E
     */
    virtual GgafDx::FigureActor* condSelectItem() {
        return nullptr;
    }


    /**
     * �u����i�U�镑���j�v���ꂽ�ꍇ�ɌĂяo�����R�[���o�b�N�B
     * ������I�[�o�[���C�h���Ď������Ă��������B<BR>
     * �����j���[�̑I�����ڂ����肳�ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �ŁAgetOnDecidedIndex() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA���莞�̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onDecision() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B
     * @param prm_pItem ���肳�ꂽ���j���[�A�C�e��
     * @param prm_item_index ���肳�ꂽ���j���[�A�C�e���̃C���f�b�N�X
     */
    virtual void onDecision(GgafDx::FigureActor* prm_pItem, int prm_item_index) = 0;

    /**
     * �u�L�����Z���i�U�镑���j�v���ꂽ�ꍇ�ɌĂяo�����R�[���o�b�N�B .
     * ������I�[�o�[���C�h���Ď������Ă��������B<BR>
     * �����j���[�̑I�����ڂ��L�����Z�����ꂽ�ꍇ�̏����L�q�R�[�h�̏ꏊ�ɂ��ā�<BR>
     * processBehavior() �ŁAgetCancelIndex() �̖߂�l�𖈃t���[�����ׂ邱�ƂŁA�L�����Z�����̏������L�q���邱�Ƃ��\�B<BR>
     * ������� onCancel() ���Ăяo�����̂ŁA�I�[�o�[���C�h���A������ swith�`case ���L�q���Ă��ǂ��B<BR>
     * �ǂ���ł��ǂ����A���p���\�B
     * @param prm_pItem
     * @param prm_item_index
     */
    virtual void onCancel(GgafDx::FigureActor* prm_pItem, int prm_item_index) = 0;

    /**
     * ���C���J�[�\�����ړ������ꍇ�ɌĂяo�����R�[���o�b�N�B .
     * ������I�[�o�[���C�h���Ď������Ă��������B<BR>
     * �y�ߑ��z<BR>
     * onMoveCursor(int,int) �� onSelect(int,int) �̃R�[���o�b�N�^�C�~���O�̍��ɂ��āB<BR>
     * onMoveCursor(int,int) �́AselectXxxxx �n�̃��\�b�h���s�̍ہA�J�[�\�����ړ������ꍇ�̂݌Ăяo����܂��B<BR>
     * onSelect(int,int) �́AselectXxxxx �n �̃��\�b�h�����s���ɁA����Ȃ��Ăяo����܂�(���Ƃ��A�J�[�\�����ړ����Ȃ��Ă�)<BR>
     * �Ăяo����鏇���́AonMoveCursor(int,int)  �� onSelect(int,int) �̏��ł��B<BR>
     * @param prm_from_index �ړ����̃��j���[�A�C�e���̃C���f�b�N�X�i�����i�����́j�ꍇ�� -1�j
     * @param prm_selected_index   �ړ���̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual void onMoveCursor(int prm_from_index, int prm_selected_index) = 0;

    /**
     * ���C���J�[�\�������j���[�A�C�e����I�����ꂽ�ꍇ�ɌĂяo�����R�[���o�b�N�B .
     * ������I�[�o�[���C�h���Ď������Ă��������B<BR>
     * �y�ߑ��z<BR>
     * onMoveCursor(int,int) �� onSelect(int,int) �̃R�[���o�b�N�^�C�~���O�̍��ɂ��āB<BR>
     * onMoveCursor(int,int) �́AselectXxxxx �n�̃��\�b�h���s�̍ہA�J�[�\�����ړ������ꍇ�̂݌Ăяo����܂��B<BR>
     * onSelect(int,int) �́AselectXxxxx �n �̃��\�b�h�����s���ɁA����Ȃ��Ăяo����܂�(���Ƃ��A�J�[�\�����ړ����Ȃ��Ă�)<BR>
     * �Ăяo����鏇���́AonMoveCursor(int,int)  �� onSelect(int,int) �̏��ł��B<BR>
     * @param prm_from_index     �I�����i����I�������O�j�̃��j���[�A�C�e���̃C���f�b�N�X�i�����i�����́j�ꍇ�� -1�j
     * @param prm_selected_index �I���̃��j���[�A�C�e���̃C���f�b�N�X
     */
    virtual void onSelect(int prm_from_index, int prm_selected_index) = 0;


    /**
     * ���j���[��\���J�n���� .
     * �{�I�u�W�F�N�g�𐶐��A�^�X�N�ɒǉ���A�\�����������^�C�~���O�Ŏ��s���Ă��������B<BR>
     */
    virtual void riseMe();

    /**
     * ���j���[�\���J�n���̃R�[���o�b�N .
     * riseMe() ���s������A�P�񂾂��R�[���o�b�N����܂��B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h���Ă��������B<BR>
     */
    virtual void onRise();

    /**
     * ���j���[�\�����g�����W�V�������� .
     * riseMe() ���s �` �t�F�[�h�C�������܂ł̊ԃR�[�����ꑱ���܂��B
     * �A���t�@�����Z���t�F�[�h�C�����ʂ��s���A�A���t�@��1.0�ɂȂ�ΏI���B
     * �Ƃ����g�����W�V���������������ς݂ł��B<BR>
     * �g�����W�V������Ǝ��ɍs�������ꍇ�̓I�[�o�[���C�h���A�g�����W�V������������<BR>
     * _with_rising = false;<BR>
     * �����s���Ă��������B<BR>
     */
    virtual void processRising();

    /**
     * ���j���[�\���������̃R�[���o�b�N .
     * �K�v�ɉ����ăI�[�o�[���C�h���Ă��������B<BR>
     */
    virtual void onRiseDone();

    /**
     * ��ԃt���O�X�V��ǉ��̂��߃I�[�o�[���C�h .
     * ������ T::processNextFrame(); ���R�[�����Ă��܂��B
     */
    virtual void processNextFrame() override;

    /**
     * ���j���[�̐U�镑�� .
     * �J�[�\���̈ړ��y�сA���j���[�A�C�e���ƃJ�[�\�������j���[�̕�̍��W�ɒǏ]������
     * �����������ς݂ł��B<BR>
     * ���j���[�̐U�镑����ǉ�����ꍇ�́A�I�[�o�[���C�h���āA
     * �������ɏ�� processBehavior() ���Ăяo���̂�Y��Ȃ��悤�ɁB<BR>
     */
    virtual void processBehavior() override;

    /**
     * ���j���[����ďI�������� .
     */
    virtual void sinkMe();

    /**
     * riseMe()�����s���ꂽ���ォ�ۂ���Ԃ� .
     * @return true:�����x riseMe()�� ���s���ꂽ����ł���/false:�����ł͂Ȃ�
     */
    virtual bool hasJustRisen() {
        return _is_just_risen;
    }

    /**
     * sinkMe() �����s���ꂽ���ォ�ۂ���Ԃ� .
     * @return true:�����x sinkMe() �����s���ꂽ����ł���/false:�����ł͂Ȃ�
     */
    virtual bool hasJustSunk() {
        return _is_just_sunk;
    }

    /**
     * �u����i�U�镑���j�v���s��ꂽ���ォ�ۂ���Ԃ� .
     * @return rue:�����x �u����i�U�镑���j�v �����s���ꂽ����ł���/false:�����ł͂Ȃ�
     */
    virtual bool hasJustDecided() {
        if (_is_just_decided && _can_controll) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * �u�L�����Z���i�U�镑���j�v���s��ꂽ���ォ�ۂ���Ԃ� .
     * @return rue:�����x �u�L�����Z���i�U�镑���j�v �����s���ꂽ����ł���/false:�����ł͂Ȃ�
     */
    virtual bool hasJustCancelled() {
        if (_is_just_cancelled && _can_controll) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * ���j���[�������J�n���̃R�[���o�b�N .
     * sinkMe() ���s������A�P�񂾂��R�[���o�b�N����܂��B<BR>
     * �K�v�ɉ����ăI�[�o�[���C�h���Ă��������B<BR>
     */
    virtual void onSink();

    /**
     * ���j���[�����̃g�����W�V�������� .
     * sinkMe() ���s �` �t�F�[�h�A�E�g�����܂ł̊ԃR�[�����ꑱ���܂��B
     * �A���t�@�����Z���t�F�[�h�A�E�g���ʂ��s���A�A���t�@��1.0�ɂȂ�ΏI��
     * �Ƃ����g�����W�V���������������ς݂ł��B<BR>
     * �g�����W�V������Ǝ��ɍs�������ꍇ�̓I�[�o�[���C�h���A�g�����W�V������������<BR>
     * _with_sinking = false;<BR>
     * T::inactivateTreeImmed();<BR>
     * �����s���Ă��������B<BR>
     */
    virtual void processSinking();

    /**
     * ���j���[�������������̃R�[���o�b�N .
     * processSinking()���A_with_sinking = false; �ɂȂ����u�ԂɃR�[������܂��B
     * �K�v�ɉ����ăI�[�o�[���C�h���Ă��������B<BR>
     */
    virtual void onSinkDone();

    /**
     * �T�u���j���[��ǉ�����B
     * @param prm_pSubMenu �T�u���j���[
     */
    virtual void addSubMenu(MenuActor<T>* prm_pSubMenu);

    /**
     * �e���j���[��Ԃ� .
     * @return �e���j���[
     */
    virtual MenuActor<T>* getParentMenu();

    /**
     * �T�u���j���[���擾 .
     * ���O�� addSubMenu() �ŃT�u���j���[��ݒ肷��K�v������܂��B<BR>
     * @param prm_index �T�u���j���[�̃C���f�b�N�X
     * @return
     */
    virtual MenuActor<T>* getSubMenu(int prm_index = 0);

    /**
     * ���݃A�N�e�B�u�ȃT�u���j���[���擾 .
     * �T�u���j���[�����o�^�̏ꍇ�B�����͓o�^���Ă��Ă��A�A�N�e�B�u�ł͂Ȃ��ꍇ�� nullptr ��Ԃ��B
     * @return �A�N�e�B�u�ȃT�u���j���[/nullptr
     */
    virtual MenuActor<T>* getRisingSubMenu();

    /**
     * �T�u���j���[���A�N�e�B�u�ɂ��ĕ\������ .
     * ���O�� addSubMenu() �ŃT�u���j���[��ݒ肷��K�v������܂��B<BR>
     * �܂��A�{���\�b�h�ɂ�茻�݃A�N�e�B�u�ȃT�u���j���[(getRisingSubMenu())�́A
     * �����C���f�b�N�X�̃��j���[�ɕύX����܂��B
     * �T�u���j���[��\������ƁA�T�u���j���[�����(sinkCurrentSubMenu()) �܂ŁA
     * �Ăяo�������j���[�͑���s�\�ɂȂ�܂��B
     * @param prm_index �A�N�e�B�u�ɂ���T�u���j���[�̃C���f�b�N�X(�ǉ��������ԁB0�`)
     */
    virtual void riseSubMenu(int prm_index = 0);

    /**
     * �\�������ʒu���w�肵�ăT�u���j���[���N�� .
     * �������W�̓T�u���j���[���X���C�h���������ė����������W���w��B
     * @param prm_index �T�u���j���[�C���f�b�N�X(�ǉ��������ԁB0�`)
     * @param prm_target_x �T�u���j���[�\������X���W
     * @param prm_target_y �T�u���j���[�\������Y���W
     */
    virtual void riseSubMenu(int prm_index, coord prm_target_x, coord prm_target_y);

    /**
     * ���݃A�N�e�B�u�ȃT�u���j���[����ďI�������� .
     * ���O�� addSubMenu() �ŃT�u���j���[��ݒ肷��K�v������܂��B<BR>
     */
    virtual void sinkCurrentSubMenu();

    virtual ~MenuActor();
};


template<class T>
MenuActor<T>::MenuActor(const char* prm_name, const char* prm_model) :
  T(prm_name, prm_model),_lstItems(3) { //�S���j���[�A�C�e���}���R�ǉ��F�u���̑����v�u���̑��O�v�u�L�����Z���v�̂R��
    T::_class_name = "MenuActor";

    _fade_frames = 0;
    _velo_alpha_fade = 1.0;

    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _is_just_decided = false;
    _is_just_cancelled = false;
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = false;
    _will_be_just_decided_next_frame = false;
    _will_be_just_cancelled_next_frame = false;
    _can_controll = false;
    _will_be_able_to_controll = false;

    _cursor_move_frames = 10;
    _cursor_move_p1 = 0.2;
    _cursor_move_p2 = 0.7;
    _x_cursor_target_prev = T::_x;
    _y_cursor_target_prev = T::_y;
    _z_cursor_target_prev = T::_z;
    _pCursorActor = nullptr;
    _x_cursor_adjust = 0;
    _y_cursor_adjust = 0;
    _z_cursor_adjust = 0;

    for (int i = 0; i < 10; i++) {
        _lstMvCursorHistory.addLast(new int(-1), true);
        _lstMvSelectHistory.addLast(new int(-1), true);
    }
    _lstMvCursorHistory.createIndex();
    _lstMvSelectHistory.createIndex();
    T::inactivate(); //���j���[�Ȃ̂ŁA������Ԃ͔񊈓���Ԃ��f�t�H���g�Ƃ���
}

template<class T>
void MenuActor<T>::processNextFrame() {
    T::processNextFrame();
    if (T::_can_live_flg) {
        _is_just_risen = false;
        if (_will_be_rising_next_frame) {
            _with_rising = true;
            _is_just_risen = true;
            _will_be_rising_next_frame = false;
            onRise();
        }

        _is_just_sunk = false;
        if (_will_be_sinking_next_frame) {
            _with_sinking = true;
            _is_just_sunk = true;
            _will_be_sinking_next_frame = false;
            onSink();
        }

        if (_will_be_just_decided_next_frame && _can_controll) {
            _is_just_decided = true;
            _will_be_just_decided_next_frame = false;
            onDecision(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
        } else {
            _is_just_decided = false;
            _will_be_just_decided_next_frame = false;
        }

        if (_will_be_just_cancelled_next_frame && _can_controll) {
            _is_just_cancelled = true;
            _will_be_just_cancelled_next_frame = false;
            onCancel(_lstItems.getCurrent(), _lstItems.getCurrentIndex());
        } else {
            _is_just_cancelled = false;
            _will_be_just_cancelled_next_frame = false;
        }

        _can_controll = _will_be_able_to_controll;
    }
}

template<class T>
void MenuActor<T>::addItem(GgafDx::FigureActor* prm_pItem,
                           coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    prm_pItem->_x_local = prm_x_local;
    prm_pItem->_y_local = prm_y_local;
    prm_pItem->_z_local = prm_z_local;
    prm_pItem->setAlpha(T::_alpha); //�������������L������B
    prm_pItem->inactivate();
    _lstItems.addLast(prm_pItem, false);
//    T::appendChild(prm_pItem);
    T::appendGroupChild(prm_pItem);

}

template<class T>
void MenuActor<T>::setPositionItem(int prm_index_of_item, coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    GgafDx::FigureActor* p = getItem(prm_index_of_item);
    p->_x_local = prm_x_local;
    p->_y_local = prm_y_local;
    p->_z_local = prm_z_local;
}

template<class T>
void MenuActor<T>::addLabel(GgafDx::FigureActor* prm_pLabel,
                           coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    prm_pLabel->_x_local = prm_x_local;
    prm_pLabel->_y_local = prm_y_local;
    prm_pLabel->_z_local = prm_z_local;
    prm_pLabel->setAlpha(T::_alpha); //�������������L������B
    prm_pLabel->inactivate();
    _lstLabelActors.addLast(prm_pLabel, false);
    T::appendChild(prm_pLabel);
}

template<class T>
void MenuActor<T>::setPositionLabel(int prm_index_of_label, coord prm_x_local, coord prm_y_local, coord prm_z_local) {
    GgafDx::FigureActor* p = getLabel(prm_index_of_label);
    p->_x_local = prm_x_local;
    p->_y_local = prm_y_local;
    p->_z_local = prm_z_local;
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_from_item, int prm_index_of_to_item) {
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElemFrom =
            _lstItems.getElemFromFirst(prm_index_of_from_item);
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElemTo =
            _lstItems.getElemFromFirst(prm_index_of_to_item);
    pElemFrom->connect(ITEM_RELATION_EX_NEXT, pElemTo);
    pElemTo->connect(ITEM_RELATION_EX_PREV, pElemFrom);
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_item1,
                                      int prm_index_of_item2,
                                      int prm_index_of_item3 ) {
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem1 =
            _lstItems.getElemFromFirst(prm_index_of_item1);
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem2 =
            _lstItems.getElemFromFirst(prm_index_of_item2);
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem3 =
            _lstItems.getElemFromFirst(prm_index_of_item3);
    pElem1->connect(ITEM_RELATION_EX_NEXT, pElem2);
    pElem2->connect(ITEM_RELATION_EX_NEXT, pElem3);
    pElem3->connect(ITEM_RELATION_EX_PREV, pElem2);
    pElem2->connect(ITEM_RELATION_EX_PREV, pElem1);
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_item1,
                                      int prm_index_of_item2,
                                      int prm_index_of_item3,
                                      int prm_index_of_item4 ) {
    relateItemToExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3);
    relateItemToExNext(prm_index_of_item3, prm_index_of_item4);
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_item1,
                                      int prm_index_of_item2,
                                      int prm_index_of_item3,
                                      int prm_index_of_item4,
                                      int prm_index_of_item5 ) {
    relateItemToExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3);
    relateItemToExNext(prm_index_of_item3, prm_index_of_item4, prm_index_of_item5);
}

template<class T>
void MenuActor<T>::relateItemToExNext(int prm_index_of_item1,
                                      int prm_index_of_item2,
                                      int prm_index_of_item3,
                                      int prm_index_of_item4,
                                      int prm_index_of_item5,
                                      int prm_index_of_item6 ) {
    relateItemToExNext(prm_index_of_item1, prm_index_of_item2, prm_index_of_item3);
    relateItemToExNext(prm_index_of_item3, prm_index_of_item4, prm_index_of_item5);
    relateItemToExNext(prm_index_of_item5, prm_index_of_item6);
}


//template<class T>
//void MenuActor<T>::relateItemToExNext(int prm_index_of_fromitem, ...) {
//    va_list pArg;
//    va_start(pArg, prm_index_of_fromitem);         //�ϒ���������J�n
//        va_arg( argptr, int );
//
//
//
//    va_end(pArg);      //�ϒ���������I��
//}


template<class T>
void MenuActor<T>::relateItemToExPrev(int prm_index_of_fromitem, int prm_index_of_toitem) {
    _lstItems.getElemFromFirst(prm_index_of_fromitem)->connect(
            ITEM_RELATION_EX_PREV, _lstItems.getElemFromFirst(prm_index_of_toitem));
    _lstItems.getElemFromFirst(prm_index_of_toitem)->connect(
            ITEM_RELATION_EX_NEXT, _lstItems.getElemFromFirst(prm_index_of_fromitem));
}

template<class T>
void MenuActor<T>::relateAllItemToCancel(int prm_index_of_cancel_item) {
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pCancelElem =
            _lstItems.getElemFromFirst(prm_index_of_cancel_item);
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem =
            _lstItems.getElemFirst();
    int n = _lstItems.length();
    for (int i = 0; i < n; i++) {
        pElem->connect(ITEM_RELATION_TO_CANCEL, pCancelElem);
        pElem = pElem->_pNext;
    }
}


template<class T>
GgafDx::FigureActor* MenuActor<T>::selectItem(int prm_index, bool prm_smooth) {
    int n = getSelectedIndex();
#ifdef MY_DEBUG
    if (n == -1) {
        throwCriticalException("MenuActor<T>::selectItem() ���j���[�A�C�e�������o�^�ł� name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
    }
#endif
    if (n == prm_index) {
        //���ɑI�����Ă���B
        *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
        onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
        return _lstItems.getCurrent();
    } else {
#ifdef MY_DEBUG
        if (_lstItems.length() <= prm_index) {
            throwCriticalException("MenuActor<T>::selectItem() ���j���[�A�C�e���v�f���I�[�o�[ name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
        }
#endif
        GgafDx::FigureActor* pTargetItem = _lstItems.current(prm_index); //����ŃZ���N�g�I
        if (T::getActiveFrame() > 1) {
            moveCursor(prm_smooth);  //�X���[�Y�ړ��͈���
        } else {
            moveCursor(false); //�X���[�Y�ړ�����(�����I���ׂ̈�selectItem)
        }
        *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
        onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
        return pTargetItem;
    }
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::selectItemBySubCursor(int prm_subcur_no, int prm_item_index, bool prm_smooth) {
    int n = getSelectedIndexOnSubCursor(prm_subcur_no);
#ifdef MY_DEBUG
    if (n == -1) {
        throwCriticalException("MenuActor<T>::selectItemBySubCursor() ���j���[�A�C�e�������o�^�ł� name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item_index="<<prm_item_index);
    }
#endif
    //�⏕�J�[�\���̓R�[���o�b�N�Ȃ�
    if (n == prm_item_index) {
        //���ɑI�����Ă���B
        return _lstItems.getFromFirst(n);
    } else {
#ifdef MY_DEBUG
        if (_lstItems.length() <= prm_item_index) {
            throwCriticalException("MenuActor<T>::selectItemBySubCursor() ���j���[�A�C�e���v�f���I�[�o�[ name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item_index="<<prm_item_index);
        }
#endif
        _lstSubCursor.getFromFirst(prm_subcur_no)->_select_index = prm_item_index; //����ŃZ���N�g�I
        GgafDx::FigureActor* pTargetItem = _lstItems.getFromFirst(prm_item_index);

        if (T::getActiveFrame() > 1) {
            moveSubCursor(prm_subcur_no, prm_smooth);  //�X���[�Y�ړ��͈����ˑ�
        } else {
            moveSubCursor(prm_subcur_no, false); //�X���[�Y�ړ�����(�����I���ׂ̈�selectItem)
        }
        return pTargetItem;
    }
}

template<class T>
int MenuActor<T>::selectItem(GgafDx::FigureActor* prm_item, bool prm_smooth) {
    int index = _lstItems.indexOf(prm_item);
    if (index == -1) {
        throwCriticalException("MenuActor<T>::selectItem() ���̑O�Ƀ��j���[�A�C�e�������o�^�ł� name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item="<<prm_item->getName());
    }
    selectItem(index, prm_smooth);
    return index;
}

template<class T>
int MenuActor<T>::selectItemIfPossible(GgafDx::FigureActor* prm_item, bool prm_smooth) {
    int index = _lstItems.indexOf(prm_item);
    if (index >= 0) {
        selectItem(index, prm_smooth);
    }
    return index;
}

template<class T>
int MenuActor<T>::selectItemBySubCursor(int prm_subcur_no, GgafDx::FigureActor* prm_item, bool prm_smooth) {
    int index = _lstItems.indexOf(prm_item);
    if (index == -1) {
        throwCriticalException("MenuActor<T>::selectItemBySubCursor() ���̑O�Ƀ��j���[�A�C�e�������o�^�ł� name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_item="<<prm_item->getName());
    }
    selectItemBySubCursor(index, prm_subcur_no, prm_smooth);
    return index;
}

template<class T>
void MenuActor<T>::setMainCursor(GgafDx::FigureActor* prm_pCursorActor,
                                 coord prm_x_cursor_adjust,
                                 coord prm_y_cursor_adjust,
                                 coord prm_z_cursor_adjust,
                                 int prm_cursor_move_frames,
                                 float prm_cursor_move_p1,
                                 float prm_cursor_move_p2) {
    _pCursorActor = prm_pCursorActor;
    _pCursorActor->setAlpha(T::_alpha);
    _pCursorActor->inactivate();
    T::appendChild(_pCursorActor);
    _x_cursor_adjust = prm_x_cursor_adjust;
    _y_cursor_adjust = prm_y_cursor_adjust;
    _z_cursor_adjust = prm_z_cursor_adjust;
    _cursor_move_frames = prm_cursor_move_frames;
    _cursor_move_p1 = prm_cursor_move_p1;
    _cursor_move_p2 = prm_cursor_move_p2;
    selectItem(0);
}

template<class T>
void MenuActor<T>::addSubCursor(GgafDx::FigureActor* prm_pCursorActor,
                                 coord prm_x_cursor_adjust,
                                 coord prm_y_cursor_adjust,
                                 coord prm_z_cursor_adjust,
                                 int prm_cursor_move_frames,
                                 float prm_cursor_move_p1,
                                 float prm_cursor_move_p2) {
    MenuActor<T>::SubCursor* pSubCursor = NEW MenuActor<T>::SubCursor();
    pSubCursor->_pActor = prm_pCursorActor;
    pSubCursor->_pActor->setAlpha(T::_alpha);
    pSubCursor->_pActor->inactivate();
    pSubCursor->_select_index = 0;
    pSubCursor->_x_adjust = prm_x_cursor_adjust;
    pSubCursor->_y_adjust = prm_y_cursor_adjust;
    pSubCursor->_z_adjust = prm_z_cursor_adjust;
    pSubCursor->_move_frames = prm_cursor_move_frames;
    pSubCursor->_move_p1 = prm_cursor_move_p1;
    pSubCursor->_move_p2 = prm_cursor_move_p2;
    _lstSubCursor.addLast(pSubCursor, true);
    T::appendChild(pSubCursor->_pActor);
    selectItemBySubCursor(0, _lstSubCursor.length()-1);
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getMainCursor() {
    return _pCursorActor;
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getSubCursor(int prm_subcur_no) {
    return _lstSubCursor.getFromFirst(prm_subcur_no)->_pActor;
}

template<class T>
int MenuActor<T>::getSelectedIndex() {
    return _lstItems.getCurrentIndex();
}

template<class T>
int MenuActor<T>::getSelectedIndexOnSubCursor(int prm_subcur_no) {
    return _lstSubCursor.getFromFirst(prm_subcur_no)->_select_index;
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getSelectedItem() {
    return _lstItems.getCurrent();
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getSelectedItemOnSubCursor(int prm_subcur_no) {
    return _lstItems.getFromFirst(getSelectedIndexOnSubCursor(prm_subcur_no));
}

template<class T>
int MenuActor<T>::getMvCursorHistoryIndex(int prm_n) {
    return (*(_lstMvCursorHistory.getPrev(prm_n)));
}

template<class T>
int MenuActor<T>::getOnDecidedIndex() {
    if (_is_just_decided) {
        return _lstItems.getCurrentIndex();
    } else {
        return -1;
    }
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getOnDecidedItem() {
    if (_is_just_decided) {
        return _lstItems.getCurrent();
    } else {
        return nullptr;
    }
}

template<class T>
int MenuActor<T>::getOnCancelledIndex() {
    if (_is_just_cancelled) {
        return _lstItems.getCurrentIndex();
    } else {
        return -1;
    }
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getOnCancelledItem() {
    if (_is_just_cancelled) {
        return _lstItems.getCurrent();
    } else {
        return nullptr;
    }
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getItem(int prm_index) {
#ifdef MY_DEBUG
    if (_lstItems.length() <= prm_index) {
        throwCriticalException("MenuActor<T>::getItem() ���j���[�A�C�e���v�f���I�[�o�[ name="<<T::getName()<<" _lstItems.length()="<<_lstItems.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstItems.getFromFirst(prm_index);
}

template<class T>
GgafDx::FigureActor* MenuActor<T>::getLabel(int prm_index) {
#ifdef MY_DEBUG
    if (_lstLabelActors.length() <= prm_index) {
        throwCriticalException("MenuActor<T>::getLabel() �\�����j���[���x�����j���[�A�C�e���v�f���I�[�o�[ name="<<T::getName()<<" _lstLabelActors.length()="<<_lstLabelActors.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstLabelActors.getFromFirst(prm_index);
}


template<class T>
void MenuActor<T>::selectNext(bool prm_smooth) {
    GgafDx::FigureActor* pCurrent = _lstItems.getCurrent();
    if (_pCursorActor) {
        _pCursorActor->setPositionAt(pCurrent);
    }
    GgafDx::FigureActor* pNext;
    while(true) {
        pNext = _lstItems.next();
        if (pNext->isActive()) {
            break;
        } else {
            if (pNext == pCurrent) {
                break;
            }
        }
    }
    moveCursor(prm_smooth);
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::selectPrev(bool prm_smooth) {
    GgafDx::FigureActor* pCurrent = _lstItems.getCurrent();
    if (_pCursorActor) {
        _pCursorActor->setPositionAt(pCurrent);
    }
    GgafDx::FigureActor* pPrev;
    while(true) {
        pPrev = _lstItems.prev();
        if (pPrev->isActive()) {
            break;
        } else {
            if (pPrev == pCurrent) {
                break;
            }
        }
    }
    moveCursor(prm_smooth);
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::selectExNext(bool prm_smooth) {
    if (_lstItems.getRelation(ITEM_RELATION_EX_NEXT)) {
        GgafDx::FigureActor* pCurrent = _lstItems.getCurrent();
        if (_pCursorActor) {
            _pCursorActor->setPositionAt(pCurrent);
        }
        GgafDx::FigureActor* pRelation;
        while(true) {
            pRelation = _lstItems.gotoRelation(ITEM_RELATION_EX_NEXT);
            if (pRelation->isActive()) {
                break;
            } else {
                if (pRelation == pCurrent) {
                    break;
                }
            }
        }
        moveCursor(prm_smooth);
    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::selectExPrev(bool prm_smooth) {
    if (_lstItems.getRelation(ITEM_RELATION_EX_PREV)) {
        GgafDx::FigureActor* pCurrent = _lstItems.getCurrent();
        if (_pCursorActor) {
            _pCursorActor->setPositionAt(pCurrent);
        }
        GgafDx::FigureActor* pRelation;
        while(true) {
            pRelation = _lstItems.gotoRelation(ITEM_RELATION_EX_PREV);
            if (pRelation->isActive()) {
                break;
            } else {
                if (pRelation == pCurrent) {
                    break;
                }
            }
        }
        moveCursor(prm_smooth);
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::selectCancel(bool prm_smooth) {
    if (_lstItems.getRelation(ITEM_RELATION_TO_CANCEL)) {
        if (_pCursorActor) {
            _pCursorActor->setPositionAt(_lstItems.getCurrent());
        }
        _lstItems.gotoRelation(ITEM_RELATION_TO_CANCEL);
        moveCursor(prm_smooth);
    } else {

    }
    *(_lstMvSelectHistory.next()) = _lstItems.getCurrentIndex();
    onSelect(*(_lstMvSelectHistory.getPrev()), *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
}

template<class T>
void MenuActor<T>::moveCursor(bool prm_smooth) {
    if (_pCursorActor) {
        GgafDx::FigureActor* pTargetItem = _lstItems.getCurrent();
        GgafDx::VecVehicle* pCursorVecVehicle = _pCursorActor->getVecVehicle();
        if (prm_smooth) {
            pCursorVecVehicle->setMvAngTwd(
                                    pTargetItem->_x + _x_cursor_adjust,
                                    pTargetItem->_y + _y_cursor_adjust,
                                    pTargetItem->_z + _z_cursor_adjust
                              );
            pCursorVecVehicle->stop();
            pCursorVecVehicle->asstMv()->slideByDt(
                                    UTIL::getDistance(_pCursorActor->_x,
                                                      _pCursorActor->_y,
                                                      _pCursorActor->_z,
                                                      pTargetItem->_x + _x_cursor_adjust,
                                                      pTargetItem->_y + _y_cursor_adjust,
                                                      pTargetItem->_z + _z_cursor_adjust ),
                                    _cursor_move_frames,
                                    _cursor_move_p1, _cursor_move_p2, 0 , true
                                  );
            _x_cursor_target_prev = pTargetItem->_x;
            _y_cursor_target_prev = pTargetItem->_y;
            _z_cursor_target_prev = pTargetItem->_z;
        } else {
            pCursorVecVehicle->asstMv()->stopSliding();
            pCursorVecVehicle->stop();
            _pCursorActor->_x = pTargetItem->_x + _x_cursor_adjust;
            _pCursorActor->_y = pTargetItem->_y + _y_cursor_adjust;
            _pCursorActor->_z = pTargetItem->_z + _z_cursor_adjust;
        }
        *(_lstMvCursorHistory.next()) = _lstItems.getCurrentIndex();
        onMoveCursor(*(_lstMvCursorHistory.getPrev()), *(_lstMvCursorHistory.getCurrent())); //�R�[���o�b�N
    }
}


template<class T>
void MenuActor<T>::moveSubCursor(int prm_subcur_no, bool prm_smooth) {
    if (_lstSubCursor.length() > 0) {
        GgafDx::FigureActor* pTargetItem = getSelectedItemOnSubCursor(prm_subcur_no);
        SubCursor* pSubCursor = _lstSubCursor.getFromFirst(prm_subcur_no);
        GgafDx::FigureActor* pSubCursorActor = pSubCursor->_pActor;
        GgafDx::VecVehicle* pSubCursorVecVehicle = pSubCursorActor->getVecVehicle();
        if (prm_smooth) {
            pSubCursorVecVehicle->setMvAngTwd(
                                     pTargetItem->_x + pSubCursor->_x_adjust,
                                     pTargetItem->_y + pSubCursor->_y_adjust,
                                     pTargetItem->_z + pSubCursor->_z_adjust
                                 );
            pSubCursorVecVehicle->stop();
            pSubCursorVecVehicle->asstMv()->slideByDt(
                                      UTIL::getDistance(pSubCursorActor->_x,
                                                        pSubCursorActor->_y,
                                                        pSubCursorActor->_z,
                                                        pTargetItem->_x + pSubCursor->_x_adjust,
                                                        pTargetItem->_y + pSubCursor->_y_adjust,
                                                        pTargetItem->_z + pSubCursor->_z_adjust ),
                                      pSubCursor->_move_frames,
                                      pSubCursor->_move_p1, pSubCursor->_move_p2, 0 , true
                                    );
            pSubCursor->_x_target_prev = pTargetItem->_x;
            pSubCursor->_y_target_prev = pTargetItem->_y;
            pSubCursor->_z_target_prev = pTargetItem->_z;
        } else {
            pSubCursorVecVehicle->asstMv()->stopSliding();
            pSubCursorVecVehicle->stop();
            pSubCursorActor->_x = pTargetItem->_x + pSubCursor->_x_adjust;
            pSubCursorActor->_y = pTargetItem->_y + pSubCursor->_y_adjust;
            pSubCursorActor->_z = pTargetItem->_z + pSubCursor->_z_adjust;
        }
    }
}

template<class T>
void MenuActor<T>::riseMe() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = true;
    _will_be_sinking_next_frame = false;
    enableControll();
    if (_velo_alpha_fade >= 1.0) {
        T::setAlpha(1.0);
    } else {
        T::setAlpha(0.0);
    }
    T::activate();
    //���j���[�A�C�e�������z�u
    GgafDx::FigureActor* p;
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem = _lstItems.getElemFirst();
    int n_i = _lstItems.length();
    for (int i = 0; i < n_i; i++) {
        p = pElem->getValue();
        p->setPosition(T::_x + p->_x_local,
                       T::_y + p->_y_local,
                       T::_z + p->_z_local);
        p->setAlpha(T::getAlpha());
        p->activate();
        GgafCore::GroupHead* pH = p->getGroupHead(); //Item�̊Ԃɂ͒c�������݂���
        if (pH) {
            pH->activate();
        }
        pElem = pElem->_pNext;
    }
    //�\�����j���[�A�C�e�������z�u
    pElem = _lstLabelActors.getElemFirst();
    int n_da = _lstLabelActors.length();
    for (int i = 0; i < n_da; i++) {
        p = pElem->getValue();
        p->setPosition(T::_x + p->_x_local,
                       T::_y + p->_y_local,
                       T::_z + p->_z_local);
        p->setAlpha(T::getAlpha());
        p->activate();
        pElem = pElem->_pNext;
    }

    if (_pCursorActor) {
        _pCursorActor->setAlpha(T::getAlpha());
        _pCursorActor->activate();
    }
    int n_sc = _lstSubCursor.length();
    for (int i = 0; i < n_sc; i++) {
        GgafDx::FigureActor* pSubCursorActor = _lstSubCursor.getFromFirst(i)->_pActor;
        pSubCursorActor->setAlpha(T::getAlpha());
        pSubCursorActor->activate();
    }
}

template<class T>
void MenuActor<T>::onRise() {
}

template<class T>
void MenuActor<T>::processRising() {
    T::addAlpha(_velo_alpha_fade);
    if (T::getAlpha() >= 1.0) {
        T::setAlpha(1.0);
        _with_rising = false;
        onRiseDone();
    }
}

template<class T>
void MenuActor<T>::onRiseDone() {
}

template<class T>
void MenuActor<T>::processBehavior() {
    if (_with_sinking) {
        processSinking();
    }
    if (_with_rising) {
        processRising();
    }
    frame active_frames = T::getActiveFrame();
    if (active_frames == 1) {
        onSelect(-1, *(_lstMvSelectHistory.getCurrent())); //�R�[���o�b�N
    }
    if (_can_controll && active_frames > 1) {
        GgafDx::FigureActor* pSelected = condSelectItem();
        if (pSelected) {
            selectItemIfPossible(pSelected);
        } else if (condSelectNext()) {
            selectNext();
        } else if (condSelectPrev()) {
            selectPrev();
        } else if (condSelectExNext()) {
            selectExNext();
        } else if (condSelectExPrev()) {
            selectExPrev();
        } else if (condSelectCancel()) {
            selectCancel();
        }
        if (condDecision()) {
            _will_be_just_decided_next_frame = true;
        } else if (condCancel()) {
            _will_be_just_cancelled_next_frame = true;
        }

    }

    if (_pCursorActor) {
        _pCursorActor->getVecVehicle()->behave();
        //���C���J�[�\�����ŁA_pVecVehicle->behave() ���Ȃ��悤�ɒ���
    }
    int n_sc = _lstSubCursor.length();
    for (int i = 0; i < n_sc; i++) {
        SubCursor* pSubCursor = _lstSubCursor.getFromFirst(i);
        pSubCursor->_pActor->getVecVehicle()->behave();
        //�⏕�J�[�\�����ŁA_pVecVehicle->behave() ���Ȃ��悤�ɒ���
    }

    //���j���[�A�C�e�������j���[�ɒǏ]
    GgafDx::FigureActor* p;
    GgafCore::RingLinkedList<GgafDx::FigureActor>::Elem* pElem = _lstItems.getElemFirst();
    int n_i = _lstItems.length();
    for (int i = 0; i < n_i; i++) {
        p = pElem->getValue();
        p->setPosition(T::_x + p->_x_local,
                       T::_y + p->_y_local,
                       T::_z + p->_z_local);
        if (_with_sinking) {
            if (T::getAlpha() < p->getAlpha()) {
                p->setAlpha(T::getAlpha());
            }
        } else if (_with_rising) {
            if (T::getAlpha() > p->getAlpha()) {
                p->setAlpha(T::getAlpha());
            }
        }
        pElem = pElem->_pNext;
    }

    //�\�����j���[�A�C�e�������j���[�ɒǏ]
    pElem = _lstLabelActors.getElemFirst();
    int n_da = _lstLabelActors.length();
    for (int i = 0; i < n_da; i++) {
        p = pElem->getValue();
        p->setPosition(T::_x + p->_x_local,
                       T::_y + p->_y_local,
                       T::_z + p->_z_local);
        if (_with_sinking) {
            if (T::getAlpha() < p->getAlpha()) {
                p->setAlpha(T::getAlpha());
            }
        } else if (_with_rising) {
            if (T::getAlpha() > p->getAlpha()) {
                p->setAlpha(T::getAlpha());
            }
        }
        pElem = pElem->_pNext;
    }

    //���C���J�[�\�������j���[�A�C�e���ɒǏ]
    if (_pCursorActor) {
        GgafDx::FigureActor* pTargetItem = _lstItems.getCurrent();
        if (_pCursorActor->getVecVehicle()->asstMv()->isSliding()) {
            _pCursorActor->_x += (pTargetItem->_x - _x_cursor_target_prev);
            _pCursorActor->_y += (pTargetItem->_y - _y_cursor_target_prev);
            _pCursorActor->_z += (pTargetItem->_z - _z_cursor_target_prev);
            _x_cursor_target_prev = pTargetItem->_x;
            _y_cursor_target_prev = pTargetItem->_y;
            _z_cursor_target_prev = pTargetItem->_z;
        } else {
            _pCursorActor->setPosition(pTargetItem->_x + _x_cursor_adjust,
                                       pTargetItem->_y + _y_cursor_adjust,
                                       pTargetItem->_z + _z_cursor_adjust );
        }
        if (_with_sinking) {
            if (T::getAlpha() < _pCursorActor->getAlpha()) {
                _pCursorActor->setAlpha(T::getAlpha());
            }
        } else if (_with_rising) {
            if (T::getAlpha() > _pCursorActor->getAlpha()) {
                _pCursorActor->setAlpha(T::getAlpha());
            }
        }
    }

    //�⏕�J�[�\�������j���[�A�C�e���ɒǏ]
    for (int i = 0; i < n_sc; i++) {
        SubCursor* pSubCursor = _lstSubCursor.getFromFirst(i);
        GgafDx::FigureActor* pTargetItem = _lstItems.getFromFirst(pSubCursor->_select_index);
        GgafDx::FigureActor* pSubCursorActor = pSubCursor->_pActor;
        if (pSubCursorActor->getVecVehicle()->asstMv()->isSliding()) {
            pSubCursorActor->_x += (pTargetItem->_x - pSubCursor->_x_target_prev);
            pSubCursorActor->_y += (pTargetItem->_y - pSubCursor->_y_target_prev);
            pSubCursorActor->_z += (pTargetItem->_z - pSubCursor->_z_target_prev);
            pSubCursor->_x_target_prev = pTargetItem->_x;
            pSubCursor->_y_target_prev = pTargetItem->_y;
            pSubCursor->_z_target_prev = pTargetItem->_z;
        } else {
            pSubCursorActor->setPosition(pTargetItem->_x + pSubCursor->_x_adjust,
                                         pTargetItem->_y + pSubCursor->_y_adjust,
                                         pTargetItem->_z + pSubCursor->_z_adjust );
        }
        if (_with_sinking) {
            if (T::getAlpha() < pSubCursorActor->getAlpha()) {
                pSubCursorActor->setAlpha(T::getAlpha());
            }
        } else if (_with_rising) {
            if (T::getAlpha() > pSubCursorActor->getAlpha()) {
                pSubCursorActor->setAlpha(T::getAlpha());
            }
        }
    }

    //�T�u���j���[��riseMe() sinkMe() ��
    int n_sm = _lstSubMenu.length();
    for (int i = 0; i < n_sm; i++) {
        MenuActor<T>* pSubMenu = _lstSubMenu.getFromFirst(i);
        if (pSubMenu->hasJustRisen()) {
            disableControll(); //�T�u���j���[�������オ�����̂ŁA���g�͑���s��
            _can_controll = false; //����
        }
        if (pSubMenu->hasJustSunk()) {
            if (_with_sinking || _is_just_sunk || _will_be_sinking_next_frame) {
                disableControll(); //���g�������ɕ��Ă���ꍇ
                _can_controll = false; //����
            } else {
                enableControll(); //�T�u���j���[���������̂ŁA���g�̑��앜�A
            }
        }
    }
}

template<class T>
void MenuActor<T>::sinkMe() {
    _with_rising = false;
    _with_sinking = false;
    _is_just_risen = false;
    _is_just_sunk = false;
    _will_be_rising_next_frame = false;
    _will_be_sinking_next_frame = true;
    disableControll();
    _can_controll = false; //����
    if (_velo_alpha_fade >= 1.0) {
        T::setAlpha(0.0);
        T::inactivateTree();
    }
}

template<class T>
void MenuActor<T>::onSink() {
}

template<class T>
void MenuActor<T>::processSinking() {
    T::addAlpha(-_velo_alpha_fade);
    if (T::getAlpha() <= 0.0) {
        T::setAlpha(0.0);
        _with_sinking = false;
        T::inactivateTree();
        onSinkDone(); //�R�[���o�b�N
    }
}

template<class T>
void MenuActor<T>::onSinkDone() {
}

template<class T>
void MenuActor<T>::addSubMenu(MenuActor<T>* prm_pSubMenu) {
    _lstSubMenu.addLast(prm_pSubMenu, false);
    T::appendChild(prm_pSubMenu); //�q�ɒǉ�
}

template<class T>
MenuActor<T>* MenuActor<T>::getParentMenu() {
    GgafCore::Actor* pActor = T::getParent(); //�q�ɒǉ�
#ifdef MY_DEBUG
    MenuActor<T>* pMenuActor = dynamic_cast<MenuActor<T>*>(pActor);
    if (pMenuActor == nullptr) {
        throwCriticalException("MenuActor<T>::getParentMenu �e�m�[�h�͓������j���[�ł͂���܂���ł����Bname="<<T::getName()<<" this="<<this);
    }
#endif
    return (MenuActor<T>*)pActor;
}

template<class T>
MenuActor<T>* MenuActor<T>::getSubMenu(int prm_index) {
#ifdef MY_DEBUG
    if (_lstSubMenu.length() < prm_index+1) {
        throwCriticalException("MenuActor<T>::getSubMenu() �T�u���j���[�A�C�e���v�f���I�[�o�[ name="<<T::getName()<<" _lstSubMenu.length()="<<_lstSubMenu.length()<<" prm_index="<<prm_index);
    }
#endif
    return _lstSubMenu.getFromFirst(prm_index);
}

template<class T>
MenuActor<T>* MenuActor<T>::getRisingSubMenu() {
    MenuActor<T>* pSubMenu = _lstSubMenu.getCurrent();
    if (pSubMenu) {
        if (pSubMenu->isActiveInTheTree()) {
            return pSubMenu;
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }
}


template<class T>
void MenuActor<T>::riseSubMenu(int prm_index) {
#ifdef MY_DEBUG
    if (_lstSubMenu.length() < prm_index+1) {
        throwCriticalException("MenuActor<T>::riseSubMenu() �T�u���j���[�A�C�e���v�f���I�[�o�[ name="<<T::getName()<<" _lstSubMenu.length()="<<_lstSubMenu.length()<<" prm_index="<<prm_index);
    }
#endif
    MenuActor<T>* pSubMenu = getSubMenu(prm_index);
    pSubMenu->riseMe();
}

template<class T>
void MenuActor<T>::riseSubMenu(int prm_index, coord prm_target_x, coord prm_target_y) {
    getSubMenu(prm_index)->setPosition(prm_target_x, prm_target_y); //���ɂ��void MenuBoard::riseMe() �ɗ������Ƀ^�[�Q�b�g�ݒ肳���
    riseSubMenu(prm_index);
}


template<class T>
void MenuActor<T>::sinkCurrentSubMenu() {
    _lstSubMenu.getCurrent()->sinkMe();
}

template<class T>
MenuActor<T>::~MenuActor() {
}

}
#endif /*GGAF_LIB_MENUACTOR_H_*/
