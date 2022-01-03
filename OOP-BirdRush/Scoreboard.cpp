#include "Scoreboard.hpp"
using namespace std;



Scoreboard::Scoreboard(){ //reading Scores.txt
    string line;
    ifstream myfile; 
    myfile.open("Scores.txt");
    int i = 4;
    while (getline(myfile, line))
    {
        scores[i] = stoi(line); //storing file contents in an array
        i--;
    }
    myfile.close();

}


//writing the first 4 scores on scoreboard
void Scoreboard::writeText(SDL_Renderer *renderer, TTF_Font *font,SDL_Texture * tex){
    
    // int n = sizeof(scores) / sizeof(scores[0]);
    // sort(scores, scores + n); //sorting scores arrays
    string s = "First: " + to_string(scores[4]);
    char *char_score = (char *)s.c_str();
    t.draw(renderer, 330, 190,  char_score,  font,  tex);

    s = "Second: " + to_string(scores[3]);
    char_score =  (char *)s.c_str();
    t.draw(renderer, 310, 285,  char_score,  font,  tex);

    s = "Third: " + to_string(scores[2]);
    char_score = (char *)s.c_str();
    t.draw(renderer, 330, 375,  char_score,  font,  tex);

    s = "Fourth: " + to_string(scores[1]);
    char_score = (char *)s.c_str();
    t.draw(renderer, 310, 475,  char_score,  font,  tex);
}

void Scoreboard::updateScore(int current_score){
    bool duplicate = false;
    for (int i = 0; i <= 4; i++){
        if (scores[i] == current_score){
            duplicate = true;
        }
    }
    if (duplicate == false){
        scores[0] = current_score;
    } 
    // scores[4] = current_score; //adding current_score to arr of stored scores
    int n = sizeof(scores) / sizeof(scores[0]);
    sort(scores, scores + n); //sorting scores arrays
    fstream clearFile; //clearing file contents 
    clearFile.open("Scores.txt", ofstream::out | std::ofstream::trunc);
    clearFile.close();
    fstream myFile;
    myFile.open("Scores.txt", ios::app);
    //writing updated top 4 scores
    for (int i = 4; i >= 1; i--)
    { 
        myFile << scores[i] << endl;
    }
    myFile.close();
}