#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct Operation {
    bool write;
    int transaction;
    string field;

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

/**
 * depth first search, detecting whether there are duplicates in the SRGraph, effectively detecting cycles in the graph
 */
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
    int numberTransactions = 0;

    // initially read the individual operations as space separated 3-tuples
    const auto operations = [&] {
        vector<Operation> result;
        char write;
        int transaction;
        string field;
        while (cin >> write &&
               cin >> transaction &&
               cin >> field) {
            result.push_back({write == 'w', transaction, field});
            if (transaction > numberTransactions) {
                numberTransactions = transaction;
            }
        }
        return result;
    }();

    // initialize the SR graph
    vector<SRGraphNode> nodes;
    for (int i = 1; i <= numberTransactions; ++i) {
        nodes.push_back(SRGraphNode(i));
    }

    // connect the conflicting transactions
    for (size_t i = 0; i < operations.size(); ++i) {
        const auto &op = operations[i];
        // an operation can only conflict with later operations
        for (size_t j = i + 1; j < operations.size(); ++j) {
            const auto &other = operations[j];
            if (op.conflicts(other)) {
                nodes[op.transaction - 1].conflicts.push_back(&nodes[other.transaction - 1]);
            }
        }
    }

    if (argc > 1) { // output DOT directed graph as a visualization
        cout << "digraph \"precedence graph\" {" << endl;
        for (const auto &node : nodes) {
            for (const auto &conflict : node.conflicts) {
                cout << node.transaction << " -> " << conflict->transaction << endl;
            }
        }
        cout << "}" << endl;
    }

    // the whole history is serializable, if the precedence graph has no cycles.
    // note: we can't just start with any node, because the graph is not necessarily connected. We need to at least
    // visit every node once. The most efficient implementation would only start at the next unvisited node again, but
    // the least effort implementation just traverses the graph from every start node.
    const auto serializable = none_of(nodes.begin(), nodes.end(), [](SRGraphNode &node) {
        return dfsDuplicate(&node);
    });

    if (argc == 1) {
        cout << (serializable ? "true" : "false") << endl;
    }

    return !serializable; // return code logic is inverted
}
