#ifndef LTL_MODEL_CHECKING_TS_HPP
#define LTL_MODEL_CHECKING_TS_HPP

#include <string>
#include <fstream>
#include <unordered_set>
#include <map>
#include <utility>
#include "exception.hpp"

class AtomicProposition {
private:
    int id;
    std::string name;
public:
    explicit AtomicProposition(int ap_id, std::string ap) : id(ap_id), name(std::move(ap)) {}

    bool operator<(const AtomicProposition &other) const { return id < other.id; }

    bool operator==(const AtomicProposition &other) const {
        return name == other.name;
    }

    [[nodiscard]] std::string toString() const noexcept {
        return name;
    }

    struct Hash {
        std::size_t operator()(const AtomicProposition &ap) const noexcept {
            return std::hash<int>{}(ap.id);
        }
    };
};

class Word {
private:
    std::vector<AtomicProposition> aps;
    std::string word;

public:
    Word() = default;

    explicit Word(std::vector<AtomicProposition> ap_list) : aps(std::move(ap_list)) {
        std::sort(aps.begin(), aps.end());
        word.append("{");
        for (const auto &ap: aps) {
            word.append(ap.toString());
        }
        word.append("}");
    }

    [[nodiscard]]  std::string toString() const noexcept {
        return word;
    }

    bool operator<(const Word &other) const {
        return word < other.word;
    }

    bool operator==(const Word &other) const {
        return word == other.word;
    }

    [[nodiscard]] bool contains(const AtomicProposition &ap) const {
        return std::find(aps.begin(), aps.end(), ap) != aps.end();
    }

    [[nodiscard]] bool equal(
            const Word &other,
            const std::unordered_set<AtomicProposition, AtomicProposition::Hash> &care
    ) const {
        std::vector<AtomicProposition> tmp;
        for (const AtomicProposition& ap: aps) {
            if (care.count(ap) > 0) {
                tmp.push_back(ap);
            }
        }
        Word tmp_word(tmp);
        return tmp_word == other;
    }
};

template<typename InnerType, typename WordType>
struct StateWrapper {
    InnerType inner;
    std::unordered_set<int> successor;
    WordType ap;

    explicit StateWrapper(InnerType i) : inner(i) {}

    bool operator==(const StateWrapper &other) const {
        return inner == other.inner;
    }
};

class TransitionSystem {
private:
    int state_num{}, transition_num{};

    std::vector<StateWrapper<int, Word>> state;
    std::unordered_set<int> initial_state;

    std::vector<std::string> ap_list;
    std::map<std::string, AtomicProposition> AP;

public:
    explicit TransitionSystem(const std::string &file_name) {
        std::ifstream ts_file(file_name);
        if (!ts_file) {
            throw RuntimeError("Invalid file path for TS.txt");
        }

        ts_file >> state_num >> transition_num;
        for (int i = 0; i < state_num; ++i) {
            state.emplace_back(i);
        }
        ts_file.ignore();

        std::string line;
        std::getline(ts_file, line);
        std::istringstream initial_state_stream(line);
        int state_id;
        while (initial_state_stream >> state_id) {
            initial_state.emplace(state_id);
        }

        // ignore actions
        std::getline(ts_file, line);

        // AP
        AP.emplace("true", AtomicProposition(-1, "true"));
        std::getline(ts_file, line);
        std::istringstream ap_stream(line);
        std::string ap;
        int cnt = 0;
        while (ap_stream >> ap) {
            ap_list.push_back(ap);
            AP.emplace(ap, AtomicProposition(cnt, ap));
            ++cnt;
        }

        // transitions
        int from, act, to;
        for (int i = 0; i < transition_num; ++i) {
            std::getline(ts_file, line);
            std::istringstream transition_stream(line);
            transition_stream >> from >> act >> to;
            state[from].successor.emplace(to);
        }

        // labels
        int label;
        for (int i = 0; i < state_num; ++i) {
            std::getline(ts_file, line);
            std::istringstream label_stream(line);
            std::vector<AtomicProposition> label_ap;
            while (label_stream >> label) {
                label_ap.push_back(getAtomicProposition(ap_list[label]));
            }
            state[i].ap = Word(label_ap);
        }
    }

    AtomicProposition getAtomicProposition(const std::string &name) const {
        auto it = AP.find(name);
        if (it != AP.end()) {
            return it->second;
        }
        throw RuntimeError("ap not found.");
    }

    std::unordered_set<int> getInit() const {
        return initial_state;
    }

    std::vector<StateWrapper<int, Word>> getStates() const {
        return state;
    }
};

#endif //LTL_MODEL_CHECKING_TS_HPP
