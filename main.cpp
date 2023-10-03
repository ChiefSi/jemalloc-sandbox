#include <iostream>
#include <stdlib.h>
#include <jemalloc/jemalloc.h>
#include <chrono>
#include <thread>
#include <vector>
int main(int argc, char* argv[])
{
	std::vector<void*> values;
	{
		bool enable = true;
		void* value = reinterpret_cast<void*>(&enable);
		mallctl("prof.active", NULL, NULL, value, sizeof(bool));
	}
	{
		const char* filename = "initial.out";
		mallctl("prof.dump", NULL, NULL, &filename, sizeof(const char*));
	}

	char* value = reinterpret_cast<char*>(malloc(10));
	values.push_back(value);
	value = nullptr;
	std::thread t([&]()
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			char* v = (char*)values[0];
			free(v);
		});


	{
		const char* filename = "intermediate.out";
		mallctl("prof.dump", NULL, NULL, &filename, sizeof(const char*));
	}
	t.join();
	{
		const char* filename = "final.out";
		mallctl("prof.dump", NULL, NULL, &filename, sizeof(const char*));
	}


	{
		bool enable = false;
		void* value = reinterpret_cast<void*>(&enable);
		mallctl("prof.active", NULL, NULL, value, sizeof(bool));
	}

	return 0;
}
