#ifndef WALLEDSCENE_H_
#define WALLEDSCENE_H_

//struct st_samp2{
//    int      a;
//    int   b[4];
//    char  c[8];
//    float    d;
//};
//
//ÇÃÇ∆Ç´ÇÕÅA
//
//struct st_samp s1={1,{2,3,4,5},"abcdefg",3.0};


#define FULL_VAL (-2)
#define KARA_VAL (-2)

namespace GgafDx9LibStg {

/**
 * GROUNDBOX .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class WalledScene : public DefaultScene {


    struct WallInfo {
        int _Y;
        int _Z;
        int _wall_draw_face;
        int _aColliBoxStretch[6];
    };
public:

    int _area_len;
    int _area_height;
    int _area_width;

    int _wall_dep;
    int _wall_width;
    int _wall_height;

    int _wall_start_X;
    frame _frame_of_launch_interval;

    int _cnt_area_len;
    WallInfo** _papaWallInfo;
    int* _paWallInfoLen;

    int _ground_speed;

    int _wall_stock;
    GgafCore::GgafActorDispatcher* _pDispatcher_Wall;

    WalledScene(const char* prm_name,
                const char* prm_data_filename,
                int prm_wall_dep, int prm_wall_width, int prm_wall_height,
                int prm_ground_speed);
    /**
     * èâä˙èàóù
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;


    virtual ~WalledScene();
};

}
#endif /*WALLEDSCENE_H_*/
