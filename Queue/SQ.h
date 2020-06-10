#ifndef SQ_H_INCLUDED
#define SQ_H_INCLUDED

#include <iostream>
#include <utility>
#include <initializer_list>

template<typename> class Queue;
template<typename T>
    void printQueue(const Queue<T>&);
template<typename T>
    void swap(Queue<T>&,Queue<T>&);

template<class Datatype>
class Queue
{
public:
    //default construct
    Queue(int m=10)//lvalue?
    {
        init(m);
    }
    //initializer list construct
    Queue(std::initializer_list<Datatype> Q)
    {
        init(30);
        for(auto &x:Q)
        {
            EnQueue(x);
        }
    }
    //Big Five
    ~Queue(){delete[]data;}

    Queue(const Queue &rhs):front(rhs.front),rear(rhs.rear),maxSize(rhs.maxSize),theSize(rhs.theSize),data{new Datatype[maxSize]}
    {
        for(int i=0;i!=theSize;i++)
            //*(data+i)=*(rhs.data+i);
            data[i]=rhs.data[i];
    }

    Queue& operator=(const Queue &rhs)
    {
        //std::cout<<"run"<<std::endl;
        Queue copy=rhs;
        //std::swap(*this,copy);
        swap(*this,copy);
        return *this;
    }

    /*Queue& operator=(Queue rhs)
    {
        swap(*this,rhs);
        return *this;
    }*/

    Queue(Queue&& rhs):front(rhs.front),rear(rhs.rear),maxSize(rhs.maxSize),theSize(rhs.theSize),data(rhs.data)
    {
        rhs.front=rhs.rear=rhs.maxSize=rhs.theSize=0;
        rhs.data=nullptr;
    }
    Queue& operator=(Queue&& rhs)
    {
        swap(*this,rhs);
        return *this;
    }

public:
    void EnQueue(const Datatype& x)
    {
        if(full())
            return ;
        data[rear]=x;
        rear=(rear+1)%maxSize;
        theSize++;
    }

    void EnQueue(Datatype&& x)
    {
        if(full())
            return ;
        data[rear]=x;
        rear=(rear+1)%maxSize;
        theSize++;
    }

    void DeQueue()
    {
        if(empty())
            return ;
        front=(front+1)%maxSize;
        theSize--;
    }

    const Datatype& top()const
    {
        return data[front];
    }

    Datatype& top()
    {
        return data[front];
    }

    const Datatype& back()const
    {
        return data[rear-1];
    }

    Datatype& back()
    {
        return data[rear-1];
    }

    bool full()const
    {
        return theSize==maxSize;
    }

    bool empty()const
    {
        return theSize==0;
    }

    const int Size()const
    {
        return theSize;
    }

    friend void printQueue<Datatype>(const Queue<Datatype>&);
    friend void swap<Datatype>(Queue<Datatype> &,Queue<Datatype> &);

private:
    int front;
    int rear;
    int maxSize;
    int theSize;
    Datatype* data;

    void init(int m)
    {
        front=0;
        rear=0;
        maxSize=m;
        theSize=0;
        data=new Datatype[maxSize];
    }
};

template<typename T>
void printQueue(const Queue<T>& Q)
{
    if(Q.empty())
        return ;
    std::cout<<"Queue length: "<<Q.Size()<<std::endl;
    std::cout<<"Queue data: ";
    std::cout << Q.data[Q.front] << " ";
    for(int p=Q.front+1;p!=Q.rear;p=(p+1)%Q.maxSize)
    {
        std::cout<<Q.data[p]<<" ";
    }
}

template<typename T>
void swap(Queue<T> &lhs,Queue<T> &rhs)
{
    using std::swap;
    swap(lhs.front,rhs.front);
    swap(lhs.rear,rhs.rear);
    swap(lhs.maxSize,rhs.maxSize);
    swap(lhs.theSize,rhs.theSize);
    swap(lhs.data,rhs.data);
}
void solve1();
#endif // SQ_H_INCLUDED