#ifndef STRBLOB_H_INCLUDED
#define STRBLOB_H_INCLUDED
#include<memory>
class StrBlobPtr;
class StrBlob
{

public:
    friend class StrBlobPtr;
    StrBlobPtr begin();
    StrBlobPtr end();

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
    std::string  back() const;
    std::string  front() const;


private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_ty i,const std::string &msg) const;

};

//构造函数
StrBlob::StrBlob():data(std::make_shared<std::vector<std::string>>())
{

}

StrBlob::StrBlob(std::initializer_list<std::string> li):
    data(std::make_shared<std::vector<std::string>>(li))
{

}

void StrBlob::check(size_ty i,const std::string &msg) const
{
    //若i大于它的引用计数，抛出数组越界异常

    if(i>=data->size())
        throw std::out_of_range(msg);
}

std::string & StrBlob::front()
{

    check(0,"front on empty StrBlob");
    return data->front();

}

std::string & StrBlob::back()
{

    check(0,"back on empty StrBlob");
    return data->back();

}

std::string  StrBlob::front() const
{

    check(0,"front on empty StrBlob");
    return data->front();

}

std::string  StrBlob::back() const
{

    check(0,"back on empty StrBlob");
    return data->back();

}

void StrBlob::pop_back()
{
    check(0,"pop_back on empty StrBlob");
    return data->pop_back();

}

class StrBlobPtr{

public:
    StrBlobPtr():m_curr(0) {}
    StrBlobPtr(StrBlob &a,size_t sz = 0):m_wptr(a.data),m_curr(sz) {}
    std::string deref() const;
    StrBlobPtr& incr(); //前缀递增
    //前缀递增运算符
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
    //后缀递增运算符
    StrBlobPtr& operator++(int);
    StrBlobPtr& operator--(int);

    StrBlobPtr& operator+(std::size_t) const;
    StrBlobPtr& operator-(std::size_t) const;
    StrBlobPtr& operator-=(std::size_t);
    StrBlobPtr& operator+=(std::size_t);

    //解引用运算符
    std::string& operator*() const
    {
        auto p = check(m_curr,"dereference past end!!!");

        return (*p)[m_curr];   //*p是一个vector

    }

    std::string* operator->() const
    {
        //将实际工作委托给解引用运算符
        return & this->operator*();
    }
    bool operator!=(const StrBlobPtr &p2) {
    if(m_wptr.lock()==p2.m_wptr.lock()&&m_curr==p2.m_curr)
        return false;
    else
        return true;


    }

private:

    std::shared_ptr<std::vector<std::string>> check(std::size_t,const std::string&) const;
    //保存一个weak_ptr，意味着底层vector可能被销毁
    std::weak_ptr<std::vector<std::string>> m_wptr;
    std::size_t m_curr; //在数组的当前位置

};

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i,const std::string& s) const
{

    auto p = m_wptr.lock();

    if(!p)  //vector是否还存在
        throw std::runtime_error("Unbound StrBlobstr!!!");

    if(i >= p->size())
        throw std::out_of_range(s);

    return p;  //否则返回这个指针
}

std::string StrBlobPtr::deref() const
{

    auto p = check(m_curr,"dereference past end");

    return (*p)[m_curr];  //(*p)是对象所指向的vector

}

StrBlobPtr& StrBlobPtr::incr()
{

    check(m_curr,"increment past end of the StrBlobPtr");
    ++m_curr;

    return *this;

}

StrBlobPtr& StrBlobPtr::operator++()
{
    check(m_curr,"increment past end of the StrBlobPtr");
    ++m_curr;

    return *this;

}


StrBlobPtr& StrBlobPtr::operator--()
{
    --m_curr;

    check(m_curr,"decrement past end of the StrBlobPtr");

    return *this;

}


//后缀版本，需要创建一个临时的对象
//后缀版本，需要创建一个临时的对象
//后缀版本，需要创建一个临时的对象
StrBlobPtr& StrBlobPtr::operator++(int)
{
    StrBlobPtr ret(*this);

    ++(*this);

    return *this;

}

StrBlobPtr& StrBlobPtr::operator--(int)
{
    StrBlobPtr ret(*this);

    --(*this);

    return *this;

}

StrBlobPtr& StrBlobPtr::operator+(std::size_t n) const
{
    StrBlobPtr ret(*this);
    ret += n;

    return ret;

}

StrBlobPtr& StrBlobPtr::operator-(std::size_t n) const
{
    StrBlobPtr ret(*this);
    ret -= n;

    return ret;
}

StrBlobPtr& StrBlobPtr::operator-=(std::size_t n)
{

    m_curr -= n;

    check(m_curr,"increment past end of the StrBlobPtr");

    return *this;

}
StrBlobPtr& StrBlobPtr::operator+=(std::size_t n)
{
    m_curr += n;

    check(m_curr,"increment past end of the StrBlobPtr");

    return *this;

}


//定义函数,要在StrBlob声明后再定义
//定义函数,要在StrBlob声明后再定义
//定义函数,要在StrBlob声明后再定义
StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end() {
    auto ret = StrBlobPtr(*this,data->size());
    return ret;

}

//结构体
//结构体
//结构体
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
    std::cout << "Use count: " << p_str.use_count() << std::endl;
    return *p_str;

}

void disconnect(connection &c)
{

    std::cout << "Close " << c.m_ip << std::endl;

}

void end_connect(connection *p)
{

    disconnect(*p);
}

class StrBlobPtr_Pointer
{

public:
        StrBlobPtr_Pointer() = default;
        StrBlobPtr_Pointer(StrBlobPtr *p):m_pointer(p) {};

        StrBlobPtr& operator*() const
        {

            return *m_pointer;

        }
        StrBlobPtr* operator->() const
        {

            return & this->operator*();

        }

private:


    StrBlobPtr * m_pointer  = nullptr;

};
#endif // STRBLOB_H_INCLUDED
