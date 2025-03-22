#ifndef LTL_MODEL_CHECKING_TS_HPP
#define LTL_MODEL_CHECKING_TS_HPP

#include <string>
#include <utility>

class AtomicProposition {
private:
    std::string name;
public:
    explicit AtomicProposition(std::string ap) {
        name = std::move(ap);
    }

    [[nodiscard]] std::string toString() const noexcept {
        return name;
    }
};

#endif //LTL_MODEL_CHECKING_TS_HPP
