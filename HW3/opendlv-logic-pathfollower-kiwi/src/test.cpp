#include <iostream>
#include <map>

using namespace std;

pair<int, int> getValue(std::map<pair<int, int>, pair<int, int>> map, pair<int, int> key) {

    auto it = map.find(key);

    if ( it == map.end() ) {
        return pair<int, int> (-1, -1);
    }
    else {
        return it->second;
    }
 
}

int main()
{


    std::pair<int, int> coor1 (1,2);
    std::pair<int, int> coor2 (3,4);
    std::pair<int, int> coor3 (100,40);
    std::pair<int, int> coor4 (213213,8862);

    std::map<pair<int, int>, pair<int, int>> map;

    map[coor1] = coor2; 
    map[coor3] = coor4;
    
    

    pair<int, int> result = getValue(map, std::pair<int, int> (1,2222));

    cout << result.first << " " << result.second;


    return 0;
}
