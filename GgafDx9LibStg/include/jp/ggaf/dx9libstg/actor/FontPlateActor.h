#ifndef FONTPLATEACTOR_H_
#define FONTPLATEACTOR_H_
namespace GgafDx9LibStg {

/**
 * 文字表示クラス(座標変換済み).
 * DefaultPlateActor を継承し、文字セットテクスチャーから文字表示機能を追加したアクターです。
 */
class FontPlateActor : public DefaultPlateActor {
    /** 文字数 */
    char* _buf;
    char* _draw_string;
    int _len;
public:
    FontPlateActor(const char* prm_name, const char* prm_model);

    virtual void processDrawMain(); //オーバーライド
    virtual void setString(float prm_x, float prm_y, const char* prm_str);
    virtual void setString(float prm_x, float prm_y, char* prm_str);
    virtual void setString(float prm_x, float prm_y, float prm_z, const char* prm_str);
    virtual void setString(float prm_x, float prm_y, float prm_z, char* prm_str);
    virtual void setString(const char* prm_str);
    virtual void setString(char* prm_str);

    virtual ~FontPlateActor();

};

}
#endif /*FONTPLATEACTOR_H_*/
