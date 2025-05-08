#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Define a structure for the grid node
struct Node {
    int x, y;          // Coordinates
    double g, h, f;    // Costs: g, h, and f

    // Constructor
    Node(int x, int y, double g, double h) {
        this->x = x;  // Set the x coordinate of the node
        this->y = y;  // Set the y coordinate of the node
        this->g = g;  // Set the actual cost to reach this node
        this->h = h;  // Set the heuristic cost to the goal
        this->f = g + h;  // Set the total cost (f = g + h)
    }

    // Comparator for priority queue (min-heap based on f)
    bool operator<(const Node& other) const {
        return f > other.f; // Higher f-values have lower priority
    }
};

// Directions for movement (up, down, left, right)
const vector<pair<int, int>> directions = {
    {0, 1},    // Right
    {1, 0},    // Down
    {0, -1},   // Left
    {-1, 0},   // Up
};

// Function to check if a position is valid
bool isValid(int x, int y, const vector<vector<int>>& grid) {
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() && grid[x][y] == 0;
}

// A* Algorithm
vector<pair<int, int>> aStar(const vector<vector<int>>& grid, pair<int, int> start, pair<int, int> goal) {
    int rows = grid.size(), cols = grid[0].size();

    // Priority queue to store open nodes
    priority_queue<Node> openList;

    // Map to track visited nodes and their costs
    unordered_map<int, double> gScore;
    unordered_map<int, pair<int, int>> cameFrom;

    // Lambda to calculate Manhattan Distance
    auto heuristic = [&](int x, int y) {
        return abs(x - goal.first) + abs(y - goal.second);
    };

    // Add the start node to the open list
    openList.push(Node(start.first, start.second, 0, heuristic(start.first, start.second)));
    gScore[start.first * cols + start.second] = 0;

    cout << "Starting A* Search...\n";

    // Process the nodes
    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        cout << "\nExpanding node (" << current.x << ", " << current.y << ") with:\n";
        cout << "  g(" << current.x << ", " << current.y << ") = " << current.g << "\n";
        cout << "  h(" << current.x << ", " << current.y << ") = " << current.h << "\n";
        cout << "  f(" << current.x << ", " << current.y << ") = " << current.f << "\n";

        // Check if the goal is reached
        if (current.x == goal.first && current.y == goal.second) {
            // Reconstruct the path
            vector<pair<int, int>> path;
            pair<int, int> curr = goal;
            while (curr != start) {
                path.push_back(curr);
                curr = cameFrom[curr.first * cols + curr.second];
            }
            path.push_back(start);
            reverse(path.begin(), path.end());
            return path;
        }

        // Explore neighbors
        for (const auto& dir : directions) {
            int nx = current.x + dir.first, ny = current.y + dir.second;

            if (isValid(nx, ny, grid)) {
                double tentative_g = gScore[current.x * cols + current.y] + 1; // Cost to neighbor
                double h = heuristic(nx, ny);
                double f = tentative_g + h;

                // Print the tentative values for each neighbor
                cout << "  Exploring neighbor (" << nx << ", " << ny << "):\n";
                cout << "    g(" << nx << ", " << ny << ") = " << tentative_g << "\n";
                cout << "    h(" << nx << ", " << ny << ") = " << h << "\n";
                cout << "    f(" << nx << ", " << ny << ") = " << f << "\n";

                // Check if this path is better
                if (gScore.find(nx * cols + ny) == gScore.end() || tentative_g < gScore[nx * cols + ny]) {
                    gScore[nx * cols + ny] = tentative_g;
                    cameFrom[nx * cols + ny] = {current.x, current.y};

                    // Add neighbor to the open list
                    openList.push(Node(nx, ny, tentative_g, h));
                    cout << "    Adding neighbor (" << nx << ", " << ny << ") to the open list with f = " << f << "\n";
                }
            }
        }
    }

    // If no path found, return empty
    return {};
}

// Main function
int main() {
    int rows, cols;

    // Input grid dimensions
    cout << "Enter the number of rows: ";
    cin >> rows;
    cout << "Enter the number of columns: ";
    cin >> cols;

    // Create the grid
    vector<vector<int>> grid(rows, vector<int>(cols));

    // Input the grid values (0 for free, 1 for obstacle)
    cout << "Enter the grid values (0 for free, 1 for obstacle):\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cin >> grid[i][j];
        }
    }

    // Input start and goal coordinates
    pair<int, int> start, goal;
    cout << "Enter the start coordinates (x y): ";
    cin >> start.first >> start.second;
    cout << "Enter the goal coordinates (x y): ";
    cin >> goal.first >> goal.second;

    // Run A* algorithm
    vector<pair<int, int>> path = aStar(grid, start, goal);

    // Print the result
    if (!path.empty()) {
        cout << "\nPath found:\n";
        for (const auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found." << endl;
    }

    return 0;
}