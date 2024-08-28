#include <iostream>
#include <vector>
#include <map>
#include <array>

using namespace std;

vector <pair<int, int>> getPossibleDimensions(int area, int height, int width) {
    vector <pair<int, int>> dims;
    for (int side = 1; side * side <= area; ++side)
        if (area % side == 0) {
            if (side <= height && area / side <= width)
                dims.emplace_back(side, area / side);
            if (side <= width && area / side <= height && side != area / side)
                dims.emplace_back(area / side, side);
        }
    return dims;
}

bool checkFreeSpace(const pair<int, int> &top_left, const pair<int, int> &bottom_right, const pair<int, int> &area_ij,
                    const vector <vector<int>> &grid) {
    for (int i = top_left.first; i <= bottom_right.first; ++i)
        for (int j = top_left.second; j <= bottom_right.second; ++j)
            if (grid[i][j] > 0 && (i != area_ij.first || j != area_ij.second)) // not the same area
                return false;
    return true;
}

vector <array<int, 4>>
getValidPlacements(const pair<int, int> &area_ij, const pair<int, int> &shape_hw, const vector <vector<int>> &grid) {
    vector <array<int, 4>> placements;
    for (int i = 0; i < grid.size(); ++i)
        for (int j = 0; j < grid[0].size(); ++j)
            // area cell inside the shape
            if (i <= area_ij.first && area_ij.first < i + shape_hw.first &&
                j <= area_ij.second && area_ij.second < j + shape_hw.second)
                // shape inside the grid
                if (i + shape_hw.first - 1 < grid.size() && j + shape_hw.second - 1 < grid[0].size())
                    if (checkFreeSpace({i, j}, {i + shape_hw.first - 1, j + shape_hw.second - 1}, area_ij, grid))
                        placements.push_back(array{i, j, i + shape_hw.first - 1, j + shape_hw.second - 1});
    return placements;
}

bool getNextPerm(const map <pair<int, int>, vector<array < int, 4>>

> &areasPlacements,
map<pair<int, int>, int> &nextGoodPlacement
) {
for (auto &[area_coords, placement_idx]: nextGoodPlacement)
if (placement_idx<areasPlacements.
at(area_coords)
.

size()

- 1) {
++
placement_idx;
return true;
}
return false;
}

bool tryPlaceShapes(vector <vector<int>> &result, const map <pair<int, int>, vector<array < int, 4>>

> &areasPlacements,
const map<pair<int, int>, int> &nextGoodPlacement
) {
int region_number = 1;
for (auto &[area_coords, placement_idx]: nextGoodPlacement) {
const array<int, 4> &shape_coords = areasPlacements.at(area_coords)[placement_idx];
for (
int i = shape_coords[0];
i <= shape_coords[2]; ++i)
for (
int j = shape_coords[1];
j <= shape_coords[3]; ++j) {
if (result[i][j] > 0)
return false;
result[i][j] =
region_number;
}
++
region_number;
}
return true;
}

void fillGrid(vector <vector<int>> &result, const map <pair<int, int>, vector<array < int, 4>>

> &areasPlacements) {
auto backupGrid = result;

map<pair<int, int>, int> nextGoodPlacement;
for (auto &[area_coords, placements]: areasPlacements)
nextGoodPlacement[area_coords] = 0;

do {
if (
tryPlaceShapes(result, areasPlacements, nextGoodPlacement
))
break;
result = backupGrid;
} while (
getNextPerm(areasPlacements, nextGoodPlacement
));
}

int main() {
    int n, m;
    cin >> n >> m;

    vector <vector<int>> grid(n, vector<int>(m));
    vector <vector<int>> result(n, vector<int>(m));

    for (auto &row: grid)
        for (auto &cell: row)
            cin >> cell;

    map < pair < int, int >, vector < pair < int, int > > > coordsDims;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (grid[i][j] > 0)
                coordsDims[{i, j}] = getPossibleDimensions(grid[i][j], n, m);

    map < pair < int, int >, vector < array < int, 4 > > > areasPlacements;

    for (auto &[area_coords, shapes]: coordsDims)
        for (auto &shape: shapes) {
            vector <array<int, 4>> placements = getValidPlacements(area_coords, shape, grid);
            for (auto &placement: placements)
                areasPlacements[area_coords].push_back(placement);
        }

    fillGrid(result, areasPlacements);

    for (auto &row: result) {
        for (auto &cell: row)
            cout << cell << ' ';
        cout << '\n';
    }

    return 0;
}

/*
3 3
4 0 0
0 0 2
3 0 0
*/
