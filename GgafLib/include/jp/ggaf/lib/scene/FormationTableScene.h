#ifndef GGAF_LIB_FORMATIONTABLESCENE_H_
#define GGAF_LIB_FORMATIONTABLESCENE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/core/util/LinkedListRing.hpp"

namespace GgafLib {

/**
 * ���񂵓G�ґ��e�[�u���Ǘ��V�[�� .
 * ���񂵓G�ґ��Ƃ͋�̓I�ɁA<BR>
 * �E�ґ������ł���΁A�������̕ґ����o���B<BR>
 * �E�ґ������ł����Ƃ��A��莞�ԂŎ��̕ґ����o���B<BR>
 * �Ƃ����悤�ȃe�[�u���̂��ƁB<BR>
 * (�����̓G�o���e�[�u���̂悤�Ȋ����ŁE�E)<BR>
 * <b>���g�p���@��</b><BR>
 * <pre><code>
 * �E����Scene��processBehavior()���Ŏ��̃R�[�h���������Ƃ���ƁB
 *
 *     FormationTableScene* ftbl = NEW FormationTableScene("TableScene_9");
 *     appendChild(ftbl);               //�q�V�[���Ƃ��ēo�^
 *     ftbl->setMaxPerformFrame(280);  //�ґ��e�[�u���S�̃t���[�����ݒ�
 *     ftbl->addToTable(((FormationAllas001a*)receiveActor(21047100)), 100);   //�ґ�a�B���� �ґ�b �� �ґ�a ���S���ł����ꍇ���o���B�S���ł��Ȃ��Ƃ��A100�t���[����o���B
 *     ftbl->addToTable(((FormationAllas001b*)receiveActor(21057100)), 100);   //�ґ�b�B���� �ґ�c �� �ґ�b ���S���ł����ꍇ���o���B�S���ł��Ȃ��Ƃ��A100�t���[����o���B
 *     ftbl->addToTable(((FormationAllas001c*)receiveActor(21067100)), 100);   //�ґ�c�B���� �ґ�d �� �ґ�c ���S���ł����ꍇ���o���B�S���ł��Ȃ��Ƃ��A100�t���[����o���B
 *     ftbl->addToTable(((FormationAllas001d*)receiveActor(21077100)), 100);   //�ґ�d�B���� �ґ�e �� �ґ�d ���S���ł����ꍇ���o���B�S���ł��Ȃ��Ƃ��A100�t���[����o���B
 *     ftbl->addToTable(((FormationAllas001e*)receiveActor(21087100)));        //�ґ�e�B���̓G���������߁A�t���[�����ݒ�̈Ӗ��͖����Ȃ�B
 *
 * �E����͉��}�̂悤�Ȏ����Ӗ�����B
 *                                                             :
 *  �e�V�[��   --------------------+---------------------------+---------------------------->
 *  �e�t���[��                     n                        n+280
 *                                                             :
 *  ���������j���Ȃ��ꍇ��                                     :
 *    �q�V�[��(FormationTableScene)+---------+---------+-------+-+---
 *    �q�t���[��                   0        100       200   280: 300
 *                                                             :
 *                                 | a       | b       | c     : | d       �� �ґ�d�ȍ~�͏o�����Ȃ��B
 *                                  <--100--> <--100--> <--100--> <--100--->  �ґ�d�̏o���^�C�~���O��300�ƂȂ�A
 *                                                             :              280�܂łɊԂɍ����Ă��Ȃ����ߏo�����Ȃ�
 *  ���ґ�a�����𑁊����j(75�t���[���Ō��j)�����ꍇ��          :
 *    �q�V�[��(FormationTableScene)+------+---------+---------++---
 *    �q�t���[��                   0     75        175      275:280
 *                                                             :
 *                                 |a     | b       | c       |: d      ���ґ�d�͏o������B
 *                                  <-75-> <--100--> <--100--> <--100---> �ґ�d�̏o���^�C�~���O��275�ƂȂ�A
 *                                                             :          280�܂łɊԂɍ����Ă���̂ŏo������B
 *                                                             :          ���ɕґ�d��5�t���[���ȓ��ŏ��ł��ꂽ�ꍇ�́A�ґ�e���o���\�B
 *  </code></pre>
 * �������̕ґ��A�Ƃ��������\�����K�v�ȏꍇ�́ATreeFormation ���ADepositoryFormation�̂ق���
 * �ґ��������s�v�Ȃ̂ŗǂ��E�E�E�B
 * @version 1.00
 * @since 2010/08/19
 * @author Masatoshi Tsuge
 */
class FormationTableScene : public DefaultScene {

private:
    /**
     * �G�o���e�[�u���v�f�N���X .
     * �ґ��A�N�^�[�A�ő�҂��t���[��(_max_delay_offset) �̏����������R���e�i
     */
    class TblElem {
    public:
        /** �ґ��A�N�^�[ */
        GgafCore::Formation* _pFormationActor;
        /** �ґ��A�N�^�[�����u���ꂽ�Ƃ��Ă��A���̓G���o������܂ł̃t���[���� */
        frame _max_delay_offset;

        /**
         * �v�f�R���X�g���N�^ .
         * @param prm_pFormationActor �ґ��A�N�^�[
         * @param prm_max_delay_offset ���̓G���o������܂ł̃t���[����(�ȗ�����0)
         * @return
         */
        TblElem(GgafCore::Formation* prm_pFormationActor, frame prm_max_delay_offset = 0) {
            _pFormationActor = prm_pFormationActor;
            _max_delay_offset = prm_max_delay_offset;
        }
        virtual ~TblElem() {
            //_pFormationActor�̓V�[�������ƂȂ邽�߉���͕s�v
        }
    };

public:
    /** ���񂵓G�o���e�[�u���S�̂̋��e�t���[�� */
    frame _max_perform_frame;
    /** �e�[�u�����̌��݂̓G(�A�N�^�[)���o�����Ă���̃t���[���� */
    frame _frame_of_current_part_began;
    /** �G�o���e�[�u��(TblElem�I�u�W�F�N�g�̘A�����X�g) */
    GgafCore::LinkedListRing<TblElem> _table;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name �V�[����
     * @return
     */
    FormationTableScene(const char* prm_name);

    /**
     * ���e�[�u���ɓG�ґ��v�f�ǉ� .
     * �v�f�ǉ����A�G�ґ��A�N�^�[�͔񊈓����(inactivateImmed())�ɂ������܂��B<BR>
     * �v�f�ǉ����Ă��� activate() �́A���Ȃ��ł��������B<BR>
     * @param prm_pFormationActor �G�ґ��A�N�^�[
     * @param prm_max_delay_offset ���̓G�o���܂ł́A�ő�҂��t���[����
     * @return
     */
    virtual GgafCore::GroupHead* addToTable(GgafCore::Formation* prm_pFormationActor, frame prm_max_delay_offset = 0);

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

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual ~FormationTableScene();
};

}
#endif /*GGAF_LIB_FORMATIONTABLESCENE_H_*/
