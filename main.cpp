#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

class Import {
    public:
      virtual string doOperation(string type) = 0;
};

class ImportTXT:public Import {
    public:
      string doOperation(string type) {
        return "This is a .TXT file.";
      }
};
class ImportJSON:public Import {
    public:
      string doOperation(string type) {
        return "This is a .JSON file.";
      }
};
class ImportXML:public Import {
   public:
      string doOperation(string type) {
        return "This is a .XML file.";
      }
};
class ImportCSV:public Import {
   public:
      string doOperation(string type) {
        return "This is a .CSV file.";
      }
};

class Context {
  private:
    Import *ImportStrategy;

  public:
    Context(Import *new_strategy){
      ImportStrategy = new_strategy;
    }
   
    void changeStrategy(Import *new_strategy){
      ImportStrategy = new_strategy;
    }

    string executeStrategy(string type){
      return ImportStrategy->doOperation(type);
   }
};

class FileAdapter : public Import {

  public:
    string input;
    FileAdapter(string impinput) {
      input = impinput;
    }
    string doOperation(string input) {

        if (input.compare("TXT") == 0 || 
        input.compare("txt") == 0) {
        ImportTXT imp;
        Context context(&imp);
        return context.executeStrategy(input);

      } else if (input.compare("JSON") == 0 || 
        input.compare("json")== 0) {
        ImportJSON imp;
        Context context(&imp);
        return context.executeStrategy(input);

      } else if (input.compare("XML") == 0 ||
        input.compare("xml") == 0) {
        ImportXML imp;
        Context context(&imp);
        return context.executeStrategy(input);

      } else if (input.compare("CSV") == 0 || 
        input.compare("csv") == 0) {
        ImportCSV imp;
        Context context(&imp);
        return context.executeStrategy(input);

      } else {
        return "You entered an unsupported file type."; 
      }
    }
};

int main() {

  cout << "Give me a file path. (This is a command)" << endl;
  string input;
  vector<string> deliver;
  cin >> input;
  split(deliver, input, boost::is_any_of("."));

  FileAdapter filAdap(deliver[1]);
  cout << "You entered: " + deliver[1] << endl;
  cout << filAdap.doOperation(deliver[1]) << endl;
  
  return 0; 
}
