#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

//Constants
double const PlasticCost = .14,
        AluminumCost = .39,
        CarbonCost = 1.35,
        minVal = 0.45,
        maxVal = 7.62,
        markUp = 1.19;


//Function Prototypes
char displayMenu();
void uploadFile(string fName, bool& loadSuccess,
                vector<string>& reg, vector<char>& sCode,
                vector<char>& mCode, vector<double>& a,
                vector<double>& c, vector<double>& r,
                vector<string>& color, vector<string>& custNumber);
void allDetails(const vector<string>& reg, const vector<char>& sCode,
                const vector<char>& mCode, const vector<double>& a,
                const vector<double>& c, const vector<double>& r,
                const vector<string>& color,
                const vector<string>& custNumber);
void customerDetails(const vector<string>& reg, const vector<char>& sCode,
                     const vector<char>& mCode, const vector<double>& a,
                     const vector<double>& c, const vector<double>& r,
                     const vector<string>& color,
                     const vector<string>& custNumber);
void summaryByShape(const vector<string>& reg, const vector<char>& sCode,
                    const vector<char>& mCode, const vector<double>& a,
                    const vector<double>& c, const vector<double>& r,
                    const vector<string>& color,
                    const vector<string>& custNumber);
void summaryByRegion(const vector<string>& reg, const vector<char>& sCode,
                     const vector<char>& mCode, const vector<double>& a,
                     const vector<double>& c, const vector<double>& r,
                     const vector<string>& color,
                     const vector<string>& custNumber);
void clearAllVectors(vector<string>& reg, vector<char>& sCode,
                     vector<char>& mCode, vector<double>& a,
                     vector<double>& c, vector<double>& r,
                     vector<string>& color, vector<string>& custNumber);
//Main Function

int main(){
    string fName;
    bool loadSuccess;
    bool incomplete;
    vector<string> reg;
    vector<char> sCode;
    vector<char> mCode;
    vector<double> a;
    vector<double> c;
    vector<double> r;
    vector<string> color;
    vector<string> custNumber;
    vector<double> cost;
    vector<double> price;
    do {
        char choice = displayMenu();
        if (choice == 'u') {
            cout << "Please type in the Customer Data Filepath:" << endl;
            cin >> fName;
            uploadFile(fName, loadSuccess, reg, sCode, mCode, a, c, r, color,
                    custNumber);
            incomplete = false;
        }else if (choice == 'a') {
            allDetails(reg, sCode, mCode, a, c, r, color, custNumber);
            incomplete = false;
        }else if (choice == 'i') {
            customerDetails(reg, sCode, mCode, a, c, r, color, custNumber);
            incomplete = false;
        }else if (choice == 'r'){
            summaryByRegion(reg, sCode, mCode, a, c, r, color, custNumber);
            incomplete = false;
        }else if (choice == 's'){
            summaryByShape(reg, sCode, mCode, a, c, r, color, custNumber);
            incomplete = false;
        }else if (choice == 'c')
            clearAllVectors(reg, sCode, mCode, a, c, r, color, custNumber);
            incomplete = false;
    } while (!incomplete);
    return 0;
}

// THESE ARE THE FUNCTION DEFINITIONS \\

char displayMenu(){
    string input;
    char cInput;

    bool menuOptionValidation = true;
    do {
        cout << "_____________________________________________________________________________________________" << endl;

        cout << "Hello, Please Select from the Following Options by Entering the Single Assigned Character:" << endl;
        cout << "_____________________________________________________________________________________________" << endl;
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
    //There might be more here to "Carry out the appropriate operation"
    return cInput;
}

void uploadFile(string fName, bool& loadSuccess, //might have to take off data type
                vector<string>& reg, vector<char>& sCode,
                vector<char>& mCode, vector<double>& a,
                vector<double>& c, vector<double>& r,
                vector<string>& color, vector<string>& custNumber){
    //Declarations from p2
    string secondline_heading, thirdline_heading, junk;
    int file_year, file_month, file_day, row_year, row_month, row_day;
    int invalid_counter = 0, valid_counter = 0, oblate_counter = 0, prolate_counter = 0, sphere_counter = 0;
    char file_datechar, row_char;
    string row_state, row_region, oColor,
            customer_num, customer_fname, customer_lname, customer_address;
    char Shape, Material;
    double semiA, semiC, Radius, SA = 0, m_cost,
    Labor_cost, Total_Fabrication_Cost = 0, Sale_Price = 0, Profit = 0, o_cost_counter = 0, p_cost_counter = 0, s_cost_counter =0,
    o_price_counter = 0, p_price_counter = 0, s_price_counter = 0, o_profit_counter = 0, p_profit_counter = 0,
    s_profit_counter = 0;
    ifstream customerfile;

    customerfile.open(fName.c_str()); //maybe .c_str()

    if (!customerfile) {
        cout << "Error: Customer Data File was unable to open, file will not be processed." << endl;
        loadSuccess = false;
        return;
    } else {
        string dash = "-";
        cout << setw(7) << "Region" << ' ' << setw(7) << "Shape" << ' ' << setw(7) << "Mat.";
        cout << ' ' << setw(7) << "Color" << ' ' << setw(7) << "A" << ' ' << setw(7) << "C" << ' ' <<
             setw(7) << "Rad." << ' ' << setw(7) << "S. Area" << ' ';
        cout << setw(7) << "Cost" << ' ' << setw(7) << "Price" << ' ' << setw(7) << "Profit" << endl;
        dash.assign(90, '-');
        cout << dash << endl;
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

    while (!customerfile.eof()) {
        bool datevalidation = true, shapevalidation = true, materialvalidation = true,
                colorvalidation = true, semiAvalidation = true, semiCvalidation = true, radiusvalidation = true;

        customerfile >> row_state >> row_region >> row_year >> row_char >> row_month >> row_char >> row_day >>
                     Shape >> Material >> oColor >> semiA >> semiC >> Radius >> customer_num >> customer_fname >>
                     customer_lname && getline(customerfile, customer_address);
        if(customerfile.eof()) break; //??

        Shape = tolower(Shape);
        Material = tolower(Material);
        //Row Outputs regardless of Validation result
        cout << setw(7) << row_region << ' ' << setw(7) << Shape << ' ' << setw(7) << Material << ' ' <<
             setw(7) << oColor << ' ';
        if (Shape == 'o' || Shape == 'p')
            cout << setw(7) << semiA << ' ' << setw(7) << semiC << ' ' << setw(7) << "n/a" << ' ';
        else if (Shape == 's')
            cout << setw(7) << "n/a" << ' ' << setw(7) << "n/a" << ' ' << setw(7) << Radius << ' ';
        else
            cout << setw(7) << "n/a" << ' ' << setw(7) << "n/a" << ' ' << setw(7) << "n/a" << ' ';



        //Date Validation
        if ((row_year > file_year) || (row_year == file_year && row_month > file_month) ||
            (row_year == file_year && row_month == file_month && row_day > file_day)) {
            datevalidation = false;
        }
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
        if (Shape == 'p' && semiC > semiA)
        {
            //Prolate Case
            prolate_counter++;
            if (semiA < minVal || semiA > maxVal || semiC > 1.95*(semiA))
                semiAvalidation = false;
        }

        //SemiC Validation while Oblate
        if (Shape == 'o' && semiC < semiA)
        {
            //Oblate Case
            oblate_counter++;
            if (semiC < minVal || semiC > maxVal || (semiC)*1.95 < semiA)
                semiCvalidation = false;
        }

        //Radius validation
        if (Shape == 's')
        {
            sphere_counter++;
            if (Radius < minVal && Radius > maxVal)
                radiusvalidation = false;
        }

        //Row Invalidation and Validation Counter
        if ((datevalidation == false) || (shapevalidation == false) || (materialvalidation == false) ||
            (colorvalidation == false) || (semiAvalidation == false) || (semiCvalidation == false)
            || (radiusvalidation == false)) {
            invalid_counter++;
        } //take out


        if (datevalidation == false)
            cout << endl << "The order date is not valid (is after the file date)" << endl;
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
        if (datevalidation == false || shapevalidation == false || materialvalidation == false ||
        colorvalidation == false || semiAvalidation == false || semiCvalidation == false || radiusvalidation == false)
            cout << row_region << " Region office must contact customer " << customer_fname << ' ' << customer_lname <<
            " to resolve the issues" << endl;

        if ((datevalidation == true) && (shapevalidation == true) && (materialvalidation == true) &&
            (colorvalidation == true) && (semiAvalidation == true) && (semiCvalidation == true)
            && (radiusvalidation == true))
        {
            valid_counter++;


            reg.push_back(row_region);
            sCode.push_back(Shape);
            mCode.push_back(Material);
            color.push_back(oColor);
            a.push_back(semiA);
            c.push_back(semiC);
            r.push_back(Radius);
            custNumber.push_back(customer_num);

            //Surface Area Stuff

            if (semiA > semiC)
            {
                double e = sqrt(1 - pow(semiC, 2)/pow(semiA, 2));
                SA = (2*(M_PI)*pow(semiA, 2));
                SA = SA + ((M_PI)*(pow(semiC, 2)/e)*log((1+e)/(1-e)));
            }
            else if (semiC > semiA)
            {
                double e = sqrt(1 - (pow(semiA, 2)/pow(semiC, 2)));
                SA = (2*(M_PI)*pow(semiA, 2))*(1+(semiC/(semiA*e))*asin(e));
            }
            else if (Radius > minVal && Radius < maxVal)
                SA = 4*(M_PI)*pow(Radius, 2);

            //Calculations
            if (Material == 'p')
            {
                m_cost = PlasticCost*SA;
                Labor_cost = 32.76 + (.19*(m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp*(Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }
            else if (Material == 'a')
            {
                m_cost = AluminumCost*SA;
                Labor_cost = 80.13 + (.29*(m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp*(Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }
            else if (Material == 'c')
            {
                m_cost = CarbonCost*SA;
                Labor_cost = 126.49 + (.49*(m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp*(Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }


            cout << fixed << setprecision(2) << setw(7) << SA << ' ' << fixed << setprecision(2) <<
                 setw(7) << Total_Fabrication_Cost << ' ' << fixed << setprecision(2) << setw(7)
                 << Sale_Price << ' ' << fixed << setprecision(2) << setw(7) << Profit << endl;

        }
    }
    customerfile.close();
}

void allDetails(const vector<string>& reg, const vector<char>& sCode,
                const vector<char>& mCode, const vector<double>& a,
                const vector<double>& c, const vector<double>& r,
                const vector<string>& color,
                const vector<string>& custNumber){
    if(reg.empty())
        cout << "Error: No Data for Region Entries" << endl;
    if(sCode.empty())
        cout << "Error: No Data for Shape Entries" << endl;
    if(mCode.empty())
        cout << "Error: No Data for Material Entries" << endl;
    if(color.empty())
        cout << "Error: No Data for Color Entries" << endl;
    if(a.empty())
        cout << "Error: No Data for Semi-Axis A Entries" << endl;
    if(c.empty())
        cout << "Error: No Data for Semi-Axis C Entries" << endl;
    if(r.empty())
        cout << "Error: No Data for Radius Entries" << endl;
    if(custNumber.empty())
        cout << "Error: No Data for Customer Number Entries" << endl;
    if(!reg.empty() && !sCode.empty() && !mCode.empty() && !color.empty() && !a.empty() && !c.empty() &&
    !r.empty() && !custNumber.empty()){
        int regSize = reg.size();
        //int sCodeSize = sCode.size();
        //int mCodeSize = mCode.size();
        int colorSize = color.size();
        int aSize = a.size();
        int cSize = c.size();
        int rSize = r.size();
        int custNumberSize = custNumber.size();
        int x;
        double SA = 0, m_cost,
                Labor_cost, Total_Fabrication_Cost = 0, Sale_Price = 0, Profit = 0;
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
        for(x=0; x<regSize; x++){
            cout << setw(12) << reg.at(x);
            cout << setw(12) << sCode.at(x);
            cout << setw(12) << mCode.at(x);
            cout << setw(12) << color.at(x);
            cout << setw(12) << a.at(x);
            cout << setw(12) << c.at(x);
            cout << setw(12) << r.at(x);
            cout << setw(17) << custNumber.at(x);

            double semiA = a.at(x);
            double semiC = c.at(x);
            double Radius = r.at(x);
            char Material = mCode.at(x);

            //Surface Area Stuff

            if (semiA > semiC)
            {
                double e = sqrt(1 - pow(semiC, 2)/pow(semiA, 2));
                SA = (2*(M_PI)*pow(semiA, 2));
                SA = SA + ((M_PI)*(pow(semiC, 2)/e)*log((1+e)/(1-e)));
            }
            else if (semiC > semiA)
            {
                double e = sqrt(1 - (pow(semiA, 2)/pow(semiC, 2)));
                SA = (2*(M_PI)*pow(semiA, 2))*(1+(semiC/(semiA*e))*asin(e));
            }
            else if (Radius > minVal && Radius < maxVal)
                SA = 4*(M_PI)*pow(Radius, 2);

            //Calculations
            if (Material == 'p')
            {
                m_cost = PlasticCost*SA;
                Labor_cost = 32.76 + (.19*(m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp*(Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }
            else if (Material == 'a')
            {
                m_cost = AluminumCost*SA;
                Labor_cost = 80.13 + (.29*(m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp*(Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }
            else if (Material == 'c')
            {
                m_cost = CarbonCost*SA;
                Labor_cost = 126.49 + (.49*(m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp*(Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }
            cout << setw(12) << Total_Fabrication_Cost;
            cout << setw(12) << Sale_Price;
            cout << setw(12) << Profit << endl;
        }


    }

}

void customerDetails(const vector<string>& reg, const vector<char>& sCode,
                     const vector<char>& mCode, const vector<double>& a,
                     const vector<double>& c, const vector<double>& r,
                     const vector<string>& color,
                     const vector<string>& custNumber){
    string customerId;
    int custSize;
    int accumulator = 0;
    double SA = 0, m_cost,
            Labor_cost, Total_Fabrication_Cost = 0, Sale_Price = 0, Profit = 0;
    if(reg.empty())
        cout << "Error: No Data for Region Entries" << endl;
    if(sCode.empty())
        cout << "Error: No Data for Shape Entries" << endl;
    if(mCode.empty())
        cout << "Error: No Data for Material Entries" << endl;
    if(color.empty())
        cout << "Error: No Data for Color Entries" << endl;
    if(a.empty())
        cout << "Error: No Data for Semi-Axis A Entries" << endl;
    if(c.empty())
        cout << "Error: No Data for Semi-Axis C Entries" << endl;
    if(r.empty())
        cout << "Error: No Data for Radius Entries" << endl;
    if(custNumber.empty())
        cout << "Error: No Data for Customer Number Entries" << endl;
    if(!reg.empty() && !sCode.empty() && !mCode.empty() && !color.empty() && !a.empty() && !c.empty() &&
       !r.empty() && !custNumber.empty()){
        cout << "Please Enter a Customer ID:" << endl;
        cin >> customerId;
        custSize = custNumber.size();
        for(int x=0; x<custSize; x++) {
            if (customerId != custNumber.at(x)) {
                accumulator++;
                if (accumulator == custSize) {
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
        for(int x=0; x<custSize; x++) {
             if (customerId == custNumber.at(x)){
                cout << "For order(s) " << customerId << ':' << endl;
                cout << setw(12) << reg.at(x);
                cout << setw(12) << sCode.at(x);
                cout << setw(12) << mCode.at(x);
                cout << setw(12) << color.at(x);
                cout << setw(12) << a.at(x);
                cout << setw(12) << c.at(x);
                cout << setw(12) << r.at(x);

                 double semiA = a.at(x);
                 double semiC = c.at(x);
                 double Radius = r.at(x);
                 char Material = mCode.at(x);

                 //Surface Area Stuff

                 if (semiA > semiC)
                 {
                     double e = sqrt(1 - pow(semiC, 2)/pow(semiA, 2));
                     SA = (2*(M_PI)*pow(semiA, 2));
                     SA = SA + ((M_PI)*(pow(semiC, 2)/e)*log((1+e)/(1-e)));
                 }
                 else if (semiC > semiA)
                 {
                     double e = sqrt(1 - (pow(semiA, 2)/pow(semiC, 2)));
                     SA = (2*(M_PI)*pow(semiA, 2))*(1+(semiC/(semiA*e))*asin(e));
                 }
                 else if (Radius > minVal && Radius < maxVal)
                     SA = 4*(M_PI)*pow(Radius, 2);

                 //Calculations
                 if (Material == 'p')
                 {
                     m_cost = PlasticCost*SA;
                     Labor_cost = 32.76 + (.19*(m_cost));
                     Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                     Sale_Price = (markUp*(Total_Fabrication_Cost));
                     Profit = Sale_Price - Total_Fabrication_Cost;
                 }
                 else if (Material == 'a')
                 {
                     m_cost = AluminumCost*SA;
                     Labor_cost = 80.13 + (.29*(m_cost));
                     Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                     Sale_Price = (markUp*(Total_Fabrication_Cost));
                     Profit = Sale_Price - Total_Fabrication_Cost;
                 }
                 else if (Material == 'c')
                 {
                     m_cost = CarbonCost*SA;
                     Labor_cost = 126.49 + (.49*(m_cost));
                     Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                     Sale_Price = (markUp*(Total_Fabrication_Cost));
                     Profit = Sale_Price - Total_Fabrication_Cost;
                 }
                 cout << setw(12) << Total_Fabrication_Cost;
                 cout << setw(12) << Sale_Price;
                 cout << setw(12) << Profit << endl;
            }
        }
    }
}

void summaryByShape(const vector<string>& reg, const vector<char>& sCode,
                    const vector<char>& mCode, const vector<double>& a,
                    const vector<double>& c, const vector<double>& r,
                    const vector<string>& color,
                    const vector<string>& custNumber){
    double SA = 0, m_cost,
            Labor_cost, Total_Fabrication_Cost = 0, Sale_Price = 0, Profit = 0, o_cost_counter = 0,
            p_cost_counter = 0, s_cost_counter =0, o_price_counter = 0, p_price_counter = 0, s_price_counter = 0,
            o_profit_counter = 0, p_profit_counter = 0, s_profit_counter = 0;
    int oblate_counter = 0;
    int prolate_counter = 0;
    int sphere_counter = 0;
    if(reg.empty())
        cout << "Error: No Data for Region Entries" << endl;
    if(sCode.empty())
        cout << "Error: No Data for Shape Entries" << endl;
    if(mCode.empty())
        cout << "Error: No Data for Material Entries" << endl;
    if(color.empty())
        cout << "Error: No Data for Color Entries" << endl;
    if(a.empty())
        cout << "Error: No Data for Semi-Axis A Entries" << endl;
    if(c.empty())
        cout << "Error: No Data for Semi-Axis C Entries" << endl;
    if(r.empty())
        cout << "Error: No Data for Radius Entries" << endl;
    if(custNumber.empty())
        cout << "Error: No Data for Customer Number Entries" << endl;
    if(!reg.empty() && !sCode.empty() && !mCode.empty() && !color.empty() && !a.empty() && !c.empty() &&
       !r.empty() && !custNumber.empty()) {

        int shapeSize = sCode.size();


        for (int x = 0; x < shapeSize; x++) {

            double semiA = a.at(x);
            double semiC = c.at(x);
            double Radius = r.at(x);
            char Material = mCode.at(x);
            char Shape = sCode.at(x);
            //Surface Area Stuff

            if (semiA > semiC) {
                double e = sqrt(1 - pow(semiC, 2) / pow(semiA, 2));
                SA = (2 * (M_PI) * pow(semiA, 2));
                SA = SA + ((M_PI) * (pow(semiC, 2) / e) * log((1 + e) / (1 - e)));
            } else if (semiC > semiA) {
                double e = sqrt(1 - (pow(semiA, 2) / pow(semiC, 2)));
                SA = (2 * (M_PI) * pow(semiA, 2)) * (1 + (semiC / (semiA * e)) * asin(e));
            } else if (Radius > minVal && Radius < maxVal)
                SA = 4 * (M_PI) * pow(Radius, 2);

            //Calculations
            if (Material == 'p') {
                m_cost = PlasticCost * SA;
                Labor_cost = 32.76 + (.19 * (m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp * (Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            } else if (Material == 'a') {
                m_cost = AluminumCost * SA;
                Labor_cost = 80.13 + (.29 * (m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp * (Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            } else if (Material == 'c') {
                m_cost = CarbonCost * SA;
                Labor_cost = 126.49 + (.49 * (m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp * (Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }

            //Cost, Price, and Profit Accumulator per shape
            if (Shape == 'o') {
                o_cost_counter += Total_Fabrication_Cost;
                o_price_counter += Sale_Price;
                o_profit_counter += Profit;
            } else if (Shape == 'p') {
                p_cost_counter += Total_Fabrication_Cost;
                p_price_counter += Sale_Price;
                p_profit_counter += Profit;
            } else if (Shape == 's') {
                s_cost_counter += Total_Fabrication_Cost;
                s_price_counter += Sale_Price;
                s_profit_counter += Profit;
            }

            //Cost, Price, and Profit Accumulator per shape
            if (Shape == 'o') {
                oblate_counter++;
                o_cost_counter += Total_Fabrication_Cost;
                o_price_counter += Sale_Price;
                o_profit_counter += Profit;
            } else if (Shape == 'p') {
                prolate_counter++;
                p_cost_counter += Total_Fabrication_Cost;
                p_price_counter += Sale_Price;
                p_profit_counter += Profit;
            } else if (Shape == 's') {
                sphere_counter++;
                s_cost_counter += Total_Fabrication_Cost;
                s_price_counter += Sale_Price;
                s_profit_counter += Profit;
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
             << setprecision(2) << setw(15)<< o_price_counter << ' ' << fixed
             << setprecision(2) << setw(15) << o_profit_counter << endl;
        cout << setw(15) << "Sphere" << ' ' << setw(15) << sphere_counter << ' ' <<
             fixed << setprecision(2) << setw(15) << s_cost_counter << ' ' << fixed << setprecision(2)
             << setw(15) << s_price_counter << ' ' << fixed << setprecision(2) << setw(15)
             << s_profit_counter << endl;
        cout << dash << endl;
    }
}

void summaryByRegion(const vector<string>& reg, const vector<char>& sCode,
                     const vector<char>& mCode, const vector<double>& a,
                     const vector<double>& c, const vector<double>& r,
                     const vector<string>& color,
                     const vector<string>& custNumber) {

    double SA = 0, m_cost,
            Labor_cost, Total_Fabrication_Cost = 0, Sale_Price = 0, Profit = 0, o_cost_counter = 0,
            p_cost_counter = 0, s_cost_counter = 0, o_price_counter = 0, p_price_counter = 0, s_price_counter = 0,
            o_profit_counter = 0, p_profit_counter = 0, s_profit_counter = 0;
    int north_counter = 0;
    int south_counter = 0;
    int west_counter = 0;
    int east_counter = 0;
    int other_counter = 0;
    if (reg.empty())
        cout << "Error: No Data for Region Entries" << endl;
    if (sCode.empty())
        cout << "Error: No Data for Shape Entries" << endl;
    if (mCode.empty())
        cout << "Error: No Data for Material Entries" << endl;
    if (color.empty())
        cout << "Error: No Data for Color Entries" << endl;
    if (a.empty())
        cout << "Error: No Data for Semi-Axis A Entries" << endl;
    if (c.empty())
        cout << "Error: No Data for Semi-Axis C Entries" << endl;
    if (r.empty())
        cout << "Error: No Data for Radius Entries" << endl;
    if (custNumber.empty())
        cout << "Error: No Data for Customer Number Entries" << endl;
    if (!reg.empty() && !sCode.empty() && !mCode.empty() && !color.empty() && !a.empty() && !c.empty() &&
        !r.empty() && !custNumber.empty()) {

        int regSize = reg.size();


        for (int x = 0; x < regSize; x++) {

            double semiA = a.at(x);
            double semiC = c.at(x);
            double Radius = r.at(x);
            char Material = mCode.at(x);
            string region = reg.at(x);
            //Surface Area Stuff

            if (semiA > semiC) {
                double e = sqrt(1 - pow(semiC, 2) / pow(semiA, 2));
                SA = (2 * (M_PI) * pow(semiA, 2));
                SA = SA + ((M_PI) * (pow(semiC, 2) / e) * log((1 + e) / (1 - e)));
            } else if (semiC > semiA) {
                double e = sqrt(1 - (pow(semiA, 2) / pow(semiC, 2)));
                SA = (2 * (M_PI) * pow(semiA, 2)) * (1 + (semiC / (semiA * e)) * asin(e));
            } else if (Radius > minVal && Radius < maxVal)
                SA = 4 * (M_PI) * pow(Radius, 2);

            //Calculations
            if (Material == 'p') {
                m_cost = PlasticCost * SA;
                Labor_cost = 32.76 + (.19 * (m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp * (Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            } else if (Material == 'a') {
                m_cost = AluminumCost * SA;
                Labor_cost = 80.13 + (.29 * (m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp * (Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            } else if (Material == 'c') {
                m_cost = CarbonCost * SA;
                Labor_cost = 126.49 + (.49 * (m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (markUp * (Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }


            //Cost, Price, and Profit Accumulator per Region
            if (region == "North") {
                north_counter++;
                o_cost_counter += Total_Fabrication_Cost;
                o_price_counter += Sale_Price;
                o_profit_counter += Profit;
            } else if (region == "South") {
                south_counter++;
                p_cost_counter += Total_Fabrication_Cost;
                p_price_counter += Sale_Price;
                p_profit_counter += Profit;
            } else if (region == "West") {
                west_counter++;
                s_cost_counter += Total_Fabrication_Cost;
                s_price_counter += Sale_Price;
                s_profit_counter += Profit;
            } else if (region == "East") {
                east_counter++;
                s_cost_counter += Total_Fabrication_Cost;
                s_price_counter += Sale_Price;
                s_profit_counter += Profit;
            } else if (region == "Other") {
                other_counter++;
                s_cost_counter += Total_Fabrication_Cost;
                s_price_counter += Sale_Price;
                s_profit_counter += Profit;
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
             << fixed << setprecision(2) << setw(15) << o_cost_counter << ' ' << fixed
             << setprecision(2) << setw(15)
             << o_price_counter << ' ' << setw(15) << o_profit_counter << endl;
        cout << setw(15) << "South" << ' ' << setw(15) << south_counter << ' ' <<
             fixed << setprecision(2) << setw(15) << p_cost_counter << ' ' << fixed
             << setprecision(2) << setw(15) << o_price_counter << ' ' << fixed
             << setprecision(2) << setw(15) << o_profit_counter << endl;
        cout << setw(15) << "East" << ' ' << setw(15) << east_counter << ' ' <<
             fixed << setprecision(2) << setw(15) << s_cost_counter << ' ' << fixed << setprecision(2)
             << setw(15) << s_price_counter << ' ' << fixed << setprecision(2) << setw(15)
             << s_profit_counter << endl;
        cout << setw(15) << "West" << ' ' << setw(15) << west_counter << ' ' <<
             fixed << setprecision(2) << setw(15) << s_cost_counter << ' ' << fixed << setprecision(2)
             << setw(15) << s_price_counter << ' ' << fixed << setprecision(2) << setw(15)
             << s_profit_counter << endl;
        cout << setw(15) << "Other" << ' ' << setw(15) << other_counter << ' ' <<
             fixed << setprecision(2) << setw(15) << s_cost_counter << ' ' << fixed << setprecision(2)
             << setw(15) << s_price_counter << ' ' << fixed << setprecision(2) << setw(15)
             << s_profit_counter << endl;
        cout << dash << endl;
    }
}

void clearAllVectors(vector<string>& reg, vector<char>& sCode,
                     vector<char>& mCode, vector<double>& a,
                     vector<double>& c, vector<double>& r,
                     vector<string>& color, vector<string>& custNumber){
    reg.clear();
    sCode.clear();
    mCode.clear();
    a.clear();
    c.clear();
    r.clear();
    color.clear();
    custNumber.clear();
}