#ifndef GGAFDXSCENE_H_
#define GGAFDXSCENE_H_
namespace GgafDxCore {

#define MAX_BGM_PER_ACTOR 3

/**
 * GgafDxCore���O��ԁA���V�[���N���X.
 * ���̋@�\���V�[���N���X�ɒǉ����Ă��܂��B<BR>
 * �EBGM���t<BR>
 * �EBGM�t�F�[�h�C���E�t�F�[�h�A�E�g<BR>
 * �E�V�[�������̕`��I�u�W�F�N�g�̃t�F�[�h�C���E�t�F�[�h�A�E�g<BR>
 * GgafDxCore���O��ԓ��ł́A���̃N���X�����V�[���Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDxScene : public GgafCore::GgafMainScene {
private :
    /**
     * ���ʂŎg�p�֎~ .
     */
    void processFinal() override {
    }
    /**
     * draw() �̃I�[�o�[���C�h�֎~ .
     * ���E(GgafDxUniverse)���S�Ă̕`����s���d�g�݂ɂȂ�܂����B<BR>
     * ���������āA�I�[�o�[���C�h���Ă��t���[�����[�N���Ăяo����邱�Ƃ͂���܂���B<BR>
     * ����ăI�[�o�[���C�h���Ȃ����߂� private �Ŏ����B<BR>
     * GgafDxUniverse::draw() ���Q�Ƃ���B<BR>
     */
    void draw() override {
    }

public :
    /** ���J�[�e�� */
    GgafDxAlphaCurtain* _pAlphaCurtain;
    /** BGM���t�� */
    GgafDxBgmPerformer* _pBgmPerformer;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @return
     */
    GgafDxScene(const char* prm_name);

    /**
     * ��ʃt�F�[�h�ABGM�t�F�[�h���� .
     * �{�N���X��processSettlementBehavior()�ŁA GgafDxAlphaCurtain��GgafDxBgmPerformer��<BR>
     * behave() ���Ă��܂��B�I�[�o�[���C�h����ƁA��ʃt�F�[�h�ABGM�t�F�[�h�������܂���B<BR>
     * �I�[�o�[���C�h����ꍇ�́A�K���������ŏ�ʃ��\�b�h���Ăяo���ĉ������B<BR>
     * �t��GgafDxAlphaCurtain��GgafDxBgmPerformer�̋@�\���g�p���Ȃ��������炩�ȃV�[���́A<BR>
     * �I�[�o�[���C�h���Ēׂ����Ƃɂ��A�͂��Ƀp�t�H�[�}���X���P�ł��邩���m��܂���<BR>
     */
    virtual void processSettlementBehavior() override;


    /**
     * ���c���[�V�[���̃A�N�^�[���t�F�[�h�C�������� .
     * @param prm_frame_fade �A���t�@�l�� 1.0 �ɂȂ�܂ł̎��s�t���[����(0�`)
     */
    void fadeinSceneTree(int prm_frame_fade);

    /**
     * ���V�[���̃A�N�^�[���t�F�[�h�C�������� .
     * @param prm_frame_fade �A���t�@�l�� 1.0 �ɂȂ�܂ł̎��s�t���[����(0�`)
     */
    void fadeinScene(int prm_frame_fade);

    /**
     * ���c���[�V�[���̃A�N�^�[���t�F�[�h�A�E�g������ .
     * @param prm_frame_fade �A���t�@�l�� 0.0 �ɂȂ�܂ł̎��s�t���[����(0�`)
     */
    void fadeoutSceneTree(int prm_frame_fade);

    /**
      * ���V�[���̃A�N�^�[���t�F�[�h�A�E�g������ .
     * @param prm_frame_fade �A���t�@�l�� 0.0 �ɂȂ�܂ł̎��s�t���[����(0�`)
     */
    void fadeoutScene(int prm_frame_fade);


    virtual ~GgafDxScene();
};

}
#endif /*GGAFDXSCENE_H_*/
