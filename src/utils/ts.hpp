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

struct State {
    std::unordered_set<int> successor;
    std::unordered_set<int> ap_id;
};

class TransitionSystem {
private:
    int state_num{}, transition_num{};

    std::vector<State> state;
    std::unordered_set<int> initial_state;

    std::vector<std::string> ap_list;
    std::map<std::string, std::shared_ptr<AtomicProposition>> AP;

public:
    explicit TransitionSystem(const std::string &file_name) {
        std::ifstream ts_file(file_name);
        if (!ts_file) {
            throw RuntimeError("Invalid file path for TS.txt");
        }

        ts_file >> state_num >> transition_num;
        state.resize(state_num);
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
        std::getline(ts_file, line);
        std::istringstream ap_stream(line);
        std::string ap;
        while (ap_stream >> ap) {
            ap_list.push_back(ap);
            AP.emplace(ap, std::make_shared<AtomicProposition>(ap));
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
            while (ap_stream >> label) {
                state[i].ap_id.emplace(label);
            }
        }
    }

    std::shared_ptr<AtomicProposition> getAtomicProposition(const std::string &name) const {
        auto it = AP.find(name);
        if (it != AP.end()) {
            return it->second;
        }
        throw RuntimeError("ap not found.");
    }
};

#endif //LTL_MODEL_CHECKING_TS_HPP
