#include <iostream>
#include <string>
#include <ctime>

bool check_data_symbols(std::string& data, const char* format) { // Checks that the string is not empty and doesn't contatin unwanted symblos
	if (data.find_first_not_of(format) == std::string::npos && data.length() != 0)
		return true;
	return false;
}

void check_initital_information_correctness(std::string sample_size_str, std::string data_type, std::string window_size_str, int& sample_size, int& window_size) { // Reading and checking initial data

	// Checking data type
	if (data_type != "double" && data_type != "float") {
		throw "Wrong data type: " + data_type + ". Must be double or float!";
	}

	// Checking the sample size
	if (!(check_data_symbols(sample_size_str, "0123456789"))) {
		throw "Wrong sample size: " + sample_size_str + ". Must be positive integer!";
	}
	else {
		sample_size = std::stoi(sample_size_str);
	}

	// Checking the window size
	if (!(check_data_symbols(window_size_str, "0123456789"))) {
		throw "Wrong window size: " + window_size_str + ". Must be positive integer!";
	}
	else {
		window_size = std::stoi(window_size_str);
	}

	return;
}

template <typename T>
void generate_data(T data, int& sample_size) { // Generates array of random numbers

	srand(time(0)); 
	for (int i = 0; i < sample_size; ++i)
		data[i] = rand() / (double)RAND_MAX;

}

template <typename T>
void simple_moving_average(T data[], int& sample_size, int& window_size, T average[]) { // Calculates simple moving average
	int i;

	// Initiate first element of the SMA
	average[0] = data[0] / window_size;

	// Separated calculations for the first k = window_size elements
	for (i = 1; i < window_size; ++i) {
		average[i] = average[i - 1] + data[i] / window_size;
	}

	// Calculations for the rest elements.
	// Calculated as mentioned here: https://en.wikipedia.org/wiki/Moving_average#Simple_moving_average
	for (i = window_size; i < sample_size; ++i) {
		average[i] = average[i - 1] + (data[i] - data[i - window_size]) / window_size;
	}

	return;

}

template <typename T>
void calculatings_and_analysis(T data[], int& sample_size, int& window_size, T average[]) { // Generates data, calculates SMA, allows the user to analyse results and data 

	// Generate data
	generate_data(data, sample_size);

	std::cout << "Data has been generated. Starting SMA calculation..." << std::endl;

	// Calculate average and performance
	simple_moving_average(data, sample_size, window_size, average);



	std::cout << "SMA has been calculated." << std::endl
		<< "What can be showen:" << std::endl
		<< "0. Elapsed time" << std::endl
		<< "1. Performance" << std::endl
		<< "2. Data elements" << std::endl
		<< "3. SMA elements" << std::endl
		<< "Choose what do you want to see (0, 1, 2 or 3): ";
	std::string action;
	std::cin >> action;

}

void working_process_with_user() { // Allows the user to chose initial information, starts calculating process

	// Read initial information
	std::string sample_size_str, data_type, window_size_str;
	std::cout << "Print the sample size (positive integer): ";
	std::cin >> sample_size_str;
	std::cout << "Print the window size (positive integer): ";
	std::cin >> window_size_str;
	std::cout << "Print the data type (double or float): ";
	std::cin >> data_type;

	// Check if input is correct and write data to sample_size and window_size variables
	int sample_size, window_size;
	check_initital_information_correctness(sample_size_str, data_type, window_size_str, sample_size, window_size);

	std::cout << "Starting calculatings..." << std::endl;

	if (data_type == "double") { // Calculatings if the chosen data type is "double"

		// Memory allocation for double data and average
		double* data = new double[sample_size];
		double* average = new double[sample_size];

		// Perform calculatings and analyse it by user
		calculatings_and_analysis(data, sample_size, window_size, average);

		// Clear storage
		delete[] data;
		delete[] average;
	}
	else { // Calculatings if the chosen data type is "float"

		// Memory allocation for float data and average
		float* data = new float[sample_size];
		float* average = new float[sample_size];

		// Perform calculatings and analyse it by user
		calculatings_and_analysis(data, sample_size, window_size, average);

		// Clear storage
		delete[] data;
		delete[] average;
	}
}

void auto_comparison() { // Performs calculatings as task requires (compare perfomance with different sizes of the window)

	// Initial parametrs:
	// size of the sample 
	// window sizes, that will be compared in term of perfomance
	int sample_size = 1000000;
	int windows_arr[] = { 4, 8, 16, 32, 64, 128 };

	// Memory allocation for double and float data and average
	double* double_data = new double[sample_size];
	float* float_data = new float[sample_size];
	double* double_average = new double[sample_size];
	float* float_average = new float[sample_size];

	// Performing calculations with different sizes of window
	for (int i = 0; i < 6; ++i) {

		// Choose another window size
		int window_size = windows_arr[i];

		// Generate data, calculate average and performance for "double" data type
		generate_data(double_data, sample_size);
		simple_moving_average(double_data, sample_size, window_size, double_average);

		// Generate data, calculate average and performance for "float" data type
		generate_data(float_data, sample_size);
		simple_moving_average(float_data, sample_size, window_size, float_average);

	}

	// Clear storage
	delete[] double_data;
	delete[] float_data;
	delete[] double_average;
	delete[] float_average;
}

bool what_is_my_task() { //Asks user what program should do

	std::cout << "Ways to work:" << std::endl <<
		"0. (As task requires). Compare performance based on data type and sample size." << std::endl <<
		"1. (For testing) Look at performance and results of the function on one example." << std::endl <<
		"Choose your way (print 0 or 1): ";

	// Here user chooses what he want to see
	std::string work_way;
	std::cin >> work_way;

	// Check if the input is correct
	if (check_data_symbols(work_way, "01") && work_way.length() == 1) {
		return work_way == "1";
	}
	else {
		throw "Wrong input: " + work_way + ". Expected 0 or 1!";
	}

}


int main() {
	try {
		// true - one example; false - auto comparison
		if (what_is_my_task()) {
			// Manual work with one example. Use for manual testing. 
			// You will be able to choose initial parameters, get elements from generated data and calculated SMA.
			working_process_with_user();
		}
		else {
			// Auto comparison. Program perform exactly what task requires
			auto_comparison();
		}
		std::cout << "The end.";
	}
	catch (std::string err) {
		std::cerr << err;
		return 1;
	}


	return 0;
}
