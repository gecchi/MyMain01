#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_
namespace MyStg2nd {

/**
 * ゲームデモシーンクラス .
 * ゲームが行なわれている場面と言っても、ゲームデモが行なわれている場合もありました。
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameDemoScene : public GgafLib::DefaultScene {

public:

    struct ScoreInfo {
        int rank;
        std::string name;
        int score;
        std::string date;
    };

    vector<ScoreInfo> ranking;
    LabelRankingFont** _papLabelRanking;

    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;
    int _demo_stage;

    int _ranking_num;

    GameDemoScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void processFinal() override;
    void onInactive() override;
    virtual ~GameDemoScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
