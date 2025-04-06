#include <iostream>
using namespace std;

class Pastry {
    protected:
        string pastryName;
        string ingredients[10];
        int ingredientCount;
        int productionCost;
        int taxRate; // in percentage
    
    public:
        Pastry() : pastryName(""), ingredientCount(0), productionCost(0), taxRate(10) {
            for (int i = 0; i < 10; i++) {
                ingredients[i] = "";
            }
        }

        virtual void totalCost() {
            int totalCost = productionCost + (productionCost * taxRate / 100);
            cout << "Total cost of " << pastryName << ": " << totalCost << endl;
        }

        virtual void retailPrice() {
            int retailPrice = productionCost + (productionCost * (taxRate + 10) / 100) + (productionCost * 6 / 100);
            cout << "Retail price of " << pastryName << ": " << retailPrice << endl;
        }

        virtual void profit() {
            int totalCost = productionCost + (productionCost * taxRate / 100);
            int retailPrice = productionCost + (productionCost * (taxRate + 10) / 100) + (productionCost * 6 / 100);
            int profit = (retailPrice - totalCost) * 70 / 100;
            cout << "Profit for " << pastryName << ": " << profit << endl;
        }

        friend void PastryCalculator(Pastry &p);
        friend class PastryReport;
};

void PastryCalculator(Pastry &p) {
    cout << "Enter the name of the pastry: ";
    cin >> p.pastryName;
    cout << "Enter the number of ingredients: ";
    cin >> p.ingredientCount;
    cout << "Enter the production cost: ";
    cin >> p.productionCost;

    for (int i = 0; i < p.ingredientCount; i++) {
        cout << "Enter ingredient " << i + 1 << ": ";
        cin >> p.ingredients[i];
    }

    cout << "Pastry details:" << endl;
    cout << "Name: " << p.pastryName << endl;
    cout << "Ingredients: ";
    for (int i = 0; i < p.ingredientCount; i++) {
        cout << p.ingredients[i] << " ";
    }
    cout << endl;
}

class SweetPastry : public Pastry {
    protected:
        int salesTaxRate = 8; // in percentage

    public:
        void totalCost() {
            int totalCost = productionCost + (productionCost * salesTaxRate / 100);
            cout << "Total cost of " << pastryName << ": " << totalCost << endl;
        }

        void retailPrice() {
            int retailPrice = productionCost + (productionCost * (salesTaxRate + 10) / 100) + (productionCost * 6 / 100);
            cout << "Retail price of " << pastryName << ": " << retailPrice << endl;
        }

        void profit() {
            int totalCost = productionCost + (productionCost * salesTaxRate / 100);
            int retailPrice = productionCost + (productionCost * (salesTaxRate + 10) / 100) + (productionCost * 6 / 100);
            int profit = (retailPrice - totalCost) * 70 / 100;
            cout << "Profit for " << pastryName << ": " << profit << endl;
        }
};

class SavoryPastry : public Pastry {
    protected:
        int salesTaxRate = 5; // in percentage
    
    public:
        void totalCost() {
            int totalCost = productionCost + (productionCost * salesTaxRate / 100);
            cout << "Total cost of " << pastryName << ": " << totalCost << endl;
        }

        void retailPrice() {
            int retailPrice = productionCost + (productionCost * (salesTaxRate + 10) / 100) + (productionCost * 6 / 100);
            cout << "Retail price of " << pastryName << ": " << retailPrice << endl;
        }

        void profit() {
            int totalCost = productionCost + (productionCost * salesTaxRate / 100);
            int retailPrice = productionCost + (productionCost * (salesTaxRate + 10) / 100) + (productionCost * 6 / 100);
            int profit = (retailPrice - totalCost) * 70 / 100;
            cout << "Profit for " << pastryName << ": " << profit << endl;
        }
};

class PastryReport {
    public:
        void generateReport(Pastry* pastries[], int count) {
            int totalProfit = 0;
            for (int i = 0; i < count; i++) {
                int totalCost = pastries[i]->productionCost + (pastries[i]->productionCost * pastries[i]->taxRate / 100);
                int retailPrice = pastries[i]->productionCost + (pastries[i]->productionCost * (pastries[i]->taxRate + 10) / 100) + (pastries[i]->productionCost * 6 / 100);
                int profit = (retailPrice - totalCost) * 70 / 100;
                totalProfit += profit;
            }
            cout << "Total profit from all pastries: " << totalProfit << endl;
        }
};

class PastryShop {
    private:
        Pastry* pastries[100]; // Fixed-size array
        int pastryCount;

    public:
        PastryShop() : pastryCount(0) {}

        void addPastry(Pastry *p) {
            if (pastryCount < 100) {
                pastries[pastryCount++] = p;
            } else {
                cout << "Pastry shop is full!" << endl;
            }
        }

        void calculateTotalProfit() {
            PastryReport report;
            report.generateReport(pastries, pastryCount);
        }
};



