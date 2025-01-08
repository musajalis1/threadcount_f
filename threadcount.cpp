#include <iostream>
#include <cuda_runtime.h>

int threadCount() {
	int deviceCount = 0;
	int totalThreads = 0;
	cudaError_t err = cudaGetDeviceCount(&deviceCount);
	if (err != cudaSuccess) {
		std::cerr << "CUDA error: " << cudaGetErrorString(err) << std::endl;
		return 0;
	}

	if (deviceCount == 0) {
		std::cerr << "Error: No CUDA-enabled GPU devices found." << std::endl;
		return 0;
	}

	for (int deviceIndex = 0; deviceIndex < deviceCount; ++deviceIndex) {
		cudaDeviceProp deviceProp;
		cudaGetDeviceProperties(&deviceProp, deviceIndex);

		int deviceThreads = deviceProp.maxThreadsPerBlock * deviceProp.multiProcessorCount;
		totalThreads += deviceThreads;
	}

	std::cout << "Total thread count:" << totalThreads << std::endl;
	return totalThreads;
}

int main() {
	threadCount();
	return 0;
}

