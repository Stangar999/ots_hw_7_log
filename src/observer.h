﻿#pragma once

#include <list>
#include <memory>
#include <vector>

class IObserver {
public:
    virtual void UpdateEnd(const std::string& comands) = 0;
    virtual void UpdateStart(){};
    virtual ~IObserver() = default;
};

class IObservered {
public:
    virtual void AddObserver(std::weak_ptr<IObserver> observer) = 0;
    virtual ~IObservered() = default;
};

class ObserveredCmd : public IObservered {
public:
    void AddObserver(std::weak_ptr<IObserver> observer) {
        _observers.push_back(observer);
    };
    void NotifyBlockEnd(const std::string& comands) {
        for(auto it = _observers.begin(); it != _observers.end(); ++it) {
            if(std::shared_ptr s_var = it->lock(); s_var) {
                s_var->UpdateEnd(comands);
            } else {
                _observers.erase(it);
            }
        }
    }

    void NotifyBlockStart() {
        for(auto it = _observers.begin(); it != _observers.end(); ++it) {
            if(std::shared_ptr s_var = it->lock(); s_var) {
                s_var->UpdateStart();
            } else {
                _observers.erase(it);
            }
        }
    }

private:
    std::list<std::weak_ptr<IObserver>> _observers;
};
