STACK & QUEUE
===

### Stack

```
#include <iostream>
#include <string>
#define max_size 101

using namespace std;
        
class Stack{
        int stack[max_size]; // stack의 크기
        int top; // top의 초깃값은 스택이 비어있을 때 -1이다.
    public:
        Stack(){top=-1;} // stack의 top 초기값을 비어있음으로 정의
        bool empty(){return top == -1;} // 스택이 비어있다면(-1) true라고 반환
        void push(int x); // push는 int x를 변수로 받는 함수
        int pop(); // pop은 top을 순차적으로 빼냄
        int peek(); // peek은 스택이 비어있지 않으면 맨 위의 변수를 반환
        int size(); // size는 스택의 사이즈를 반환
};

void Stack::push(int x){
    stack[++top]=x; // top에 x를 올림
}

int Stack::pop(){
    if (top < 0) { // top이 0미만 즉, 비어있음
        cout << "stack 비어있음";
        return 0;
    }
    else {
        int x = stack[top--]; // top에서 x를 뺌
        return x; // 함수가 아니므로 return
    }
}

int Stack::peek(){
    if (top < 0) { // top이 0미만 즉, 비어있음
        cout << "Stack is Empty";
        return 0;
    }
    else {
        int x = stack[top]; // top = x
        return x;
    }
}

int Stack::size(){
    return top+1;
}

int main(){

    Stack real; // Stack클래스에 real객체 생성
    int value;
    cout << "stack: push | pop | peek | empty | size" << endl;
    for(int i=0;i<max_size;i++) { // stack의 크기가 10이므로
        string str;
        int value;
        cin >> str;
        if(str=="push"){
            cin >> value;
            real.push(value); 
        }
        if(str=="pop"){
            cout << real.pop() << '\n';
        }
        if (str == "peek") {
			cout  << real.peek() << '\n';
		}
        if (str == "empty") {
			cout << boolalpha << real.empty() << '\n'; // boolalpha를 통해 0,1 이 아닌 true, false 반환
            if (real.empty() == true){
                break;
            }
        }
        if (str == "size"){
            cout << real.size() << '\n';
        }
    }
    return 0;
}
```

### Queue
```
#include <iostream>
#include <string>
#define max_size 101

using namespace std;
        
class Que{
        int que[max_size]; 
        int front; 
        int rear; 
    public:
        Que(){front=rear=0;}
        bool empty(){return front==rear;} 
        void enqueue(int x); // 데이터 삽입시 그 데이터는 큐의 rear에 위치
        int dequeue(); // queue의 front에 위치한 데이터를 삭제
        int first(); // 제일 앞의 원소를 반환
        int peek(); 
        int size(){return rear-front;}
};

void Que::enqueue(int x){
    rear=(rear+1)%max_size;
    que[rear]=x;
}

int Que::dequeue(){
    front=(front+1)%max_size;
    return que[front];
}

int Que::first(){ //first는 맨 처음 요소 반환
    if(empty()){
        cout << "queue가 공백입니다";
    }
    else   
        return que[front+1];
}

int Que::peek(){ //peek은 맨 위 요소 반환
    if(empty()){
        cout << "queue가 공백입니다";
    }
    else   
        return que[rear];
}

int main(){

    Que real; // que클래스에 real객체 생성
    int value;
    cout << "Que: enqueue | dequeue | peek | first | empty | size" << endl;
    for(int i=0;i<max_size;i++) { // que의 크기가 10이므로
        string str;
        int value;
        cin >> str;
        if(str=="enqueue"){
            cin >> value;
            real.enqueue(value); 
        }
        if(str=="dequeue"){
            cout << real.dequeue() << '\n';
        }
        if (str == "peek") {
			cout  << real.peek() << '\n';
		}
        if (str == "first") {
			cout  << real.first() << '\n';
		}
        if (str == "empty") {
			cout << boolalpha << real.empty() << '\n'; // boolalpha를 통해 0,1 이 아닌 true, false 반환
            if (real.empty() == true){
                break;
            }
        }
        if (str == "size"){
            cout << real.size() << '\n';
        }
    }
    return 0;
}
```
