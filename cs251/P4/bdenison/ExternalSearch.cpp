#include "ExternalSearch.h"

bool extern_search(string filename, string toFind){

//cout<<"toFind: "<<toFind<<", filename: "<<filename<<"\n";
    FILE* toSearch;
    toSearch = fopen(filename.c_str(),"r");
    if(toSearch==NULL){
        cout << "File not found!\n";
        return false;
    }
    fseek(toSearch, 0L, SEEK_END);
    long int sz = ftell(toSearch);
    long int offset = 0;
    long int midDex;

    string cur;
    string prev = "";
    int i = 1;
    char c;
    while(midDex>1){

        cur = "";

        midDex = (sz/(2*i));
        //For loop to get to the nextline char before this
        for(long int j = 0; j<midDex+offset; j++){
            fseek(toSearch, midDex+offset-j-1, SEEK_SET);
            c = fgetc(toSearch);
            if(c=='\n'){
                break;
            }
        }

        //For loop to get to the end of the string
        while((c = fgetc(toSearch))!='\n'){
            cur = cur+c;
        }

        if(toFind.compare(cur)>0){
            offset+=midDex;
        }
        else if(toFind.compare(cur)==0){
            return true;
        }
        if(cur.compare(prev)==0){
            break;
        }
        i++;

    }
    return false;
}
