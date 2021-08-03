
#include<iostream>
using namespace std;
#include<unordered_map>

class node
{
    public:
    node*next;
    node*prev;
    int value;
    int key;
    public:
        node(int value,int key)
        {
            this->value=value;
            prev=NULL;
            next=NULL;
            this->key=key;
        }
};





class LRUCache {
    int count;
    int capacity;
    node*head;
    node*tail;
    unordered_map<int,node*>mp;
    
public:
    
    
    LRUCache(int capacity)
    {
        count=0;
        this->capacity=capacity;
        head=NULL;
        tail=NULL;
    }
    void helper(node*temp)
    {
        if(temp==head)
        {
            head=head->next;
            temp->next->prev=NULL;
            temp->next=NULL;
            tail->next=temp;
            temp->prev=tail;
            tail=tail->next;
            return ;
            
        }
        node*h1=temp->prev;
        node*h2=temp->next;
        h1->next=h2;
        h2->prev=h1;
        temp->next=NULL;
        temp->prev=NULL;
        tail->next=temp;
        temp->prev=tail;
        tail=tail->next;
        return ;
    }
    int get(int key)
    {
        
        
        if(mp[key]!=NULL)
        {
            //cout<<mp[key]->value<<endl;
            node*temp=mp[key];
            int ans=temp->value;
            if(temp==tail)
            {
                return ans;
            }
            helper(temp);
            
            return ans;
            
            
        }
        else
        {
            return -1;
        }
        
    }
    
    void put(int key, int value)
    {
        if(mp[key]!=NULL)
        {
            node*temp=mp[key];
            temp->value=value;
            if(temp==tail)
            {
                return ;
            }
            helper(temp);
            
        }
        
        else
        {
            
            node*temp=new node(value,key);
            mp[key]=temp;
            if(head==NULL)
            {
                head=temp;
                tail=temp;
                count++;
                 
            }
            else
            {
                if(count==capacity)
                {
                    tail->next=temp;
                    temp->prev=tail;
                    tail=tail->next;
                    
                    node*remove=head;
                    head=head->next;
                    head->prev=NULL;
                    remove->next=NULL;
                    mp.erase(remove->key);
                    delete(remove);
                    
                    
                    
                }
                else
                {
                    tail->next=temp;
                    temp->prev=tail;
                    tail=tail->next;
                    count++;
                }
            }
            //cout<<head->value<<" "<<tail->value<<endl;
            
        }
        
        
        
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */


int main()
{
    LRUCache l(2);
    l.put(1,1);
    l.put(2, 2);
    int ans=l.get(1);
    cout<<ans<<endl;
    l.put(3, 3);
     ans=l.get(2);
    cout<<ans<<endl;
    l.put(4, 4);
     ans=l.get(3);
    cout<<ans<<endl;
    
}
