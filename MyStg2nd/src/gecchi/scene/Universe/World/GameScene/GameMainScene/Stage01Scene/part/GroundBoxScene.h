#ifndef GROUNDBOXSCENE_H_
#define GROUNDBOXSCENE_H_

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

namespace MyStg2nd {

/**
 * GROUNDBOX .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class GroundBoxScene : public GgafDx9LibStg::DefaultScene {


    struct BoxInfo {
        int _Y;
        int _Z;
        int _box_draw_face;
        int _aColliBoxStretch[6];
    };
public:

    int _area_len;
    int _area_height;
    int _area_width;


    BoxInfo** _papaBoxInfo;


    int _box_stock;
    GgafCore::GgafActorDispatcher* _pDispatcher_Box;

    GroundBoxScene(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void processFinal() override;

    virtual ~GroundBoxScene();
};

}
#endif /*STAGE01_01_H_*/
