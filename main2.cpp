#include<unordered_map>
#include<iostream>
#include<string>
#include<fstream>


using namespace std;

struct Writer{
    string name;
    int count;
};


class WriterDB{
    private:
    struct Writer_data{
        int name_count;

        // A sorted tree that stores the map adresses for the
        // Pseudonyms of the writer.

        vector<int> writer_ids;
    };

    unordered_map<int,string> Writer_names;

    //Hashmap  key: Writers name ;value: struct Writer_data

    unordered_map<string,Writer_data> Writer_list;


    public:

    // Find a writer by id
    // Return name of writer from the id
    // Return empty string if failed
    // Should be O(log n)

    string lookup_writer(int id){
        auto it = Writer_names.find(id);
        if(it != Writer_names.end()){
            return Writer_names[id];
        }else{
            return "";
        }
    }

    // Return true if such writer exists
    // False otherwise
    bool blookup_writer(int id){
        auto it = Writer_names.find(id);
        if(it != Writer_names.end()){
            return true;
        }else{
            return false;
        }
    }

    // Insert writer
    // Return true if succesful
    // Return false if fail

    bool insert_writer(string wname,int id){

        auto it = Writer_names.find(id);

        //If someone has this id
        if(it != Writer_names.end()){
            //If this is ours then all is good
            if(it->second == wname){
                return true;
            }else{
                return false;
            }
        }
        // Check whether such int id already exists for this writer.


        //Noone has this id. Lets make it ours

        Writer_names[id] = wname;
        Writer_list[wname].writer_ids.push_back(id);

        return true;
    }


    // Delete a writer by id
    // Return true if succesful
    // Return false if not found or other fail.

    bool delete_writer(int id){
        // First we go trough all iterators for this man or womanman and
        // erase all elements in writer_names using the itrators.

        // lets get the his name from the writer names first to access the hashmap.

        string wname = lookup_writer(id);
        if(wname.empty()) return false;

        for (auto it = Writer_list[wname].writer_ids.begin(); it != Writer_list[wname].writer_ids.end(); ++it) {
            Writer_names.erase(*it);
        }

        //Once all traces of this pleb in Writer_names is erased. Erase the entry in Writer_list
        Writer_list.erase(wname);

        return true;
    }

    bool can_insert(string wname,int id){
        if(Writer_list[wname].writer_ids.size() >= 50) return false;

        auto it = Writer_names.find(id);

        //If someone has this id
        if(it != Writer_names.end()){
            //If this is ours then all is good
            if(it->second == wname){
                return true;
            }else{
                return false;
            }
        }
        return true;
    }

};




int solve(string filepath, string outfilepath){
    ifstream inFile(filepath);
    ofstream outFile(outfilepath);

    WriterDB writer_database;

    if(!inFile.is_open()){
        cerr<<"Error opening file"<<endl;
        cerr<<filepath;
        return -1;
    }

    char operation;
    string sbuffer;
    int ibuffer;
    int count;

    int current_ids[50];


    while (!inFile.eof()) {
        inFile >> operation;
        if(inFile.eof()){
            return 0;
        }
        if (operation == 'I') {
            inFile >> sbuffer;
            inFile >> count;
            bool flag = true;
            for (int i = 0; i < count; i++) {
                inFile >> ibuffer;
                current_ids[i] = ibuffer;
                flag = writer_database.can_insert(sbuffer, ibuffer);
            }
            if (!flag) {
                outFile << "no\n";
            } else {
                for (int i = 0; i < count; i++) {
                    writer_database.insert_writer(sbuffer, current_ids[i]);
                }
            }
            outFile << (flag ? "ok\n" : "");
        } else if (operation == 'L') {
            inFile >> ibuffer;
            string lookup;
            lookup = writer_database.lookup_writer(ibuffer);
            if (lookup.empty()) {
                outFile << "no\n";
            } else {
                outFile << lookup << endl;
            }
        } else if (operation == 'D') {
            inFile >> ibuffer;
            if(writer_database.blookup_writer(ibuffer)){
                writer_database.delete_writer(ibuffer);
                outFile << "ok\n";
            }else{
                outFile << "no\n";
            }
        }
    }



    return 0;
}


int main(){
    solve("tests/reviewers.i1","myresults/output.o1");
    solve("tests/reviewers.i2","myresults/output.o2");
    solve("tests/reviewers.i3","myresults/output.o3");
    solve("tests/reviewers.i4","myresults/output.o4");
    solve("tests/reviewers.i5","myresults/output.o5");
    solve("tests/reviewers.i6","myresults/output.o6");
    solve("tests/reviewers.i7","myresults/output.o7");
    solve("tests/reviewers.i8","myresults/output.o8");
    solve("tests/reviewers.i9","myresults/output.o9");

}