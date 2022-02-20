#include <math.h>
#include <ostream>
#include <algorithm> 
#include "utilities.h"
#include <fstream>
#include <exception>
#include <sstream>
using std::istringstream;
void sort_by_magnitude(vector<double> &source){
    auto sort_lambda = [](double const &num1, double const &num2){
        return abs(num1) < abs(num2);
    };//ascending  order
    std::sort(source.begin(),source.end(),sort_lambda);
};
void create_csv(){
        std::ofstream myFile("bin//TEST.csv");
        // Send data to the stream
        myFile << "1,100,5\n";
        myFile << "2,3,7\n";
        myFile << "05,7,20\n";
        myFile << "3,3,3\n";
        myFile.close();
}
void create_txt(){
    // string text = "Lorem ipsum, dolor sit! ame456!t, consectetur? adipiscing elit. Ut porttitor.";
    // std::cout << text << std::endl;
    // text.erase(std::remove_if(text.begin(), text.end(), ispunct), text.end());
    // std::cout << text << std::endl;
    std::ofstream outfile ("bin//test.txt");
    outfile << "the)s are no%y6 wo!e4" << std::endl;

    outfile.close();
}
map<string, int> occurrence_map(const string path){
    map<string, int> result;
    std::ifstream file(path);
    string sentence,word; 
    if (!file.is_open()) {
        throw std::runtime_error("File can not find");
    }
    while(getline(file,sentence))
    {
        istringstream str(sentence);
            while(getline(str,word,' ')){
                string key;
                if (word.size()==1 && iswalnum(word[0])){key = word; result[key]+=1;}

                for (int i= 0;i < word.size()-1;i++){
                    if (i == 0){
                        if (iswalnum(word[i]) || word[i] == '\''){
                            key.push_back(char (tolower(word[i])));
                        }
                        else if (word[i] == '(' || word[i] == '"'){ }
                        else{break;}            
                        if (word.size() ==2){
                            if (iswalnum(word[i+1]) || word[i+1] == '\''){
                            key.push_back(char (tolower(word[i+1])));
                            }
                            else if (word[i+1] == '(' || word[i+1] == ')' || word[i+1] == '"' || ispunct(word[i+1] )){ }
                            else{continue;}
                            result[key]+=1;
                        }           
                    }
                    else if (i== word.size()-2){
                        if (iswalnum(word[i])|| word[i] == '\''){key.push_back(char (tolower(word[i])));}
                        else if(word[i]== ')'|| word[i] == '\"'){
                            if (iswpunct(word[i+1])){
                                result[key]+=1;
                            }
                            break;
                        }
                        else if(iswpunct(word[i])){
                            if(word[i+1]== ')'|| word[i+1] == '\"'){
                                result[key]+=1;
                            }
                            break;
                        }
                        else{
                            break;
                        }

                        //checking the end of the word
                        if (iswalnum(word[i+1]) || word[i+1] == '\''){
                            key.push_back(char (tolower(word[i+1])));
                            result[key]+=1;
                        }
                        else if (word[i+1] == ')' || word[i+1] == '"' || iswpunct(word[i+1])){
                            result[key]+=1;
                        }     
                    }
                    else{
                        if (iswalnum(word[i]) || word[i] == '\''){
                        key.push_back(char (tolower(word[i])));
                        }
                        else{
                            break;
                        }
                    }

                }
                //std::cout << key<<std::endl;
            }  
    }

    return result;
}
TypedArray<TypedArray<double>> read_matrix_csv(const string path){
    TypedArray<TypedArray<double>> matrix;
    string line,number;
    int pre_size = 0;
    bool start = false;
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("File can not find");
    }
    try{
        while(getline(file,line))
        {
            TypedArray<double> row;
            istringstream str(line);
            while(getline(str,number,',')){
                row.push(std::stod(number));
            }            
            if (!start){
                start = true;
                pre_size =  row.size();
            }
            if (pre_size != row.size()){
                throw std::runtime_error("data in CSV file is not metrix");
            }
            
            matrix.push(row);
        }
    }catch(std::exception e ){
        throw std::runtime_error("data in CSV file is not metrix");
    } 
    return matrix;
}