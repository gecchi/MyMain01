#ifndef GGAFEXCEPTION_H_
#define GGAFEXCEPTION_H_
namespace GgafCore {


class GgafException : public GgafObject {

public:
	std::string _message;
	GgafException(std::string prm_message);
	virtual std::string getMsg();
	virtual ~GgafException();
};


}
#endif /*GGAFEXCEPTION_H_*/
