#include "DatabaseConnector.h"
using namespace std;
using namespace pqxx;

int removeBlanks(string* in){
  int dim=0;
  for(int i=0;i<in->size();i++){
    if(in->at(i)==32 && dim==0)
    dim=i;
  }
  return dim;
}

struct DatabaseConnector:: bar{
  string name;
  string addr;
  string license;
};

struct DatabaseConnector:: drinker{
  string name;
  string addr;
  string phone;
};

struct DatabaseConnector:: beer{
  string name;
  string manf;
};

struct DatabaseConnector:: like{
  string drinker;
  string beer;
};

struct DatabaseConnector:: sell{
  string bar;
  string beer;
  double price;
};

struct DatabaseConnector:: frequent{
  string drinker;
  string bar;
};

struct DatabaseConnector::answer{
  string first="";
  string second="";
};

DatabaseConnector:: DatabaseConnector(){
  cout<<"\033[1;34m\n";
  string user;
  string dbname;
  string password;
  string host;
  cout<<"Host:\n";
  cin>>host;
  cout<<"Database name\n";
  cin>>dbname;
  cout<<"User\n";
  cin>>user;
  password=getpass("Password:\n");
  initConnection(host, dbname, user, password);
  cout<<"\033[0m\n";
}

DatabaseConnector::DatabaseConnector(string host, string databasename, string user, string password){
  initConnection(host, databasename, user, password);
}

void DatabaseConnector::initConnection(string host, string databasename, string user, string password){
     string connectionString="host=";
     connectionString+=host;
     connectionString.append(" user=");
     connectionString+=user;
     connectionString.append(" dbname=");
     connectionString+=databasename;
     connectionString.append(" password=");
     connectionString+=password;
     try{
       C=new connection(connectionString.c_str());
      if (C->is_open())
          cout << "Opened database successfully: " << C->dbname() << endl;
      else{
        cerr << "Can't open database" << endl;
        exit(EXIT_FAILURE);
      }
    }
    catch (const std::exception &e) {
       cerr << e.what() << std::endl;
       exit(EXIT_FAILURE);
    }
}

void DatabaseConnector::mainMenu(){
  int i=0;
  while(i!=6){
    cout<<"\033[1;31m";
    cout<<"Select operation:\n";
    cout<<"[0]: init tables\n";
    cout<<"[1]: populate tables\n";
    cout<<"[2]: execute a SELECT query\n";
    cout<<"[3]: see output of a question\n";
    cout<<"[4]: check if the query is correct\n";
    cout<<"[5]: drop tables\n";
    cout<<"[6]: quit\n\n";
    cout<<"\033[0m";
    cin>>i;
    cout<<"\033[1;31m";
    switch (i) {
      case 0:
        cout<<endl;
        initTables();
      break;
      case 1:
        cout<<endl;
        populationSubMenu();
      break;
      case 2:
        cout<<endl;
        selectSubMenu();
      break;
      case 3:
        cout<<endl;
        seeQuestionOutpuSubMenu();
      break;
      case 4:
        queryValidationSubMenu();
      break;
      case 5:
        cout<<endl;
        dropTablesSubMenu();
      break;
      case 6:
        cout<<endl<<"Quitting...\n";
        C->disconnect();
      break;
      default:
        cout<<"\n Wrong option\n";
      break;
    }
  }
    cout<<"\033[0m\n";
}

void DatabaseConnector::populationSubMenu(){
  int i=0;
  readEntities();
  while(i!=2){
    cout<<"\033[1;33m";
    cout<<"[0]: See values to be inserted\n";
    cout<<"[1]: Insert values\n";
    cout<<"[2]: Return to main menu\n\n";
    cout<<"\033[0m";
    cin>>i;
    cout<<"\033[1;33m";
    switch (i) {
      case 0:
        printVectorOfTuples();
      break;
      case 1:
        cout<<endl;
        insertValueInDatabase();
      break;
      case 2:
        cout<<"\nReturning to main menu...\n";
      break;
      default:
        cout<<"\n Wrong option\n";
      break;
    }
    cout<<"\033[0m\n";
  }
}

void DatabaseConnector::dropTablesSubMenu(){
  int i=0;
  while(i!=7){
    cout<<"\033[1;33m";
    cout<<"[0]: Drop Bars\n";
    cout<<"[1]: Drop Beers\n";
    cout<<"[2]: Drop Drinkers\n";
    cout<<"[3]: Drop Sells\n";
    cout<<"[4]: Drop Likes\n";
    cout<<"[5]: Drop Frequents\n";
    cout<<"[6]: Drop All\n";
    cout<<"[7]: Return to main menu\n\n";
    cout<<"\033[0m";
    cin>>i;
    cout<<"\033[1;33m";
    switch (i) {
      case 0:
        cout<<endl;
        dropBars();
      break;
      case 1:
        cout<<endl;
        dropBeers();
      break;
      case 2:
        cout<<endl;
        dropDrinkers();
      break;
      case 3:
        cout<<endl;
        dropSells();
      break;
      case 4:
        cout<<endl;
        dropLikes();
      break;
      case 5:
        cout<<endl;
        dropFrequents();
      break;
      case 6:
        cout<<endl;
        dropAllTables();
      break;
      case 47:
        cout<<"\nReturning to main menu...\n";
      break;
      default:
        cout<<"\n Wrong option\n";
      break;
    }
    cout<<"\033[0m\n";
  }
}

void DatabaseConnector::printVectorOfTuples(){
  cout<<"\033[1;35m";
  cout<<endl<<"Bars:\n";
  for(int i=0;i<bars.size();i++){
    cout<<setw(20)<<left;
    cout<<"\t"<<i<<":"<<bars.at(i).name<<"\t"<<bars.at(i).addr<<"\t"<<bars.at(i).license<<"\n";
  }
  cout<<endl<<"Drinkers:\n";
  for(int i=0;i<drinkers.size();i++){
    cout<<setw(20)<<left;
    cout<<"\t"<<i<<":"<<drinkers.at(i).name<<"\t"<<drinkers.at(i).addr<<"\t"<<drinkers.at(i).phone<<"\n";
  }
  cout<<endl<<"Beers:\n";
  for(int i=0;i<beers.size();i++){
    cout<<setw(20)<<left;
    cout<<"\t"<<i<<":"<<beers.at(i).name<<"\t"<<beers.at(i).manf<<"\n";
  }
  cout<<endl<<"Sells:\n";
  for(int i=0;i<sells.size();i++){
    cout<<setw(20)<<left;
    cout<<"\t"<<i<<":"<<sells.at(i).bar<<"\t"<<sells.at(i).beer<<"\t"<<sells.at(i).price<<"\n";
  }
  cout<<endl<<"Likes:\n";
  for(int i=0;i<likes.size();i++){
    cout<<setw(20)<<left;
    cout<<"\t"<<i<<":"<<likes.at(i).drinker<<"\t"<<likes.at(i).beer<<"\n";
  }
  cout<<endl<<"Frequents:\n";
  for(int i=0;i<frequents.size();i++){
    cout<<setw(20)<<left;
    cout<<"\t"<<i<<":"<<frequents.at(i).drinker<<"\t"<<frequents.at(i).bar<<"\n";
  }
  cout<<"\033[0m\n";
}

void DatabaseConnector::inputQuery(string query){
  cout<<"\033[1;32m";
  cout<<"Executing:\n"<<query<<endl;
  try{
    work W(*C);
    W.exec(query.c_str());
    W.commit();
    cout << "Query successful" << endl;
  }
  catch (const std::exception &e) {
    cout<<"\033[1;35m";
    cerr << e.what() << std::endl;
  }
  cout<<"\033[0m\n";
}

void DatabaseConnector::initTables(){
  inputQuery("CREATE TABLE IF NOT EXISTS \"Beers\" (name char(20) PRIMARY KEY, manf char(20));");
  inputQuery("CREATE TABLE IF NOT EXISTS \"Bars\" (name char(20) PRIMARY KEY, addr char(20), license char(20));");
  inputQuery("CREATE TABLE IF NOT EXISTS \"Drinkers\" (name char(20) PRIMARY KEY, addr char(20), phone char(20));");
  inputQuery("CREATE TABLE IF NOT EXISTS \"Likes\" (drinker char(20) REFERENCES \"Drinkers\"(name), beer char(20) REFERENCES \"Beers\"(name), PRIMARY KEY(drinker, beer));");
  inputQuery("CREATE TABLE IF NOT EXISTS \"Frequents\" (drinker char(20) REFERENCES \"Drinkers\"(name), bar char(20) REFERENCES \"Bars\"(name), PRIMARY KEY(drinker, bar));");
  inputQuery("CREATE TABLE IF NOT EXISTS \"Sells\"(bar char(20) REFERENCES  \"Bars\"(name), beer char(20) REFERENCES \"Beers\"(name), PRIMARY KEY(bar, beer), price real);");
}

void DatabaseConnector::readEntities(){
  drinkers.clear();
  bars.clear();
  beers.clear();
  likes.clear();
  frequents.clear();
  sells.clear();
  ifstream in("Tables.txt");
  string input;
  while(in>>input){
    if(input=="Drinkers>"){
      in>>input;
      while(input!="STOP"){
        string name;
        string addr;
        string phone;
        in>>name;
        in>>addr;
        in>>phone;
        drinker temp={name, addr, phone};
        drinkers.push_back(temp);
        in>>input;
      }
    }
    else if(input=="Bars>"){
      in>>input;
      while(input!="STOP"){
        string name;
        string addr;
        string license;
        in>>name;
        in>>addr;
        in>>license;
        bar temp={name, addr, license};
        bars.push_back(temp);
        in>>input;
      }
    }
    else if(input=="Beers>"){
      in>>input;
      while(input!="STOP"){
        string name;
        string manf;
        in>>name;
        in>>manf;
        beer temp={name, manf};
        beers.push_back(temp);
        in>>input;
      }
    }
    else if(input=="Likes>"){
      in>>input;
      while(input!="STOP"){
        string drinker;
        string beer;
        in>>drinker;
        in>>beer;
        like temp={drinker, beer};
        likes.push_back(temp);
        in>>input;
      }
    }
    else if(input=="Frequents>"){
      in>>input;
      while(input!="STOP"){
        string drinker;
        string bar;
        in>>drinker;
        in>>bar;
        frequent temp={drinker, bar};
        frequents.push_back(temp);
        in>>input;
      }
    }
    else if(input=="Sells>"){
      in>>input;
      while(input!="STOP"){
        string bar;
        string beer;
        double price;
        in>>bar;
        in>>beer;
        in>>price;
        sell temp={bar, beer, price};
        sells.push_back(temp);
        in>>input;
      }
    }
  }
}

void DatabaseConnector::insertValueInDatabase(){
  insertBars();
  insertBeers();
  insertDrinkers();
  insertLikes();
  insertFrequents();
  insertSells();
}

void DatabaseConnector::insertBars(){
  string queryStart="INSERT INTO \"Bars\" VALUES('";
  for(int i=0;i<bars.size();i++){
    string query="";
    query+=queryStart;
    query+=bars.at(i).name;
    query+="', '";
    query+=bars.at(i).addr;
    query+="', '";
    query+=bars.at(i).license;
    query+="');";
    inputQuery(query);
  }
}

void DatabaseConnector::insertDrinkers(){
  string queryStart="INSERT INTO \"Drinkers\" VALUES('";
  for(int i=0;i<drinkers.size();i++){
    string query="";
    query+=queryStart;
    query+=drinkers.at(i).name;
    query+="', '";
    query+=drinkers.at(i).addr;
    query+="', '";
    query+=drinkers.at(i).phone;
    query+="');";
    inputQuery(query);
  }
}

void DatabaseConnector::insertBeers(){
  string queryStart="INSERT INTO \"Beers\" VALUES('";
  for(int i=0;i<beers.size();i++){
    string query="";
    query+=queryStart;
    query+=beers.at(i).name;
    query+="', '";
    query+=beers.at(i).manf;
    query+="');";
    inputQuery(query);
  }
}

void DatabaseConnector::insertLikes(){
  string queryStart="INSERT INTO \"Likes\" VALUES('";
  for(int i=0;i<likes.size();i++){
    string query="";
    query+=queryStart;
    query+=likes.at(i).drinker;
    query+="', '";
    query+=likes.at(i).beer;
    query+="');";
    inputQuery(query);
  }
}

void DatabaseConnector::insertFrequents(){
  string queryStart="INSERT INTO \"Frequents\" VALUES('";
  for(int i=0;i<frequents.size();i++){
    string query="";
    query+=queryStart;
    query+=frequents.at(i).drinker;
    query+="', '";
    query+=frequents.at(i).bar;
    query+="');";
    inputQuery(query);
  }
}

void DatabaseConnector::insertSells(){
  string queryStart="INSERT INTO \"Sells\" VALUES('";
  for(int i=0;i<sells.size();i++){
    string query="";
    query+=queryStart;
    query+=sells.at(i).bar;
    query+="', '";
    query+=sells.at(i).beer;
    query+="', '";
    query+=to_string(sells.at(i).price);
    query+="');";
    inputQuery(query);
  }
}

void DatabaseConnector::dropAllTables(){
  dropLikes();
  dropSells();
  dropFrequents();
  dropBars();
  dropBeers();
  dropDrinkers();
}

void DatabaseConnector::dropBars(){
  inputQuery("DROP TABLE \"Bars\"");
}

void DatabaseConnector::dropDrinkers(){
  inputQuery("DROP TABLE \"Drinkers\"");
}

void DatabaseConnector::dropBeers(){
  inputQuery("DROP TABLE \"Beers\"");
}

void DatabaseConnector::dropLikes(){
  inputQuery("DROP TABLE \"Likes\"");
}

void DatabaseConnector::dropFrequents(){
  inputQuery("DROP TABLE \"Frequents\"");
}

void DatabaseConnector::dropSells(){
  inputQuery("DROP TABLE \"Sells\"");
}

result* DatabaseConnector::selectQuery(string query){
result* res;
  try {
    nontransaction N(*C);
    res= new result( N.exec(query));
    cout << "Operation done successfully" << endl;
  }
  catch (const std::exception &e) {
    cout<<"\033[1;35m";
    cerr << e.what() << std::endl;
  }
  return res;
}

result* DatabaseConnector::askQuery(){
  cout<<"\033[1;33m";
  cout<<"Select type query:\n\n";
  cout<<"\033[0m";
  string query=" ";
  string temp;
  while(query.size()<3 || query.at(query.size()-2)!=';'){
    cin>>temp;
    query+=temp;
    query+=" ";
  }
  query.resize(query.size()-1);
  result* temp1=selectQuery(query);
  if(temp1!=nullptr)
    printSelect(temp1);
  return temp1;
}

void DatabaseConnector::printSelect(result* collection){
  cout<<endl;
  cout<<setw(5)<<left;
  cout<<"\033[1;36m";
  const int num_rows = collection->size();
  cout<<setw(5)<<"\t";
  for(int i=0;i<collection->columns();i++){
    cout<<setw(20)<<left;
    cout<<left<<collection->column_name(i)<<'\t';
  }
  cout<<endl;
  cout<<endl;

  cout<<"\033[1;39m";
  for (int rownum=0; rownum < num_rows; ++rownum){
    const row row = (*collection)[rownum];
    const int num_cols = row.size();
    cout<<setw(5)<<left;
    cout<<rownum<<"\t";
    for (int colnum=0; colnum < num_cols; ++colnum){
      const pqxx::field field = row[colnum];
      std::cout << field.c_str() << '\t';
    }
    std::cout << std::endl;
  }
  cout<<"\033[0m\n";

}

void DatabaseConnector::selectSubMenu(){
  int i=0;
  while(i!=7){
    cout<<"\033[1;33m";
    cout<<"[0]: See Bars\n";
    cout<<"[1]: See Beers\n";
    cout<<"[2]: See Drinkers\n";
    cout<<"[3]: See Likes\n";
    cout<<"[4]: See Frequents\n";
    cout<<"[5]: See Sells\n";
    cout<<"[6]: Custom Select\n";
    cout<<"[7]: Return to main menu\n\n";
    cout<<"\033[0m";
    cin>>i;
    cout<<"\033[1;33m";
    switch (i) {
      case 0:
        cout<<endl;
        printSelect(selectQuery("SELECT * FROM \"Bars\""));
      break;
      case 1:
        cout<<endl;
        printSelect(selectQuery("SELECT * FROM \"Beers\""));
      break;
      case 2:
        cout<<endl;
        printSelect(selectQuery("SELECT * FROM \"Drinkers\""));
      break;
      case 3:
        cout<<endl;
        printSelect(selectQuery("SELECT * FROM \"Likes\""));
      break;
      case 4:
        cout<<endl;
        printSelect(selectQuery("SELECT * FROM \"Frequents\""));
      break;
      case 5:
        cout<<endl;
        printSelect(selectQuery("SELECT * FROM \"Sells\""));
      break;
      case 6:
        cout<<endl;
        askQuery();
      break;
      case 7:
        cout<<"\nReturning to main menu...\n";
      break;
      default:
        cout<<"\n Wrong option\n";
      break;
    }
    cout<<"\033[0m\n";
  }
}

void DatabaseConnector::seeQuestionOutpuSubMenu(){
  readAllDataFromDatabase();
  int i=-1;
  while(i!=0){
    cout<<"\033[1;33m";
    cout<<"Select operation:\n";
    cout<<"[0]: return to main menu\n\n";
    cout<<"[1]: see question 1 output\n";
    cout<<"[2]: see question 2 output\n";
    cout<<"[3]: see question 3 output\n";
    cout<<"[4]: see question 4 output\n";
    cout<<"[5]: see question 5 output\n";
    cout<<"[6]: see question 6 output\n";
    cout<<"[7]: see question 7 output\n";
    cout<<"[8]: see question 8 output\n";
    cout<<"[9]: see question 9 output\n";
    cout<<"[10]: see question 10 output\n";
    cout<<"\033[0m\n";
    cin>>i;
    cout<<"\033[1;31m";
    switch (i) {
      case 0:
        cout<<"\nReturning to main menu...\n";
      break;
      case 1:
        printAnswerVector(computeFirstQuestion());
      break;
      case 2:
        printAnswerVector(computeSecondQuestion());
      break;
      case 3:
        printAnswerVector(computeThirdQuestion());
      break;
      case 4:
        printAnswerVector(computeForthQuestion());
      break;
      case 5:
        printAnswerVector(computeFifthQuestion());
      break;
      case 6:
        printAnswerVector(computeSixthQuestion());
      break;
      case 7:
        printAnswerVector(computeSeventhQuestion());
      break;
      case 8:
        printAnswerVector(computeEighthQuestion());
      break;
      case 9:
        printAnswerVector(computeNinthQuestion());
      break;
      case 10:
        printAnswerVector(computeTenthQuestion());
      break;
      default:
        cout<<"\n Wrong option\n";
      break;
    }
  }
    cout<<"\033[0m\n";
}

void DatabaseConnector::readAllDataFromDatabase(){
  drinkers.clear();
  bars.clear();
  beers.clear();
  likes.clear();
  sells.clear();
  frequents.clear();
  result* drinkersTable=selectQuery("SELECT * FROM \"Drinkers\"");
  result* barsTable=selectQuery("SELECT * FROM \"Bars\"");
  result* beersTable=selectQuery("SELECT * FROM \"Beers\"");
  result* likesTable=selectQuery("SELECT * FROM \"Likes\"");
  result* sellsTable=selectQuery("SELECT * FROM \"Sells\"");
  result* frequentsTable=selectQuery("SELECT * FROM \"Frequents\"");
  printSelect(drinkersTable);
  printSelect(barsTable);
  printSelect(beersTable);
  printSelect(likesTable);
  printSelect(sellsTable);
  printSelect(frequentsTable);
  int num_rows = drinkersTable->size();
  for (int rownum=0; rownum < num_rows; ++rownum){
    const row row = (*drinkersTable)[rownum];
    const int num_cols = row.size();
    drinker temp;
    for (int colnum=0; colnum < num_cols; ++colnum){
      const pqxx::field field = row[colnum];
      string test=field.c_str();
      test.resize(removeBlanks(&test));
      if(colnum==0){
        temp.name=test.c_str();
      }
      else if(colnum==1){
        temp.addr=test.c_str();
      }
      else if(colnum==2){
        temp.phone=test.c_str();
      }
    }
    drinkers.push_back(temp);
  }
  num_rows = barsTable->size();
  for (int rownum=0; rownum < num_rows; ++rownum){
    const row row = (*barsTable)[rownum];
    const int num_cols = row.size();
    bar temp;
    for (int colnum=0; colnum < num_cols; ++colnum){
      const pqxx::field field = row[colnum];
      string test=field.c_str();
      test.resize(removeBlanks(&test));
      if(colnum==0){
        temp.name=test.c_str();
      }
      else if(colnum==1){
        temp.addr=test.c_str();
      }
      else if(colnum==2){
        temp.license=test.c_str();
      }
    }
    bars.push_back(temp);
  }
  num_rows = beersTable->size();
  for (int rownum=0; rownum < num_rows; ++rownum){
    const row row = (*beersTable)[rownum];
    const int num_cols = row.size();
    beer temp;
    for (int colnum=0; colnum < num_cols; ++colnum){
      const pqxx::field field = row[colnum];
      string test=field.c_str();
      test.resize(removeBlanks(&test));
      if(colnum==0)
        temp.name=test.c_str();
      else if(colnum==1)
        temp.manf=test.c_str();
    }
    beers.push_back(temp);
  }

  num_rows = likesTable->size();
  for (int rownum=0; rownum < num_rows; ++rownum){
    const row row = (*likesTable)[rownum];
    const int num_cols = row.size();
    like temp;
    for (int colnum=0; colnum < num_cols; ++colnum){
      const pqxx::field field = row[colnum];
      string test=field.c_str();
      test.resize(removeBlanks(&test));
      if(colnum==0)
        temp.drinker=test.c_str();
      else if(colnum==1)
        temp.beer=test.c_str();
    }
    likes.push_back(temp);
  }

  num_rows = frequentsTable->size();
  for (int rownum=0; rownum < num_rows; ++rownum){
    const row row = (*frequentsTable)[rownum];
    const int num_cols = row.size();
    frequent temp;
    for (int colnum=0; colnum < num_cols; ++colnum){
      const pqxx::field field = row[colnum];
      string test=field.c_str();
      test.resize(removeBlanks(&test));
      if(colnum==0)
        temp.drinker=test.c_str();
      else if(colnum==1)
        temp.bar=test.c_str();
    }
    frequents.push_back(temp);
  }

  num_rows = sellsTable->size();
  for (int rownum=0; rownum < num_rows; ++rownum){
    const row row = (*sellsTable)[rownum];
    const int num_cols = row.size();
    sell temp;
    for (int colnum=0; colnum < num_cols; ++colnum){
      const pqxx::field field = row[colnum];
      string test=field.c_str();
      test.resize(removeBlanks(&test));
      if(colnum==0)
        temp.bar=test.c_str();
      else if(colnum==1)
        temp.beer=test.c_str();
      else if(colnum==2){
        temp.price=atof(field.c_str());
      }
    }
    sells.push_back(temp);
  }
}

void DatabaseConnector::printAnswerVector(vector<answer>* in){
  cout<<"\033[1;38m\n";
  for(int i=0;i<in->size();i++){
    cout<<in->at(i).first<<"\t"<<in->at(i).second<<endl;
  }
  cout<<"\033[0m\n";
}

void DatabaseConnector::setDistinct(vector<answer>* in){
  for(int i=0;i<in->size();i++){
    for(int j=0;j<in->size() && i<in->size();j++){
      if(i!=j && in->at(j).first==in->at(i).first && in->at(j).second==in->at(i).second)
        in->erase(in->begin()+i);
    }
  }

}

vector<DatabaseConnector::answer>* DatabaseConnector::computeFirstQuestion(){
  vector<answer>* res=new vector<answer>;
  for(int i=0;i<beers.size();i++){
    if(beers.at(i).manf=="Anheuser-Busch"){
      string name=beers.at(i).name;
      answer temp;
      temp.first=name;
      res->push_back(temp);
    }
  }
  return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::computeSecondQuestion(){
  vector<answer>* res=new vector<answer>;
  for(int i=0;i<sells.size();i++){
    for(int j=0;j<sells.size();j++){
      if(i!=j && sells.at(i).bar==sells.at(j).bar && sells.at(i).beer=="Bud" && sells.at(j).beer=="Miller" && sells.at(i).price==sells.at(j).price){
        answer temp;
        temp.first=sells.at(i).bar;
        res->push_back(temp);
      }
    }
  }
  return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::computeThirdQuestion(){
  vector<answer>* res=new vector<answer>;
  vector<string> temp;
  for(int i=0;i<likes.size();i++){
    if(likes.at(i).drinker=="Fred")
      temp.push_back(likes.at(i).beer);
  }
  for(int i=0;i<temp.size();i++){
    for(int j=0;j<beers.size();j++){
        if(temp.at(i)==beers.at(j).name){
          answer temp1;
          temp1.first=beers.at(j).name;
          temp1.second=beers.at(j).manf;
          res->push_back(temp1);
        }
    }
  }
  return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::computeForthQuestion(){
  vector<answer>* res=new vector<answer>;
  for(int i=0;i<beers.size();i++){
    bool unique=true;
    for(int j=0;j<beers.size();j++){
      if(i!=j && beers.at(i).manf==beers.at(j).manf)
      unique=false;
    }
    if(unique){
      answer temp;
      temp.first=beers.at(i).name;
      res->push_back(temp);
    }
  }
  return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::computeFifthQuestion(){
  vector<answer>* res=new vector<answer>;
  double max=0;
  for(int i=0;i<sells.size();i++){
    if(sells.at(i).price>max)
      max=sells.at(i).price;
  }
  for(int i=0;i<sells.size();i++){
    if(sells.at(i).price==max){
      answer temp;
      temp.first=sells.at(i).beer;
      res->push_back(temp);
    }
  }
  return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::computeSixthQuestion(){
  vector<answer>* res=new vector<answer>;
  for(int i=0;i<likes.size();i++){
    for(int j=0;j<sells.size();j++){
      for(int z=0;z<frequents.size();z++){
        if(likes.at(i).drinker==frequents.at(z).drinker && likes.at(i).beer==sells.at(j).beer && frequents.at(z).bar==sells.at(j).bar){
          answer temp;
          temp.first=likes.at(i).drinker;
          temp.second=likes.at(i).beer;
          res->push_back(temp);
        }
      }
    }
  }
  setDistinct(res);
  return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::computeSeventhQuestion(){
  vector<answer>* res=new vector<answer>;
  double max=0;
  for(int i=0;i<sells.size();i++){
    answer temp;
    temp.first=sells.at(i).beer;
    temp.second=to_string(sells.at(i).price);
    res->push_back(temp);
  }
  setDistinct(res);
  return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::computeEighthQuestion(){
    vector<answer>* res=new vector<answer>;
    for(int i=0;i<likes.size();i++){
      if(likes.at(i).drinker=="Joe"){
        for(int j=0;j<sells.size();j++){
          if(likes.at(i).beer==sells.at(j).beer){
            answer temp;
            temp.first=sells.at(j).bar;
            res->push_back(temp);
          }
        }
      }
    }
    setDistinct(res);
    return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::computeNinthQuestion(){
  vector<answer>* res=new vector<answer>;
  for(int i=0;i<likes.size();i++){
    for(int j=0;j<sells.size();j++){
      for(int z=0;z<frequents.size();z++){
        if(likes.at(i).drinker==frequents.at(z).drinker && likes.at(i).beer==sells.at(j).beer && frequents.at(z).bar==sells.at(j).bar){
          answer temp;
          temp.first=likes.at(i).drinker;
          res->push_back(temp);
        }
      }
    }
  }
  setDistinct(res);
  return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::computeTenthQuestion(){
  vector<answer>* res=new vector<answer>;
  for(int i=0;i<drinkers.size();i++){
    string drinkerTemp=drinkers.at(i).name;
    vector<string> likedBeers;
    for(int j=0;j<likes.size();j++){
      if(likes.at(j).drinker==drinkerTemp)
        likedBeers.push_back(likes.at(j).beer);
    }
    vector<string> frequentedBars;
    for(int j=0;j<frequents.size();j++){
      if(frequents.at(j).drinker==drinkerTemp)
        frequentedBars.push_back(frequents.at(j).bar);
    }
    for(int j=0;j<frequentedBars.size();j++){
      for(int z=0;z<likedBeers.size();z++){
        if(beerSoldInBar(likedBeers.at(z), frequentedBars.at(j))){
          frequentedBars.erase(frequentedBars.begin()+j);
          j--;
          break;
        }
      }
    }
    if(frequentedBars.empty()){
      answer temp;
      temp.first=drinkerTemp;
      res->push_back(temp);
    }
  }
  setDistinct(res);
  return res;

}

bool DatabaseConnector::beerSoldInBar(string beer, string bar){
  bool res=false;
  for(int i=0;i<sells.size();i++)
    if(sells.at(i).bar==bar && sells.at(i).beer==beer)
      res=true;
  return res;
}

void DatabaseConnector::queryValidationSubMenu(){
  readAllDataFromDatabase();
  int i=-1;
  while(i!=0){
    cout<<"\033[1;33m";
    cout<<"Select operation:\n";
    cout<<"[0]: return to main menu\n\n";
    cout<<"[1]: check for question 1\n";
    cout<<"[2]: check for question 2\n";
    cout<<"[3]: check for question 3\n";
    cout<<"[4]: check for question 4\n";
    cout<<"[5]: check for question 5\n";
    cout<<"[6]: check for question 6\n";
    cout<<"[7]: check for question 7\n";
    cout<<"[8]: check for question 8\n";
    cout<<"[9]: check for question 9\n";
    cout<<"[10]: check for question 10\n";
    cout<<"\033[0m\n";
    cin>>i;
    cout<<"\033[1;31m";
    switch (i) {
      case 0:
        cout<<"\nReturning to main menu...\n";
      break;
      case 1:
        checkFirstQuestion();
      break;
      case 2:
        checkSecondQuestion();
      break;
      case 3:
        checkThirdQuestion();
      break;
      case 4:
        checkForthQuestion();
      break;
      case 5:
        checkFifthQuestion();
      break;
      case 6:
        checkSixthQuestion();
      break;
      case 7:
        checkSeventhQuestion();
      break;
      case 8:
        checkEighthQuestion();
      break;
      case 9:
        checkNinthQuestion();
      break;
      case 10:
        checkTenthQuestion();
      break;
      default:
        cout<<"\n Wrong option\n";
      break;
    }
  }
    cout<<"\033[0m\n";
}

void DatabaseConnector::checkFirstQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeFirstQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::checkSecondQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeSecondQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::checkThirdQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeThirdQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::checkForthQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeForthQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::checkFifthQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeFifthQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::checkSixthQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeSixthQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::checkSeventhQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeSeventhQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::checkEighthQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeEighthQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::checkNinthQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeNinthQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::checkTenthQuestion(){
  result* userIn=askQuery();
  vector<answer>* realResult=computeTenthQuestion();
  vector<answer>* userResult=fromResultToAnswer(userIn);
  sortAnswer(realResult);
  sortAnswer(userResult);
  cout<<"Yuor result:\n\n";
  printAnswerVector(userResult);
  cout<<endl<<"You were supposed to get:\n\n";
  printAnswerVector(realResult);
  if(compareSortedAnswer(realResult, userResult))
    cout<<"\nYou got the correct answer\n\n";
  else
    cout<<"\nYou got the wrong answer\n\n";
}

void DatabaseConnector::sortAnswer(vector<answer>* in){
  bool scambio=true;
  while(scambio){
    scambio=false;
    for(int i=0;i<in->size()-1;i++){
      if(in->at(i).first>in->at(i+1).first){
        swap(in->at(i), in->at(i+1));
        scambio=true;
      }
    }
  }
}

bool DatabaseConnector::compareSortedAnswer(vector<answer>* first, vector<answer>* second){
  bool res=true;
  if(first->size()!=second->size())
    return false;
  for(int i=0;i<first->size();i++){
    if(first->at(i).first!=second->at(i).first || first->at(i).second!=second->at(i).second)
      res=false;
  }
  return res;
}

vector<DatabaseConnector::answer>* DatabaseConnector::fromResultToAnswer(result* collection){
  vector<answer>* res=new vector<answer>;
  const int num_rows = collection->size();
  for (int rownum=0; rownum < num_rows; ++rownum){
    const row row = (*collection)[rownum];
    const int num_cols = row.size();
    if(num_cols>2){
      cerr<<"Wrong number of columns\n";
      return nullptr;
    }
    answer temp;
    for (int colnum=0; colnum < num_cols; ++colnum){
      const pqxx::field field = row[colnum];
      string test=field.c_str();
      test.resize(removeBlanks(&test));
      if(colnum==0){
        temp.first=test.c_str();
      }
      else if(colnum==1){
        temp.second=test.c_str();
      }
      }
      res->push_back(temp);
    }
    return res;

}
