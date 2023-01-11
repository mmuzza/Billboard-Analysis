/*
Program 5: March Madness
Course: CS 141, Spring 2021.
System: Mac using Replit
Author: Muhammad Muzzammil
UIN: 661657007
*/

#include <iostream>   // For Input and Output
#include <fstream>    // For file input and output
#include <cassert>    // For the assert statement
#include <cctype>     // Allows using the tolower() function
#include <vector>     // For vectors
#include <cstring>    // For C string function strcpy
#include <sstream>    // For reading in CSV file and splitting by commas
#include <algorithm>  // For find(), which searches within a vector
#include <map> // using map. Profeesor Fulton said maps are allowed
using namespace std;

class Tournament {
  private:
  string region;
  int rank1;
  string team1;
  int score1;
  int rank2;
  string team2;
  int score2;
  string winningTeam;
  int roundNumber;
  int gameNumber;
  
  

  public:
  Tournament(){
  }

  Tournament(string region, int rank1, string team1, int score1, int rank2, string team2, int score2, string winningTeam, int roundNumber, int gameNumber){
    
    this->region = region;
    this->rank1 = rank1;
    this->team1 = team1;
    this->score1 = score1;
    this->rank2 = rank2;
    this->team2 = team2;
    this->score2 = score2;
    this->winningTeam = winningTeam;
    this->roundNumber = roundNumber;
    this->gameNumber = gameNumber;
  }

  string getRegion() {
    return region;
  }

  int getRank1() {
    return rank1;
  }

  string getTeam1() {
    return team1;
  }

  int getScore1() {
    return score1;
  }

  int getRank2() {
    return rank2;
  }

  string getTeam2() {
    return team2;
  }

  int getScore2() {
    return score2;
  }

  string getWinningTeam() {
    return winningTeam;
  }

  int getRoundNumber() {
    return roundNumber;
  }

  int getGameNumber() {
    return gameNumber;
  }

};


void readingTheCSVFile(string fileName, vector <Tournament> &tournaments){

  ifstream inStream;
  inStream.open(fileName);
  assert( inStream.fail() == false );

  tournaments.clear();

  string line, temp, word;
    int rowIndex = -1;
    vector<string> row;
    
    while(getline(inStream, line)) {
      row.clear();
      rowIndex++;
      int rank1 = 0, score1 = 0, rank2 = 0, score2 = 0, roundNumber = 0, gameNumber = 0;
      stringstream s(line);

      if (rowIndex == 0) {
        continue;
      }
      
      while (getline(s, word, ',')) { // read in columns of each line separated by comma
        row.push_back(word);
      }
      
      if (row[1] != "") {
        rank1 = stoi(row[1]);
      }
      if (row[3] != "") {
        score1 = stoi(row[3] );
      }
      if (row[4] != "") {
        rank2 = stoi(row[4]);
      }
      if (row[6] != "") {
        score2 = stoi(row[6]);
      }
      if (row[8] != "") {
        roundNumber = stoi(row[8]);
      }
      if (row[9] != "") {
        gameNumber = stoi(row[9]);
      }

      Tournament tournament (row[0], rank1, row[2], score1, rank2 , row[5] , score2, row[7], roundNumber, gameNumber);
      tournaments.push_back(tournament);
    }
    inStream.close();
}

void introducingTheProgram()
{
  cout << "Program 5: March Madness Frenzy" << endl;
  cout << "CS 141, Spring 2022, UIC\n" << endl;
  cout << "This program reads in data from NCAA Basketball Tournaments (aka March" << endl;
  cout << "Madness). It provides overall information regarding the data, allows you to" << endl;
  cout << "see the path taken to the championship, uses rankings of teams to determine" << endl;
  cout << "which region is expected to win at a given round and to find the best underdog" << endl;
  cout << "team, and calculates point differences within the games. You can also compare" << endl;
  cout << "the actual brackets to your own predictions!\n" << endl;
}


string takingFileFromTheUser(){
  string takeFileName;
  //cout << "Enter the name of the file with the data for the NCAA tournament: \n";
  cin >> takeFileName;
  return(takeFileName);
}


void showMenuOption(){
  cout << "\nSelect a menu option:" << endl;
  cout << "   1. Display overall information about the data" << endl;
  cout << "   2. Display the path of the winning team to the championship" << endl;
  cout << "   3. Determine which region is expected to win the championship based on a " << endl;
  cout << "given round" << endl;
  cout << "   4. Identify the best underdog within a given round" << endl;
  cout << "   5. Find the shoo-in and nail-biting games within a given round, or overall" << endl;
  cout << "   6. Compare the actual brackets to your predicted brackets" << endl;
  cout << "   7. Exit" << endl;
  cout << "Your choice --> ";
}

//menu option 1 //FULLY DONE
void getOverallInformation(vector <Tournament> &tournaments, string usersFile){

    map<string, bool>overallStats;

  cout << "Total number of games played in tournament: " << tournaments.size() << endl;
  cout << "The Final Four contestants are:" << endl;
  
  for (int i=0; i<tournaments.size(); i++){
    if(tournaments.at(i).getRegion() == "Final Four"){
      overallStats.insert(pair<string, bool>(tournaments.at(i).getTeam1(), true));
      overallStats.insert(pair<string, bool>(tournaments.at(i).getTeam2(), true));
    }
  }

  for (int i=0; i<tournaments.size(); i++){
    if(tournaments.at(i).getRegion() == "Championship" || tournaments.at(i).getRegion() == "Final Four"){
      continue;
    }
    string key = tournaments.at(i).getTeam1();
    if(overallStats.count(key) > 0 && overallStats.find(key)->second == true){
      cout << "        " << tournaments.at(i).getRegion() << " region: " << key << endl;
        overallStats[key] = false;
    }
    key = tournaments.at(i).getTeam2();
    if(overallStats.count(key) > 0 && overallStats.find(key)->second == true){
      cout << "        " << tournaments.at(i).getRegion() << " region: " << key << endl;
      overallStats[key] = false;
    }
  }
}

//menu option 2 //FULLY DONE
void pathToWinningTeamChampionship(vector <Tournament> &tournaments){
  
  string teamWinner; // save the championship winner team name
  vector<int>unsortedRounds, sortedRounds, numberGame;
  vector<string>firstTeam, secondTeam;

  //Find the team that won the championship and later use it to find the games
  for(int i=0; i<tournaments.size(); i++){
    if(tournaments.at(i).getRegion() == "Championship"){
      teamWinner = tournaments.at(i).getWinningTeam();
    }
  }

  // Now we search all the games that the championship team played all the way to finals.
  int numberOfRounds = 0;
  cout << "Path to the championship:" << endl;

  // save the round number, game number, team1, team2 in a vector for outout
  for(int k=0; k<tournaments.size(); k++){
    if((tournaments.at(k).getTeam1() == teamWinner) || (tournaments.at(k).getTeam2() == teamWinner)){
      unsortedRounds.push_back(tournaments.at(k).getRoundNumber());
      numberGame.push_back(tournaments.at(k).getGameNumber());
      firstTeam.push_back(tournaments.at(k).getTeam1());
      secondTeam.push_back(tournaments.at(k).getTeam2());
    }
  }

  // sort out the round numbers to print in order
  sortedRounds = unsortedRounds;
  sort(sortedRounds.begin(), sortedRounds.end());

  // matching the sorted with unsorted rounds so I can output the correct matching teams, and game numbers.
  for(int j=0; j<sortedRounds.size(); j++){
    for(int k=0; k<sortedRounds.size(); k++){
      if(sortedRounds[j] == unsortedRounds[k]){
        numberOfRounds++;
        cout << "Round " << numberOfRounds << ", Game " << numberGame[k] << ": ";
        cout << firstTeam[k] << " vs " << secondTeam[k] << ". Winner: ";
        cout << teamWinner << endl;
      }
      else{
        continue;
      }
    }
  }
}

//menu option 3 //FULLY DONE
void regionChampionsBasedOnRound(vector <Tournament> &tournaments){
  int roundNumber;
  int highestRank = 16;
  
  cout << "Enter a round to be evaluated: " << endl;
  cout << "   Select 2 for round 2" << endl;
  cout << "   Select 3 for round 3 'Sweet 16'" << endl;
  cout << "   Select 4 for round 4 'Elite 8'" << endl;
  cout << "   Select 5 for round 5 'Final 4'" << endl;
  cout << "Your choice --> ";
  cin >> roundNumber;
  cout << "Analyzing round " << roundNumber << "..." << endl;
  
  vector<int> region1, region2, region3, region4;
  vector<string> savingTeamName1, savingTeamName2, savingTeamName3, savingTeamName4, savingTeamName5;
  int countRankOfRegion1 = 0, countRankOfRegion2 = 0, countRankOfRegion3 = 0, countRankOfRegion4 = 0;

  if((roundNumber > 1) && (roundNumber < 5)){
    
    for(int i=0; i<tournaments.size(); i++){
      if ((tournaments.at(i).getRoundNumber() == roundNumber) && ((tournaments.at(i).getRegion() == "West") || (tournaments.at(i).getRegion() == "Greensboro"))){
        if (tournaments.at(i).getTeam1() == tournaments.at(i).getWinningTeam()){
          region1.push_back(tournaments.at(i).getRank1());
          savingTeamName1.push_back(tournaments.at(i).getRegion());
        }
        else{
          region1.push_back(tournaments.at(i).getRank2());
          savingTeamName1.push_back(tournaments.at(i).getRegion());
        } //saving all ranks for winning teams of User's chosen round for the West Region in a vector
      }
      if ((tournaments.at(i).getRoundNumber() == roundNumber) && ((tournaments.at(i).getRegion() == "East") || (tournaments.at(i).getRegion() == "Spokane"))){
        if (tournaments.at(i).getTeam1() == tournaments.at(i).getWinningTeam()){
          region2.push_back(tournaments.at(i).getRank1());
          savingTeamName2.push_back(tournaments.at(i).getRegion());
        }
        else{
          region2.push_back(tournaments.at(i).getRank2());
          savingTeamName2.push_back(tournaments.at(i).getRegion());
        } //saving all ranks for winning teams of User's chosen round for the East Region in a vector
      }
      if((tournaments.at(i).getRoundNumber() == roundNumber) && ((tournaments.at(i).getRegion() == "South") || (tournaments.at(i).getRegion() == "Wichita"))){
        if (tournaments.at(i).getTeam1() == tournaments.at(i).getWinningTeam()){
          region3.push_back(tournaments.at(i).getRank1());
          savingTeamName3.push_back(tournaments.at(i).getRegion());
        }
        else{
          region3.push_back(tournaments.at(i).getRank2());
          savingTeamName3.push_back(tournaments.at(i).getRegion());
        } //saving all ranks for winning teams of User's chosen round for the South Region in a vector
      }
      if ((tournaments.at(i).getRoundNumber() == roundNumber) && ((tournaments.at(i).getRegion() == "Midwest") || (tournaments.at(i).getRegion() == "Bridgeport"))){
        if (tournaments.at(i).getTeam1() == tournaments.at(i).getWinningTeam()){
          region4.push_back(tournaments.at(i).getRank1());
          savingTeamName4.push_back(tournaments.at(i).getRegion());
        }
        else{
          region4.push_back(tournaments.at(i).getRank2());
          savingTeamName4.push_back(tournaments.at(i).getRegion());
        } //saving all ranks for winning teams of User's chosen round for the Midwest Region in a vector
      }
    }
  
  //Adding all of the ranks up based on the region and round.
  for(int i = 0; i < region1.size(); i++){
    countRankOfRegion1 = countRankOfRegion1 + region1[i];
    countRankOfRegion2 = countRankOfRegion2 + region2[i];
    countRankOfRegion3 = countRankOfRegion3 + region3[i];
    countRankOfRegion4 = countRankOfRegion4 + region4[i];
  }

    // Evaluating which is the champion by comparing.
  if((countRankOfRegion1 <= countRankOfRegion2) && (countRankOfRegion1 <= countRankOfRegion3) && (countRankOfRegion1 <= countRankOfRegion4)){
    cout << "\nThe region expected to win is: " << savingTeamName1[0] << endl;
  }  
  else if((countRankOfRegion2 <= countRankOfRegion3) && (countRankOfRegion2 <= countRankOfRegion4) && (countRankOfRegion2 < countRankOfRegion1)){
    cout << "\nThe region expected to win is: " << savingTeamName2[0] << endl;
  }
  else if ((countRankOfRegion3 <= countRankOfRegion4) && (countRankOfRegion3 < countRankOfRegion1) && (countRankOfRegion3 < countRankOfRegion2)){
    cout << "\nThe region expected to win is: " << savingTeamName3[0] << endl;
  }
  else if((countRankOfRegion4 < countRankOfRegion1) && (countRankOfRegion4 < countRankOfRegion2) && (countRankOfRegion4 < countRankOfRegion3)) {
    cout << "\nThe region expected to win is: " << savingTeamName4[0] << endl;
  }
}

  else if(roundNumber == 5){

    // Get the highest Rank from Round 5
    for(int i = 0; i<tournaments.size(); i++){
      if((tournaments.at(i).getRegion() == "Final Four") && (tournaments.at(i).getRoundNumber() == roundNumber)){
        if(tournaments.at(i).getRank1() < tournaments.at(i).getRank2()){
          if(tournaments.at(i).getRank1() < highestRank){
            highestRank = tournaments.at(i).getRank1();
          }
        }
        else if(tournaments.at(i).getRank2() < tournaments.at(i).getRank1()){
          if(tournaments.at(i).getRank2() < highestRank){
          highestRank = tournaments.at(i).getRank2();
          }
        }
      }
    }
    // goes back in vector to get the teams with the highest Rank we got (Since it can be more than one team with same Rank)
    for(int i = 0; i<tournaments.size(); i++){
      if((tournaments.at(i).getRegion() == "Final Four") && (tournaments.at(i).getRoundNumber() == roundNumber)){
        if((tournaments.at(i).getWinningTeam() == tournaments.at(i).getTeam1()) && (tournaments.at(i).getRank1()==highestRank)){
          savingTeamName5.push_back(tournaments.at(i).getTeam1());
        }
        else if((tournaments.at(i).getWinningTeam() == tournaments.at(i).getTeam2()) && (tournaments.at(i).getRank2()==highestRank)){
          savingTeamName5.push_back(tournaments.at(i).getTeam2());
        }
        else{
          continue;
        }
      }
    }

    for(int i = 0; i<tournaments.size(); i++){
      bool isFound = false;
      if(tournaments.at(i).getRegion() != "Championship" && tournaments.at(i).getRegion() != "Final Four"){
        for (int j = 0; j<savingTeamName5.size(); j++){
          if ((tournaments.at(i).getTeam1() == savingTeamName5[j] || tournaments.at(i).getTeam2() == savingTeamName5[j])){
            cout << "\nThe region expected to win is: " << tournaments.at(i).getRegion() << endl;
            isFound = true;
          }
        }
        if (isFound == true){
          break;
        }
      }
    }
  }
}

//menu option 4 //FULLY DONE
void bestUnderdog(vector <Tournament> &tournaments){
  map <int, string> underDogs;
  vector<string>savingTeamName;
  vector<int>savingTeamRank;
  int userRound;
  int tempRankHolder = 0;

  cout << "Enter a round to be evaluated: " << endl;
  cout << "   Select 2 for round 2" << endl;
  cout << "   Select 3 for round 3 'Sweet 16'" << endl;
  cout << "   Select 4 for round 4 'Elite 8'" << endl;
  cout << "   Select 5 for round 5 'Final 4'" << endl;
  cout << "   Select 6 for round 6 'Championship'" << endl;
  cout << "Your choice --> ";
  cin >> userRound;

  if((userRound > 1) && (userRound < 7)){
    for (int i=0; i < tournaments.size(); i++){ // search through whole csv file
      if(tournaments.at(i).getRoundNumber() == userRound){ // find the lines of users round numbers
        if (tournaments.at(i).getRank1() > tournaments.at(i).getRank2()){ // check if rank 1 is > rank 2
          if (tournaments.at(i).getRank1() > tempRankHolder){ 
            underDogs.clear();
            tempRankHolder = tournaments.at(i).getRank1();
            underDogs.insert(pair<int, string>(tournaments.at(i).getRank1(), tournaments.at(i).getTeam1()));
          }
          else{
            continue;
          }
        }
        else if(tournaments.at(i).getRank2() > tournaments.at(i).getRank1()){
          if (tournaments.at(i).getRank2() > tempRankHolder){
            underDogs.clear();
            tempRankHolder = tournaments.at(i).getRank2();
            underDogs.insert(pair<int, string>(tournaments.at(i).getRank2(), tournaments.at(i).getTeam2()));
          }
          else{
            continue;
          }
        }
        else if(tournaments.at(i).getRank2() == tournaments.at(i).getRank1()){ // if they happen to be equal
          if (tournaments.at(i).getRank1() > tempRankHolder){
            underDogs.clear();
            savingTeamName.push_back(tournaments.at(i).getTeam1());
            savingTeamRank.push_back(tournaments.at(i).getRank1());
            savingTeamName.push_back(tournaments.at(i).getTeam2());
            savingTeamRank.push_back(tournaments.at(i).getRank2());
            for(int j = 0; j<tournaments.size(); j++){
              bool found = false;
              for(int k = 0; k < savingTeamName.size(); k++){
                if ((tournaments.at(j).getTeam1() == savingTeamName[k] || tournaments.at(j).getTeam2() == savingTeamName[k])){
                  underDogs.insert(pair<int, string>(savingTeamRank[k], savingTeamName[k]));
                  found = true;
                }
              }
              if (found == true){
                break;
              }
            }
          }  
        }
      }
    }
  }
  for(auto pair : underDogs)
    cout << "The best underdog team is " << pair.second << " which has rank " << pair.first << "." << endl;
}

// Menu option 5 FULLY DONE
void shooInAndNailBitingGames(vector <Tournament> &tournaments){
  int bigDifference = 0;
  int smallDifference = 500;
  int roundNumber;
  cout << "Enter a round to be evaluated: " << endl;
  cout << "   Select 1 for round 1" << endl;
  cout << "   Select 2 for round 2" << endl;
  cout << "   Select 3 for round 3 'Sweet 16'" << endl;
  cout << "   Select 4 for round 4 'Elite 8'" << endl;
  cout << "   Select 5 for round 5 'Final 4'" << endl;
  cout << "   Select 6 for round 6 'Championship'" << endl;
  cout << "   Select 7 for the overall tournament" << endl;
  cout << "Your choice --> ";
  cin >> roundNumber;
  
  vector<string>storingGameInfo;
  vector<int>storingGameNumber;
  vector<int>storingRoundNumber;
  
  if(roundNumber >= 1 && roundNumber <= 6){
    cout << "Analyzing round " << roundNumber << "..." << endl;
    //  shoo-in game: the one with the greatest difference in scores
    for (int i=0; i<tournaments.size(); i++){ // going through whole csv file
      if ((tournaments.at(i).getRoundNumber() == roundNumber)){ //searching for users round rows only
        if((tournaments.at(i).getScore1() - tournaments.at(i).getScore2()) > bigDifference){
          storingGameInfo.clear();
          storingGameNumber.clear();
          bigDifference = tournaments.at(i).getScore1() - tournaments.at(i).getScore2();
          storingGameInfo.push_back(tournaments.at(i).getTeam1()); // save team 1 name in index 0 
          storingGameInfo.push_back(tournaments.at(i).getTeam2()); // save team 2 name in index 1
          storingGameInfo.push_back(tournaments.at(i).getWinningTeam()); // save winning team name index 2
          storingGameNumber.push_back(tournaments.at(i).getGameNumber()); // saving game number index 0
        }
        else if ((tournaments.at(i).getScore2() - tournaments.at(i).getScore1()) > bigDifference){
          bigDifference = tournaments.at(i).getScore2() - tournaments.at(i).getScore1();
          storingGameInfo.clear();
          storingGameNumber.clear();
          storingGameInfo.push_back(tournaments.at(i).getTeam1()); // save team 1 in index 0 
          storingGameInfo.push_back(tournaments.at(i).getTeam2()); // save team 2 in index 1
          storingGameInfo.push_back(tournaments.at(i).getWinningTeam()); // save winning team index 2
          storingGameNumber.push_back(tournaments.at(i).getGameNumber()); // saving game number index 0
        }
      }
    }
    cout << "\nThe shoo-in game was: " << endl;
    cout << "Round " << roundNumber << ", " << "Game " << storingGameNumber[0] << ": " << storingGameInfo[0];
    cout << " vs " << storingGameInfo[1] << ". Winner: " << storingGameInfo[2] << endl;
    cout << "The difference was " << bigDifference << " points." << endl;
  
    
  
    
      //  nail-biting game: the one with the smallest difference in scores
    for (int i=0; i<tournaments.size(); i++){ // going through whole csv file
      if ((tournaments.at(i).getRoundNumber() == roundNumber)){ //searching for users round rows only
        if(((tournaments.at(i).getScore1() - tournaments.at(i).getScore2()) < smallDifference) && ((tournaments.at(i).getScore1() - tournaments.at(i).getScore2()) >= 0)){
          storingGameInfo.clear();
          storingGameNumber.clear();
          smallDifference = tournaments.at(i).getScore1() - tournaments.at(i).getScore2();
          storingGameInfo.push_back(tournaments.at(i).getTeam1()); // save team 1 name in index 0 
          storingGameInfo.push_back(tournaments.at(i).getTeam2()); // save team 2 name in index 1
          storingGameInfo.push_back(tournaments.at(i).getWinningTeam()); // save winning team name index 2
          storingGameNumber.push_back(tournaments.at(i).getGameNumber()); // saving game number index 0
        }
        else if ((tournaments.at(i).getScore2() - tournaments.at(i).getScore1() < smallDifference) && (tournaments.at(i).getScore2() - tournaments.at(i).getScore1() >= 0)){
          smallDifference = tournaments.at(i).getScore2() - tournaments.at(i).getScore1();
          storingGameInfo.clear();
          storingGameNumber.clear();
          storingGameInfo.push_back(tournaments.at(i).getTeam1()); // save team 1 in index 0 
          storingGameInfo.push_back(tournaments.at(i).getTeam2()); // save team 2 in index 1
          storingGameInfo.push_back(tournaments.at(i).getWinningTeam()); // save winning team index 2
          storingGameNumber.push_back(tournaments.at(i).getGameNumber()); // saving game number index 0
        }
      }
    }
  
    cout << "\nThe nail-biting game was: " << endl;
    cout << "Round " << roundNumber << ", " << "Game " << storingGameNumber[0] << ": " << storingGameInfo[0];
    cout << " vs " << storingGameInfo[1] << ". Winner: " << storingGameInfo[2] << endl;
    cout << "The difference was " << smallDifference << " points.\n" << endl;
  }

  else if(roundNumber == 7){

    bigDifference = 0;
    smallDifference = 500;
    cout << "Analyzing the overall tournament..." << endl;

    //Option 7: User wants shoo in game and nail biting game for all rounds.
  
    for (int i=0; i<tournaments.size(); i++){ // going through whole csv file
        if((tournaments.at(i).getScore1() - tournaments.at(i).getScore2()) > bigDifference){
          storingRoundNumber.clear();
          storingGameInfo.clear();
          storingGameNumber.clear();
          bigDifference = tournaments.at(i).getScore1() - tournaments.at(i).getScore2();
          storingGameInfo.push_back(tournaments.at(i).getTeam1()); // save team 1 name in index 0 
          storingGameInfo.push_back(tournaments.at(i).getTeam2()); // save team 2 name in index 1
          storingGameInfo.push_back(tournaments.at(i).getWinningTeam()); // save winning team name index 2
          storingGameNumber.push_back(tournaments.at(i).getGameNumber()); // saving game number index 0
          storingRoundNumber.push_back(tournaments.at(i).getRoundNumber());
        }
        else if ((tournaments.at(i).getScore2() - tournaments.at(i).getScore1()) > bigDifference){
          storingRoundNumber.clear();
          bigDifference = tournaments.at(i).getScore2() - tournaments.at(i).getScore1();
          storingGameInfo.clear();
          storingGameNumber.clear();
          storingGameInfo.push_back(tournaments.at(i).getTeam1()); // save team 1 in index 0 
          storingGameInfo.push_back(tournaments.at(i).getTeam2()); // save team 2 in index 1
          storingGameInfo.push_back(tournaments.at(i).getWinningTeam()); // save winning team index 2
          storingGameNumber.push_back(tournaments.at(i).getGameNumber()); // saving game number index 0
          storingRoundNumber.push_back(tournaments.at(i).getRoundNumber());
        }
      }
    cout << "\nThe shoo-in game was: " << endl;
    cout << "Round " << storingRoundNumber[0] << ", " << "Game " << storingGameNumber[0] << ": " << storingGameInfo[0];
    cout << " vs " << storingGameInfo[1] << ". Winner: " << storingGameInfo[2] << endl;
    cout << "The difference was " << bigDifference << " points." << endl;
  
  
      //  nail-biting game: the one with the smallest difference in scores
    for (int i=0; i<tournaments.size(); i++){ // going through whole csv file
        if(((tournaments.at(i).getScore1() - tournaments.at(i).getScore2()) < smallDifference) && ((tournaments.at(i).getScore1() - tournaments.at(i).getScore2()) >= 0)){
          storingRoundNumber.clear();
          storingGameInfo.clear();
          storingGameNumber.clear();
          smallDifference = tournaments.at(i).getScore1() - tournaments.at(i).getScore2();
          storingGameInfo.push_back(tournaments.at(i).getTeam1()); // save team 1 name in index 0 
          storingGameInfo.push_back(tournaments.at(i).getTeam2()); // save team 2 name in index 1
          storingGameInfo.push_back(tournaments.at(i).getWinningTeam()); // save winning team name index 2
          storingGameNumber.push_back(tournaments.at(i).getGameNumber()); // saving game number index 0
          storingRoundNumber.push_back(tournaments.at(i).getRoundNumber());
        }
        else if ((tournaments.at(i).getScore2() - tournaments.at(i).getScore1() < smallDifference) && (tournaments.at(i).getScore2() - tournaments.at(i).getScore1() >= 0)){
          storingRoundNumber.clear();
          smallDifference = tournaments.at(i).getScore2() - tournaments.at(i).getScore1();
          storingGameInfo.clear();
          storingGameNumber.clear();
          storingGameInfo.push_back(tournaments.at(i).getTeam1()); // save team 1 in index 0 
          storingGameInfo.push_back(tournaments.at(i).getTeam2()); // save team 2 in index 1
          storingGameInfo.push_back(tournaments.at(i).getWinningTeam()); // save winning team index 2
          storingGameNumber.push_back(tournaments.at(i).getGameNumber()); // saving game number index 0
          storingRoundNumber.push_back(tournaments.at(i).getRoundNumber());
        }
      }
  
    cout << "\nThe nail-biting game was: " << endl;
    cout << "Round " << storingRoundNumber[0] << ", " << "Game " << storingGameNumber[0] << ": " << storingGameInfo[0];
    cout << " vs " << storingGameInfo[1] << ". Winner: " << storingGameInfo[2] << endl;
    cout << "The difference was " << smallDifference << " points.\n" << endl;
  }
}

void compareUsersPredictionFile(vector <Tournament> &prediction, vector<string>actualWinners, vector<int>savingRoundNumbers){

  vector<string> predcitedWinners;
  vector<int> savingWinnerRoundNumbers;
  int multiplyingBy5 = 0;
  int addingThemTogether = 0;

  // running through the predicted fie and saving team names:
  for (int i=0; i<prediction.size(); i++){
    predcitedWinners.push_back(prediction.at(i).getWinningTeam());
    }

  //comparing the files to see which ones are guessed correctly and extracting those round numbers to later multiply by 5
  int correctlyGuessed=0;
  for(int i=0; i<prediction.size(); i++){
    if (actualWinners[i] == predcitedWinners[i]){
      savingWinnerRoundNumbers.push_back(savingRoundNumbers[i]);
      correctlyGuessed++;
    }
  }
  
  // using this loop we multiple each round that was guessed correctly and add them together 
  for(int i=0; i<savingWinnerRoundNumbers.size(); i++){
    multiplyingBy5 = 5 * savingWinnerRoundNumbers[i];
    addingThemTogether = addingThemTogether + multiplyingBy5;
    multiplyingBy5 = 0;
  }

  cout << "You correctly predicted the winner for " << correctlyGuessed << " games." << endl;
  cout << "This means that you have a score of " << addingThemTogether << "." << endl;

  if(addingThemTogether>=250){
    cout << "Great job! You could consider entering your predictions to win money!" << endl;
  }
  else{
    cout << "You may want to learn more about basketball to improve your predictions next " << endl;
    cout << "year." << endl;
  }
  
}

int main() {

  string usersChosenFile;
  int menu;
  vector <Tournament> tournaments;


  
  introducingTheProgram();
  cout << "Enter the name of the file with the data for the NCAA tournament: \n";
  usersChosenFile = takingFileFromTheUser();
  readingTheCSVFile(usersChosenFile, tournaments);


  do{
    showMenuOption();
    cin >> menu;
    if((menu>=1) && (menu<=6)){
      switch(menu){
      case 1:
        getOverallInformation(tournaments, usersChosenFile);
        break;
      case 2:
        pathToWinningTeamChampionship(tournaments);
        break;
      case 3:
        regionChampionsBasedOnRound(tournaments);
        break;
      case 4:
        bestUnderdog(tournaments);
        break;
      case 5:
        shooInAndNailBitingGames(tournaments);
        break;
      case 6:
        vector<string> actualWinners;
        vector<int> savingRoundNumbers;
        string passPredictionFile;
  
        // Using this loop we save the actual file's winning team names and round #'s' that the user will be comparing with.
        for (int i=0; i<tournaments.size(); i++){
          actualWinners.push_back(tournaments.at(i).getWinningTeam());
          savingRoundNumbers.push_back(tournaments.at(i).getRoundNumber());
        }

        vector<Tournament>prediction;
        cout << "Enter the name of the file with your predicted brackets: " << endl;
        passPredictionFile = takingFileFromTheUser();
        readingTheCSVFile(passPredictionFile, prediction);
        compareUsersPredictionFile(prediction, actualWinners, savingRoundNumbers);
        break;
      }
    }
    else if(menu > 7){
      cout << "Invalid value.  Please re-enter a value from the menu options below." << endl;
    }
  } while(menu != 7);
  cout << "Exiting program..." << endl;
  
}