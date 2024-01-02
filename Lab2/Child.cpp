#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
	std::cout << "Child created." << std::endl;

	if (argc > 1) {
		size_t n = atoi(argv[1]);
		std::vector<int> arr(n);

		for (int i = 2, j = 0; i < argc; ++i) { arr[j] = atoi(argv[i]); ++j; }

		for (int i = 1; i < n; i++) {
			int j = i;
			while (j > 0 && arr[j] < arr[j - 1]) {
				std::swap(arr[j], arr[j - 1]);
				--j;
			}
		}

		std::cout << "Array after sorting: ";
		for (auto i : arr) {
			std::cout << i << ' ';
		}
		std::cout << std::endl;

	}
	else {
		std::cout << "Child.exe not found" << std::endl;
	}
	return 0;
}