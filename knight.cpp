#include "knight.h"
#include <algorithm>
#include <cmath>

using namespace std;

int minKnightMoves(const Pos& start, const Pos& target) {
    if (start == target) return 0;

    const vector<Pos> directions = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    unordered_set<Pos, PosHash> visited;
    queue<pair<Pos, int>> q;

    q.push({start, 0});
    visited.insert(start);

    while (!q.empty()) {
        auto [current, dist] = q.front(); q.pop();

        for (const auto& d : directions) {
            Pos next{current.row + d.row, current.col + d.col};
            if (next == target) return dist + 1;

            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push({next, dist + 1});
            }
        }
    }
    return -1;
}


vector<Pos> getKnightPath(const Pos& start, const Pos& target) {
    if (start == target) return {start};

    const vector<Pos> directions = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    unordered_set<Pos, PosHash> visited;
    unordered_map<Pos, Pos, PosHash> parent;
    queue<Pos> q;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        Pos current = q.front(); q.pop();

        for (const auto& d : directions) {
            Pos next{current.row + d.row, current.col + d.col};

            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                parent[next] = current;
                q.push(next);

                if (next == target) {
                    vector<Pos> path;
                    for (Pos at = target; at != start; at = parent[at]) {
                        path.push_back(at);
                    }
                    path.push_back(start);
                    reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }

    return {};
}


bool isValidPosition(const Pos& pos, int boardSize) {
    if (boardSize == -1) return true;
    return pos.row >= 0 && pos.row < boardSize &&
           pos.col >= 0 && pos.col < boardSize;
}