#ifndef LTL_MODEL_CHECKING_CHECK_HPP
#define LTL_MODEL_CHECKING_CHECK_HPP

#include "ts.hpp"
#include "automata.hpp"

class TransitionSystemProductNBA {
private:
    std::vector<StateWrapper<int, Word>> S;
    std::vector<std::shared_ptr<ElementarySetCopy>> Q; // AP

    std::vector<StateWrapper<std::pair<int, int>, int>> state; // S x Q (id pair)
    std::unordered_set<int> initial_state;

public:
    TransitionSystemProductNBA(const TransitionSystem &ts, const NBA &nba, int state_id) {
        // states
        S = ts.getStates();
        Q = nba.getStates();
        for (int s_idx = 0; s_idx < S.size(); ++s_idx) {
            for (int q_idx = 0; q_idx < Q.size(); ++q_idx) {
                StateWrapper<std::pair<int, int>, int> new_state({s_idx, q_idx});
                new_state.ap = q_idx; // {q}
                state.push_back(new_state);
            }
        }
        // transition
        for (int s_idx = 0; s_idx < S.size(); ++s_idx) {
            for (int q_idx = 0; q_idx < Q.size(); ++q_idx) {
                StateWrapper<int, Word> ts_state = S[s_idx];
                // s -> t
                for (auto t_idx: ts_state.successor) {
                    // q --L(t)--> p
                    Word l_t = S[t_idx].ap;
                    std::unordered_set<int> valid_p = nba.getTransition({q_idx, l_t});
                    for (auto p_idx: valid_p) {
                        state[s_idx * Q.size() + q_idx].successor.emplace(t_idx * Q.size() + p_idx);
                    }
                }
            }
        }
        // init_s states
        std::unordered_set<int> init_s, init_q = nba.getInit();
        if (state_id < 0) {
            init_s = ts.getInit();
        } else {
            init_s.emplace(state_id);
        }
        for (int init_idx: init_s) {
            for (int q0_idx: init_q) {
                Word l_init = S[init_idx].ap;
                // q0 --L(s0)--> q
                std::unordered_set<int> valid_q = nba.getTransition({q0_idx, l_init});
                for (auto q_idx: valid_q) {
                    initial_state.emplace(init_idx * Q.size() + q_idx);
                }
            }
        }
    }

    bool check() {
        // TODO
        return false;
    }
};

#endif //LTL_MODEL_CHECKING_CHECK_HPP
