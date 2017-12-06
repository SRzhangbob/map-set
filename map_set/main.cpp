#include <iostream>
#include<set>
#include<map>
#include<string>
#include<cctype>
#include<algorithm>
#include<vector>
#include<fstream>
#include<list>
#include<sstream>
#include<unordered_map>
#include<iterator>
#include"StrBlob.h"
#include<string.h>

using namespace std;
bool elim_dulp(const vector<string> &s1,const string &s2);
const string & tran_word(const string &word,const unordered_map<string,string> &m);
unordered_map<string,string> createmap(ifstream &mapfile);

bool is_p(char c)
{

    return  ispunct(c)?true:false;

}

char re(char c)
{
    if(isupper(c))
        return tolower(c);
    else
        return c;

}

void remove_punct(string &s)
{
    if(ispunct(s[s.size()-1]))
        s = s.substr(0,s.size()-1);

}


void map_1()
{


    map<string,size_t> word_count;
    set<string> exclude = {"The","but","And"};
    string word;
    while(cin >> word)
    //若未在排除的集合中，则加入map中
    {
        //去除单词尾部的标点
        remove_punct(word);
        //将其转为小写
        transform(word.begin(),word.end(),word.begin(),re);

        if(exclude.find(word)==exclude.end())
            ++word_count[word];
//        {
//                 //使用插入来统计单词，可读性差很多
//                auto ret = word_count.insert({word,1});
//
//                if(!ret.second)
//                    ++ret.first->second;
//
//        }
    }

    for(const auto &w:word_count)
        cout << w.first << " occurs " << w.second
            << (w.second>1?" times":" time") << endl;

}

void test_it()
{

    map<string,vector<string>> family;
    string name,temp;
    cout << "Enter family's name: ";
    while(cin >> name)
    {
        while(cin)
        {
            cout << "enter family: ";
            cin >> temp;
            family[name].push_back(temp);

        }
    cin.clear();
    cout << "Enter family's name: ";
    }

    cin.clear();
    for(const auto &a:family)
    {
        cout <<"Family: " << a.first <<endl;
        for(const auto &b:a.second)
            cout <<b <<" ,";
        cout << endl;
    }

}

void test_it2()
{

    map<string,vector<pair<string,string>>> family;
    string name,temp;
    string birth;
    cout << "Enter family's name: ";
    while(cin >> name)
    {
        while(cin)
        {
            cout << "enter name and birth: ";
            cin >> temp >> birth;
            family[name].push_back({temp,birth});

        }
    cin.clear();
    cout << "Enter family's name: ";
    }

    cin.clear();
    for(const auto &a:family)
    {
        cout <<"Family: " << a.first <<endl;
        for(const auto &b:a.second)
            cout <<b.first <<" ," << b.second;
        cout << endl;
    }

}

void tets_set()
{
    vector<string> line;
    string word;
    while(cin >> word)
        if(elim_dulp(line,word))
            line.push_back(word);

    for_each(line.cbegin(),line.cend(),[](const string &s) { cout << s << ", " ;});

    cout << endl;

}

bool elim_dulp(const vector<string> &s1,const string &s2)
{

//在vector不存在这个单词
    if(find(s1.cbegin(),s1.cend(),s2)==s1.cend())
        return true;
    else
        return false;

}

void file_1()
{

    ifstream fin("test.txt");

    if(!fin.is_open())
    {

        cerr << "Cannot open file!!!\n";
        exit(1);
    }
    string temp;
    int line = 1;
    string word;
    string::size_type t1;
    map<string,list<int>> word_line;
    while(getline(fin,temp))
    {
        istringstream s1(temp);  //关联到行
        while(s1>>word)
        {
            t1 = word.size()-1;
            //去除标点符号
            if(ispunct(word[t1]))
                word = word.substr(0,t1);
            //首字母转为小写
            if(isupper(word[0]))
               word[0] = tolower(word[0]);

            //若line未出现在list中，加入list中
            if(find(word_line[word].cbegin(),
                    word_line[word].cend(),line)==word_line[word].cend())
            word_line[word].push_back(line);

        }

        ++ line;

    }

    //打印map的内容
    for(const auto &i:word_line)
    {
        cout << i.first << ": ";
        for(const auto &j:i.second)
            cout << j << " ,";
        cout << endl;
    }



    fin.close();


}

void test_pair()
{

    vector<pair<string,int>> v_pair;
    string s1;
    int i;
    while(cin >>s1 >>i )
    {

       // v_pair.push_back({s1,i});
        v_pair.push_back(pair<string,int>(s1,i));
        //v_pair.push_back(make_pair(s1,i));
        //以上三个是等价的，第一种简单，第二种更容易读写

        cin.get();

    }

    for(const auto &vi:v_pair)
        cout << vi.first << ", " << vi.second << endl;

}

void multimap_test()
{

    multimap<string,string> author_book;
    string author,book;
    cout << "Enter the autor and book: ";
    while(cin>>author>>book)
    {

    author_book.insert({author,book});
    cin.get();
    cout << "Enter the autor and book: ";
    }

    author = book = "";
    //
    cin.clear();
    cout << "Enter the autor and book you want to erase: ";
    cin >> author >> book;
    auto iter = author_book.find(author);
    auto count_i =  author_book.count(author);
    while(count_i)
    {

        if(iter->second == book)
        {
            author_book.erase(iter);
            break;
        }
        ++iter;
        --count_i;

    }

    //11.32
    map<string,set<string>> author_b;
    for(const auto&i:author_book)
    {
        author_b[i.first].insert(i.second);

    }

    for(const auto&ib:author_b)
    {
        for(const auto &b:ib.second)
            cout << ib.first << ", " << b << endl;
    }
    for(const auto&ab : author_book)
        cout << ab.first << ", " << ab.second << endl;

}



map<string,string> buildMap(ifstream &mapfile)
{

    map<string,string> temp;
    string key,value;
    while(mapfile>>key && getline(mapfile,value))
        if(value.size()>1)
            temp[key] = value.substr(1);  //去除空格影响
        else
            throw runtime_error("no rule for" + key);
    return temp;

}

const string& transform(const string &s,const map<string,string> &m)
{
    auto map_it = m.find(s);

    if(map_it!=m.cend())
        return map_it->second;

    else
        return s;

}

void word_transform(ifstream &mapfile,ifstream &input)
{
    auto tran_map = createmap(mapfile);

    string text;
    string word;

    while(getline(input,text))
    {

        istringstream stream(text);
        //cout << text << endl;

        bool firstword = true;

        //除了第一个单词之后所有单词之间都有一个空格
        while(stream >> word)
        {
            //cout << word << endl;
            if(firstword)
                firstword = false;

            else
                cout << " ";

            cout << tran_word(word,tran_map);

        }

        cout << endl;

    }

}

void word_count()
{
    //无序的容器不用维护元素的顺序，通常这个代价很高，所以他们平均性能更好
    //简单 + 性能好
    unordered_map<string,int> word_c;

    string word;
    while(cin >> word)
        ++word_c[word];   //提取并且递增word的计数器

    for(const auto & w:word_c)
        cout << w.first << ": " << w.second << endl;


}

void test_23()
{

    ifstream mapfile,input;
    mapfile.open("test.txt");
    input.open("input.txt");
    if(!mapfile.is_open())
    {
        cerr << "Cannot open file test.txt\n";
        exit(1);

    }

    if(!input.is_open())
    {
        cerr << "Cannot open file input.txt\n";
        exit(1);

    }

    word_transform(mapfile,input);

    mapfile.close();
    input.close();

}

unordered_map<string,string> createmap(ifstream &mapfile)
{
    string key,value;

    unordered_map<string,string> temp;
    while(mapfile >> key && getline(mapfile,value))
        if(value.size()>1)
            temp[key] = value.substr(1);
        else
            throw runtime_error("No rule for" + key);

    return temp;
}

const string & tran_word(const string &word,const unordered_map<string,string> &m)
{

    auto m_it = m.find(word);
    if(m_it!=m.cend()) //找到对应的key
        return m_it->second;
    else
        return word;

}

void test_hash()
{

    unordered_map<string ,int> c1 = {{"ds1g",34},{"dsg",35},{"dsger",15},{"dsgd2ger",25},
                                    {"dsFRg",34},{"dsDFg",35},{"dsgFGer",15},{"dsgdger",35}};
    for(const auto &a : c1)
        cout << a.first << ", " << a.second << endl;

    cout << "Bucket operator:\n";
    cout <<"bucket count: " << c1.bucket_count() << endl;
    cout <<"max bucket count: " << c1.max_bucket_count() << endl;
    //第n个桶中含有多少个元素
    cout << "elements of nth buckte: " << c1.bucket_size(1) <<endl;
    //关键字ds1g在哪个桶中
    cout << "which bucket is the element k ? " << c1.bucket("ds1g") << endl;
    unordered_map<string,int>::const_local_iterator bucket_it;

    for(bucket_it = c1.cbegin(1);bucket_it!=c1.cend(1);++bucket_it)
        cout << bucket_it->first << ", " << bucket_it->second << endl;

    cout << "Load factor: " << c1.load_factor() << endl;
    cout << "max Load factor: " << c1.max_load_factor() << endl;

}

//智能指针之常规指针
//
vector<int> * create_v()
{

    vector<int> *a = new vector<int>;

    return a;

}

void in(vector<int> *p)
{
    cout << "Enter numbers: ";
    int i;
    while(cin>>i)
        p->push_back(i);

}

void out(vector<int> *p)
{
    cout << "Vector as follow: ";
    for(auto it= p->cbegin();it!=p->cend();++it)
        cout << *it << ", ";
    cout << endl;

}

void tets_p()
{

    auto p = create_v();
    in(p);
    out(p);

    delete p;

    cout << "The End\n";
}

//智能指针之shared_ptr
shared_ptr<vector<int>> create_shv()
{

    return make_shared<vector<int>>();

}

void in1(shared_ptr<vector<int>> p)
{
    cout << "Enter numbers: ";
    int i;
    while(cin>>i)
        p->push_back(i);

}

void out1(shared_ptr<vector<int>> p)
{
    cout << "Vector as follow: ";
    for(auto it= p->cbegin();it!=p->cend();++it)
        cout << *it << ", ";
    cout << endl;

}

void tets_sh_p()
{

    auto p = create_shv();
    in1(p);
    out1(p);

 //   delete p;

    cout << "The End\n";
}

void f(destination &d)
{

    connection c = connect(&d);
    //使用end_connect作为删除器
    shared_ptr<connection> pstr(&c,end_connect);
    //使用匿名函数作为删除器函数
    //shared_ptr<connection> pstr(&c,[](connection *p) {disconnect(*p);});

}

void test_strblob()
{
    ifstream fin("test.txt");
    if(!fin.is_open())
    {
        cerr<<("Cannot open file!!!\n");
        exit(1);
    }
    string temp,word;

    while(getline(fin,temp))
    {

        istringstream stream(temp);
        StrBlob c1;
        while(stream >> word)
        {

            c1.push_back(word);

        }
        //需要为StrBlobPtr定义操作符！=
        for(auto beg = c1.begin();beg!=c1.end();beg.incr())
            cout << beg.deref() << " ";
        cout << endl;


    }

}

void test_pr()
{

    char s1[] = "Hello,";
    char s2[] = "C++!";

    char *p = new char[strlen(s1),strlen(s2)+1]();
    strcat(p,s1);
    strcat(p,s2);

    cout << p << endl;

    string ss1 = "Hello!";
    string ss2 = "C#!";

    char *p2 = new char[ss1.size()+ss2.size()+1]();

    //将两个string链接保存到一个char数组中
    strcat(p2,ss1.c_str());
    strcat(p2,ss2.c_str());

    cout << p2 << endl;

    //切记释放内存，否则可能内存泄漏
    delete [] p;
    delete [] p2;


}

void tets1()
{
    char *p = new char[10];
    //会读入9个字符，丢弃9个字符以后的字符，然后写入\0
    cin.get(p,10);

    cout <<strlen(p) <<p << endl;

    //切记切记释放分配的内存
    delete [] p;

    unique_ptr<int []> up(new int[10]);
    for(size_t i =0;i!=10;++i)
        up[i] = i;
    for(size_t i = 0;i!=10;++i)
        cout << up[i] << ", ";
    cout << endl;

    up.release();


}

//allocator类，它是将内存分配和对象构造分离的,这样可以节省部分构造对象的开销？
//allocator类，它是将内存分配和对象构造分离的
//allocator类，它是将内存分配和对象构造分离的
void test_alloc()
{
    allocator<string> alloc;
    const int N_size = 100;
    auto const p = alloc.allocate(N_size);

    string s;

    string *q = p;
    //对部分分配的内存创建对象
    while(cin >> s && q!=p+N_size)
        alloc.construct(q++,s);


    for(auto a = p;a!=q;++a)
        cout << *a << ", ";
    cout << endl;

    //对进行了对象构造的区域进行destroy操作
    while(q!=p)
        alloc.destroy(--q);

    //在对创建了对象的区域进行了destroy之后，
    //那么可以将这个区域进行释放还给系统
    alloc.deallocate(p,N_size);



}

void test_ptr()
{
    StrBlob sb{"hello", "world"};
    StrBlobPtr iter = sb.begin();
    StrBlobPtr_Pointer p(&iter);
    std::cout << p->deref() << std::endl;



}


int main()
{
    test_ptr();
    test_alloc();
    tets1();
    test_pr();
    test_strblob();
    destination d("192.168.1.0",8080);
    f(d);
    auto sp = make_shared<int>();
    unique_ptr<int> p1(new int(43));
    //unique_ptr不支持拷贝和赋值操作，它们在定义中被显示地删除
    //unique_ptr<int> p2(p1);
   // unique_ptr<int> p2 = p1;
    auto p = sp.get();
    delete p;
    tets_sh_p();
    test_hash();
    //word_count();
    test_23();
    multimap_test();
    //test_pair();
    multiset<string> c;
    vector<string> v = {"sdfa","dgdg"};
    copy(v.cbegin(),v.cend(),inserter(c,c.end()));
    file_1();
    test_it2();
    tets_set();
    cout << is_p(',');
    map_1();
    cout << "Hello world!" << endl;
    return 0;
}
