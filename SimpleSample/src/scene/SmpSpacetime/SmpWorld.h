#ifndef SMPWORLD_H_
#define SMPWORLD_H_
#include "SimpleSample.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/ggaf/lib/actor/DefaultSceneMediator.h"

#include "jp/ggaf/lib/util/VirtualButton.h"

namespace SimpleSample {

/**
 * 世界シーンの雛形 .
 * GgafLib::DefaultScene を継承してシーンクラスを作成して下さい。<BR>
 * 本サンプルでは「世界」シーンと名づけました。<BR>
 * processBehavior() をオーバーライドし、毎フレームの処理を記述します。<BR>
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class SmpWorld : public GgafLib::DefaultScene {

public:
    /**
     * シーンとアクターの仲介者 .
     */
    class Mediator : public GgafLib::DefaultSceneMediator {
    public:
        /** 仮想ボタンオブジェクト */
        GgafLib::VirtualButton vb_;

        /**
         * コンストラクタ
         * @param prm_pSmpWorld
         * @return
         */
        Mediator(SmpWorld* prm_pSmpWorld);

        void initialize() override {
        }

        void processBehavior() override {
            vb_.update();
        }

        /**
         * 仮想ボタンオブジェクトを返す .
         * @return 仮想ボタン
         */
        GgafLib::VirtualButton* getVB() {
            return &vb_;
        }

        virtual ~Mediator() {
        }
    };

public:
    /**
     * コンストラクタ .
     * @param prm_name 名称
     */
    SmpWorld(const char* prm_name);

    /**
     * 世界シーンの初期処理 .
     */
    void initialize() override;

    /**
     * 世界シーンの振る舞い処理 .
     */
    void processBehavior() override;

    virtual ~SmpWorld();
};

}
#endif /*SMPWORLD_H_*/
