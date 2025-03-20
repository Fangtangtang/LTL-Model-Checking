#ifndef LTL_MODEL_CHECKING_EXCEPTION_HPP
#define LTL_MODEL_CHECKING_EXCEPTION_HPP

#include <exception>
#include <string>

class Exception : public std::exception {
public:
    explicit Exception(std::string msg) : msg(std::move(msg)) {}

    Exception(const Exception &o) noexcept { msg = o.msg; }

    ~Exception() override = default;

    const char *what() const noexcept override { return msg.c_str(); }

    void setMsg(const std::string &msg_) { msg = msg_; }

private:
    std::string msg;
};

class NotSupportedError : public Exception {
public:
    explicit NotSupportedError(const std::string &msg)
            : Exception("\033[31mNotSupported: \033[0m" + msg) {}
};

class InvalidRequestError : public Exception {
public:
    explicit InvalidRequestError(const std::string &msg)
            : Exception("\033[31mInvalidRequest: \033[0m" + msg) {}
};
#endif //LTL_MODEL_CHECKING_EXCEPTION_HPP
