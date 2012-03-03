#ifndef GGAFMAINSCENE_H_
#define GGAFMAINSCENE_H_
namespace GgafCore {

/**
 * ���ʃV�[���N���X�ւ̃C���^�[�t�F�C�X .
 * GgafCore���C�u�����̗��p�҂͖{�N���X���p�����i�ăV�[���j�N���X�����B<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */

class GgafMainScene : public GgafScene {
    friend class GgafGod;
    friend class GgafScene;

public:

    GgafMainScene(const char* prm_name);

    virtual void updateActiveInTheTree() override;

    virtual ~GgafMainScene();

};

}
#endif /*GGAFMAINSCENE_H_*/
