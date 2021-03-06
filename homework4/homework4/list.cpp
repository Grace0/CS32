
void listAll(const File* f, string path)  // two-parameter overload
{
    //Base case: we've hit a PlanFile
    if (f->files() == nullptr) {
        cout << path + "/" + f->name() << endl; //base case
        return;
    }
    
    //Other base case: we've hit an empty Directory
    if (f->files()->size() == 0)  {
        cout << path + "/" + f->name() << endl; //base case
        return;
    }
    
    cout << path + "/" + f->name() << endl;
    
    //We've hit a Directory, so we want to iterate through the directory's Files
    for (vector<File*>::const_iterator it = f->files()->begin(); it != f->files()->end(); it++) { //magic function that can do everything except the root file
        listAll(*it, path + "/" + f->name());
    }
    
}
