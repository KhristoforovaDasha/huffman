#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <ostream>
using namespace std;
map <char,int> mp;
map <string,string> code;
struct node
{
    node* left;
    node* right;
    string c;
    int val;
    node(char c_, int val_)
    {
        c += c_;
        val = val_;
        left = right = nullptr;
    }
    node(string st)
    {
        c = st;
        left = right = nullptr;
    }
    node(node* left_, node* right_,int val_)
    {
        left = left_;
        right = right_;
        val = val_;
        c = "nd";
    }
    node(string st,int val_)
    {
        c = st;
        left = right = nullptr;
        val = val_;
    }
};
void dfs(node* tree,string s,ofstream& filename);
void gen()
{
    node* root;
    int fl = 0;
    set <pair<int,node*> > st;
    for(auto it = mp.begin(); it != mp.end(); ++it)
    {
        node* cnt = new node(it->first,it->second);
        st.insert({it->second,cnt});
    }
    if(st.size() == 1)
    {
        fl = 1;
        auto it = st.begin();
        root = new node(it->second->c,it->first);
    }
    while(st.size() != 1)
    {
        auto it1 = st.begin();
        auto it2 = next(st.begin());
        int k = it1->first + it2->first;
        node* cnt = new node(it1->second,it2->second,k);
        st.erase(it1);
        st.erase(it2);
        st.insert({k,cnt});
        if(st.size() == 1)
        {
            root = cnt;
            //break;
        }
    }
    ofstream filename ("D:\\tree.txt");
    if(fl) dfs(root,"0",filename);
    else  dfs(root,"",filename);
    ofstream file ("D:\\table.txt");
    for(auto it = code.begin(); it != code.end(); ++it)
    {
        file << it->first <<" " << it->second <<'\n';
    }

}
void dfs(node* tree,string s,ofstream& file)
{
    if(tree == nullptr) return;
    file << tree->c << " ";
    if (tree->right == nullptr && tree->left == nullptr)
    {
        string cnt = tree->c;
        code[cnt] = s;
    }
    dfs(tree->left, s + '0',file);
    dfs(tree->right,s + '1',file);
}
void encode()
{
    fstream file("D:\\text.txt");
    ofstream file1("D:\\encoded.txt");
    ifstream filename ("D:\\table.txt");
    char c;
    while(filename.is_open())
    {
        //string s;
        while((c = filename.get()) != EOF)
        {
            std::string buff;
            filename >> buff;
            filename.get();
            code[std::string(1, c)] = buff;
        }
        filename.close();
    }
    //char c;
    while(file.is_open())
    {
        while((c = file.get()) != EOF)
        {
            string s;
            s += c;
            file1 << code[s];
        }
        file.close();
    }
    file1.close();
}
void decode(node*& tree, fstream& file)
{
    char c;
    while(file.is_open())
    {
        string s = "";
        while((c = file.get()) != EOF)
        {
            if(c == ' ' && s != "")
            {
                tree = new node(s);
                if(s == "nd")
                {
                    s = "";
                    decode(tree->left,file);
                    decode(tree->right,file);
                    return;
                }
                else
                {
                    s = "";
                    return;
                }
            }
            else s += c;
        }
        file.close();
    }
}
void write(node*& root,fstream& file,ofstream& code)
{
    char cc;
    node* cnt = root;
    while(file.is_open())
    {
        while((cc = file.get()) != EOF)
        {
            if(cc == '0' && cnt->left) cnt = cnt->left;
            else if(cnt->right) cnt = cnt->right;
            if(cnt->c != "nd")
            {
                code << cnt->c;
                cnt = root;
            }
        }
        file.close();
    }
}
int main()
{
    string command;
    cin >> command;
    if(command == "generate" || command == "all")
    {
        fstream file("D:\\text.txt");
        char c;
        while(file.is_open())
        {
            while((c = file.get()) != EOF)
            {
                mp[c]++;
            }
            file.close();
        }
        gen();
    }
    if(command == "encode" || command == "all") encode();
    if(command == "decode" || command == "all")
    {
        fstream filename("D:\\tree.txt");
        node* root = nullptr;
        decode(root,filename);
        fstream file1("D:\\encoded.txt");
        ofstream code("D:\\decoded.txt");
        write(root,file1,code);
    }
    return 0;
}
