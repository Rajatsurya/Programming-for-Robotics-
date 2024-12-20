#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <eigen3/Eigen/Eigen>

Eigen::MatrixXd csv2mat(std::ifstream &ifs)
{
    if (!ifs.good())
    {
        throw std::runtime_error("failed to open file!");
    }

    int rows, cols;
    ifs >> rows;
    ifs >> cols;
    Eigen::MatrixXd mat(rows, cols);

    int row = 0;
    int col = 0;
    while (ifs.peek() != ifs.eof())
    {
        double x;
        ifs >> x;
        mat(row, col) = x;
        ++col;
        if (col == cols)
        {
            col = 0;
            ++row;
        }
        if (row == rows)
        {
            break;
        }
    }
    return mat;
}

class Layer
{
public:
    Layer() {};
    virtual ~Layer() = default;
    virtual Eigen::MatrixXd forward(Eigen::MatrixXd const &x) const = 0;
};

class Linear : public Layer
{
public:
    Linear(std::string const &A_filename, std::string const &b_filename)
    {
        std::ifstream A_file(A_filename);
        std::ifstream b_file(b_filename);
        A = csv2mat(A_file);
        b = csv2mat(b_file);
    }

    Eigen::MatrixXd forward(Eigen::MatrixXd const &x) const override
    {
        return (A * x) + b.replicate(1, x.cols());
    }

private:
    Eigen::MatrixXd A;
    Eigen::MatrixXd b;
};

class ReLU : public Layer
{
public:
    ReLU() {}

    Eigen::MatrixXd forward(Eigen::MatrixXd const &x) const override
    {
        return x.array().max(0);
    }
};

class Softmax : public Layer
{
public:
    Softmax() {}

    Eigen::MatrixXd forward(Eigen::MatrixXd const &x) const override
    {
        Eigen::MatrixXd output(x.rows(), x.cols());
        
        // Process each column (sample) independently
        for(int i = 0; i < x.cols(); ++i) {
            // Get the current column
            Eigen::VectorXd col = x.col(i);
            
            // Subtract maximum value for numerical stability
            double max_val = col.maxCoeff();
            col = col.array() - max_val;
            
            // Compute exponentials
            Eigen::VectorXd exp_values = col.array().exp();
            
            // Compute sum of exponentials
            double sum_exp = exp_values.sum();
            
            // Normalize to get probabilities
            output.col(i) = exp_values / sum_exp;
        }
        
        return output;
    }
};

// Main function
int main(int argc, char* argv[])
{
    const Eigen::IOFormat vec_csv_format(3, Eigen::DontAlignCols, ", ", ", ");
    std::ofstream ofs("output.csv");

    // Load the weights, biases, and the data from files
    std::vector<std::string> data_filenames{"data1.csv", "data2.csv", "data3.csv", "data4.csv"};
    if (argc >= 2) {
        data_filenames.clear();
        for (int i{1}; i < argc; ++i) {
            data_filenames.push_back(argv[i]);
        }
    }

    // Initialize layers
    Linear l1("A1.csv", "b1.csv");
    ReLU r;
    Linear l2("A2.csv", "b2.csv");
    Softmax s;

    for (std::string const &data_filename : data_filenames)
    {
        std::cout << "Evaluating " << data_filename << '\n';
        std::ifstream ifs{data_filename};
        Eigen::MatrixXd X = csv2mat(ifs);

        // Propagate through the layers
        Eigen::MatrixXd out_l1 = l1.forward(X);       // Linear layer 1
        Eigen::MatrixXd out_relu = r.forward(out_l1); // ReLU activation
        Eigen::MatrixXd out_l2 = l2.forward(out_relu); // Linear layer 2
        Eigen::MatrixXd probabilities = s.forward(out_l2); // Softmax

        // Output probabilities to file
        ofs << probabilities.format(vec_csv_format) << std::endl;
    }

    ofs.close();
    return 0;
}
