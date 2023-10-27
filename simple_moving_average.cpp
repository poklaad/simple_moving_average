#include <iostream>
#include <string>

bool check_data_symbols(std::string& data, const char* format) { // Checks that the string is not empty and doesn't contatin unwanted symblos
	if (data.find_first_not_of(format) == std::string::npos && data.length() != 0)
		return true;
	return false;
}

std::pair <int, int> check_initital_information_correctness(std::string sample_size_str, std::string data_type, std::string window_size_str) { // Reading and checking initial data
	
	// Checking data type
	if (data_type != "double" && data_type != "float") {
		throw "Wrong data type: " + data_type + ". Must be double or float!";
	}

	// Checking the sample size
	int sample_size;
	if (!(check_data_symbols(sample_size_str, "0123456789"))) {
		throw "Wrong sample size: " + sample_size_str + ". Must be positive integer!";
	}
	else {
		sample_size = std::stoi(sample_size_str);
	}

	// Checking the window size
	int window_size;
	if (!(check_data_symbols(window_size_str, "0123456789"))) {
		throw "Wrong window size: " + window_size_str + ". Must be positive integer!";
	}
	else {
		window_size = std::stoi(window_size_str);
	}
	
	return std::make_pair(sample_size, window_size);
}

int main() {
	try {
		// Read initial information
		std::string sample_size_str, data_type, window_size_str;
		std::cout << "Print the sample size (positive integer): ";
		std::cin >> sample_size_str;
		std::cout << "Print the window size (positive integer): ";
		std::cin >> window_size_str;
		std::cout << "Print the data type (double or float): ";
		std::cin >> data_type;

		// Verify initial data
		int sample_size, window_size;
		std::pair <int, int> pr = check_initital_information_correctness(sample_size_str, data_type, window_size_str);
		sample_size = pr.first;
		window_size = pr.first;
		if (data_type == "double") {
			double* data = new double[sample_size];
		}
		else if (data_type == "float") {
			float* data = new float[sample_size];
		}

		


	}
	catch (std::string err) {
		std::cerr << err;
		return 1;
	}


	return 0;
}