#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_
namespace MyStg2nd {

/**
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class WalledScene : public GgafDx9LibStg::DefaultScene {
//    class Section {
//    public :
//        GgafDx9LibStg::WalledSectionScene* _pScene;
//        int _repeat;
//        Section(GgafDx9LibStg::WalledSectionScene* prm_pScene, int prm_repeat) {
//            _pScene = prm_pScene;
//            _repeat = prm_repeat;
//        }
//    };

public:
    int _ground_speed;

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::WalledSectionScene>* _pRingSection;

    WalledScene(const char* prm_name);
    /**
     * _pFuncWallMove �Ƀf�t�H���g�Őݒ肳��Ă���֐� .
     * �A�N�^�[��X���̕��̕�����_ground_speed�X�N���[��������
     * @param pThat �A�N�^�[�̃|�C���^
     * @param p1 _ground_speed�̃|�C���^
     * @param p2 NULL�i���g�p�j
     */
    static void moveX(GgafCore::GgafObject* pThat, void* p1, void* p2);

    /**
     * ��������
     */
    void initialize() override;

    virtual void onActive() override;
    /**
     * �z���A�N�^�[�S�Ă�_pFuncWallMove �����s�B
     * �I�[�o�[���C�h����ꍇ�ADefaultScene::processSettlementBehavior(); ���Ăяo�����Ƃ�Y�ꂸ�ɁB
     */
    virtual void processSettlementBehavior() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~WalledScene();
};

}
#endif /*WALLEDSCENE_H_*/
