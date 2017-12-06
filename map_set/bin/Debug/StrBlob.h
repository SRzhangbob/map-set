#ifndef STRBLOB_H_INCLUDED
#define STRBLOB_H_INCLUDED
#include<memory>
class StrBlob
{

public:
    typedef std::vector<std::string>::size_type size_ty;
    StrBlob();
    StrBlob(std::initializer_list<std::string> li);
    size_ty size() const {return data->size();}
    bool empty() const {return data->empty();}

    //添加和删除元素
    void push_back(const std::string &t) { data->push_back(t);}
    void pop_back();

    //元素访问
    std::string& front();
    std::string& back();

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_ty i,const std::string &msg) const;

};

//构造函数
StrBlob::StrBlob():data(make_shared<std::vector<std::string>>())
{

}

StrBlob::StrBlob(std::initializer_list<std::string> li):
    data(make_shared<std::vector<std::string>>(li))
{

}

void StrBlob::check(size_ty i,const string &msg) const
{
    //若i大于它的引用计数，抛出数组越界异常

    if(i>=data->size())
        throw out_of_range(msg);
}

string & StrBlob::front()
{

    check(0,"front on empty StrBlob");
    return data->front();

}

string & StrBlob::back()
{

    check(0,"back on empty StrBlob");
    return data->back();

}

void pop_back()
{
    check(0,"pop_back on empty StrBlob");
    return data->pop_back();

}

struct destination
{
    std::string m_ip;
    int m_port;
    destination(std::string p,int port):m_ip(p),m_port(port){}

};

struct connection
{
    std::string m_ip;
    int m_port;
    connection(std::string p,int port):m_ip(p),m_port(port){}

};

connection connect(destination *p)
{

    std::shared_ptr<connection> p_str(new connection(p->m_ip,p->m_port));
    cout << "Use count: " << p_str.use_count() << endl;
    return *p_str;

}

void disconnect(connection &c)
{

    cout << "Close " << c.m_ip << endl;

}

void end_connect(connection *p)
{

    disconnect(*p);
}

#endif // STRBLOB_H_INCLUDED
