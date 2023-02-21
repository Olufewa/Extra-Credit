#include <iostream>
#include <fstream>

using namespace std;

const int NUMOFMATCHES = 5;

bool programmerPrefersCurDept(int preferences[NUMOFMATCHES*2][NUMOFMATCHES],int programmerIndex,int dep,int curDep){

    for(int i = 0; i < NUMOFMATCHES; i++){
        if(preferences[programmerIndex][i] == curDep){
            return true;
        }
        if(preferences[programmerIndex][i] == dep){
            return false;
        }
    }
  
    return false;
};
void matchPreferences(int preferences[NUMOFMATCHES*2][NUMOFMATCHES])
{

    int programmer[NUMOFMATCHES] = {-1,-1,-1,-1,-1};
 
    bool takenDepart[NUMOFMATCHES] = {};
    int freeDep = 5;

    while(freeDep > 0){
        int d;

        for(d=0; d<NUMOFMATCHES; d++){
            if(takenDepart[d] == false){
                break;
            }
        }

        for(int i = 0; i<NUMOFMATCHES && takenDepart[d]==false; i++)
        {

            int progPref = preferences[d][i];

            if(programmer[progPref-1]==-1){
                programmer[progPref-1]= d;
                takenDepart[d]= true;
                freeDep--;
            }
            else{
                
                int curDep = programmer[progPref-1];

                if(programmerPrefersCurDept(preferences, progPref+4, d+1, curDep+1) == false)
                {
                    programmer[progPref-1]= d;
                    takenDepart[d]= true;
                    takenDepart[curDep]=false;
                }
            }
        }
    }

    for (int i = 0; i < NUMOFMATCHES; i++){

        for(int j=0; j < NUMOFMATCHES; j++){
            if(i==programmer[j]){
                cout << "Department #" << i+1 << " will get Programmer " << j+1 << endl; 
            }
        }
    }
};
int main()
{
    int preferences[NUMOFMATCHES*2][NUMOFMATCHES] = {-1};
 
    ifstream myFile;
    myFile.open("/home/o581a507/EECS_348/extra_credit/matching-data.txt");
    if(myFile.fail())
    {
        cout << "File was unable to be opened."; 
    }
    else{
        while(myFile){
            for(int i = 0; i < NUMOFMATCHES; i++)
            {
                for(int j = 0; j < NUMOFMATCHES; j++)
                {
                    myFile >> preferences[j][i];                    
                }
            }
            for(int i = 0; i < NUMOFMATCHES; i++)
            {
                for(int j = NUMOFMATCHES; j < NUMOFMATCHES*2; j++)
                {
                    myFile >> preferences[j][i];             
                }
            }
        }
    }
    myFile.close();

    matchPreferences(preferences);
    return 0;
}