#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_
namespace VioletVreath {

/**
 * ゲームデモシーンクラス .
 * ゲームが行なわれている場面と言っても、ゲームデモが行なわれている場合もありました。
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameDemoScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_DEMOPLAY,
        PROG_RANKING ,
        PROG_FINISH  ,
    };
    struct ScoreInfo {
        int rank;
        std::string name;
        int score;
        std::string date;
    };

    std::vector<ScoreInfo> ranking;
    LabelRankingFont** papLabelRanking_;

    LabelGecchi16Font* pStringBoard01_;
    LabelGecchi16Font* pStringBoard02_;
    int demo_stage_;

    int ranking_num_;

    GameDemoScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void onInactive() override;
    virtual ~GameDemoScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
