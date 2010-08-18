#ifndef FORMATIONPALLAS001A_H_
#define FORMATIONPALLAS001A_H_
namespace MyStg2nd {

/**
 * 敵機パラス用フォーメーションその001-a .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationPallas001a : public FormationPallas001 {
public:

    FormationPallas001a(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void onActive() override;

    virtual ~FormationPallas001a();
};

}
#endif /*FORMATIONPALLAS001A_H_*/
