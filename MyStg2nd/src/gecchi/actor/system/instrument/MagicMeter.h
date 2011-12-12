#ifndef MAGICMETER_H_
#define MAGICMETER_H_
namespace MyStg2nd {

#define MMETER_MAX_LEVEL 8

#ifdef P_MYSHIP_SCENE
    #define P_MAGICMETER (P_MYSHIP_SCENE->_pMagicMeter)
#else
    #error P_MYSHIP_SCENE isnt define
#endif


/**
 * ���@���[�^�[ .
 * @version 1.00
 * @since 2011/01/11
 * @author Masatoshi Tsuge
 */
class MagicMeter : public GgafLib::DefaultBoardSetActor {

public:
    D3DXHANDLE _h_active_magic;
    /** MP */
    GgafLib::AmountGraph _mp;
    /** �c���@���ʎ������ԕ\�� */
    MagicMeterStatus* _pMagicMeterStatus;
    /** �G�l���M�[�o�[ */
    EnagyBar* _pEnagyBar;
    /** ���@���X�g */
    GgafCore::GgafLinkedListRing<Magic> _ringMagics;

    /** ���[�^��J�[�\�� */
    MagicMeterCursor001* _pMagicCursor;
    /** �e���@�̃��x���J�[�\��(�z��) */
    MagicMeterCursor002** _papLvCursor;
    /** �e���@�̃��x���J�[�\�����w���Ă��郌�x��(�z��) */
    int* _paCursorLv;

    /** ���@���[�^�[�P�̉���(px) */
    float _width_px;
    /** ���@���[�^�[�P�̍���(px) */
    float _height_px;
    /** ���@���[�^�[�P�̉��� */
    coord _width;
    /** ���@���[�^�[�P�̍��� */
    coord _height;


    MagicMeter(const char* prm_name);

    void save(std::stringstream& sts);

    void load(std::stringstream& sts);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void processDraw() override;

    virtual ~MagicMeter();
};

}
#endif /*MAGICMETER_H_*/

