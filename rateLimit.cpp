std::vector<int> rateLimit(std::vector<std::vector<int>> sentBatches, std::vector<std::vector<int>> receivedMessages, int startingAllowance) {
    std::map<int,int> Users;
    std::vector<int> failedMsgs;
    std::map<int,std::vector<Msg>> time_msg_map;
    
    // load all sent messages    
    if (sentBatches.size() > 0){
        for (int i = 0 ; i < sentBatches.size(); i++ ){
            std::vector<int> temp;
            int time  = sentBatches[i][0];
            //cout << time << endl;
            for (int j = 1 ; j < sentBatches[i].size(); j++){
                temp.push_back(sentBatches[i][j]);
                Users.insert(
                    std::pair<int,int>(sentBatches[i][j],startingAllowance));
            }
            
            auto it = time_msg_map.find(time);
            if ( it != time_msg_map.end()){
                it->second.push_back(Msg("SENT",i,temp));
            } else {
                std::vector<Msg> msgs;                
                msgs.push_back(Msg("SENT",i,temp));
                time_msg_map.insert(
                    std::pair<int,std::vector<Msg>>(time,msgs));
            }        
        }
    } else {
        return failedMsgs;
    }

    // load all receive messages
    if (receivedMessages.size() > 0){
        for (int i = 0 ; i < receivedMessages.size(); i++ ){
            std::vector<int> temp = {receivedMessages[i][1]};
            int time  = receivedMessages[i][0];
            //cout << time << endl;
            Users.insert(
                std::pair<int,int>(receivedMessages[i][1],startingAllowance));
            auto it = time_msg_map.find(time);
            if ( it != time_msg_map.end()){
                it->second.push_back(Msg("RECEIVE",i,temp));
            } else {
                std::vector<Msg> msgs;                
                msgs.push_back(Msg("RECEIVE",i,temp));
                time_msg_map.insert(
                    std::pair<int,std::vector<Msg>>(time,msgs));
            } 
        }
    }
    
    int current_time = 0;
    // check batches for failures
    for (auto time_msgs : time_msg_map){
        
        resetAllowance(Users,current_time,time_msgs.first,startingAllowance);
        std::vector<Msg> msgs = time_msgs.second;
        current_time = time_msgs.first;
   
        //sort msgs by time
        std::sort(msgs.begin(),msgs.end(),msgComp());
        
        for (auto msg : msgs){
          /*  time_t ts = current_time;
            cout << "Time :" << "(" << time_msgs.first << ")" 
             << std::asctime(std::localtime(&ts))
             << " Msg:" << msg.SorR << "-" << msg.index << " Users:";
            
            for (auto u : msg.users)
                cout << u  << "(" << Users[u] << ")" << ",";
            cout << endl;
            */
            if (!msg.SorR.compare("RECEIVE")){
                Users[msg.users[0]] += 1;
            } else {
                bool error = false;
                for (auto user : msg.users){
                    if(Users[user] == 0){
                        error = true;
                        break;
                    }
                }
                
                if ( error ==  true){
                    //cout << "failed" << endl;
                    failedMsgs.push_back(msg.index);
                } else{
                    for (auto user : msg.users){
                        Users[user] -= 1;
                    }                
                }   
            }
        }
    }
    return failedMsgs;
}


class Msg {
    public:
    std::string SorR;
    int index;
    std::vector<int> users;
    Msg(std::string SR,int i,std::vector<int> u){
        SorR = SR;
        index = i;
        users = u;
    }
};

struct msgComp {
    bool operator() (Msg& A, Msg& B)
    {
        return A.SorR < B.SorR;
    } 
};

void resetAllowance(std::map<int,int> &Users, int before,
                    int now, int allowance){

    time_t ts = before;
    struct tm *_localtime = std::localtime(&ts);
    int before_yr = _localtime->tm_year,
        before_mon = _localtime->tm_mon,
        before_day = _localtime->tm_mday;
        
    ts = now;
    _localtime = std::localtime(&ts);
    int now_yr = _localtime->tm_year,
        now_mon = _localtime->tm_mon,
        now_day = _localtime->tm_mday;
    
    //cout << before_day << "-" << now_day << endl;
    if (before_yr != now_yr || before_mon != now_mon || 
        before_day != now_day){
        //cout << "Time reset" << endl;
        for (auto &elem : Users)
            elem.second = allowance;
    }
}