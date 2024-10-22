#include <stdio.h>
#include "Poly.h"



//-------------------------------------------------
// Creates a polynomial from an expression.
// Returns a pointer to the first PolyNode in the list (head of the list)
//
// Expression will be of the following sort:
// Ex1: 2.3x^4 + 5x^3 - 2.64x - 4
// Ex2: -4.555x^10 - 45.44
// Ex3: x^6 + 2x^4 - x^3 - 6.3x + 4.223 
// Ex4: 34
// Ex5: -x+1
// Ex6: -3x^4    +   4x
// Ex7: -2x  - 5
PolyNode* CreatePoly(char* expr) {
    PolyNode* head = NULL;
    PolyNode* tail = NULL;

    char* token = expr;

    int sign;
    double coef;
    int flag;
    int count;
    double temp;
    int exp;

    while (*token != '\0')
    {
        sign = 1;
        coef = 0;
        flag = 1;
        count = 0;
        temp = 0;
        exp = 0;

        while (*token == ' ')
        {
            token++;
        }
        if (*token == '+')
        {
            sign = 1;
            token++;
            while (*token == ' ')
            {
                token++;
            }
        }

        else if (*token == '-')
        {
            sign = -1;
            token++;
            while (*token == ' ')
            {
                token++;
            }
        }

        if (*token == 'x')
        {
            coef = 1.0; // Default coefficient for 'x' is 1
        }
        else
        {
            while ((*token >= '0' && *token <= '9') || *token == '.')
            {
                if (flag == 1)
                {
                    if (*token == '.')
                    {
                        flag = -1;
                    }
                    else
                    {
                        coef = coef * 10;
                        coef = coef + (int)(*token - '0');
                    }
                }
                else if (flag == -1)
                {
                    temp = (double)(*token - '0');
                    count++;
                    for (int i = 0; i < count; i++)
                    {
                        temp = temp / 10;
                    }
                    coef = coef + temp;
                }
                token++;
            }
        }

        coef *= sign;

        if (*token == 'x')
        {
            token++;

            if (*token == '^')
            {
                token++;
                while (*token >= '0' && *token <= '9')
                {
                    exp = exp * 10;
                    exp = exp + (int)(*token - '0');
                    token++;
                }
            }
            else
            {
                exp = 1;
            }
        }
        else
        {
            exp = 0;
        }

        head = AddNode(head, coef, exp);
    }
    return head;
}





//end-CreatePoly

/// -------------------------------------------------
/// Walk over the poly nodes & delete them
///
void DeletePoly(PolyNode* poly) {
    // Fill this in
    PolyNode* temp = poly;
    while (temp != NULL)
    {
        poly = poly->next;
        delete temp;
        temp = poly;
    }
} // end-DeletePoly

//-------------------------------------------------
// Adds a node (coefficient, exponent) to poly. If there already 
// is a node with the same exponent, then you simply add the coefficient
// to the existing coefficient. If not, you add a new node to polynomial
// Returns a pointer to the possibly new head of the polynomial.
//
PolyNode* AddNode(PolyNode* head, double coef, int exp) {
    // Fill this in
    PolyNode* newNode = new PolyNode;
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        PolyNode* it = head;
        for (PolyNode* it = head; it != NULL; it = it->next)
        {
            if (it->exp == exp)
            {
                it->coef += coef;
                if (it->coef == 0.0)
                {
                    PolyNode* temp = head;
                    if (temp == it)
                    {
                        head = head->next;
                        delete it;
                        return head;
                    }
                    while (temp->next != it)
                    {
                        temp = temp->next;
                    }
                    temp->next = it->next;
                    delete it;
                }
                return head;
            }
            else
                if (it == head && it->exp < newNode->exp)
                {
                    newNode->next = head;
                    head = newNode;
                    return head;
                }
                else if (it->next != NULL && it->next->exp < exp && it->exp > exp)
                {
                    newNode->next = it->next;
                    it->next = newNode;
                    return head;
                }
                else if (it->next == NULL)
                {
                    it->next = newNode;
                    return head;
                }
        }
    }
    return head;
} // end-AddNode

//-------------------------------------------------
// Adds two polynomials and returns a new polynomial that contains the result
// Computes: poly3 = poly1 + poly2 and returns poly3
//
PolyNode* Add(PolyNode* poly1, PolyNode* poly2) {
    // Fill this in
    PolyNode* poly = NULL;
    PolyNode* it1 = poly1;
    PolyNode* it2 = poly2;


    while (it1 != NULL)
    {
        poly = AddNode(poly, it1->coef, it1->exp);
        it1 = it1->next;
    }

    while (it2 != NULL)
    {
        poly = AddNode(poly, it2->coef, it2->exp);
        it2 = it2->next;
    }

    return poly;
} //end-Add

//-------------------------------------------------
// Subtracts poly2 from poly1 and returns the resulting polynomial
// Computes: poly3 = poly1 - poly2 and returns poly3
//
PolyNode* Subtract(PolyNode* poly1, PolyNode* poly2) {
    // Fill this in

    PolyNode* poly = NULL;
    PolyNode* it1 = poly1;
    PolyNode* it2 = poly2;


    while (it1 != NULL)
    {
        poly = AddNode(poly, it1->coef, it1->exp);
        it1 = it1->next;
    }

    while (it2 != NULL)
    {
        poly = AddNode(poly, -1 * it2->coef, it2->exp);
        it2 = it2->next;
    }

    return poly;
} //end-Substract

//-------------------------------------------------
// Multiplies poly1 and poly2 and returns the resulting polynomial
// Computes: poly3 = poly1 * poly2 and returns poly3
//
PolyNode* Multiply(PolyNode* poly1, PolyNode* poly2) {
    // Fill this in
    PolyNode* poly = NULL;
    PolyNode* it1 = poly1;
    PolyNode* it2 = poly2;


    while (it1 != NULL)
    {
        while (it2 != NULL)
        {
            poly = AddNode(poly, it1->coef * it2->coef, it1->exp + it2->exp);
            it2 = it2->next;
        }
        it1 = it1->next;
        it2 = poly2;
    }

    return poly;
} //end-Multiply

//-------------------------------------------------
// Evaluates the polynomial at a particular "x" value and returns the result
//
double Evaluate(PolyNode* poly, double x) {
    // Fill this in
    double result = 0;
    double temp = 0;
    PolyNode* it = poly;
    while (it != NULL)
    {
        temp = it->coef;
        for (int i = 0; i < it->exp; i++)
        {
            temp = x * temp;
        }
        it = it->next;
        result = result + temp;
    }
    return result;
} //end-Evaluate

//-------------------------------------------------
// Computes the derivative of the polynomial and returns it
// Ex: poly(x) = 3x^4 - 2x + 1-->Derivative(poly) = 12x^3 - 2
//
PolyNode* Derivative(PolyNode* poly) {
    // Fill this in
    PolyNode* result = NULL;
    while (poly != NULL)
    {
        if (poly->exp != 0)
            result = AddNode(result, poly->coef * poly->exp, poly->exp - 1);
        poly = poly->next;
    }
    return result;
} //end-Derivative

//-------------------------------------------------
// Plots the polynomial in the range [x1, x2].
// -39<=x1<x2<=39
// -12<=y<=12
// On the middle of the screen you gotta have x & y axis plotted
// During evaluation, if "y" value does not fit on the screen,
// then just skip it. Otherwise put a '*' char depicting the curve
//
void Plot(PolyNode* poly, int x1, int x2) {
    const int width = 79;  // Width of the plot
    const int height = 25; // Height of the plot
    const int xOffset = width / 2;
    const int yOffset = height / 2;

    // Create a 2D grid initialized with spaces
    char grid[height][width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            grid[i][j] = ' ';
        }
    }

    // Plot the x and y axes
    for (int i = 0; i < width; ++i) {
        grid[yOffset][i] = '-';
    }
    for (int i = 0; i < height; ++i) {
        grid[i][xOffset] = '|';
    }
    grid[yOffset][xOffset] = '+'; // Origin

    // Evaluate the polynomial at each x value in the range [x1, x2]
    for (int x = x1; x <= x2; ++x) {
        double y = Evaluate(poly, x);
        int plotX = x + xOffset;
        int plotY = yOffset - static_cast<int>(y + 0.5); // Round to nearest integer

        // Check if the point is within the grid bounds
        if (plotX >= 0 && plotX < width && plotY >= 0 && plotY < height) {
            grid[plotY][plotX] = '*';
        }
    }

    // Print the grid
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            putchar(grid[i][j]);
        }
        putchar('\n');
    }
}

