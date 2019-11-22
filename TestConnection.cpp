#include "DatabaseConnector.h"
using namespace std;
using namespace pqxx;

void createTable(connection C, char* query);

int main(int argc, char* argv[]) {
  cout<<"START\n";
  system("sudo systemctl start postgresql.service");
  DatabaseConnector* test=new DatabaseConnector();
  test->mainMenu();
  return 0;
}
