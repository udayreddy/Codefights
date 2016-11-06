
std::vector<int> minimalBasketPrice(int maxPrice, std::vector<int> vendorsDelivery, std::vector<std::vector<int>> vendorsProducts) {
        int comboSize = vendorsProducts[0].size();
        Combos combo(comboSize);
        Combos bestCombo(comboSize);
        getBestCombo(vendorsProducts,0,combo,
                 bestCombo,maxPrice,vendorsDelivery);
        std::sort(bestCombo.vendors.begin(), bestCombo.vendors.end());
    return bestCombo.vendors;
}

class Combos {
    public:
        std::vector<int> vendors;
        std::vector<int> products;
        int maxDelivery;
        Combos(int proNo){
            maxDelivery = -1 ;
            vendors.resize(proNo);
            products.resize(proNo);
        }
};


void getAllcombos(const vector<vector<int> > &allVecs, int vecIndex, 
                  Combos combo,std::vector<Combos> &combos, int maxPrice){
    if (vecIndex >= allVecs[0].size())
    {
        if (std::find(combo.products.begin(), combo.products.end(), -1) == combo.products.end() && std::accumulate(combo.products.begin(),combo.products.end(),0) <= maxPrice)
        {
            set<int> s;
            unsigned size = combo.vendors.size();
            for( unsigned j = 0; j < size; ++j ) s.insert( combo.vendors[j] );
                    combo.vendors.assign( s.begin(), s.end() );
            combos.push_back(combo);
        }       
        return;
    }
    for (int i=0; i<allVecs.size(); i++){
      
        combo.vendors[vecIndex] = i;
        combo.products[vecIndex] = allVecs[i][vecIndex];
        //recurssion
        getAllcombos(allVecs, vecIndex+1, combo,combos,maxPrice);
    }
}


std::vector<int> getBestCombo (std::vector<Combos> &combos,std::vector<int> vendorsDelivery) {
    Combos bestCombo = combos[0] ;
    // get max delivery time for each combo
    for (int i = 0 ; i < combos.size() ; i++){
        combos[i].maxDelivery = vendorsDelivery[combos[i].vendors[0]];
        for (int j = 0 ; j < combos[i].vendors.size(); j++){
                if (vendorsDelivery[combos[i].vendors[j]] >
                    combos[i].maxDelivery){
                combos[i].maxDelivery = vendorsDelivery[combos[i].vendors[j]];
            }
        }
        if (combos[i].maxDelivery <= bestCombo.maxDelivery || 
            bestCombo.maxDelivery == -1){
                bestCombo = combos[i];
            }
    }
    
    std::sort(bestCombo.vendors.begin(), bestCombo.vendors.end());
    return bestCombo.vendors;
}

void getBestCombo(const vector<vector<int> > &allVecs, int vecIndex,
                  Combos combo,Combos &bestCombo, int maxPrice,
                  std::vector<int> vendorsDelivery){
    if (vecIndex >= allVecs[0].size())
    {
        if (std::find(combo.products.begin(), combo.products.end(), -1) == combo.products.end() && std::accumulate(combo.products.begin(),combo.products.end(),0) <= maxPrice)
        {
            //unique vendors
            set<int> s;
            unsigned size = combo.vendors.size();
            for( unsigned j = 0; j < size; ++j ) s.insert( combo.vendors[j] );
                    combo.vendors.assign( s.begin(), s.end() );
            
            //bestCombo
            combo.maxDelivery = vendorsDelivery[combo.vendors[0]];
            for (int k = 0 ; k < combo.vendors.size(); k++){
                if (vendorsDelivery[combo.vendors[k]] >
                    combo.maxDelivery){
                    combo.maxDelivery =
                        vendorsDelivery[combo.vendors[k]];
                }
            }
            if (combo.maxDelivery <= bestCombo.maxDelivery || 
                bestCombo.maxDelivery == -1){
                    bestCombo = combo;
            }            
        }       
        return;
    }
    for (int i=0; i<allVecs.size(); i++){
      
        combo.vendors[vecIndex] = i;
        combo.products[vecIndex] = allVecs[i][vecIndex];
        //recurssion
        getBestCombo(allVecs, vecIndex+1, combo,
                     bestCombo,maxPrice,vendorsDelivery);
    }    
}


void printcomboVendors(Combos &combo){
    cout << "Combo Vendors: [";
            for (std::vector<int>::iterator it = combo.vendors.begin(); it !=
                 combo.vendors.end() ; ++it ){
                cout << *it  << "," ;
            }
            cout << "]" << endl;
}

void printcomboProducts(Combos &combo){
    cout << "Combo Products: [";
            for (std::vector<int>::iterator it = combo.products.begin(); it !=
                 combo.products.end() ; ++it ){
                cout << *it  << "," ;
            }
            cout << "]" << endl;
}

void printOut(std::vector<int> out){
    cout << "Out: [";
            for (std::vector<int>::iterator it = out.begin(); it !=
                out.end() ; ++it ){
                cout << *it  << "," ;
            }
            cout << "]" << endl;
}

