#ifndef SCROLLEDSCENE_H_
#define SCROLLEDSCENE_H_
namespace GgafLib {

/**
 * �X�N���[���V�[�� .
 * �z���c���[�V�[���̑S�A�N�^�[�ɑ΂��A
 * �ړ���K�p���邱�Ƃ��\�B����ȃV�[���ł��B
 * @version 1.00
 * @since 2010/11/05
 * @author Masatoshi Tsuge
 */
class ScrolledScene : public DefaultScene {
    /** �X�N���[�����x */
    velo _scroll_speed;
    /** [r/w]�X�N���[���֐��ւ̃|�C���^ */
    void (*_pFuncScrolling)(GgafCore::GgafObject*, void*, void*);
public:

    /**
     * X�����@�ɃX�N���[�� .
     * @param pThat �A�N�^�[
     * @param p1 �X�N���[���X�s�[�h(_scroll_speed�ւ̃|�C���^)
     * @param p2 �C�Ӂi�����͓��ɖ����j
     */
    static void scroll_X(GgafObject* pThat, void* p1, void* p2);


    /**
     * �X�N���[���֐���ݒ肷��B
     * �ݒ肳�ꂽ�X�N���[���֐���z���c���[�V�[���̑S�A�N�^�[�Ɏ��s���s���B<BR>
     * ��P�����ɂ́A�ΏۃA�N�^�[�A��Q�����ɂ́A�X�N���[���X�s�[�h(_scroll_speed�ւ̃|�C���^)���n�����B<BR>
     * �f�t�H���g�ł� ScrolledScene::scroll_X(GgafObject*, void*, void*) ���ݒ肳��Ă��邪�A<BR>
     * �{���\�b�h�ɂ���āA���[�U�[��`�X�N���[���֐��ɐ؂�ւ����ł���B<BR>
     * @param prm_pFuncScrolling ������(GgafObject*, void*, void*) �ƂȂ�֐��|�C���^
     */
    void setScrollingFunction(void (*prm_pFuncScrolling)(GgafCore::GgafObject*, void*, void*)) {
        _pFuncScrolling = prm_pFuncScrolling;
    }

    void setScrollSpeed(velo prm_scroll_speed) {
        _scroll_speed = prm_scroll_speed;
    }

    velo getScrollSpeed() {
        return _scroll_speed;
    }

    void addScrollSpeed(acce prm_acce) {
        _scroll_speed += prm_acce;
    }


    /**
     *
     * @param prm_name
     * @return
     */
    ScrolledScene(const char* prm_name);

    /**
     * ������ԂȂ�΁A���t���[���X�N���[���֐���z���c���[�V�[���̑S�A�N�^�[�Ɏ��s�B
     */
    virtual void processBehavior() override;


    virtual ~ScrolledScene();
};

}
#endif /*SCROLLEDSCENE_H_*/
