#pragma once

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
 private:
  virtual void AddObserver(
      std::initializer_list<const std::shared_ptr<IObserver>*> observers) = 0;

 public:
  virtual ~IObservered() = default;
};

class ObserveredCmd : public IObservered {
 public:
  void AddObserver(std::initializer_list<const std::shared_ptr<IObserver>*>
                       observers) override {
    for (const auto& observer : observers) {
      _observers.push_back(*observer);
    }
  };

  void NotifyBlockEnd(const std::string& comands) {
    for (auto it = _observers.begin(); it != _observers.end(); ++it) {
      if (std::shared_ptr s_var = it->lock(); s_var) {
        s_var->UpdateEnd(comands);
      } else {
        _observers.erase(it);
      }
    }
  }

  void NotifyBlockStart() {
    for (auto it = _observers.begin(); it != _observers.end(); ++it) {
      if (std::shared_ptr s_var = it->lock(); s_var) {
        s_var->UpdateStart();
      } else {
        _observers.erase(it);
      }
    }
  }

 private:
  std::vector<std::weak_ptr<IObserver>> _observers;
};
