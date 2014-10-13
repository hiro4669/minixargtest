#include <iostream>
#include <stdlib.h>
#include <stdint.h>

class Test {
public:
	uint8_t *text;
	uint8_t *data;
	uint8_t *t_memory;
	uint8_t *d_memory;
	

	Test() {
		t_memory = new uint8_t[0x10000];
		d_memory = new uint8_t[0x10000];		
		init();
	}

	void init() {
		for (int i = 0; i < 100; ++i) {
			t_memory[i] = i;
		}
		for (int i = 0; i < 100; ++i) {
			d_memory[i] = i + 100;
		}
	}

	void setDiff() {
		text = t_memory;
		data = d_memory;
	}

	void setSame() {
		text = t_memory;
		data = t_memory;
	}

	uint8_t getData(int index) {
		return data[index];
	}

	~Test() {
		delete[] t_memory;
		delete[] d_memory;
	}
};

int main(void) {
	Test t;
	int index;
	t.setDiff();

	index = 10;
	printf("[%d] = %d\n", index, t.getData(index));

	t.setSame();
	printf("[%d] = %d\n", index, t.getData(index));
	return 0;
}
