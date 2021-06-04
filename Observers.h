#pragma once
#include <vector>

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
private:
    std::vector<Observer*> v;
public:
    void addObeserv(Observer* obs) {
        v.push_back(obs);
    }

    void removeObserv(Observer* obs) {
        for (auto it = v.begin(); it != v.end(); it++)
            if (*it == obs) {
                v.erase(it);
                return;
            }
    }

    void notify() {
        for (auto& it : v) { it->update(); }
    }
};
