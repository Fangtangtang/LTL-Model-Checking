#ifndef LTL_MODEL_CHECKING_AP_HPP
#define LTL_MODEL_CHECKING_AP_HPP

#include <string>
#include <utility>

class AtomicProposition {
private:
    std::string name;
public:
    explicit AtomicProposition(std::string ap) {
        name = std::move(ap);
    }
};

#endif //LTL_MODEL_CHECKING_AP_HPP
