#ifndef ACTORTABLESCENE_H_
#define ACTORTABLESCENE_H_
namespace GgafDx9LibStg {

/**
 * ���񂵓G�o���e�[�u���Ǘ��V�[�� .
 * ���񂵓G�o���Ƃ͋�̓I�ɁA<BR>
 * �E�G�i��ґ��j�����ł���΁A�������̓G�i��ґ��j���o���B<BR>
 * �E�G�����ł����Ƃ��A��莞�ԂŎ��̓G���o���B<BR>
 * �Ƃ����悤�ȃe�[�u���̂��ƁB<BR>
 * (�����̓G�o���e�[�u���̂悤�Ȋ����ŁE�E)<BR>
 * <b>���g�p���@��</b><BR>
 * <pre><code>
 * �E����Scene��processBehavior()���Ŏ��̃R�[�h���������Ƃ���B
 *
 *     ActorTableScene* ta = NEW ActorTableScene("TableScene_9");
 *     ta->setMaxPerformFrame(290);  //�S�̃t���[�����ݒ�
 *     addSubLast(ta);               //�q�V�[���Ƃ��ēo�^
 *     ta->addToTable(((FormationPallas001a*)obtainActorFromFactory(21047100)), 100);   //�ґ�a�B�S���ł��Ȃ��Ƃ��A���̕ґ�b��100�t���[����o��
 *     ta->addToTable(((FormationPallas001b*)obtainActorFromFactory(21057100)), 100);   //�ґ�b�B�S���ł��Ȃ��Ƃ��A���̕ґ�c��100�t���[����o��
 *     ta->addToTable(((FormationPallas001c*)obtainActorFromFactory(21067100)), 100);   //�ґ�c�B�S���ł��Ȃ��Ƃ��A���̕ґ�d��100�t���[����o��
 *     ta->addToTable(((FormationPallas001d*)obtainActorFromFactory(21077100)), 100);   //�ґ�d�B�S���ł��Ȃ��Ƃ��A���̕ґ�e��100�t���[����o��
 *     ta->addToTable(((FormationPallas001e*)obtainActorFromFactory(21087100)));        //�ґ�e�B���̓G���������߁A�t���[�����ݒ�̈Ӗ��͖����Ȃ�B
 *
 * �E����͉��}�̂悤�Ȏ����Ӗ�����B
 *
 *  �e�V�[��   --------------------+----------------------------+---------------------------->
 *  �e�t���[��                     n                            n+290
 *
 *  ���������Ȃ��ꍇ��
 *    �q�V�[��(ActorTableScene)    +---------+---------+--------+
 *    �q�t���[��                   0         100       200      290
 *
 *                                 | a       | b       | c       |   d  ��  �ґ�d�ȍ~�͏o�����Ȃ��B
 *                                 <--100---><--100---><--100---><--100--->      �ґ�d�̏o���^�C�~���O��300�ƂȂ�A290�܂łɊԂɍ����Ă��Ȃ����ߏo�����Ȃ�
 *
 *  ���ґ�a�����𑁊����j(80�t���[��)���ꂽ�ꍇ��
 *    �q�V�[��(ActorTableScene)    +------+---------+---------+-+
 *    �q�t���[��                   0      80        180     280 290
 *
 *                                 |a     | b       | c       | d  ��  �ґ�d�͏o������B
 *                                 <--80-><--100---><--100---><--100--->   �ґ�d�̏o���^�C�~���O��280�ƂȂ�A290�܂łɊԂɍ����Ă���̂ŏo������B
 *                                                                         ���ɕґ�d��10�t���[���ȓ��ŏ��ł��ꂽ�ꍇ�́A�ґ�e���o���\�B
 *  </code></pre>
 * @version 1.00
 * @since 2010/08/19
 * @author Masatoshi Tsuge
 */
class ActorTableScene : public GgafDx9Core::GgafDx9Scene {

private:
    /**
     * �G�o���e�[�u���v�f�N���X .
     * �ґ��A�N�^�[�A�ő�҂��t���[��(_max_delay_offset) �̏����������R���e�i
     */
    class TblElem {
    public:
        /** �ґ��A�N�^�[ */
        GgafDx9Core::GgafDx9FormationActor* _pFormationActor;
        /** �ґ��A�N�^�[�����u���ꂽ�Ƃ��Ă��A���̓G���o������܂ł̃t���[���� */
        frame _max_delay_offset;

        /**
         * �v�f�R���X�g���N�^ .
         * @param prm_pFormationActor �ґ��A�N�^�[
         * @param prm_max_delay_offset ���̓G���o������܂ł̃t���[����(�ȗ�����0)
         * @return
         */
        TblElem(GgafDx9Core::GgafDx9FormationActor* prm_pFormationActor, frame prm_max_delay_offset = 0) {
            _pFormationActor = prm_pFormationActor;
            _max_delay_offset = prm_max_delay_offset;
        }
        virtual ~TblElem() {
            //_pActor�̓V�[�������ƂȂ邽�߉���͕s�v
        }
    };

public:
    /** ���񂵓G�o���e�[�u���S�̂̋��e�t���[�� */
    frame _max_perform_frame;
    /** �e�[�u�����̌��݂̓G(�A�N�^�[)���o�����Ă���̃t���[���� */
    frame _frame_of_current_part_began;
    /** �G�o���e�[�u��(TblElem�I�u�W�F�N�g�̘A�����X�g) */
    GgafCore::GgafLinkedListRing<TblElem> _table;

    /**
     * �R���X�g���N�^ .
     * @param prm_name �V�[����
     * @return
     */
    ActorTableScene(const char* prm_name);

    /**
     * ���e�[�u���ɓG�ґ��v�f�ǉ� .
     * �v�f�ǉ����A�G�ґ��A�N�^�[�͔񊈓����(inactivateImmediately())�ɂ������܂��B<BR>
     * �v�f�ǉ����Ă��� activate() �́A���Ȃ��ł��������B<BR>
     * @param prm_pFormationActor �G�ґ��A�N�^�[
     * @param prm_max_delay_offset ���̓G�o���܂ł́A�ő�҂��t���[����
     * @return
     */
    virtual GgafCore::GgafGroupHead* addToTable(GgafDx9Core::GgafDx9FormationActor* prm_pFormationActor, frame prm_max_delay_offset = 0);

    /**
     * ���񂵓G�o���e�[�u���S�̂̋��e�t���[����ݒ肷��B
     * �ݒ���s��Ȃ��ꍇ�A0xffffffff ���ݒ肳��Ă���B
     * @param prm_max_perform_frame
     */
    virtual void setMaxPerformFrame(frame prm_max_perform_frame) {
        _max_perform_frame = prm_max_perform_frame;
    }

    virtual void initialize() override {
    }

    virtual void onActive() override;

    /**
     * �e�[�u���ɂ��������āA�G(�A�N�^�[)��activate()���Ă����܂��B
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

    virtual void processDraw() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual ~ActorTableScene();
};

}
#endif /*ACTORTABLESCENE_H_*/
