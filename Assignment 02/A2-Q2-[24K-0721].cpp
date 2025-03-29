#include <iostream>
using namespace std;

class Ghost {
protected:
    string workerName;
    int scareLevel; // RNG 1-10

public:

    Ghost() : workerName(""), scareLevel(0) {} // Default constructor
    Ghost(string workerName, int scareLevel) : workerName(workerName), scareLevel(scareLevel) {}

    virtual void haunt() {
        cout << "Ghost " << workerName << " is haunting." << endl;
    }

    friend ostream& operator<<(ostream& os, const Ghost &ghost) {
        os << "Ghost (Name: " << ghost.workerName << ", Scare Level: " << ghost.scareLevel << ")";
        return os;
    }
    
    Ghost operator+(const Ghost& ghost) {
        string combinedName = workerName + " & " + ghost.workerName;
        int combinedScareLevel = scareLevel + ghost.scareLevel;
        return Ghost(combinedName, combinedScareLevel);
    }

    int getScareLevel() { 
        return scareLevel; 
    }
};

class Poltergeist : public virtual Ghost {
public:
    Poltergeist(string workerName, int scareLevel) : Ghost(workerName, scareLevel) {}

    void haunt() {
        cout << "Poltergeist " << workerName << " is moving objects!" << endl;
    }
};

class Banshee : public Ghost {
public:
    Banshee(string workerName, int scareLevel) : Ghost(workerName, scareLevel) {}

    void haunt() {
        cout << "Banshee " << workerName << " is screaming loudly!" << endl;
    }
};

class ShadowGhost : public virtual Ghost {
public:
    ShadowGhost(string workerName, int scareLevel) : Ghost(workerName, scareLevel) {}

    void haunt() {
        cout << "ShadowGhost " << workerName << " is whispering creepily!" << endl;
    }
};

class ShadowPoltergeist : public Poltergeist, public ShadowGhost {
public:
    ShadowPoltergeist(string workerName, int scareLevel)
        : Ghost(workerName, scareLevel), Poltergeist(workerName, scareLevel), ShadowGhost(workerName, scareLevel) {}

    void haunt() {
        Poltergeist::haunt();
        ShadowGhost::haunt();
    }
};

class Visitor {
protected:
    string name;
    int bravery; // (1-4: Cowardly, 5-7: Average, 8-10: Fearless)

public:
    Visitor(string name, int bravery) : name(name), bravery(bravery) {}

    void reactToHaunt(int scareLevel) {
        if (scareLevel < bravery - 3) {
            cout << name << " laughs and taunts the ghost!" << endl;
        } else if (scareLevel > bravery + 3) {
            cout << name << " screams and runs away!" << endl;
        } else {
            cout << name << " gets a shaky voice!" << endl;
        }
    }

    string getName () {
        return name;
    }

    int getBravery () {
        return bravery;
    }
};

class HauntedHouse {
private:
    string houseName;
    Ghost* ghosts[10];
    int ghostCount;

public:
    HauntedHouse(string houseName) : houseName(houseName), ghostCount(0) {}

    void addGhost(Ghost* ghost) {
        if (ghostCount < 10) {
            ghosts[ghostCount++] = ghost;
        } else {
            cout << "Haunted House is full! Cannot add more ghosts." << endl;
        }
    }

    void hauntAll(Visitor& visitor) {
        for (int i = 0; i < ghostCount; i++) {
            ghosts[i]->haunt();
            visitor.reactToHaunt(ghosts[i]->getScareLevel());
        }
    }

    string getHouseName() {
        return houseName;
    }
};

void visit(Visitor visitors[], int visitorCount, HauntedHouse& house) {
    cout << "Visitors are entering the Haunted House: " << endl;
    for (int i = 0; i < visitorCount; i++) {
        cout << "Visitor " << i + 1 << ": " << visitors[i].getName() << " with bravery level " << visitors[i].getBravery() << endl;
    }
    house.hauntAll(visitors[0]);
    for (int i = 1; i < visitorCount; i++) {
        house.hauntAll(visitors[i]);
    }
}

int main() {
    HauntedHouse house1("221B Baker Street");
    HauntedHouse house2("Magnussen's Vault");

    Poltergeist poltergeist1("Sherlock", 5);
    Banshee banshee1("Moriarty", 8);
    ShadowGhost shadowGhost1("Mycroft", 3);

    Poltergeist poltergeist2("John", 6);
    Banshee banshee2("Irene", 7);
    ShadowGhost shadowGhost2("Mary", 4);

    house1.addGhost(&poltergeist1);
    house1.addGhost(&banshee1);
    house1.addGhost(&shadowGhost1);

    house2.addGhost(&poltergeist2);
    house2.addGhost(&banshee2);
    house2.addGhost(&shadowGhost2);

    Visitor visitors[] = {
        Visitor("Lestrade", 3), // Coward
        Visitor("Molly", 6),    // Average
        Visitor("Mrs. Hudson", 9) // Fearless
    };

    cout << "Visiting " << house1.getHouseName() << ":" << endl;
    visit(visitors, 3, house1);

    cout << "\nVisiting " << house2.getHouseName() << ":" << endl;
    visit(visitors, 3, house2);

    return 0;
}









