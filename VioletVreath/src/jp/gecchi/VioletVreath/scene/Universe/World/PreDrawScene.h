#ifndef PREDRAWSCENE_H_
#define PREDRAWSCENE_H_
namespace VioletVreath {

/**
 * 事前表示シーン .
 * ゲームの前に各モデルのキャラを１キャラずつ出力し、
 * モデルクラスをプリロードしておく。
 * @version 1.00
 * @since 2010/04/20
 * @author Masatoshi Tsuge
 */
class PreDrawScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1 ,
        PROG_CALM ,
        PROG_WAIT ,
    };
    TurboMeter* pTurboMeter001_;
    int order_id_begin_;
    int order_id_end_;
    int _id_;

public:
    PreDrawScene(const char* prm_name);
    void onReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~PreDrawScene();
};

}
#endif /*PREDRAWSCENE_H_*/
