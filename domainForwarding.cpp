std::vector<std::vector<std::string>> domainForwarding(std::vector<std::vector<std::string>> redirects) {
    std::vector<std::vector<std::string>> groups;
    std::map<std::string,std::vector<std::string>> outMap;

    //unsorted groups
    while (redirects.begin() != redirects.end()) {
        std::vector<std::string> out;
        string final_domain = "";
        for (std::vector<std::vector<std::string>>::iterator redirect =
             redirects.begin(); redirect != redirects.end() ;){
            std::vector<std::string> temp = *redirect;
            bool erase = false;
            if (out.size() == 0) {
                out.push_back(temp[0]);
                final_domain = temp[1];
                out.push_back(temp[1]);
                erase = true;
            } else {
                bool firstelement = searchdomain(temp[0],out);
                bool secondelement = searchdomain(temp[1],out);
                if (firstelement || secondelement){
                    if (firstelement != true){
                        out.push_back(temp[0]);
                    }else if (secondelement != true){
                        out.push_back(temp[1]);
                        final_domain = temp[1];
                    }
                     erase = true;
                }
            }

            if (erase == true && redirect != redirects.end()){
                // remove redirect
                  redirect =  redirects.erase(redirect);
                  redirect = redirects.begin();
            } else {
                ++redirect;
            }
        
        }
        std::sort(out.begin(), out.end());
        outMap.insert(std::pair<string,vector<string>>(final_domain,out));
        
    }

    //sort the groups
for ( auto it = outMap.begin(); it != outMap.end(); it++ )
{
                  groups.push_back(it->second);
}
    
    //std::sort(outMap.begin(), outMap.end());
    
    return groups;
}

bool searchdomain(std::string input, std::vector<string> list){
    if (std::find(list.begin(),list.end(), input) != list.end()){
        return true;
    }
    return false;
    
}
