#ifndef FORMATIONPALLAS001B_H_
#define FORMATIONPALLAS001B_H_
namespace MyStg2nd {

/**
 * 敵機イリス用フォーメーションその001-b .
 * @version 1.00
 * @since 2010/06/27
 * @author Masatoshi Tsuge
 */
class FormationPallas001b : public FormationPallas001 {
public:

    FormationPallas001b(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual ~FormationPallas001b();
};

}
#endif /*FORMATIONPALLAS001B_H_*/
