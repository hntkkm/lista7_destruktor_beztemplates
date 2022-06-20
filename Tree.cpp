#include <iostream>
#include <string>
using namespace std;

class Tree{
public:
    struct drzewkoPojedyncze {
        int key;
        drzewkoPojedyncze* left;
        drzewkoPojedyncze* right;
    };
    drzewkoPojedyncze *korzen;

    Tree();
    ~Tree();
    drzewkoPojedyncze* insert(int addKey, drzewkoPojedyncze* drzewko);
    string draw(drzewkoPojedyncze* drzewko);
    string search(int x, drzewkoPojedyncze* drzewko);
    drzewkoPojedyncze* remove(int remoweKey, drzewkoPojedyncze* drzewko);

    drzewkoPojedyncze* deleteAll(drzewkoPojedyncze* t);
    drzewkoPojedyncze* findMin(drzewkoPojedyncze* drzewko);
};

Tree::Tree()
{
    korzen = nullptr;
    cout<<"kontruktor"<<endl;
}

Tree::~Tree()
{
    korzen = deleteAll(korzen);
    cout<< "destruktor"<<endl;
}

Tree::drzewkoPojedyncze *Tree::insert(int addKey, Tree::drzewkoPojedyncze *drzewko) {
    if(drzewko == nullptr)
    {
        drzewko = new drzewkoPojedyncze;
        drzewko->key = addKey;
        drzewko->left = drzewko->right = nullptr;
    }
    else if(addKey < drzewko->key)
        drzewko->left = insert(addKey, drzewko->left);
    else if(addKey > drzewko->key)
        drzewko->right = insert(addKey, drzewko->right);
    return drzewko;
}

string Tree::draw(Tree::drzewkoPojedyncze *drzewko) {
    if(drzewko == nullptr)
        return "()";
    return "(" + to_string(drzewko->key) + ":" + draw(drzewko->left) + ":" + draw(drzewko->right) + ")";
}

string Tree::search(int x, Tree::drzewkoPojedyncze *drzewko) {
    if(drzewko == nullptr)
        return "Nie ma elementu: " + to_string(x) ;
    else if(x < drzewko->key)
        return search(x, drzewko->left);
    else if(x > drzewko->key)
        return search(x, drzewko->right);
    else
        return "Jest element: " + to_string(x);
}

Tree::drzewkoPojedyncze *Tree::findMin(Tree::drzewkoPojedyncze *drzewko) {
    if(drzewko == nullptr)
        return nullptr;
    else if(drzewko->left == nullptr)
        return drzewko;
    return findMin(drzewko->left);
}

Tree::drzewkoPojedyncze *Tree::remove(int remoweKey, Tree::drzewkoPojedyncze *drzewko) {
    drzewkoPojedyncze* tempDrzewko;
    if(drzewko == nullptr)
        return nullptr;

    //szukamy element do usuniecia
    else if(remoweKey < drzewko->key)
        drzewko->left = remove(remoweKey, drzewko->left);
    else if(remoweKey > drzewko->key)
        drzewko->right = remove(remoweKey, drzewko->right);

    //usuniecie
    else if(drzewko->left && drzewko->right)
    {
        tempDrzewko = findMin(drzewko->right);
        drzewko->key = tempDrzewko->key;
        drzewko->right = remove(drzewko->key, drzewko->right);
    }
    else
    {
        tempDrzewko = drzewko;
        if(drzewko->left == nullptr)
            drzewko = drzewko->right;
        else if(drzewko->right == nullptr)
            drzewko = drzewko->left;
        delete tempDrzewko;
    }
    return drzewko;
}

Tree::drzewkoPojedyncze *Tree::deleteAll(Tree::drzewkoPojedyncze *t) {
    if(t == nullptr)
        return nullptr;
    else {
        deleteAll(t->left);
        deleteAll(t->right);
        delete t;
    }
    return nullptr;
}

int main()
{
    Tree root;
    root.korzen = root.remove(5, root.korzen);
    cout << root.draw(root.korzen) << endl;
    root.korzen = root.insert(10, root.korzen);
    root.korzen = root.insert(8, root.korzen);
    root.korzen = root.insert(9, root.korzen);
    root.korzen = root.insert(20, root.korzen);
    root.korzen = root.insert(15, root.korzen);
    root.korzen = root.insert(25, root.korzen);
    root.korzen = root.insert(12, root.korzen);
    cout << root.draw(root.korzen) << endl;
    root.korzen = root.remove(20, root.korzen);
    cout << root.draw(root.korzen) << endl;
    root.korzen = root.remove(10, root.korzen);
    cout << root.draw(root.korzen) << endl;
    root.korzen = root.insert(10,root.korzen);
    cout << root.search(6, root.korzen) << endl;
    cout << root.search(9, root.korzen) << endl;

//todo templates
//todo header
    return 0;
}