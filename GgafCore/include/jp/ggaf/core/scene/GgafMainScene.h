#ifndef GGAFMAINSCENE_H_
#define GGAFMAINSCENE_H_
namespace GgafCore {

/**
 * 下位シーンクラスへのインターフェイス .
 * GgafCoreライブラリの利用者は本クラスを継承し（てシーン）クラスを作る。<BR>
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
