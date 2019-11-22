#include <iostream>
#include <pqxx/pqxx>
#include<string>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace pqxx;

class DatabaseConnector{
private:
  struct beer;
  struct drinker;
  struct bar;
  struct like;
  struct sell;
  struct frequent;
  struct answer;
  vector<beer> beers;
  vector<drinker> drinkers;
  vector<bar> bars;
  vector<like> likes;
  vector<sell> sells;
  vector<frequent> frequents;

  connection* C;
  void initConnection(string host, string databasename, string user, string password);

  void inputQuery(string query);

  void populationSubMenu();
  void initTables();
  void readEntities();
  void printVectorOfTuples();
  void insertValueInDatabase();
  void insertBars();
  void insertDrinkers();
  void insertBeers();
  void insertLikes();
  void insertFrequents();
  void insertSells();
  void dropTablesSubMenu();
  void dropAllTables();
  void dropBars();
  void dropDrinkers();
  void dropBeers();
  void dropLikes();
  void dropFrequents();
  void dropSells();
  void selectSubMenu();
  result* askQuery();
  result* selectQuery(string query);
  void printSelect(result* collection);

  void seeQuestionOutpuSubMenu();
  void readAllDataFromDatabase();
  void printAnswerVector(vector<answer>* in);
  void setDistinct(vector<answer>* in);
  vector<answer>* computeFirstQuestion();
  vector<answer>* computeSecondQuestion();
  vector<answer>* computeThirdQuestion();
  vector<answer>* computeForthQuestion();
  vector<answer>* computeFifthQuestion();
  vector<answer>* computeSixthQuestion();
  vector<answer>* computeSeventhQuestion();
  vector<answer>* computeEighthQuestion();
  vector<answer>* computeNinthQuestion();
  vector<answer>* computeTenthQuestion();
  bool beerSoldInBar(string beer, string bar);

  void queryValidationSubMenu();
  void sortAnswer(vector<answer>* in);
  bool compareSortedAnswer(vector<answer>* first, vector<answer>* second);
  vector<answer>* fromResultToAnswer(result* collection);
  void checkFirstQuestion();
  void checkSecondQuestion();
  void checkThirdQuestion();
  void checkForthQuestion();
  void checkFifthQuestion();
  void checkSixthQuestion();
  void checkSeventhQuestion();
  void checkEighthQuestion();
  void checkNinthQuestion();
  void checkTenthQuestion();
public:
  DatabaseConnector(string host, string databasename, string user, string password);
  DatabaseConnector();
  void mainMenu();
};
