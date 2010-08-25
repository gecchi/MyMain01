#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_

#define GAMEMAIN_PROG_INIT     1
#define GAMEMAIN_PROG_BEGIN    2
#define GAMEMAIN_PROG_PLAY     3
#define GAMEMAIN_PROG_END      4



namespace MyStg2nd {

/**
 * ゲームメインシーンクラス .
 */
class GameMainScene : public GgafDx9LibStg::DefaultScene {

public:
    int _dZ_camera_init;
    int _lim_CAM_top;
    int _lim_CAM_bottom;
    int _lim_CAM_front;
    int _lim_CAM_behaind;
    int _lim_CAM_zleft;
    int _lim_CAM_zright;

    int _lim_VP_top;
    int _lim_VP_bottom;
    int _lim_VP_front;
    int _lim_VP_behaind;
    int _lim_VP_zleft;
    int _lim_VP_zright;

    angle _angXY_nowCamUp;

    int _correction_width;
    int _correction_height;
    int _pos_camera;
    int _cam_velo_renge;
    int _stop_renge;
    frame _frame_pushdown_zmove;



    static GameMainScene* _pGameMainScene;













    char _buf[20];
    LabelGecchi16Font* _pFont16_SCORE;
    LabelGecchi16Font* _pFont16_RANK;
    LabelGecchi16Font* _pFont16_STAMINA;
    LabelGecchi8Font* _pFont8_JIKI_X;
    LabelGecchi8Font* _pFont8_JIKI_Y;
    LabelGecchi8Font* _pFont8_JIKI_Z;
    LabelGecchi16Font* _pFont1601;
    LabelGecchi16Font* _pFont1602;



    Stage01Scene* _pScene_Stage01;
    Stage02Scene* _pScene_Stage02;
    Stage03Scene* _pScene_Stage03;
    Stage04Scene* _pScene_Stage04;
    Stage05Scene* _pScene_Stage05;
    StageScene* _pSceneMainCannnel;

    frame _frame_Begin;
    frame _frame_Play;
    frame _frame_End;

    int _stage;

    boolean _had_ready_stage;
    frame _frame_ready_stage;
    GameMainScene(const char* prm_name);

    void setStage(int prm_stage) {
        _stage = prm_stage;
    }

    void reset();
    void ready(int prm_stage);


    void cannelStage(int prm_stage);

    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;
    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~GameMainScene();

};

}
#endif /*GAMEMAINSCENE_H_*/
