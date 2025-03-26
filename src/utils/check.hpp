#ifndef LTL_MODEL_CHECKING_CHECK_HPP
#define LTL_MODEL_CHECKING_CHECK_HPP

#include <stack>
#include "ts.hpp"
#include "automata.hpp"

class TransitionSystemProductNBA {
private:
    std::vector<StateWrapper<int, Word>> S;
    std::vector<std::shared_ptr<ElementarySetCopy>> Q; // AP
    std::unordered_set<int> F;

    std::vector<StateWrapper<std::pair<int, int>, int>> state; // S x Q (id pair)
    std::unordered_set<int> initial_state;

    std::unordered_set<int> R;
    std::stack<int> U;
    std::unordered_set<int> T;
    std::stack<int> V;
    bool cycle_found = false;

private:
    bool cycleCheck(int id, StateWrapper<std::pair<int, int>, int> s) {
        bool found = false;
        V.push(id);
        T.emplace(id);
        while (true) {
            int top_s_id = V.top();
            StateWrapper<std::pair<int, int>, int> top_s = state[top_s_id];
            if (top_s.successor.count(id) > 0) {
                found = true;
                V.push(id);
            } else {
                std::unordered_set<int> post_s_T = diffSet(top_s.successor, T);
                if (!post_s_T.empty()) {
                    int selected_s_id = *post_s_T.begin();
                    V.push(selected_s_id);
                    T.emplace(selected_s_id);
                } else {
                    V.pop();
                }
            }
            if (V.empty() || found) {
                break;
            }
        }
        return found;
    }

    void reachableCycle(int s_id) {
        U.push(s_id);
        R.emplace(s_id);
        while (true) {
            int top_s_id = U.top();
            StateWrapper<std::pair<int, int>, int> top_s = state[top_s_id];
            std::unordered_set<int> post_s_R = diffSet(top_s.successor, R);
            if (!post_s_R.empty()) {
                int selected_s_id = *post_s_R.begin();
                U.push(selected_s_id);
                R.emplace(selected_s_id);
            } else {
                U.pop();
                if (F.count(top_s.ap) > 0) {
                    cycle_found = cycleCheck(top_s_id, top_s);
                }
            }
            if (U.empty() || cycle_found) {
                break;
            }
        }
    }

    static inline std::unordered_set<int> diffSet(const std::unordered_set<int> &set_a, std::unordered_set<int> set_b) {
        std::unordered_set<int> diff;
        for (const auto &elem: set_a) {
            if (set_b.find(elem) == set_b.end()) {
                diff.insert(elem);
            }
        }
        return diff;
    }

public:
    TransitionSystemProductNBA(const TransitionSystem &ts, const NBA &nba, int state_id) {
        // states
        S = ts.getStates();
        Q = nba.getStates();
        F = nba.getFinal();
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


    // check by nested DFS
    bool check() {
        std::unordered_set<int> I_R = diffSet(initial_state, R);
        while (!I_R.empty() && !cycle_found) {
            reachableCycle(*I_R.begin());
            I_R = diffSet(initial_state, R);
        }
        return !cycle_found;
    }
};

#endif //LTL_MODEL_CHECKING_CHECK_HPP
