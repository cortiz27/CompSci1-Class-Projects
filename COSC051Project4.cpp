/*
* main.cpp
*
* COSC 051 Spring 2020
* Project #4
*
* Due on: 12 April 2020
* Author: <clo42>
*
* In accordance with the class policies and Georgetown’s Honor Code,
* I certify that, with the exception of the class resources and those
* items noted below, I have neither given nor received any assistance
* on this project.
*
* References not otherwise commented within the program source code.
* Note that you should not mention help from our TAs, professors, or
* any code taken from the course textbook.
*/
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

/*Constants*/
double const PlasticCost = .14,
        AluminumCost = .39,
        CarbonCost = 1.35,
        minVal = 0.45,
        maxVal = 7.62,
        markUp = 1.19;


/********************************************************************************
*                ShapeOrder class declaration                                  *
********************************************************************************/

class ShapeOrder
{
    // Friend Operator Overloading Functions
    friend ostream& operator<<( ostream &os, const ShapeOrder &rhsObj );
    friend istream& operator>>( istream &in, ShapeOrder &rhsObj );
private:
    // Member Data
    string reg;
    char sCode;
    char mCode;
    string color;
    double a;
    double c;
    double r;
    string custNumber;

public:

    // Constructors
    ShapeOrder();
    ShapeOrder(string reg, char sc, char mc, string col,
               double semiA, double semiC, double rad, string custNum);
    ShapeOrder( const ShapeOrder& otherOrder );

    // Member Assignment Operator Overloading Prototype
    ShapeOrder& operator=( const ShapeOrder& otherOrder );



    // Basic Mutator Functions,
    // you may change parameter identifiers but NOT the function identifiers

    void setRegion( string region ) { reg = region; }
    void setShapeCode( char shapeCode ) { sCode = shapeCode; }
    void setMaterialCode( char materialCode ) { mCode = materialCode; }
    void setColor( string colour ) { color = colour; }
    void setSemiAxisA( double semiAxisA ) { a = semiAxisA; }
    void setSemiAxisC( double semiAxisC ) { c = semiAxisC; }
    void setRadius( double radius ) { r = radius; }
    void setCustomerNumber( string customerNumber ) { custNumber = customerNumber; }


    // Basic Accessor Functions,
    // you may change parameter identifiers but NOT the function identifiers

    string getRegion() const { return reg; }
    char getShapeCode() const { return sCode; }
    char getMaterialCode() const { return mCode; }
    string getColor() const { return color; }
    double getSemiAxisA() const { return a; }
    double getSemiAxisC() const { return c; }
    double getRadius() const { return r; }
    string getCustomerNumber() const { return custNumber; }


    // required accessor functions that perform more detailed calculations,
    // you may NOT change the function identifiers
    double getMaterialCost() const;
    double getLaborCost() const;
    double getManufacturingCost() const;
    double getSalesPrice() const;
    double getProfit() const;
    double getVolume() const;
    double getSurfaceArea() const;
    string getShapeName() const;



}; // END declaration of class ShapeOrder


/********************************************************************************
*                           Function Prototypes                                 *
********************************************************************************/

char displayMenu();
void uploadFile(string fName, bool& loadSuccess,
                vector<ShapeOrder>& shapeOrders);
void allDetails(const vector<ShapeOrder>& shapeOrders);
void customerDetails(const vector<ShapeOrder>& shapeOrders);
void summaryByShape(const vector<ShapeOrder>& shapeOrders);
void summaryByRegion(const vector<ShapeOrder>& shapeOrders);
void clearAllVectors(vector<ShapeOrder>& shapeOrders);

// End of Function Prototypes

/********************************************************************************
*                              Main Function                                    *
********************************************************************************/


int main() {
    string fName;
    bool loadSuccess;
    bool incomplete;
    vector<ShapeOrder> shapeOrders;
    do {
        char choice = displayMenu();
        if (choice == 'u') {
            cout << "Please type in the Customer Data Filepath:" << endl;
            cin >> fName;
            uploadFile(fName, loadSuccess, shapeOrders);
            incomplete = false;
        }else if (choice == 'a') {
            allDetails(shapeOrders);
            incomplete = false;
        }else if (choice == 'i') {
            customerDetails(shapeOrders);
            incomplete = false;
        }else if (choice == 'r'){
            summaryByRegion(shapeOrders);
            incomplete = false;
        }else if (choice == 's'){
            summaryByShape(shapeOrders);
            incomplete = false;
        }else if (choice == 'c')
            clearAllVectors(shapeOrders);
        incomplete = false;
    } while (!incomplete);
    return 0;
}
    // End of Main Function



/********************************************************************************
*                 ShapeOrder Member Function Definitions                        *
********************************************************************************/

double ShapeOrder::getMaterialCost() const
{
    char Material = mCode;
    double m_cost;
    double SA = getSurfaceArea();
    if (Material == 'p')
    {
        m_cost = PlasticCost*SA;
        return m_cost;
    }
    else if (Material == 'a')
    {
        m_cost = AluminumCost*SA;
        return m_cost;
    }
    else if (Material == 'c')
    {
        m_cost = CarbonCost*SA;
        return m_cost;
    }
}
double ShapeOrder::getLaborCost() const
{
    double labor_cost;
    char Material = mCode;
    if (Material == 'p')
    {
        labor_cost = 32.76 + (.19*(getMaterialCost()));
        return labor_cost;
    }
    else if (Material == 'a')
    {
        labor_cost = 80.13 + (.29*(getMaterialCost()));
        return labor_cost;
    }
    else if (Material == 'c')
    {
        labor_cost = 126.49 + (.49*(getMaterialCost()));
        return labor_cost;
    }
}
double ShapeOrder::getManufacturingCost() const
{
    double manufacturing_cost;
    manufacturing_cost = (getMaterialCost()) + (getLaborCost());
    return manufacturing_cost;
}
double ShapeOrder::getSalesPrice() const
{
    double sale_price;
    sale_price = (markUp*(getManufacturingCost()));
    return sale_price;
}
double ShapeOrder::getProfit() const
{
    double profit;
    profit = getSalesPrice() - getManufacturingCost();
    return profit;
}
double ShapeOrder::getVolume() const
{
    double semiA = a;
    double semiC = c;
    double Radius = r;
    double Volume;

    if (semiA > semiC)
    {
        Volume = (4*(M_PI)*pow(semiA, 2)*semiC)/3;
        return Volume;
    }
    else if (semiC > semiA)
    {
        Volume = (4*(M_PI)*pow(semiA, 2)*semiC)/3;
        return Volume;
    }
    else if (Radius > minVal && Radius < maxVal)
    {
        Volume = (4*(M_PI)*pow(Radius, 3))/3;
        return Volume;
    }
}
double ShapeOrder::getSurfaceArea() const
{
    double semiA = a;
    double semiC = c;
    double Radius = r;
    double SA;

    //Surface Area Stuff

    if (semiA > semiC)
    {
        double e = sqrt(1 - pow(semiC, 2)/pow(semiA, 2));
        SA = (2*(M_PI)*pow(semiA, 2)) + ((M_PI)*(pow(semiC, 2)/e)*log((1+e)/(1-e)));
        return SA;
    }
    else if (semiC > semiA)
    {
        double e = sqrt(1 - (pow(semiA, 2)/pow(semiC, 2)));
        SA = (2*(M_PI)*pow(semiA, 2))*(1+(semiC/(semiA*e))*asin(e));
        return SA;
    }
    else if (Radius > minVal && Radius < maxVal)
    {
        SA = 4 * (M_PI) * pow(Radius, 2);
        return SA;
    }
}
string ShapeOrder::getShapeName() const
{
    if (sCode == 's') { return "Sphere";}
    else if (sCode == 'o') { return "Oblate Spheroid";}
    else if (sCode == 'p') { return "Prolate Spheroid";}
}
    // End of Member Function Definitions


/********************************************************************************
*                  Operator Overloading Definitions                             *
********************************************************************************/

ostream& operator<<( ostream &os, const ShapeOrder &rhsObj )
{
    os << fixed << setprecision(2);
    os << setw(12) << rhsObj.getRegion();
    os << setw(12) << rhsObj.getShapeCode();
    os << setw(12) << rhsObj.getMaterialCode();
    os << setw(12) << rhsObj.getColor();
    os << setw(12) << rhsObj.getSemiAxisA();
    os << setw(12) << rhsObj.getSemiAxisC();
    os << setw(12) << rhsObj.getRadius();
    os << setw(17) << rhsObj.getCustomerNumber();
    os << setw(12) << rhsObj.getManufacturingCost();
    os << setw(12) << rhsObj.getSalesPrice();
    os << setw(12) << rhsObj.getProfit() << endl;
    return os;
}
istream& operator>>( istream &in, ShapeOrder &rhsObj )
{
    int row_year, row_month, row_day;
    char row_char;
    string row_state, row_region, oColor,
            customer_num, customer_fname, customer_lname, customer_address;
    char Shape, Material;
    double semiA, semiC, Radius;
    in >> row_state >> row_region >> row_year >> row_char >> row_month >> row_char >> row_day >>
                 Shape >> Material >> oColor >> semiA >> semiC >> Radius >> customer_num >> customer_fname >>
                 customer_lname && getline(in, customer_address);
    Shape = tolower(Shape);
    Material = tolower(Material);
    rhsObj.setRegion(row_region);
    rhsObj.setShapeCode(Shape);
    rhsObj.setMaterialCode(Material);
    rhsObj.setColor(oColor);
    rhsObj.setSemiAxisA(semiA);
    rhsObj.setSemiAxisC(semiC);
    rhsObj.setRadius(Radius);
    rhsObj.setCustomerNumber(customer_num);
    return in;
}
ShapeOrder& ShapeOrder::operator=( const ShapeOrder& otherOrder )
{
    reg = otherOrder.getRegion();
    sCode = otherOrder.getShapeCode();
    mCode = otherOrder.getMaterialCode();
    color = otherOrder.getColor();
    a = otherOrder.getSemiAxisA();
    c = otherOrder.getSemiAxisC();
    r = otherOrder.getRadius();
    custNumber = otherOrder.getCustomerNumber();
    return *this;
}
    // End of Overloading Definition

/********************************************************************************
*                   Copy Constructor Definitions                                *
********************************************************************************/

ShapeOrder::ShapeOrder()
{
    reg = "";
    sCode = ' ';
    mCode = ' ';
    color = "";
    a = 0;
    c = 0;
    r = 0;
    custNumber = "";
}
ShapeOrder::ShapeOrder(string reg, char sc, char mc, string col,
double semiA, double semiC, double rad, string custNum)
{
    reg = reg;
    sCode = sc;
    mCode = mc;
    color = col;
    a = semiA;
    c = semiC;
    r = rad;
    custNumber = custNum;
}
ShapeOrder::ShapeOrder( const ShapeOrder& otherOrder )
{
    reg = otherOrder.getRegion();
    sCode = otherOrder.getShapeCode();
    mCode = otherOrder.getMaterialCode();
    color = otherOrder.getColor();
    a = otherOrder.getSemiAxisA();
    c = otherOrder.getSemiAxisC();
    r = otherOrder.getRadius();
    custNumber = otherOrder.getCustomerNumber();
}

/********************************************************************************
*                      Menu Function Definitions                                *
********************************************************************************/

char displayMenu()
{
    string input;
    char cInput;

    bool menuOptionValidation = true;
    do {
        cout << "_________________________________________________________________________________________" << endl;

        cout << "Hello, Please Select from the Following Options by Entering the Single Assigned Character:" << endl;
        cout << "_________________________________________________________________________________________" << endl;
        cout << "-Upload a Regional Sales Data File (U)" << endl;
        cout << "-Display Details (All Loaded Data) (A)" << endl;
        cout << "-List Sales for Specific Customer ID (I)" << endl;
        cout << "-Display Summary by Region (R)" << endl;
        cout << "-Display Summary by Shape Code (S)" << endl;
        cout << "-Clear All Vectors (C)" << endl;
        cout << "-Quit (Q)" << endl;

        cin >> input;
        cInput = input[0];
        cin.ignore(300, '\n');
        cInput = tolower(cInput);

        if (cInput=='q'){
            menuOptionValidation = false;
            exit(EXIT_SUCCESS);}
        else if(cInput!='u' && cInput!='a' && cInput!='i' && cInput!='r' && cInput!='s' && cInput!='c'){
            cout << "**Invalid Entry: Please enter appropriate character for the desired option.**" << endl;
            menuOptionValidation = false;}


    } while (!menuOptionValidation);
    return cInput;
}
void uploadFile(string fName, bool& loadSuccess,
                vector<ShapeOrder>& shapeOrders)
{
    string secondline_heading, thirdline_heading, junk;
    int file_year, file_month, file_day;
    char file_datechar;
    ifstream customerfile;

    customerfile.open(fName.c_str()); //maybe .c_str()

    if (!customerfile) {
        cout << "Error: Customer Data File was unable to open, file will not be processed." << endl;
        loadSuccess = false;
        return;
    }

    //Reads first line, stores date into different fields, and validates date
    //Second and Third Lines are Column Headings that aren't processed
    customerfile >> file_year >> file_datechar >> file_month >> file_datechar >> file_day;
    getline(customerfile, junk);
    getline(customerfile, secondline_heading);
    getline (customerfile, thirdline_heading);

    if (file_month < 1 || file_month > 12)
        return;
    if (file_day < 1 || file_day > 31)
        return;

    // Object Creation Through Read In Operator
    while (!customerfile.eof())
    {
        ShapeOrder order;
        // Boolean Declarations GO HERE:
        bool shapevalidation = true, materialvalidation = true,
                colorvalidation = true, semiAvalidation = true, semiCvalidation = true, radiusvalidation = true;
        // Line Read-In:
        customerfile >> order;


        if(customerfile.eof()) break; //Break??
        char Shape = order.getShapeCode();
        char Material = order.getMaterialCode();
        string oColor = order.getColor();

        /********************************************************************************
        *                      Data Validation Goes Here                                *
        ********************************************************************************/
        //Shape Validation
        if (Shape != 'o' && Shape != 'p' && Shape != 's'){
            shapevalidation = false;
        }

        //Material Validation
        if (Material != 'a' && Material != 'p' && Material != 'c') {
            materialvalidation = false;
        }

        //Color Validation
        if (oColor != "Red" && oColor != "Orange" && oColor != "Yellow" && oColor != "Green" &&
            oColor != "Blue" && oColor != "Indigo" && oColor != "Violet") {
            colorvalidation = false;
        }

        //SemiA Validation while Prolate
        if (Shape == 'p' && order.getSemiAxisC() > order.getSemiAxisA())
        {
            if (order.getSemiAxisA() < minVal || order.getSemiAxisA() > maxVal ||
            order.getSemiAxisC() > 1.95*(order.getSemiAxisA()))
                semiAvalidation = false;
        }

        //SemiC Validation while Oblate
        if (Shape == 'o' && order.getSemiAxisC() < order.getSemiAxisA())
        {
            if (order.getSemiAxisC() < minVal || order.getSemiAxisC() > maxVal ||
            (order.getSemiAxisC())*1.95 < order.getSemiAxisA())
                semiCvalidation = false;
        }

        //Radius validation
        if (Shape == 's')
        {
            if (order.getRadius() < minVal && order.getRadius() > maxVal)
                radiusvalidation = false;
        }


        if (shapevalidation == false)
            cout << endl << "The Shape Entry is not valid" << endl;
        if (materialvalidation == false)
            cout << endl << "The Material entry is not valid" << endl;
        if (colorvalidation == false)
            cout << endl << "The Color entry is not valid" << endl;
        if (semiAvalidation == false)
            cout << endl << "The Semiaxis A is outside the limits" << endl;
        if (semiCvalidation == false)
            cout << endl << "The Semiaxis C is outside the limits" << endl;
        if (radiusvalidation == false)
            cout << endl << "The Radius is outside the limits" << endl;
        if (shapevalidation == false || materialvalidation == false ||
            colorvalidation == false || semiAvalidation == false ||
            semiCvalidation == false|| radiusvalidation == false)
            cout << order.getRegion() << " Region office must contact order w/ customerID: "
            <<order.getCustomerNumber() << " to resolve the issues" << endl;

        if ( (shapevalidation == true) && (materialvalidation == true) &&
            (colorvalidation == true) && (semiAvalidation == true) && (semiCvalidation == true)
            && (radiusvalidation == true))
        {
            shapeOrders.push_back(order);
            loadSuccess = true;
        }
    }
    customerfile.close();
}
void allDetails(const vector<ShapeOrder>& shapeOrders)
{
    // Validation Check here to see if order vector are empty
    // If vector isnt empty
    int vectorSize = shapeOrders.size();
    int x;
    string dash = "-";
    cout << setw(12) << "Region";
    cout << setw(12) << "Shape";
    cout << setw(12) << "Material";
    cout << setw(12) << "Color";
    cout << setw(12) << "Semiaxis A";
    cout << setw(12) << "Semiaxis C";
    cout << setw(12) << "Radius";
    cout << setw(17) << "Customer Number";
    cout << setw(12) << "Cost";
    cout << setw(12) << "Price";
    cout << setw(12) << "Profit" << endl;
    dash.assign(180, '-');
    cout << dash << endl;
    for(x=0; x<vectorSize; x++)
    {
        // overloaded output
        cout << shapeOrders.at(x);
    }
}
void customerDetails(const vector<ShapeOrder>& shapeOrders)
{
    // Validation Check here to see if order vector are empty
    // If vector isnt empty
    string customerId;
    string custId;
    int vectorSize;
    int accumulator = 0;
    cout << "Please Enter a Customer ID:" << endl;
    cin >> customerId;
    vectorSize = shapeOrders.size();
    for(int x=0; x<vectorSize; x++)
    {
        custId = shapeOrders.at(x).getCustomerNumber();
        if (customerId != custId)
        {
            accumulator++;
            if (accumulator == vectorSize)
            {
                cout << "There are No Orders Matching this Customer ID" << endl;
                return;
            }
        }
    }
    string dash = "-";
    cout << setw(12) << "Region";
    cout << setw(12) << "Shape";
    cout << setw(12) << "Material";
    cout << setw(12) << "Color";
    cout << setw(12) << "Semiaxis A";
    cout << setw(12) << "Semiaxis C";
    cout << setw(12) << "Radius";
    cout << setw(17) << "Customer Number";
    cout << setw(12) << "Cost";
    cout << setw(12) << "Price";
    cout << setw(12) << "Profit" << endl;
    dash.assign(180, '-');
    cout << dash << endl;
    for(int x=0; x<vectorSize; x++)
    {
        custId = shapeOrders.at(x).getCustomerNumber();
        if (customerId == custId)
        {
            cout << "For order(s) " << customerId << ':' << endl;
            cout << shapeOrders.at(x);
        }
    }
}
void summaryByShape(const vector<ShapeOrder>& shapeOrders) {
    double o_cost_counter = 0, p_cost_counter = 0, s_cost_counter = 0, o_price_counter = 0,
            p_price_counter = 0, s_price_counter = 0,
            o_profit_counter = 0, p_profit_counter = 0, s_profit_counter = 0;
    double manufacturing_cost, sale_price, profit;
    int oblate_counter = 0;
    int prolate_counter = 0;
    int sphere_counter = 0;
    // Validation Check here to see if order vector are empty
    // If vector isnt empty
    for (int x = 0; x < shapeOrders.size(); x++) {
        manufacturing_cost = shapeOrders.at(x).getManufacturingCost();
        sale_price = shapeOrders.at(x).getSalesPrice();
        profit = shapeOrders.at(x).getProfit();

        //Cost, Price, and Profit Accumulator per shape
        if (shapeOrders.at(x).getShapeCode() == 'o') {
            oblate_counter++;
            o_cost_counter += manufacturing_cost;
            o_price_counter += sale_price;
            o_profit_counter += profit;
        } else if (shapeOrders.at(x).getShapeCode() == 'p') {
            prolate_counter++;
            p_cost_counter += manufacturing_cost;
            p_price_counter += sale_price;
            p_profit_counter += profit;
        } else if (shapeOrders.at(x).getShapeCode() == 's') {
            sphere_counter++;
            s_cost_counter += manufacturing_cost;
            s_price_counter += sale_price;
            s_profit_counter += profit;

        }
    }
    cout << "Summary Totals by Shape: " << endl;
    cout << endl;
    cout << endl;
    cout << setw(15) << "Shape" << ' ' << setw(15) << "Number" << ' ' << setw(15) << "Cost" << ' '
         << setw(15) << "Price" << ' ' << setw(15) << "Profit" << endl;
    string dash = "-";
    dash.assign(90, '-');
    cout << dash << endl;
    cout << setw(15) << "Oblate" << ' ' << setw(15) << oblate_counter << ' '
         << fixed << setprecision(2) << setw(15) << o_cost_counter << ' ' << fixed
         << setprecision(2) << setw(15)
         << o_price_counter << ' ' << setw(15) << o_profit_counter << endl;
    cout << setw(15) << "Prolate" << ' ' << setw(15) << prolate_counter << ' ' <<
         fixed << setprecision(2) << setw(15) << p_cost_counter << ' ' << fixed
         << setprecision(2) << setw(15)<< p_price_counter << ' ' << fixed
         << setprecision(2) << setw(15) << p_profit_counter << endl;
    cout << setw(15) << "Sphere" << ' ' << setw(15) << sphere_counter << ' ' <<
         fixed << setprecision(2) << setw(15) << s_cost_counter << ' ' << fixed
         << setprecision(2) << setw(15)<< s_price_counter << ' ' << fixed
         << setprecision(2) << setw(15) << s_profit_counter << endl;
    cout << dash << endl;
}
void summaryByRegion(const vector<ShapeOrder>& shapeOrders)
{
    int north_counter = 0, n_cost_counter = 0, n_price_counter = 0, n_profit_counter = 0;
    int south_counter = 0, s_cost_counter = 0, s_price_counter = 0, s_profit_counter = 0;
    int west_counter = 0, w_cost_counter = 0, w_price_counter = 0, w_profit_counter = 0;
    int east_counter = 0, e_cost_counter = 0, e_price_counter = 0, e_profit_counter = 0;
    int other_counter = 0, o_cost_counter = 0, o_price_counter = 0, o_profit_counter = 0;
    double manufacturing_cost, sale_price, profit;
    string region;
    // Validation Check here to see if order vector are empty
    // If vector isnt empty
    for (int x = 0; x < shapeOrders.size(); x++)
    {
        manufacturing_cost = shapeOrders.at(x).getManufacturingCost();
        sale_price = shapeOrders.at(x).getSalesPrice();
        profit = shapeOrders.at(x).getProfit();
        region = shapeOrders.at(x).getRegion();

        //Cost, Price, and Profit Accumulator per Region
        if (region == "North") {
            north_counter++;
            n_cost_counter += manufacturing_cost;
            n_price_counter += sale_price;
            n_profit_counter += profit;
        } else if (region == "South") {
            south_counter++;
            s_cost_counter += manufacturing_cost;
            s_price_counter += sale_price;
            s_profit_counter += profit;
        } else if (region == "West") {
            west_counter++;
            w_cost_counter += manufacturing_cost;
            w_price_counter += sale_price;
            w_profit_counter += profit;
        } else if (region == "East") {
            east_counter++;
            e_cost_counter += manufacturing_cost;
            e_price_counter += sale_price;
            e_profit_counter += profit;
        } else if (region == "Other") {
            other_counter++;
            o_cost_counter += manufacturing_cost;
            o_price_counter += sale_price;
            o_profit_counter += profit;
        }


    }
    cout << "Summary Totals by Region: " << endl;
    cout << endl;
    cout << endl;
    cout << setw(15) << "Region" << ' ' << setw(15) << "Number" << ' ' << setw(15) << "Cost" << ' '
         << setw(15) << "Price" << ' ' << setw(15) << "Profit" << endl;
    string dash = "-";
    dash.assign(90, '-');
    cout << dash << endl;
    cout << setw(15) << "North" << ' ' << setw(15) << north_counter << ' '
         << fixed << setprecision(2) << setw(15) << n_cost_counter << ' ' << fixed
         << setprecision(2) << setw(15)
         << n_price_counter << ' ' << setw(15) << n_profit_counter << endl;
    cout << setw(15) << "South" << ' ' << setw(15) << south_counter << ' ' <<
         fixed << setprecision(2) << setw(15) << s_cost_counter << ' ' << fixed
         << setprecision(2) << setw(15) << s_price_counter << ' ' << fixed
         << setprecision(2) << setw(15) << s_profit_counter << endl;
    cout << setw(15) << "East" << ' ' << setw(15) << east_counter << ' ' <<
         fixed << setprecision(2) << setw(15) << e_cost_counter << ' ' << fixed << setprecision(2)
         << setw(15) << e_price_counter << ' ' << fixed << setprecision(2) << setw(15)
         << e_profit_counter << endl;
    cout << setw(15) << "West" << ' ' << setw(15) << west_counter << ' ' <<
         fixed << setprecision(2) << setw(15) << w_cost_counter << ' ' << fixed << setprecision(2)
         << setw(15) << w_price_counter << ' ' << fixed << setprecision(2) << setw(15)
         << w_profit_counter << endl;
    cout << setw(15) << "Other" << ' ' << setw(15) << other_counter << ' ' <<
         fixed << setprecision(2) << setw(15) << o_cost_counter << ' ' << fixed << setprecision(2)
         << setw(15) << o_price_counter << ' ' << fixed << setprecision(2) << setw(15)
         << o_profit_counter << endl;
    cout << dash << endl;
}
void clearAllVectors(vector<ShapeOrder>& shapeOrders)
{
    shapeOrders.clear();
}
    // End of Menu Function Definitions
