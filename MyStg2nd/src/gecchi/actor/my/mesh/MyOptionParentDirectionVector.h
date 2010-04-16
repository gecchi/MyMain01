#ifndef MYOPTIONPARENTDIRECTIONVECTOR_H_
#define MYOPTIONPARENTDIRECTIONVECTOR_H_
namespace MyStg2nd {

/**
 * オプションの纏め役クラスの方向ベクトル表示 .
 * @version 1.00
 * @since 2010/03/18
 * @author Masatoshi Tsuge
 */
class MyOptionParentDirectionVector : public GgafDx9LibStg::DefaultMeshActor {

public:
    int _ptn_no;

    MyOptionParentDirectionVector(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override {
    }

    void onInactive() override;

    int isOffscreen() override {
        //画面外判定無し
        return 0;
    }

    bool isOutOfGameSpace() override {
        //ゲーム座標範囲外判定無し
        return false;
    }


    virtual ~MyOptionParentDirectionVector();
};

}
#endif /*MYOPTIONPARENTDIRECTIONVECTOR_H_*/

