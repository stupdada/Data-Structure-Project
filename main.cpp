#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <iomanip>

using namespace std;

// 乘客信息结构体
struct Passenger {
    string name;
    string id;
    string phone;
    int vipLevel; // 0: 非VIP, 1: VIP青春版, 2: VIP Pro, 3: VIP Pro Max
};

// 航班信息结构体
struct Flight {
    string flightNo;
    string departureTime;     // 格式: YYYY-MM-DD_HH:MM
    string departure;
    string destination;
    string arrivalTime;       // 格式: YYYY-MM-DD_HH:MM
    int seats;
    int availableSeats;
    double price;
};

// 等待订票的乘客信息结构体
struct WaitingPassenger {
    string flightNo;
    string passengerId;
    int vipLevel;
};

// 单链表模板类
template <typename ElemType>
class LinkList {
protected:
    struct Node {
        ElemType data;
        Node *next;
        Node() : next(NULL) {}
        Node(ElemType d, Node *n = NULL) : data(d), next(n) {}
    };
    Node *head;
    int length;

public:
    LinkList();
    virtual ~LinkList();
    int GetLength() const;
    bool IsEmpty() const;
    void Clear();
    void Traverse(void (*Visit)(const ElemType &)) const;
    int LocateElem(const ElemType &e) const;
    bool GetElem(int i, ElemType &e) const;
    bool SetElem(int i, const ElemType &e);
    bool DeleteElem(int i, ElemType &e);
    bool Insert(int i, const ElemType &e);
    bool InsertElem(const ElemType &e);
    LinkList(const LinkList &la);
    LinkList &operator=(const LinkList &la);
};

template <typename ElemType>
LinkList<ElemType>::LinkList() {
    head = new Node;
    assert(head);
    length = 0;
}

template <typename ElemType>
LinkList<ElemType>::~LinkList() {
    Clear();
    delete head;
}

template <typename ElemType>
int LinkList<ElemType>::GetLength() const {
    return length;
}

template <typename ElemType>
bool LinkList<ElemType>::IsEmpty() const {
    return length == 0;
}

template <typename ElemType>
void LinkList<ElemType>::Clear() {
    typename LinkList<ElemType>::Node *p = head->next;
    while (p != NULL) {
        head->next = p->next;
        delete p;
        p = head->next;
    }
    length = 0;
}

template <typename ElemType>
void LinkList<ElemType>::Traverse(void (*Visit)(const ElemType &)) const {
    typename LinkList<ElemType>::Node *p = head->next;
    while (p != NULL) {
        (*Visit)(p->data);
        p = p->next;
    }
}

template <typename ElemType>
int LinkList<ElemType>::LocateElem(const ElemType &e) const {
    typename LinkList<ElemType>::Node *p = head->next;
    int count = 1;
    while (p != NULL && p->data != e) {
        count++;
        p = p->next;
    }
    return (p != NULL) ? count : 0;
}

template <typename ElemType>
bool LinkList<ElemType>::GetElem(int i, ElemType &e) const {
    if (i < 1 || i > length) return false;
    typename LinkList<ElemType>::Node *p = head->next;
    int j = 1;
    while (j < i && p != NULL) {
        p = p->next;
        j++;
    }
    if (p == NULL) return false;
    e = p->data;
    return true;
}

template <typename ElemType>
bool LinkList<ElemType>::SetElem(int i, const ElemType &e) {
    if (i < 1 || i > length) return false;
    typename LinkList<ElemType>::Node *p = head->next;
    int j = 1;
    while (j < i && p != NULL) {
        p = p->next;
        j++;
    }
    if (p == NULL) return false;
    p->data = e;
    return true;
}

template <typename ElemType>
bool LinkList<ElemType>::DeleteElem(int i, ElemType &e) {
    if (i < 1 || i > length) return false;
    typename LinkList<ElemType>::Node *p = head;
    int j = 0;
    while (j < i - 1 && p->next != NULL) {
        p = p->next;
        j++;
    }
    if (p->next == NULL) return false;
    typename LinkList<ElemType>::Node *q = p->next;
    e = q->data;
    p->next = q->next;
    delete q;
    length--;
    return true;
}

template <typename ElemType>
bool LinkList<ElemType>::Insert(int i, const ElemType &e) {
    if (i < 1 || i > length + 1) return false;
    typename LinkList<ElemType>::Node *p = head;
    int j = 0;
    while (j < i - 1 && p != NULL) {
        p = p->next;
        j++;
    }
    if (p == NULL) return false;
    typename LinkList<ElemType>::Node *s = new typename LinkList<ElemType>::Node(e, p->next);
    assert(s);
    p->next = s;
    length++;
    return true;
}

template <typename ElemType>
bool LinkList<ElemType>::InsertElem(const ElemType &e) {
    return Insert(length + 1, e);
}

template <typename ElemType>
LinkList<ElemType>::LinkList(const LinkList<ElemType> &la) {
    head = new Node;
    assert(head);
    length = 0;
    typename LinkList<ElemType>::Node *p = la.head->next;
    while (p != NULL) {
        InsertElem(p->data);
        p = p->next;
    }
}

template <typename ElemType>
LinkList<ElemType> &LinkList<ElemType>::operator=(const LinkList<ElemType> &la) {
    if (this == &la) return *this;
    Clear();
    typename LinkList<ElemType>::Node *p = la.head->next;
    while (p != NULL) {
        InsertElem(p->data);
        p = p->next;
    }
    return *this;
}

// 链式队列模板类
template <typename ElemType>
class LinkQueue {
protected:
    struct Node {
        ElemType data;
        Node *next;
        Node() : next(NULL) {}
        Node(ElemType d, Node *n = NULL) : data(d), next(n) {}
    };
    Node *front, *rear;

public:
    LinkQueue();
    virtual ~LinkQueue();
    int GetLength() const;
    bool IsEmpty() const;
    void Clear();
    bool DelQueue(ElemType &e);
    bool GetHead(ElemType &e) const;
    bool EnQueue(const ElemType &e);
};

template <typename ElemType>
LinkQueue<ElemType>::LinkQueue() {
    rear = front = new Node;
    assert(front);
}

template <typename ElemType>
LinkQueue<ElemType>::~LinkQueue() {
    Clear();
    delete front;
}

template <typename ElemType>
int LinkQueue<ElemType>::GetLength() const {
    int count = 0;
    Node *p = front->next;
    while (p != NULL) {
        count++;
        p = p->next;
    }
    return count;
}

template <typename ElemType>
bool LinkQueue<ElemType>::IsEmpty() const {
    return rear == front;
}

template <typename ElemType>
void LinkQueue<ElemType>::Clear() {
    Node *p = front->next;
    while (p != NULL) {
        front->next = p->next;
        delete p;
        p = front->next;
    }
    rear = front;
}

template <typename ElemType>
bool LinkQueue<ElemType>::EnQueue(const ElemType &e) {
    Node *p = new Node(e);
    assert(p);
    rear->next = p;
    rear = p;
    return true;
}

template <typename ElemType>
bool LinkQueue<ElemType>::DelQueue(ElemType &e) {
    if (IsEmpty()) return false;
    Node *p = front->next;
    e = p->data;
    front->next = p->next;
    if (rear == p)
        rear = front;
    delete p;
    return true;
}

template <typename ElemType>
bool LinkQueue<ElemType>::GetHead(ElemType &e) const {
    if (IsEmpty()) return false;
    e = front->next->data;
    return true;
}

// 航班信息管理类
class FlightManager {
private:


public:
        LinkList<Flight> flightList;
    void LoadFlights(const string &filename);
    void SaveFlights(const string &filename);
    void AddFlight();
    void QueryFlight();
    void DisplayAllFlights();
    void ModifyFlight();
    Flight* FindFlight(const string &flightNo);
    void DisplayFlightDetails(const Flight &flight);
};

// 乘客信息管理类
class PassengerManager {
private:
    LinkList<Passenger> passengerList;

public:
    void LoadPassengers(const string &filename);
    void SavePassengers(const string &filename);
    void AddPassenger();
    Passenger* FindPassenger(const string &id);
    void DisplayAllPassengers();
};

// 订票系统类
class BookingSystem {
private:
    FlightManager flightManager;
    PassengerManager passengerManager;
    LinkQueue<WaitingPassenger> waitingQueue;

public:
    void LoadData();
    void SaveData();
    void Menu();
    void FlightQuery();
    void BookTicket();
    void RefundTicket();
    void ManageFlights();
    void HandleWaitingList(const string &flightNo);
};

// 实现FlightManager类的成员函数

// 加载航班信息
void FlightManager::LoadFlights(const string &filename) {
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "无法打开航班信息文件 " << filename << "！" << endl;
        return;
    }
    Flight flight;
    while (infile >> flight.flightNo >> flight.departureTime >> flight.departure >> flight.destination
                  >> flight.arrivalTime >> flight.seats >> flight.availableSeats >> flight.price) {
        flightList.InsertElem(flight);
    }
    infile.close();
}

// 保存航班信息
void FlightManager::SaveFlights(const string &filename) {
    ofstream outfile(filename.c_str());
    if (!outfile) {
        cout << "无法打开航班信息文件 " << filename << " 进行写入！" << endl;
        return;
    }
    int len = flightList.GetLength();
    for(int i=1; i<=len; ++i){
        Flight flight;
        flightList.GetElem(i, flight);
        outfile << flight.flightNo << " " << flight.departureTime << " " << flight.departure << " "
                << flight.destination << " " << flight.arrivalTime << " " << flight.seats << " "
                << flight.availableSeats << " " << fixed << setprecision(2) << flight.price << endl;
    }
    outfile.close();
}

// 添加航班
void FlightManager::AddFlight() {
    Flight flight;
    cout << "请输入航班号: ";
    cin >> flight.flightNo;
    cout << "请输入起飞时间 (格式: YYYY-MM-DD_HH:MM): ";
    cin >> flight.departureTime;
    cout << "请输入起飞地点: ";
    cin >> flight.departure;
    cout << "请输入目的地: ";
    cin >> flight.destination;
    cout << "请输入抵达时间 (格式: YYYY-MM-DD_HH:MM): ";
    cin >> flight.arrivalTime;
    cout << "请输入座位总数: ";
    cin >> flight.seats;
    flight.availableSeats = flight.seats;
    cout << "请输入票价: ";
    cin >> flight.price;
    flightList.InsertElem(flight);
    cout << "航班添加成功！" << endl;
}

// 查询航班
void FlightManager::QueryFlight() {
    string flightNo, departureTime, departure, destination, arrivalTime;
    cout << "请输入航班号（不填输入0）: ";
    cin >> flightNo;
    cout << "请输入起飞时间（格式: YYYY-MM-DD_HH:MM，不填输入0）: ";
    cin >> departureTime;
    cout << "请输入起飞地点（不填输入0）: ";
    cin >> departure;
    cout << "请输入目的地（不填输入0）: ";
    cin >> destination;
    cout << "请输入抵达时间（格式: YYYY-MM-DD_HH:MM，不填输入0）: ";
    cin >> arrivalTime;

    int len = flightList.GetLength();
    bool found = false;
    for(int i=1; i<=len; ++i){
        Flight flight;
        flightList.GetElem(i, flight);
        bool match = true;
        if (flightNo != "0" && flight.flightNo != flightNo) match = false;
        if (departureTime != "0" && flight.departureTime != departureTime) match = false;
        if (departure != "0" && flight.departure != departure) match = false;
        if (destination != "0" && flight.destination != destination) match = false;
        if (arrivalTime != "0" && flight.arrivalTime != arrivalTime) match = false;
        if (match) {
            DisplayFlightDetails(flight);
            found = true;
        }
    }
    if (!found) {
        cout << "未找到符合条件的航班。" << endl;
    }
}

// 显示所有航班信息
void FlightManager::DisplayAllFlights() {
    int len = flightList.GetLength();
    if(len == 0){
        cout << "当前没有航班信息。" << endl;
        return;
    }
    for(int i=1; i<=len; ++i){
        Flight flight;
        flightList.GetElem(i, flight);
        DisplayFlightDetails(flight);
    }
}

// 显示航班详细信息
void FlightManager::DisplayFlightDetails(const Flight &flight) {
    cout << "-----------------------------------------" << endl;
    cout << "航班号: " << flight.flightNo << endl;
    cout << "起飞时间: " << flight.departureTime << endl;
    cout << "起飞地点: " << flight.departure << endl;
    cout << "目的地: " << flight.destination << endl;
    cout << "抵达时间: " << flight.arrivalTime << endl;
    cout << "座位总数: " << flight.seats << endl;
    cout << "剩余座位数: " << flight.availableSeats << endl;
    cout << "票价: " << fixed << setprecision(2) << flight.price << endl;
    cout << "-----------------------------------------" << endl;
}

// 修改航班信息
void FlightManager::ModifyFlight() {
    string flightNo;
    cout << "请输入要修改的航班号: ";
    cin >> flightNo;
    Flight* flight = FindFlight(flightNo);
    if(!flight){
        cout << "未找到该航班。" << endl;
        return;
    }
    cout << "请选择要修改的内容：" << endl;
    cout << "1. 起飞时间" << endl;
    cout << "2. 票价" << endl;
    cout << "3. 取消" << endl;
    int choice;
    cin >> choice;
    switch(choice){
        case 1:
            cout << "当前起飞时间: " << flight->departureTime << endl;
            cout << "请输入新的起飞时间 (格式: YYYY-MM-DD_HH:MM): ";
            cin >> flight->departureTime;
            cout << "起飞时间已更新。" << endl;
            break;
        case 2:
            cout << "当前票价: " << fixed << setprecision(2) << flight->price << endl;
            cout << "请输入新的票价: ";
            cin >> flight->price;
            cout << "票价已更新。" << endl;
            break;
        case 3:
            cout << "修改已取消。" << endl;
            break;
        default:
            cout << "无效的选择。" << endl;
            break;
    }
}

// 查找航班
Flight* FlightManager::FindFlight(const string &flightNo) {
    int len = flightList.GetLength();
    for(int i=1; i<=len; ++i){
        Flight flight;
        flightList.GetElem(i, flight);
        if(flight.flightNo == flightNo){
            // 返回找到的航班的引用
            // 为了简化实现，这里返回堆上的副本
            Flight* foundFlight = new Flight(flight);
            return foundFlight;
        }
    }
    return NULL;
}

// 实现PassengerManager类的成员函数

// 加载乘客信息
void PassengerManager::LoadPassengers(const string &filename) {
    ifstream infile(filename.c_str());
    if (!infile) {
        cout << "无法打开乘客信息文件 " << filename << "！" << endl;
        return;
    }
    Passenger passenger;
    while (infile >> passenger.name >> passenger.id >> passenger.phone >> passenger.vipLevel) {
        passengerList.InsertElem(passenger);
    }
    infile.close();
}

// 保存乘客信息
void PassengerManager::SavePassengers(const string &filename) {
    ofstream outfile(filename.c_str());
    if (!outfile) {
        cout << "无法打开乘客信息文件 " << filename << " 进行写入！" << endl;
        return;
    }
    int len = passengerList.GetLength();
    for(int i=1; i<=len; ++i){
        Passenger passenger;
        passengerList.GetElem(i, passenger);
        outfile << passenger.name << " " << passenger.id << " " << passenger.phone << " " << passenger.vipLevel << endl;
    }
    outfile.close();
}

// 添加乘客
void PassengerManager::AddPassenger() {
    Passenger passenger;
    cout << "请输入乘客姓名: ";
    cin >> passenger.name;
    cout << "请输入乘客身份证号: ";
    cin >> passenger.id;
    cout << "请输入乘客联系电话: ";
    cin >> passenger.phone;
    cout << "请输入VIP等级（0: 非VIP, 1: VIP青春版, 2: VIP Pro, 3: VIP Pro Max）: ";
    cin >> passenger.vipLevel;
    passengerList.InsertElem(passenger);
    cout << "乘客信息添加成功！" << endl;
}

// 查找乘客
Passenger* PassengerManager::FindPassenger(const string &id) {
    int len = passengerList.GetLength();
    for(int i=1; i<=len; ++i){
        Passenger passenger;
        passengerList.GetElem(i, passenger);
        if(passenger.id == id){
            // 返回找到的乘客的引用
            // 为了简化实现，这里返回堆上的副本
            Passenger* foundPassenger = new Passenger(passenger);
            return foundPassenger;
        }
    }
    return NULL;
}

// 显示所有乘客信息
void PassengerManager::DisplayAllPassengers() {
    int len = passengerList.GetLength();
    if(len == 0){
        cout << "当前没有乘客信息。" << endl;
        return;
    }
    for(int i=1; i<=len; ++i){
        Passenger passenger;
        passengerList.GetElem(i, passenger);
        cout << "-----------------------------------------" << endl;
        cout << "姓名: " << passenger.name << endl;
        cout << "身份证号: " << passenger.id << endl;
        cout << "联系电话: " << passenger.phone << endl;
        cout << "VIP等级: ";
        switch(passenger.vipLevel){
            case 0: cout << "非VIP"; break;
            case 1: cout << "VIP青春版"; break;
            case 2: cout << "VIP Pro"; break;
            case 3: cout << "VIP Pro Max"; break;
            default: cout << "未知"; break;
        }
        cout << endl;
        cout << "-----------------------------------------" << endl;
    }
}

// 实现BookingSystem类的成员函数

// 加载所有数据
void BookingSystem::LoadData() {
    flightManager.LoadFlights("flights.txt");
    passengerManager.LoadPassengers("passengers.txt");
    // 加载等待队列
    ifstream infile("waiting_queue.txt");
    if (!infile) {
        cout << "无法打开等待队列文件 waiting_queue.txt！" << endl;
        return;
    }
    WaitingPassenger wp;
    while (infile >> wp.flightNo >> wp.passengerId) {
        // 查找乘客VIP等级
        Passenger* pPassenger = passengerManager.FindPassenger(wp.passengerId);
        if(pPassenger){
            wp.vipLevel = pPassenger->vipLevel;
            waitingQueue.EnQueue(wp);
            delete pPassenger;
        }
    }
    infile.close();
}

// 保存所有数据
void BookingSystem::SaveData() {
    flightManager.SaveFlights("flights.txt");
    passengerManager.SavePassengers("passengers.txt");
    // 保存等待队列
    ofstream outfile("waiting_queue.txt");
    if (!outfile) {
        cout << "无法打开等待队列文件 waiting_queue.txt 进行写入！" << endl;
        return;
    }
    int len = waitingQueue.GetLength();
    // 为了遍历队列，我们需要临时队列
    LinkQueue<WaitingPassenger> tempQueue;
    WaitingPassenger wp;
    while(waitingQueue.DelQueue(wp)){
        outfile << wp.flightNo << " " << wp.passengerId << endl;
        tempQueue.EnQueue(wp);
    }
    // 将临时队列的数据恢复到原队列
    while(tempQueue.DelQueue(wp)){
        waitingQueue.EnQueue(wp);
    }
    outfile.close();
}

// 菜单界面
void BookingSystem::Menu() {
    int choice;
    while(true){
        cout << "\n========== 航空订票系统 ==========" << endl;
        cout << "1. 航班查询" << endl;
        cout << "2. 旅客订票" << endl;
        cout << "3. 旅客退票" << endl;
        cout << "4. 航班管理" << endl;
        cout << "5. 旅客管理" << endl;
        cout << "6. 退出系统" << endl;
        cout << "请输入您的选择: ";
        cin >> choice;
        switch(choice){
            case 1:
                FlightQuery();
                break;
            case 2:
                BookTicket();
                break;
            case 3:
                RefundTicket();
                break;
            case 4:
                ManageFlights();
                break;
            case 5:
                passengerManager.DisplayAllPassengers();
                break;
            case 6:
                cout << "正在保存数据并退出系统..." << endl;
                return;
            default:
                cout << "无效的选择，请重新输入。" << endl;
                break;
        }
    }
}

// 航班查询功能
void BookingSystem::FlightQuery() {
    flightManager.QueryFlight();
}

// 订票功能
void BookingSystem::BookTicket() {
    string flightNo, passengerId;
    cout << "请输入要订票的航班号: ";
    cin >> flightNo;
    cout << "请输入乘客身份证号: ";
    cin >> passengerId;

    // 查找航班
    Flight* flight = flightManager.FindFlight(flightNo);
    if(!flight){
        cout << "航班信息不存在。" << endl;
        return;
    }

    // 查找乘客
    Passenger* pPassenger = passengerManager.FindPassenger(passengerId);
    if (!pPassenger) {
        cout << "乘客信息不存在，请先添加乘客信息。" << endl;
        cout << "是否添加新乘客？(Y/N): ";
        char choice;
        cin >> choice;
        if(choice == 'Y' || choice == 'y'){
            passengerManager.AddPassenger();
            // 重新查找
            pPassenger = passengerManager.FindPassenger(passengerId);
            if(!pPassenger){
                cout << "添加乘客失败。" << endl;
                return;
            }
        }
        else{
            return;
        }
    }

    // 判断是否有余票
    if(flight->availableSeats > 0){
        flight->availableSeats -=1;
        // 更新航班信息
        // 为了简化实现，这里直接更新航班列表
        int len = flightManager.flightList.GetLength();
        for(int i=1; i<=len; ++i){
            Flight tempFlight;
            flightManager.flightList.GetElem(i, tempFlight);
            if(tempFlight.flightNo == flight->flightNo){
                flightManager.flightList.SetElem(i, *flight);
                break;
            }
        }
        cout << "订票成功！" << endl;
    }
    else{
        cout << "当前航班已无余票，是否加入等待队列？(Y/N): ";
        char choice;
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            WaitingPassenger wp;
            wp.flightNo = flightNo;
            wp.passengerId = passengerId;
            wp.vipLevel = pPassenger->vipLevel;
            waitingQueue.EnQueue(wp);
            cout << "已加入等待队列。" << endl;
        }
        else{
            cout << "已取消订票。" << endl;
        }
    }

    delete flight;
    delete pPassenger;
}

// 退票功能
void BookingSystem::RefundTicket() {
    string flightNo, passengerId;
    cout << "请输入要退票的航班号: ";
    cin >> flightNo;
    cout << "请输入乘客身份证号: ";
    cin >> passengerId;

    // 查找航班
    Flight* flight = flightManager.FindFlight(flightNo);
    if(!flight){
        cout << "航班信息不存在。" << endl;
        return;
    }

    // 假设乘客已经订票，直接增加一张座位
    flight->availableSeats +=1;
    // 更新航班信息
    int len = flightManager.flightList.GetLength();
    for(int i=1; i<=len; ++i){
        Flight tempFlight;
        flightManager.flightList.GetElem(i, tempFlight);
        if(tempFlight.flightNo == flight->flightNo){
            flightManager.flightList.SetElem(i, *flight);
            break;
        }
    }
    cout << "退票成功！" << endl;

    // 处理等待队列
    HandleWaitingList(flightNo);

    delete flight;
}

// 管理航班功能
void BookingSystem::ManageFlights() {
    int choice;
    while(true){
        cout << "\n---------- 航班管理 ----------" << endl;
        cout << "1. 添加航班" << endl;
        cout << "2. 显示所有航班" << endl;
        cout << "3. 修改航班信息" << endl;
        cout << "4. 返回主菜单" << endl;
        cout << "请输入您的选择: ";
        cin >> choice;
        switch(choice){
            case 1:
                flightManager.AddFlight();
                break;
            case 2:
                flightManager.DisplayAllFlights();
                break;
            case 3:
                flightManager.ModifyFlight();
                break;
            case 4:
                return;
            default:
                cout << "无效的选择，请重新输入。" << endl;
                break;
        }
    }
}

// 处理等待队列
void BookingSystem::HandleWaitingList(const string &flightNo) {
    // 遍历等待队列，找到该航班的等待乘客
    // 将符合条件的乘客订票，并调整航班座位
    LinkQueue<WaitingPassenger> tempQueue;
    WaitingPassenger wp;
    bool seatAssigned = false;

    while(!waitingQueue.IsEmpty()){
        waitingQueue.DelQueue(wp);
        if(wp.flightNo == flightNo && !seatAssigned && flightNo != ""){
            // 优先级高的乘客优先
            // 这里简单处理，假设队列已经按照VIP等级排序
            // 实际应用中可能需要更复杂的排序
            // 查找乘客信息
            Passenger* pPassenger = passengerManager.FindPassenger(wp.passengerId);
            if(pPassenger && pPassenger->vipLevel > 0){
                // 订票
                // 查找航班
                Flight* flight = flightManager.FindFlight(flightNo);
                if(flight && flight->availableSeats > 0){
                    flight->availableSeats -=1;
                    // 更新航班信息
                    int len = flightManager.flightList.GetLength();
                    for(int i=1; i<=len; ++i){
                        Flight tempFlight;
                        flightManager.flightList.GetElem(i, tempFlight);
                        if(tempFlight.flightNo == flight->flightNo){
                            flightManager.flightList.SetElem(i, *flight);
                            break;
                        }
                    }
                    cout << "等待队列中的VIP乘客 " << pPassenger->name << " 订票成功！" << endl;
                    seatAssigned = true;
                }
                delete flight;
            }
            delete pPassenger;
        }
        else{
            tempQueue.EnQueue(wp);
        }
    }

    // 恢复等待队列
    while(tempQueue.DelQueue(wp)){
        waitingQueue.EnQueue(wp);
    }
}

// 主函数
int main() {
    BookingSystem system;
    system.LoadData();
    system.Menu();
    system.SaveData();
    cout << "系统已成功退出。" << endl;
    return 0;
}