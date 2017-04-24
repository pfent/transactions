#include <iostream>
#include <vector>
#include <set>
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
        return (transaction != other.transaction)
               && (field == other.field)
               && (write || other.write);
    }
};

struct SRGraphNode {
    int transaction;
    vector<SRGraphNode *> conflicts{};

    SRGraphNode(int transaction) : transaction(transaction) {
    }
};

bool dfsDuplicate(SRGraphNode *node, set<SRGraphNode *> visited = {}) {
    if (visited.find(node) != visited.end()) {
        return true;
    }
    visited.insert(node);
    return any_of(node->conflicts.begin(), node->conflicts.end(), [visited](auto n) {
        return dfsDuplicate(n, visited);
    });
}

int main(int argc, char *[]) {
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
                nodes[op.transaction - 1].conflicts.push_back(&conflict);
            }
        }
    }

    if (argc > 1) {
        cout << "digraph \"precedence graph\" {" << endl;
        for (const auto &node : nodes) {
            for (const auto &conflict : node.conflicts) {
                cout << node.transaction << " -> " << conflict->transaction << endl;
            }
        }
        cout << "}" << endl;
    }

    auto serializable = none_of(nodes.begin(), nodes.end(), [](SRGraphNode &node) {
        return dfsDuplicate(&node);
    });

    if (argc == 1) {
        cout << (serializable ? "true" : "false") << endl;
    }

    return !serializable; // return code logic is inverted
}