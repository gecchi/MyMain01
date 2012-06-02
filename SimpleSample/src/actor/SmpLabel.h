#ifndef SPRITELABELTEST_H_
#define SPRITELABELTEST_H_
namespace SimpleSample {

/**
 * オリジナル16x16ドットフォントのラベル .
 * @version 1.00
 * @since 2012/05/16
 * @author Masatoshi Tsuge
 */
class SmpLabel : public GgafLib::StringSpriteActor {

public:
    SmpLabel(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~SmpLabel();

};

}
#endif /*SPRITELABELTEST_H_*/
