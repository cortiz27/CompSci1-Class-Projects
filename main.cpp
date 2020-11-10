/*
* main.cpp
*
* COSC 051 Spring 2020
* Project #2
*
* Due on: 26 February 2020
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
#include <fstream>

using namespace std;

int main() {

    //Constants
    double const PlasticCost = .14,
            AluminumCost = .39,
            CarbonCost = 1.35,
            minVal = 0.45,
            maxVal = 7.62;

    //Object definitions
    string filename, secondline_heading, thirdline_heading, junk;
    int file_year, file_month, file_day, row_year, row_month, row_day;
    int invalid_counter = 0, valid_counter = 0, oblate_counter = 0, prolate_counter = 0, sphere_counter = 0;
    char file_datechar, row_char;
    string row_state, row_region, color,
    customer_num, customer_fname, customer_lname, customer_address;
    char Shape, Material;
    double semiA, semiC, Radius, SA = 0, m_cost,
    Labor_cost, Total_Fabrication_Cost = 0, Sale_Price = 0, Profit = 0, o_cost_counter = 0, p_cost_counter = 0, s_cost_counter =0,
    o_price_counter = 0, p_price_counter = 0, s_price_counter = 0, o_profit_counter = 0, p_profit_counter = 0,
    s_profit_counter = 0;
    ifstream customerfile;

    cout << "Please type in the Customer Data Filename:" << endl;
    cin >> filename;
    customerfile.open(filename);

    //Validates file opening
    if (!customerfile) {
        cout << "Error: Customer Data File was unable to open, file will not be processed." << endl;
        return 0;
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
        return 0;
    if (file_day < 1 || file_day > 31)
        return 0;

    while (!customerfile.eof()) {
        bool datevalidation = true, shapevalidation = true, materialvalidation = true,
                colorvalidation = true, semiAvalidation = true, semiCvalidation = true, radiusvalidation = true;

        customerfile >> row_state >> row_region >> row_year >> row_char >> row_month >> row_char >> row_day >>
                     Shape >> Material >> color >> semiA >> semiC >> Radius >> customer_num >> customer_fname >>
                     customer_lname && getline(customerfile, customer_address);
        if(customerfile.eof()) break;

        Shape = tolower(Shape);
        Material = tolower(Material);
        //Row Outputs regardless of Validation result
        cout << setw(7) << row_region << ' ' << setw(7) << Shape << ' ' << setw(7) << Material << ' ' <<
             setw(7) << color << ' ';
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
        if (color != "Red" && color != "Orange" && color != "Yellow" && color != "Green" &&
        color != "Blue" && color != "Indigo" && color != "Violet") {
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

        //Row Invalidation and Validation Counter, check this tho -- conditional might be off
        if ((datevalidation == false) || (shapevalidation == false) || (materialvalidation == false) ||
        (colorvalidation == false) || (semiAvalidation == false) || (semiCvalidation == false)
            || (radiusvalidation == false)) {
            invalid_counter++;
        }

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
            //cout << row_region << " Region office must contact customer " << customer_fname << ' ' << customer_lname <<
            //" to resolve the issues" << endl;

        if ((datevalidation == true) && (shapevalidation == true) && (materialvalidation == true) &&
            (colorvalidation == true) && (semiAvalidation == true) && (semiCvalidation == true)
            && (radiusvalidation == true))
        {
            valid_counter++;

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
                Sale_Price = (1.19*(Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }
            else if (Material == 'a')
            {
                m_cost = AluminumCost*SA;
                Labor_cost = 80.13 + (.29*(m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (1.19*(Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }
            else if (Material == 'c')
            {
                m_cost = CarbonCost*SA;
                Labor_cost = 126.49 + (.49*(m_cost));
                Total_Fabrication_Cost = (m_cost) + (Labor_cost);
                Sale_Price = (1.19*(Total_Fabrication_Cost));
                Profit = Sale_Price - Total_Fabrication_Cost;
            }

            //Cost, Price, and Profit Accumulator per shape
            if (Shape == 'o')
            {
                o_cost_counter += Total_Fabrication_Cost;
                o_price_counter += Sale_Price;
                o_profit_counter += Profit;
            }
            else if (Shape == 'p')
            {
                p_cost_counter += Total_Fabrication_Cost;
                p_price_counter += Sale_Price;
                p_profit_counter += Profit;
            }
            else if (Shape == 's')
            {
                s_cost_counter += Total_Fabrication_Cost;
                s_price_counter += Sale_Price;
                s_profit_counter += Profit;
            }

            cout << fixed << setprecision(2) << setw(7) << SA << ' ' << fixed << setprecision(2) <<
            setw(7) << Total_Fabrication_Cost << ' ' << fixed << setprecision(2) << setw(7)
            << Sale_Price << ' ' << fixed << setprecision(2) << setw(7) << Profit << endl;
        }
    }
    customerfile.close();

    //Summary after Reading every Row
    cout << "File Summary:" << endl;
    cout << "Valid Records: " << valid_counter << endl;
    cout << "Invalid Records: " << invalid_counter << endl;
    cout << "Total Records: " << (valid_counter+invalid_counter) << endl;
    cout << "Summary Totals: " << endl;
    cout << endl;
    cout << endl;
    cout << setw(8) << "Shape" << ' ' << setw(8) << "Number" << ' ' << setw(8) << "Cost" << ' '
    << setw(8) << "Price" << ' ' << setw(8) << "Profit" << endl;
    string dash = "-";
    dash.assign(55, '-');
    cout << dash << endl;
    cout << setw(8) << "Oblate" << ' ' << setw(8) << oblate_counter << ' '
    << fixed << setprecision(2) << setw(8) << o_cost_counter << ' ' << fixed << setprecision(2) << setw(8)
    << o_price_counter << ' ' << setw(8) << o_profit_counter << endl;
    cout << setw(8) << "Prolate" << ' ' << setw(8) << prolate_counter << ' ' <<
    fixed << setprecision(2) << setw(8) << p_cost_counter << ' ' << fixed << setprecision(2) << setw(8)
         << o_price_counter << ' ' << fixed << setprecision(2) << setw(8) << o_profit_counter << endl;
    cout << setw(8) << "Sphere" << ' ' << setw(8) << sphere_counter << ' ' <<
         fixed << setprecision(2) << setw(8) << s_cost_counter << ' ' << fixed << setprecision(2)
         << setw(8) << s_price_counter << ' ' << fixed << setprecision(2) << setw(8)
         << s_profit_counter << endl;
    cout << dash << endl;

    return 0;
}
