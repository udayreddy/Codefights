std::vector<std::vector<std::vector<int>>> kikCode(std::string userId) {
    KIKcode kikcode;
    std::queue<bool> binary = get52Binary(userId);
    
    // load all circumferences
    getCoordinates(1,binary,3,kikcode);
    getCoordinates(2,binary,4,kikcode);
    getCoordinates(3,binary,8,kikcode);
    getCoordinates(4,binary,10,kikcode);
    getCoordinates(5,binary,12,kikcode);
    getCoordinates(6,binary,15,kikcode);
    
    return kikcode;
}

typedef std::vector<std::vector<std::vector<int>>> KIKcode;

std::queue<bool> get52Binary(std::string id){
    std::queue<bool> bin;
    
    std::string binary = std::bitset<52>(atol(id.c_str())).to_string();
    for (int i = binary.size()-1 ; i >= 0; i--)
        bin.push(to_bool(binary[i]));

    return bin;
}

void getCoordinates (int circumference, std::queue<bool> &bq , int sectors, 
                     KIKcode &kikcode ){
    std::vector<std::vector<int>> segment;
    int deg = 360/sectors;
    
    for (int i = 0 ; i < sectors ; i++ ){
        bool curr = bq.front();
        bq.pop();
        if (curr == true){
            std::vector<int> temp = {circumference,i*deg};
            //cout << temp[0] << "," << temp[1] << endl;
             if(std::find(segment.begin(), segment.end(), temp)==segment.end())
            {
                segment.push_back({circumference,i*deg});
            } else {
                segment.pop_back();
            }
            segment.push_back({circumference,(i+1)*deg});
        }
    }
    
    if (segment.size() > 2){
        std::vector<int> start = {circumference,0};
        std::vector<int> end = {circumference,360};
        if (std::find(segment.begin(), segment.end(), start)
             != segment.end() &&
            std::find(segment.begin(), segment.end(), end)
             != segment.end()){
            int i = segment[1][1];
            std::vector<std::vector<int>> temp_segment;
            temp_segment.push_back({circumference,i+360});
            for (int k = 2; k < segment.size()-1; k++){
                //cout << segment.size() << temp_segment.size() << endl;
                temp_segment.push_back(segment[k]);
            }
            segment = temp_segment;
        }
    }
    
    std::sort(segment.begin(),segment.end());
    
    for (int j = 0; j < segment.size(); j = j+2){
        std::vector<std::vector<int>> temp_segment = {segment[j],segment[j+1]};
        cout << j << endl;
        kikcode.push_back(temp_segment);
    }
}


bool to_bool(char &s) {
     return s != '0';
}