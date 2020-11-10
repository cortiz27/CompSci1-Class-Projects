/**
* clo42P1.pdf
*
* COSC 051 Spring 2020
* Project #1
*
* Due on: 12 February 2020 * Author clo42
*
* In accordance with the class policies and Georgetown’s Honor Code,
* I certify that, with the exception of the class resources and those
* items noted below, I have neither given nor received any assistance
* on this project.
*
* References not otherwise commented within the program source code. * Note that you should
not mention help from our TAs, professors, or * any code taken from the course textbook.
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main()
{
    //Constants

    double PlasticCost = .14,
        AluminumCost = .39,
        CarbonCost = 1.35,
        minVal = .45,
        maxVal = 7.62;

    //Variables

    char Material, Shape;
    double HorAxis, VerAxis, Radius, SA, m_cost, Labor_cost, Total_Fabrication_Cost, Sale_Price;

    //Input and Outputs

    cout << "What Shape Would you like?" << endl;
    cout << "** We have Oblate Spheroids, Prolate Spheroids, and Spheres." << endl;
    cin >> Shape;
    cin.ignore(300, '\n');
    Shape = tolower(Shape);
    
    //Oblate Spheroid Conditional
    if (Shape == 'o')
    {
        cout << "What are the dimensions of the shape?" << endl;
        cout << "** Minumum Value accepted is " << minVal << " and Maximum Value accepted is " << maxVal << endl;

        cout << "Vertical Axis:" << endl;
        cin >> VerAxis;

        if (VerAxis > maxVal || VerAxis < HorAxis)
        {
            cout << "Input is NOT within accepted range of values";
            return 0;
        }

        cout << "Horizontal Axis: " << endl;
        cin >> HorAxis;

        if (HorAxis > maxVal || HorAxis < minVal || HorAxis > 1.95*(VerAxis))
        {
            cout << "Input is NOT within accepted range of values ";
            cout << "OR Input makes Horizontal Axis more than 1.95x the Vertical Axis";
            return 0;
        }

        cout << "What material would you like your Oblate Spheroid to be made of?" << endl;
        cout << "** We have aluminum, plastic, and carbon fiber" << endl;
        cin >> Material;
        cin.ignore(300, '\n');
        Material = tolower(Material);

        if (Material != 'a' && Material != 'p' && Material != 'c')
        {
            cout << "Material input is invalid, enter one of the options listed";
            return 0;
        }
    }

    //Prolate Spheroid Conditional
    if (Shape == 'p')
    {
        cout << "What are the dimensions of the shape?" << endl;
        cout << "** Minumum Value accepted is " << minVal << " and Maximum Value accepted is " << maxVal << endl;

        cout << "Horizontal Axis: " << endl;
        cin >> HorAxis;

        if (HorAxis > maxVal || HorAxis < minVal)
        {
            cout << "Input is NOT within accepted range of values ";
            return 0;
        }

        cout << "Vertical Axis:" << endl;
        cin >> VerAxis;

        if (VerAxis > maxVal || VerAxis < HorAxis || VerAxis > 1.95*(HorAxis))
        {
            cout << "Input is NOT within accepted range of values";
            cout << "OR Input makes Vertical Axis more than 1.95x the Horizontal Axis";
            return 0;
        }



        cout << "What material would you like your Prolate Spheroid to be made of?" << endl;
        cout << "** We have aluminum, plastic, and carbon fiber" << endl;
        cin >> Material;
        cin.ignore(300, '\n');
        Material = tolower(Material);

        if (Material != 'a' && Material != 'p' && Material != 'c')
        {
            cout << "Material input is invalid, enter one of the options listed";
            return 0;
        }


    }

    //Sphere Conditional
    if (Shape == 's')
    {
        cout << "What are the dimensions of the shape?" << endl;
        cout << "** Minumum Value accepted is " << minVal << " and Maximum Value accepted is " << maxVal << endl;

        cout << "Radius: " << endl;
        cin >> Radius;

        if (Radius > maxVal || Radius < minVal)
        {
            cout << "Input is NOT within accepted range of values ";
            return 0;
        }

        cout << "What material would you like your Sphere to be made of?" << endl;
        cout << "** We have aluminum, plastic, and carbon fiber" << endl;
        cin >> Material;
        cin.ignore(300, '\n');
        Material = tolower(Material);
        
        if (Material != 'a' && Material != 'p' && Material != 'c')
        {
            cout << "Material input is invalid, enter one of the options listed";
            return 0;
        }
    }

    //Surface Area Stuff

    if (HorAxis > VerAxis)
    {
        double e = sqrt(1 - pow(VerAxis, 2)/pow(HorAxis, 2));
        SA = (2*(M_PI)*pow(HorAxis, 2));
        SA = SA + ((M_PI)*(pow(VerAxis, 2)/e)*log((1+e)/(1-e)));
    }
    else if (VerAxis > HorAxis)
    {
        double e = sqrt(1 - (pow(HorAxis, 2)/pow(VerAxis, 2)));
        SA = (2*(M_PI)*pow(HorAxis, 2))*(1+(VerAxis/(HorAxis*e))*asin(e));
    }
    else if (Radius > minVal && Radius < maxVal)
    {
        SA = 4*(M_PI)*pow(Radius, 2);
    }

    //Materials Cost and Labor Cost

    if (Material == 'p')
    {
        m_cost = .14*SA;
        Labor_cost = 32.76 + (.19*(m_cost));
        Total_Fabrication_Cost = (m_cost) + (Labor_cost);
        Sale_Price = (1.19*(Total_Fabrication_Cost));
    }
    else if (Material == 'a')
    {
        m_cost = .39*SA;
        Labor_cost = 80.13 + (.29*(m_cost));
        Total_Fabrication_Cost = (m_cost) + (Labor_cost);
        Sale_Price = (1.19*(Total_Fabrication_Cost));
    }
    else if (Material == 'c')
    {
      m_cost = 1.35*SA;
      Labor_cost = 126.49 + (.49*(m_cost));
      Total_Fabrication_Cost = (m_cost) + (Labor_cost);
      Sale_Price = (1.19*(Total_Fabrication_Cost));
    }

    //Outputs of Order

    if (Shape == 'o')
    {
        cout << "The shape selected is an Oblate Spheroid." << endl;
        cout << "The horizontal semiaxis measures " << HorAxis << " inches and the vertical semiaxis measures " << VerAxis << " inches." << endl;
    }

    if (Shape == 'p')
    {
        cout << "The shape selected is a Prolate Spheroid." << endl;
        cout << "The horizontal semiaxis measures " << HorAxis << " inches and the vertical semiaxis measures " << VerAxis << " inches." << endl;
    }

    if (Shape == 's')
    {
        cout << "The shape selected is an Sphere" << endl;
        cout << "The radius measures " << Radius << " inches." << endl;
    }

    if (Material == 'p')
    {
        cout << "and the material selected for the shape is Plastic";
    }

    if (Material == 'a')
    {
        cout << "and the material selected for the shape is Aluminum";
    }

    if (Material == 'c')
    {
        cout << "and the material selected for the shape is Carbon Fiber";
    }

    cout << endl;
    cout << fixed;
    cout << "The Total Cost of Materials for your Order is " << setprecision(2) << m_cost << " dollars." << endl;
    cout << "The Total Cost of Labor for your Order is " << setprecision(2) << Labor_cost << " dollars." << endl;
    cout << "The Total Fabrication Cost for your Order is " << setprecision(2) << Total_Fabrication_Cost << " dollars." << endl;
    cout << "The Final Sale Price for your order is " << setprecision(2) << Sale_Price << " dollars." << endl;


    return 0;
}
