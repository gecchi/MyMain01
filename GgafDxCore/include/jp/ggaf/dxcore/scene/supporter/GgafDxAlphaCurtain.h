#ifndef GGAFDXALPHACURTAIN_H_
#define GGAFDXALPHACURTAIN_H_
namespace GgafDxCore {

/**
 * αカーテン .
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaCurtain : public GgafCore::GgafCurtain {
public:
    /** [r]αカーテンを取り付けるシーン */
    GgafDxScene* _pDxScene;
    /** [r]カーテンが閉じたときのα */
    float _min_alpha;
    /** [r]カーテンが開いたときのα */
    float _max_alpha;
    /** [r]カーテンの幅（開閉の長さ） */
    float _range_alpha;
    /** [r]現在のシーンのα */
    float _alpha;

    /**
     * コンストラクタ .
     * @param prm_pScene αカーテンを取り付けるシーン
     * @param prm_min_alpha カーテンが閉じたときのα
     * @param prm_max_alpha カーテンが開いたときのα
     */
    GgafDxAlphaCurtain(GgafDxScene* prm_pScene, float prm_min_alpha = 0.0f, float prm_max_alpha = 1.0f);

    void processOpenBegin() override;

    void processOpening() override;

    void processOpenDone() override;

    void processCloseBegin() override;

    void processClosing() override;

    void processCloseDone() override;

    void behave() override;

    virtual ~GgafDxAlphaCurtain();
};

}
#endif /*GGAFDXALPHACURTAIN_H_*/

