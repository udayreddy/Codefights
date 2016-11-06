std::vector<std::string> spamDetection(std::vector<std::vector<std::string>> messages, std::vector<std::string> spamSignals) {
    std::vector<std::string> out(4);
    
    // check word count
    out[0] = word_count(messages);
    //cout << out[0] << endl;
    // check user content
    out[1] = check_user_content(messages);
    //cout << out[1] << endl;
    // check content
    out[2] = check_content(messages);
    //cout << out[2] << endl;
    // check spam signals
    out[3] = check_spam_signals(messages,spamSignals);
    //cout << out[3] << endl;

    return out;
}

typedef std::vector<std::vector<std::string>> Msgs;

std::string word_count(Msgs msgs){
    std::string result;
    int count = 0 , total_count = msgs.size();
    for (auto msg : msgs){
        if (CountWords(msg[0]) < 5)
            count++;
    }
    
    if ((float(count)/float(total_count))*100 > 90){
        int gcd = GCD(count, total_count);
        result = "failed: ";
        result += std::to_string((count/gcd));
        result += "/";
        result += std::to_string((total_count/gcd));
    } else {
        result = "passed";
    }
        
    return result ;
}

std::string check_user_content(Msgs msgs){
    std::map<int,std::vector<std::string>> msgs_per_user;
    std::string failed_out = "failed:";
    bool failed = false;
    // map users to their messages
    for (auto elem : msgs){
        int id = atoi(elem[1].c_str());
        auto it = msgs_per_user.find(id);
        if (it != msgs_per_user.end())
            it->second.push_back(elem[0]);
        else {
            std::vector<std::string> temp ;
            temp.push_back(elem[0]);
            msgs_per_user.insert(
                std::pair<int,std::vector<std::string>>
                (id,temp));
        }
    }
    
    // check each user messages
    for (auto elem : msgs_per_user){
        std::vector<std::string> msg_list = elem.second;
        if (msg_list.size() > 1){
            for (int i = 0 ; i < msg_list.size(); i++){
                int count = 0, total_count = msg_list.size();
                for (int j = 0 ; j < msg_list.size() ; j++){
                    if (!msg_list[i].compare(msg_list[j]))
                        count++;
                }
                if ((float(count)/float(total_count))*100 > 50.00){
                    failed = true;
                    failed_out += " ";
                    failed_out += std::to_string(elem.first);
                    break;
                }
            }
        }
    }
    
    if (failed == true)
        return failed_out;
    
    return "passed";
}

std::string check_content(Msgs msgs){
    std::set<std::string> failed_out ;
    
    if (msgs.size() > 1){
        for (int i = 0 ; i < msgs.size(); i++){
            int count = 0, total_count = msgs.size();
            //std::string curr_msg = msg[i][0]
            for (int j = 0 ; j < msgs.size() ; j++){
                if (!msgs[i][0].compare(msgs[j][0]))
                    count++;
            }
            if ((float(count)/float(total_count))*100 > 50){
                failed_out.insert(msgs[i][0]);
                break;
            }
        }
    
        if (failed_out.size() > 0){
            std::string out = "failed:";
                for (auto item : failed_out){
                    out += " ";
                    out += item;
                }
            return out;
        }
    }
    
    return "passed";
}

std::string check_spam_signals(Msgs msgs,std::vector<std::string> signals){
   if (signals.size() > 0){
        std::set<std::string> failed_out;
        int count = 0, total_count = msgs.size();
        for (auto elem : msgs){
            std::string msg = Uppercase(elem[0]);
            bool found = false;
            for (auto signal : signals){
                if (findSignal(msg,Uppercase(signal))){
                    failed_out.insert(signal);
                    found = true;
                }
            }
            if (found == true)
                count++;
        }
        
        if ((float(count)/float(total_count))*100 > 50){
            std::string out = "failed:";
                for (auto item : failed_out){
                    out += " ";
                    out += item;
                }
            return out;
        }
   }
    return "passed";
}

int CountWords(std::string str){
   int numWords = 0;
    std::string word = "";
    for (int i = 0 ; i < str.size() ; i++){
        while (std::isalpha(str[i])){
            word += str[i];
            i++;
        }
        if (word.compare(""))
            numWords++;
        word = "";
    }

   return numWords;
}

std::string Uppercase(std::string str){
    for (auto & c: str) c = toupper(c);
    return str;
}

int GCD(int a, int b){
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

bool findSignal(std::string str, std::string signal){
    std::string word = "";
    for (int i = 0 ; i < str.size() ; i++){
        while (std::isalpha(str[i])){
            word += str[i];
            i++;
        }
        if (!word.compare(signal))
            return true;
        word = "";
    }
    return false;
}