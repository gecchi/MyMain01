#ifndef GGAFDX9SCENE_H_
#define GGAFDX9SCENE_H_
namespace GgafDx9Core {

#define MAX_BGM_PER_ACTOR 3

/**
 * GgafDx9Core���O��ԁA���V�[���N���X.
 * ���̋@�\���V�[���N���X�ɒǉ����Ă��܂��B<BR>
 * �EBGM���t<BR>
 * �EBGM�t�F�[�h�C���E�t�F�[�h�A�E�g<BR>
 * �E�V�[�������̕`��I�u�W�F�N�g�̃t�F�[�h�C���E�t�F�[�h�A�E�g<BR>
 * GgafDx9Core���O��ԓ��ł́A���̃N���X�����V�[���Ƃ��܂��B<BR>
 * @version 1.00
 * @since 2008/01/24
 * @author Masatoshi Tsuge
 */
class GgafDx9Scene : public GgafCore::GgafMainScene {
private :
    /**
     * draw() �̃I�[�o�[���C�h�֎~ .
     * ���E(GgafDx9Universe)���S�Ă̕`����s���d�g�݂ɂȂ�܂����B<BR>
     * ���������āA�I�[�o�[���C�h���Ă��t���[�����[�N���Ăяo����邱�Ƃ͂���܂���B<BR>
     * ����ăI�[�o�[���C�h���Ȃ����߂� private �Ŏ����B<BR>
     * GgafDx9Universe::draw() ���Q�Ƃ���B<BR>
     */
    void draw() override {
    }

public :
    /** ���J�[�e�� */
    GgafDx9AlphaCurtain* _pAlphaCurtain;
    /** BGM���t�� */
    GgafDx9BgmPerformer* _pBgmPerformer;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @return
     */
    GgafDx9Scene(const char* prm_name);

    /**
     * ��ʃt�F�[�h�ABGM�t�F�[�h���� .
     * �{�N���X��processSettlementBehavior()�ŁA GgafDx9AlphaCurtain��GgafDx9BgmPerformer��<BR>
     * behave() ���Ă��܂��B�I�[�o�[���C�h����ƁA��ʃt�F�[�h�ABGM�t�F�[�h�������܂���B<BR>
     * �I�[�o�[���C�h����ꍇ�́A�K���������ŏ�ʃ��\�b�h���Ăяo���ĉ������B<BR>
     */
    virtual void processSettlementBehavior() override;


    /**
     * ���c���[�V�[�����t�F�[�h�C�������� .
     * ���V�[�����܂ޔz���S�ẴV�[���ɂ��āA�V�[�������I�u�W�F�N�g�̃t�F�[�h�C�����s���܂��B<BR>
     * �t�F�[�h�C���͋�̓I�ɂ́A�V�[�������I�u�W�F�N�g�ɑ΂��āA<BR>
     * �`�掞�Ƀ��l��0.0�`1.0��ω������Ȃ���Z���鎖���s���܂��B<BR>
     * �T�u�V�[���ɉe����^�����A���V�[���݂̂̃t�F�[�h�C�����s���ɂ�<BR>
     * <pre>
     * _pAlphaCurtain->open(1.0 / prm_frame_fade); //���J�[�e���I�[�v��
     * </pre>
     * �Ƃ��邱�Ƃŉ\�ł��B<BR>
     * @param prm_frame_fade 0% -> 100%�ɂȂ�܂ł̎��s�t���[����
     */
    void fadeinSceneTree(int prm_frame_fade);

    /**
     * ���V�[���݂̂̃t�F�[�h�C�� .
     * @param prm_frame_fade 0% -> 100%�ɂȂ�܂ł̎��s�t���[����
     */
    void fadeinScene(int prm_frame_fade);

    /**
     * ���c���[�V�[�����t�F�[�h�A�E�g������ .
     * ���V�[�����܂ޔz���S�ẴV�[���ɂ��āA�V�[�������I�u�W�F�N�g�̃t�F�[�h�A�E�g���s���܂��B<BR>
     * �t�F�[�h�A�E�g�͋�̓I�ɂ́A�V�[�������I�u�W�F�N�g�ɑ΂��āA<BR>
     * �`�掞�Ƀ��l��1.0�`0.0��ω������Ȃ���Z���鎖���s���܂��B<BR>
     * �T�u�V�[���ɉe����^�����A���V�[���̂݃t�F�[�h�A�E�g������ɂ�<BR>
     * <pre>
     * _pAlphaCurtain->close(1.0 / prm_frame_fade); //���J�[�e���N���[�Y
     * </pre>
     * �Ƃ��邱�Ƃŉ\�ł��B<BR>
     * @param prm_frame_fade 100% -> 0%�ɂȂ�܂ł̎��s�t���[����
     */
    void fadeoutSceneTree(int prm_frame_fade);

    /**
     * ���V�[���݂̂̃t�F�[�h�A�E�g .
     * @param prm_frame_fade 100% -> 0%�ɂȂ�܂ł̎��s�t���[����
     */
    void fadeoutScene(int prm_frame_fade);

    /**
     * �Ó]
     */
    void blackoutScene();

    virtual ~GgafDx9Scene();
};

}
#endif /*GGAFDX9SCENE_H_*/
