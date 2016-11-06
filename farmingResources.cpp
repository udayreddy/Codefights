bool farmingResources(std::vector<int> friendlyTroops, std::vector<int> enemyTroops, std::vector<int> loggingCamp, std::vector<std::vector<int>> impassableCells) {
    int our_time = 0 , their_time = 0;
    bool did_we_win = false;
    coordinate our_loc(friendlyTroops[0],friendlyTroops[1]);
    int our_nos = friendlyTroops[2];
    coordinate their_loc(enemyTroops[0],enemyTroops[1]);
    int their_nos = enemyTroops[2];
    std::vector<coordinate> swamps;
    coordinate mordor(loggingCamp[0],loggingCamp[1]);
    
    for (auto &elem : impassableCells) {
        coordinate temp (elem[0],elem[1]);
        swamps.push_back(temp);
    }
    
    our_time = traversal_time(our_loc,our_nos,mordor,swamps);
    their_time = traversal_time(their_loc,their_nos,mordor,swamps);
    
    cout << our_time << their_time << endl;
    
    if (our_time < their_time)
        did_we_win = true;
    
    return did_we_win;
}

class coordinate {
   public:
        int x;
        int y;
    coordinate(int i, int j){
        x = i;
        y = j;
    }
    
    bool operator==(coordinate &A){
        if (x == A.x && y == A.y)
            return true;
        else
            return false;
    }
};

int traversal_time(coordinate loc , int count , coordinate dest ,
                   std::vector<coordinate> swamps){
    int time = 0;
    if (swamps.size() == 0){
        time = manhattan_distance(loc,dest)*count;
    } else {   
        while (manhattan_distance(loc,dest) != 0) {
            std::vector<coordinate> adjacent;
            // select all adjacent cells
            generateAdjacent(adjacent,loc,1);
            
            //select the best adjacent
            loc = adjacent[0];
            for (int i = 1; i < adjacent.size(); i++){
                if (manhattan_distance(loc,dest) >
                    manhattan_distance(adjacent[i],dest) 
                    && !checkSwap(adjacent[i],swamps)){
                        loc = adjacent[i];
                    cout << loc.x << "," << loc.y << endl;
                }
            }
            time += count;
        }
    }
    return time;
}

int manhattan_distance (coordinate a, coordinate b){
    int dx = a.x - b.x;
    int dy = a.y - b.y;

    if (oppositeSigns(dx,dy) != true)
        return abs(dx + dy);
    else
        return max(abs(dx), abs(dy));    
}

bool oppositeSigns(int x, int y)
{
    return ((x ^ y) < 0);
}

void generateAdjacent(std::vector<coordinate> &adjacent, 
                      coordinate selectionCenter , int range){
    for ( int x = selectionCenter.x - range;
            x <= selectionCenter.x + range;
            ++x )
      {
        for ( int y = selectionCenter.y - range;
              y <= selectionCenter.y + range;
              ++y )
        {
              coordinate temp(x,y);
              int man_dist = manhattan_distance(selectionCenter, temp);
              if ( man_dist == range ){
                    adjacent.push_back(temp);
                   /* cout << "A:" << selectionCenter.x << "," << selectionCenter.y  << " B:" << temp.x<< "," << temp.y << " Distance:" << man_dist << endl;*/
              }
        }
      }
}

bool checkSwap(coordinate A, std::vector<coordinate> items){
    for (auto &elem : items){
        if (elem == A)
            return true;
    }
    return false;
}