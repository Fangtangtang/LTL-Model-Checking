#ifndef LTL_MODEL_CHECKING_TS_HPP
#define LTL_MODEL_CHECKING_TS_HPP

#include <string>
#include <utility>

class AtomicProposition {
private:
    std::string name;
public:
    explicit AtomicProposition(std::string ap) : name(std::move(ap)) {}

    bool operator==(const AtomicProposition &other) const {
        return name == other.name;
    }

    [[nodiscard]] std::string toString() const noexcept {
        return name;
    }

    struct Hash {
        std::size_t operator()(const AtomicProposition &ap) const noexcept {
            return std::hash<std::string>{}(ap.name);
        }
    };
};

#endif //LTL_MODEL_CHECKING_TS_HPP
