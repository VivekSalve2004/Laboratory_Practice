#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string name;
    Node* next;
    Node* down;

    Node(string n = "") {
        name = n;
        next = nullptr;
        down = nullptr;
    }
};

class Graph {
    Node* head = nullptr;

    void add(string NodeA, string NodeB) {
        if (head == nullptr) {
            Node* node1 = new Node(NodeA);
            Node* node2 = new Node(NodeB);
            head = node1;
            node1->next = node2;
            return;
        }

        Node* current = head;
        Node* prev = nullptr;
        bool found = false;

        while (current != nullptr) {
            if (current->name == NodeA) {
                found = true;

                Node* temp = current->next;
                while (temp != nullptr) {
                    if (temp->name == NodeB) return; // avoid duplicate
                    temp = temp->next;
                }

                Node* newNode = new Node(NodeB);
                newNode->next = current->next;
                current->next = newNode;
                return;
            }
            prev = current;
            current = current->down;
        }

        // NodeA not found, create new list
        Node* newNode1 = new Node(NodeA);
        Node* newNode2 = new Node(NodeB);
        prev->down = newNode1;
        newNode1->next = newNode2;
    }

public:
    void addNode(string NodeA, string NodeB) {
        add(NodeA, NodeB);
        add(NodeB, NodeA); // bidirectional
    }

    void print() {
        cout << "\nAdjacency List:\n";
        Node* row = head;
        while (row != nullptr) {
            Node* col = row;
            while (col != nullptr) {
                cout << col->name;
                if (col->next) cout << " -> ";
                col = col->next;
            }
            cout << endl;
            row = row->down;
        }
    }

    void printOutDegrees() {
        cout << "\nOutdegrees:\n";
        Node* current = head;
        while (current != nullptr) {
            int degree = 0;
            Node* temp = current->next;
            while (temp != nullptr) {
                degree++;
                temp = temp->next;
            }
            cout << current->name << " : " << degree << endl;
            current = current->down;
        }
    }

    void printInDegrees() {
        cout << "\nIndegrees:\n";
        Node* current = head;
        while (current != nullptr) {
            int count = 0;
            Node* temp = head;
            while (temp != nullptr) {
                Node* neighbor = temp->next;
                while (neighbor != nullptr) {
                    if (neighbor->name == current->name)
                        count++;
                    neighbor = neighbor->next;
                }
                temp = temp->down;
            }
            cout << current->name << " : " << count << endl;
            current = current->down;
        }
    }

    void BFS(string start) {
        cout << "\nBFS from " << start << ":\n";
        queue<string> q;
        unordered_set<string> visited;
        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            string node = q.front();
            q.pop();
            cout << node << " ";

            Node* current = head;
            while (current != nullptr && current->name != node)
                current = current->down;

            if (!current) continue;

            Node* neighbor = current->next;
            while (neighbor) {
                if (!visited.count(neighbor->name)) {
                    visited.insert(neighbor->name);
                    q.push(neighbor->name);
                }
                neighbor = neighbor->next;
            }
        }
        cout << endl;
    }

    void DFS(string start) {
        cout << "\nDFS from " << start << ":\n";
        stack<string> s;
        unordered_set<string> visited;
        s.push(start);
        visited.insert(start);

        while (!s.empty()) {
            string node = s.top();
            s.pop();
            cout << node << " ";

            Node* current = head;
            while (current != nullptr && current->name != node)
                current = current->down;

            if (!current) continue;

            Node* neighbor = current->next;
            while (neighbor) {
                if (!visited.count(neighbor->name)) {
                    visited.insert(neighbor->name);
                    s.push(neighbor->name);
                }
                neighbor = neighbor->next;
            }
        }
        cout << endl;
    }

    bool isConnected(string start) {
        queue<string> q;
        unordered_set<string> visited;
        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            string node = q.front(); q.pop();

            Node* current = head;
            while (current != nullptr && current->name != node)
                current = current->down;
            if (!current) continue;

            Node* neighbor = current->next;
            while (neighbor) {
                if (!visited.count(neighbor->name)) {
                    visited.insert(neighbor->name);
                    q.push(neighbor->name);
                }
                neighbor = neighbor->next;
            }
        }

        // Count total unique nodes
        int totalNodes = 0;
        Node* temp = head;
        while (temp) {
            totalNodes++;
            temp = temp->down;
        }

        return visited.size() == totalNodes;
    }
};

int main() {
    Graph g;

    g.addNode("Katraj", "PICT");
    g.addNode("Bharti", "Katraj");
    g.addNode("Bharti", "PICT");
    g.addNode("Katraj", "SKNCOE");
    g.addNode("PICT", "SKNCOE");
    g.addNode("SKNCOE", "Temple");
    g.addNode("Temple", "Katraj");
    g.addNode("Temple", "Kondhwa");

    g.print();
    g.printInDegrees();
    g.printOutDegrees();
    g.BFS("Bharti");
    g.DFS("Katraj");

    cout << "\nGraph is " << (g.isConnected("Katraj") ? "connected" : "not connected") << ".\n";

    return 0;
}