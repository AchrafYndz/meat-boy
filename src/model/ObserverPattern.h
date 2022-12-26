#ifndef INC_2022_PROJECT_ACHRAFYNDZ_OBSERVERPATTERN_H
#define INC_2022_PROJECT_ACHRAFYNDZ_OBSERVERPATTERN_H

#include <vector>
#include <memory>
#include <iostream>

// The Observer class defines an interface for observing the Player's state
class Observer {
public:
	virtual ~Observer() = default;

	// This method is called when the Player's state changes
	virtual void update(int x, int y) = 0;
};

// The Subject class allows Observers to register and be notified of changes
class Subject {
public:
	// Register an Observer to be notified of changes
	void registerObserver(std::shared_ptr<Observer> observer) {
		observers.push_back(observer);
	}

	// Notify all registered Observers of a change
	void notifyObservers(int x, int y) {
		for (auto& observer : observers) {
			observer->update(x, y);
		}
	}

private:
	std::vector<std::shared_ptr<Observer>> observers;
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_OBSERVERPATTERN_H
