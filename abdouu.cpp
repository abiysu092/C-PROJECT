#include <algorithm>
#include <math.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;

map<string, int> readFile(string fileName) {

    ifstream file;
    file.open(fileName);

    string ligne;
    map<string, int> f1;

    while (getline(file, ligne)){
        
        int id = 0;
        string word = "";
        string sp = " ";

        for (int i=0; i<ligne.length(); i++){
            
            string chh = "";
            chh += tolower(ligne[i]);

            if ((chh != sp) & (int(ligne[i]) != 13) & (chh.length() > 0)){
                word += chh;
            } else{  
                if (int(word[0]) != 0){  
                    
                    if (f1.count(word) == 1){  
                        f1[word] ++;
                    }else{
                        f1[word] = 1;
                    }
                    word = "";
                    id = i+1;
                }
            }
        }    
        if ((int(word[0]) != 13) & (int(word[0]) != 0)){  
            if (f1.count(word) == 1){
                f1[word] ++;
            }else{
                f1[word] = 1;
            }
        }
    }
    file.close();
    return f1;
}
int main(int argc, char *argv[]) {

    map<string, int> f1, f2;

    f1 = readFile(argv[1]);
    f2 = readFile(argv[2]);

    vector<string> keys;

    for (auto it = f1.begin(); it != f1.end(); ++it) {
        
        if (find(keys.begin(), keys.end(), it->first) == keys.end()){
            
            keys.push_back(it->first);
        }
    }
    for (auto it = f2.begin(); it != f2.end(); ++it) {
        
        if (find(keys.begin(), keys.end(), it->first) == keys.end()){
            
            keys.push_back(it->first);
        }
    }

    int prod, ta1, ta2 = 0;
    int rep1, rep2 = 0;
    float ta = 1.0;
    
    for (int i=0; i<keys.size(); i++){

        if (f1.count(keys[i]) == 1){
            rep1 = f1[keys[i]];}else rep1 = 0;
        
        if (f2.count(keys[i]) == 1){
            rep2 = f2[keys[i]];}else rep2 = 0;

        cout << keys[i] << ": " << rep1 << " | " << rep2 << endl;

        prod += rep1*rep2;
        ta1 += pow(rep1, 2);
        ta2 += pow(rep2, 2);

    }
    float sim = (prod / (sqrt(ta1) * sqrt(ta2))) * 100;  
    cout << sim << "%\n";
    return 0;
}