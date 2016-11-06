bool farmingResources(std::vector<int> friendlyTroops, std::vector<int> enemyTroops, std::vector<int> loggingCamp, std::vector<std::vector<int>> impassableCells) {
    int our_time = 0 , their_time = 0;
    int our_nos = friendlyTroops[2], their_nos = enemyTroops[2];;
    bool did_we_win = false;
    
    coordinate mordor(loggingCamp[0],loggingCamp[1]);
    coordinate our_loc(friendlyTroops[0],friendlyTroops[1]);
    coordinate their_loc(enemyTroops[0],enemyTroops[1]);
    our_loc.setMdistance(mordor);
    their_loc.setMdistance(mordor);
     
    //A* queues
     AstarQ ourQ;
        ourQ.push(our_loc);
     AstarQ theirQ;  
        theirQ.push(their_loc);
    
    //impassable cells
    std::vector<coordinate> swamps;
    for (auto &elem : impassableCells) {
        coordinate temp (elem[0],elem[1]);
        swamps.push_back(temp);
    }
    
    // calculate time taken
    our_time = traversal_time(mordor,our_nos,ourQ,swamps);
    cout << "========" << endl;
    their_time = traversal_time(mordor,their_nos,theirQ,swamps);
    
    cout << our_time << "---" <<their_time << endl;
    
    // compare durations
    if (our_time < their_time)
        did_we_win = true;
    
    return did_we_win;
}


class coordinate {
   public:
        int x;
        int y;
        int mDist;
        int time;
    coordinate(int i, int j){
        x = i;
        y = j;
        time = 0;
    }
    
    bool operator==(coordinate &A){
        if (x == A.x && y == A.y)
            return true;
        else
            return false;
    }
    
    void setMdistance (coordinate dest){
        int dx = x - dest.x;
        int dy = y - dest.y;

        if (((dx ^ dy) < 0) != true)
            mDist = abs(dx + dy);
        else
            mDist = max(abs(dx), abs(dy)); 
    }
};

struct balanceQueue{
     bool operator()(const coordinate &A, const coordinate &B) const {
         return A.mDist > B.mDist;
     };
};

typedef std::priority_queue<coordinate,std::vector<coordinate>,balanceQueue> AstarQ;

int traversal_time(coordinate loc , int count , AstarQ &q ,
                   std::vector<coordinate> swamps){
    int time = 0;
    if (swamps.size() == 0){
        time = manhattan_distance(q.top(),loc)*count;
    } else {   
        while (true) {
            coordinate curr = q.top();
            q.pop();
           /* std::cout << "curr:" << curr.x << "," << curr.y << " mDist:" 
                << curr.mDist << " time:" << curr.time <<std::endl; */
            // if destination reached
            if (curr == loc){
                return curr.time;
            }
            
            // generate all adjacent cells
            std::vector<coordinate> adjacent;
            generateAdjacent(adjacent,curr,1);
            
            //load all unblocked adjacent cells to the queue
            for (int i = 0; i < adjacent.size(); i++){
                if (!checkSwap(adjacent[i],swamps)){
                    adjacent[i].time = curr.time + count;
                    adjacent[i].setMdistance(loc);
                    q.push(adjacent[i]);
                   /* std::cout << "adjacent:" << adjacent[i].x << "," 
                        << adjacent[i].y << " mDist:" << adjacent[i].mDist 
                        << " time:" << adjacent[i].time <<std::endl;*/
                }
            }   
        }
    }
    return time;
}

int manhattan_distance (coordinate a, coordinate b){
    int dx = a.x - b.x;
    int dy = a.y - b.y;

    if (((dx ^ dy) < 0) != true)
        return abs(dx + dy);
    else
        return max(abs(dx), abs(dy));    
}

void generateAdjacent(std::vector<coordinate> &adjacent, 
                      coordinate selectionCenter , int range){
    
    int d[6][2] ={{0, -1},{1,0}, {-1,1},{-1, 0},{1,-1},{0,1}}; 
    
    for(int i = 0 ; i< 6; ++i){
        int X = selectionCenter.x + d[i][0];
        int Y = selectionCenter.y + d[i][1];
        coordinate temp(X,Y);
        adjacent.push_back(temp);
                   /* cout << "A:" << selectionCenter.x << "," << selectionCenter.y  << " B:" << temp.x<< "," << temp.y << " Distance:" << man_dist << endl; */
    }
}

bool checkSwap(coordinate A, std::vector<coordinate> items){
    for (auto &elem : items){
        if (elem == A)
            return true;
    }
    return false;
}

