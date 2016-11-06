bool plagiarismCheck(std::vector<std::string> code1, std::vector<std::string> code2) {
    if (code1.size() != code2.size())
        return false;
    
    bool result = true;
    std::string rest_of_code_1 = "", rest_of_code_2 = "";
    std::vector<std::string> code_1 = getVariables(code1,rest_of_code_1);
    std::vector<std::string> code_2 = getVariables(code2,rest_of_code_2);
    
    cout << "code1: " << rest_of_code_1 << endl;
    cout << "code2: " << rest_of_code_2 << endl;
    
    if (rest_of_code_1.compare(rest_of_code_2) 
        || code_1.size() != code_2.size()){
        return false;
    }
    
    printVector(code_1);
    printVector(code_2);
    
    // compare the variables
    compareVariables(code_1,code_2,result);   
    
    return result;
    
}

std::vector<std::string> getVariables( std::vector<std::string> code,
                                      std::string &rest_of_code){
    std::vector<std::string> out;
    std::string temp1 = "", temp2 = "";
        
    //create single line of code
    for (auto elem : code) {
        temp1 = elem;
       //create list of variables
        for (int i = 0; i < temp1.size() ; i ++){           
                while (isalnum(temp1[i]) || temp1[i] == '_'){
                    temp2 += temp1[i];
                    i++;
                }
                if (temp2.compare("")){
                    if (isdigit(temp2[0]))
                        rest_of_code += temp2;
                    else
                        out.push_back(temp2);
                    temp2 = "";
                }
                rest_of_code += temp1[i]; 
        }
    }
    
    return out;
}

void printVector(std::vector<std::string> &in){
    for (auto elem : in)
        cout << elem << ":";
    cout << endl;
}

void compareVariables(std::vector<std::string> one, std::vector<std::string> two, bool &cheated){
    for(int i = 0 ; i < one.size() ; i++){
        if (one[i] != two[i]){
                std::string original = one[i];
                std::string change = two[i];
            for(int j = 0 ; j < one.size(); j++){
                if (one[j] == original){
                    if (two[j] != change){
                        cheated = false;
                        return;
                    }
                }
            }
        }
    }
}


bool isKeyword(std::string word){
    std::vector<std::string> keywords = {"def","alignas","alignof","and","and_eq","asm","atomic_cancel","atomic_commit","atomic_noexcept","auto","bitand","bitor","bool","break","case","catch","char","char16_t","char32_t","class","compl","concept","const","constexpr","const_cast","continue","decltype","default","delete","do","double","dynamic_cast","else","enum","explicit","export","extern","false","float","for","friend","goto","if","inline","int","import","long","module","mutable","namespace","new","noexcept","not","not_eq","nullptr","operator","or","or_eq","private","protected","public","register","reinterpret_cast","requires","return","short","signed","sizeof","static","static_assert","static_cast","struct","switch","synchronized","template","this","thread_local","throw","true","try","typedef","typeid","typename","union","unsigned","using","virtual","void","volatile","wchar_t","while","xor","xor_eq"};
    for (auto elem : keywords){
        if (!word.compare(elem))
            return true;
    }
        return false;
}