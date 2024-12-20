#include <iostream>
#include <initializer_list>
#include <vector>
// needed for setting printing precision
#include <iomanip>
#include <fstream>

using Coefficient = double;
class UnivariatePolynomial
{
public:
    UnivariatePolynomial() = default;
    // constructor from an initializer list of coefficients
    UnivariatePolynomial(std::vector<Coefficient>);

    // the degree of the polynomial; for simplicity, we will let the degree of
    // the zero polynomial be -1
    int degree() const;

    // change the symbol for the polynomial such as 'y' or 'x'
    void setSymbol(char c);
    // get the symbol
    char symbol() const;

    // return the derivative of the polynomial
    UnivariatePolynomial derivative() const;

    // addition operation with another polynomial
    UnivariatePolynomial operator+(const UnivariatePolynomial &) const;

    // multiplication with a scalar
    UnivariatePolynomial operator*(Coefficient) const;

    // return its coefficients
    // note that we have both a const and non-const version
    // the const version is needed when the object is const
    // this is an example of method overloading
    const std::vector<Coefficient> &coeffcients() const;
    std::vector<Coefficient> &coeffcients();

private:
    std::vector<Coefficient> _coef;
    // default initialization via assignment
    char _symbol = 'x';
};

// overload the output operator
// note that the polynomial parameter is const, so we can only use const methods on it
std::ostream &operator<<(std::ostream &out, const UnivariatePolynomial &polynomial)
{
    // do not print monomials with 0 coefficient
    // monomials with exponent above 1 should have ^exponent behind the symbol
    char symbol = polynomial.symbol();

    const std::vector<Coefficient> &coefficients = polynomial.coeffcients();

    for (std::size_t i = 0; i < coefficients.size(); i++)
    {
        if (coefficients[i] != 0.0)
        {
            if (i == 0)
            {
                out << coefficients[i];
            }
            else if (i == 1)
            {
                out << coefficients[i] << symbol;
            }
            else
            {
                out << coefficients[i] << symbol << "^" << i;
            }

            if (i < coefficients.size() - 1 && polynomial.degree() > 0)
            {
                out << " + ";
            }
        }
    }

    return out;
}

// similarly for the input stream operator
// a bit tricky because we want to only read a single line for our coefficients
// the next line belongs to the next polynomial
std::istream &operator>>(std::istream &input, UnivariatePolynomial &polynomial)
{

    Coefficient coef;
    std::string line;

    if (std::getline(input, line))
    {
        std::istringstream iss(line);
        while (iss >> coef)
        {
            polynomial.coeffcients().push_back(coef);
        }
    }

    return input;
}

// implementation of the constructor
UnivariatePolynomial::UnivariatePolynomial(std::vector<Coefficient> l)
{
    for (const Coefficient &c : l)
    {
        _coef.push_back(c);
    }
}

int UnivariatePolynomial::degree() const
{
    return _coef.size() - 1;
}

void UnivariatePolynomial::setSymbol(char c)
{
    _symbol = c;
}

char UnivariatePolynomial::symbol() const
{
    return _symbol;
}

UnivariatePolynomial UnivariatePolynomial::derivative() const
{
    std::vector<Coefficient> derivativeCoefficients;

    for (std::size_t i = 1; i < _coef.size(); i++)
    {
        derivativeCoefficients.push_back(i * _coef[i]);
    }

    return UnivariatePolynomial{derivativeCoefficients};
}

UnivariatePolynomial UnivariatePolynomial::operator+(const UnivariatePolynomial &p) const
{
    std::vector<Coefficient> resultCoefficients;

    int lowestDegree = std::min(degree(), p.degree());

    // adding coefficients up to the lowest degree
    for (int i = 0; i <= lowestDegree; i++)
    {
        resultCoefficients.push_back(_coef[i] + p.coeffcients()[i]);
    }

    // either of these polynomials have higher degree
    for (int i = lowestDegree + 1; i <= degree(); i++)
    {
        resultCoefficients.push_back(_coef[i]);
    }

    for (int i = lowestDegree + 1; i <= p.degree(); i++)
    {
        resultCoefficients.push_back(p.coeffcients()[i]);
    }

    return UnivariatePolynomial{resultCoefficients};
}

// multiplication with a scalar
UnivariatePolynomial UnivariatePolynomial::operator*(Coefficient scalar) const
{
    std::vector<Coefficient> resultCoefficients;

    for (const Coefficient &c : _coef)
    {
        resultCoefficients.push_back(c * scalar);
    }

    return UnivariatePolynomial{resultCoefficients};
}

const std::vector<Coefficient> &UnivariatePolynomial::coeffcients() const
{
    return _coef;
}

std::vector<Coefficient> &UnivariatePolynomial::coeffcients()
{
    return _coef;
}

int main()
{
    // p(x) = 1.5 + 0.2x + 5.5x^3
    UnivariatePolynomial p1{std::vector<Coefficient>{1.5, 0.2, 0, 5.5}};
    // coefficients should be printed to 1 decimal place
    std::cout << std::fixed << std::setprecision(1);

    // should print 1.5 + 0.2x + 5.5x^3
    // std::cout << p1 << std::endl;

    // create p2(x) = -0.1 + -1.4x^2
    UnivariatePolynomial p2{std::vector<Coefficient>{-0.1, 0, -1.4}};

    // should print -0.1 + -1.4x^2
    // std::cout << p2 << std::endl;

    // should print 0.2 + 16.5x^2
    // std::cout << p1.derivative() << std::endl;

    // should print 1.2 + 0.2x + -4.2x^2 + 5.5x^3
    // std::cout << p1 + p2 * 3 << std::endl;

    std::ifstream input{"input.txt"};
    std::ofstream output{"output.txt"};

    // configure output  format
    output << std::fixed << std::setprecision(1);

    output << p1 + p2 * 3 << std::endl;
    UnivariatePolynomial p_total;
    while (input.peek() != std::ifstream::traits_type::eof())
    {
        UnivariatePolynomial p;
        input >> p;
        output << p << std::endl;
        output << p.derivative() << std::endl;
        p_total = p_total + p;
    }
    output << p_total << std::endl;
    output << p_total.derivative() << std::endl;
}