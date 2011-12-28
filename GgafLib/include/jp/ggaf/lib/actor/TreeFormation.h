#ifndef TREEFORMATION_H_
#define TREEFORMATION_H_

#define FORMATION_END_DELAY (30*60)
namespace GgafLib {



/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 * processJudgement()�������ς݂̂��߁A
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class TreeFormation : public GgafCore::GgafTreeFormation {
private:
    /**
     * �g�p�s�� .
     */
    virtual void processJudgement() override {
        GgafCore::GgafTreeFormation::processJudgement();
    }
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    TreeFormation(const char* prm_name, frame prm_offset_frames_end = FORMATION_END_DELAY);


    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }


    virtual void processDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~TreeFormation();
};

}
#endif /*TREEFORMATION_H_*/
