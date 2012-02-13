#ifndef FORMATIONPALLAS001C_H_
#define FORMATIONPALLAS001C_H_
namespace VioletVreath {

/**
 * 敵機イリス用フォーメーションその1-a .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationPallas001c : public FormationPallas001 {
public:

    FormationPallas001c(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void onActive() override;

    virtual ~FormationPallas001c();
};

}
#endif /*FORMATIONPALLAS001C_H_*/
