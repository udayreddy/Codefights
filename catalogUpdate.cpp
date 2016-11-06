std::vector<std::vector<std::string>> catalogUpdate(std::vector<std::vector<std::string>> catalog, std::vector<std::vector<std::string>> updates) {
    
    for (std::vector<std::vector<std::string>>::iterator update = updates.begin() ; update != updates.end(); ++update){
        bool found = false;
        std::vector<std::string> Update = *update;
        for (std::vector<std::vector<std::string>>::iterator item = catalog.begin(); item != catalog.end(); ++item){
            std::vector<std::string> catalogItem = *item;
            std::vector<std::string>::iterator itv = update->begin();
            //std::string temp = *itv;
            if (Update[0].compare(catalogItem[0]) == 0){
                itv++;
                while(itv != update->end()) {
                    item->push_back(*itv);
                    itv++;
                }
                std::sort(item->begin()+1, item->end());
                found = true;
                break;
            }
            
        }
        if (found != true){
            catalog.push_back(*update);
        }
    }
    
    std::sort(catalog.begin(), catalog.end());
    return catalog;
}