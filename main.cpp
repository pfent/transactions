#include <iostream>
#include <vector>
#include <set>
#include <tuple>
#include <functional>
#include <algorithm>

using namespace std;

struct Operation {
    bool write;
    int transaction;
    char field;

    /**
     * conflict matrix:
     *        | r_i[x] | w_i[x]
     * -------+--------+-------
     * r_j[x] | false  | true
     * -------+--------+-------
     * w_j[x] | true   | true
     */
    bool conflicts(const Operation &other) const {
        return (field == other.field)
               && (write || other.write);
    }
};

struct SRGraphNode {
    int transaction;
    vector<reference_wrapper<SRGraphNode>> conflicts{};

    SRGraphNode(int transaction) : transaction(transaction) {
    }
};

bool dfsDuplicate(SRGraphNode &node, set<reference_wrapper<SRGraphNode>> visited = {}) {
    if(visited.find(ref(node)) != visited.end()) {
        return true;
    }
    visited.insert(ref(node));
    return any_of(node.conflicts.begin(), node.conflicts.end(), [visited](auto& n) {
        dfsDuplicate(n, visited);
    });
}

int main() {
    vector<Operation> operations;
    int numberTransactions = 0;
    for (char write, transaction, field;
         cin >> write &&
         cin >> transaction &&
         cin >> field;) {
        operations.push_back({write == 'w', transaction - '0', field});
        if (operations.back().transaction > numberTransactions) {
            numberTransactions = operations.back().transaction;
        }
    }

    for (auto op : operations) {
        cout << op.write << ' ' << op.transaction << ' ' << op.field << endl;
    }

    vector<SRGraphNode> nodes;
    for (int i = 1; i <= numberTransactions; ++i) {
        nodes.push_back(SRGraphNode(i));
    }

    for (size_t i = 0; i < operations.size(); ++i) {
        const auto &op = operations[i];
        for (size_t j = i + 1; j < operations.size(); ++j) {
            const auto &other = operations[j];
            if (op.conflicts(other)) {
                auto &conflict = nodes[other.transaction - 1];
                nodes[op.transaction - 1].conflicts.push_back(ref(conflict));
            }
        }
    }

    for (const auto &node : nodes) {
        for (const auto &conflict : node.conflicts) {
            cout << node.transaction << " -> " << conflict.get().transaction << endl;
        }
    }

    return any_of(nodes.begin(), nodes.end(), [](auto& node) {
        return dfsDuplicate(node);
    });
}